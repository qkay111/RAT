#include "functionalityform.h"
#include "ui_functionalityform.h"
#include <QInputDialog>
#include <QLineEdit>    // Для выравнивания комбо-бокса

FunctionalityForm::FunctionalityForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionalityForm)
{
    ui->setupUi(this);

    mainWindow = nullptr;
    fileSystemForm = new FileSystemForm();  // Создаём окно для работы с файловой системой
    screenSharingForm = new ScreenSharingForm(); // Создаём окно для трансляции экрана

    setWindowTitle("Действия");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    ui->enteredAsLabel->setAlignment(Qt::AlignCenter);
    ui->enteredAsLabel->setStyleSheet("border: 4px solid #2a4158;"
                                      "background-color: #958a56;"
                                      "color: #2a4158;");
    ui->fileSystemButton->setStyleSheet("font-size: 27px;");
    ui->screenShareButton->setStyleSheet("font-size: 27px;");
    ui->systemActionsLabel->setAlignment(Qt::AlignCenter);
    ui->systemActionsLabel->setStyleSheet("border: 4px solid #2a4158;"
                                          "background-color: #958a56;"
                                          "color: #2a4158;"
                                          "font-size: 30px;");
    ui->systemComboBox->setEditable(true); // выравнивание комбо-бокса
    ui->systemComboBox->lineEdit()->setReadOnly(true); // выравнивание комбо-бокса
    ui->systemComboBox->lineEdit()->setAlignment(Qt::AlignCenter);  // выравнивание комбо-бокса
    for(int i = 0; i < ui->systemComboBox->count(); i++)    // выравнивание комбо-бокса
        ui->systemComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole); // выравнивание комбо-бокса
    ui->systemComboBox->setStyleSheet("border: 4px solid #2a4158;"
                                      "color: #8c9ea3;");
    ui->runButton->setStyleSheet("font-size: 27px;");
    ui->systemInfoLabel->setAlignment(Qt::AlignCenter);
    ui->systemInfoLabel->setStyleSheet("border: 4px solid #2a4158;"
                                       "background-color: #958a56;"
                                       "color: #2a4158;"
                                       "font-size: 30px;");
    ui->systemInfoEdit->setReadOnly(true);

    connect(this, SIGNAL(send_functionalityForm(FunctionalityForm*, QTcpSocket*)), fileSystemForm, SLOT(get_functionalityForm(FunctionalityForm*, QTcpSocket*)));
    connect(this, SIGNAL(send_functionalityForm_for_sharing(FunctionalityForm*,QTcpSocket*)), screenSharingForm, SLOT(get_functionalityForm(FunctionalityForm*, QTcpSocket*)));
    connect(this, SIGNAL(send_screenshot_for_sharing(QPixmap*)), screenSharingForm, SLOT(get_screenshot_for_sharing(QPixmap*)));
}

FunctionalityForm::~FunctionalityForm()
{
    delete ui;
    delete fileSystemForm;
}

void FunctionalityForm::get_mainWindow(QMainWindow* mw)
{
    mainWindow = mw;
}

void FunctionalityForm::get_user_info(QTcpSocket* sk, const char* permissions, QPixmap* av, QString userName, QString sysInfo)
{
    socket = sk;

    for (int i = 0; i < 3; i++)
        userPermissions[i] = permissions[i];

    uName = userName;
    if (userName.length() > 22) // Если слишком большое имя пользователя
    {
        QString tmpName;
        for (int i = 0; i < 20; i++)
            tmpName += userName[i];
        tmpName += "...";
        ui->enteredAsLabel->setText(ui->enteredAsLabel->text() + tmpName);
    }
    else
        ui->enteredAsLabel->setText(ui->enteredAsLabel->text() + userName);

    if (av == nullptr)  // Если нет аватарки
    {
        av = new QPixmap(":/emptyAvatar.png");
        int w = ui->userAvLabel->width();
        int h = ui->userAvLabel->height();
        ui->userAvLabel->clear();
        ui->userAvLabel->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAvLabel->setStyleSheet("background: none;");
    }

    if (userPermissions[0] == 0)
    {
        ui->fileSystemButton->setStyleSheet("font-size: 27px;"
                                            "color: red;");
        ui->fileSystemButton->setEnabled(false);
    }
    else
    {
        ui->fileSystemButton->setStyleSheet("font-size: 27px;"
                                            "color: #8c9ea3;");
        ui->fileSystemButton->setEnabled(true);
    }
    if (userPermissions[1] == 0)
    {
        ui->screenShareButton->setStyleSheet("font-size: 27px;"
                                             "color: red;");
        ui->screenShareButton->setEnabled(false);
    }
    else
    {
        ui->screenShareButton->setStyleSheet("font-size: 27px;"
                                             "color: #8c9ea3;");
        ui->screenShareButton->setEnabled(true);
    }
    if (userPermissions[2] == 0)
    {
        ui->systemComboBox->setStyleSheet("border: 4px solid #2a4158;"
                                          "color: #8c9ea3;"
                                          "color: red;");
        ui->runButton->setStyleSheet("font-size: 27px;"
                                     "color: red;");
        ui->systemComboBox->setEnabled(false);
        ui->runButton->setEnabled(false);
    }
    else
    {
        ui->systemComboBox->setStyleSheet("border: 4px solid #2a4158;"
                                          "color: #8c9ea3;"
                                          "color: #8c9ea3;");
        ui->runButton->setStyleSheet("font-size: 27px;"
                                     "color: #8c9ea3;");
        ui->systemComboBox->setEnabled(true);
        ui->runButton->setEnabled(true);
    }

    if (sysInfo.isEmpty())
        ui->systemInfoEdit->setText("Информация о системе не найдена");
    else
        ui->systemInfoEdit->setText(sysInfo);
}

void FunctionalityForm::on_userInfoButton_clicked()
{
    QString availableActions;
    if (userPermissions[0] == 1)
        availableActions += "- Работа с файловой системой\n";
    if (userPermissions[1] == 1)
        availableActions += "- Трансляция экрана\n";
    if (userPermissions[2] == 1)
        availableActions += "- Системные операции";
    QMessageBox::about(this, "About user", "Имя пользователя:\n- " + uName + "\nДоступные действия:\n" + availableActions);
}

void FunctionalityForm::on_exitButton_clicked()
{
    int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выйти", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;

    ui->enteredAsLabel->setText("Вы вошли как: ");

    mainWindow->show();
    this->hide();
}

void FunctionalityForm::on_fileSystemButton_clicked()
{
    emit send_functionalityForm(this, socket);
    fileSystemForm->show();
    this->hide();
}

void FunctionalityForm::on_screenShareButton_clicked()
{
    emit send_functionalityForm_for_sharing(this, socket);
    screenSharingForm->show();
    this->hide();
}

void FunctionalityForm::on_runButton_clicked()
{
    int index = ui->systemComboBox->currentIndex();
    switch (index)
    {
    case 0: // Вывести сообщение
    {
        QString message = QInputDialog::getText(this, "Message", "Enter a message:");
        if (message.isEmpty())
            return;
        socket->write(("message:" + message + '$').toStdString().c_str());
        socket->waitForBytesWritten(500);
        this->setEnabled(false);
        break;
    }
    case 1: // Выключить компьютер
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выключить компьютер ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        if (socket->isOpen())
        {
            socket->write(QString("command:$shutdown /s$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 2: // Перезагрузить компьютер
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите перезагрузить компьютер ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        if (socket->isOpen())
        {
            socket->write(QString("command:$shutdown /r$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 3: // Получить xml файл с системной информацией
    {
        if (socket->isOpen())
        {
            socket->write(QString("command:xmlSysFile$msinfo32 /nfo C:/NjTmpSysInfo.txt$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 4: // Получить версию windows
    {
        if (socket->isOpen())
        {
            socket->write(QString("command:file$ver > D:/NjTmpSysInfo.txt$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 5: // Получить системное время
    {
        if (socket->isOpen())
        {
            socket->write(QString("command:file$time /T > D:/NjTmpSysInfo.txt$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 6: // Получить дату
    {
        if (socket->isOpen())
        {
            socket->write(QString("command:file$date /T > D:/NjTmpSysInfo.txt$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 7: // Получить часовой пояс
    {
        if (socket->isOpen())
        {
            socket->write(QString("command:file$tzutil /g > D:/NjTmpSysInfo.txt$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 8: // Перейти в режим гибернации
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите перевести компьютер в режим гибернации ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        if (socket->isOpen())
        {
            socket->write(QString("command:$rundll32.exe PowrProf.dll,SetSuspendState$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 9: // Перейти в режим сна
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите перевести компьютер в режим сна ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        if (socket->isOpen())
        {
            socket->write(QString("command:$rundll32.exe powrprof.dll,SetSuspendState 0,1,0$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 10:    // Заблокировать компьютер
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите заблокировать компьютер ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        if (socket->isOpen())
        {
            socket->write(QString("command:$Rundll32.exe User32.dll,LockWorkStation$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 11:    // Установить время
    {
        break;
    }
    case 12:    // Установить дату
    {
        break;
    }
    case 13:    // Изменить положение курсора
    {
        break;
    }
    case 14:    // Сделать скриншот
    {
        if (socket->isOpen())
        {
            socket->write(QString("screen:$").toStdString().c_str());
            socket->waitForBytesWritten(500);
        }
        else
        {
            mainWindow->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    }
}

void FunctionalityForm::get_screenshot(QPixmap *screenshot)
{
    emit send_screenshot_for_sharing(screenshot);
}
