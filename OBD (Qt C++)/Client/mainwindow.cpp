#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.37", 1024);

    if(socket->waitForConnected())
        LogDat("Connected to 127.0.0.1::1024");
    else
        LogDatError("Failed to connect");



    if(writeData("ATZ\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT Z");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATWS\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT WS");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATZ\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT Z");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATE0\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT E0");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATL0\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT L0");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATH1\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT H1");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATI\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT I");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("AT@1\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT @1");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("AT@2\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT @2");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATRV\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT RV");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATSP0\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT SP0");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("0100\r"))
        LogDat("Sended to 127.0.0.1::1024 : 0100");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead()) {
        QByteArray res = socket->readAll();
        QString pids;

        for(int i = 10; i < res.size() - 2; ++i) {
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
    } else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("ATDP\r"))
        LogDat("Sended to 127.0.0.1::1024 : AT DP");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("011C\r"))
        LogDat("Sended to 127.0.0.1::1024 : 011C");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("0101\r"))
        LogDat("Sended to 127.0.0.1::1024 : 0101");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("010C\r"))
        LogDat("Sended to 127.0.0.1::1024 : 010C");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead()){
        QByteArray res = socket->readAll();
        res.remove(0,10);
        res.remove(res.size()-2,2);
        QString res2(res);

        int rpm = res2.toUInt(nullptr, 16) / 4;

        LogDat("Server response: " + QString::number(rpm) + "RPM");
    } else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("0103\r"))
        LogDat("Sended to 127.0.0.1::1024 : 0103");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }

    if(writeData("0113\r"))
        LogDat("Sended to 127.0.0.1::1024 : 0113");
    else {
        LogDatError("Failed to send"); return;
    }

    if(socket->waitForReadyRead())
        LogDat("Server response: " + socket->readAll());
    else {
        LogDatError("Didn't respond"); return;
    }
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
