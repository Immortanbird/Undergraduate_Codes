#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyTCPServer* serverhand = MyTCPServer::gethand();
    connect(serverhand,SIGNAL(sig_serverStartListening()),this,SLOT(slot_serverStartListening()));
    connect(serverhand,SIGNAL(sig_getipaddresses(QHostInfo)),this,SLOT(slot_getipaddresses(QHostInfo)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    MyTCPServer* serverhand = MyTCPServer::gethand();
    QString IP = ui->comboBox->currentText();
    QString port = ui->lineEdit->text();
    serverhand->openTCPserver(IP,port);
}


void MainWindow::slot_serverStartListening()
{
    ui->pushButton->setText("服务器已开启");
}

void MainWindow::slot_getipaddresses(QHostInfo info){
    QList<QHostAddress> addlist = info.addresses();
    if(addlist.count()>0){
        for(int i=0;i<addlist.count();i++){
            ui->comboBox->addItem(addlist.at(i).toString());
        }
    }
}


