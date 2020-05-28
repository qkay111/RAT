#ifndef FILESYSTEMFORM_H
#define FILESYSTEMFORM_H

#include "functionalityform.h"
#include <QTcpSocket>
#include <QWidget>

class FunctionalityForm;

namespace Ui {
    class FileSystemForm;
}

class FileSystemForm : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystemForm(QWidget *parent = 0);
    ~FileSystemForm();

public slots:
    void get_functionalityForm(FunctionalityForm*, QTcpSocket*);  // Получение главного окна

private slots:
    void on_acceptButton_clicked();
    void on_backButton_clicked();
    void get_file_sys(QString);

private:
    Ui::FileSystemForm *ui;
    FunctionalityForm* functionalityForm;
    QTcpSocket* socket;
};

#endif // FILESYSTEMFORM_H
