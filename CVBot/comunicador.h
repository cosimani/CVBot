#ifndef COMUNICADOR_H
#define COMUNICADOR_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

class Comunicador : public QObject
{
    Q_OBJECT
public:
    explicit Comunicador(QObject *parent = nullptr);

private:
    QNetworkAccessManager * manager;


signals:

public slots:
};

#endif // COMUNICADOR_H
