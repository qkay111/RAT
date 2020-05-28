#ifndef WRITEFORM_H
#define WRITEFORM_H

#include "functionalityform.h"
#include <QTcpSocket>
#include <QWidget>

#define WRITE_MESSAGE 0
#define CHANGE_TIME 1
#define CHANGE_DATE 2

class FunctionalityForm;

namespace Ui {
    class WriteForm;
}

class WriteForm : public QWidget
{
    Q_OBJECT

public:
    explicit WriteForm(QWidget *parent = 0);
    explicit WriteForm(FunctionalityForm*, int, QTcpSocket*, QWidget *parent = 0);
    ~WriteForm();

private slots:
    void on_acceptButton_clicked();

    void on_backButton_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::WriteForm *ui;
    FunctionalityForm* mainWindow;
    int type;
    QTcpSocket* socket;
    QString cmd;
};

#endif // WRITEFORM_H
