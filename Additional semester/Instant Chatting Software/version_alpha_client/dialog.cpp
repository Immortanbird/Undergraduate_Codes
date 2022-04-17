#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->errorLabel->clear();
}

Dialog::Dialog(QWidget *parent, QTcpSocket *tcpsocket, QString username, QString friendname) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->errorLabel->clear();
    ui->userLabel->setText(friendname);
    this->tcpsocket = tcpsocket;
    this->username = username;
    this->friendname = friendname;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::displayMessage(QString message)
{
    if(message == "message_send")
    {
        ui->textBrowser->moveCursor(QTextCursor::End);
        ui->textBrowser->insertPlainText("You " + QTime::currentTime().toString() + "\n" + ui->textEdit->toPlainText() + "\n");
    }

    if(message == "no_connection")
    {
        ui->textBrowser->moveCursor(QTextCursor::End);
        ui->textBrowser->insertPlainText("User offline!\n");
    }
}

void Dialog::sendMessage()
{
    if(ui->textEdit->toPlainText().size() == 0)
    {
        ui->errorLabel->setText("Cannot send empty message!");
        return;
    }
    tcpsocket->write(("MES" + username + friendname + ui->textEdit->toPlainText()).toUtf8());
}

QString Dialog::getFriendname()
{
    return friendname;
}

void Dialog::receiveMessage(QString message)
{
    ui->textBrowser->moveCursor(QTextCursor::End);
    ui->textBrowser->insertPlainText(friendname + " " + QTime::currentTime().toString() + "\n" + message + "\n");
}

void Dialog::on_sendPushButton_clicked()
{
    sendMessage();
}

void Dialog::on_closePushButton_clicked()
{
    accept();
}
