#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    usersTableForm = new UsersTableForm;    // Создаём окно пользователей

    setWindowTitle("RAT-Server application");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    ui->run->setShortcut(tr("Ctrl+C"));
    ui->usersTable->setShortcut(tr("Ctrl+W"));
    ui->quit->setShortcut(tr("Ctrl+E"));
    ui->author->setShortcut(tr("Ctrl+A"));
    ui->about->setShortcut(tr("Ctrl+D"));

    ui->logoLabel->setAlignment(Qt::AlignCenter);
    ui->logoLabel->setStyleSheet("font-size: 100px;");
    ui->waitingConnectionLabel->setAlignment(Qt::AlignCenter);
    ui->waitingConnectionLabel->setStyleSheet("font-size: 60px;");
    ui->activeUser->setAlignment(Qt::AlignCenter);
    ui->activeUser->setStyleSheet("border: 4px solid #597387;"
                                  "font-size: 30px;");
    ui->userAv->setStyleSheet("background: none;");

    connect(this, SIGNAL(send_main_window_for_user_window(QMainWindow*)), usersTableForm, SLOT(get_main_window(QMainWindow*)));
    connect(&server, SIGNAL(send_user_info(QString, QString*)), this, SLOT(set_active_user(QString, QString*)));
    connect(&server, SIGNAL(waiting_for_connection()), this, SLOT(get_waiting_for_connection()));
    connect(this, SIGNAL(send_sLogger(QString)), &server, SLOT(set_sLogger(QString)));
    connect(&server, SIGNAL(send_start_ui()), this, SLOT(start_ui()));

    ui->waitingConnectionLabel->hide();
    ui->canselButton->hide();
    ui->activeUser->hide();
    ui->userAv->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete usersTableForm;
}

void MainWindow::set_active_user(QString name, QString* sPath)
{
    ui->logoLabel->hide();
    ui->connectButton->hide();
    ui->menuBar->hide();
    ui->waitingConnectionLabel->hide();
    ui->canselButton->hide();
    ui->activeUser->show();
    ui->userAv->show();

    ui->activeUser->clear();
    if (name.size() > 15)
    {
        QString tmpName;
        for (int i = 0; i < 12; i++)
            tmpName += name[i];
        tmpName += "...";
        ui->activeUser->setText(tmpName + " is using this PC");
    }
    else
        ui->activeUser->setText(name + " is using this PC");

    if (sPath->isEmpty())
    {
        QPixmap* av = new QPixmap(":/emptyAvatar.png");
        int w = ui->userAv->width();
        int h = ui->userAv->height();
        ui->userAv->clear();
        ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAv->setStyleSheet("background: none;");
        delete av;
    }
    else
    {
        QPixmap* av = new QPixmap(*sPath);
        int w = ui->userAv->width();
        int h = ui->userAv->height();
        ui->userAv->clear();
        ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAv->setStyleSheet("background: none;");
        delete av;
    }
}

void MainWindow::on_run_triggered()
{
    on_connectButton_clicked();
}

void MainWindow::on_author_triggered()
{
    QMessageBox::about(this, "Author", "Программу разработал студент группы\n"
                                       "850502: Домбровский Тимур");
}

void MainWindow::on_connectButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open file"));    // ввод пути к файлу
    if (path.isNull())
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка открытия файла!");
        return;
    }

    QFile file(path + "/main.ratut");   // открытие файла
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка открытия файла!");
        return;
    }

    emit send_sLogger(path);

    unsigned int file_quantity;
    file.read((char*)&file_quantity, sizeof(file_quantity));    // получение количества пользователей в файле
    userList.set_adress(path);   // добаление адреса открытого файла

    for (unsigned int i(0); i < file_quantity; i++) // считываем основную информацию о пользователях
    {
        file.seek(10 + i * 60 + i * 30 + i * 10 + i * 10);
        userInfo* userInfoPtr = nullptr;
        userInfoPtr = new userInfo;
        char tmpText1[60] = {};
        file.read(tmpText1, 60);
        userInfoPtr->setName(tmpText1);
        file.seek(10 + (i + 1) * 60 + i * 30 + i * 10 + i * 10);
        char tmpText2[30] = {};
        file.read(tmpText2, 30);
        userInfoPtr->setPassword(tmpText2);
        file.seek(10 + (i + 1) * 60 + (i + 1) * 30 + i * 10 + i * 10);
        int isAv;
        file.read((char*)&isAv, sizeof(int));
        if (isAv == 1)
            userInfoPtr->setAv(true);
        else
            userInfoPtr->setAv(false);
        file.seek(10 + (i + 1) * 60 + (i + 1) * 30 + (i + 1) * 10 + i * 10);
        int permissions;
        file.read((char*)&permissions, sizeof(int));
        userInfoPtr->setPermissions(permissions);
        userList.push(userInfoPtr, new QString);
        userList.set_quantity(userList.get_quantity() + 1);
        delete userInfoPtr;
    }
    file.flush();
    file.close();
    for (unsigned int i(0); i < userList.get_quantity(); i++)
        if (userList.findID(i + 1)->ptr->getAv() && userList.findID(i + 1)->ptr_i->isEmpty())
        {   // если всей информации о пользователе нет, то считываем её из старого файла
            QString** tmp = &(userList.findID(i + 1)->ptr_i);
            *tmp = new QString;
            *(*tmp) = userList.get_adress() + "/" + userList.findID(i + 1)->ptr->getName() + "/pic.jpg";
        }
    if (file_quantity == 0) // если нет пользователей, то файл - новый
    {
        QMessageBox::critical(this, "Error", "Файл пуст!");
        userList.Delete();
        return;
    }

    ui->logoLabel->hide();
    ui->connectButton->hide();
    ui->menuBar->hide();
    ui->waitingConnectionLabel->show();
    ui->canselButton->show();
    ui->activeUser->hide();
    ui->userAv->hide();

    server.startServer(&userList);
}

void MainWindow::on_canselButton_clicked()
{
    userList.Delete();

    ui->logoLabel->show();
    ui->connectButton->show();
    ui->menuBar->show();
    ui->waitingConnectionLabel->hide();
    ui->canselButton->hide();
    ui->activeUser->hide();
    ui->userAv->hide();

    server.close();
}

void MainWindow::start_ui()
{
    on_canselButton_clicked();
}

void MainWindow::on_quit_triggered()
{
    int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выйти", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    this->close();
}

void MainWindow::on_usersTable_triggered()
{
    emit send_main_window_for_user_window(this);
    usersTableForm->show();
    this->hide();
}

void MainWindow::get_waiting_for_connection()
{
    ui->logoLabel->hide();
    ui->connectButton->hide();
    ui->menuBar->hide();
    ui->waitingConnectionLabel->show();
    ui->canselButton->show();
    ui->activeUser->hide();
    ui->userAv->hide();
}
