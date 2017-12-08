#ifndef GO_H
#define GO_H

#include "myclient.h"

inline int go(int argc, char** argv, User* user)
{
        QCoreApplication app(argc, argv);
        MyClient client(user);
        client.check("localhost", 3425);
        QObject::connect(&client, SIGNAL(valueChanged(int)), &app, SLOT(quit()));
        return app.exec();
}

#endif // GO_H

