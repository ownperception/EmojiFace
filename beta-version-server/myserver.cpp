#include "myserver.h"

QT_USE_NAMESPACE

MyServer::MyServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_nNextBlockSize(0),
    m_debug(debug),
    count(0)
{

    m_pTcpSocket = new QTcpServer(this);

    if (m_pTcpSocket->listen(QHostAddress::Any, port)) {
        if (m_debug) { qDebug() << "Echoserver listening on port" << port; }
            connect(m_pTcpSocket, SIGNAL(newConnection()),
                            this, SLOT(slotNewConnection()));
    }
}

void MyServer::slotNewConnection() {
    QTcpSocket* pClientSocket = m_pTcpSocket->nextPendingConnection(); //conect signal with newConnection()

    _clients << pClientSocket;

    //QObject::connect(&Отправитель,SIGNAL(mysignal()),&Адресат,SLOT(myslot()));
    QObject::connect(pClientSocket, SIGNAL(disconnected()), //отсоединение
                     pClientSocket, SLOT(deleteLater()));
    QObject::connect(pClientSocket, SIGNAL(readyRead()),    //готовность
                              this, SLOT(game()));


}

QString MyServer::slotReadClient(User* player) {
    QTcpSocket* pClientSocket = (QTcpSocket*)sender(); //преобразование типов
    QDataStream in(pClientSocket);                     //in.setVersion(QDataStream::Qt_4_2);

    QString str;

    for (;;) {                                         //чтение пакетов
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime time;
        in >> time >> *player ; //time  str
        std::cout << *player <<std::endl;
        _users << player;
        QString strMessage = time.toString() + " " + "Client has sended - " + str;
        qDebug() << QString(strMessage);
        m_nNextBlockSize = 0;
    }
    return str;
}

void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str) {

    std::cout << "MyServer::sendToClient()" << std::endl;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
void MyServer::game() {
    std::cout << "MyServer::game()" << std::endl;

    User* player = new User;
     ++count;

    if (count == 2)
    {
        sendToClient(_clients.at(0), "GO");
        sendToClient(_clients.at(1), "GO");
    } else if (count < 2) sendToClient(_clients.at(0), "Wait");



}
