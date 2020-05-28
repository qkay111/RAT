#include "userstableform.h"
#include "ui_userstableform.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

UsersTableForm::UsersTableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersTableForm)
{
    ui->setupUi(this);

    mainWindow = nullptr;
    infoForm = new InfoForm;

    setWindowTitle("User table window");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    connect(this, SIGNAL(send_window_for_info_form(UsersTableForm*)), infoForm, SLOT(get_window_for_back(UsersTableForm*)));
    connect(this, SIGNAL(send_window_for_info_form_for_view(UsersTableForm*,userInfo*,QString*)), infoForm, SLOT(get_ptr_i_for_view(UsersTableForm*,userInfo*,QString*)));
    connect(this, SIGNAL(send_window_for_info_form_for_change(UsersTableForm*,userInfo*,QString*)), infoForm, SLOT(get_ptr_i_for_change(UsersTableForm*,userInfo*,QString*)));
    connect(infoForm, SIGNAL(send_new_user(userInfo*,QString*)), this, SLOT(get_new_user(userInfo*,QString*)));
    connect(infoForm, SIGNAL(send_changed_user(userInfo*,QString*)), this, SLOT(get_changed_user(userInfo*,QString*)));
    connect(this, SIGNAL(existing_name()), infoForm, SLOT(existing_name()));

    ui->aboutButton->hide();
    ui->addButton->hide();
    ui->changeButton->hide();
    ui->deleteButton->hide();
    ui->listWidget->hide();
}

UsersTableForm::~UsersTableForm()
{
    delete ui;
    delete infoForm;
}

void UsersTableForm::get_main_window(QMainWindow *mw)
{
    mainWindow = mw;
}

void UsersTableForm::on_backButton_clicked()
{
    if (!userList.get_adress().isEmpty())
    {
        int result = QMessageBox::question(this, "Сохранение", "Вы желаете сохранить текущий файл?", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes)
            saveFile();
    }

    userList.Delete();
    ui->createButton->show();
    ui->openButton->show();
    ui->aboutButton->hide();
    ui->addButton->hide();
    ui->changeButton->hide();
    ui->deleteButton->hide();
    ui->listWidget->hide();
    ui->listWidget->clear();

    mainWindow->show();
    this->hide();
}

void UsersTableForm::on_createButton_clicked()
{
    QString tmp = nullptr;
    tmp = QFileDialog::getSaveFileName(this);   // путь для создания папки для хранения
    QDir dirName;
    if (!dirName.mkdir(tmp))    // создание папки
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка создания каталога!");
        return;
    }
    QFile fout(tmp + "/main.ratut");    // создание файла с основной информацие о пользователях
    if (!fout.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка создания файла!");
        return;
    }
    unsigned int file_quantity = 0u;
    fout.write((char*)&file_quantity, sizeof(file_quantity));   // заносим количество пользователей
    fout.flush();
    userList.set_quantity(0);
    userList.set_adress(tmp);    // добаление адреса нового файла
    fout.close();

    ui->createButton->hide();
    ui->openButton->hide();
    ui->aboutButton->show();
    ui->addButton->show();
    ui->changeButton->show();
    ui->deleteButton->show();
    ui->listWidget->show();

    ui->aboutButton->setEnabled(false);
    ui->changeButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

void UsersTableForm::on_openButton_clicked()
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
    for (unsigned int i(0); i < file_quantity; i++) // добавление названий пользователей в список пользователей
    {
        char tmpptr[15];
        bool tmpcheacker;
        tmpcheacker = _itoa_s(i + 1, tmpptr, 15, 10);
        if (tmpcheacker == true)
        {
            QMessageBox::critical(this, "Ошибка!", "Ошибка преобразования числа в строку!");
            return;
        }
        ui->listWidget->addItem(tmpptr + (".   " + userList.findID(i + 1)->ptr->getName()));
    }
    if (file_quantity == 0) // если нет пользователей, то файл - новый
    {
        ui->aboutButton->setEnabled(false);
        ui->changeButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }
    else
    {
        ui->aboutButton->setEnabled(true);
        ui->changeButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
    }

    ui->createButton->hide();
    ui->openButton->hide();
    ui->aboutButton->show();
    ui->addButton->show();
    ui->changeButton->show();
    ui->deleteButton->show();
    ui->listWidget->show();
}

void UsersTableForm::saveFile()
{
    QFile fs(userList.get_adress() + "/main.ratut"); // открытие файла
    if (!fs.open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка открытия файла!");
        return;
    }
    unsigned int file_quantity;
    fs.read((char*)&file_quantity, sizeof(file_quantity));  // считываем старое количество пользователей
    if (file_quantity == 0) // если не было пользователей, то файл - новый
    {
        fs.seek(0);
        file_quantity = userList.get_quantity();
        fs.write((char*)&file_quantity, sizeof(file_quantity)); // запись нового количества пользователей в файл
        for (unsigned int i(0); i < userList.get_quantity(); i++)    // запись информации о пользователях в файл
        {
            fs.seek(10 + i * 60 + i * 30 + i * 10 + i * 10);
            fs.write(userList.findID(i + 1)->ptr->getName().toStdString().c_str(),
            strlen(userList.findID(i + 1)->ptr->getName().toStdString().c_str()));
            fs.seek(10 + (i + 1) * 60 + i * 30 + i * 10 + i * 10);
            fs.write(userList.findID(i + 1)->ptr->getPassword().toStdString().c_str(),
            strlen(userList.findID(i + 1)->ptr->getPassword().toStdString().c_str()));
            fs.seek(10 + (i + 1) * 60 + (i + 1) * 30 + i * 10 + i * 10);
            if (userList.findID(i + 1)->ptr->getAv())
            {
                int num = 1;
                fs.write((char*)&num, sizeof(int));
            }
            else
            {
                int num = 0;
                fs.write((char*)&num, sizeof(int));
            }
            fs.seek(10 + (i + 1) * 60 + (i + 1) * 30 + (i + 1) * 10 + i * 10);
            int tmpPerm = userList.findID(i + 1)->ptr->getPermissions();
            fs.write((char*)&tmpPerm, sizeof(int));
            QDir dirName;
            QString tmpAdress = userList.get_adress() + "/" + userList.findID(i + 1)->ptr->getName();
            if (!dirName.mkdir(tmpAdress))  // создание каталога под каждый файл
            {
                QMessageBox::critical(this, "Ошибка!", "Ошибка создания каталога!");
                fs.flush();
                fs.close();
                return;
            }
            if (userList.findID(i + 1)->ptr->getAv())
                QFile::copy(*(userList.findID(i + 1)->ptr_i), tmpAdress + "/pic.jpg");
        }
    }
    else    // если пользователи уже были в файле
    {
        fs.flush();
        fs.close();
        for (unsigned int i(0); i < userList.get_quantity(); i++)
            if (userList.findID(i + 1)->ptr->getAv() && userList.findID(i + 1)->ptr_i->isEmpty())
            {   // если всей информации о пользователе нет, то считываем её из старого файла
                QString** tmp = &(userList.findID(i + 1)->ptr_i);
                *tmp = new QString;
                *(*tmp) = userList.get_adress() + "/" + userList.findID(i + 1)->ptr->getName() + "/pic.jpg";
            }
        QString oldAdress = userList.get_adress();   // старый адрес
        QDir newFolder(oldAdress); // новая директория
        newFolder.cdUp();
        if (!newFolder.mkdir("tmpRatutdir"))    // запись в новый файл
        {
            QMessageBox::critical(this, "Ошибка!", "Ошибка создания каталога!");
            return;
        }
        QFile fout(newFolder.path() + "/tmpRatutdir" + "/main.ratut");
        if (!fout.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, "Ошибка!", "Ошибка создания файла!");
            return;
        }
        unsigned int file_quantity = 0u;
        fout.write((char*)&file_quantity, sizeof(file_quantity));
        fout.flush();
        fout.close();

        QFile::copy(userList.get_adress() + "/logfile.txt", newFolder.path() + "/tmpRatutdir" + "/logfile.txt");

        userList.set_adress(newFolder.path() + "/tmpRatutdir");
        saveFile();

        QDir newName(oldAdress);
        QString newNameFolder = newName.dirName();
        QDir toRemove(oldAdress);   // удаление старого файла
        toRemove.removeRecursively();   // удаление старого файла
        newFolder.rename("tmpRatutdir", newNameFolder); // переименовывание нового файла
        userList.set_adress(newFolder.path() + "/" + newNameFolder);
    }
}

void UsersTableForm::on_aboutButton_clicked()
{
    bool flag = true;
    for (unsigned int i(0); i < userList.get_quantity(); i++)    // проверка на выделение пользователя
        if (ui->listWidget->isItemSelected(ui->listWidget->item(i)))
            flag = false;
    if (flag)
    {
        QMessageBox::information(this, "Предупреждение!", "Вы не выбрали элемент!");
        return;
    }
    unsigned int tmpID = 0; // получение номера пользователя
    for (int i(0); ((ui->listWidget->currentItem()->text()).toStdString())[i] != '.'; i++ )
        tmpID = tmpID * 10 + ((ui->listWidget->currentItem()->text()).toStdString())[i] - '0';
    if (userList.findID(tmpID)->ptr->getAv() && userList.findID(tmpID)->ptr_i->isEmpty())    // проверка на наличие информации об этом пользователе
    {   // если основной информации нет, то считываем её из файла
        QString** tmp = &(userList.findID(tmpID)->ptr_i);
        *tmp = new QString;
        *(*tmp) = userList.get_adress() + "/" + userList.findID(tmpID)->ptr->getName() + "/pic.jpg";
    }
    emit send_window_for_info_form_for_view(this, userList.findID(tmpID)->ptr, userList.findID(tmpID)->ptr_i);
    infoForm->show();
    this->hide();
}

void UsersTableForm::on_addButton_clicked()
{
    emit send_window_for_info_form(this);
    infoForm->show();
    this->hide();
}

void UsersTableForm::get_new_user(userInfo *ptr, QString *ptr_i)
{
    for (unsigned int i(0); i < userList.get_quantity(); i++)    // проверка на наличие такого же названия
    {
        if (userList.findID(i + 1)->ptr->getName() == ptr->getName())
        {
            emit existing_name();   // если такое название уже есть, повторно вызываем окно ввода
            return;
        }
    }
    userList.push(ptr, ptr_i);   // добавление пользователя
    userList.set_quantity(userList.get_quantity() + 1); // обновление количества пользователей
    char tmpptr[15];
    bool tmpcheacker;
    tmpcheacker = _itoa_s(userList.get_quantity(), tmpptr, 15, 10);  // преобразовываем число в строку
    if (tmpcheacker == true)
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка преобразования числа в строку!");
        return;
    }
    ui->listWidget->addItem(tmpptr + (".   " + ptr->getName()));   // добавление названия нового товара в список

    ui->aboutButton->setEnabled(true);
    ui->changeButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}

void UsersTableForm::on_changeButton_clicked()
{
    bool flag = true;
    for (unsigned int i(0); i < userList.get_quantity(); i++)    // проверка на выделение пользователя
        if (ui->listWidget->isItemSelected(ui->listWidget->item(i)))
            flag = false;
    if (flag)   // если пользователь не выбран
    {
        QMessageBox::information(this, "Предупреждение!", "Вы не выбрали элемент!");
        return;
    }
    unsigned int tmpID = 0; // получение номера продукта
    for (int i(0); ((ui->listWidget->currentItem()->text()).toStdString())[i] != '.'; i++ )
        tmpID = tmpID * 10 + ((ui->listWidget->currentItem()->text()).toStdString())[i] - '0';
    if (userList.findID(tmpID)->ptr->getAv() && userList.findID(tmpID)->ptr_i->isEmpty())   // проверка на наличие информации об этом пользователе
    {   // если всей информации нет, то считываем её из файла
        QString** tmp = &(userList.findID(tmpID)->ptr_i);
        *tmp = new QString;
        *(*tmp) = userList.get_adress() + "/" + userList.findID(tmpID)->ptr->getName() + "/pic.jpg";
    }
    emit send_window_for_info_form_for_change(this, userList.findID(tmpID)->ptr, userList.findID(tmpID)->ptr_i);
    infoForm->show();
    this->hide();
}

void UsersTableForm::get_changed_user(userInfo *_ptr, QString *_ptr_i)
{
    unsigned int tmpID = 0;
    for (int i(0); ((ui->listWidget->currentItem()->text()).toStdString())[i] != '.'; i++ )
        tmpID = tmpID * 10 + ((ui->listWidget->currentItem()->text()).toStdString())[i] - '0';
    for (unsigned int i(0); i < userList.get_quantity(); i++)    // проверка на наличие такого же названия
    {
        if (userList.findID(i + 1)->ptr->getName() == _ptr->getName())
        {
            if (userList.findID(tmpID)->ptr->getName() == _ptr->getName())
                continue;
            emit existing_name();   // если такое название уже есть, повторно вызываем окно ввода
            return;
        }
    }

    if (_ptr->getName() != userList.findID(tmpID)->ptr->getName())   // если название было изменено, то обновляем его в списке продуктов
    {
        userList.findID(tmpID)->ptr->setName(_ptr->getName());
        char tmpptr[15];
        bool tmpcheacker;
        tmpcheacker = _itoa_s(tmpID, tmpptr, 15, 10);
        if (tmpcheacker == true)
        {
            QMessageBox::critical(this, "Ошибка!", "Ошибка преобразования числа в строку!");
            return;
        }
        ui->listWidget->currentItem()->setText(tmpptr + (".   " + _ptr->getName()));
    }

    userList.findID(tmpID)->ptr->setName(_ptr->getName());
    userList.findID(tmpID)->ptr->setPassword(_ptr->getPassword());
    userList.findID(tmpID)->ptr->setAv(_ptr->getAv());
    userList.findID(tmpID)->ptr->setPermissions(_ptr->getPermissions());
    *(userList.findID(tmpID)->ptr_i) = *_ptr_i;
}

void UsersTableForm::on_deleteButton_clicked()
{
    bool flag = true;
    for (unsigned int i(0); i < userList.get_quantity(); i++)    // проверка на выделение пользователя
        if (ui->listWidget->isItemSelected(ui->listWidget->item(i)))
            flag = false;
    if (flag)
    {
        QMessageBox::information(this, "Предупреждение!", "Вы не выбрали элемент!");
        return;
    }
    unsigned int tmpID = 0; // получение номера пользователя
    for (int i(0); ((ui->listWidget->currentItem()->text()).toStdString())[i] != '.'; i++ )
        tmpID = tmpID * 10 + ((ui->listWidget->currentItem()->text()).toStdString())[i] - '0';

    if (userList.pop(tmpID)) // удаление пользователя из контейнера
    {
        unsigned int tmpValueID = 1;
        while (userList.findID(tmpID + 1)) // уменьшение индекса в последующих элементах, если они есть
        {
            userList.findID(tmpID++ + 1)->id--;
        }
        ui->listWidget->clear();
        while (tmpValueID < tmpID)  // обновление названий пользователей в списке пользователей
        {
            char tmpptr[15];
            bool tmpcheacker;
            tmpcheacker = _itoa_s(tmpValueID, tmpptr, 15, 10);
            if (tmpcheacker == true)
            {
                QMessageBox::critical(this, "Ошибка!", "Ошибка преобразования числа в строку!");
                return;
            }
            ui->listWidget->addItem(tmpptr + (".   " + userList.findID(tmpValueID++)->ptr->getName()));
        }
        if (userList.get_quantity() == 0u)   // если был удалён последний пользователь, то ограничиваем интерфейс
        {
            ui->aboutButton->setEnabled(false);
            ui->changeButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
        }
    }
}
