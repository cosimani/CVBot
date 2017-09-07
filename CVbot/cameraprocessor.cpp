#include "cameraprocessor.h"

bool CameraProcessor::getSmiling() const
{
    return smiling;
}

void CameraProcessor::setSmiling(bool value)
{
    smiling = value;
}

bool CameraProcessor::getIsCalibrated() const
{
    return isCalibrated;
}

CameraProcessor::CameraProcessor(int rows, int cols, QObject *parent) :
    QObject( parent ),
                                                                        videoCapture ( new cv::VideoCapture( 0 ) ),
                                                                        sceneTimer ( new QTimer( this ) ),
                                                                        rows( rows ),
                                                                        cols( cols ),
                                                                        isCalibrated( false ),
                                                                        countFrameFaceless( 0 )
{
    frontalFaceClassifier.load( "../Classifiers/FrontalFace.xml" );
    smileClassifier.load( "../Classifiers/Smile.xml" );

    sceneTimer->start( 10 );
    connect( sceneTimer, SIGNAL( timeout() ), SLOT( slot_process() ) );
}

void CameraProcessor::calibrate()
{
    calibration.x = actualFace.x + actualFace.width / 4;
    calibration.y = actualFace.y + actualFace.height / 4;
    calibration.width = actualFace.width / 2;
    calibration.height = actualFace.height / 2;

    this->isCalibrated = true;
}

void CameraProcessor::discalibrate()
{
    this->isCalibrated = false;
}

CameraProcessor::~CameraProcessor()  {
    videoCapture->release();
    delete videoCapture;

    qDebug() << "Destructor de CameraProcessor";
}

void CameraProcessor::slot_process()
{
    videoCapture->operator >>( cameraTexture );
    flip( cameraTexture, cameraTexture, 1 );

    // Esta signal envia el nuevo Mat a la interfaz para que la pueda visualizar
    emit signal_newCameraFrame( &cameraTexture );



//        int index = this->getSize() - ( ( xFaceCenter - calibration.x ) / ( calibration.width / size ) ) - 1;

//        emit positionDetected( index );

//        vector< Rect > detectedSmiles;
//        detectedSmiles.clear();

//        detectedFaces.operator []( 0 ).width -= detectedFaces.operator []( 0 ).width % 3;

//        Mat face( *this->getCameraTexture(), detectedFaces.at( 0 ) );

//        smileClassifier->detectMultiScale( face, detectedSmiles,
//                                          1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 50, 50 ) );

//        if( detectedSmiles.size() > 0 )
//        {
//            if( ! this->getSmiling() )
//            {
//                emit selectionDetected( index );
//                this->setSmiling( true );
//            }
//        }
//        else
//        {
//            if( smiling )
//            {
//                this->setSmiling( false );
//            }
//        }
//    }





    /////////

    vector< Rect > detectedFaces;
    detectedFaces.clear();

    frontalFaceClassifier.detectMultiScale( cameraTexture, detectedFaces,
                                            1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );


    if( detectedFaces.size() > 0 )
    {
        actualFace = detectedFaces.at( 0 );
        countFrameFaceless = 0;
    }
    else  {
        this->isCalibrated = false;  // Si no detecta cara ya no se tiene control de la interfaz
//        emit positionDetected( -1, -1 );  // Aca desiluminamos el ultimo boton iluminado

        countFrameFaceless++;

        if ( countFrameFaceless == FRAMES_FACELESS_BACK )  {
            emit signal_nonFaceDetectedForBack();
        }
        else if ( countFrameFaceless > FRAMES_FACELESS )  {
            emit signal_nonFaceDetected();
            countFrameFaceless = 0;
        }
    }






    if( detectedFaces.size() > 0 && rows != 0 && cols != 0 )
    {
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

            Mat face( cameraTexture, detectedFaces.at( 0 ) );

            smileClassifier.detectMultiScale( face, detectedCalibrationSmiles,
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

        int xIndex = ( xFaceCenter - calibration.x ) / ( calibration.width / cols );
        int yIndex = ( yFaceCenter - calibration.y ) / ( calibration.height / rows );

        emit positionDetected( xIndex, yIndex );

        vector< Rect > detectedSmiles;
        detectedSmiles.clear();

        detectedFaces.operator []( 0 ).width -= detectedFaces.operator []( 0 ).width % 3;

        Mat face( cameraTexture, detectedFaces.at( 0 ) );

        smileClassifier.detectMultiScale( face, detectedSmiles,
                                          1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 50, 50 ) );



//        if( detectedSmiles.size() > 0 )
//        {
//            if( ! this->getSmiling() )
//            {
////                emit selectionDetected( index );
//                this->setSmiling( true );
//                emit smile();
//            }
//        }
//        else
//        {
//            emit notSmile();

//            if( smiling )
//            {
//                this->setSmiling( false );

//                    if ( xIndex == 1 && yIndex == 1 )  {
//                        this->isCalibrated = false;  // Si no detecta cara ya no se tiene control de la interfaz
//                        emit positionDetected( -1, -1 );  // Aca desiluminamos el ultimo boton iluminado
//                    }

//            }
//        }




        if ( detectedSmiles.size() > 0 )
        {
            emit smile();

        }
        else
        {
            emit notSmile();


        }


    }
}
