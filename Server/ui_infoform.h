/********************************************************************************
** Form generated from reading UI file 'infoform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOFORM_H
#define UI_INFOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoForm
{
public:
    QLabel *userAv;
    QLabel *nicknameLabel;
    QLabel *passwordLabel;
    QLabel *repPasswordLabel;
    QPushButton *avButton;
    QCheckBox *fileSystemBox;
    QCheckBox *screenShareBox;
    QCheckBox *systemOpBox;
    QLineEdit *nicknameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *repPasswordEdit;
    QPushButton *acceptButton;
    QPushButton *backButton;

    void setupUi(QWidget *InfoForm)
    {
        if (InfoForm->objectName().isEmpty())
            InfoForm->setObjectName(QStringLiteral("InfoForm"));
        InfoForm->resize(1200, 720);
        InfoForm->setMinimumSize(QSize(1200, 720));
        InfoForm->setMaximumSize(QSize(1200, 720));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hacker.png"), QSize(), QIcon::Normal, QIcon::Off);
        InfoForm->setWindowIcon(icon);
        userAv = new QLabel(InfoForm);
        userAv->setObjectName(QStringLiteral("userAv"));
        userAv->setGeometry(QRect(25, 25, 200, 200));
        nicknameLabel = new QLabel(InfoForm);
        nicknameLabel->setObjectName(QStringLiteral("nicknameLabel"));
        nicknameLabel->setGeometry(QRect(300, 50, 200, 50));
        passwordLabel = new QLabel(InfoForm);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(300, 150, 200, 50));
        repPasswordLabel = new QLabel(InfoForm);
        repPasswordLabel->setObjectName(QStringLiteral("repPasswordLabel"));
        repPasswordLabel->setGeometry(QRect(300, 250, 200, 50));
        avButton = new QPushButton(InfoForm);
        avButton->setObjectName(QStringLiteral("avButton"));
        avButton->setGeometry(QRect(25, 275, 225, 75));
        fileSystemBox = new QCheckBox(InfoForm);
        fileSystemBox->setObjectName(QStringLiteral("fileSystemBox"));
        fileSystemBox->setGeometry(QRect(300, 350, 350, 50));
        screenShareBox = new QCheckBox(InfoForm);
        screenShareBox->setObjectName(QStringLiteral("screenShareBox"));
        screenShareBox->setGeometry(QRect(300, 450, 350, 50));
        systemOpBox = new QCheckBox(InfoForm);
        systemOpBox->setObjectName(QStringLiteral("systemOpBox"));
        systemOpBox->setGeometry(QRect(300, 550, 350, 50));
        nicknameEdit = new QLineEdit(InfoForm);
        nicknameEdit->setObjectName(QStringLiteral("nicknameEdit"));
        nicknameEdit->setGeometry(QRect(550, 50, 625, 50));
        passwordEdit = new QLineEdit(InfoForm);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setGeometry(QRect(550, 150, 625, 50));
        repPasswordEdit = new QLineEdit(InfoForm);
        repPasswordEdit->setObjectName(QStringLiteral("repPasswordEdit"));
        repPasswordEdit->setGeometry(QRect(550, 250, 625, 50));
        acceptButton = new QPushButton(InfoForm);
        acceptButton->setObjectName(QStringLiteral("acceptButton"));
        acceptButton->setGeometry(QRect(25, 500, 225, 75));
        backButton = new QPushButton(InfoForm);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(25, 600, 225, 75));

        retranslateUi(InfoForm);

        QMetaObject::connectSlotsByName(InfoForm);
    } // setupUi

    void retranslateUi(QWidget *InfoForm)
    {
        InfoForm->setWindowTitle(QApplication::translate("InfoForm", "Form", Q_NULLPTR));
        userAv->setText(QApplication::translate("InfoForm", "TextLabel", Q_NULLPTR));
        nicknameLabel->setText(QApplication::translate("InfoForm", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("InfoForm", "\320\237\320\260\321\200\320\276\320\273\321\214", Q_NULLPTR));
        repPasswordLabel->setText(QApplication::translate("InfoForm", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", Q_NULLPTR));
        avButton->setText(QApplication::translate("InfoForm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        fileSystemBox->setText(QApplication::translate("InfoForm", "\320\244\320\260\320\271\320\273\320\276\320\262\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260", Q_NULLPTR));
        screenShareBox->setText(QApplication::translate("InfoForm", "\320\242\321\200\320\260\320\275\321\201\320\273\321\217\321\206\320\270\321\217 \321\215\320\272\321\200\320\260\320\275\320\260", Q_NULLPTR));
        systemOpBox->setText(QApplication::translate("InfoForm", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\321\213\320\265 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\270", Q_NULLPTR));
        acceptButton->setText(QApplication::translate("InfoForm", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", Q_NULLPTR));
        backButton->setText(QApplication::translate("InfoForm", "\320\235\320\260\320\267\320\260\320\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InfoForm: public Ui_InfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOFORM_H
