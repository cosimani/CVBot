#include <QApplication>
#include "window.h"
#include "controlador.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    int side = 200;

//    Controlador controlador;
//    controlador.show();

    Window controlMenu( 3, 3 );

    Block *b00   = new Block( "",   "",      side );
    Block *b01   = new Block( "flecha_arriba.png",   "Avanzar", side );
    Block *b02   = new Block( "", "",     side );
//    Block *b03   = new Block( "Phone.png",  "Llamadas",    side );
//    Block *b04   = new Block( "Pin.png",    "Lugares",     side );

    Block *b10  = new Block( "flecha_izquierda.png",   "Izquierda",     side );
    Block *b11  = new Block( "flecha_detener.png",   "Detener",  side );
    Block *b12  = new Block( "flecha_derecha.png",   "Derecha", side );
//    Block *b13  = new Block( "Delete.png", "Borrar",  side );
//    Block *b14  = new Block( "Home.png",   "Hogar",   side );

    Block *b20  = new Block( "",   "", side );
    Block *b21  = new Block( "flecha_abajo.png", "Retroceder",     side );
    Block *b22  = new Block( "",  "", side );
//    Block *b23  = new Block( "Pin.png",    "Pines",     side );
//    Block *b24  = new Block( "Plus.png",   "Opciones",  side );

//    Block *b30  = new Block( "Plus.png",   "Mas",     side );
//    Block *b31  = new Block( "User.png",   "Perfil",  side );
//    Block *b32  = new Block( "Cart.png",   "Compras", side );
//    Block *b33  = new Block( "Delete.png", "Borrar",  side );
//    Block *b34  = new Block( "Home.png",   "Hogar",   side );

//    Block *b40  = new Block( "Info.png",   "Intereses", side );
//    Block *b41  = new Block( "Pencil.png", "Lapiz",     side );
//    Block *b42  = new Block( "Phone.png",  "Contactos", side );
//    Block *b43  = new Block( "Pin.png",    "Pines",     side );
//    Block *b44  = new Block( "Plus.png",   "Opciones",  side );

    controlMenu.container->setBlock( 0, 0,  b00 );
    controlMenu.container->setBlock( 0, 1,  b01 );
    controlMenu.container->setBlock( 0, 2,  b02 );
//    controlMenu.container->setBlock( 0, 3,  b03 );
//    controlMenu.container->setBlock( 0, 4,  b04 );

    controlMenu.container->setBlock( 1, 0,  b10 );
    controlMenu.container->setBlock( 1, 1,  b11 );
    controlMenu.container->setBlock( 1, 2,  b12 );
//    controlMenu.container->setBlock( 1, 3,  b13 );
//    controlMenu.container->setBlock( 1, 4,  b14 );

    controlMenu.container->setBlock( 2, 0,  b20 );
    controlMenu.container->setBlock( 2, 1,  b21 );
    controlMenu.container->setBlock( 2, 2,  b22 );
//    controlMenu.container->setBlock( 2, 3,  b23 );
//    controlMenu.container->setBlock( 2, 4,  b24 );

//    controlMenu.container->setBlock( 3, 0,  b30 );
//    controlMenu.container->setBlock( 3, 1,  b31 );
//    controlMenu.container->setBlock( 3, 2,  b32 );
//    controlMenu.container->setBlock( 3, 3,  b33 );
//    controlMenu.container->setBlock( 3, 4,  b34 );

//    controlMenu.container->setBlock( 4, 0,  b40 );
//    controlMenu.container->setBlock( 4, 1,  b41 );
//    controlMenu.container->setBlock( 4, 2,  b42 );
//    controlMenu.container->setBlock( 4, 3,  b43 );
//    controlMenu.container->setBlock( 4, 4,  b44 );

    controlMenu.show();

    return app.exec();
}
