#ifndef MYCLIENT_H
#define MYCLIENT_H


#include <QtWidgets>

#include <QTcpSocket>

#include <iostream>

#include "user.h"

class QTextEdit;
class QLineEdit;

class MyClient : public QWidget {
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;

public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0) ;

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
};

#endif // MYCLIENT_H


