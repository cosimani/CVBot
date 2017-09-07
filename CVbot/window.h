#ifndef WINDOW_H
#define WINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include "container.h"
#include <QKeyEvent>
#include "camerawidget.h"

class Window : public QWidget
{
    Q_OBJECT

public:

    QImage backgroundImage;
    Container *container;
    QPushButton *calibrateButton;
    QGridLayout *layout;

    CameraWidget * cameraWidget;

    Window( int containerRows = 1,
            int containerCols = 1,
            QWidget *parent = 0 );

    ~Window();

protected:

    void paintEvent( QPaintEvent * );

    void closeEvent(QCloseEvent *);

    void keyPressEvent( QKeyEvent * e );

private slots:

    void slot_calibrate();
};

#endif // WINDOW_H
