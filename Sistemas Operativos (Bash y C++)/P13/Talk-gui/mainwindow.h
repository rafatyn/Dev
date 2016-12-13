#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ExitButton_clicked();

    void on_ConectButton_clicked();

    void on_AboutButton_clicked();

    void on_InputText_returnPressed();

    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void processReadyReadStandardOutput();

    void processError(QProcess::ProcessError error);

    void on_ConfButton_clicked();

private:
    Ui::MainWindow *ui;
    bool IsConnected_;
    QProcess process_;
};

#endif // MAINWINDOW_H
