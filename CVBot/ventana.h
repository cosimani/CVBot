#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QImage>

#include "processor/camera.h"
#include "camerathread.h"
#include "boton.h"
#include "clientetcp.h"

namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();

    enum QueControla { ROBOT, CAMARA };

private:
    Ui::Ventana *ui;

    CameraThread * camera;
    CameraThread * cameraFondo;
    QImage imCamara, imFondo;
    Boton bArriba, bAbajo, bIzquierda, bDerecha, bCamara_o_robot;

    QTimer * timerDespresionarBoton;

    QueControla queControla;

    ClienteTcp * cliente;

    // Son las ubicaciones de los botones. columna = x | fila = y
    QPoint * pArriba, * pAbajo, * pIzquierda, * pDerecha, * pCam_o_robot;


protected:
    void paintEvent( QPaintEvent * );
    void keyPressEvent( QKeyEvent * e );
    void closeEvent( QCloseEvent * e );

private slots:
    void slot_activarBoton( int columna , int fila );
    void slot_clicBoton( int columna , int fila );

    void slot_recibirFrames( cv::Mat * frame );
    void slot_recibirFramesFondo( cv::Mat * frame );

    void slot_despresionarBoton();

};

#endif // VENTANA_H
