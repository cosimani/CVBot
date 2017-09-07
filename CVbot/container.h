#ifndef CONTAINER_H
#define CONTAINER_H

#include <QVector>

#include "block.h"
#include "cameraprocessor.h"

#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>

class Container : public QWidget
{
    Q_OBJECT

private:

    QGridLayout *layout;
    QVector< QVector < Block * > *> *blocks;

    CameraProcessor *cameraProcessor;
    int activatedBlockX, activatedBlockY;

    QSerialPort * serial;

public:

    Container( int rows = 1, int cols = 1, QWidget *parent = 0 );

    ~Container();

    void setBlock( int row, int col, Block *block );

    void calibrate();

    QSerialPort *getSerial() const;

    CameraProcessor *getCameraProcessor() const;

protected:
    void closeEvent(QCloseEvent *);

private slots:

    void slot_activateCell( int row, int col );

    void slot_clickCell();

    void slot_releaseCell();

};

#endif // CONTAINER_H

