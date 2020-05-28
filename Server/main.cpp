#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Подключение общих стилей
    QFile styleFile(":/style.css");
    styleFile.open(QFile::ReadOnly);
    app.setStyleSheet(styleFile.readAll());
    // .Подключение общих стилей

    MainWindow mainWindow;  // создаём главное окно
    mainWindow.show();  // вызываем главное окно

    return app.exec();
}
