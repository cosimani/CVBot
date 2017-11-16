#ifndef CLIENTETCP_H
#define CLIENTETCP_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>


class ClienteTcp : public QObject
{
    Q_OBJECT
public:
    explicit ClienteTcp(QObject *parent = 0);

    void mensajear( QString ip, int puerto, QString mensaje );

private:
    QTcpSocket * tcpClient;
    QTcpSocket *tcpServerConnection;
    int bytesToWrite;
    int bytesWritten;
    int bytesReceived;

    QString mensajeActual;

signals:

private slots:
    void updateClientProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // CLIENTETCP_H
