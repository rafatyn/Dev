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

private:
    Ui::Login *ui;

    //Var comprobacion
    bool Ok;

protected:
    //Sobreescribir
    void closeEvent(QCloseEvent *event) override;

signals:

    //Salida normal
    void Name(QString name);

    //Salida cerrar programa
    void FinishNoName();
};

#endif // LOGIN_H
