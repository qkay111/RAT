#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "functionalityform.h"
#include <QMainWindow>
#include <QString>
#include <QTcpSocket>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    send_mainWindow(QMainWindow*);  // Передать главное окно
    send_user_info(QTcpSocket*, const char*, QString, QString); // Передать информацию о пользователе
    send_screenshot_for_sharing(QPixmap*);  // Отправка скриншота
    enable_file_system();
    void send_file_sys(QString);
    void hide_all();

private slots:
    void on_author_triggered();
    void on_connectButton_clicked();
    void on_canselButton_clicked();
    void on_connect_triggered();
    void on_okButton_clicked();
    void on_quit_triggered();
    void on_acceptButton_clicked();
    void on_disconnectButton_clicked();

public slots:
    void socketReady(); // Готовность читать данные от сервера
    void socketDisc();  // Отключение от сервера

private:
    Ui::MainWindow *ui;
    FunctionalityForm* functionalityForm;
    QTcpSocket* socket;
    QByteArray bufferData;
    char permissions[3];

    void beginUi();
    void ipEnterUi();
    void vereficationUi();
    bool ipValidation(QString);
};

#endif // MAINWINDOW_H
