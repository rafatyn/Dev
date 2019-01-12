#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QBitArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool connectToHost(QString host);
    bool writeData(QByteArray data);
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    void LogDat(QString log);
    void LogDatError(QString log);
};

#endif // MAINWINDOW_H
