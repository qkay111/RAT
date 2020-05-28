#include "filesystemform.h"
#include "ui_filesystemform.h"
#include <QLineEdit>    // Для выравнивания комбо-бокса

FileSystemForm::FileSystemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSystemForm)
{
    ui->setupUi(this);

    functionalityForm = nullptr;

    setWindowTitle("Файловая система");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    ui->showDirWidget->setStyleSheet("QListView {"
                                     "background-color: #8c9ea3;"
                                     "color: black;"
                                     "font-size: 25px;"
                                     "}");
    ui->pathLabel->setAlignment(Qt::AlignCenter);
    ui->pathLabel->setStyleSheet("border: 4px solid #2a4158;"
                                 "background-color: #958a56;"
                                 "color: #2a4158;"
                                 "font-size: 24px;");
    ui->pathEdit->setStyleSheet("font-size: 24px");
    ui->actionBox->setEditable(true); // выравнивание комбо-бокса
    ui->actionBox->lineEdit()->setReadOnly(true); // выравнивание комбо-бокса
    ui->actionBox->lineEdit()->setAlignment(Qt::AlignCenter);  // выравнивание комбо-бокса
    for(int i = 0; i < ui->actionBox->count(); i++)    // выравнивание комбо-бокса
        ui->actionBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole); // выравнивание комбо-бокса
    ui->acceptButton->setStyleSheet("QPushButton {"
                                    "background: #2a4158;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background: green;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "background: #958a56;"
                                    "}");
    ui->backButton->setStyleSheet("QPushButton {"
                                  "background: #2a4158;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background: red;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background: #958a56;"
                                  "}");

    QRegExp validator("[A-Za-zА-Яа-я0-9._:/ ]{1,150}");
    ui->pathEdit->setValidator(new QRegExpValidator(validator, this));
}

FileSystemForm::~FileSystemForm()
{
    delete ui;
}

void FileSystemForm::get_functionalityForm(FunctionalityForm* mw, QTcpSocket* sk)
{
    ui->showDirWidget->clear();
    ui->pathEdit->clear();
    ui->actionBox->setCurrentIndex(0);

    functionalityForm = mw;
    socket = sk;
}

void FileSystemForm::on_acceptButton_clicked()
{
    if (ui->pathEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "Error!", "Вы не указали путь!");
        return;
    }

    switch (ui->actionBox->currentIndex())
    {
    case 0: // Войти
        for (int i = 0; i < ui->pathEdit->text().size(); i++)
            if (ui->pathEdit->text()[i] == '.')
            {
                QMessageBox::critical(this, "Error!", "Путь указан неверно!");
                return;
            }

        if (socket->isOpen())
        {
            //socket->write(QString("filesys:enter$" + ui->pathEdit->text() + '$').toStdString().c_str());
            socket->write((char*)(QString("filesys:enter$" + ui->pathEdit->text() + '$').toStdWString().c_str()), (QString("filesys:enter$" + ui->pathEdit->text() + '$').size() * 2));
            socket->waitForBytesWritten(500);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    case 1: // Создать папку
        for (int i = 0; i < ui->pathEdit->text().size(); i++)
            if (ui->pathEdit->text()[i] == '.')
            {
                QMessageBox::critical(this, "Error!", "Путь указан неверно!");
                return;
            }

        if (socket->isOpen())
        {
            //socket->write(QString("filesys:mkdir$" + ui->pathEdit->text() + '$').toStdString().c_str());
            socket->write((char*)(QString("filesys:mkdir$" + ui->pathEdit->text() + '$').toStdWString().c_str()), (QString("filesys:mkdir$" + ui->pathEdit->text() + '$').size() * 2));
            socket->waitForBytesWritten(500);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    case 2: // Создать файл
    {
        bool dotFlag = true;
        for (int i = ui->pathEdit->text().size() - 1; i >= 0; i--)
        {
            if (ui->pathEdit->text()[i] == '/')
                break;
            if (ui->pathEdit->text()[i] == '.')
            {
                dotFlag = false;
                break;
            }
        }
        if (dotFlag)
        {
            QMessageBox::critical(this, "Error!", "Путь указан неверно!");
            return;
        }

        if (socket->isOpen())
        {
            //socket->write(QString("filesys:mkfile$" + ui->pathEdit->text() + '$').toStdString().c_str());
            socket->write((char*)(QString("filesys:mkfile$" + ui->pathEdit->text() + '$').toStdWString().c_str()), (QString("filesys:mkfile$" + ui->pathEdit->text() + '$').size() * 2));
            socket->waitForBytesWritten(500);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 3: // Открыть файл
    {
        bool dotFlag = true;
        for (int i = ui->pathEdit->text().size() - 1; i >= 0; i--)
        {
            if (ui->pathEdit->text()[i] == '/')
                break;
            if (ui->pathEdit->text()[i] == '.')
            {
                dotFlag = false;
                break;
            }
        }
        if (dotFlag)
        {
            QMessageBox::critical(this, "Error!", "Путь указан неверно!");
            return;
        }

        if (socket->isOpen())
        {
            //socket->write(QString("filesys:openfile$" + ui->pathEdit->text() + '$').toStdString().c_str());
            socket->write((char*)(QString("filesys:openfile$" + ui->pathEdit->text() + '$').toStdWString().c_str()), (QString("filesys:openfile$" + ui->pathEdit->text() + '$').size() * 2));
            socket->waitForBytesWritten(500);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
    case 4: // Удалить папку
        for (int i = 0; i < ui->pathEdit->text().size(); i++)
            if (ui->pathEdit->text()[i] == '.')
            {
                QMessageBox::critical(this, "Error!", "Путь указан неверно!");
                return;
            }

        if (socket->isOpen())
        {
            //socket->write(QString("filesys:mkdir$" + ui->pathEdit->text() + '$').toStdString().c_str());
            socket->write((char*)(QString("filesys:rmdir$" + ui->pathEdit->text() + '$').toStdWString().c_str()), (QString("filesys:mkdir$" + ui->pathEdit->text() + '$').size() * 2));
            socket->waitForBytesWritten(500);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    case 5: // Удалить файл
        bool dotFlag = true;
        for (int i = ui->pathEdit->text().size() - 1; i >= 0; i--)
        {
            if (ui->pathEdit->text()[i] == '/')
                break;
            if (ui->pathEdit->text()[i] == '.')
            {
                dotFlag = false;
                break;
            }
        }
        if (dotFlag)
        {
            QMessageBox::critical(this, "Error!", "Путь указан неверно!");
            return;
        }

        if (socket->isOpen())
        {
            //socket->write(QString("filesys:openfile$" + ui->pathEdit->text() + '$').toStdString().c_str());
            socket->write((char*)(QString("filesys:rmfile$" + ui->pathEdit->text() + '$').toStdWString().c_str()), (QString("filesys:openfile$" + ui->pathEdit->text() + '$').size() * 2));
            socket->waitForBytesWritten(500);
        }
        else
        {
            functionalityForm->show();
            this->hide();
            QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
        }
        this->setEnabled(false);
        break;
    }
}

void FileSystemForm::get_file_sys(QString str)
{
    ui->showDirWidget->clear();

    QStringList strList = str.split("/");

    for (QString tmp : strList)
    {
        if (tmp.isEmpty() || tmp == '.' || tmp == "..")
            continue;

        QListWidgetItem *itm = new QListWidgetItem(tmp);
        bool isDir = true;
        for (int i = 0; i < tmp.size(); i++)
            if (tmp[i] == '.')
            {
                isDir = false;
                break;
            }
        if (isDir)
            itm->setIcon(QIcon(":/folder.png"));
        else
            itm->setIcon(QIcon(":/file.png"));

        ui->showDirWidget->addItem(itm);
    }
}

void FileSystemForm::on_backButton_clicked()
{
    int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выйти из режима файловой системы ?", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    functionalityForm->show();
    this->hide();
}
