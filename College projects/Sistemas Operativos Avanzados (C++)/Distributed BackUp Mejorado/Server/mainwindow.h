#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QPair>
#include <syslog.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFileDialog>

#include "configfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, bool gui = true, quint16 port = 0);
    ~MainWindow();
    unsigned int get_clients(void);
    QPair<QHostAddress,int> get_this_client(int indice);
    QString get_this_client_name(int indice);
    unsigned int get_pending_clients();
    QPair<QHostAddress,int> get_this_pending_client(int indice);
    QString get_this_pending_client_name(QPair<QHostAddress,int> cliente);
    bool user_action(QString user, QString accion);
    bool is_occupied();
    void inc_nFiles();
    int get_nFiles();
    void inc_nBytesReceived(int inc);
    int get_nBytesReceived(void);
    void insert_transfer_time(int time);
    int get_total_transfer_time();


private slots:
    void on_ConnectButton_clicked();
    void Read();
    
    void on_PortNumber_valueChanged(int arg1);

    void on_ImportButton_clicked();

    void on_ExportButton_clicked();


private:
    Ui::MainWindow *ui;

    bool GUI;
    quint16 SelfPort;

    QUdpSocket* Server;

    QVector<QPair<QHostAddress, int> > Clients;
    QVector<QPair<QHostAddress, int> > NewClients;
    QVector<QPair<QHostAddress, int> > AliveClients;
    QVector<QPair<QHostAddress, int> > WaitingClients;
    QVector<uint> DestNumber;
    int DesNumber;
    uint ClientNumber;    

    bool canSend;
    bool init;
    QTimer KeepAlive;
    bool WaitingKeepAlive;
    QTimer MaxTimeAlive;

    QSqlDatabase Database;
    QVector<QString> ClientsNames;

    void setConfigFile(QString fileUrl);

    ConfigFile Configurationini;

    QTimer timer;

    int nFiles;
    int nBytesReceived;
    QVector<int> transfer_time;
};

#endif // MAINWINDOW_H
