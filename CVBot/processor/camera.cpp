#include "camera.h"

#include <QDebug>
#include <QCameraInfo>
#include <QCamera>



Camera::Camera( QObject *parent ) : QObject( parent ),
    isCalibrated( false ),
    countFrameFaceless( 0 ),
    dim( new Dimension( 3, 3 ) ),
                                    indexColumnaActual( -1 ),
                                    indexFilaActual( -1 ),
                                    tipoCaptura( NO_DEFINIDO )
{
    videoCapture = new VideoCapture;

    this->sceneTimer = new QTimer( this );
    cameraTexture = new Mat();

    QString faceClassifier( APPLICATION_PATH );
    faceClassifier.append( CLASSIFIERS_PATH );
    faceClassifier.append( "face.xml" );
    string face = faceClassifier.toStdString();
//    qDebug() << faceClassifier;

    QString smileClassifier( APPLICATION_PATH );
    smileClassifier.append( CLASSIFIERS_PATH );
    smileClassifier.append( "smile.xml" );
    string smile = smileClassifier.toStdString();

    this->setFrontalFaceClassifier( new CascadeClassifier( face ) );
    this->setSmileClassifier( new CascadeClassifier( smile ) );
    this->setSize( 0 );

    connect( sceneTimer, SIGNAL( timeout() ), SLOT( process() ) );

    // No lo iniciamos porque lo hacemos en encender camara
//    this->getSceneTimer()->start( 10 );
}

Camera::~Camera()
{
    sceneTimer->stop();
    videoCapture->release();
}

Camera::TipoCaptura Camera::getTipoCaptura() const
{
    return tipoCaptura;
}

void Camera::setTipoCaptura(const TipoCaptura &value)
{
    tipoCaptura = value;
}


CascadeClassifier *Camera::getFrontalFaceClassifier() const
{
    return frontalFaceClassifier;
}

void Camera::setFrontalFaceClassifier( CascadeClassifier *value )
{
    frontalFaceClassifier = value;
}

CascadeClassifier *Camera::getSmileClassifier() const
{
    return smileClassifier;
}

void Camera::setSmileClassifier( CascadeClassifier *value )
{
    smileClassifier = value;
}

int Camera::getSize() const
{
    return size;
}

void Camera::setSize( int value )
{
    size = value;
}

bool Camera::getSmiling() const
{
    return smiling;
}

void Camera::setSmiling( bool value )
{
    smiling = value;
}

void Camera::detenerCamara()
{
    sceneTimer->stop();
    videoCapture->release();
}

/**
 * @brief Camera::encenderCamara Enciende la camara y empieza a procesar las imagenes cada esos milisegundos
 * @param milisegundos
 */
void Camera::encenderCamara( int indexCamara, int milisegundos, QString url )
{
    bool exito = false;

    if ( ! url.isEmpty() && indexCamara == -1 )  {
        exito = videoCapture->open( url.toStdString().c_str() );
    }
    else  {
        exito = videoCapture->open( indexCamara );
    }

    if ( ! exito )  {
        qDebug() << "No se pudo con open de VideoCapture";
        return;
    }

    sceneTimer->setInterval( milisegundos );
    sceneTimer->start();
}

void Camera::process()
{
    // Retornamos porque es condicion que se setee alguno tipo de captura, sino ni se obtienen las imagenes
    if ( tipoCaptura == NO_DEFINIDO )
        return;

    videoCapture->operator>>( *cameraTexture );

    // Esta signal envia el nuevo Mat a la interfaz para que la pueda visualizar
    emit signal_newCameraFrame( cameraTexture );

    // Retornamos porque esta configurado solo para obtener las imagenes de la camara sin procesarlas
    if ( tipoCaptura == SOLO_VIDEO )
        return;

    // Si las dimensiones no estan seteadas, no vale la pena continuar
    if ( dim->columnas == 0 || dim->filas == 0 )
        return;

    vector< Rect > detectedFaces;
    detectedFaces.clear();

    frontalFaceClassifier->detectMultiScale( *cameraTexture, detectedFaces,
                                             1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );

    if( detectedFaces.size() > 0 )
    {
        currentFace = detectedFaces.at( 0 );
        countFrameFaceless = 0;

        int xFaceCenter = detectedFaces.at( 0 ).x + detectedFaces.at( 0 ).width / 2;
        int yFaceCenter = detectedFaces.at( 0 ).y + detectedFaces.at( 0 ).height / 2;

        // Entra a este if cuando aun no esta calibrado. Directamente retorna. Pero en esta version le agregamos la
        // posibilidad de calibrar con la sonrisa. Entonces, dentro de aqui detectamos sonrisas.
        if( ( xFaceCenter < calibration.x ||
              xFaceCenter > calibration.x + calibration.width ||
              yFaceCenter < calibration.y ||
              yFaceCenter > calibration.y + calibration.height )
              || this->isCalibrated == false )
        {
            vector< Rect > detectedCalibrationSmiles;
            detectedCalibrationSmiles.clear();

            detectedFaces.operator []( 0 ).width -= detectedFaces.operator []( 0 ).width % 3;

            Mat face( *cameraTexture, detectedFaces.at( 0 ) );

            smileClassifier->detectMultiScale( face, detectedCalibrationSmiles,
                                               1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 50, 50 ) );

            // Si detecta sonrisa, entonces calibramos
            if( detectedCalibrationSmiles.size() > 0 )
            {
                // El getSmiling setSmiling y smiling es para evitar que la sonrisa sea detectada en frames consecutivos
                if( ! this->getSmiling() )
                {
                    this->calibrate();
                    this->setSmiling( true );
                }
            }
            else
            {
                if( smiling )
                {
                    this->setSmiling( false );
                }
            }
        }

        // Si no esta calibrado, entonces no se puede controlar el menu.
        if ( ! this->isCalibrated )  {
            return;
        }

//        int index = this->getSize() - ( ( xFaceCenter - calibration.x ) / ( calibration.width / size ) ) - 1;

        int indexColumna = dim->columnas - ( ( xFaceCenter - calibration.x ) /
                                           ( calibration.width / dim->columnas ) ) - 1;
        int indexFila = ( yFaceCenter - calibration.y ) / ( calibration.height / dim->filas );

        // Son validaciones para que columna y fila detectada se mantenga siempre entre los limites
        // de las cantidad e columnas y filas seteadas para el menu a controlar
        if ( indexColumna < 0 )  indexColumna = 0;
        if ( indexFila < 0 )  indexFila = 0;
        if ( indexColumna >= dim->columnas )  indexColumna = dim->columnas - 1;
        if ( indexFila >= dim->filas )  indexFila = dim->filas - 1;

        // Para que no se emita constantemente sino cuando hay nuevos indexes
        if ( this->indexColumnaActual != indexColumna || this->indexFilaActual != indexFila )  {

            emit posicionDetectada( indexColumna, indexFila );

            this->indexColumnaActual = indexColumna;
            this->indexFilaActual = indexFila;

        }

//        emit positionDetected( index );

        vector< Rect > detectedSmiles;
        detectedSmiles.clear();

        detectedFaces.operator []( 0 ).width -= detectedFaces.operator []( 0 ).width % 3;

        Mat face( *cameraTexture, detectedFaces.at( 0 ) );

        smileClassifier->detectMultiScale( face, detectedSmiles,
                                          1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 50, 50 ) );

        if( detectedSmiles.size() > 0 )
        {
            if( ! this->getSmiling() )
            {
//                emit selectionDetected( index );
                emit seleccionDetectada( indexColumna, indexFila );
                this->setSmiling( true );
            }
        }
        else
        {
            if( smiling )
            {
                this->setSmiling( false );
            }
        }
    }
    else  {
        this->isCalibrated = false;  // Si no detecta cara ya no se tiene control de la interfaz

        // Para que no se emita constantemente sino cuando hay nuevos indexes
        if ( this->indexColumnaActual != -1 || this->indexFilaActual != -1 )  {

            emit posicionDetectada( -1, -1 );  // Aca desiluminamos el ultimo boton iluminado

            this->indexColumnaActual = -1;
            this->indexFilaActual = -1;
        }

        countFrameFaceless++;

        if ( countFrameFaceless == FRAMES_FACELESS_BACK )  {
            emit signal_nonFaceDetectedForBack();
        }
        else if ( countFrameFaceless > FRAMES_FACELESS )  {
            emit signal_nonFaceDetected();
            countFrameFaceless = 0;
        }
    }
}

/**
 * @brief Camera::calibrate Se calibra definiendo un cv::Rect que es un rectangulo que es de la mitad de
 * tamano que el rectangulo detectado de la cara y centrado en el cara.
 */
void Camera::calibrate()
{
    calibration.x = currentFace.x + currentFace.width / 4;
    calibration.y = currentFace.y + currentFace.height / 4;
    calibration.width = currentFace.width / 2;
    calibration.height = currentFace.height / 2;

    this->isCalibrated = true;
}

void Camera::setDimension( int columnas, int filas )
{
    tipoCaptura = CONTROL_MENU;
    dim->columnas = columnas;
    dim->filas = filas;
}



