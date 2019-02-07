#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 1024);

    if(socket->waitForConnected())
        LogDat("Connected to 192.168.0.10::35000");
    else
        LogDatError("Failed to connect");

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readNetworkLine);

    serial = new QSerialPort();
    serial->close();
    serial->setPortName("COM2");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QSerialPort::ReadWrite);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialLine);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::readLine()
{
    QByteArray msg = "";
    while(socket->bytesAvailable() > 0){
        QByteArray c = socket->read(1);
        msg.append(c);
        if(c[0] == '>'){
            return msg;
        }
    }
    return "";
}

void MainWindow::readNetworkLine()
{
    QByteArray msg = readLine();
    LogDat("OBD sended: " + msg);

    if (msg.toUpper().startsWith("416B104100") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0100"))){
        LogDat("Transcriber change it to: 41 6B 10 4100 FF FF FF FF");
        serial->write("416B104100FFFFFFFF\r 416B104100FFFFFFFF\r\r>");
        /*
    }else if (msg.toUpper().startsWith("41 6B 10 41 20") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0120"))){
        LogDat("Transcriber change it to: 41 6B 10 4120 FF FF FF FF");
        serial->write("41 6B 10 41 20 FF FF FF FF\r 41 6B 10 41 20 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 41 40") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0140"))){
        LogDat("Transcriber change it to: 41 6B 10 4140 FF FF FF FF");
        serial->write("41 6B 10 41 40 FF FF FF FF\r 41 6B 10 41 40 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 41 60") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0160"))){
        LogDat("Transcriber change it to: 41 6B 10 4160 FF FF FF FF");
        serial->write("41 6B 10 41 60 FF FF FF FF\r 41 6B 10 41 60 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 41 80") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0180"))){
        LogDat("Transcriber change it to: 41 6B 10 4180 FF FF FF FF");
        serial->write("41 6B 10 41 80 FF FF FF FF\r 41 6B 10 41 80 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 41 A0") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("01A0"))){
        LogDat("Transcriber change it to: 41 6B 10 41A0 FF FF FF FF");
        serial->write("41 6B 10 41 A0 FF FF FF FF\r 41 6B 10 41 A0 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 41 C0") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("01C0"))){
        LogDat("Transcriber change it to: 41 6B 10 41C0 FF FF FF FF");
        serial->write("41 6B 10 41 C0 FF FF FF FF\r 41 6B 10 41 C0 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 45 00") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0500"))){
        LogDat("Transcriber change it to: 41 6B 10 4500 FF FF FF FF");
        serial->write("41 6B 10 45 00 FF FF FF FF\r 41 6B 10 45 00 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 00") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0600"))){
        LogDat("Transcriber change it to: 41 6B 10 4600 FF FF FF FF");
        serial->write("41 6B 10 46 00 FF FF FF FF\r 41 6B 10 46 00 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 20") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0620"))){
        LogDat("Transcriber change it to: 41 6B 10 4620 FF FF FF FF");
        serial->write("41 6B 10 46 20 FF FF FF FF\r 41 6B 10 46 20 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 40") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0640"))){
        LogDat("Transcriber change it to: 41 6B 10 4640 FF FF FF FF");
        serial->write("41 6B 10 46 40 FF FF FF FF\r 41 6B 10 46 40 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 60") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0660"))){
        LogDat("Transcriber change it to: 41 6B 10 4660 FF FF FF FF");
        serial->write("41 6B 10 46 60 FF FF FF FF\r 41 6B 10 46 60 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 80") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0680"))){
        LogDat("Transcriber change it to: 41 6B 10 4680 FF FF FF FF");
        serial->write("41 6B 10 46 80 FF FF FF FF\r 41 6B 10 46 80 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 A0") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("06A0"))){
        LogDat("Transcriber change it to: 41 6B 10 46A0 FF FF FF FF");
        serial->write("41 6B 10 46 A0 FF FF FF FF\r 41 6B 10 46 A0 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 46 C0") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("06C0"))){
        LogDat("Transcriber change it to: 41 6B 10 46C0 FF FF FF FF");
        serial->write("41 6B 10 46 C0 FF FF FF FF\r 41 6B 10 46 C0 FF FF FF FF\r\r>");
    }else if (msg.toUpper().startsWith("41 6B 10 49 00") || (msg.toUpper().startsWith("NO DATA") && lastSerial.startsWith("0900"))){
        LogDat("Transcriber change it to: 41 6B 10 4900 FF FF FF FF");
        serial->write("41 6B 10 49 00 FF FF FF FF\r 41 6B 10 49 00 FF FF FF FF\r\r>");
        */
    }else{
        serial->write(msg);
    }
}

void MainWindow::readSerialLine()
{
    QByteArray msg = serial->readAll();
    lastSerial = msg;
    LogDat("PC sended: " + msg);
    socket->write(msg);
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
