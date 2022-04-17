#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QStringList>
#include <QHostAddress>
#include <QHostInfo>
#include <myuser.h>
#include <mysql.h>


class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    static MyTCPServer* gethand(){
        if(tcpserverhand == nullptr){
            tcpserverhand=new MyTCPServer();
        }
        return tcpserverhand;
    }
    void openTCPserver(QString ip,QString port);
    void stopServer();
private:
    explicit MyTCPServer(QObject *parent = nullptr);
    static MyTCPServer* tcpserverhand;
    QTcpServer tcp_server;
    QTcpSocket *tcp_socket;
    QHostInfo hostinfo;
    QList<QHostAddress> hostaddlist;
    QList <MyUser> userlist;
    QList <QTcpSocket*> socketlist;
    QByteArray buffer;
    MySql db;
private slots:
    void slot_getaddress(QHostInfo info);
    void slot_readdate();
    void slot_mycreatNewConnect();
signals:
    void sig_serverStartListening();
    void sig_getipaddresses(QHostInfo info);
};

#endif // MYTCPSERVER_H
