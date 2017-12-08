#include "myclient.h"

MyClient::MyClient(User * user,
                   QObject *parent
                  ) : QObject(parent),user_(user), status(0)
                    , m_nNextBlockSize(0)
{

    m_pTcpSocket = new QTcpSocket(this);
}

int MyClient::check( const QString& strHost, int nPort)
{
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );
   return 1;
}

int MyClient::get_status()
{
    return status;
}


void MyClient::setValue(int value)
{
   if (status != value) {
     status = value;
     emit valueChanged(value);
   }
}


void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    //in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;



        if (str == "GO")
        {
            std::cout << str.toStdString() <<std::endl;
            m_nNextBlockSize = 0;
            this->setValue(1);
            return;

        }
        std::cout << str.toStdString() <<std::endl;
        m_nNextBlockSize = 0;
    }
}

void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    std::cout << strError.toStdString() << std::endl;
    exit(1);
}

void MyClient::slotSendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << *user_;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}



void MyClient::slotConnected()
{
    std::cout << "Received the connected() signal" << std::endl;
    slotSendToServer();
}


