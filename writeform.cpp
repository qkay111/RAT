#include "writeform.h"
#include "ui_writeform.h"

WriteForm::WriteForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteForm)
{
    ui->setupUi(this);
}

WriteForm::WriteForm(FunctionalityForm* mw, int typeOp, QTcpSocket* sk, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteForm)
{
    ui->setupUi(this);

    mainWindow = mw;
    type = typeOp;
    socket = sk;

    setWindowTitle("Ввод");
    this->setWindowFlags(Qt::FramelessWindowHint);  // чтобы не было Windows bar'a

    ui->label->setAlignment(Qt::AlignCenter);

    switch (type)
    {
    case WRITE_MESSAGE:
    {
        ui->label->setText("Введите сообщение:");
        QRegExp validator("[A-Za-z0-9!?.,+*/_ ]{1,30}");
        ui->lineEdit->setValidator(new QRegExpValidator(validator, this));
        break;
    }
    case CHANGE_TIME:
    {
        ui->label->setText("Введите время:\n(Формат чч:мм:сс)");
        QRegExp validator("[2]{1}[0-3]{1}[:]{1}[0-5]{1}[0-9]{1}[:]{1}[0-5]{1}[0-9]{1}|"
                          "[0-1]{1}[0-9]{1}[:]{1}"
                          "[0-5]{1}[0-9]{1}[:]{1}"
                          "[0-5]{1}[0-9]{1}");
        ui->lineEdit->setValidator(new QRegExpValidator(validator, this));
        break;
    }
    case CHANGE_DATE:
    {
        ui->label->setText("Введите дату:\n(Формат дд.мм.гггг)");
        QRegExp validator("([3]{1}[0-1]{1}|[0]{1}[1-9]{1}|[1-2]{1}[0-9]{1})[.]{1}"
                          "([0]{1}[1-9]{1}|[1]{1}[0-2]{1})[.]{1}"
                          "[0-9]{1}[0-9]{1}[0-9]{1}[0-9]{1}");
        ui->lineEdit->setValidator(new QRegExpValidator(validator, this));
        break;
    }
    }
}

WriteForm::~WriteForm()
{
    delete ui;
}

void WriteForm::on_acceptButton_clicked()
{
    if (cmd.isEmpty())
    {
        QMessageBox::critical(this, "Error!", "Данные введены некорректно!");
        return;
    }

    switch (type)
    {
    case WRITE_MESSAGE:
        socket->write(("message:" + cmd + '$').toStdString().c_str());
        socket->waitForBytesWritten(500);
        break;
    case CHANGE_TIME:
        socket->write(("command:" + ("nfile$time " + cmd) + '$').toStdString().c_str());
        socket->waitForBytesWritten(500);
        break;
    case CHANGE_DATE:
    {
        QVector<int> value;
        QStringList valueList = cmd.split(".");

        for (QString var : valueList)
            value.push_back(var.toInt());

        if ((value[0] == 31 && (value[1] == 2 || value[1] == 4 || value[1] == 6 || value[1] == 9 || value[1] == 11)) ||
            (value[0] > 28 && value[1] == 2) || value[2] < 1951 || value[2] > 2150)
        {
            QMessageBox::critical(this, "Error!", "Данные введены некорректно!");
            return;
        }

        socket->write(("command:" + ("nfile$date " + cmd) + '$').toStdString().c_str());
        socket->waitForBytesWritten(500);
        break;
    }
    }

    mainWindow->show();
    this->hide();
}

void WriteForm::on_backButton_clicked()
{
    mainWindow->show();
    mainWindow->setEnabled(true);
    this->hide();
}

void WriteForm::on_lineEdit_editingFinished()
{
    cmd = ui->lineEdit->text();
}
