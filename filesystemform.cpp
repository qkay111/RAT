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
                                     "font-size: 20px;"
                                     "}");
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
}

FileSystemForm::~FileSystemForm()
{
    delete ui;
}

void FileSystemForm::get_functionalityForm(FunctionalityForm* mw, QTcpSocket* sk)
{
    functionalityForm = mw;
    socket = sk;
}

void FileSystemForm::on_acceptButton_clicked()
{
    switch (ui->actionBox->currentIndex())
    {
    case 0: // Войти
        if (socket->isOpen())
        {
            socket->write(QString("filesys:" + sPath + '$').toStdString().c_str());
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
        this->setEnabled(false);
        break;
    case 2: // Создать файл
        this->setEnabled(false);
        break;
    case 3: // Открыть файл
        this->setEnabled(false);
        break;
    case 4: // Скачать файл
        this->setEnabled(false);
        break;
    case 5: // Переместить (Переименовать)
        this->setEnabled(false);
        break;
    case 6: // Удалить
        this->setEnabled(false);
        break;
    }
}

void FileSystemForm::on_backButton_clicked()
{
    int result = QMessageBox::question(this, "Choice", "Вы уверены, что хотите выйти из режима файловой системы ?", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No)
        return;
    ui->showDirWidget->clear();
    ui->actionBox->setCurrentIndex(0);
    functionalityForm->show();
    this->hide();
}
