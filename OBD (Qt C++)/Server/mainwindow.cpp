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

    rpm.append("0E78");
    rpm.append("0F85");
    rpm.append("13B8");
    rpm.append("18E2");
    rpm.append("1E20");
    rpm.append("2156");
    rpm.append("26A0");
    rpm.append("2C20");
    rpm.append("32A5");
    rpm.append("3534");
    rpm.append("39CA");
    rpm.append("3EA0");
    rpm.append("457F");
    rpm.append("4845");
    rpm.append("4FB4");
    rpm.append("514F");
    rpm.append("5610");
    rpm.append("5D2D");
    rpm.append("633B");
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
        else if (readed == "ATDP\r")
            socket->write("AUTO,SAE J1850 PWM\r>");
        else if (readed == "0100\r"){
            socket->write("416B104100FFFFFFFF\r");
            socket->write("416B104100FFFFFFFF\r\r>");
        }else if (readed == "0120\r"){
            socket->write("416B104120FFFFFFFF\r");
            socket->write("416B104120FFFFFFFF\r\r>");
        }else if (readed == "0140\r"){
            socket->write("416B104140FFFFFFFF\r");
            socket->write("416B104140FFFFFFFF\r\r>");
        }else if (readed == "0160\r"){
            socket->write("416B104160FFFFFFFF\r");
            socket->write("416B104160FFFFFFFF\r\r>");
        }else if (readed == "0180\r"){
            socket->write("416B104180FFFFFFFF\r");
            socket->write("416B104180FFFFFFFF\r\r>");
        }else if (readed == "01A0\r"){
            socket->write("416B1041A0FFFFFFFF\r");
            socket->write("416B1041A0FFFFFFFF\r\r>");
        }else if (readed == "01C0\r"){
            socket->write("416B1041C0FFFFFFFF\r");
            socket->write("416B1041C0FFFFFFFF\r\r>");
        }else if (readed == "0500\r"){
            socket->write("416B104500FFFFFFFF\r");
            socket->write("416B104500FFFFFFFF\r\r>");
        }else if (readed == "0600\r"){
            socket->write("416B104600FFFFFFFF\r");
            socket->write("416B104600FFFFFFFF\r\r>");
        }else if (readed == "0620\r"){
            socket->write("416B104620FFFFFFFF\r");
            socket->write("416B104620FFFFFFFF\r\r>");
        }else if (readed == "0640\r"){
            socket->write("416B104640FFFFFFFF\r");
            socket->write("416B104640FFFFFFFF\r\r>");
        }else if (readed == "0660\r"){
            socket->write("416B104660FFFFFFFF\r");
            socket->write("416B104660FFFFFFFF\r\r>");
        }else if (readed == "0680\r"){
            socket->write("416B104680FFFFFFFF\r");
            socket->write("416B104680FFFFFFFF\r\r>");
        }else if (readed == "06A0\r"){
            socket->write("416B1046A0FFFFFFFF\r");
            socket->write("416B1046A0FFFFFFFF\r\r>");
        }else if (readed == "06C0\r"){
            socket->write("416B1046C0FFFFFFFF\r");
            socket->write("416B1046C0FFFFFFFF\r\r>");
        }else if (readed == "0900\r"){
            socket->write("416B104900FFFFFFFF\r");
            socket->write("416B104900FFFFFFFF\r\r>");
        }else if (readed == "011C\r")
            socket->write("NO DATA\r>");
        else if (readed == "0101\r"){
            socket->write("416B1041010306E0E0\r");
            socket->write("416B1041010306E0E0\r\r>");
        }else if (readed == "010C\r"){
            //socket->write("416B10410C0E78\r");
            //socket->write("416B10410C0E78\r\r>");
            socket->write("416B10410C" + rpm[co] + "\r");
            socket->write("416B10410C" + rpm[co] + "\r\r>");
            co != rpm.size()-1 ? co++ : co = 0;
        }else if (readed == "0103\r"){
            socket->write("416B1041030100\r");
            socket->write("416B1041030100\r\r>");
        }else if (readed == "010F\r"){
            socket->write("416B10410F32\r");
            socket->write("416B10410F32\r\r>");
        }else if (readed == "0111\r"){
            socket->write("416B1041117F\r");
            socket->write("416B1041117F\r\r>");
        }else if (readed == "0113\r"){
            socket->write("416B10411333\r");
            socket->write("416B10411333\r\r>");
        }
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
