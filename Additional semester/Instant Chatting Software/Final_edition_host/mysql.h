#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

class MySql : public QObject
{
    Q_OBJECT
public:
    void openDatabase();//打开数据库
    void createTable();//创表
    bool insertUserstable(int id,QString password);//插入账号及密码,注册时用
    int selectData(int id,QString password);//查找 用于判断账号是否重复
    void dropTable(QString tablename);//删表
    bool selectFriend(int id);//查找用户
    MySql* getinstance();
    explicit MySql(QObject *parent = nullptr);
private:

    static MySql* sqlhand;
    QSqlDatabase database;
signals:
};

#endif // MYSQL_H
