#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QFileDialog>
#include <QInputDialog>
#include <QMediaPlayer>
#include <QList>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_WebcamButton_clicked();

    void on_PlaypauseButton_clicked();

    void on_RewindButton_clicked();

    void on_ForwardButton_clicked();

    void on_StopButton_clicked();

    void on_WCameraButton_clicked();

    void updateProgressBar(qint64 position);

    void updateProgressBarRange(qint64 duration);

    void updatePlayerPosition();

    void pausePlayerPosition();

    void on_MuteButton_clicked();

    void updateVolume();

private:
    Ui::MainWindow *ui;
    QCamera* camera;
    QMediaPlayer* player;
    bool SCamera;
    QByteArray CameraName;
    int volume;
};

#endif // MAINWINDOW_H
