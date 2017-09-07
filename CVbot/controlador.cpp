#include "controlador.h"
#include "ui_controlador.h"
#include <QMessageBox>

Controlador::Controlador(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::Controlador),
                                            serial( new QSerialPort( this ) )
{
    ui->setupUi(this);

    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    bool exito = serial->open(QIODevice::WriteOnly);

    if ( ! exito )  {
        QMessageBox::critical( this, " NO ", " no se conecto para escribir con arduino");
    }

    connect(ui->pbAvanzar, SIGNAL(pressed()), this, SLOT(avanzar()));
    connect(ui->pbDerecha, SIGNAL(pressed()), this, SLOT(derecha()));
    connect(ui->pbIzquierda, SIGNAL(pressed()), this, SLOT(izquierda()));
    connect(ui->pbRetroceder, SIGNAL(pressed()), this, SLOT(retorceder()));
    connect(ui->pbParar, SIGNAL(pressed()), this, SLOT(detener()));
}

Controlador::~Controlador()
{
    delete ui;
}

void Controlador::avanzar()
{
    if ( serial->isOpen() )  {
        QByteArray data = "<1,1,255>";
        serial->write(data);
    }
}

void Controlador::retorceder()
{
    if ( serial->isOpen() )  {
        QByteArray data = "<1,2,255>";
        serial->write(data);
    }

}

void Controlador::izquierda()
{
    if ( serial->isOpen() )  {
        QByteArray data = "<1,4,255>";
        serial->write(data);
    }
}

void Controlador::derecha()
{
    if ( serial->isOpen() )  {
        QByteArray data = "<1,3,255>";
        serial->write(data);
    }
}

void Controlador::detener()
{
    if ( serial->isOpen() )  {
        QByteArray data = "<1,0,255>";
        serial->write(data);
    }
}
