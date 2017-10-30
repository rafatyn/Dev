#include "progresswindow.h"
#include "ui_progresswindow.h"

ProgressWindow::ProgressWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgressWindow)
{
    ui->setupUi(this);
    FileSize = 0;
    CurrentFileRW = 0;
    TotalSize = 0;
    CurrentTotalRW = 0;
    Name = "";

    QIcon icon("../Client/data/32x32/Client.png");
    this->setWindowIcon(icon);
}

ProgressWindow::~ProgressWindow()
{
    delete ui;
}

void ProgressWindow::setName(QString name)
{
    Name = name;
    ui->FileNameLabel->setText(Name);
}

void ProgressWindow::setTotalFileSize(qint64 size)
{
    FileSize = size;
    ui->TotalFileBytesLabel->setText(QString().setNum(size));
    ui->FileProgressBar->setRange(0, size);
}

void ProgressWindow::setCurrentFileRW(qint64 size)
{
    CurrentFileRW = size;
    ui->FileBytesRWLabel->setText(QString().setNum(size));
    ui->FileProgressBar->setValue(size);
}

void ProgressWindow::setTotalSize(qint64 size)
{
    TotalSize = size;
    ui->TotalBytesLabel->setText(QString().setNum(size));
    ui->TotalProgressBar->setRange(0, size);
}

void ProgressWindow::setCurrentTotalRW(qint64 size)
{
    CurrentTotalRW = size;
    ui->TotalBytesRWlabel->setText(QString().setNum(size));
    ui->TotalProgressBar->setValue(size);

    if(CurrentTotalRW == TotalSize){
        QMessageBox::information(this, "Finish", "The transmision has finished", QMessageBox::Ok);
        this->close();
        emit Terminated();
    }
}
