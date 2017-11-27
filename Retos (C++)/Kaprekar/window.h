#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void on_run_clicked();

private:
    Ui::Window *ui;
    int Calculate(int input);
};

#endif // WINDOW_H
