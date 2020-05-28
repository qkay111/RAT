#include "functionalityform.h"
#include "ui_functionalityform.h"
#include "writeform.h"
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
    ui->fileSystemButton->setStyleSheet("QPushButton {"
                                        "border-radius: 5px;"
                                        "background-color: #2a4158;"
                                        "color: #8c9ea3;"
                                        "font-size: 27px;"
                                        "}"
                                        "QPushButton:hover {"
                                        "background-color: #2a5370;"
                                        "font-size: 24px;"
                                        "}"
                                        "QPushButton:pressed {"
                                        "background-color: #958a56;"
                                        "color: black;"
                                        "}");
    ui->screenShareButton->setStyleSheet("QPushButton {"
                                         "border-radius: 5px;"
                                         "background-color: #2a4158;"
                                         "color: #8c9ea3;"
                                         "font-size: 27px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "background-color: #2a5370;"
                                         "font-size: 24px;"
                                         "}"
                                         "QPushButton:pressed {"
                                         "background-color: #958a56;"
                                         "color: black;"
                                         "}");
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
    ui->runButton->setStyleSheet("QPushButton {"
                                 "border-radius: 5px;"
                                 "background-color: #2a4158;"
                                 "color: #8c9ea3;"
                                 "font-size: 27px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #2a5370;"
                                 "font-size: 24px;"
                                 "}"
                                 "QPushButton:pressed {"
                                 "background-color: #958a56;"
                                 "color: black;"
                                 "}");
    ui->systemInfoLabel->setAlignment(Qt::AlignCenter);
    ui->systemInfoLabel->setStyleSheet("border: 4px solid #2a4158;"
                                       "background-color: #958a56;"
                                       "color: #2a4158;"
                                       "font-size: 30px;");
    ui->systemInfoEdit->setReadOnly(true);

    connect(this, SIGNAL(send_functionalityForm(FunctionalityForm*, QTcpSocket*)), fileSystemForm, SLOT(get_functionalityForm(FunctionalityForm*, QTcpSocket*)));
    connect(this, SIGNAL(send_functionalityForm_for_sharing(FunctionalityForm*,QTcpSocket*)), screenSharingForm, SLOT(get_functionalityForm(FunctionalityForm*, QTcpSocket*)));
    connect(this, SIGNAL(send_screenshot_for_sharing(QPixmap*)), screenSharingForm, SLOT(get_screenshot_for_sharing(QPixmap*)));
    connect(this, SIGNAL(send_file_sys(QString)), fileSystemForm, SLOT(get_file_sys(QString)));
}

FunctionalityForm::~FunctionalityForm()
{
    delete ui;
    delete fileSystemForm;
    delete screenSharingForm;
}

void FunctionalityForm::get_mainWindow(QMainWindow* mw)
{
    mainWindow = mw;
}

void FunctionalityForm::get_user_info(QTcpSocket* sk, const char* permissions, QString userName, QString sysInfo)
{
    ui->enteredAsLabel->setText("Вы вошли как: ");
    ui->systemComboBox->setCurrentIndex(0);

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

    QPixmap* av = new QPixmap(":/emptyAvatar.png");
    int w = ui->userAvLabel->width();
    int h = ui->userAvLabel->height();
    ui->userAvLabel->clear();
    ui->userAvLabel->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
    ui->userAvLabel->setStyleSheet("background: none;");
    delete av;

    if (userPermissions[0] == 0)
    {
        ui->fileSystemButton->setStyleSheet("font-size: 27px;"
                                            "color: red;");
        ui->fileSystemButton->setEnabled(false);
    }
    else
    {
        ui->fileSystemButton->setStyleSheet("QPushButton {"
                                            "border-radius: 5px;"
                                            "background-color: #2a4158;"
                                            "color: #8c9ea3;"
                                            "font-size: 27px;"
                                            "}"
                                            "QPushButton:hover {"
                                            "background-color: #2a5370;"
                                            "font-size: 24px;"
                                            "}"
                                            "QPushButton:pressed {"
                                            "background-color: #958a56;"
                                            "color: black;"
                                            "}");
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
        ui->screenShareButton->setStyleSheet("QPushButton {"
                                             "border-radius: 5px;"
                                             "background-color: #2a4158;"
                                             "color: #8c9ea3;"
                                             "font-size: 27px;"
                                             "}"
                                             "QPushButton:hover {"
                                             "background-color: #2a5370;"
                                             "font-size: 24px;"
                                             "}"
                                             "QPushButton:pressed {"
                                             "background-color: #958a56;"
                                             "color: black;"
                                             "}");
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
        ui->runButton->setStyleSheet("QPushButton {"
                                     "border-radius: 5px;"
                                     "background-color: #2a4158;"
                                     "color: #8c9ea3;"
                                     "font-size: 27px;"
                                     "}"
                                     "QPushButton:hover {"
                                     "background-color: #2a5370;"
                                     "font-size: 24px;"
                                     "}"
                                     "QPushButton:pressed {"
                                     "background-color: #958a56;"
                                     "color: black;"
                                     "}");
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

void FunctionalityForm::get_hide_all()
{
    fileSystemForm->setEnabled(true);
    fileSystemForm->hide();
    screenSharingForm->setEnabled(true);
    screenSharingForm->hide();
    this->setEnabled(true);
    this->hide();
}

void FunctionalityForm::on_exitButton_clicked()
{
    int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выйти", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;

    emit user_disc();
}

void FunctionalityForm::on_fileSystemButton_clicked()
{
    emit send_functionalityForm(this, socket);
    fileSystemForm->show();
    this->hide();
}

void FunctionalityForm::get_enable_file_system()
{
    fileSystemForm->setEnabled(true);
}

void FunctionalityForm::get_file_sys(QString str)
{
    emit send_file_sys(str);
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
        WriteForm* writeForm;
        writeForm = new WriteForm(this, WRITE_MESSAGE, socket, nullptr);
        writeForm->show();
        this->hide();
        this->setEnabled(false);
        break;
    }
    case 1:     // Выключить компьютер
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выключить компьютер ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        sendAction("command:$shutdown /s$");
        break;
    }
    case 2:     // Перезагрузить компьютер
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите перезагрузить компьютер ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        sendAction("command:$shutdown /r$");
        break;
    }
    case 3:     // Получить xml файл с системной информацией
    {
        sendAction("command:xmlSysFile$msinfo32 /report C:/NjTmpSysInfo.txt$");
        break;
    }
    case 4:     // Получить версию windows
    {
        sendAction("command:file$ver > D:/NjTmpSysInfo.txt$");
        break;
    }
    case 5:     // Получить системное время
    {
        sendAction("command:file$time /T > D:/NjTmpSysInfo.txt$");
        break;
    }
    case 6:     // Получить дату
    {
        sendAction("command:file$date /T > D:/NjTmpSysInfo.txt$");
        break;
    }
    case 7:     // Получить часовой пояс
    {
        sendAction("command:file$tzutil /g > D:/NjTmpSysInfo.txt$");
        break;
    }
    case 8:     // Перейти в режим гибернации
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите перевести компьютер в режим гибернации ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        sendAction("command:$rundll32.exe PowrProf.dll,SetSuspendState$");
        break;
    }
    case 9:     // Перейти в режим сна
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите перевести компьютер в режим сна ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        sendAction("command:$rundll32.exe powrprof.dll,SetSuspendState 0,1,0$");
        break;
    }
    case 10:    // Заблокировать компьютер
    {
        int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите заблокировать компьютер ?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        sendAction("command:$Rundll32.exe User32.dll,LockWorkStation$");
        break;
    }
    case 11:    // Установить время
    {
        WriteForm* writeForm;
        writeForm = new WriteForm(this, CHANGE_TIME, socket, nullptr);
        writeForm->show();
        this->hide();
        this->setEnabled(false);
        break;
    }
    case 12:    // Установить дату
    {
        WriteForm* writeForm;
        writeForm = new WriteForm(this, CHANGE_DATE, socket, nullptr);
        writeForm->show();
        this->hide();
        this->setEnabled(false);
        break;
    }
    case 13:    // Сделать скриншот
        sendAction("screen:$");
        break;
    }
}

void FunctionalityForm::get_screenshot(QPixmap *screenshot)
{
    emit send_screenshot_for_sharing(screenshot);
}

void FunctionalityForm::sendAction(QString cmd)
{
    if (socket->isOpen())
    {
        socket->write(cmd.toStdString().c_str());
        socket->waitForBytesWritten(500);
    }
    else
    {
        mainWindow->show();
        this->hide();
        QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
    }
    this->setEnabled(false);
}
