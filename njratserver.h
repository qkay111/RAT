#ifndef NJRATSERVER_H
#define NJRATSERVER_H

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

public:
    NjRatServer();
    ~NjRatServer();
    void close();   // Выключение сервера

public slots:
    void startServer(); // Запуск сервера
    void incomingConnection(int);  // Описание действий при присоединении клиента
    void socketReady(); // Готовность сокета считать полученные данные
    void socketDisc();  // Действия при отключении клиента
};

#endif // NJRATSERVER_H
