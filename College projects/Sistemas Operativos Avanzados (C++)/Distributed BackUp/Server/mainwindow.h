#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QPair>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ConnectButton_clicked();
    void Read();
    
private:
    Ui::MainWindow *ui;
    QUdpSocket* Server;

    QVector<QPair<QHostAddress, int> > Clients;
    QVector<QPair<QHostAddress, int> > NewClients;
    QVector<QPair<QHostAddress, int> > AliveClients;
    QVector<QPair<QHostAddress, int> > WaitingClients;
    QVector<uint> DestNumber;
    int DesNumber;
    uint ClientNumber;    

    bool canSend;
    QTimer KeepAlive;
    bool WaitingKeepAlive;
    QTimer MaxTimeAlive;
};

#endif // MAINWINDOW_H
