#include "infoform.h"
#include "ui_infoform.h"
#include <QFileDialog>
#include <QMessageBox>

InfoForm::InfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoForm)
{
    ui->setupUi(this);

    allOk = true;
    changeMode = false;
    usersTableForm = nullptr;
    ptr = new userInfo;
    ptr_i = new QString;

    setWindowTitle("User info window");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    ui->avButton->setStyleSheet("QPushButton {"
                                "border-radius: 5px;"
                                "background-color: #2a4158;"
                                "color: #8c9ea3;"
                                "font-size: 30px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #2a5370;"
                                "font-size: 27px;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: #958a56;"
                                "color: black;"
                                "}");
    ui->nicknameLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->passwordLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->repPasswordLabel->setStyleSheet("color: #597387;"
                                        "font-size: 23px;");
    ui->fileSystemBox->setStyleSheet("color: #8c9ea3;"
                                     "font-size: 23px;");
    ui->screenShareBox->setStyleSheet("color: #8c9ea3;"
                                      "font-size: 23px;");
    ui->systemOpBox->setStyleSheet("color: #8c9ea3;"
                                   "font-size: 23px;");
    ui->acceptButton->setStyleSheet("QPushButton {"
                                    "border-radius: 5px;"
                                    "background-color: #2a4158;"
                                    "color: #8c9ea3;"
                                    "font-size: 30px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #2a5370;"
                                    "font-size: 27px;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #958a56;"
                                    "color: black;"
                                    "}");
    ui->backButton->setStyleSheet("QPushButton {"
                                  "border-radius: 5px;"
                                  "background-color: #2a4158;"
                                  "color: #8c9ea3;"
                                  "font-size: 30px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #2a5370;"
                                  "font-size: 27px;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: #958a56;"
                                  "color: black;"
                                  "}");

    QRegExp exp1("[A-Za-z0-9_ ]{1,30}");  // установка валидатора
    ui->nicknameEdit->setValidator(new QRegExpValidator(exp1, this));   // установка валидатора
    QRegExp exp2("[A-Za-z0-9_ ]{1,15}");  // установка валидатора
    ui->passwordEdit->setValidator(new QRegExpValidator(exp2, this));   // установка валидатора
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->repPasswordEdit->setValidator(new QRegExpValidator(exp2, this));    // установка валидатора
    ui->repPasswordEdit->setEchoMode(QLineEdit::Password);

    QPixmap* av = new QPixmap(":/emptyAvatar.png");
    int w = ui->userAv->width();
    int h = ui->userAv->height();
    ui->userAv->clear();
    ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
    ui->userAv->setStyleSheet("background: none;");
    delete av;
}

InfoForm::~InfoForm()
{
    delete ui;
    delete ptr;
    delete ptr_i;
}

void InfoForm::existing_name()
{
    allOk = false;
}

void InfoForm::get_window_for_back(UsersTableForm *mw)
{
    usersTableForm = mw;
}

void InfoForm::get_ptr_i_for_view(UsersTableForm *mw, userInfo *_ptr, QString *_ptr_i)
{
    changeMode = false;

    usersTableForm = mw;

    ui->nicknameEdit->setText(_ptr->getName());
    ui->passwordEdit->setText(_ptr->getPassword());
    ui->repPasswordEdit->setText(_ptr->getPassword());

    if (!_ptr_i->isEmpty())
    {
        QPixmap* av = new QPixmap(*_ptr_i);
        int w = ui->userAv->width();
        int h = ui->userAv->height();
        ui->userAv->clear();
        ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAv->setStyleSheet("background: none;");
        delete av;
    }
    else
    {
        QPixmap* av = new QPixmap(":/emptyAvatar.png");
        int w = ui->userAv->width();
        int h = ui->userAv->height();
        ui->userAv->clear();
        ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAv->setStyleSheet("background: none;");
        delete av;
    }

    if (_ptr->getPermissions() & 4)
        ui->fileSystemBox->setCheckState(Qt::CheckState::Checked);
    if (_ptr->getPermissions() & 2)
        ui->screenShareBox->setCheckState(Qt::CheckState::Checked);
    if (_ptr->getPermissions() & 1)
        ui->systemOpBox->setCheckState(Qt::CheckState::Checked);

    ui->avButton->setEnabled(false);
    ui->nicknameEdit->setEnabled(false);
    ui->passwordEdit->setEnabled(false);
    ui->repPasswordEdit->setEnabled(false);
    ui->fileSystemBox->setEnabled(false);
    ui->screenShareBox->setEnabled(false);
    ui->systemOpBox->setEnabled(false);
    ui->acceptButton->setEnabled(false);
}

void InfoForm::get_ptr_i_for_change(UsersTableForm *mw, userInfo *_ptr, QString *_ptr_i)
{
    changeMode = true;

    usersTableForm = mw;

    ptr->setName(_ptr->getName());
    ptr->setPassword(_ptr->getPassword());
    ptr->setAv(_ptr->getAv());
    ptr->setPermissions(_ptr->getPermissions());
    *ptr_i = *_ptr_i;

    ui->nicknameEdit->setText(_ptr->getName());
    ui->passwordEdit->setText(_ptr->getPassword());
    ui->repPasswordEdit->setText(_ptr->getPassword());

    if (!_ptr_i->isEmpty())
    {
        QPixmap* av = new QPixmap(*_ptr_i);
        int w = ui->userAv->width();
        int h = ui->userAv->height();
        ui->userAv->clear();
        ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAv->setStyleSheet("background: none;");
        delete av;
    }
    else
    {
        QPixmap* av = new QPixmap(":/emptyAvatar.png");
        int w = ui->userAv->width();
        int h = ui->userAv->height();
        ui->userAv->clear();
        ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
        ui->userAv->setStyleSheet("background: none;");
        delete av;
    }

    if (_ptr->getPermissions() & 4)
        ui->fileSystemBox->setCheckState(Qt::CheckState::Checked);
    if (_ptr->getPermissions() & 2)
        ui->screenShareBox->setCheckState(Qt::CheckState::Checked);
    if (_ptr->getPermissions() & 1)
        ui->systemOpBox->setCheckState(Qt::CheckState::Checked);
}

void InfoForm::on_backButton_clicked()
{
    ui->avButton->setStyleSheet("QPushButton {"
                                "border-radius: 5px;"
                                "background-color: #2a4158;"
                                "color: #8c9ea3;"
                                "font-size: 30px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #2a5370;"
                                "font-size: 27px;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: #958a56;"
                                "color: black;"
                                "}");
    ui->nicknameLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->passwordLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->repPasswordLabel->setStyleSheet("color: #597387;"
                                        "font-size: 23px;");
    ui->fileSystemBox->setStyleSheet("color: #8c9ea3;"
                                     "font-size: 23px;");
    ui->screenShareBox->setStyleSheet("color: #8c9ea3;"
                                      "font-size: 23px;");
    ui->systemOpBox->setStyleSheet("color: #8c9ea3;"
                                   "font-size: 23px;");
    ui->acceptButton->setStyleSheet("QPushButton {"
                                    "border-radius: 5px;"
                                    "background-color: #2a4158;"
                                    "color: #8c9ea3;"
                                    "font-size: 30px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #2a5370;"
                                    "font-size: 27px;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background-color: #958a56;"
                                    "color: black;"
                                    "}");
    ui->backButton->setStyleSheet("QPushButton {"
                                  "border-radius: 5px;"
                                  "background-color: #2a4158;"
                                  "color: #8c9ea3;"
                                  "font-size: 30px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #2a5370;"
                                  "font-size: 27px;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: #958a56;"
                                  "color: black;"
                                  "}");

    ui->avButton->setEnabled(true);
    ui->nicknameEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);
    ui->repPasswordEdit->setEnabled(true);
    ui->fileSystemBox->setEnabled(true);
    ui->screenShareBox->setEnabled(true);
    ui->systemOpBox->setEnabled(true);
    ui->acceptButton->setEnabled(true);

    ui->nicknameEdit->clear();
    ui->passwordEdit->clear();
    ui->repPasswordEdit->clear();

    ui->fileSystemBox->setCheckState(Qt::CheckState::Unchecked);
    ui->screenShareBox->setCheckState(Qt::CheckState::Unchecked);
    ui->systemOpBox->setCheckState(Qt::CheckState::Unchecked);

    QPixmap* av = new QPixmap(":/emptyAvatar.png");
    int w = ui->userAv->width();
    int h = ui->userAv->height();
    ui->userAv->clear();
    ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
    ui->userAv->setStyleSheet("background: none;");
    delete av;

    delete ptr;
    ptr = new userInfo;
    delete ptr_i;
    ptr_i = new QString;

    changeMode = false; // сброс режима работы
    allOk = true;   // сброс режима работы

    usersTableForm->show();
    this->hide();
}

void InfoForm::on_avButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("(*.jpg)"));
    QPixmap pix(path);
    if (path.isNull())
    {
        QMessageBox::critical(this, "Ошибка!", "Ошибка открытия изображения!");
        return;
    }
    int w = ui->userAv->width();
    int h = ui->userAv->height();
    ui->userAv->clear();
    ui->userAv->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ptr->setAv(true);
    *ptr_i = path;
}

void InfoForm::on_nicknameEdit_editingFinished()
{
    ptr->setName(ui->nicknameEdit->text());
}

void InfoForm::on_passwordEdit_cursorPositionChanged(int arg1, int arg2)
{
    //EMPTY
}

void InfoForm::on_passwordEdit_editingFinished()
{
    ptr->setPassword(ui->passwordEdit->text());
}

void InfoForm::on_repPasswordEdit_editingFinished()
{

}

void InfoForm::on_acceptButton_clicked()
{
    if (ui->nicknameEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty() || ui->repPasswordEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Ошибка!", "Введены не все обязательные элементы!");
        ui->nicknameLabel->setStyleSheet("color: red;"
                                         "font-size: 23px;");
        ui->passwordLabel->setStyleSheet("color: red;"
                                         "font-size: 23px;");
        ui->repPasswordLabel->setStyleSheet("color: red;"
                                            "font-size: 23px;");
        return;
    }
    ui->nicknameLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->passwordLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->repPasswordLabel->setStyleSheet("color: #597387;"
                                        "font-size: 23px;");
    if (ui->passwordEdit->text() != ui->repPasswordEdit->text())
    {
        QMessageBox::information(this, "Ошибка!", "Пароль введён некорректно!");
        ui->passwordLabel->setStyleSheet("color: red;"
                                         "font-size: 23px;");
        ui->repPasswordLabel->setStyleSheet("color: red;"
                                            "font-size: 23px;");
        return;
    }
    ui->passwordLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->repPasswordLabel->setStyleSheet("color: #597387;"
                                        "font-size: 23px;");

    if (ui->fileSystemBox->checkState() != Qt::CheckState::Unchecked)
        ptr->setPermissions(ptr->getPermissions() | 4);
    else
        ptr->setPermissions(ptr->getPermissions() & -5);
    if (ui->screenShareBox->checkState() != Qt::CheckState::Unchecked)
        ptr->setPermissions(ptr->getPermissions() | 2);
    else
        ptr->setPermissions(ptr->getPermissions() & -3);
    if (ui->systemOpBox->checkState() != Qt::CheckState::Unchecked)
        ptr->setPermissions(ptr->getPermissions() | 1);
    else
        ptr->setPermissions(ptr->getPermissions() & -2);

    if (changeMode == false)    // проверка на режим работы
        emit send_new_user(ptr, ptr_i);
    else
        emit send_changed_user(ptr, ptr_i);

    if (!allOk) // проверка на режим работы
    {
        QMessageBox::information(this, "Предупреждение!", "Пользователь с таким именем уже существует!");
        ui->nicknameLabel->setStyleSheet("color: red;"
                                         "font-size: 23px;");
        allOk = true;
        return;
    }
    ui->nicknameLabel->setStyleSheet("color: #597387;"
                                     "font-size: 23px;");
    ui->avButton->setEnabled(true);
    ui->nicknameEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);
    ui->repPasswordEdit->setEnabled(true);
    ui->fileSystemBox->setEnabled(true);
    ui->screenShareBox->setEnabled(true);
    ui->systemOpBox->setEnabled(true);
    ui->acceptButton->setEnabled(true);

    ui->nicknameEdit->clear();
    ui->passwordEdit->clear();
    ui->repPasswordEdit->clear();

    ui->fileSystemBox->setCheckState(Qt::CheckState::Unchecked);
    ui->screenShareBox->setCheckState(Qt::CheckState::Unchecked);
    ui->systemOpBox->setCheckState(Qt::CheckState::Unchecked);

    QPixmap* av = new QPixmap(":/emptyAvatar.png");
    int w = ui->userAv->width();
    int h = ui->userAv->height();
    ui->userAv->clear();
    ui->userAv->setPixmap(av->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
    ui->userAv->setStyleSheet("background: none;");
    delete av;

    delete ptr;
    ptr = new userInfo;
    delete ptr_i;
    ptr_i = new QString;

    changeMode = false; // сброс режима работы
    allOk = true;   // сброс режима работы

    usersTableForm->show();
    this->hide();
}
