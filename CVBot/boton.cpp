#include "boton.h"
#include <QPainter>
#include <QDebug>

Boton::Boton( QWidget * parent ) : QWidget( parent ),
                                   isSeleccionado( false ),
                                   isPresionado( false )
{

}

void Boton::setImages( QImage imNormal, QImage imSeleccionada, QImage imCliqueada )
{
    this->imNormal = imNormal;
    this->imSeleccionada = imSeleccionada;
    this->imCliqueada = imCliqueada;
    this->imParaMostrar = imNormal;
    repaint();
}

QImage Boton::getImage()  {
    return imParaMostrar;
}

/**
 * @brief Boton::setSeleccionado Le agrega el efecto de boton seleccionado
 */
void Boton::setSeleccionado( bool seleccionado )
{
    if ( seleccionado )  {

        imParaMostrar = imSeleccionada;

//        for ( int x=0 ; x<im.width() ; x++ )  {
//            for ( int y=0 ; y<im.height() ; y++ )  {
//                QColor color = im.pixelColor( x, y );  // typedef unsigned int QRgb;
//                if ( color.alpha() != 0 )  {
//                    if ( ! isSeleccionado )  {
//                        QColor nuevoColor( color.red(), color.green()+80, color.blue(), color.alpha() );
//                        im.setPixelColor( x, y, nuevoColor );
//                    }
//                }
//            }
//        }
    }
    else  {
        imParaMostrar = imNormal;
//        for ( int x=0 ; x<im.width() ; x++ )  {
//            for ( int y=0 ; y<im.height() ; y++ )  {
//                QColor color = im.pixelColor( x, y );  // typedef unsigned int QRgb;
//                if ( color.alpha() != 0 )  {
//                    if ( isSeleccionado )  {
//                        QColor nuevoColor( color.red(), color.green()-80, color.blue(), color.alpha() );
//                        im.setPixelColor( x, y, nuevoColor );
//                    }

//                }
//            }
//        }
    }

    this->isSeleccionado = seleccionado;

    repaint();
}

/**
 * @brief Boton::setSeleccionado Le agrega el efecto de boton presionado
 */
void Boton::setPresionado( bool presionado )
{
    if ( presionado )  {
        imParaMostrar = imCliqueada;
//        for ( int x=0 ; x<im.width() ; x++ )  {
//            for ( int y=0 ; y<im.height() ; y++ )  {
//                QColor color = im.pixelColor( x, y );  // typedef unsigned int QRgb;
//                if ( color.alpha() != 0 )  {
//                    if ( ! isPresionado )  {
//                        QColor nuevoColor( color.red()-150, color.green(), color.blue(), color.alpha() );
//                        im.setPixelColor( x, y, nuevoColor );
//                    }
//                }
//            }
//        }
    }
    else  {
        imParaMostrar = imNormal;
//        for ( int x=0 ; x<im.width() ; x++ )  {
//            for ( int y=0 ; y<im.height() ; y++ )  {
//                QColor color = im.pixelColor( x, y );  // typedef unsigned int QRgb;
//                if ( color.alpha() != 0 )  {
//                    if ( isPresionado )  {
//                        QColor nuevoColor( color.red()+150, color.green(), color.blue(), color.alpha() );
//                        im.setPixelColor( x, y, nuevoColor );
//                    }
//                }
//            }
//        }
    }

    this->isPresionado = presionado;

    repaint();
}

void Boton::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    painter.drawImage( 0, 0, imParaMostrar );
}

void Boton::mousePressEvent(QMouseEvent *)
{
    emit signal_clic();
}
