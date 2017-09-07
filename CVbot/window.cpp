#include "window.h"


Window::Window(int containerRows, int containerCols, QWidget *parent) : QWidget( parent ),
                                container( new Container( containerRows, containerCols, this ) ),
                                calibrateButton( new QPushButton( "Calibrar", this ) ),
                                layout( new QGridLayout( this ) ),
                                cameraWidget( new CameraWidget )
{
    backgroundImage.load( "../Images/Background.jpg" );
    layout->addWidget( container, 0, 0, 1, 1, Qt::AlignCenter );
    layout->addWidget( calibrateButton, 1, 0, 1, 1, Qt::AlignCenter );
    this->setLayout( layout );

    connect( calibrateButton, SIGNAL( clicked() ), SLOT( slot_calibrate() ) );

    connect( container->getCameraProcessor(), SIGNAL( signal_newCameraFrame(cv::Mat*) ),
             cameraWidget, SLOT( slot_setCameraTexture(cv::Mat*) ) );

}

Window::~Window()  {
    delete container;
    qDebug() << "Destructor de Window";
}

void Window::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    if( !backgroundImage.isNull() )
        painter.drawImage( this->width() / 2 - backgroundImage.width() / 2,
                           this->height() / 2 - backgroundImage.height() / 2,
                           backgroundImage );
}

void Window::closeEvent(QCloseEvent *)  {
    qDebug() << "Se cierra Window";
}

void Window::keyPressEvent(QKeyEvent *e)  {

    qDebug() << "key window" << e->key();

    if ( container->getSerial()->isOpen() )  {
        switch ( e->key() )  {
        case Qt::Key_W:
            container->getSerial()->write("<1,1,255>");  // Avanza
            break;
        case Qt::Key_S:
            container->getSerial()->write("<1,2,255>");  // Retrocede
            break;
        case Qt::Key_Space:
            container->getSerial()->write("<1,0,255>");  // Detiene
            break;
        case Qt::Key_A:
            container->getSerial()->write("<1,3,255>");  // Derecha
            break;
        case Qt::Key_D:
            container->getSerial()->write("<1,4,255>");  // Izquierda
            break;
        case Qt::Key_Escape:
            container->getSerial()->write("<1,0,255>");  // Detiene
            this->close();
            break;

        case Qt::Key_O:
            container->getSerial()->write("<1,0,255>");  // Detiene
            container->getCameraProcessor()->discalibrate();
            break;

        case Qt::Key_Z:  // Mostrar el widget de la camara para ver que esta tomando
            if ( cameraWidget->isVisible() )  {
                cameraWidget->setParent(NULL);
    //            cameraWidget->move( 0, this->height() );
                cameraWidget->hide();
            }
            else  {
    //            cameraWidget->setWindowFlags( Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::Window );
                cameraWidget->setWindowFlags( Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint );

                cameraWidget->resize( 640/4, 480/4 );
                cameraWidget->move( 10, this->height()-cameraWidget->height()-10 );

                // Le quitamos el focu para que no impida detectar las teclas
                cameraWidget->setFocusPolicy(Qt::NoFocus);

                cameraWidget->setParent(this);

                cameraWidget->show();
            }
            break;
        default:
            container->getSerial()->write("<1,0,255>");  // Detiene
        }
    }
    else
        qDebug() << "No esta conectado al serial";
}

void Window::slot_calibrate()
{
    this->container->calibrate();
}
