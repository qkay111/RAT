/********************************************************************************
** Form generated from reading UI file 'filesystemform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESYSTEMFORM_H
#define UI_FILESYSTEMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSystemForm
{
public:
    QPushButton *backButton;
    QPushButton *acceptButton;
    QComboBox *actionBox;
    QListWidget *showDirWidget;
    QLabel *pathLabel;
    QLineEdit *pathEdit;

    void setupUi(QWidget *FileSystemForm)
    {
        if (FileSystemForm->objectName().isEmpty())
            FileSystemForm->setObjectName(QStringLiteral("FileSystemForm"));
        FileSystemForm->resize(1600, 900);
        FileSystemForm->setMinimumSize(QSize(1600, 900));
        FileSystemForm->setMaximumSize(QSize(1600, 900));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hacker.png"), QSize(), QIcon::Normal, QIcon::Off);
        FileSystemForm->setWindowIcon(icon);
        backButton = new QPushButton(FileSystemForm);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(1510, 800, 60, 60));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon1);
        backButton->setIconSize(QSize(60, 60));
        acceptButton = new QPushButton(FileSystemForm);
        acceptButton->setObjectName(QStringLiteral("acceptButton"));
        acceptButton->setGeometry(QRect(1400, 800, 60, 60));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/tick.png"), QSize(), QIcon::Normal, QIcon::Off);
        acceptButton->setIcon(icon2);
        acceptButton->setIconSize(QSize(60, 60));
        actionBox = new QComboBox(FileSystemForm);
        actionBox->setObjectName(QStringLiteral("actionBox"));
        actionBox->setGeometry(QRect(30, 800, 1320, 60));
        showDirWidget = new QListWidget(FileSystemForm);
        showDirWidget->setObjectName(QStringLiteral("showDirWidget"));
        showDirWidget->setGeometry(QRect(30, 30, 1540, 590));
        pathLabel = new QLabel(FileSystemForm);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        pathLabel->setGeometry(QRect(30, 650, 1540, 60));
        pathEdit = new QLineEdit(FileSystemForm);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));
        pathEdit->setGeometry(QRect(30, 720, 1540, 60));

        retranslateUi(FileSystemForm);

        QMetaObject::connectSlotsByName(FileSystemForm);
    } // setupUi

    void retranslateUi(QWidget *FileSystemForm)
    {
        FileSystemForm->setWindowTitle(QApplication::translate("FileSystemForm", "Form", Q_NULLPTR));
        backButton->setText(QString());
        acceptButton->setText(QString());
        actionBox->clear();
        actionBox->insertItems(0, QStringList()
         << QApplication::translate("FileSystemForm", "\320\222\320\276\320\271\321\202\320\270", Q_NULLPTR)
         << QApplication::translate("FileSystemForm", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", Q_NULLPTR)
         << QApplication::translate("FileSystemForm", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", Q_NULLPTR)
         << QApplication::translate("FileSystemForm", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", Q_NULLPTR)
         << QApplication::translate("FileSystemForm", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", Q_NULLPTR)
         << QApplication::translate("FileSystemForm", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", Q_NULLPTR)
        );
        pathLabel->setText(QApplication::translate("FileSystemForm", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\277\321\203\321\202\321\214:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FileSystemForm: public Ui_FileSystemForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESYSTEMFORM_H
