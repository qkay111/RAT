#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

#define SERVER_PORT 12345
#define CLIENT_PORT 17325

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    functionalityForm = new FunctionalityForm();    // Создаём окно для выбора функциональностей

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisc()));

    for (int i = 0; i < 3; i++)
        permissions[i] = 0;

    setWindowTitle("njRAT-Client application");

    ui->connect->setShortcut(tr("Ctrl+C"));
    ui->quit->setShortcut(tr("Ctrl+E"));
    ui->author->setShortcut(tr("Ctrl+A"));
    ui->about->setShortcut(tr("Ctrl+D"));

    ui->logoLabel->setAlignment(Qt::AlignCenter);
    ui->logoLabel->setStyleSheet("font-size: 100px;");
    ui->ipLabel->setAlignment(Qt::AlignCenter);
    ui->ipLabel->setStyleSheet("border: 3px solid #597387;"
                               "font-size: 35px;");
    ui->ipEdit->setAlignment(Qt::AlignCenter);
    ui->ipEdit->setStyleSheet("border: 3px solid #597387;"
                              "font-size: 25px;"
                              "color: #597387;");
    ui->loginLabel->setAlignment(Qt::AlignCenter);
    ui->loginLabel->setStyleSheet("border: 3px solid #2a4158;"
                                  "font-size: 27px;");
    ui->passwordLabel->setAlignment(Qt::AlignCenter);
    ui->passwordLabel->setStyleSheet("border: 3px solid #2a4158;"
                                     "font-size: 27px;");
    ui->loginEdit->setAlignment(Qt::AlignCenter);
    ui->loginEdit->setStyleSheet("border: 3px solid #597387;"
                                 "font-size: 25px;"
                                 "color: #597387;");
    ui->passwordEdit->setAlignment(Qt::AlignCenter);
    ui->passwordEdit->setStyleSheet("border: 3px solid #597387;"
                                    "font-size: 25px;"
                                    "color: #597387;");
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->loadSystemInfoLabel->setAlignment(Qt::AlignCenter);
    ui->loadSystemInfoLabel->setStyleSheet("border: 3px solid #2a4158;"
                                           "font-size: 27px;");
    ui->loadCheckBox->setStyleSheet("color: #597387;"
                                    "font-size: 27px;");

    QRegExp ipValidator("[0-9]{1,3}[.]{1}[0-9]{1,3}[.]{1}[0-9]{1,3}[.]{1}[0-9]{1,3}");   // Установка валидатора
    ui->ipEdit->setValidator(new QRegExpValidator(ipValidator, this));   // Установка валидатора
    QRegExp loginValidator("[0-9_A-Za-z]{1,30}");   // Установка валидатора
    ui->loginEdit->setValidator(new QRegExpValidator(loginValidator, this));    // Установка валидатора
    QRegExp passwordValidator("[0-9_A-Za-z]{1,30}");    // Установка валидатора
    ui->passwordEdit->setValidator(new QRegExpValidator(passwordValidator, this));  // Установка валидатора

    connect(this, SIGNAL(send_mainWindow(QMainWindow*)), functionalityForm, SLOT(get_mainWindow(QMainWindow*)));
    connect(this, SIGNAL(send_user_info(QTcpSocket*, const char*, QPixmap*, QString, QString)), functionalityForm, SLOT(get_user_info(QTcpSocket*, const char*, QPixmap*, QString, QString)));
    connect(this, SIGNAL(send_screenshot_for_sharing(QPixmap*)), functionalityForm, SLOT(get_screenshot(QPixmap*)));

    beginUi();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete functionalityForm;
    socket->deleteLater();
}

void MainWindow::beginUi()
{
    ui->ipEdit->setStyleSheet("border: 3px solid #597387;"
                              "font-size: 25px;"
                              "color: #597387;");
    ui->loginEdit->setStyleSheet("border: 3px solid #597387;"
                                 "font-size: 25px;"
                                 "color: #597387;");
    ui->passwordEdit->setStyleSheet("border: 3px solid #597387;"
                                    "font-size: 25px;"
                                    "color: #597387;");
    ui->logoLabel->show();
    ui->connectButton->show();
    ui->ipLabel->hide();
    ui->ipEdit->hide();
    ui->ipEdit->clear();
    ui->okButton->hide();
    ui->canselButton->hide();
    ui->menuBar->show();
    ui->loginLabel->hide();
    ui->passwordLabel->hide();
    ui->loginEdit->hide();
    ui->loginEdit->clear();
    ui->passwordEdit->hide();
    ui->passwordEdit->clear();
    ui->acceptButton->hide();
    ui->disconnectButton->hide();
    ui->loadSystemInfoLabel->hide();
    ui->loadCheckBox->hide();
    ui->loadCheckBox->setCheckState(Qt::CheckState::Unchecked);
}

void MainWindow::ipEnterUi()
{
    ui->loginEdit->setStyleSheet("border: 3px solid #597387;"
                                 "font-size: 25px;"
                                 "color: #597387;");
    ui->passwordEdit->setStyleSheet("border: 3px solid #597387;"
                                    "font-size: 25px;"
                                    "color: #597387;");
    ui->logoLabel->hide();
    ui->connectButton->hide();
    ui->ipLabel->show();
    ui->ipEdit->show();
    ui->okButton->show();
    ui->canselButton->show();
    ui->menuBar->hide();
    ui->loginLabel->hide();
    ui->passwordLabel->hide();
    ui->loginEdit->hide();
    ui->loginEdit->clear();
    ui->passwordEdit->hide();
    ui->passwordEdit->clear();
    ui->acceptButton->hide();
    ui->disconnectButton->hide();
    ui->loadSystemInfoLabel->hide();
    ui->loadCheckBox->hide();
    ui->loadCheckBox->setCheckState(Qt::CheckState::Unchecked);
}

void MainWindow::vereficationUi()
{
    ui->logoLabel->hide();
    ui->connectButton->hide();
    ui->ipLabel->hide();
    ui->ipEdit->hide();
    ui->okButton->hide();
    ui->canselButton->hide();
    ui->menuBar->hide();
    ui->loginLabel->show();
    ui->passwordLabel->show();
    ui->loginEdit->show();
    ui->passwordEdit->show();
    ui->acceptButton->show();
    ui->disconnectButton->show();
    ui->loadSystemInfoLabel->show();
    ui->loadCheckBox->show();
    ui->loadCheckBox->setCheckState(Qt::CheckState::Unchecked);
}

bool MainWindow::ipValidation(QString ipPath)
{
    int value;
    QStringList ipList = ipPath.split(".");

    if (ipList.length() != 4)
        return false;

    for (QString ip : ipList)
    {
        value = ip.toInt();
        if (value == 0 && ip.length() == 1)
            continue;
        if (value > 255)
            return false;
        if (value < 100 && ip[0] == '0')
            return false;
        if (value < 10 && ip[1] == '0')
            return false;
    }

    return true;
}

void MainWindow::on_author_triggered()
{
    QMessageBox::about(this, "Author", "Программу разработал студент группы\n"
                                       "850502: Домбровский Тимур");
}

void MainWindow::on_connectButton_clicked()
{
    ipEnterUi();
}

void MainWindow::on_canselButton_clicked()
{
    beginUi();
}

void MainWindow::on_connect_triggered()
{
   on_connectButton_clicked();
}

void MainWindow::on_okButton_clicked()
{
    QString ipPath; // ip сервера
    ipPath = ui->ipEdit->text();
    if (!ipValidation(ipPath))
    {
        ui->ipEdit->setStyleSheet("border: 3px solid red;"
                                  "font-size: 25px;"
                                  "color: red;");
        QMessageBox::critical(this, "Error!", "   Wrong IP address!   ");
    }
    else
    {
        ui->ipEdit->setStyleSheet("border: 3px solid #597387;"
                                  "font-size: 25px;"
                                  "color: #597387;");

        socket->connectToHost(ipPath, SERVER_PORT);
        socket->waitForConnected(500);
        if (socket->state() == QTcpSocket::SocketState::ConnectedState)
        {
            vereficationUi();
            QMessageBox::information(this, "Connection", "Successfull connection to the server : " + ipPath);
        }
        else
            QMessageBox::critical(this, "Error!", "Can not connect to the server :\n" + ipPath);
    }
}

void MainWindow::on_quit_triggered()
{
    int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выйти", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    this->close();
}

void MainWindow::socketReady()
{
    if (socket->waitForConnected(500))
    {
        bufferData = socket->readAll();

        while (socket->waitForReadyRead(500))
            bufferData += socket->readAll();

        if (bufferData[0] == 's' &&
            bufferData[2] == 'u' &&
            bufferData[4] == 'c' &&
            bufferData[6] == 'c' &&
            bufferData[8] == 'e' &&
            bufferData[10] == 's' &&
            bufferData[12] == 's')    // Если было получено сообщение об успехе
        {
            wchar_t* ptr = new wchar_t[bufferData.size() / 2];
            for (int i = 0, j = 0; i < bufferData.size() / 2; i++, j++)
            {
                ptr[i] = bufferData[j++];
                ptr[i] += bufferData[j] * 256;
            }
            QString successString = QString::fromWCharArray(ptr, bufferData.size() / 2);
            delete[] ptr;

            if (successString[8] == '1') permissions[0] = 1;   // Разрешение на файловую систему
            if (successString[9] == '1') permissions[1] = 1;   // Разрешение на трансляцию экрана
            if (successString[10] == '1') permissions[2] = 1;   // Разрешение на системные операции

            QPixmap* av = nullptr;
            if (successString[11] != 0) // Если есть аватарка
            {

            }

            QString userName;   // Имя пользователя, под которым мы зашли
            int i;
            for (i = 12; successString[i] != '$'; i++)
                userName += successString[i];

            QString sysInfo;    // Системная информация
            i++;
            for (; i < successString.size(); i++)
                sysInfo += successString[i];

            emit send_mainWindow(this);
            emit send_user_info(socket, permissions, av, userName, sysInfo);
            this->setEnabled(true);
            functionalityForm->setEnabled(true);
            functionalityForm->show();
            this->hide();

            if (ui->loadCheckBox->checkState() != Qt::CheckState::Unchecked && sysInfo.isEmpty())
                QMessageBox::critical(this, "Error!", "Ошибка сбора системной информации!");
            return;
        }
        if (bufferData[0] == 'x' &&
            bufferData[2] == 'm' &&
            bufferData[4] == 'l' &&
            bufferData[6] == 'S' &&
            bufferData[8] == 'y' &&
            bufferData[10] == 's' &&
            bufferData[12] == 'F' &&
            bufferData[14] == 'i' &&
            bufferData[16] == 'l' &&
            bufferData[18] == 'e')
        {
            wchar_t* ptr = new wchar_t[bufferData.size() / 2];
            for (int i = 0, j = 0; i < bufferData.size() / 2; i++, j++)
            {
                ptr[i] = bufferData[j++];
                ptr[i] += bufferData[j] * 256;
            }
            QString requestString = QString::fromWCharArray(ptr, bufferData.size() / 2);
            delete[] ptr;

            QString xmlFileString;
            for (int i = 11; i < requestString.size(); i++)
                xmlFileString += requestString[i];

            if (!xmlFileString.isEmpty())   // Если файл удалось передать
            {
                QString sPath = nullptr;
                sPath = QFileDialog::getExistingDirectory(this, tr("Save file"));   // путь для создания папки для хранения
                if (sPath.isEmpty())
                {
                    functionalityForm->setEnabled(true);
                    QMessageBox::critical(this, "Error", "Ошибка сбора системной информации!");
                    return;
                }
                sPath += "/systemInfo.NFO";
                QFile file(sPath);
                if (file.open(QFile::WriteOnly | QFile::Text))
                {
                    QTextStream stream(&file);
                    stream << xmlFileString;
                    file.close();

                    QProcess* process = new QProcess(this);
                    QString sysCom = QString("cmd.exe %1 \"%2\"").arg("/C").arg("start " + sPath);
                    process->start(sysCom);
                    if (process->waitForStarted(-1))
                        while (process->waitForReadyRead(-1));

                    functionalityForm->setEnabled(true);
                    QMessageBox::about(this, "Success!", "Операция была успешно выполнена!");
                    return;
                }
                else
                {
                    functionalityForm->setEnabled(true);
                    QMessageBox::critical(this, "Error", "Ошибка создания файла!");
                    return;
                }
            }
            else
            {
                functionalityForm->setEnabled(true);
                QMessageBox::critical(this, "Error", "Ошибка сбора системной информации!");
            }
            return;
        }
        if (bufferData.contains("screenSharing"))
        {
            QByteArray screenshot;
            for (int i = 14; i < bufferData.size(); i++)
                screenshot += bufferData[i];

            QPixmap* pix = new QPixmap();
            pix->loadFromData(screenshot, "PNG");

            emit send_screenshot_for_sharing(pix);  // Отправка скриншота
            return;
        }
        if (bufferData.contains("screen"))
        {
            QString sPath = nullptr;
            sPath = QFileDialog::getExistingDirectory(this, tr("Save file"));   // путь для создания папки для хранения
            if (sPath.isEmpty())
            {
                functionalityForm->setEnabled(true);
                QMessageBox::critical(this, "Error", "Неправильный путь!");
                return;
            }
            sPath += "/screenshot.png";

            QByteArray screenshot;
            for (int i = 7; i < bufferData.size(); i++)
                screenshot += bufferData[i];

            QFile file(sPath);
            if (file.open(QFile::WriteOnly))
            {
                file.write(screenshot);
                file.close();

                QProcess* process = new QProcess(this);
                QString sysCom = QString("cmd.exe %1 \"%2\"").arg("/C").arg("start " + sPath);
                process->start(sysCom);
                if (process->waitForStarted(-1))
                    while (process->waitForReadyRead(-1));

                functionalityForm->setEnabled(true);
                QMessageBox::about(this, "Success!", "Операция была успешно выполнена!");
                return;
            }
            else
            {
                functionalityForm->setEnabled(true);
                QMessageBox::critical(this, "Error", "Ошибка создания файла!");
                return;
            }
            return;
        }
        if (bufferData.contains("operation"))
        {
            QString operation;
            for (int i = 10; i < bufferData.size(); i++)
                operation += bufferData[i];

            if (operation.isEmpty())
            {
                functionalityForm->setEnabled(true);
                QMessageBox::critical(this, "Error!", "Ошибка!");
                return;
            }

            functionalityForm->setEnabled(true);
            QMessageBox::about(this, "Operation", operation);
            return;
        }
        if (bufferData.contains("Ok"))  // Если пришло уведомление о выполненной операции
        {
            functionalityForm->setEnabled(false);
            QMessageBox::about(this, "Success!", "Операция была успешно выполнена!");
            functionalityForm->setEnabled(true);
        }
    }
}

void MainWindow::socketDisc()
{
    beginUi();
    QMessageBox::information(this, "Alert", "Disconnection from server");
}

void MainWindow::on_acceptButton_clicked()
{
    if (socket->isOpen())
    {
        char state;
        if (ui->loadCheckBox->checkState() == Qt::CheckState::Unchecked)
            state = 0;
        else
            state = 1;
        socket->write(QString("verification:" + ui->loginEdit->text() + "$" + ui->passwordEdit->text() + "$" + state).toStdString().c_str());
        socket->waitForBytesWritten(500);
        this->setEnabled(false);
        functionalityForm->setEnabled(false);
    }
    else
    {
        beginUi();
        QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
    }
}

void MainWindow::on_disconnectButton_clicked()
{
    beginUi();
    socket->disconnectFromHost();
}
