#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
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

signals:
    void dataReceived(QByteArray);

private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer *server;
    Ui::MainWindow *ui;
    QVector<QByteArray> rpm;
    int co = 0;

    void LogDat(QString log);
    void LogDatError(QString log);
};

#endif // MAINWINDOW_H
