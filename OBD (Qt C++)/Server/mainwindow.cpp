#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));

    if(server->listen(QHostAddress::Any, 1024))
        LogDat("Listening to 1024");
    else
        LogDatError("Failed to listen");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    while (server->hasPendingConnections())
    {
        QTcpSocket *socket = server->nextPendingConnection();
        LogDat("Client connected from " + QHostAddress(socket->peerAddress().toIPv4Address()).toString() + "::" + QString::number(socket->peerPort()));
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
    }
}

void MainWindow::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    LogDat("Client disconnected from " + QHostAddress(socket->peerAddress().toIPv4Address()).toString() + "::" + QString::number(socket->peerPort()));
    socket->deleteLater();
}

void MainWindow::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    while (socket->bytesAvailable() > 0)
    {
        QString readed = socket->readAll();
        LogDat(QHostAddress(socket->peerAddress().toIPv4Address()).toString() + "::" + QString::number(socket->peerPort()) + " sended: " + readed);

        if (readed == "ATZ\r")
            socket->write("ELM327 v1.5\r>");
        else if (readed == "ATWS\r")
            socket->write("ELM327 v1.5\r>");
        else if (readed == "ATE0\r")
            socket->write("OK\r>");
        else if (readed == "ATL0\r")
            socket->write("OK\r>");
        else if (readed == "ATH1\r")
            socket->write("OK\r>");
        else if (readed == "ATI\r")
            socket->write("ELM327 v1.5\r>");
        else if (readed == "AT@1\r")
            socket->write("OBDII to RS232 Interpreter\r>");
        else if (readed == "AT@2\r")
            socket->write("?\r>");
        else if (readed == "ATRV\r")
            socket->write("13.5V\r>");
        else if (readed == "ATSP0\r")
            socket->write("OK\r>");
        else if (readed == "0100\r")
            socket->write("416B10410000000000\r>");
        else if (readed == "ATDP\r")
            socket->write("AUTO,SAE J1850 PWM\r>");
        else if (readed == "011C\r")
            socket->write("NO DATA\r>");
        else if (readed == "0101\r")
            socket->write("416B1041010306E0E0\r>");
        else if (readed == "010C\r")
            socket->write("416B10410C0E78\r>");
        else if (readed == "0103\r")
            socket->write("416B1041030100\r>");
        else if (readed == "0113\r")
            socket->write("416B10411333\r>");
    }
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
