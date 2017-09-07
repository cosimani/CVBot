#include "container.h"


CameraProcessor *Container::getCameraProcessor() const
{
    return cameraProcessor;
}

Container::Container(int rows, int cols, QWidget *parent) :
    QWidget( parent ),
                                                            layout( new QGridLayout( this ) ),
                                                            blocks( new QVector< QVector< Block * > * >( rows ) ),
                                                            cameraProcessor( new CameraProcessor( rows, cols ) ),
                                                            activatedBlockX( -1 ),
                                                            activatedBlockY( -1 ),
                                                            serial( new QSerialPort( this ) )
{
    for( int i = 0; i < rows; i++ )
        blocks->operator []( i ) = new QVector< Block * >( cols );

    layout->setSpacing( 10 );
    this->setLayout( layout );

    connect( cameraProcessor, SIGNAL( positionDetected( int, int ) ), SLOT( slot_activateCell( int, int ) ) );
    connect( cameraProcessor, SIGNAL( smile() ), SLOT( slot_clickCell() ) );
    connect( cameraProcessor, SIGNAL( notSmile() ), SLOT( slot_releaseCell() ) );

    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    bool exito = serial->open(QIODevice::WriteOnly);

    if ( ! exito )  {
        QMessageBox::critical( this, " NO ", "No se conecto para escribir con arduino");
        qDebug() << "No se conecto para escribir con arduino";
    }

}

Container::~Container()  {
    serial->write("<1,0,255>");  // Detiene
    serial->disconnect();

    delete cameraProcessor;

    qDebug() << "Destructor de Container";
}

void Container::setBlock(int row, int col, Block *block)
{
    blocks->operator []( row )->operator []( col ) = block;
    layout->addWidget( block, row, col );
}

void Container::calibrate()
{
    cameraProcessor->calibrate();
}

QSerialPort *Container::getSerial() const  {
    return serial;
}

void Container::closeEvent(QCloseEvent *)  {
    qDebug() << "Se cierra Container";
}

void Container::slot_activateCell(int row, int col)
{
    if ( row == -1 && col == -1 )  {
        qDebug() << "-1 -1";

        if ( serial->isOpen() )
            serial->write("<1,0,255>");  // Detiene

        blocks->at( activatedBlockX )->at( activatedBlockY )->deactivate();
        this->cameraProcessor->discalibrate();
    }

    if( row < 0 || row >= blocks->at( 0 )->size() ||
            col < 0 || col >= blocks->size() ) return;

    if( row == activatedBlockY && col == activatedBlockX )
    {
        return;
    }
    else
    {
        if( activatedBlockX != -1 && activatedBlockY != -1 )
            blocks->at( activatedBlockX )->at( activatedBlockY )->deactivate();

        blocks->at( col )->at( row )->activate();

        if ( serial->isOpen() )  {
            if ( col == 1 && row == 0 )
                serial->write("<1,4,255>");  // Izquierda
            else if ( col == 1 && row == 1 )
                serial->write("<1,0,255>");  // Detiene
            else if ( col == 1 && row == 2 )
                serial->write("<1,3,255>");  // Derecha
            else if ( col == 0 && row == 1 )
                serial->write("<1,1,255>");  // Avanza
            else if ( col == 2 && row == 1 )
                serial->write("<1,2,255>");  // Retrocede
            else
                serial->write("<1,0,255>");  // Detiene
        }

        activatedBlockX = col;
        activatedBlockY = row;
    }
}

void Container::slot_clickCell()
{
    blocks->at( activatedBlockX )->at( activatedBlockY )->click();

}

void Container::slot_releaseCell()
{
    blocks->at( activatedBlockX )->at( activatedBlockY )->release();
}

