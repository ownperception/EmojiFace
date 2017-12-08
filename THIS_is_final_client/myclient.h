#ifndef MYCLIENT_H
#define MYCLIENT_H

//#include <QtWidgets>

#include <QTcpSocket>

#include <QTime>

#include <iostream>

#include "user.h"

class QTextEdit;
class QLineEdit;

class MyClient : public QObject {
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    User* user_;
    quint16     m_nNextBlockSize;
    int status;

public:
    MyClient(User* user = NULL, QObject *parent = Q_NULLPTR ) ;
    int check( const QString& strHost, int nPort);
    int get_status();
    void slotSendToServer(                            );
public slots:
    void setValue(int value);
signals:
    void valueChanged(int newValue);
private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    //void slotSendToServer(                            );
    void slotConnected   (                            );

};

#endif // MYCLIENT_H

