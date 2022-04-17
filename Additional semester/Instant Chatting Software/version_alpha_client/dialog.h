#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    Dialog(QWidget *parent, QTcpSocket *tcpsocket, QString username, QString friendname);
    Dialog(const Dialog &dlg);
    ~Dialog();
    QString getFriendname();
    void receiveMessage(QString message);
    void displayMessage(QString message);

private:
    Ui::Dialog *ui;
    QTcpSocket *tcpsocket;
    QString username;
    QString friendname;

private slots:
    void sendMessage();
    void on_sendPushButton_clicked();
    void on_closePushButton_clicked();
};

#endif // DIALOG_H
