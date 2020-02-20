#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    Ok = false;
}

Login::~Login()
{
    delete ui;
}

void Login::on_LogInButton_clicked()
{
    if(ui->NameEdit->text() != ""){
        emit Name(ui->NameEdit->text());
        Ok = true;
        this->close();
    }else{
        QMessageBox::warning(this, "Error", "You must introduce a name", QMessageBox::Ok);
    }
}

void Login::closeEvent(QCloseEvent *event)
{
    if(!Ok){
        emit FinishNoName();
    }
    QMainWindow::closeEvent(event);
}

void Login::on_NameEdit_returnPressed()
{
    if(ui->NameEdit->text() != ""){
        emit Name(ui->NameEdit->text());
        Ok = true;
        this->close();
    }else{
        QMessageBox::warning(this, "Error", "You must introduce a name", QMessageBox::Ok);
    }
}
