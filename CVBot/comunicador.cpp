#include "comunicador.h"

Comunicador::Comunicador(QObject *parent) : QObject(parent),
                                            manager( new QNetworkAccessManager )
{

}
