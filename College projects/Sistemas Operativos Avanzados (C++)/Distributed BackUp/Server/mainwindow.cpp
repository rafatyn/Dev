#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ClientNumber = 0;

    ui->PortNumber->setMinimum(1024);
    ui->PortNumber->setMaximum(65536);

    Server = new QUdpSocket(this);

    canSend = true;
    WaitingKeepAlive = false;

    MaxTimeAlive.setInterval(2000);
    MaxTimeAlive.setSingleShot(true);
    connect(&MaxTimeAlive, &QTimer::timeout, this, [=](){
        Clients.clear();
        Clients = AliveClients;
        ClientNumber = Clients.size();
        AliveClients.clear();
        canSend = true;
    });

    KeepAlive.setInterval(30000);
    connect(&KeepAlive, &QTimer::timeout, this, [=](){
        if(canSend){
            canSend = false;
            for(auto client : Clients){
                Server->writeDatagram(QByteArray("Keep Alive?"), client.first, client.second);
            }
            MaxTimeAlive.start();
        }else{
            WaitingKeepAlive = true;
        }
    });
    KeepAlive.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Server;
}

void MainWindow::on_ConnectButton_clicked()
{
    if(Server->bind(QHostAddress::LocalHost, ui->PortNumber->value())){
        connect(Server, &QUdpSocket::readyRead, this, &MainWindow::Read);
        ui->ConnectButton->setText("Connected");
        ui->ConnectButton->setEnabled(false);
        ui->PortNumber->setEnabled(false);
        ui->statusBar->showMessage(QString("Connected to: %1::%2").arg(Server->localAddress().toString()).arg(Server->localPort()));
    }else{
        QMessageBox::warning(this, "Error", Server->errorString(), QMessageBox::Ok);
    }
}

void MainWindow::Read()
{
    while(Server->hasPendingDatagrams()){
        QNetworkDatagram datagram = Server->receiveDatagram();
        QByteArray data = datagram.data();
        QHostAddress sendDir = datagram.senderAddress();
        int sendPort = datagram.senderPort();

        if(data.startsWith("Hi Server")){
            bool exist = false;
            qint64 bytessended;

            for(auto client : Clients){
                if((client.first == sendDir)&&(client.second == sendPort)){
                    exist = true;
                }
            }

            if(!exist){
                bytessended = Server->writeDatagram(QByteArray("Connected client ").append(Server->localAddress().toString()).append("::").append(Server->localPort()), sendDir, sendPort);

                if( bytessended == -1){
                    QMessageBox::warning(this, "Error",
                                         Server->errorString(),
                                         QMessageBox::Ok);
                }

                if(canSend){
                    Clients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
                    ClientNumber++;

                    if(WaitingClients.size()>0){
                        for(int i=0; i<WaitingClients.size(); i++){
                            if((ClientNumber>=(DestNumber[i]+1))&&canSend){
                                bytessended = Server->writeDatagram(QByteArray("Ready Clients"), WaitingClients[i].first, WaitingClients[i].second);

                                if( bytessended == -1){
                                    QMessageBox::warning(this, "Error",
                                                         Server->errorString(),
                                                         QMessageBox::Ok);
                                }

                                WaitingClients.remove(i);
                                DesNumber = DestNumber[i];
                                DestNumber.remove(i);
                                canSend = false;
                                break;
                            }
                        }
                    }
                }else{
                    NewClients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
                }
            }
        }else if(data.startsWith("Ready Send")){
            uint DNumber = data.remove(0, data.indexOf(":")+1).toUInt();

            if((ClientNumber>=(DNumber+1))&&canSend){
                qint64 bytessended = Server->writeDatagram(QByteArray("Ready Clients"), sendDir, sendPort);

                if( bytessended == -1){
                    QMessageBox::warning(this, "Error",
                                         Server->errorString(),
                                         QMessageBox::Ok);
                }

                DesNumber = DNumber;
                canSend = false;
            }else{
                WaitingClients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
                DestNumber.push_back(DNumber);
            }
        }else if(data.startsWith("Sended")){

            qint64 bytessended;

            for(int i=0,j=0; i<Clients.size() && j<DesNumber; i++){
                if((Clients[i].first != sendDir)||(Clients[i].second != sendPort)){
                    bytessended = Server->writeDatagram(data, Clients[i].first, Clients[i].second);

                    if( bytessended == -1){
                        QMessageBox::warning(this, "Error",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    }

                    j++;
                }
            }

            if(NewClients.size() > 0){
                for(auto Newclient : NewClients){
                    Clients.push_back(Newclient);
                    ClientNumber++;
                }
            }

            if(WaitingKeepAlive){
                for(auto client : Clients){
                    bytessended = Server->writeDatagram(QByteArray("Keep Alive?"), client.first, client.second);

                    if( bytessended == -1){
                        QMessageBox::warning(this, "Error",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    }
                }
                MaxTimeAlive.start();
                KeepAlive.start();
            }else{
                canSend = true;
            }
        }else if(data.startsWith("Im OK")){
            AliveClients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
        }else if(data.startsWith("Bye Server")){
            bool found = false;
            for(int i=0; i<Clients.size() && !found; i++){
                if((Clients[i].first == sendDir)&&(Clients[i].second == sendPort)){
                    Clients.remove(i);
                    found = true;
                }
            }

            found = false;

            for(int i=0; i<NewClients.size() && !found; i++){
                if((NewClients[i].first == sendDir)&&(NewClients[i].second == sendPort)){
                    NewClients.remove(i);
                    found = true;
                }
            }

            found = false;

            for(int i=0; i<AliveClients.size() && !found; i++){
                if((AliveClients[i].first == sendDir)&&(AliveClients[i].second == sendPort)){
                    AliveClients.remove(i);
                    found = true;
                }
            }

            found = false;

            for(int i=0; i<WaitingClients.size() && !found; i++){
                if((WaitingClients[i].first == sendDir)&&(WaitingClients[i].second == sendPort)){
                    WaitingClients.remove(i);
                    DestNumber.remove(i);
                    found = true;
                }
            }
        }else{
            qint64 bytessended;

            for(int i=0,j=0; i<Clients.size() && j<DesNumber; i++){
                if((Clients[i].first != sendDir)||(Clients[i].second != sendPort)){
                    bytessended = Server->writeDatagram(data, Clients[i].first, Clients[i].second);

                    if( bytessended == -1){
                        QMessageBox::warning(this, "Error",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    }

                    j++;
                }
            }
        }
    }
}
