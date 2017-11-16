#include <QApplication>
#include <QFile>

#include "interface/interface.h"
#include "common.h"
#include "processor/camera.h"

#include "principal.h"
#include "ventana.h"
#include <QDesktopWidget>

#include "config.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );


//    QString xml( DATA_PATH );
//    xml.append( XML_PATH );
//    xml.append( "ottaa.xml" );
//    xml.append( "ubp.xml" );
//    xml.append( "casa.xml" );
//    QFile file( xml );

//    Interface *_interface = new Interface();
//    _interface->showMaximized();
//    _interface->initInterface( &file );


    // Iniciamos config
    Config::getInstance();

    QRect rec = QApplication::desktop()->screenGeometry();
    int anchoScreen = rec.width();
    int altoScreen = rec.height();

    int wVentana = altoScreen*4/3, hVentana = altoScreen;
//    int wVentana = 200, hVentana = 200;


    Ventana ventana;
    ventana.resize( wVentana, hVentana );
    ventana.move( anchoScreen / 2 - wVentana / 2, altoScreen / 2 - hVentana / 2 );
    ventana.show();

    return app.exec();
}
