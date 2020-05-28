#ifndef INFOFORM_H
#define INFOFORM_H

#include "userinfo.h"
#include "userstableform.h"
#include <QWidget>

class UsersTableForm;

namespace Ui {
    class InfoForm;
}

class InfoForm : public QWidget
{
    Q_OBJECT

public slots:
    void get_window_for_back(UsersTableForm*);

public:
    explicit InfoForm(QWidget *parent = 0);
    ~InfoForm();

signals:
    void send_new_user(userInfo*, QString*);
    void send_changed_user(userInfo*, QString*);

public slots:
    void get_ptr_i_for_view(UsersTableForm*, userInfo*, QString*);
    void get_ptr_i_for_change(UsersTableForm*, userInfo*, QString*);
    void existing_name();

private slots:
    void on_backButton_clicked();
    void on_avButton_clicked();
    void on_nicknameEdit_editingFinished();
    void on_passwordEdit_cursorPositionChanged(int arg1, int arg2);
    void on_repPasswordEdit_editingFinished();
    void on_passwordEdit_editingFinished();
    void on_acceptButton_clicked();

private:
    Ui::InfoForm *ui;
    UsersTableForm* usersTableForm;
    userInfo* ptr;
    QString* ptr_i;
    bool changeMode;
    bool allOk;
};

#endif // INFOFORM_H
