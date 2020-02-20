#include <QMessageBox>
#include <QSettings>

#include "aboutdialog.h"
#include "settingsdialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow),
    IsConnected_(false),
    process_(this)
{
    ui->setupUi(this);

    connect(&process_, SIGNAL(finished(int,QProcess::ExitStatus)),SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(&process_, SIGNAL(readyReadStandardOutput()),SLOT(processReadyReadStandardOutput()));
    connect(&process_, SIGNAL(error(QProcess::ProcessError)), SLOT(processError(QProcess::ProcessError)));
}

MainWindow::~MainWindow()
{
    process_.disconnect();
    delete ui;
}

void MainWindow::on_ExitButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_ConectButton_clicked()
{
    if(IsConnected_){
        process_.terminate();
        ui->ConectButton->setText("Conectar");
        IsConnected_=false;
    }else{
        QSettings settings;
        QString talkPath = settings.value("talkPath", "").toString();
        bool ServerMode = settings.value("ServerMode", false).toBool();
        QString ServerAddres = settings.value("ServerAddres", "127.0.0.1").toString();
        QString port = settings.value("Port", 6000).toString();
        QString Username = settings.value("Username").toString();

        QStringList arguments;
        if(ServerMode)
            arguments.append("-s");
        else
            arguments.append("-c " + ServerAddres);
        arguments.append("-p " + port);
        if (!Username.isEmpty())
            arguments.append("-u " + Username);

        process_.start(talkPath, arguments);
        ui->ConectButton->setText("Desconectar");
        IsConnected_=true;
    }
}

void MainWindow::on_AboutButton_clicked()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_InputText_returnPressed()
{
    QString line = ui->InputText->text();
    ui->OutputText->appendPlainText(line);
    line += '\n';
    process_.write(line.toLocal8Bit());
    ui->InputText->clear();
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->ConectButton->setText("Conectar");
    IsConnected_=false;
}

void MainWindow::processReadyReadStandardOutput()
{
    while(process_.canReadLine()){
        QString line = process_.readLine();
        line.truncate(line.length() - 1);
        ui->OutputText->appendPlainText(line);
    }
}

void MainWindow::processError(QProcess::ProcessError error)
{
    QMessageBox::critical(this, "Talk GUI", "Error con Talk.\n" + process_.errorString());
}


void MainWindow::on_ConfButton_clicked()
{
    SettingsDialog dialog;
    dialog.exec();
}
