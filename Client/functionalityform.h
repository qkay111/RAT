#ifndef FUNCTIONALITYFORM_H
#define FUNCTIONALITYFORM_H

#include "filesystemform.h"
#include "screensharingform.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QTcpSocket>
#include <QWidget>

class FileSystemForm;
class ScreenSharingForm;

namespace Ui {
    class FunctionalityForm;
}

class FunctionalityForm : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionalityForm(QWidget *parent = 0);
    ~FunctionalityForm();

public slots:
    void get_mainWindow(QMainWindow*);  // Получение главного окна
    void get_user_info(QTcpSocket*, const char*, QString, QString);   // Получение всей информации о пользователе
    void get_screenshot(QPixmap*);
    void get_enable_file_system();
    void get_file_sys(QString);
    void get_hide_all();

private slots:
    void on_userInfoButton_clicked();
    void on_exitButton_clicked();
    void on_fileSystemButton_clicked();
    void on_screenShareButton_clicked();
    void on_runButton_clicked();

signals:
    send_functionalityForm(FunctionalityForm*, QTcpSocket*);  // Передать главное окно
    send_functionalityForm_for_sharing(FunctionalityForm*, QTcpSocket*);    // Передать главное окно
    send_screenshot_for_sharing(QPixmap*);  // Отправка скриншота
    send_file_sys(QString);
    user_disc();

private:
    Ui::FunctionalityForm *ui;
    QMainWindow* mainWindow;
    FileSystemForm* fileSystemForm;
    ScreenSharingForm* screenSharingForm;
    QTcpSocket* socket;
    char userPermissions[3];
    QString uName;
    void sendAction(QString);
};

#endif // FUNCTIONALITYFORM_H
