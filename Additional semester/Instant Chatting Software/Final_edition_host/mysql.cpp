#include "mysql.h"
MySql* MySql::sqlhand = nullptr;

MySql::MySql(QObject *parent) : QObject(parent)//直接打开数据库,没有表就创建一个
{
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("root");
        database.setPassword("123456");
    }
//    database.open();
    if(database.open()){
         QSqlQuery* sqlquery;
        QStringList tablelist = database.tables();
        sqlquery = new QSqlQuery(database);
        if(!tablelist.contains("userstable")){
            QString createusers = "CREATE TABLE userstable (ID int primary key,PASSWORD varchar)";
            if(sqlquery->prepare(createusers)){
                if(sqlquery->exec()){
                    qDebug()<<"Create userstable OK";
                }
            }
            else{
                qDebug()<<"create userstable command error !";
            }
        }
        else{
            qDebug()<<"userstable already exist !";
        }

    }
    else{
        qDebug()<<"database open faild !";
    }

}
void MySql::openDatabase(){

}
void MySql::createTable(){

}
bool MySql::insertUserstable(int id,QString password){//插入账号及密码,注册时用 账号重复会报错
    QSqlQuery sqlquery;
    sqlquery.prepare("INSERT INTO userstable(ID ,PASSWORD) VALUES(?,?)");
    sqlquery.addBindValue(id);
    sqlquery.addBindValue(password);
    if(sqlquery.exec()){

        qDebug()<<"insert userstable OK";
        return true;
    }
    else
    {
        qDebug()<<"Account already exists";
        return false;
    }
}
int MySql::selectData(int id,QString password){//登录时判断账号密码是否正确 密码错误就注册
    QSqlQuery sqlquery;
    QString str_select= "SELECT * FROM userstable";
    if(sqlquery.prepare(str_select)){
        if(sqlquery.exec()){
            int flag=0;
            while(sqlquery.next()){
                int dataid = sqlquery.value(0).toInt();
                QString datapassword = sqlquery.value(1).toString();
                if(dataid==id&&datapassword==password){
                    qDebug()<<"password right";
                    flag=1;
                    return 1;
                }
                else if(dataid==id&&datapassword!=password){
                    qDebug()<<"password wrong";
                    flag=2;
                    return 2;
                }

            }
            if(flag==0){
                qDebug()<<"No account !";
                return 3;
            }

        }
    }
    else{
        qDebug()<<"select table command error !";
    }
}

bool MySql::selectFriend(int id){
    QSqlQuery sqlquery;
    QString str_select= "SELECT id FROM userstable";
    if(sqlquery.prepare(str_select)){
        if(sqlquery.exec()){
            int flag=0;
            while(sqlquery.next()){
                int dataid = sqlquery.value(0).toInt();
                if(dataid==id){
                    qDebug()<<"find friend";
                    flag=1;
                    return true;
                }
            }
            if(flag==0){
                qDebug()<<"no friend";
                return false;
            }

        }
    }
    else{
        qDebug()<<"select table command error !";
    }
}

void MySql::dropTable(QString tablename){
     QSqlQuery sqlquery;
    tablename="userstable";
    QString str_drop="DROP TABLE "+tablename;
    if(sqlquery.prepare(str_drop)){
        if(sqlquery.exec()){
            qDebug()<<"drop userstable OK";
        }
    }
    else{
        qDebug()<<"drop table command error !";
    }
}

MySql* MySql::getinstance()
{
    if(sqlhand==NULL)sqlhand=new MySql;
    return sqlhand;
}
