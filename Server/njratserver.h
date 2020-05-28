#ifndef NJRATSERVER_H
#define NJRATSERVER_H

#include "slogger.h"
#include "userinfo.h"
#include "userlist.h"
#include <QTcpServer>
#include <QTcpSocket>

#define SERVER_PORT 12345
#define CLIENT_PORT 17325

class NjRatServer : public QTcpServer
{
    Q_OBJECT

private:
    QByteArray bufferData;
    QTcpSocket* socket;
    bool state;
    UserList<userInfo, QString>* userList;
    sLogger* logger;

signals:
    void send_user_info(QString, QString*);
    void waiting_for_connection();
    void send_start_ui();

public:
    NjRatServer();
    ~NjRatServer();
    void close();   // Выключение сервера

public slots:
    void startServer(UserList<userInfo, QString>*); // Запуск сервера
    void incomingConnection(int);  // Описание действий при присоединении клиента
    void socketReady(); // Готовность сокета считать полученные данные
    void socketDisc();  // Действия при отключении клиента
    void set_sLogger(QString);  // Передать путь для лог-файла
};

#endif // NJRATSERVER_H
