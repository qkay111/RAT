/********************************************************************************
** Form generated from reading UI file 'userstableform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSTABLEFORM_H
#define UI_USERSTABLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UsersTableForm
{
public:
    QListWidget *listWidget;
    QPushButton *aboutButton;
    QPushButton *addButton;
    QPushButton *changeButton;
    QPushButton *deleteButton;
    QPushButton *backButton;
    QPushButton *createButton;
    QPushButton *openButton;

    void setupUi(QWidget *UsersTableForm)
    {
        if (UsersTableForm->objectName().isEmpty())
            UsersTableForm->setObjectName(QStringLiteral("UsersTableForm"));
        UsersTableForm->resize(1200, 720);
        UsersTableForm->setMinimumSize(QSize(1200, 720));
        UsersTableForm->setSizeIncrement(QSize(1200, 720));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hacker.png"), QSize(), QIcon::Normal, QIcon::Off);
        UsersTableForm->setWindowIcon(icon);
        listWidget = new QListWidget(UsersTableForm);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(295, 0, 1005, 720));
        aboutButton = new QPushButton(UsersTableForm);
        aboutButton->setObjectName(QStringLiteral("aboutButton"));
        aboutButton->setGeometry(QRect(35, 90, 225, 75));
        addButton = new QPushButton(UsersTableForm);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(35, 180, 225, 75));
        changeButton = new QPushButton(UsersTableForm);
        changeButton->setObjectName(QStringLiteral("changeButton"));
        changeButton->setGeometry(QRect(35, 270, 225, 75));
        deleteButton = new QPushButton(UsersTableForm);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(35, 360, 225, 75));
        backButton = new QPushButton(UsersTableForm);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(35, 560, 225, 75));
        createButton = new QPushButton(UsersTableForm);
        createButton->setObjectName(QStringLiteral("createButton"));
        createButton->setGeometry(QRect(350, 340, 225, 75));
        openButton = new QPushButton(UsersTableForm);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(625, 340, 225, 75));

        retranslateUi(UsersTableForm);

        QMetaObject::connectSlotsByName(UsersTableForm);
    } // setupUi

    void retranslateUi(QWidget *UsersTableForm)
    {
        UsersTableForm->setWindowTitle(QApplication::translate("UsersTableForm", "Form", Q_NULLPTR));
        aboutButton->setText(QApplication::translate("UsersTableForm", "\320\237\320\276\320\264\321\200\320\276\320\261\320\275\320\265\320\265", Q_NULLPTR));
        addButton->setText(QApplication::translate("UsersTableForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        changeButton->setText(QApplication::translate("UsersTableForm", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("UsersTableForm", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        backButton->setText(QApplication::translate("UsersTableForm", "\320\235\320\260\320\267\320\260\320\264", Q_NULLPTR));
        createButton->setText(QApplication::translate("UsersTableForm", "Create", Q_NULLPTR));
        openButton->setText(QApplication::translate("UsersTableForm", "Open", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UsersTableForm: public Ui_UsersTableForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSTABLEFORM_H
