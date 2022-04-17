#include "loginform.h"
#include "ui_loginform.h"

QString LoginForm::localUser = "";

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->errorLabel->clear();
    ui->userLineEdit->setPlaceholderText("Please enter user name.");
    ui->passwordLineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->passwordLineEdit->setPlaceholderText("Please enter password.");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    tcpsocket = new QTcpSocket(this);
    connect(ui->userLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(refresh()));
    connect(ui->passwordLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(refresh()));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::login()
{
    QString user = ui->userLineEdit->text();

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

    if(ui->passwordLineEdit->text().size() == 0)
    {
        ui->errorLabel->setText("Please enter password!");
        return;
    }

    ui->errorLabel->clear();
    if(tcpsocket->state() != QAbstractSocket::ConnectedState)
    {
        tcpsocket->connectToHost("10.195.200.206", 5566);
        connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    }
    LoginForm::localUser = user;
    tcpsocket->write(("LOG" + user + ui->passwordLineEdit->text()).toUtf8());
}

void LoginForm::signin()
{
    QString user = ui->userLineEdit->text();

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

    if(ui->passwordLineEdit->text().size() == 0)
    {
        ui->errorLabel->setText("Please enter password!");
        return;
    }

    ui->errorLabel->clear();
    if(tcpsocket->state() != QAbstractSocket::ConnectedState)
    {
        tcpsocket->connectToHost("10.195.200.206", 5566);
        connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    }
    tcpsocket->write(("REG" + user + ui->passwordLineEdit->text()).toUtf8());
}

void LoginForm::refresh()
{
    ui->errorLabel->clear();
}

void LoginForm::readMessage()
{
    QString message;
    message.prepend(tcpsocket->readAll());

    if(message == "log_in_ok")
    {
        this->hide();
        connectform.show();
        disconnect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
        connectform.getTcpSocket(tcpsocket);
        return;
    }

    if(message == "password_wrong")
    {
        ui->errorLabel->setText("Wrong password!");
        return;
    }

    if(message == "No_account")
    {
        ui->errorLabel->setText("Username doesn't exist, please sign in first!");
        return;
    }

    if(message == "sign_in_ok")
    {
        ui->errorLabel->setText("Signed in successfully.");
        return;
    }

    if(message == "sign_in_fail")
    {
        ui->errorLabel->setText("Username already exists!");
        return;
    }
}

void LoginForm::on_loginPushButton_clicked()
{
    login();
}

void LoginForm::on_signinPushButton_clicked()
{
    signin();
}
