#include "screensharingform.h"
#include "ui_screensharingform.h"

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

void ScreenSharingForm::get_functionalityForm(FunctionalityForm *mw, QTcpSocket *sk)
{
    functionalityForm = mw;
    socket = sk;
    sharingPermission = true;

    ui->screenshotSharingLabel->clear();
    ui->screenshotSharingLabel->setText("Wait the screen share...");

    // temporary
    sendQuery();
}

void ScreenSharingForm::on_backButton_clicked()
{
    sharingPermission = false;
    functionalityForm->show();
    this->hide();
}

void ScreenSharingForm::sendQuery()
{
    if (socket->isOpen())
    {
        socket->write(QString("screen:share$").toStdString().c_str());
        socket->waitForBytesWritten(500);
    }
    else
    {
        functionalityForm->show();
        this->hide();
        QMessageBox::critical(this, "Error!", "Loss of connection to the server!");
    }
}

void ScreenSharingForm::get_screenshot_for_sharing(QPixmap *screenshot)
{
    int w = ui->screenshotSharingLabel->width();
    int h = ui->screenshotSharingLabel->height();
    ui->screenshotSharingLabel->clear();
    ui->screenshotSharingLabel->setPixmap(screenshot->scaled(w, h, Qt::KeepAspectRatio));  // Установка картинки
    ui->screenshotSharingLabel->setStyleSheet("background: none;");

    // temporary
    sendQuery();
}
