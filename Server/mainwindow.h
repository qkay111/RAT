#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "njratserver.h"
#include "userinfo.h"
#include "userlist.h"
#include "userstableform.h"
#include <QMainWindow>

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
    void send_main_window_for_user_window(QMainWindow*);
    void send_sLogger(QString);

public slots:
    void set_active_user(QString, QString*);
    void get_waiting_for_connection();
    void start_ui();

private slots:
    void on_run_triggered();
    void on_author_triggered();
    void on_connectButton_clicked();
    void on_canselButton_clicked();
    void on_quit_triggered();
    void on_usersTable_triggered();

private:
    Ui::MainWindow *ui;
    UsersTableForm* usersTableForm;
    NjRatServer server;
    UserList<userInfo, QString> userList;
};

#endif // MAINWINDOW_H
