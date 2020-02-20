#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QTimer>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <QLabel>
#include <QMessageBox>

#include "mythread.h"
#include "qjsonmodel.h"
#include "lshwworker.h"
#include "cpuinfo.h"
#include "netstat.h"
#include "users.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    MyThread *hilo;
    QQueue <QString> sensorqueue;
    QMutex mutex;

    QTimer fivesectimer;
    QQueue <QStringList> processqueue;
    QVector<QPair<QString,QTimer*> > delUptdate;
    struct Proc{
        QString ProcPID;
        QString Cmd;
        struct Status{
            QString Name;
            QString PPid;
            QString State;
            QString Threads;
            QString CPUAll;
        }Stats;
    };

    QThread lshw;
    LshwWorker LW;

    QThread CpuIf;
    CpuInfo CPUI;

    QThread NetST;
    NetStat NS;

    QThread UserW;
    Users USR;

    MainWindow::Proc processProp(QString path, QString process);
    void closeEvent(QCloseEvent *event);

private slots:

    void updateSensor();
    void updateProcess();
    void addProcessQueue();
    void updateHardware(QByteArray out);
    void updateCpuInfo(QString out);
    void updateNetStat(QString out);
    void updateUsers(QString out);


signals:

    void RequestLshw();
    void RequestCpuInfo();
    void RequestNetStat();
    void RequestUsers();
    void RequestDelThread();
};

#endif // MAINWINDOW_H
