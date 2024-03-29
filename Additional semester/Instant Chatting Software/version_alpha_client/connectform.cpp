#include "connectform.h"
#include "loginform.h"
#include "ui_connectform.h"

ConnectForm::ConnectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
    ui->errorLabel->clear();
    ui->lineEdit->setPlaceholderText("Please enter user name.");

    dialoglist = new Dialog*[50];
    length = 0;

    connect(ui->lineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(refresh()));
}

ConnectForm::~ConnectForm()
{
    delete ui;
}

void ConnectForm::getTcpSocket(QTcpSocket *tcpsocket)
{
    this->tcpsocket = tcpsocket;
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void ConnectForm::refresh()
{
    ui->errorLabel->clear();
}

void ConnectForm::newConnect()
{
    QString user = ui->lineEdit->text();

    if(user.size() == 0)
    {
        ui->errorLabel->setText("Please enter username!");
        return;
    }

    if(user.size() != 9)
    {
        ui->errorLabel->setText("Invalid username!");
        return;
    }

    for(int i=0; i < user.size(); i++)
    {
        if(user[i] < '0' || user[i] > '9')
        {
            ui->errorLabel->setText("Invalid username!");
            return;
        }
    }

    if(user == LoginForm::localUser)
    {
        ui->errorLabel->setText("Invalid username!");
        return;
    }

    tcpsocket->write(("SCH" + user).toUtf8());
    buffer = user;
}

void ConnectForm::readMessage()
{
    QString message = tcpsocket->readAll();

    qDebug() << message << endl;

    if(message == "no_friend_name")
    {
        ui->errorLabel->setText("No such user!");
        return;
    }

    if(message == "friend_no_connection")
    {
        ui->errorLabel->setText("The user is offline!");
        return;
    }

    if(message == "connect_friend")
    {
        Dialog *dlg = new Dialog(this, tcpsocket, LoginForm::localUser, buffer);
        dialoglist[length] = dlg;
        length++;
        dlg->show();
        return;
    }

    if(message.left(12) == "message_send")
    {
        QString temp = message.mid(12);
        for(int i=0; i<length; i++)
        {
            if(dialoglist[i]->getFriendname() == temp)
            {
                dialoglist[i]->displayMessage("message_send");
                return;
            }
        }
    }

    if(message.left(13) == "no_connection")
    {
        QString temp = message.mid(13);
        for(int i=0; i<length; i++)
        {
            if(dialoglist[i]->getFriendname() == temp)
            {
                dialoglist[i]->displayMessage("no_connection");
                return;
            }
        }
    }

    if(message.left(4) == "NAME")
    {
        QString temp;
        temp = message.mid(4, 9);
        message = message.mid(13);

        for(int i=0; i < length; i++)
        {
            if(dialoglist[i]->getFriendname() == temp)
            {
                dialoglist[i]->receiveMessage(message);
                return;
            }
        }

        Dialog *dlg = new Dialog(this, tcpsocket, LoginForm::localUser, temp);
        dialoglist[length] = dlg;
        length++;
        dlg->show();
        dlg->receiveMessage(message);
    }
}

void ConnectForm::on_connectPushButton_clicked()
{
    newConnect();
}

void ConnectForm::on_closePushButton_clicked()
{
    close();
}
