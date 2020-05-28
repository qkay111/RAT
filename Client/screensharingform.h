#ifndef SCREENSHARINGFORM_H
#define SCREENSHARINGFORM_H

#include "functionalityform.h"
#include <QTcpSocket>
#include <QWidget>

class FunctionalityForm;

namespace Ui {
    class ScreenSharingForm;
}

class ScreenSharingForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenSharingForm(QWidget *parent = 0);
    ~ScreenSharingForm();

public slots:
    void get_functionalityForm(FunctionalityForm*, QTcpSocket*);  // Получение главного окна
    void get_screenshot_for_sharing(QPixmap*);  // Получить скриншот

private:
    Ui::ScreenSharingForm *ui;
    FunctionalityForm* functionalityForm;
    QTcpSocket* socket;
    void sendQuery();
};

#endif // SCREENSHARINGFORM_H
