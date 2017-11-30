#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    QString text = this->ui->text->text();
    QString decoded;
    if(text.size() > 0) {
        int ascii_p = 'p';
        int ascii_first = text.at(0).toLatin1();
        int desp = ascii_first - ascii_p;
        for(int i=1;i<text.size();i++){
            int ascii = static_cast<int>(text.at(i).toLatin1());
            if(!(ascii < 65 || ascii > 122 || (ascii < 97 && ascii > 90))) {
                ascii -= desp;
                if(ascii < 65) { ascii = 91-(65-ascii); }
                if(ascii > 122) { ascii = 96+(ascii-122); }
                if(ascii < 97 && ascii > 90) {
                    if(desp > 0) { ascii = 123-(97-ascii); }
                    else { ascii = 64+(ascii-90); }
                }
            }
            decoded.append(static_cast<char>(ascii));
        }
        this->ui->result->setText(decoded);
        if(decoded.toLower() == "fin" || decoded == "FIN") {
            this->close();
        }
    }
}
