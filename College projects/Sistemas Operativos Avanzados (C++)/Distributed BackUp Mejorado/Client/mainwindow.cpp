#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,  quint16 clientPort, QString serverAddress, quint16 serverPort, QString sourceDir, QString destinationDir) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PortNumber->setMinimum(1024);
    ui->PortNumber->setMaximum(65536);

    ui->ServerPort->setMinimum(1024);
    ui->ServerPort->setMaximum(65536);

    ServerAddOk = true;
    canUpdateDir = true;
    canUpdateDDir = true;

    QLocale local = QLocale::system();
    QString language = QLocale::languageToString(local.language());

    QString sourceDirAddress("/home/");
    QString destinationDirAddress("/home/");
    sourceDirAddress.append(qgetenv("USER"));
    destinationDirAddress.append(qgetenv("USER"));

    if(language == "Spanish"){
        sourceDirAddress.append("/Documentos");
        destinationDirAddress.append("/Descargas");
    }else{
        sourceDirAddress.append("/Documents");
        destinationDirAddress.append("/Downloads");
    }

    ui->SourceDirAddress->setText(sourceDirAddress);
    ui->DestinationDirAddress->setText(destinationDirAddress);

    SourceDir.setPath(sourceDirAddress);
    DestinationDir.setPath(destinationDirAddress);

    setConfigFile("/etc/Client.conf");

    if(clientPort != 0) ui->PortNumber->setValue(clientPort);
    if(serverPort != 0) ui->ServerPort->setValue(serverPort);
    if(serverAddress != "") ui->ServerAddress->setText(serverAddress);
    if(sourceDir != ""){
        QDir dir(sourceDir);

        if(!dir.exists()){
            QMessageBox::warning(this, "Error",
                                 "Directory doesn't exists",
                                 QMessageBox::Ok);
        }else{
            if(sourceDir.size() != 0){
                SourceDir.setPath(sourceDir);
                ui->SourceDirAddress->setText(sourceDir);
            }else{
                QMessageBox::warning(this, "Error",
                                     "Destination directory cannot be empty",
                                     QMessageBox::Ok);
            }
        }
    }

    if(destinationDir != ""){
        QDir dir(destinationDir);

        if(!dir.exists()){
            QMessageBox::warning(this, "Error",
                                 "Directory doesn't exists",
                                 QMessageBox::Ok);
        }else{
            if(destinationDir.size() != 0){
                DestinationDir.setPath(destinationDir);
                ui->DestinationDirAddress->setText(destinationDir);
            }else{
                QMessageBox::warning(this, "Error",
                                     "Destination directory cannot be empty",
                                     QMessageBox::Ok);
            }
        }
    }

    Client = new QUdpSocket(this);

    ActualFile = NULL;

    connected = false;

    qRegisterMetaType<QByteArray>("QByteArray");
    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<qint64>("qint64");

    connect(this, &MainWindow::SendS, &ReadF, &ReadFile::Read);
    connect(this, &MainWindow::NACK, &ReadF, &ReadFile::NACK);
    connect(&ReadF, &ReadFile::UpdateCurrentFileSizeRW, this, &MainWindow::UpdateCurrentSizeRW);
    connect(&ReadF, &ReadFile::UpdateCurrentSizeRW, this, &MainWindow::UpdateCurrentTotalSizeRW);
    connect(&ReadF, &ReadFile::UpdateTotalFileSize, this, &MainWindow::UpdateFileSize);
    connect(&ReadF, &ReadFile::UpdateTotalSize, this, &MainWindow::UpdateTotalSize);
    connect(&ReadF, &ReadFile::UpdateName, this, &MainWindow::UpdateName);
    connect(&ReadF, &ReadFile::Send, this, &MainWindow::Send);
    connect(&progressWindow, &ProgressWindow::Terminated, this, &MainWindow::TTerminated);

    ReadF.setWaitCondition(SendPause);
    ReadF.moveToThread(&RThread);
    RThread.start();

    connect(&LogIn, &Login::Name, this, &MainWindow::Name);
    connect(&LogIn, &Login::FinishNoName, this, [=](){
        this->close();
    });

    RecieveSeq = 0;

    Nack = false;
    TryRegister = false;

    db = QSqlDatabase::addDatabase("QSQLITE", "FILES");
    db.setDatabaseName("tableFile");
    if(db.open()){

        QSqlQuery query(db);
        if (!query.exec("CREATE TABLE IF NOT EXISTS files"
                   "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "Tipo VARCHAR(10),"
                   "Nombre VARCHAR(50),"
                   "Fecha DATE,"
                   "Hora DATETIME,"
                   "Tamaño INTEGER(64));")) {
            QMessageBox::information(this,"Error","CREATE",QMessageBox::Ok);
        }

        model = new QSqlTableModel(0,db);

        model->setTable("files");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setHeaderData(0, Qt::Horizontal, tr("Id"));
        model->setHeaderData(1, Qt::Horizontal, tr("Tipo"));
        model->setHeaderData(2, Qt::Horizontal, tr("Nombre"));
        model->setHeaderData(3, Qt::Horizontal, tr("Fecha"));
        model->setHeaderData(4, Qt::Horizontal, tr("Hora"));
        model->setHeaderData(5, Qt::Horizontal, tr("Tamaño"));
        ui->tableView->setModel(model);
        ui->tableView->hideColumn(0);
        model->select();

    }else{
        QMessageBox::warning(this,"Error","Can't open DataBase",QMessageBox::Ok);
    }

    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::sortHandler);
    connect(&ReadF, &ReadFile::insert, this, &MainWindow::Insert);
}

MainWindow::~MainWindow()
{    
    qint64 bytessended = Client->writeDatagram(QByteArray("Bye Server"),
                                               QHostAddress(ui->ServerAddress->text()),
                                               quint16(ui->ServerPort->value()));
    if( bytessended == -1){
        QMessageBox::warning(this, "Error",
                             Client->errorString(),
                             QMessageBox::Ok);
    }

    delete ui;
    delete Client;
    delete ActualFile;

    if(RThread.isRunning()){
        RThread.exit();
    }
}

void MainWindow::on_ConnectButton_clicked()
{
    if((ui->PortNumber->value() != ui->ServerPort->value())&&(QHostAddress::LocalHost != ui->ServerAddress->text())&&ServerAddOk){
        if(Client->state() == QAbstractSocket::BoundState){
            Client->close();
        }

        if(Client->bind(QHostAddress::LocalHost, ui->PortNumber->value())){
            connect(Client, &QUdpSocket::readyRead, this, &MainWindow::Read);
            qint64 bytessended = Client->writeDatagram(QByteArray("Hi Server"),
                                                       QHostAddress(ui->ServerAddress->text()),
                                                       quint16(ui->ServerPort->value()));
            if( bytessended == -1){
                QMessageBox::warning(this, "Error",
                                     Client->errorString(),
                                     QMessageBox::Ok);
            }else{
                ui->ConnectButton->setEnabled(false);
                ui->PortNumber->setEnabled(false);
                ui->ServerAddress->setEnabled(false);
                ui->ServerPort->setEnabled(false);
                ui->ConnectButton->setText("Connecting");
                ui->statusBar->showMessage(QString("Connecting to: %1::%2")
                                           .arg(Client->localAddress().toString())
                                           .arg(Client->localPort()));

                QTimer *CheckConnected = new QTimer(this);
                CheckConnected->setInterval(5000);

                connect(CheckConnected, &QTimer::timeout, this, [=](){
                    if(!connected){
                        ui->ConnectButton->setEnabled(true);
                        ui->PortNumber->setEnabled(true);
                        ui->ServerAddress->setEnabled(true);
                        ui->ServerPort->setEnabled(true);
                        ui->ConnectButton->setText("Connect");
                        ui->statusBar->showMessage("");

                        QMessageBox::warning(this, "Error",
                                             "Cannot connect with the server",
                                             QMessageBox::Ok);
                     }

                     CheckConnected->deleteLater();
                });

                CheckConnected->start();

            }
        }else{
            QMessageBox::warning(this, "Error",
                                 Client->errorString(), QMessageBox::Ok);
        }
    }else{
        if(ServerAddOk){
            QMessageBox::warning(this, "Error",
                                 "Cannot connect on the same address and port as the server",
                                 QMessageBox::Ok);
        }else{
            QMessageBox::warning(this, "Error",
                                 "Server address is not valid",
                                 QMessageBox::Ok);
        }
    }
}

void MainWindow::Read()
{
    while(Client->hasPendingDatagrams()){
        QNetworkDatagram datagram = Client->receiveDatagram();
        QByteArray data = datagram.data();

        if(data.startsWith("Connected client")){
            connected = true;
            QHostAddress sendDir = datagram.senderAddress();
            int sendPort = datagram.senderPort();
            ui->ConnectButton->setText("Connected");
            ui->ConnectButton->setEnabled(false);
            ui->PortNumber->setEnabled(false);
            ui->ServerAddress->setEnabled(false);
            ui->ServerPort->setEnabled(false);
            ui->statusBar->showMessage(QString("Connected to: %1::%2")
                                       .arg(sendDir.toString())
                                       .arg(sendPort), QMessageBox::Ok);
            if(TryRegister){
                QMessageBox::information(this, "Register",
                                         "Registered succesfully",
                                         QMessageBox::Ok);
            }
        }else if(data.startsWith("Need Auth")){
            connected = true;
            this->setEnabled(false);
            LogIn.show();
            LogIn.setEnabled(true);
        }else if(data.startsWith("You have been disconnected")){
            ui->ConnectButton->setText("Connect");
            ui->ConnectButton->setEnabled(true);
            ui->PortNumber->setEnabled(true);
            ui->ServerAddress->setEnabled(true);
            ui->ServerPort->setEnabled(true);
            ui->statusBar->showMessage(QString("You have been disconnected by HTTP Request")
                                       , QMessageBox::Ok);
            Client->close();
        }else if(data.startsWith("Cannot Auth")){
            ui->ConnectButton->setEnabled(true);
            ui->PortNumber->setEnabled(true);
            ui->ServerAddress->setEnabled(true);
            ui->ServerPort->setEnabled(true);
            ui->ConnectButton->setText("Connect");
            ui->statusBar->showMessage("");
            QMessageBox::warning(this, "Bad auth",
                                     "User or Password incorrect",
                                     QMessageBox::Ok);
        }else if(data.startsWith("Cannot Register")){
            ui->ConnectButton->setEnabled(true);
            ui->PortNumber->setEnabled(true);
            ui->ServerAddress->setEnabled(true);
            ui->ServerPort->setEnabled(true);
            ui->ConnectButton->setText("Connect");
            ui->statusBar->showMessage("");
            QMessageBox::warning(this, "Bad auth",
                                     "Cannot register now, try it again later",
                                     QMessageBox::Ok);
        }else if(data.startsWith("Cannot LogIn")){
            ui->ConnectButton->setEnabled(true);
            ui->PortNumber->setEnabled(true);
            ui->ServerAddress->setEnabled(true);
            ui->ServerPort->setEnabled(true);
            ui->ConnectButton->setText("Connect");
            ui->statusBar->showMessage("");
            QMessageBox::warning(this, "Bad auth",
                                     "Cannot login now, try it again later",
                                     QMessageBox::Ok);
        }else if(data.startsWith("Already LogIn")){
            ui->ConnectButton->setEnabled(true);
            ui->PortNumber->setEnabled(true);
            ui->ServerAddress->setEnabled(true);
            ui->ServerPort->setEnabled(true);
            ui->ConnectButton->setText("Connect");
            ui->statusBar->showMessage("");
            QMessageBox::warning(this, "Bad auth",
                                     "Cannot login, account already logged",
                                     QMessageBox::Ok);
        }else if(data.startsWith("Ready Clients")){
            ui->SourceDirAddress->setEnabled(false);
            ui->SourceFindDirButton->setEnabled(false);
            canUpdateDir = false;
            canUpdateDDir = false;
            emit SendS(SourceDir.absolutePath(), UserName);
        }else if(data.startsWith("Keep Alive?")){
            qint64 bytessended = Client->writeDatagram(QByteArray("Im OK"),
                                                       QHostAddress(ui->ServerAddress->text()),
                                                       quint16(ui->ServerPort->value()));
            if( bytessended == -1){
                QMessageBox::warning(this, "Error",
                                     Client->errorString(),
                                     QMessageBox::Ok);
            }
        }else if(data.startsWith("File Path")){
            if(ActualFile != NULL){
                if(progressWindow.getCurrentFileRW() != progressWindow.getTotalFileSize()){
                    QMessageBox::warning(this, "Error writing",
                                             "Last file was incomplete",
                                             QMessageBox::Ok);
                }
                ActualFile->close();
            }

            QByteArray dataPath(data);
            QString path(DestinationDir.absolutePath());
                    path.append("/").append(dataPath.remove(dataPath.lastIndexOf("/"),
                                            dataPath.size() - dataPath.lastIndexOf("/"))
                                    .remove(0, 11));
            QDir dir(path);

            if(!dir.exists()){
                dir.mkpath(path);
            }

            QByteArray dataSize(data);
            dataSize.remove(dataSize.lastIndexOf("Permision:")-1, data.size() - (dataSize.lastIndexOf("Permision:")-1))
                    .remove(0, dataSize.lastIndexOf("size:")+6);

            qint64 fileSize = dataSize.toLongLong();

            progressWindow.setCurrentFileRW(0);
            progressWindow.setTotalFileSize(fileSize);

            QString FilePermisions(data);
            QString dataFile(path);

            dataFile.append(data.remove(0, data.lastIndexOf("/")));
            dataFile.remove((dataFile.lastIndexOf("Total size:")-1), dataFile.size() - (dataFile.lastIndexOf("Total size:")-1));

            ActualFile = new QFile(dataFile);

            FilePermisions.remove(0, FilePermisions.lastIndexOf("Permision:")+10);

            QFile::Permissions permisions = ConvPermision(FilePermisions);

            ActualFile->setPermissions(permisions);

            progressWindow.setName(dataFile.remove(0, dataFile.lastIndexOf("/")+1));

            QDateTime now = QDateTime::currentDateTime();
            QSqlQuery query(db);

            query.prepare("INSERT INTO files(Tipo,Nombre,Fecha,Hora,Tamaño)"
                          "VALUES('Recibido',:name,:date,:time,:size)");

            query.bindValue(":name", dataFile);
            query.bindValue(":date", now.date().toString("dd-MM-yyyy"));
            query.bindValue(":time", now.time().toString());
            query.bindValue(":size", fileSize);

            if(!query.exec()){
                QMessageBox::information(this,"Error",query.lastError().databaseText(),QMessageBox::Ok);
            }else{
                model->select();
            }

            if(ActualFile->open(QIODevice::WriteOnly)){

            }else{
                QMessageBox::warning(this, "Cannot open a file",
                                         ActualFile->errorString(),
                                         QMessageBox::Ok);
            }
        }else if(data.startsWith("Directory size")){
            if(!isReceiving){
                isReceiving = true;
                canUpdateDDir = false;
                canUpdateDir = false;

                this->setEnabled(false);

                progressWindow.setWindowTitle("Receiving Progress");
                progressWindow.show();
                progressWindow.setEnabled(true);

                qint64 TotalSize = data.remove(0, data.indexOf(":")+1).toLongLong();

                progressWindow.setTotalSize(TotalSize);
                progressWindow.setCurrentTotalRW(4096);
            }

        }else if(data.startsWith("Add directory")){
            progressWindow.setCurrentTotalRW(progressWindow.getCurrentTotalRW()+4096);
        }else if(data.startsWith("Sended")){
            RecieveSeq = 0;
            if(ActualFile != NULL){
                ActualFile->close();
            }
        }else if(data.startsWith("NACK Seq:")){
            emit NACK(data);
        }else if(data.startsWith("File Completed")){
            SendPause.wakeAll();
        }else if(data.startsWith("Seq:")){
            if(ActualFile->exists()){
                if(ActualFile->isWritable()){
                    QString Seq(data);
                    Seq.remove(data.indexOf("/"), data.size());
                    Seq.remove(0, Seq.indexOf(":")+1);
                    data.remove(0, data.indexOf("/")+1);

                    if(RecieveSeq == Seq.toLongLong()){
                        if(Nack){
                            Nack = false;
                        }

                        for(int i=0; i<PacketBuffer.size(); i++){
                            if(PacketBuffer[i].second == RecieveSeq){
                                PacketBuffer.remove(i);
                            }
                        }

                        RecieveSeq++;

                        qint64 writeBytes = ActualFile->write(data);

                        if(writeBytes != data.size()){
                            QMessageBox::warning(this, "Bad write",
                                                 "Error ocurred while writing",
                                                 QMessageBox::Ok);
                        }else{
                            progressWindow.setCurrentFileRW(progressWindow.getCurrentFileRW()+writeBytes);
                            progressWindow.setCurrentTotalRW(progressWindow.getCurrentTotalRW()+writeBytes);

                            if(progressWindow.getCurrentFileRW() == progressWindow.getTotalFileSize()){
                                qint64 bytessended = Client->writeDatagram(QByteArray("File Completed"),
                                                                           QHostAddress(ui->ServerAddress->text()),
                                                                           quint16(ui->ServerPort->value()));
                                if( bytessended == -1){
                                    QMessageBox::warning(this, "Error",
                                                         Client->errorString(),
                                                         QMessageBox::Ok);
                                }
                            }
                        }
                    }else{
                        QByteArray result("");

                        if(Nack){
                            for(int i=0; i<PacketBuffer.size(); i++){
                                if(PacketBuffer[i].second == Seq.toLongLong()){
                                    result = PacketBuffer[i].first;
                                    PacketBuffer.remove(i);
                                }
                            }
                        }

                        if(!result.size()){
                            if(PacketBuffer.size()<1500){
                                PacketBuffer.push_back(QPair<QByteArray, qint64>(data, Seq.toLongLong()));
                            }else{
                                if(!Nack){
                                    Nack = true;
                                    qint64 bytessended = Client->writeDatagram(QByteArray("NACK Seq:")
                                                                               .append(QByteArray().setNum(RecieveSeq)),
                                                                               QHostAddress(ui->ServerAddress->text()),
                                                                               quint16(ui->ServerPort->value()));

                                    if( bytessended == -1){
                                        QMessageBox::warning(this, "Error",
                                                             Client->errorString(),
                                                             QMessageBox::Ok);
                                    }
                                }
                            }
                        }else{
                            if(Nack){
                                Nack = false;
                            }
                            RecieveSeq++;

                            qint64 writeBytes = ActualFile->write(data);

                            if(writeBytes != data.size()){
                                QMessageBox::warning(this, "Bad write",
                                                     "Error ocurred while writing",
                                                     QMessageBox::Ok);
                            }else{
                                progressWindow.setCurrentFileRW(progressWindow.getCurrentFileRW()+writeBytes);
                                progressWindow.setCurrentTotalRW(progressWindow.getCurrentTotalRW()+writeBytes);

                                if(progressWindow.getCurrentFileRW() == progressWindow.getTotalFileSize()){
                                    qint64 bytessended = Client->writeDatagram(QByteArray("File Completed"),
                                                                               QHostAddress(ui->ServerAddress->text()),
                                                                               quint16(ui->ServerPort->value()));
                                    if( bytessended == -1){
                                        QMessageBox::warning(this, "Error",
                                                             Client->errorString(),
                                                             QMessageBox::Ok);
                                    }
                                }
                            }
                        }
                    }
                }else{
                    QMessageBox::warning(this, "Bad write",
                                             "Cannot write in the file",
                                             QMessageBox::Ok);
                }
            }else{
                QMessageBox::warning(this, "Bad write",
                                         "File doesn't exist",
                                         QMessageBox::Ok);
            }
        }
    }
}

void MainWindow::on_SendFileButton_clicked()
{
    if(ui->SourceDirAddress->text().size() != 0 && connected){
        qint64 bytessended = Client->writeDatagram(QByteArray("Ready Send, dest: ")
                                                   .append(QByteArray().setNum(ui->DestNumber->value())),
                                                   QHostAddress(ui->ServerAddress->text()),
                                                   quint16(ui->ServerPort->value()));
        if( bytessended == -1){
            QMessageBox::warning(this, "Error",
                                 Client->errorString(),
                                 QMessageBox::Ok);
        }else{
            ui->DestNumber->setEnabled(false);
            ui->SendFileButton->setEnabled(false);
            ui->SourceDirAddress->setEnabled(false);
            ui->SourceFindDirButton->setEnabled(false);
        }
    }else{
        if(connected){
            QMessageBox::warning(this, "Error",
                                 "There isn't source directory",
                                 QMessageBox::Ok);
        }else{
            QMessageBox::warning(this, "Error",
                                 "Client not connected with the server yet",
                                 QMessageBox::Ok);
        }
    }
}

void MainWindow::on_SourceFindDirButton_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this, "Select a directory",
                                                         SourceDir.absolutePath());

    if((filename != "")&&(canUpdateDir)){
        SourceDir.setPath(filename);
        ui->SourceDirAddress->setText(filename);
    }
}

void MainWindow::on_DestinationFindDirAddress_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this, "Select a directory",
                                                         DestinationDir.absolutePath());

    if((filename != "")&&(canUpdateDDir)){
        DestinationDir.setPath(filename);
        ui->DestinationDirAddress->setText(filename);
    }
}

void MainWindow::on_SourceDirAddress_editingFinished()
{
    QDir dir(ui->SourceDirAddress->text());

    if(!dir.exists()){
        QMessageBox::warning(this, "Error",
                             "Directory doesn't exists",
                             QMessageBox::Ok);
    }else{
        if(ui->SourceDirAddress->text().size() != 0){
            SourceDir.setPath(ui->SourceDirAddress->text());
        }else{
            QMessageBox::warning(this, "Error",
                                 "Source directory cannot be empty",
                                 QMessageBox::Ok);
        }
    }
}

void MainWindow::on_DestinationDirAddress_editingFinished()
{
    QDir dir(ui->DestinationDirAddress->text());

    if(!dir.exists()){
        QMessageBox::warning(this, "Error",
                             "Directory doesn't exists",
                             QMessageBox::Ok);
    }else{
        if(ui->DestinationDirAddress->text().size() != 0){
            DestinationDir.setPath(ui->DestinationDirAddress->text());
        }else{
            QMessageBox::warning(this, "Error",
                                 "Destination directory cannot be empty",
                                 QMessageBox::Ok);
        }
    }
}

void MainWindow::UpdateCurrentTotalSizeRW(qint64 size)
{
    progressWindow.setCurrentTotalRW(progressWindow.getCurrentTotalRW() + size);
}

void MainWindow::UpdateCurrentSizeRW(qint64 size)
{
    progressWindow.setCurrentFileRW(progressWindow.getCurrentFileRW() + size);
}

void MainWindow::UpdateTotalSize(qint64 size)
{
    progressWindow.setTotalSize(size);

    this->setEnabled(false);

    progressWindow.setWindowTitle("Sending Progress");
    progressWindow.show();
    progressWindow.setEnabled(true);
    progressWindow.setCurrentTotalRW(4096);
}

void MainWindow::UpdateFileSize(qint64 size)
{
    progressWindow.setTotalFileSize(size);
    progressWindow.setCurrentFileRW(0);
}

void MainWindow::UpdateName(QString name)
{
    progressWindow.setName(name);
}

void MainWindow::Send(QByteArray out)
{
    qint64 bytessended = Client->writeDatagram(out, QHostAddress(ui->ServerAddress->text()),
                                               quint16(ui->ServerPort->value()));

    if( bytessended == -1){
        QMessageBox::warning(this, "Error",
                             Client->errorString(),
                             QMessageBox::Ok);
    }
}

void MainWindow::TTerminated()
{
    this->setEnabled(true);
    if(isReceiving){
        isReceiving = false;
    }

    ui->SourceDirAddress->setEnabled(true);
    ui->SourceFindDirButton->setEnabled(true);
    ui->DestNumber->setEnabled(true);
    ui->SendFileButton->setEnabled(true);
    canUpdateDir = true;
    canUpdateDDir = true;
    QSqlQuery queryExec(db);
    for(auto query: Querys){
        if(!queryExec.exec(query)){
            QMessageBox::information(this,"Error",queryExec.lastError().databaseText(),QMessageBox::Ok);
        }
    }
    model->select();
}

void MainWindow::Name(QChar option, QString name, QString pass)
{
    UserName = name;
    qint64 bytessended;

    if(option == 'L'){
        bytessended = Client->writeDatagram(QByteArray("LogIn: ").append(name)
                                                   .append("/").append(pass),
                                                   QHostAddress(ui->ServerAddress->text()),
                                                   quint16(ui->ServerPort->value()));
    }else if(option == 'R'){
        TryRegister = true;
        bytessended = Client->writeDatagram(QByteArray("Register: ").append(name)
                                                   .append("/").append(pass),
                                                   QHostAddress(ui->ServerAddress->text()),
                                                   quint16(ui->ServerPort->value()));
    }

    if( bytessended == -1){
        QMessageBox::warning(this, "Error",
                             Client->errorString(),
                             QMessageBox::Ok);
    }

    this->setEnabled(true);
}

QFileDevice::Permissions MainWindow::ConvPermision(QString perm)
{
    QFile::Permissions permisions;

    if(perm[0] == "r"){
        permisions |= QFile::ReadOwner;
    }

    if(perm[1] == "w"){
        permisions |= QFile::WriteOwner;
    }

    if(perm[2] == "x"){
        permisions |= QFile::ExeOwner;
    }

    if(perm[3] == "r"){
        permisions |= QFile::ReadGroup;
    }

    if(perm[4] == "w"){
        permisions |= QFile::WriteGroup;
    }

    if(perm[5] == "x"){
        permisions |= QFile::ExeGroup;
    }

    if(perm[6] == "r"){
        permisions |= QFile::ReadOther;
    }

    if(perm[7] == "w"){
        permisions |= QFile::WriteOther;
    }

    if(perm[8] == "x"){
        permisions |= QFile::ExeOther;
    }

    return permisions;
}

void MainWindow::on_ServerAddress_editingFinished()
{
    QString address(ui->ServerAddress->text());
    int C1, C2, C3, C4;
    int I1, I2, I3;

    I1 = address.indexOf(".");
    I2 = address.indexOf(".", I1+1);
    I3 = address.indexOf(".", I2+1);

    if((I1 == -1)||(I2 == -1)||(I3 == -1)){
        ServerAddOk = false;
        QMessageBox::warning(this, "Server Address", "Server address isn't valid", QMessageBox::Ok);
    }else{
        QString add(address);
        C1 = add.remove(I1, address.size()).toInt();
        add = address;
        C2 = add.remove(I2, address.size()).remove(0, I1).toInt();
        add = address;
        C3 = add.remove(I3, address.size()).remove(0, I2).toInt();
        add = address;
        C4 = add.remove(0, I3+1).toInt();

        if((C1 >= 0)&&(C1 <= 255)&&(C2 >= 0)&&(C2 <= 255)&&(C3 >= 0)&&(C3 <= 255)&&(C4 >= 0)&&(C4 <= 255)){
            ServerAddOk = true;
        }else{
            ServerAddOk = false;
            QMessageBox::warning(this, "Server Address", "Server address isn't valid", QMessageBox::Ok);
        }
    }
}

void MainWindow::Insert(QString name, qint64 size)
{
    QDateTime now = QDateTime::currentDateTime();

    Querys.push_back(QString("INSERT INTO files(Tipo,Nombre,Fecha,Hora,Tamaño) VALUES('Enviado',")
               .append("'").append(name).append("',")
               .append("'").append(now.date().toString("dd-MM-yyyy")).append("',")
               .append("'").append(now.time().toString()).append("',")
               .append(QByteArray().setNum(size)).append(");"));
}

void MainWindow::sortHandler(int index)
{
    model->setSort(index, static_cast<QHeaderView*>(sender())->sortIndicatorOrder());
    model->select();
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
                  ("Client",QVector<QPair<QString,QString>>
                  (1,QPair<QString,QString>("port",QString().setNum(ui->PortNumber->value())))));

    data.push_back(QPair<QString,QVector<QPair<QString,QString> > >
                  ("Server",QVector<QPair<QString,QString>>
                  (1,QPair<QString,QString>("address",ui->ServerAddress->text()))));

    data[1].second.push_back(QPair<QString,QString>("port",QString().setNum(ui->ServerPort->value())));

    data.push_back(QPair<QString,QVector<QPair<QString,QString> > >
                  ("Directories",QVector<QPair<QString,QString>>
                  (1,QPair<QString,QString>("source",SourceDir.absolutePath()))));

    data[2].second.push_back(QPair<QString,QString>("destination",DestinationDir.absolutePath()));

    if(Configurationini.WriteConfigFile(data)){
        QMessageBox::warning(this, "Error",
                             "Error exporting Config file",
                             QMessageBox::Ok);
    }else{
        QMessageBox::warning(this, "Success",
                             "Configuration exported",
                             QMessageBox::Ok);
    }
}

void MainWindow::setConfigFile(QString fileUrl)
{
    if(Configurationini.ReadConfigFile(fileUrl)){
        QMessageBox::warning(this, "Error",
                             "Error importing Config file",
                             QMessageBox::Ok);
    }else{
        QString tmp;
        tmp = Configurationini.getValue("Client","port");
        if(tmp != "Not Found") ui->PortNumber->setValue(tmp.toShort());
        tmp = Configurationini.getValue("Server","port");
        if(tmp != "Not Found") ui->ServerPort->setValue(tmp.toShort());
        tmp = Configurationini.getValue("Server","address");
        if(tmp != "Not Found") ui->ServerAddress->setText(tmp);
        tmp = Configurationini.getValue("Directories","source");
        if(tmp != "Not Found"){
            QDir dir(tmp);

            if(!dir.exists()){
                QMessageBox::warning(this, "Error",
                                     "Directory doesn't exists",
                                     QMessageBox::Ok);
            }else{
                if(tmp.size() != 0){
                    SourceDir.setPath(tmp);
                    ui->SourceDirAddress->setText(tmp);
                }else{
                    QMessageBox::warning(this, "Error",
                                         "Destination directory cannot be empty",
                                         QMessageBox::Ok);
                }
            }
        }
        tmp = Configurationini.getValue("Directories","destination");
        if(tmp != "Not Found"){
            QDir dir(tmp);

            if(!dir.exists()){
                QMessageBox::warning(this, "Error",
                                     "Directory doesn't exists",
                                     QMessageBox::Ok);
            }else{
                if(tmp.size() != 0){
                    DestinationDir.setPath(tmp);
                    ui->DestinationDirAddress->setText(tmp);
                }else{
                    QMessageBox::warning(this, "Error",
                                         "Destination directory cannot be empty",
                                         QMessageBox::Ok);
                }
            }
        }
    }
}
