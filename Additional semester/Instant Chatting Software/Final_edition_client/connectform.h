#ifndef CONNECTFORM_H
#define CONNECTFORM_H

#include <QWidget>
#include <QtNetwork>
#include "dialog.h"

namespace Ui {
class ConnectForm;
}

class ConnectForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectForm(QWidget *parent = nullptr);
    ~ConnectForm();
    void getTcpSocket(QTcpSocket *tcpsocket);
    void paintEvent(QPaintEvent*);

private:
    Ui::ConnectForm *ui;
    QTcpSocket *tcpsocket;
    Dialog **dialoglist;
    int length;
    QString buffer;
    QString usersent;

private slots:
    void refresh();
    void newConnect();
    void readMessage();
    void on_connectPushButton_clicked();
    void on_closePushButton_clicked();
};

#endif // CONNECTFORM_H
