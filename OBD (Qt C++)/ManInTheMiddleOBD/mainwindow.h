#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QTcpServer *server;
    QList<QTcpSocket*> clients;

    void readNetwork1Line();
    void readNetwork2Line();
    void LogDat(QString log);
    void LogDatError(QString log);
    QByteArray readLine(QTcpSocket* sk);
    void newConnection();
    void disconnected();
};

#endif // MAINWINDOW_H
