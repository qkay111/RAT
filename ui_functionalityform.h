/********************************************************************************
** Form generated from reading UI file 'functionalityform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONALITYFORM_H
#define UI_FUNCTIONALITYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FunctionalityForm
{
public:
    QLabel *enteredAsLabel;
    QLabel *userAvLabel;
    QPushButton *userInfoButton;
    QPushButton *exitButton;
    QLabel *systemActionsLabel;
    QPushButton *fileSystemButton;
    QPushButton *screenShareButton;
    QComboBox *systemComboBox;
    QPushButton *runButton;
    QLabel *systemInfoLabel;
    QTextEdit *systemInfoEdit;

    void setupUi(QWidget *FunctionalityForm)
    {
        if (FunctionalityForm->objectName().isEmpty())
            FunctionalityForm->setObjectName(QStringLiteral("FunctionalityForm"));
        FunctionalityForm->resize(1600, 900);
        FunctionalityForm->setMinimumSize(QSize(1600, 900));
        FunctionalityForm->setMaximumSize(QSize(1600, 900));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hacker.png"), QSize(), QIcon::Normal, QIcon::Off);
        FunctionalityForm->setWindowIcon(icon);
        enteredAsLabel = new QLabel(FunctionalityForm);
        enteredAsLabel->setObjectName(QStringLiteral("enteredAsLabel"));
        enteredAsLabel->setGeometry(QRect(50, 60, 490, 51));
        userAvLabel = new QLabel(FunctionalityForm);
        userAvLabel->setObjectName(QStringLiteral("userAvLabel"));
        userAvLabel->setGeometry(QRect(590, 60, 50, 50));
        userInfoButton = new QPushButton(FunctionalityForm);
        userInfoButton->setObjectName(QStringLiteral("userInfoButton"));
        userInfoButton->setGeometry(QRect(670, 60, 50, 50));
        exitButton = new QPushButton(FunctionalityForm);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(750, 60, 50, 50));
        systemActionsLabel = new QLabel(FunctionalityForm);
        systemActionsLabel->setObjectName(QStringLiteral("systemActionsLabel"));
        systemActionsLabel->setGeometry(QRect(50, 520, 490, 80));
        fileSystemButton = new QPushButton(FunctionalityForm);
        fileSystemButton->setObjectName(QStringLiteral("fileSystemButton"));
        fileSystemButton->setGeometry(QRect(50, 190, 490, 120));
        screenShareButton = new QPushButton(FunctionalityForm);
        screenShareButton->setObjectName(QStringLiteral("screenShareButton"));
        screenShareButton->setGeometry(QRect(50, 340, 490, 120));
        systemComboBox = new QComboBox(FunctionalityForm);
        systemComboBox->setObjectName(QStringLiteral("systemComboBox"));
        systemComboBox->setGeometry(QRect(50, 630, 490, 80));
        runButton = new QPushButton(FunctionalityForm);
        runButton->setObjectName(QStringLiteral("runButton"));
        runButton->setGeometry(QRect(50, 740, 490, 120));
        systemInfoLabel = new QLabel(FunctionalityForm);
        systemInfoLabel->setObjectName(QStringLiteral("systemInfoLabel"));
        systemInfoLabel->setGeometry(QRect(590, 190, 960, 120));
        systemInfoEdit = new QTextEdit(FunctionalityForm);
        systemInfoEdit->setObjectName(QStringLiteral("systemInfoEdit"));
        systemInfoEdit->setGeometry(QRect(590, 340, 960, 520));

        retranslateUi(FunctionalityForm);

        QMetaObject::connectSlotsByName(FunctionalityForm);
    } // setupUi

    void retranslateUi(QWidget *FunctionalityForm)
    {
        FunctionalityForm->setWindowTitle(QApplication::translate("FunctionalityForm", "Form", Q_NULLPTR));
        enteredAsLabel->setText(QApplication::translate("FunctionalityForm", "\320\222\321\213 \320\262\320\276\321\210\320\273\320\270 \320\272\320\260\320\272: ", Q_NULLPTR));
        userAvLabel->setText(QApplication::translate("FunctionalityForm", "Avatar", Q_NULLPTR));
        userInfoButton->setText(QApplication::translate("FunctionalityForm", "?", Q_NULLPTR));
        exitButton->setText(QApplication::translate("FunctionalityForm", "X", Q_NULLPTR));
        systemActionsLabel->setText(QApplication::translate("FunctionalityForm", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\321\213\320\265 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\270", Q_NULLPTR));
        fileSystemButton->setText(QApplication::translate("FunctionalityForm", "\320\240\320\260\320\261\320\276\321\202\320\260\321\202\321\214 \321\201 \321\204\320\260\320\271\320\273\320\276\320\262\320\276\320\271\n"
"\321\201\320\270\321\201\321\202\320\265\320\274\320\276\320\271", Q_NULLPTR));
        screenShareButton->setText(QApplication::translate("FunctionalityForm", "\320\242\321\200\320\260\320\275\321\201\320\273\321\217\321\206\320\270\321\217 \321\215\320\272\321\200\320\260\320\275\320\260", Q_NULLPTR));
        systemComboBox->clear();
        systemComboBox->insertItems(0, QStringList()
         << QApplication::translate("FunctionalityForm", "1. \320\222\321\213\320\267\320\262\320\260\321\202\321\214 \321\201\320\270\321\201\321\202\320\265\320\274\320\275\320\276\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "2. \320\222\321\213\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "3. \320\237\320\265\321\200\320\265\320\267\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "4. \320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\201\320\270\321\201\321\202\320\265\320\274\320\275\321\203\321\216 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\216", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "5. \320\222\320\265\321\200\321\201\320\270\321\217 Windows", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "6. \320\241\320\270\321\201\321\202\320\265\320\274\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "7. \320\224\320\260\321\202\320\260", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "8. \320\247\320\260\321\201\320\276\320\262\320\276\320\271 \320\277\320\276\321\217\321\201", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "9. \320\240\320\265\320\266\320\270\320\274 \320\263\320\270\320\261\320\265\321\200\320\275\320\260\321\206\320\270\320\270", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "10. \320\240\320\265\320\266\320\270\320\274 \321\201\320\275\320\260", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "11. \320\227\320\260\320\261\320\273\320\276\320\272\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "12. \320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\262\321\200\320\265\320\274\321\217", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "13. \320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "14. \320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\272\321\203\321\200\321\201\320\276\321\200\320\260", Q_NULLPTR)
         << QApplication::translate("FunctionalityForm", "15. \320\241\320\264\320\265\320\273\320\260\321\202\321\214 \321\201\320\272\321\200\320\270\320\275\321\210\320\276\321\202", Q_NULLPTR)
        );
        runButton->setText(QApplication::translate("FunctionalityForm", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", Q_NULLPTR));
        systemInfoLabel->setText(QApplication::translate("FunctionalityForm", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276\320\261 \321\203\320\277\321\200\320\260\320\262\320\273\321\217\320\265\320\274\320\276\320\274\n"
"\320\277\320\265\321\200\321\201\320\276\320\275\320\260\320\273\321\214\320\275\320\276\320\274 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FunctionalityForm: public Ui_FunctionalityForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONALITYFORM_H
