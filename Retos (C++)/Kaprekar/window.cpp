#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    setWindowTitle("Kaprekar");
}

Window::~Window()
{
    delete ui;
}

int Window::Calculate(int input)
{
    int v1 = input, v2 = 0, res = 0, count = 0;
    while(res != 6174) {
        QString* tmp = new QString(); tmp->setNum(v1);
        while(tmp->size() < 4) { tmp->push_front('0'); }
        QVector<int> vector;
        for(int i=0; i<tmp->size(); i++) { vector.push_back(QChar::digitValue(tmp->at(i).unicode())); }
        int min = std::numeric_limits<int>::max();
        int max = std::numeric_limits<int>::min();
        for(int i=0; i<vector.size(); i++) {
            if(vector[i] < min){ min = vector[i];}
            if(vector[i] > max){ max = vector[i];}
        }
        QVector<int> counted(max-min+1, 0);
        for (int i=0;i<vector.size();i++) {
            counted[vector[i]-min]++;
        }
        int outputindex=0;
        for (int j=0;j<max-min+1;j++) {
            while (counted[j]--)
                vector[outputindex++] = j+min;
        }
        v1 = vector[0]*1000 + vector[1]*100 + vector[2]*10 + vector[3];
        v2 = vector[3]*1000 + vector[2]*100 + vector[1]*10 + vector[0];
        if(v1 > v2) {
            res = v1-v2;
        }else{
            res = v2-v1;
        }
        v1 = res;
        if(res == 0) {
            count = 0;
            break;
        }
        count++;
    }
    return count;
}

void Window::on_run_clicked()
{
    int input = this->ui->input->value();
    QString* text = new QString();
    bool found = false;
    text->setNum(input);
    for(int i=0; i<text->size(); i++) {
        if(text->at(0) != text->at(i) || (text->size() < 4 && !text->contains('0'))) {
            int result = Calculate(input);
            text->setNum(result);
            this->ui->result->setText("Number of iterations: " + *text);
            found = true;
            break;
        }
    }
    if(!found) {
        this->ui->result->setText("Invalid input number");
    }
}
