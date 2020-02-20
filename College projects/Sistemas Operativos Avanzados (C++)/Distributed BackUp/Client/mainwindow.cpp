#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
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

    QTimer *time = new QTimer();
    time->setInterval(1);
    connect(time, &QTimer::timeout, this, [=](){
        this->setEnabled(false);
        LogIn.show();
        LogIn.setEnabled(true);

        time->deleteLater();
    });

    time->start();

    RecieveSeq = 0;

    Nack = false;

    perder = true;
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

                    if(RecieveSeq == Seq.toLongLong() && (RecieveSeq != 10013 || !perder)){
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
                        perder = false;
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
}

void MainWindow::Name(QString name)
{
    UserName = name;
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
