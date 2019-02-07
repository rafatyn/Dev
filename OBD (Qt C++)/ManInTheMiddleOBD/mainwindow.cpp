#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    socket->connectToHost("192.168.0.10", 35000);

    if(socket->waitForConnected())
        LogDat("Connected to OBD");
    else
        LogDatError("Failed to connect");

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readNetwork1Line);


    server = new QTcpServer(this);

    if(server->listen(QHostAddress::Any, 1024))
        LogDat("Listening to 1024");
    else
        LogDatError("Failed to listen");

    connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::readLine(QTcpSocket* sk)
{
    QByteArray msg = "";
    while(sk->bytesAvailable() > 0){
        QByteArray c = sk->read(1);
        msg.append(c);
        if(c[0] == '>'){
            return msg;
        }
    }
    return "";
}

void MainWindow::newConnection()
{
    while (server->hasPendingConnections())
    {
        QTcpSocket *s_socket = server->nextPendingConnection();
        LogDat("Client connected from " + QHostAddress(s_socket->peerAddress().toIPv4Address()).toString() + "::" + QString::number(s_socket->peerPort()));
        clients.append(s_socket);
        connect(s_socket, &QTcpSocket::readyRead, this, &MainWindow::readNetwork2Line);
        connect(s_socket, &QTcpSocket::disconnected, this, &MainWindow::disconnected);
    }
}

void MainWindow::disconnected()
{
    QTcpSocket *s_socket = static_cast<QTcpSocket*>(sender());
    LogDat("Client disconnected from " + QHostAddress(s_socket->peerAddress().toIPv4Address()).toString() + "::" + QString::number(s_socket->peerPort()));
    s_socket->deleteLater();
    clients.removeAll(s_socket);
}

void MainWindow::readNetwork1Line()
{
    QByteArray msg = readLine(socket);
    LogDat("OBD sended: " + msg);
    foreach(QTcpSocket* sk,  clients)
        sk->write(msg);
}

void MainWindow::readNetwork2Line()
{
    QTcpSocket *s_socket = static_cast<QTcpSocket*>(sender());
    QByteArray msg = readLine(s_socket);
    LogDat("Mobile App sended: " + msg);
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
