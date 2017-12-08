#include <QtCore/QCoreApplication>
#include <QFile>
#include "myserver.h"

QScopedPointer<QFile> m_logFile;

const QString logFilePath = ".. /debug.log";
bool logToFile = true;


void customMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
    QByteArray localMsg = msg.toLocal8Bit();
    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss.zzz");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
    QString logLevelName = msgLevelHash[type];
    QByteArray logLevelMsg = logLevelName.toLocal8Bit();

    if (logToFile) {
        QString txt = QString("%1 %2: %3 (%4)").arg(formattedTime, logLevelName, msg,  context.file);

        QFile outFile(logFilePath);

        std::cout << logFilePath << std::endl;
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << txt << endl;
        outFile.close();

    } else {
        fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
        fflush(stderr);
    }

    if (type == QtFatalMsg)
        abort();
}

int main(int argc, char *argv[]) {

    qInstallMessageHandler(customMessageOutput);
    QCoreApplication a(argc, argv);


    std::cout << "start" << std::endl;
    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets server");
    parser.addHelpOption();
    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));

    parser.addOption(dbgOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 3425]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("3425"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    //connect
    MyServer *server = new MyServer(port, debug);
    QObject::connect(server, &MyServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
