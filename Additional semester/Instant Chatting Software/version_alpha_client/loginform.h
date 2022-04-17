#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QtNetwork>
#include "connectform.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT
public:
    static QString localUser;

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;
    QTcpSocket *tcpsocket;
    ConnectForm connectform;

private slots:
    void login();
    void signin();
    void refresh();
    void readMessage();
    void on_loginPushButton_clicked();
    void on_signinPushButton_clicked();
};

#endif // LOGINFORM_H
