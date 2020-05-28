#include "userinfo.h"

userInfo::userInfo() :
    isAv(false) ,
    permissions(0)
{

}

QString userInfo::getName()
{
    return name;
}

QString userInfo::getPassword()
{
    return password;
}

bool userInfo::getAv()
{
    return isAv;
}

int userInfo::getPermissions()
{
    return permissions;
}

void userInfo::setName(QString str)
{
    name = str;
}

void userInfo::setPassword(QString str)
{
    password = str;
}

void userInfo::setAv(bool av)
{
    isAv = av;
}

void userInfo::setPermissions(int var)
{
    permissions = var;
}
