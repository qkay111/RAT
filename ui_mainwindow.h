/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *author;
    QAction *about;
    QAction *connect;
    QAction *quit;
    QWidget *centralWidget;
    QPushButton *connectButton;
    QPushButton *canselButton;
    QLabel *logoLabel;
    QLabel *ipLabel;
    QLineEdit *ipEdit;
    QPushButton *okButton;
    QPushButton *acceptButton;
    QPushButton *disconnectButton;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QLabel *loadSystemInfoLabel;
    QCheckBox *loadCheckBox;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1280, 720));
        MainWindow->setMaximumSize(QSize(1280, 720));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hacker.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        author = new QAction(MainWindow);
        author->setObjectName(QStringLiteral("author"));
        about = new QAction(MainWindow);
        about->setObjectName(QStringLiteral("about"));
        connect = new QAction(MainWindow);
        connect->setObjectName(QStringLiteral("connect"));
        quit = new QAction(MainWindow);
        quit->setObjectName(QStringLiteral("quit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(465, 500, 350, 100));
        canselButton = new QPushButton(centralWidget);
        canselButton->setObjectName(QStringLiteral("canselButton"));
        canselButton->setGeometry(QRect(680, 500, 350, 100));
        logoLabel = new QLabel(centralWidget);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        logoLabel->setGeometry(QRect(290, 100, 700, 250));
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setGeometry(QRect(290, 95, 700, 150));
        ipEdit = new QLineEdit(centralWidget);
        ipEdit->setObjectName(QStringLiteral("ipEdit"));
        ipEdit->setGeometry(QRect(290, 315, 700, 45));
        okButton = new QPushButton(centralWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(250, 500, 350, 100));
        acceptButton = new QPushButton(centralWidget);
        acceptButton->setObjectName(QStringLiteral("acceptButton"));
        acceptButton->setGeometry(QRect(250, 500, 350, 100));
        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));
        disconnectButton->setGeometry(QRect(680, 500, 350, 100));
        loginLabel = new QLabel(centralWidget);
        loginLabel->setObjectName(QStringLiteral("loginLabel"));
        loginLabel->setGeometry(QRect(250, 120, 200, 45));
        passwordLabel = new QLabel(centralWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(250, 220, 200, 45));
        loginEdit = new QLineEdit(centralWidget);
        loginEdit->setObjectName(QStringLiteral("loginEdit"));
        loginEdit->setGeometry(QRect(550, 120, 480, 45));
        passwordEdit = new QLineEdit(centralWidget);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setGeometry(QRect(550, 220, 480, 45));
        loadSystemInfoLabel = new QLabel(centralWidget);
        loadSystemInfoLabel->setObjectName(QStringLiteral("loadSystemInfoLabel"));
        loadSystemInfoLabel->setGeometry(QRect(250, 320, 300, 135));
        loadCheckBox = new QCheckBox(centralWidget);
        loadCheckBox->setObjectName(QStringLiteral("loadCheckBox"));
        loadCheckBox->setGeometry(QRect(650, 320, 250, 135));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 25));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(connect);
        menu->addSeparator();
        menu->addAction(quit);
        menu_2->addAction(author);
        menu_2->addAction(about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        author->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\321\200", Q_NULLPTR));
        about->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", Q_NULLPTR));
        connect->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", Q_NULLPTR));
        quit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect...", Q_NULLPTR));
        canselButton->setText(QApplication::translate("MainWindow", "Cansel", Q_NULLPTR));
        logoLabel->setText(QApplication::translate("MainWindow", "njRAT - Client", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 IP \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\260,\n"
"\320\272 \320\272\320\276\321\202\320\276\321\200\320\276\320\274\321\203 \321\205\320\276\321\202\320\270\321\202\320\265 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 :", Q_NULLPTR));
        okButton->setText(QApplication::translate("MainWindow", "Ok", Q_NULLPTR));
        acceptButton->setText(QApplication::translate("MainWindow", "Accept", Q_NULLPTR));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        loginLabel->setText(QApplication::translate("MainWindow", "\320\233\320\276\320\263\320\270\320\275:", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\276\320\273\321\214:", Q_NULLPTR));
        loadSystemInfoLabel->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214\n"
"\321\201\320\270\321\201\321\202\320\265\320\274\320\275\321\203\321\216\n"
"\320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\216", Q_NULLPTR));
        loadCheckBox->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\265", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\264\321\200\320\276\320\261\320\275\320\265\320\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
