#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    Ok = false;

    QIcon icon("../Client/data/32x32/Client.png");
    this->setWindowIcon(icon);

    ui->PassEdit->setEchoMode(QLineEdit::Password);
    ui->PassEdit->setInputMethodHints(Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}

Login::~Login()
{
    delete ui;
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
    check('L');
}

void Login::on_PassEdit_returnPressed()
{
    check('L');
}

void Login::on_LogInButton_clicked()
{
    check('L');
}

void Login::on_RegisterButton_clicked()
{
    check('R');
}

void Login::check(QChar option)
{
    if(ui->NameEdit->text() != "" && ui->PassEdit->text() != ""){
        emit Name(option, ui->NameEdit->text(), ui->PassEdit->text());
        ui->PassEdit->setText("");
        Ok = true;
        this->close();
    }else{
        QMessageBox::warning(this, "Error", "You must introduce a name and password", QMessageBox::Ok);
    }
}

