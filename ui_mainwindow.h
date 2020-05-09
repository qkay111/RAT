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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *usersTable;
    QAction *author;
    QAction *about;
    QAction *quit;
    QAction *run;
    QWidget *centralWidget;
    QLabel *logoLabel;
    QPushButton *connectButton;
    QLabel *waitingConnectionLabel;
    QPushButton *canselButton;
    QMenuBar *menuBar;
    QMenu *general;
    QMenu *details;

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
        usersTable = new QAction(MainWindow);
        usersTable->setObjectName(QStringLiteral("usersTable"));
        author = new QAction(MainWindow);
        author->setObjectName(QStringLiteral("author"));
        about = new QAction(MainWindow);
        about->setObjectName(QStringLiteral("about"));
        quit = new QAction(MainWindow);
        quit->setObjectName(QStringLiteral("quit"));
        run = new QAction(MainWindow);
        run->setObjectName(QStringLiteral("run"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        logoLabel = new QLabel(centralWidget);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        logoLabel->setGeometry(QRect(290, 100, 700, 250));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(465, 500, 350, 100));
        waitingConnectionLabel = new QLabel(centralWidget);
        waitingConnectionLabel->setObjectName(QStringLiteral("waitingConnectionLabel"));
        waitingConnectionLabel->setGeometry(QRect(290, 100, 700, 250));
        waitingConnectionLabel->setMinimumSize(QSize(700, 250));
        canselButton = new QPushButton(centralWidget);
        canselButton->setObjectName(QStringLiteral("canselButton"));
        canselButton->setGeometry(QRect(465, 500, 350, 100));
        canselButton->setMinimumSize(QSize(350, 100));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 25));
        general = new QMenu(menuBar);
        general->setObjectName(QStringLiteral("general"));
        details = new QMenu(menuBar);
        details->setObjectName(QStringLiteral("details"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(general->menuAction());
        menuBar->addAction(details->menuAction());
        general->addAction(run);
        general->addAction(usersTable);
        general->addSeparator();
        general->addAction(quit);
        details->addAction(author);
        details->addAction(about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        usersTable->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265\320\271", Q_NULLPTR));
        author->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\321\200", Q_NULLPTR));
        about->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", Q_NULLPTR));
        quit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
        run->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", Q_NULLPTR));
        logoLabel->setText(QApplication::translate("MainWindow", "njRAT - Server", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect...", Q_NULLPTR));
        waitingConnectionLabel->setText(QApplication::translate("MainWindow", "Waiting for a connection...", Q_NULLPTR));
        canselButton->setText(QApplication::translate("MainWindow", "Cancel", Q_NULLPTR));
        general->setTitle(QApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\265", Q_NULLPTR));
        details->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\264\321\200\320\276\320\261\320\275\320\265\320\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
