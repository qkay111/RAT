#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class userInfo
{
private:
    QString name;
    QString password;
    bool isAv;
    int permissions;

public:
    userInfo();
    QString getName();
    QString getPassword();
    bool getAv();
    int getPermissions();
    void setName(QString);
    void setPassword(QString);
    void setAv(bool);
    void setPermissions(int);
};

#endif // USERINFO_H
