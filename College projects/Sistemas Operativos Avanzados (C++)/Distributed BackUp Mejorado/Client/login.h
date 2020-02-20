#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    //Slots continuar
    void on_LogInButton_clicked();
    void on_NameEdit_returnPressed();

    void on_RegisterButton_clicked();

    void on_PassEdit_returnPressed();

private:
    Ui::Login *ui;

    //Var comprobacion
    bool Ok;

    void check(QChar option);

protected:
    //Sobreescribir
    void closeEvent(QCloseEvent *event) override;

signals:

    //Salida normal
    void Name(QChar option, QString name, QString pass);

    //Salida cerrar programa
    void FinishNoName();
};

#endif // LOGIN_H
