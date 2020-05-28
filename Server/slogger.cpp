#include "slogger.h"

sLogger::sLogger(QString str) :
    path(str)
{
    file = new QFile(path + LOG_FILE_NAME);
    if (file->open(QIODevice::ReadWrite | QFile::Text))
    {
        flag = true;
    }
    else
        flag = false;
}

sLogger::~sLogger()
{
    if (flag)
    {
        file->seek(file->size());
        file->write("=================================================="
                    "==================================================\n");
        file->close();
        delete file;
    }
}

QString sLogger::getName()
{
    return name;
}

QString sLogger::getPath()
{
    return path;
}

void sLogger::setName(QString str)
{
    name = str;
}

void sLogger::operator <<(QString str)
{
    if (this == nullptr)
        return;

    if (flag)
        if (name.isEmpty())
        {
            file->seek(file->size());
            file->write((str + '\n').toStdString().c_str());
        }
        else
        {
            file->seek(file->size());
            file->write((name + ':' + str + '\n').toStdString().c_str());
        }
}
