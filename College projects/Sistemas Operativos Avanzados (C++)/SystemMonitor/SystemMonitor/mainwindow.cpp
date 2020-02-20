#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hilo(new MyThread(sensorqueue, mutex))
{
    ui->setupUi(this);

    connect(this, &MainWindow::RequestDelThread, hilo, &MyThread::exitWhile);
    connect(hilo, &MyThread::QueueEmpty, this, &MainWindow::updateSensor);
    hilo->start();

    fivesectimer.setInterval(5000);
    fivesectimer.start();

    connect(&fivesectimer, &QTimer::timeout, this, &MainWindow::updateProcess);
    ui->ProcessTree->sortByColumn(1, Qt::AscendingOrder);
    updateProcess();

    qRegisterMetaType<QByteArray>("QByteArray");
    qRegisterMetaType<QString>("QString");

    connect(&LW, &LshwWorker::Readed, this, &MainWindow::updateHardware);
    connect(this, &MainWindow::RequestLshw, &LW, &LshwWorker::exec);
    LW.moveToThread(&lshw);
    lshw.start();

    connect(&CPUI, &CpuInfo::Readed, this, &MainWindow::updateCpuInfo);
    connect(this, &MainWindow::RequestCpuInfo, &CPUI, &CpuInfo::exec);
    CPUI.moveToThread(&CpuIf);
    CpuIf.start();

    connect(&NS, &NetStat::Readed, this, &MainWindow::updateNetStat);
    connect(this, &MainWindow::RequestNetStat, &NS, &NetStat::exec);
    NS.moveToThread(&NetST);
    NetST.start();

    connect(&USR, &Users::Readed, this, &MainWindow::updateUsers);
    connect(this, &MainWindow::RequestUsers, &USR, &Users::exec);
    USR.moveToThread(&UserW);
    UserW.start();

    emit RequestLshw();
    emit RequestCpuInfo();
    emit RequestNetStat();
    emit RequestUsers();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete hilo;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit RequestDelThread();
    hilo->wait();
    QMainWindow::closeEvent(event);
}

void MainWindow::updateSensor()
{
    mutex.lock();

    QString name = sensorqueue[0];
    sensorqueue.pop_front();

    mutex.unlock();

    QString aux = name;
    int pos = name.indexOf("\n");
    name.remove(pos-1,name.size());

    QLabel *actlabel = nullptr;
    for(auto label: ui->SensorsLayout->findChildren<QLabel *> ()){
            if(label->text().startsWith(name)){
                actlabel = label;
            }
    }

    if(actlabel!=nullptr){
        actlabel->setText(aux);
    }else{
        QLabel* x = new QLabel(aux);
        ui->VSLayout->addWidget(x);
    }
}

void MainWindow::updateProcess()
{
    QString parentpath("/proc");
    QDir processdir(parentpath);
    QStringList filter;
    filter << "[0-9]*";

    for(auto process: processdir.entryList(filter)){
        QFutureWatcher<Proc> *fwres = new QFutureWatcher<Proc>(this);
        QObject::connect(fwres, &QFutureWatcher<Proc>::finished, this, &MainWindow::addProcessQueue);
        QFuture<Proc> fres = QtConcurrent::run(this, &MainWindow::processProp, parentpath, process);
        fwres->setFuture(fres);
    }
}

MainWindow::Proc MainWindow::processProp(QString path, QString processPID)
{
    QString processpath = QString("%1/%2").arg(path).arg(processPID);
    QStringList files;
    files.append(QString("%1/cmdline").arg(processpath));
    files.append(QString("%1/status").arg(processpath));

    Proc result;
    result.ProcPID = processPID;

    for(auto filess: files){
        QFile file(filess);
        if(file.open(QIODevice::ReadOnly)){
            while(true){
                QByteArray s = file.readLine();

                if(s.startsWith("Name:")){
                    result.Stats.Name = QString(s).remove(0,6).remove(result.Stats.Name.size()-1,1);
                }else if(s.startsWith("State:")){
                    result.Stats.State = QString(s).remove(0,7).remove(result.Stats.State.size()-1,1);
                }else if(s.startsWith("Threads:")){
                    result.Stats.Threads = QString(s).remove(0,9).remove(result.Stats.Threads.size()-1,1);
                }else if(s.startsWith("PPid:")){
                    result.Stats.PPid = QString(s).remove(0,6).remove(result.Stats.PPid.size()-1,1);
                }else if(s.startsWith("Cpus_allowed_list:")){
                    result.Stats.CPUAll = QString(s).remove(0,19).remove(result.Stats.CPUAll.size()-1,1);
                }else if(s.startsWith("/")){
                    s.replace('\000',"");
                    result.Cmd = QString(s);
                }else if(s == "") {
                    break;
                }
            }
        }
    }

    return result;
}

void MainWindow::addProcessQueue()
{
    QFutureWatcher<Proc> *watcher = static_cast< QFutureWatcher<Proc>* >(sender());
    if(watcher){
        QFuture<Proc> future = watcher->future();
        Proc result = future.result();
        watcher->deleteLater();

        QList<QTreeWidgetItem *> items = ui->ProcessTree->findItems(result.ProcPID, Qt::MatchFixedString, 1);
        QTreeWidgetItem *process;

        QTimer *timeout;
        if(!items.isEmpty()){
            process = new QTreeWidgetItem();

            for(auto it: delUptdate){
                if(it.first == result.ProcPID){
                    timeout = it.second;
                }
            }
        }else{
            process = new QTreeWidgetItem(ui->ProcessTree);

            timeout = new QTimer();
            timeout->setInterval(7000);
            timeout->setSingleShot(true);
            delUptdate.push_back(QPair<QString,QTimer*>(result.ProcPID,timeout));

            connect(timeout, &QTimer::timeout, this, [=]() {
                delete process;
                timeout->deleteLater();
            });
        }

        process->setText(0,result.Stats.Name);
        process->setText(1,result.ProcPID);

        QTreeWidgetItem *processCmdLine = new QTreeWidgetItem();
        processCmdLine->setText(0,"CmdLine");
        processCmdLine->setText(1,result.Cmd);

        QTreeWidgetItem *processPPid = new QTreeWidgetItem();
        processPPid->setText(0,"Parent Process");
        processPPid->setText(1,result.Stats.PPid);

        QTreeWidgetItem *processState = new QTreeWidgetItem();
        processState->setText(0,"State");
        processState->setText(1,result.Stats.State);

        QTreeWidgetItem *processThreads = new QTreeWidgetItem();
        processThreads->setText(0,"Threads");
        processThreads->setText(1,result.Stats.Threads);

        QTreeWidgetItem *processCpu = new QTreeWidgetItem();
        processCpu->setText(0,"Allowed CPUs");
        processCpu->setText(1,result.Stats.CPUAll);

        process->addChild(processCmdLine);
        process->addChild(processPPid);
        process->addChild(processState);
        process->addChild(processThreads);
        process->addChild(processCpu);

        if(!items.isEmpty()){
            items[0] = process;
        }

        timeout->start();
    }
}

void MainWindow::updateHardware(QByteArray out)
{
    if(out.startsWith("Lshw error")){
        QMessageBox::warning(this, "Error", out , QMessageBox::Ok);
        ui->HardwareTree->deleteLater();
        ui->HardwareLabel->setText("Cannot run Lshw");
    }else{
        ui->HardwareLabel->deleteLater();
        QJsonModel* model = new QJsonModel(this);
        model->loadJson(out);
        ui->HardwareTree->setModel(model);
    }
}

void MainWindow::updateCpuInfo(QString out)
{
    if(out.startsWith("Cpu Info error")){
        QMessageBox::warning(this, "Error", out , QMessageBox::Ok);
        ui->CpuLabel->setText("Cannot read Cpu Info");
    }else{
        ui->CpuLabel->setText(out);
    }
}

void MainWindow::updateNetStat(QString out)
{
    if(out.startsWith("Netstat error")){
        QMessageBox::warning(this, "Error", out , QMessageBox::Ok);
        ui->TcpLabel->setText("Cannot run Netstat");
        ui->UdpLabel->setText("Cannot run Netstat");
        ui->UnixLabel->setText("Cannot run Netstat");
    }else if(out.contains("tcp",Qt::CaseInsensitive)){
        ui->TcpLabel->setText(out);
    }else if(out.contains("udp",Qt::CaseInsensitive)){
        ui->UdpLabel->setText(out);
    }else if(out.contains("unix",Qt::CaseInsensitive)){
        ui->UnixLabel->setText(out);
    }
}

void MainWindow::updateUsers(QString out)
{
    if(out.startsWith("Users error")){
        QMessageBox::warning(this, "Error", out , QMessageBox::Ok);
        ui->UsersLabel->setText("Cannot run W");
    }else{
        QString aux = QString("%1 %2").arg(ui->UsersLabel->text()).arg(out);
        ui->UsersLabel->setText(aux);
    }
}
