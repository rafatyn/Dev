#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, bool gui, quint16 port) :
    QMainWindow(parent),
    GUI(gui),
    SelfPort(port)
{
    if(GUI){
        ui = new Ui::MainWindow;
        ui->setupUi(this);
        ui->PortNumber->setMinimum(1024);
        ui->PortNumber->setMaximum(65536);
    }

    ClientNumber = 0;
    nBytesReceived = 0;
    nFiles = 0;

    init = true;

    Database = QSqlDatabase::addDatabase("QSQLITE", "Auth");
    Database.setDatabaseName("ServerAuth");

    bool exits = QFile("ServerAuth").exists();

    if(Database.open()){
        QSqlQuery query(Database);

        if(!exits){
            if(query.exec("CREATE TABLE Clients "
                          "(NAME VARCHAR(30) PRIMARY KEY,"
                          "PASS VARCHAR(30));")){
                QMessageBox::warning(this, "Database", "Database and table created", QMessageBox::Ok);
            }
        }
    }else{
        if(GUI)
            QMessageBox::warning(this, "Database", "Cannot open or create the database", QMessageBox::Ok);
        else
            syslog(LOG_ERR, "Cannot open or create the database\n");
        this->close();
    }

    setConfigFile("/etc/Distributed-Backup-Server.conf");

    if(port) SelfPort = port;

    if(GUI)
        ui->PortNumber->setValue(SelfPort);

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
                qint64 bytessended = Server->writeDatagram(QByteArray("Keep Alive?"), client.first, client.second);
                if(bytessended == -1){
                    if(GUI)
                        QMessageBox::warning(this, "Error sending Keep Alive",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    else
                        syslog(LOG_WARNING, "Error sending Keep Alive: %s\n", Server->errorString().toLatin1().data());
                }
            }
            MaxTimeAlive.start();
        }else{
            WaitingKeepAlive = true;
        }
    });
    KeepAlive.start();

    if(port){
        if(Server->bind(QHostAddress::LocalHost, port)){
            connect(Server, &QUdpSocket::readyRead, this, &MainWindow::Read);
            if(GUI){
                ui->ConnectButton->setText("Connected");
                ui->ConnectButton->setEnabled(false);
                ui->PortNumber->setEnabled(false);
                ui->statusBar->showMessage(QString("Connected to: %1::%2")
                                           .arg(Server->localAddress().toString())
                                           .arg(Server->localPort()));
            }else{
                syslog(LOG_NOTICE, "Connected to: %s::%d\n", Server->localAddress().toString().toLatin1().data(), (int)Server->localPort());
            }
        }else{
            if(GUI)
                QMessageBox::warning(this, "Error", Server->errorString(), QMessageBox::Ok);
            else
                syslog(LOG_ERR, "Error binding: %s\n", Server->errorString().toLatin1().data());
        }
    }
}

MainWindow::~MainWindow()
{
    if(GUI){
        delete ui;
    }

    delete Server;
    closelog();
}

unsigned int MainWindow::get_clients()
{
    return Clients.size();
}

QPair<QHostAddress, int> MainWindow::get_this_client(int indice)
{
    return Clients.at(indice);
}

QString MainWindow::get_this_client_name(int indice)
{
    return ClientsNames.at(indice);
}

unsigned int MainWindow::get_pending_clients()
{
    return WaitingClients.size();
}

QPair<QHostAddress, int> MainWindow::get_this_pending_client(int indice)
{
    return WaitingClients.at(indice);
}

QString MainWindow::get_this_pending_client_name(QPair<QHostAddress, int> cliente)
{
    for(int j=0; j<Clients.size();j++){
        if(cliente == Clients.at(j)){
            return(ClientsNames.at(j));
        }
    }

    return "";
}

bool MainWindow::user_action(QString user, QString action)
{
    if(user=="server" && action == "disconnect"){
        if(Clients.size()>0){
            for(int j=0;j<Clients.size();j++){
                Server->writeDatagram(QByteArray("You have been disconnected"),Clients.at(j).first, Clients.at(j).second);
            }
        }
        ui->ConnectButton->setText("Connect");
        ui->ConnectButton->setEnabled(true);
        ui->PortNumber->setEnabled(true);
        ui->statusBar->showMessage(QString("Disconnected by HTTP Request"));
        Server->close();
        return true;
    }

    for(int i=0;i<ClientsNames.size();i++){
        if(ClientsNames.at(i)==user){
            if(action == "disconnect"){
                Server->writeDatagram(QByteArray("You have been disconnected"),Clients.at(i).first, Clients.at(i).second);
                return true;
            }
        }
    }
    return false;
}

bool MainWindow::is_occupied()
{
    return canSend;
}

void MainWindow::on_ConnectButton_clicked()
{
    quint16 p;
    if(SelfPort == 0)
        p = ui->PortNumber->value();
    else
        p = SelfPort;

    if(Server->bind(QHostAddress::LocalHost, p)){
        connect(Server, &QUdpSocket::readyRead, this, &MainWindow::Read);
        ui->ConnectButton->setText("Connected");
        ui->ConnectButton->setEnabled(false);
        ui->PortNumber->setEnabled(false);
        ui->statusBar->showMessage(QString("Connected to: %1::%2")
                                   .arg(Server->localAddress().toString())
                                   .arg(Server->localPort()));
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
                bytessended = Server->writeDatagram(QByteArray("Need Auth"),
                                                    sendDir, sendPort);

                if(bytessended == -1){
                    if(GUI)
                        QMessageBox::warning(this, "Error sending Need Auth",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    else
                        syslog(LOG_WARNING, "Error sending Need Auth: %s\n", Server->errorString().toLatin1().data());
                }
            }
        }else if(data.startsWith("LogIn")){
            data.remove(0, data.indexOf(":")+2);
            QString name(data);

            name.remove(name.indexOf("/"), name.size());

            QString pass(data);

            pass.remove(0, pass.indexOf("/")+1);

            bool found = false;
            for(auto Name: ClientsNames){
                if(Name == name){
                    found = true;
                }
            }

            if(!found){
                QSqlQuery query(Database);

                query.prepare("SELECT * FROM Clients "
                              "WHERE NAME = :name AND PASS = :pass");
                query.bindValue(":name", name);
                query.bindValue(":pass", pass);

                if(!query.exec()){
                    qint64 bytessended = Server->writeDatagram(QByteArray("Cannot LogIn"),
                                                        sendDir, sendPort);

                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending Cannot Login",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending Cannot Login: %s\n", Server->errorString().toLatin1().data());
                    }
                }else{
                    if(!query.seek(1) && query.seek(0)){
                        ClientsNames.push_back(name);

                        qint64 bytessended = Server->writeDatagram(QByteArray("Connected client ")
                                                            .append(Server->localAddress().toString())
                                                            .append("::").append(Server->localPort()),
                                                            sendDir, sendPort);

                        if(bytessended == -1){
                            if(GUI)
                                QMessageBox::warning(this, "Error sending Connected Client",
                                                     Server->errorString(),
                                                     QMessageBox::Ok);
                            else
                                syslog(LOG_WARNING, "Error sending Connected Client: %s\n", Server->errorString().toLatin1().data());
                        }

                        if(canSend){
                            Clients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
                            ClientNumber++;

                            if(WaitingClients.size()>0){
                                for(int i=0; i<WaitingClients.size(); i++){
                                    if((ClientNumber>=(DestNumber[i]+1))&&canSend){
                                        bytessended = Server->writeDatagram(QByteArray("Ready Clients"),
                                                                            WaitingClients[i].first, WaitingClients[i].second);

                                        if(bytessended == -1){
                                            if(GUI)
                                                QMessageBox::warning(this, "Error sending Ready Clients",
                                                                     Server->errorString(),
                                                                     QMessageBox::Ok);
                                            else
                                                syslog(LOG_WARNING, "Error sending Ready Clients: %s\n", Server->errorString().toLatin1().data());
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
                    }else{
                        qint64 bytessended = Server->writeDatagram(QByteArray("Cannot Auth"),
                                                            sendDir, sendPort);

                        if(bytessended == -1){
                            if(GUI)
                                QMessageBox::warning(this, "Error sending Cannot Auth",
                                                     Server->errorString(),
                                                     QMessageBox::Ok);
                            else
                                syslog(LOG_WARNING, "Error sending Cannot Auth: %s\n", Server->errorString().toLatin1().data());
                        }
                    }
                }
            }else{
                qint64 bytessended = Server->writeDatagram(QByteArray("Already LogIn"),
                                                    sendDir, sendPort);

                if(bytessended == -1){
                    if(GUI)
                        QMessageBox::warning(this, "Error sending Already LogIn",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    else
                        syslog(LOG_WARNING, "Error sending Already LogIn: %s\n", Server->errorString().toLatin1().data());
                }
            }
        }else if(data.startsWith("Register")){
            data.remove(0, data.indexOf(":")+2);
            QString name(data);

            name.remove(name.indexOf("/"), name.size());

            QString pass(data);

            pass.remove(0, pass.indexOf("/")+1);

            bool found = false;
            for(auto Name: ClientsNames){
                if(Name == name){
                    found = true;
                }
            }

            if(!found){
                QSqlQuery query(Database);

                query.prepare("INSERT INTO Clients "
                              "VALUES(:name, :pass);");
                query.bindValue(":name", name);
                query.bindValue(":pass", pass);

                if(!query.exec()){
                    qint64 bytessended = Server->writeDatagram(QByteArray("Cannot Register"),
                                                        sendDir, sendPort);

                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending Cannot Register",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending Cannot Register: %s\n", Server->errorString().toLatin1().data());
                    }
                }else{
                    qint64 bytessended = Server->writeDatagram(QByteArray("Connected client ")
                                                        .append(Server->localAddress().toString())
                                                        .append("::").append(Server->localPort()),
                                                        sendDir, sendPort);

                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending Connected Client",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending Connected Client: %s\n", Server->errorString().toLatin1().data());
                    }

                    ClientsNames.push_back(name);

                    if(canSend){
                        Clients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
                        ClientNumber++;

                        if(WaitingClients.size()>0){
                            for(int i=0; i<WaitingClients.size(); i++){
                                if((ClientNumber>=(DestNumber[i]+1))&&canSend){
                                    bytessended = Server->writeDatagram(QByteArray("Ready Clients"),
                                                                        WaitingClients[i].first, WaitingClients[i].second);

                                    if(bytessended == -1){
                                        if(GUI)
                                            QMessageBox::warning(this, "Error sending Ready Clients",
                                                                 Server->errorString(),
                                                                 QMessageBox::Ok);
                                        else
                                            syslog(LOG_WARNING, "Error sending Ready Clients: %s\n", Server->errorString().toLatin1().data());
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
            }else{
                qint64 bytessended = Server->writeDatagram(QByteArray("Already LogIn"),
                                                    sendDir, sendPort);

                if(bytessended == -1){
                    if(GUI)
                        QMessageBox::warning(this, "Error sending Already LogIn",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    else
                        syslog(LOG_WARNING, "Error sending Already LogIn: %s\n", Server->errorString().toLatin1().data());
                }
            }
        }else if(data.startsWith("Ready Send")){
            uint DNumber = data.remove(0, data.indexOf(":")+1).toUInt();
            timer.setInterval(300000);
            timer.start();

            if((ClientNumber>=(DNumber+1))&&canSend){
                qint64 bytessended = Server->writeDatagram(QByteArray("Ready Clients"), sendDir, sendPort);

                if(bytessended == -1){
                    if(GUI)
                        QMessageBox::warning(this, "Error sending Ready Clients",
                                             Server->errorString(),
                                             QMessageBox::Ok);
                    else
                        syslog(LOG_WARNING, "Error sending Ready Clients: %s\n", Server->errorString().toLatin1().data());
                }

                DesNumber = DNumber;
                canSend = false;
            }else{
                WaitingClients.push_back(QPair<QHostAddress,int>(sendDir, sendPort));
                DestNumber.push_back(DNumber);
            }
        }else if(data.startsWith("Sended")){

            qint64 bytessended;
            insert_transfer_time(300000 - timer.remainingTime());
            for(int i=0,j=0; i<Clients.size() && j<DesNumber; i++){
                if((Clients[i].first != sendDir)||(Clients[i].second != sendPort)){
                    bytessended = Server->writeDatagram(data, Clients[i].first, Clients[i].second);
                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending Sended message",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending Sended message: %s\n", Server->errorString().toLatin1().data());
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

                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending Keep Alive",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending Keep Alive: %s\n", Server->errorString().toLatin1().data());
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
                    ClientsNames.remove(i);
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
        }else if(data.startsWith("File Path: ")){
            qint64 bytessended;
            inc_nFiles();
            QByteArray dataSize(data);
            dataSize.remove(dataSize.lastIndexOf("Permision:")-1, data.size() - (dataSize.lastIndexOf("Permision:")-1))
                    .remove(0, dataSize.lastIndexOf("size:")+6);

            qint64 fileSize = dataSize.toLongLong();
            inc_nBytesReceived(fileSize);
            for(int i=0,j=0; i<Clients.size() && j<DesNumber; i++){
                if((Clients[i].first != sendDir)||(Clients[i].second != sendPort)){
                    bytessended = Server->writeDatagram(data, Clients[i].first, Clients[i].second);

                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending files",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending files: %s\n", Server->errorString().toLatin1().data());
                    }

                    j++;
                }
            }
        }else{
            qint64 bytessended;

            for(int i=0,j=0; i<Clients.size() && j<DesNumber; i++){
                if((Clients[i].first != sendDir)||(Clients[i].second != sendPort)){
                    bytessended = Server->writeDatagram(data, Clients[i].first, Clients[i].second);

                    if(bytessended == -1){
                        if(GUI)
                            QMessageBox::warning(this, "Error sending files",
                                                 Server->errorString(),
                                                 QMessageBox::Ok);
                        else
                            syslog(LOG_WARNING, "Error sending files: %s\n", Server->errorString().toLatin1().data());
                    }

                    j++;
                }
            }
        }
    }
}

void MainWindow::on_PortNumber_valueChanged(int arg1)
{
    SelfPort = arg1;
}

void MainWindow::on_ImportButton_clicked()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, "Select config file", "/home", "Config File (*.conf)");
    if(fileUrl != "")
        setConfigFile(fileUrl);
}

void MainWindow::on_ExportButton_clicked()
{
    QVector<QPair<QString,QVector<QPair<QString,QString> > > > data;
    data.push_back(QPair<QString,QVector<QPair<QString,QString> > >
                  ("Server",QVector<QPair<QString,QString>>
                  (1,QPair<QString,QString>("port",QString().setNum(SelfPort)))));

    if(Configurationini.WriteConfigFile(data)){
        if(GUI)
            QMessageBox::warning(this, "Error",
                                 "Error exporting Config file",
                                 QMessageBox::Ok);
    }else{
        if(GUI)
            QMessageBox::warning(this, "Success",
                                 "Configuration exported",
                                 QMessageBox::Ok);
    }
}

void MainWindow::inc_nFiles()
{
    nFiles++;
}

int MainWindow::get_nFiles()
{
    return nFiles;
}

void MainWindow::inc_nBytesReceived(int inc)
{
    nBytesReceived += inc;
}

int MainWindow::get_nBytesReceived()
{
    return nBytesReceived;
}

void MainWindow::insert_transfer_time(int time)
{
    transfer_time.push_back(time);
}

int MainWindow::get_total_transfer_time()
{
    int tmp = 0;
    for(int i = 0; i<transfer_time.size();i++){
        tmp +=transfer_time.at(i);
    }
    return tmp;
}

void MainWindow::setConfigFile(QString fileUrl)
{
    if(Configurationini.ReadConfigFile(fileUrl)){
        if(GUI)
            QMessageBox::warning(this, "Error",
                                 "Error importing Config file",
                                 QMessageBox::Ok);
        else
            syslog(LOG_WARNING, "Error importing Config file");
    }else{
        QString tmp;
        tmp = Configurationini.getValue("Server","port");
        if(tmp != "Not Found"){
            SelfPort = tmp.toShort();
            if(GUI){
                ui->PortNumber->setValue(SelfPort);
            }
        }

        if(GUI && !init){
            QMessageBox::warning(this, "Success",
                                 "Configuration imported",
                                 QMessageBox::Ok);
            init = false;
        }
    }
}
