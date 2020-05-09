/********************************************************************************
** Form generated from reading UI file 'screensharingform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHARINGFORM_H
#define UI_SCREENSHARINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenSharingForm
{
public:
    QLabel *screenshotSharingLabel;
    QPushButton *backButton;

    void setupUi(QWidget *ScreenSharingForm)
    {
        if (ScreenSharingForm->objectName().isEmpty())
            ScreenSharingForm->setObjectName(QStringLiteral("ScreenSharingForm"));
        ScreenSharingForm->resize(1600, 900);
        ScreenSharingForm->setMinimumSize(QSize(1600, 900));
        ScreenSharingForm->setMaximumSize(QSize(1600, 900));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hacker.png"), QSize(), QIcon::Normal, QIcon::Off);
        ScreenSharingForm->setWindowIcon(icon);
        screenshotSharingLabel = new QLabel(ScreenSharingForm);
        screenshotSharingLabel->setObjectName(QStringLiteral("screenshotSharingLabel"));
        screenshotSharingLabel->setGeometry(QRect(0, 0, 1600, 900));
        backButton = new QPushButton(ScreenSharingForm);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(425, 750, 750, 100));

        retranslateUi(ScreenSharingForm);

        QMetaObject::connectSlotsByName(ScreenSharingForm);
    } // setupUi

    void retranslateUi(QWidget *ScreenSharingForm)
    {
        ScreenSharingForm->setWindowTitle(QApplication::translate("ScreenSharingForm", "Form", Q_NULLPTR));
        screenshotSharingLabel->setText(QString());
        backButton->setText(QApplication::translate("ScreenSharingForm", "\320\237\321\200\320\265\320\272\321\200\320\260\321\202\320\270\321\202\321\214 \321\202\321\200\320\260\320\275\321\201\320\273\321\217\321\206\320\270\321\216 \321\215\320\272\321\200\320\260\320\275\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScreenSharingForm: public Ui_ScreenSharingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHARINGFORM_H
