#ifndef CAMERAPROCESSOR_H
#define CAMERAPROCESSOR_H

#include <QTimer>

#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QDebug>

#define FRAMES_FACELESS 70
#define FRAMES_FACELESS_BACK 50


using namespace std;
using namespace cv;

class CameraProcessor : public QObject
{
    Q_OBJECT

private:

    VideoCapture *videoCapture;
    QTimer *sceneTimer;
    Mat cameraTexture;
    int rows, cols;

    CascadeClassifier frontalFaceClassifier;
    CascadeClassifier smileClassifier;

    Rect actualFace;
    Rect calibration;

    bool isCalibrated;
    int countFrameFaceless;

    bool smiling;

public:

    CameraProcessor( int rows = 1, int cols = 1, QObject *parent = 0 );

    void calibrate();

    void discalibrate();

    ~CameraProcessor();

    bool getSmiling() const;
    void setSmiling(bool value);

    bool getIsCalibrated() const;

private slots:

    void slot_process();

signals:

    void positionDetected( int x, int y );
    void smile();
    void notSmile();

    void signal_newCameraFrame( cv::Mat * cameraTexture );

    /**
     * @brief signal_nonFaceDetected Se dispara cuando se no se detecta una cara luego de una cantidad de FRAMES_FACELESS
     * frames.
     */
    void signal_nonFaceDetected();

    /**
     * @brief signal_nonFaceDetectedForBack Se dispara cuando se no se detecta una cara luego de una cantidad de
     * FRAMES_FACELESS_BACK frames. Es para volver atras en la frase que se esta armando.
     */
    void signal_nonFaceDetectedForBack();

};

#endif // CAMERAPROCESSOR_H
