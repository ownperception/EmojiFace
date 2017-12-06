#include <QApplication>

#include "myclient.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MyClient     client("localhost", 3425);

    client.show();

    return app.exec();
}
