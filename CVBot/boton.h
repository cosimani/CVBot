#ifndef BOTON_H
#define BOTON_H

#include <QWidget>
#include <QImage>

class Boton : public QWidget
{
    Q_OBJECT
public:
    explicit Boton( QWidget * parent = nullptr );

    void setImages(QImage imNormal , QImage imSeleccionada, QImage imCliqueada);
    void setSeleccionado( bool seleccionado );

    QImage getImage();

    void setPresionado(bool presionado);
private:
    QImage imParaMostrar, imNormal, imSeleccionada, imCliqueada;
    bool isSeleccionado;
    bool isPresionado;

protected:
    void paintEvent( QPaintEvent * );
    void mousePressEvent( QMouseEvent * );

signals:
    /**
     * @brief signal_clic Se emite cuando se hace clic con el mouse
     */
    void signal_clic();

public slots:
};

#endif // BOTON_H
