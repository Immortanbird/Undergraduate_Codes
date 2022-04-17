#include "mytcpserver.h"



MyTCPServer* MyTCPServer::tcpserverhand = nullptr;
MyTCPServer::MyTCPServer(QObject *parent) : QObject(parent)
{
    qDebug()<<"This Pc name is :"<<hostinfo.localHostName();
    hostinfo.setHostName(hostinfo.localHostName());
    QHostInfo::lookupHost(hostinfo.localHostName(),this,SLOT(slot_getaddress(QHostInfo)));
}



void MyTCPServer::slot_getaddress(QHostInfo info){
    emit sig_getipaddresses(info);
}


void MyTCPServer::stopServer(){
    tcp_server.close();
}

void MyTCPServer::openTCPserver(QString ip,QString port){
    qDebug()<<"IP: "<<ip<<" port: "<<port.toInt();
    QHostAddress IP;
    IP.setAddress(ip);
    if(tcp_server.listen(IP,port.toInt())){
        emit sig_serverStartListening();    //如果监听成功则发送信号
        connect(&tcp_server,SIGNAL(newConnection()),this,SLOT(slot_mycreatNewConnect()));
    }
    else{
         qDebug()<<"Server can not listening";
    }
}



    void MyTCPServer::slot_mycreatNewConnect(){
        tcp_socket = tcp_server.nextPendingConnection();
        socketlist.append(tcp_socket);
        //tcp_socket=qobject_cast<QTcpSocket *>(sender());
        connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(slot_readdate()));
    }


    void MyTCPServer::slot_readdate(){
        //qDebug()<<"客户端IP："<<tcp_socket->peerAddress()<<"port:"<<tcp_socket->peerPort();
        foreach(QTcpSocket* socket, socketlist) {
            if(!(socket->state()==QAbstractSocket::ConnectedState)){
                socketlist.removeOne(socket);
                continue;
            }
            QByteArray buffer1 = socket->readAll();
            if(buffer1.isEmpty())    continue;
            else{
                tcp_socket=socket;
                buffer = buffer1;
                break;
            }
        }
        QString message = QString::fromStdString(buffer.toStdString());
        qDebug() << message;
        QString str2=message.left(3);
        if(str2=="LOG"){
            QString name = message.mid(3,9);            //取出名字
            QString password = message.mid(12);        //取出密码
            int num=db.selectData(name.toInt(),password);
            if(num==1){
                int flag=0;
                for(int i=0;i<userlist.count();i++){
                    if(userlist[i].name==name){
                        userlist[i].socket = tcp_socket;
                        QString str= "log_in_ok";
                        tcp_socket->write(str.toUtf8());
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    MyUser user;
                    user.name = name;
                    user.socket = tcp_socket;
                    userlist.append(user);
                    QString str= "log_in_ok";
                    tcp_socket->write(str.toUtf8());
                }
            }
            else if(num==2){
                QString str= "password_wrong";
                tcp_socket->write(str.toUtf8());
            }
            else if(num==3){
                QString str= "No_account";
                tcp_socket->write(str.toUtf8());
            }
        }
        else if(str2=="REG"){
            QString name = message.mid(3,9);            //取出名字
            QString password = message.mid(12);        //取出密码
            if(db.insertUserstable(name.toInt(),password)){
                QString str= "sign_in_ok";
                qDebug()<<"sign_in_ok";
                tcp_socket->write(str.toUtf8());
                //sql will been inserted;
            }
            else{
                QString str= "sign_in_fail";
                qDebug()<<"sign_in_fail";
                tcp_socket->write(str.toUtf8());
            }
        }
        else if(str2=="SCH"){
            QString friend_name = message.mid(3,9);      //取出好友名字
            if(!db.selectFriend(friend_name.toInt())){
                QString str = "no_friend_name";
                qDebug()<<"no_friend_name";
                tcp_socket->write(str.toUtf8());
            }
            else{
                int i;
                for(i=0;i<userlist.count();i++){
                    if(userlist.at(i).name == friend_name){
                        if(userlist.at(i).socket->state()==QAbstractSocket::ConnectedState){
                            QString str = "connect_friend";
                            qDebug()<<"connect_friend";
                            tcp_socket->write(str.toUtf8());
                        }
                        else{
                            QString str = "friend_no_connection";
                            qDebug()<<"friend_no_connection";
                            tcp_socket->write(str.toUtf8());
                        }
                        break;
                    }
                }
                if(i==userlist.count()){
                    QString str = "friend_no_connection";
                    qDebug()<<"friend_no_connection";
                    tcp_socket->write(str.toUtf8());
                }
            }

        }
        else if(str2=="MES"){
            QString self_name = message.mid(3,9);
            QString friend_name = message.mid(12,9);//取出好友名字
            QString mes = message.mid(21);       //取出谈话信息
            int i;
            for(i=0;i<userlist.count();i++){
                if(userlist.at(i).name == friend_name){
                    if(userlist.at(i).socket->state()==QAbstractSocket::ConnectedState){
                        QString str="NAME"+self_name+mes;
                        qDebug()<<str;
                        userlist.at(i).socket->write(str.toUtf8());
                        QString str3="message_send"+friend_name;
                        qDebug()<<str3;
                        tcp_socket->write(str3.toUtf8());
                    }
                    else{
                        QString str = "no_connection"+friend_name;
                        qDebug()<<str;
                        tcp_socket->write(str.toUtf8());
                    }
                    break;
                }
            }
            if(i==userlist.count()){
                QString str = "no_connection";
                qDebug()<<"no_connection";
                tcp_socket->write(str.toUtf8());
            }
        }
    }







