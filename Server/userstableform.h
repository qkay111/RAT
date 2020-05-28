#ifndef USERSTABLEFORM_H
#define USERSTABLEFORM_H

#include "infoform.h"
#include "userinfo.h"
#include "userlist.h"
#include <QMainWindow>
#include <QWidget>

class InfoForm;

namespace Ui {
    class UsersTableForm;
}

class UsersTableForm : public QWidget
{
    Q_OBJECT

signals:
    void send_window_for_info_form(UsersTableForm*);
    void send_window_for_info_form_for_view(UsersTableForm*, userInfo*, QString*);
    void send_window_for_info_form_for_change(UsersTableForm*, userInfo*, QString*);
    void existing_name();

public slots:
    void get_main_window(QMainWindow*);
    void get_new_user(userInfo*, QString*);
    void get_changed_user(userInfo*, QString*);

public:
    explicit UsersTableForm(QWidget *parent = 0);
    ~UsersTableForm();

private slots:
    void on_backButton_clicked();
    void on_createButton_clicked();
    void on_openButton_clicked();
    void on_aboutButton_clicked();
    void on_addButton_clicked();
    void on_changeButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::UsersTableForm *ui;
    QMainWindow* mainWindow;
    InfoForm* infoForm;
    UserList<userInfo, QString> userList;

    void saveFile();
};

#endif // USERSTABLEFORM_H
