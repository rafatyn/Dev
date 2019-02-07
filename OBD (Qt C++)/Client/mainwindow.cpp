#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    ui->comboBox->addItem("RPM",1);
    ui->comboBox->addItem("Throttle Position",2);
    ui->comboBox->addItem("Intake Temperature",3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(data);
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

QByteArray MainWindow::readLine()
{
    QByteArray line;
    while(socket->bytesAvailable() > 0) {
        QByteArray car = socket->read(1);
        if(car == "\r" || car == "\n")
            break;
        else
            line.append(car);
    }

    return line;
}

void MainWindow::LogDat(QString log)
{
    ui->scrollArea->widget()->layout()->addWidget(new QLabel(log));
}

void MainWindow::LogDatError(QString log)
{
    QLabel* aux = new QLabel("ERROR: " + log);
    QPalette* aux2 = new QPalette();
    aux2->setColor(aux->foregroundRole(), Qt::red);
    aux->setPalette(*aux2);

    ui->scrollArea->widget()->layout()->addWidget(aux);
}

bool MainWindow::setupOBD()
{
    if(!writeData("ATZ\r")){
        LogDatError("Failed to send AT Z"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATWS\r")){
        LogDatError("Failed to send AT WS"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATZ\r")){
        LogDatError("Failed to send AT Z"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATE0\r")){
        LogDatError("Failed to send AT E0"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATL0\r")){
        LogDatError("Failed to send AT L0"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATH1\r")){
        LogDatError("Failed to send AT H1"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATI\r")){
        LogDatError("Failed to send AT I"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("AT@1\r")){
        LogDatError("Failed to send AT @1"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("AT@2\r")){
        LogDatError("Failed to send AT @2"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATRV\r")){
        LogDatError("Failed to send AT RV"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATSP0\r")){
        LogDatError("Failed to send AT SP0"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    if(!writeData("ATDP\r")){
        LogDatError("Failed to send AT DP"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    return 1;
}

bool MainWindow::requestPIDs()
{
    if(writeData("0100\r"))
        LogDat("Sended to 127.0.0.1::1024 : 0100");
    else {
        LogDatError("Failed to send"); return 0;
    }

    if(socket->waitForReadyRead()){
        QByteArray res = readLine();
        QString pids;

        if(res.mid(8,2) != "00")
            return 0;

        for(int i = 10; i <= 18; ++i) {
            QString aux = QString::number(QString(res[i].operator char()).toLongLong(nullptr, 16),2);
            if(aux.length() < 4){
                int auxl = aux.length();
                for(int i=0; i<4-auxl; i++)
                    aux.insert(0,'0');
            }
            for(int j = 0; j < 4; j++) {
                if(aux[j] == '1'){
                    QString aux2 = QString::number((i - 10) * 4 + j + 1, 16).toUpper();
                    pids.append(aux2.length() > 1 ? aux2 : "0" + aux2);
                    pids.append(" - ");
                }
            }
        }

        if(pids.length() > 0)
            pids.remove(pids.length()-3,3);

        LogDat("PIDs avaliables: " + pids);
        socket->readAll();
    } else {
        LogDatError("Didn't respond"); return 0;
    }

    return 1;
}

bool MainWindow::requestOBDStandar()
{
    if(!writeData("011C\r")){
        LogDatError("Failed to send 011C"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    return 1;
}

bool MainWindow::requestMILs()
{
    if(!writeData("0101\r")){
        LogDatError("Failed to send 0101"); return 0;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readLine());
    else {
        LogDatError("Didn't respond"); return 0;
    }

    return 1;
}

int MainWindow::requestRPM()
{
    if(!writeData("010C\r")){
        LogDatError("Failed to send 010C"); return -1;
    }

    int rpm;
    if(socket->waitForReadyRead()) {
        QByteArray res = readLine();

        if(res.mid(8,2) != "0C")
            return 0;

        QString res2(res.mid(10,4));
        rpm = res2.toUInt(nullptr, 16) / 4;

        LogDat("Actual RPM: " + QString::number(rpm) + "RPM");
        socket->readAll();
    } else {
        LogDatError("Didn't respond"); return -1;
    }

    return rpm;
}

int MainWindow::requestIntakeTemperature()
{
    if(!writeData("010F\r")){
        LogDatError("Failed to send 010F"); return -1;
    }

    int temp;
    if(socket->waitForReadyRead()) {
        QByteArray res = readLine();

        if(res.mid(8,2) != "0F")
            return 0;

        QString res2(res.mid(10,2));
        temp = static_cast<int>(res2.toUInt(nullptr, 16)) - 40;

        LogDat("Actual Intake Temperature: " + QString::number(temp) + "ºC");
        socket->readAll();
    } else {
        LogDatError("Didn't respond"); return -1;
    }

    return temp;
}

int MainWindow::requestTPS()
{
    if(!writeData("0111\r")){
        LogDatError("Failed to send 0111"); return -1;
    }

    int tps;
    if(socket->waitForReadyRead()) {
        QByteArray res = readLine();

        if(res.mid(8,2) != "11")
            return 0;

        QString res2(res.mid(10,4));
        tps = res2.toUInt(nullptr, 16) * 100 / 255;

        LogDat("Actual Throttle Position: " + QString::number(tps) + "%");
        socket->readAll();
    } else {
        LogDatError("Didn't respond"); return -1;
    }

    return tps;
}

bool MainWindow::requestFuelSystem()
{
    if(!writeData("0103\r")){
        LogDatError("Failed to send"); return 0;
    }

    if(socket->waitForReadyRead()){
        QByteArray res = readLine();
        QString fuel;

        if(res.mid(8,2) != "03")
            return 0;

        if(res.mid(10,2) == "01")
            fuel = "Open loop due to insufficient engine temperature";
        else if(res.mid(10,2) == "02")
            fuel = "Closed loop, using oxygen sensor feedback to determine fuel mix";
        else if(res.mid(10,2) == "04")
            fuel = "Open loop due to engine load OR fuel cut due to deceleration";
        else if(res.mid(10,2) == "08")
            fuel = "Open loop due to system failure";
        else if(res.mid(10,2) == "10")
            fuel = "Closed loop, using at least one oxygen sensor but there is a fault in the feedback system";

        LogDat("Fuel System Status: " + fuel);
        socket->readAll();
    } else {
        LogDatError("Didn't respond"); return 0;
    }

    return 1;
}

bool MainWindow::requestOxygenSensor()
{
    if(!writeData("0113\r")){
        LogDatError("Failed to send 0113"); return 0;
    }

    if(socket->waitForReadyRead()){
        QByteArray res = readLine();
        QString sensor;

        if(res.mid(8,2) != "13")
            return 0;

        for(int i = 10; i <= 12; ++i) {
            QString aux = QString::number(QString(res[i].operator char()).toLongLong(nullptr, 16),2);
            if(aux.length() < 4){
                int auxl = aux.length();
                for(int i=0; i<4-auxl; i++)
                    aux.insert(0,'0');
            }
            for(int j=0; j<aux.size(); j++){
                if(aux[j] == '1'){
                    sensor.append("Bank " + QString::number(i-9) + " sensor " + QString::number(aux.size()-j) + " - ");
                }
            }
        }

        if(sensor.length() > 0)
            sensor.remove(sensor.length()-3,3);

        LogDat("Oxygen Sensors Avaliable: " + sensor);
        socket->readAll();
    } else {
        LogDatError("Didn't respond"); return 0;
    }

    return 1;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 1024);

    if(socket->waitForConnected())
        LogDat("Connected to 127.0.0.1::1024");
    else
        LogDatError("Failed to connect");


    if(setupOBD())
        LogDat("OBDII Reader setup done");
    else
        LogDatError("Failed to setup OBDII Reader");

    if(!requestPIDs())
        LogDatError("Failed to request PIDs");

    if(!requestOBDStandar())
        LogDatError("Failed to request OBD Standar");

    if(!requestMILs())
        LogDatError("Failed to request MIL");

    if(requestRPM() < 0)
        LogDatError("Failed to request RPM");

    if(!requestFuelSystem())
        LogDatError("Failed to request Fuel System");

    if(!requestOxygenSensor())
        LogDatError("Failed to request Oxygen Sensor");
}

void MainWindow::on_pushButton_2_clicked()
{
    QTimer* timer = new QTimer();

    series = new QtCharts::QLineSeries();
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->graph->layout()->addWidget(chartView);

    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    axisX->setTitleText("Time");
    axisX->setRange(0,25);
    axisX->setTickCount(6);
    axisX->setLabelFormat("%d");

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setLabelFormat("%d");

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    qint64 time_1;
    switch (ui->comboBox->currentData().toInt()) {
        case 1:
            axisY->setTitleText("RPM");
            axisY->setRange(0,8000);
            axisY->setTickCount(9);
            time_1 = QDateTime::currentMSecsSinceEpoch();
            connect(timer, &QTimer::timeout, this,[=]{ graph_RPM(time_1); });
            break;
        case 2:
            axisY->setTitleText("TPS");
            axisY->setRange(0,100);
            axisY->setTickCount(11);
            time_1 = QDateTime::currentMSecsSinceEpoch();
            connect(timer, &QTimer::timeout, this,[=]{ graph_TPS(time_1); });
            break;
        case 3:
            axisY->setTitleText("ºC");
            axisY->setRange(-40,215);
            axisY->setTickCount(14);
            time_1 = QDateTime::currentMSecsSinceEpoch();
            connect(timer, &QTimer::timeout, this,[=]{ graph_ITS(time_1); });
            break;
    }

    timer->start(250);
}

void MainWindow::graph_RPM(qint64 timer)
{
    series->append(static_cast<double>(QDateTime::currentMSecsSinceEpoch() - timer)/1000, requestRPM());
}

void MainWindow::graph_TPS(qint64 timer)
{
    series->append(static_cast<double>(QDateTime::currentMSecsSinceEpoch() - timer)/1000, requestTPS());
}

void MainWindow::graph_ITS(qint64 timer)
{
    series->append(static_cast<double>(QDateTime::currentMSecsSinceEpoch() - timer)/1000, requestIntakeTemperature());
}
