#ifndef USER_H
#define USER_H
#include "score.h"

class User
{
public:
    User(char* name = nullptr);
    char* getname();
private:
    char name[100];
};

#endif // USER_H
