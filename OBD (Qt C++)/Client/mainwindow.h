#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QBitArray>
#include <QTimer>
#include <QThread>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QDateTime>
#include <QCategoryAxis>

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
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void graph_RPM(qint64 timer);
    void graph_TPS(qint64 timer);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QtCharts::QLineSeries *series;

    void LogDat(QString log);
    void LogDatError(QString log);

    bool setupOBD();
    bool requestPIDs();
    bool requestOBDStandar();
    bool requestMILs();
    int requestRPM();
    bool requestFuelSystem();
    bool requestOxygenSensor();
    QByteArray readLine();
    int requestIntakeTemperature();
    int requestTPS();
    void graph_ITS(qint64 timer);
};

#endif // MAINWINDOW_H
