#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QWidget>

#include <QSerialPort>

namespace Ui {
class Controlador;
}

class Controlador : public QWidget
{
    Q_OBJECT

public:
    explicit Controlador(QWidget *parent = 0);
    ~Controlador();

private:
    Ui::Controlador *ui;

    QSerialPort * serial;

private slots:
    void avanzar();
    void retorceder();
    void izquierda();
    void derecha();
    void detener();
};

#endif // CONTROLADOR_H
