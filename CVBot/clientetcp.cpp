#include "clientetcp.h"
#include <QDebug>


static const int TotalBytes = 50 * 1024 * 1024;
static const int PayloadSize = 64 * 1024; // 64 KB

ClienteTcp::ClienteTcp(QObject *parent) : QObject(parent),
                                          tcpClient( new QTcpSocket( this ) )
{


    connect(tcpClient, SIGNAL(bytesWritten(qint64)),
            this, SLOT(updateClientProgress(qint64)));

    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}


void ClienteTcp::mensajear( QString ip, int puerto, QString mensaje )
{
    this->mensajeActual = mensaje;
    qDebug() << "mensaje enviado:" << mensaje;
    this->disconnect( tcpClient, NULL, NULL, NULL );

    connect( tcpClient, &QAbstractSocket::connected, [&] ()  {

        qDebug() << "Se escribe:" << this->mensajeActual << " en ::" << tcpClient->write( this->mensajeActual.toStdString().c_str() );

        tcpClient->close();
    });

    if ( ! tcpClient->isOpen() )  {
        tcpClient->connectToHost( ip, puerto );
        qDebug() << "connectToHost" << ip << puerto;
    }
}

void ClienteTcp::updateClientProgress(qint64 numBytes)
{
    qDebug() << "startTransfer" << numBytes;
}

void ClienteTcp::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error";

    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;





}
