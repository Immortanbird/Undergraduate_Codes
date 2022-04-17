#ifndef MYUSER_H
#define MYUSER_H
#include <QTcpSocket>
#include <QString>

class MyUser
{
public:
    MyUser();
    QTcpSocket *socket;
    QString name;
};

#endif // MYUSER_H


//log_in_ok
//log_in_fail

//sign_in_ok
//sign_in_fail

//connect_friend
//no_friend_name
//firend_no_connection

//NAME【】message
//message_send
//no_connection


