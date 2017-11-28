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

bool Window::isDiabolic(int size, int *matrix, int* sum)
{
    int sum_col = 0, sum_row = 0, cur_col, cur_row, sum_dig1 = 0, sum_dig2 = 0;
    for(int i=0; i<size; i++) {
        cur_col = 0;
        for(int j=0; j<size; j++) {
            cur_col += matrix[j*size + i];
        }
        if(i==0) {
            sum_col = cur_col;
        }else if(cur_col != sum_col) {
            return false;
        }
    }
    for(int i=0; i<size; i++) {
        cur_row = 0;
        for(int j=0; j<size; j++) {
            cur_row += matrix[i*size + j];
        }
        if(i==0) {
            sum_row = cur_row;
        }else if(cur_row != sum_row) {
            return false;
        }
    }
    if(sum_col != sum_row) { return false; }
    for(int i=0; i<size; i++) {
        sum_dig1 += matrix[i*size + i];
        sum_dig2 += matrix[i*size + (size-i-1)];
    }
    if(sum_dig1 != sum_dig2 || sum_dig1 != sum_col) { return false; }
    *sum = sum_col;
    return true;
}

bool Window::isExoteric(int size, int *matrix, int cm)
{
    for(int i=0; i<size*size; i++) {
        if(matrix[i] > size*size || matrix[i] < 1) { return false; }
    }
    int cm2 = matrix[0] + matrix[size-1] + matrix[(size-1)*size] + matrix[size*size-1];
    if(cm2 != ((4*cm)/size)) { return false; }
    if(size%2!=0){
        if(cm2 != (matrix[(size/2)] + matrix[(size/2)*size] +
                   matrix[(size/2)*size + (size-1)] + matrix[(size-1)*size + (size/2)])) { return false; }
        if(cm2 != 4*matrix[(size/2)*size + (size/2)]) { return false; }
    }else {
        if(cm2 != (matrix[(size/2-1)*size + (size/2-1)] + matrix[(size/2-1)*size + (size/2)] +
                   matrix[(size/2)*size + (size/2-1)] + matrix[(size/2)*size + (size/2)])) { return false; }
        if((2*cm2) != (matrix[(size/2-1)] + matrix[(size/2)] +
                       matrix[(size/2-1)*size] + matrix[(size/2)*size] +
                       matrix[(size/2-1)*size + (size-1)] + matrix[(size/2)*size + (size-1)] +
                       matrix[(size-1)*size + (size/2-1)] + matrix[(size-1)*size + (size/2)])) { return false; }
    }
    return true;
}

void Window::on_pushButton_clicked()
{
    int size = this->ui->spinBox->value();
    int* matrix = new int[size*size];
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            matrix[i*size + j] = this->ui->tableWidget->takeItem(i,j)->text().toInt();
        }
    }
    int cm = 0;
    if(isDiabolic(size, matrix, &cm)) {
        if(isExoteric(size, matrix, cm)){
            QMessageBox::information(this, "Result", "The matrix is exoteric",
                                     QMessageBox::Close, QMessageBox::Close);
        }else{
            QMessageBox::information(this, "Result", "The matrix is diabolic",
                                     QMessageBox::Close, QMessageBox::Close);
        }
    }else{
        QMessageBox::information(this, "Result", "The matrix is not diabolic or exoteric",
                                 QMessageBox::Close, QMessageBox::Close);
    }
}

void Window::on_spinBox_valueChanged(int arg1)
{
    this->ui->tableWidget->setColumnCount(arg1);
    this->ui->tableWidget->setRowCount(arg1);
}
