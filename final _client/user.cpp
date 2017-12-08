#include "user.h"
#include "score.h"

User::User(char* name)
{
    memcpy(this->name,name,sizeof(name));
}

const char* User::getname()
{
    return name;
}
