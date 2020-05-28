#ifndef SLOGGER_H
#define SLOGGER_H

#include <QFileDialog>
#include <QString>

#define LOG_FILE_NAME "/logfile.txt"

class sLogger
{
private:
    bool flag;
    QFile* file;
    QString name;
    QString path;

public:
    sLogger(QString);
    ~sLogger();
    QString getName();
    QString getPath();
    void setName(QString);
    void operator <<(QString);
};

#endif // SLOGGER_H
