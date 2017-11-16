#include "ventana.h"
#include "ui_ventana.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

#include "config.h"

Ventana::Ventana(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::Ventana),
                                    camera( new CameraThread( this ) ),
                                    cameraFondo( new CameraThread( this ) ),
                                    timerDespresionarBoton( new QTimer( this ) ),
                                    cliente( new ClienteTcp( this ) ),
                                    pArriba(new QPoint( 2, 1 ) ),
                                    pAbajo(new QPoint( 2, 3 ) ),
                                    pIzquierda(new QPoint( 1, 2 ) ),
                                    pDerecha(new QPoint( 3, 2 ) ),
                                    pCam_o_robot(new QPoint( 3, 1 ) )

//                                    pArriba(new QPoint( 1, 0 ) ),
//                                    pAbajo(new QPoint( 1, 2 ) ),
//                                    pIzquierda(new QPoint( 0, 1 ) ),
//                                    pDerecha(new QPoint( 2, 1 ) ),
//                                    pCam_o_robot(new QPoint( 2, 0 ) )
{
    ui->setupUi(this);

    camera->setTipoCaptura( CameraThread::CONTROL_MENU );
    camera->setDimension( 5, 5 );
    camera->encenderCamara( 0, 10 );

    cameraFondo->setTipoCaptura( CameraThread::SOLO_VIDEO );
//    cameraFondo->encenderCamara( -1, 10, "http://10.0.4.222:8160/" );
//    cameraFondo->encenderCamara( -1, 10, "http://192.168.2.103:8160/" );
    cameraFondo->encenderCamara( -1, 10,
                                 "tcp://" +
                                 Config::getInstance()->getString( "ip_raspberry" ) +
                                 ":" +
                                 Config::getInstance()->getString( "stream_port" ) );

    // En RPi> raspivid -t 0 -w 640 -h 480 -hf -ih -fps 15 -o - | nc -k -l 2222
    // La mejor: raspivid -n -t 0 -w 320 -h 240 -hf -vf -ih -fps 10 -o - | nc -k -l 2222

//    ffmpeg://tcp://192.168.2.103:2222

//    cameraFondo->encenderCamara( -1, 10, "rtsp://192.168.2.103:8160" );
//    cameraFondo->encenderCamara( -1, 10, "rtsp://192.168.2.103:8554/" );

    QImage imFlecha( ":/images/flecha_derecha.png" );
    QImage imFlechaSeleccionada( ":/images/flecha_derecha_seleccionada.png" );
    QImage imFlechaCliqueada( ":/images/flecha_derecha_cliqueada.png" );

    bArriba.setImages( imFlecha.mirrored( false, true ),
                       imFlechaSeleccionada.mirrored( false, true ),
                       imFlechaCliqueada.mirrored( false, true ) );
    bAbajo.setImages( imFlecha, imFlechaSeleccionada, imFlechaCliqueada );

    QImage imIconoCamara( ":/images/camara.png" );
    QImage imIconoCamaraSeleccionada( ":/images/camara_seleccionada.png" );
    QImage imIconoCamaraCliqueada( ":/images/camara_cliqueada.png" );

    queControla = CAMARA;
    bCamara_o_robot.setImages( imIconoCamara, imIconoCamaraSeleccionada, imIconoCamaraCliqueada );

    QPoint center = imFlecha.rect().center();
    QMatrix matrix;  matrix.translate(center.x(), center.y());
    matrix.rotate(90);  QImage imIzquierda = imFlecha.transformed(matrix);

    QPoint centerSeleccionada = imFlechaSeleccionada.rect().center();
    QMatrix matrixSeleccionada;  matrixSeleccionada.translate(centerSeleccionada.x(), centerSeleccionada.y());
    matrixSeleccionada.rotate(90);  QImage imIzquierdaSeleccionada = imFlechaSeleccionada.transformed(matrix);

    QPoint centerCliqueada = imFlechaCliqueada.rect().center();
    QMatrix matrixCliqueada;  matrixCliqueada.translate(centerCliqueada.x(), centerCliqueada.y());
    matrixCliqueada.rotate(90);  QImage imIzquierdaCliqueada = imFlechaCliqueada.transformed(matrix);

    bIzquierda.setImages( imIzquierda, imIzquierdaSeleccionada, imIzquierdaCliqueada );

    QImage imDerecha = imIzquierda.mirrored( true, false );
    QImage imDerechaSeleccionada = imIzquierdaSeleccionada.mirrored( true, false );
    QImage imDerechaCliqueada = imIzquierdaCliqueada.mirrored( true, false );

    bDerecha.setImages( imDerecha, imDerechaSeleccionada, imDerechaCliqueada );



    connect( camera, SIGNAL( posicionDetectada( int, int ) ), this, SLOT( slot_activarBoton( int, int ) ) );

    connect( camera, SIGNAL( seleccionDetectada( int, int ) ), this, SLOT( slot_clicBoton( int, int ) ) );

    connect( camera, SIGNAL( signal_newCameraFrame( cv::Mat * ) ),
             this, SLOT( slot_recibirFrames( cv::Mat * ) ) );

    connect( cameraFondo, SIGNAL( signal_newCameraFrame( cv::Mat * ) ),
             this, SLOT( slot_recibirFramesFondo( cv::Mat * ) ) );

    connect( timerDespresionarBoton, SIGNAL(timeout()), this, SLOT(slot_despresionarBoton()));



}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter( this );

    if ( ! imFondo.isNull() )
        painter.drawImage( 0, 0, imFondo.scaled( this->width(), this->height() ) );


    QImage imArriba = bArriba.getImage().scaled( this->width() / 4, this->height() / 4 );
    QImage imAbajo = bAbajo.getImage().scaled( this->width() / 4, this->height() / 4 );
    QImage imIzquierda = bIzquierda.getImage().scaled( this->width() / 4, this->height() / 4 );
    QImage imDerecha = bDerecha.getImage().scaled( this->width() / 4, this->height() / 4 );

    QImage imCamara_o_robot = bCamara_o_robot.getImage().scaled( this->width() / 5, this->height() / 5 );

    painter.drawImage( this->width() / 2 - imArriba.width() / 2,
                       0, imArriba );

    painter.drawImage( this->width() / 2 - imAbajo.width() / 2,
                       this->height() - imAbajo.height(),
                       imAbajo );

    painter.drawImage( 0,
                       this->height() / 2 - imIzquierda.height() / 2,
                       imIzquierda );

    painter.drawImage( this->width() - imDerecha.width(),
                       this->height() / 2 - imDerecha.height() / 2,
                       imDerecha );

    painter.drawImage( this->width() - imCamara_o_robot.width(),
                       0,
                       imCamara_o_robot );

    imCamara = imCamara.scaled( 160, 120 );
    painter.drawImage( this->width() - imCamara.width(),
                       this->height() - imCamara.height(),
                       imCamara );


}

void Ventana::keyPressEvent( QKeyEvent *e )
{
    switch( e->key() )  {
    case Qt::Key_Escape:
        this->close();
        break;
    default:;
    }
}

void Ventana::closeEvent(QCloseEvent *e)
{
    camera->detenerCamara();
    cameraFondo->detenerCamara();
}

void Ventana::slot_activarBoton( int columna , int fila )
{
    qDebug() << "Se activo columna" << columna << " fila " << fila;

    if ( columna == pArriba->x() && fila == pArriba->y() )  {  // Arriba
        bArriba.setSeleccionado( true );
        bAbajo.setSeleccionado( false );
        bIzquierda.setSeleccionado( false );
        bDerecha.setSeleccionado( false );
        bCamara_o_robot.setSeleccionado( false );
    }
    else if ( columna == pAbajo->x() && fila == pAbajo->y() )  {  // Abajo
        bArriba.setSeleccionado( false );
        bAbajo.setSeleccionado( true );
        bIzquierda.setSeleccionado( false );
        bDerecha.setSeleccionado( false );
        bCamara_o_robot.setSeleccionado( false );
    }
    else if ( columna == pIzquierda->x() && fila == pIzquierda->y() )  {  // Izquierda
        bArriba.setSeleccionado( false );
        bAbajo.setSeleccionado( false );
        bIzquierda.setSeleccionado( true );
        bDerecha.setSeleccionado( false );
        bCamara_o_robot.setSeleccionado( false );
    }
    else if ( columna == pDerecha->x() && fila == pDerecha->y() )  {  // Derecha
        bArriba.setSeleccionado( false );
        bAbajo.setSeleccionado( false );
        bIzquierda.setSeleccionado( false );
        bDerecha.setSeleccionado( true );
        bCamara_o_robot.setSeleccionado( false );
    }
    else if ( columna == pCam_o_robot->x() && fila == pCam_o_robot->y() )  {  // Cam o robot
        bArriba.setSeleccionado( false );
        bAbajo.setSeleccionado( false );
        bIzquierda.setSeleccionado( false );
        bDerecha.setSeleccionado( false );
        bCamara_o_robot.setSeleccionado( true );
    }
    else  {  // Ninguno
        bArriba.setSeleccionado( false );
        bAbajo.setSeleccionado( false );
        bIzquierda.setSeleccionado( false );
        bDerecha.setSeleccionado( false );
        bCamara_o_robot.setSeleccionado( false );
    }

    this->repaint();

}

void Ventana::slot_clicBoton( int columna, int fila )
{
    qDebug() << "Clic sobre columna " << columna << " fila " << fila;

    // Hacemos esto para que no se cambie el estado de los botones durante 300 milisegundos, que es el tiempo
    // en que se ejecuta este timer. Tambien evita que se envien rafagas de mensaes TCP. Por lo menos nos
    // aseguramos que esten separados 300 ms como m[nimo
    if ( timerDespresionarBoton->isActive() )  {

        return;
    }

    if ( columna == pArriba->x() && fila == pArriba->y() )  {  // Arriba
        bArriba.setPresionado( true );
        bAbajo.setPresionado( false );
        bIzquierda.setPresionado( false );
        bDerecha.setPresionado( false );
        bCamara_o_robot.setPresionado( false );

        if ( queControla == ROBOT )
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "arriba robot" );
        else
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "arriba camara" );
    }
    else if ( columna == pAbajo->x() && fila == pAbajo->y() )  {  // Abajo
        bArriba.setPresionado( false );
        bAbajo.setPresionado( true );
        bIzquierda.setPresionado( false );
        bDerecha.setPresionado( false );
        bCamara_o_robot.setPresionado( false );
        if ( queControla == ROBOT )
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "abajo robot" );
        else
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "abajo camara" );


    }
    else if ( columna == pIzquierda->x() && fila == pIzquierda->y() )  {  // Izquierda
        bArriba.setPresionado( false );
        bAbajo.setPresionado( false );
        bIzquierda.setPresionado( true );
        bDerecha.setPresionado( false );
        bCamara_o_robot.setPresionado( false );
        if ( queControla == ROBOT )
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "izquierda robot" );
        else
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "izquierda camara" );

    }
    else if ( columna == pDerecha->x() && fila == pDerecha->y() )  {  // Derecha
        bArriba.setPresionado( false );
        bAbajo.setPresionado( false );
        bIzquierda.setPresionado( false );
        bDerecha.setPresionado( true );
        bCamara_o_robot.setPresionado( false );
        if ( queControla == ROBOT )
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "derecha robot" );
        else
            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "derecha camara" );


    }
    else if ( columna == pCam_o_robot->x() && fila == pCam_o_robot->y() )  {  // Cam o robot
        bArriba.setPresionado( false );
        bAbajo.setPresionado( false );
        bIzquierda.setPresionado( false );
        bDerecha.setPresionado( false );

        if ( queControla == CAMARA)  {
            QImage imIconoRobot( ":/images/robot.png" );
            QImage imIconoRobotSeleccionada( ":/images/robot_seleccionada.png" );
            QImage imIconoRobotCliqueada( ":/images/robot_cliqueada.png" );

            bCamara_o_robot.setImages( imIconoRobot, imIconoRobotSeleccionada, imIconoRobotCliqueada );
            queControla = ROBOT;

            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "Controlar robot" );
        }
        else if ( queControla == ROBOT)  {
            QImage imIconoCamara( ":/images/camara.png" );
            QImage imIconoCamaraSeleccionada( ":/images/camara_seleccionada.png" );
            QImage imIconoCamaraCliqueada( ":/images/camara_cliqueada.png" );

            bCamara_o_robot.setImages( imIconoCamara, imIconoCamaraSeleccionada, imIconoCamaraCliqueada );
            queControla = CAMARA;

            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "Controlar camara" );

        }
        else  {
            QImage imIconoCamara( ":/images/camara.png" );
            QImage imIconoCamaraSeleccionada( ":/images/camara_seleccionada.png" );
            QImage imIconoCamaraCliqueada( ":/images/camara_cliqueada.png" );

            bCamara_o_robot.setImages( imIconoCamara, imIconoCamaraSeleccionada, imIconoCamaraCliqueada );
            queControla = CAMARA;

            cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                                Config::getInstance()->getString( "data_port" ).toInt(),
                                "Controlar camara" );

        }
        bCamara_o_robot.setPresionado( true );
    }
    else  {  // Ninguno
        bArriba.setPresionado( false );
        bAbajo.setPresionado( false );
        bIzquierda.setPresionado( false );
        bDerecha.setPresionado( false );
        bCamara_o_robot.setPresionado( false );

        cliente->mensajear( Config::getInstance()->getString( "ip_raspberry" ),
                            Config::getInstance()->getString( "data_port" ).toInt(),
                            "detener robot" );

    }

    timerDespresionarBoton->start( 300 );

    this->repaint();
}

void Ventana::slot_recibirFrames( cv::Mat * frame )
{
    if ( frame->rows == 0 )  {
        return;
    }

//    cv::resize( frame, frame, cv::Size( 320, 240 ) );  // resize image

    QImage image = QImage( (uchar*) frame->data, frame->cols, frame->rows, frame->step, QImage::Format_RGB888 );
    imCamara = image.rgbSwapped();
    this->repaint();

}

void Ventana::slot_recibirFramesFondo( cv::Mat * frame )
{
    if ( frame->rows == 0 )  {
        return;
    }
    QImage image = QImage( (uchar*) frame->data, frame->cols, frame->rows, frame->step, QImage::Format_RGB888 );
    imFondo = image.rgbSwapped();
    this->repaint();

}

void Ventana::slot_despresionarBoton()
{
    bArriba.setPresionado( false );
    bAbajo.setPresionado( false );
    bIzquierda.setPresionado( false );
    bDerecha.setPresionado( false );

    timerDespresionarBoton->stop();
}
