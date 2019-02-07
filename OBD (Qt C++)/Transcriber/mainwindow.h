#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QSerialPort>
#include <QSerialPortInfo>

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
    QSerialPort *serial;

    void readNetworkLine();
    void readSerialLine();
    void LogDat(QString log);
    void LogDatError(QString log);
    QByteArray readLine();

    QByteArray lastSerial;
};

#endif // MAINWINDOW_H
