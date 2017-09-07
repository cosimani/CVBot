#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QGridLayout>
#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

class Block : public QWidget
{
    Q_OBJECT

private:

    QGridLayout *layout;
    QLabel *label;
    QPalette *palette;
    QImage image;

public:

    Block( QString iconName, QString text, int size, QWidget *parent = 0 ) :
                                                     QWidget( parent ),
                                                     layout( new QGridLayout ),
                                                     label( new QLabel( text ) ),
                                                     palette( new QPalette )
    {
        label->setFont( QFont( "Segoe UI", 14 ) );
        this->setFixedSize( size, size );

        layout->addWidget( this->label, 0, 0, 1, 1, Qt::AlignBottom );
        this->setLayout( layout );

        palette->setColor( QPalette::Background, QColor( 0, 0, 100, 200 ) );
        palette->setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
        this->setAutoFillBackground( true );
        this->setPalette( *palette );

        image.load( "../Images/" + iconName );
        this->repaint();
    }

    void setText( QString text )
    {
        label->setText( text );
    }

    void activate()
    {
        palette->setColor( QPalette::Background, QColor( 0, 0, 255, 200 ) );
        this->setPalette( *palette );
    }

    void deactivate()
    {
        palette->setColor( QPalette::Background, QColor( 0, 0, 100, 200 ) );
        this->setPalette( *palette );
    }

    void click()
    {
        palette->setColor( QPalette::Background, QColor( 0, 255, 0, 200 ) );
        this->setPalette( *palette );

        emit clicked();
    }

    void release()
    {
        palette->setColor( QPalette::Background, QColor( 0, 0, 255, 200 ) );
        this->setPalette( *palette );

        emit released( this );
    }

protected:

    bool event( QEvent *event )
    {
        if( event->type() == QEvent::Enter )
        {
            palette->setColor( QPalette::Background, QColor( 0, 0, 255, 200 ) );
            this->setPalette( *palette );
        }

        if( event->type() == QEvent::Leave )
        {
            palette->setColor( QPalette::Background, QColor( 0, 0, 100, 200 ) );
            this->setPalette( *palette );
        }

        return QWidget::event( event );
    }

    void paintEvent( QPaintEvent * )
    {
        QPainter painter( this );

        if( !image.isNull() )
        {
            painter.drawImage( this->width() / 2 - image.width() / 2,
                               this->height() / 2 - image.height() / 2,
                               image );
        }
    }

    void mousePressEvent( QMouseEvent * )
    {
        palette->setColor( QPalette::Background, QColor( 0, 255, 0, 200 ) );
        this->setPalette( *palette );

        emit clicked();
    }

    void mouseReleaseEvent( QMouseEvent * )
    {
        palette->setColor( QPalette::Background, QColor( 0, 0, 255, 200 ) );
        this->setPalette( *palette );

        emit released( this );
    }

signals:

    void clicked();
    void released( Block *block );
};

#endif // BLOCK_H
