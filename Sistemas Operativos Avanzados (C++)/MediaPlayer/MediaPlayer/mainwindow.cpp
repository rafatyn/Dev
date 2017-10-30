#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->RewindButton->setIcon(QIcon("../Imagenes/rewind.png"));
    ui->ForwardButton->setIcon(QIcon("../Imagenes/forward.png"));
    ui->PlaypauseButton->setIcon(QIcon("../Imagenes/play.png"));
    ui->StopButton->setIcon(QIcon("../Imagenes/stop.png"));
    ui->MuteButton->setIcon(QIcon("../Imagenes/unmute.png"));
    camera = new QCamera(this);
    player = new QMediaPlayer(this);
    SCamera = false;
    volume = 50;
    ui->VolumeBar->setValue(volume);
    player->setVolume(volume);
    ui->ProgressBar->hide();
    ui->ProgressBar->setOrientation(Qt::Horizontal);
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(updateProgressBar(qint64)));
    QObject::connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(updateProgressBarRange(qint64)));
    QObject::connect(ui->ProgressBar, SIGNAL(sliderReleased()), this, SLOT(updatePlayerPosition()));
    QObject::connect(ui->ProgressBar, SIGNAL(sliderPressed()), this, SLOT(pausePlayerPosition()));
    QObject::connect(ui->VolumeBar, SIGNAL(sliderReleased()), this, SLOT(updateVolume()));

    QObject::connect(camera, static_cast<void(QCamera::*)(QCamera::Error)>(&QCamera::error), this, [=](){
       QMessageBox::warning(this, "Error", camera->errorString(), QMessageBox::Ok);
    });

    QObject::connect(player, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error), this, [=](){
        QMessageBox::warning(this, "Error", player->errorString(), QMessageBox::Ok);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_WebcamButton_clicked()
{
    if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::PlayingState){
        player->stop();
    }
    camera = new QCamera(CameraName, this);
    camera->setViewfinder(ui->ViewPanel);
    camera->start();
    ui->StopButton->setEnabled(true);
    if(ui->ProgressBar->isVisible()){
        ui->ProgressBar->hide();
    }
    if(player->state()==QMediaPlayer::PlayingState){
        player->stop();
    }
    QList<QCameraInfo> devices = QCameraInfo::availableCameras();
    if(SCamera){
        ui->statusBar->showMessage(CameraName);
    }else{
        ui->statusBar->showMessage(devices[0].description());
    }

}

void MainWindow::on_PlaypauseButton_clicked()
{
    if(camera->status()==QCamera::ActiveStatus||player->state()==QMediaPlayer::StoppedState){
         QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../MediaPlayer", "Video (*.mp4)");
         player->setMedia(QUrl::fromLocalFile(fileName));
         player->setVideoOutput(ui->ViewPanel);
         ui->RewindButton->setEnabled(true);
         ui->ForwardButton->setEnabled(true);
         ui->StopButton->setEnabled(true);
         ui->PlaypauseButton->setIcon(QIcon("../Imagenes/pause.png"));
         int LBarra = fileName.lastIndexOf("/");
         fileName.remove(0,LBarra+1);
         ui->statusBar->showMessage(fileName);
         ui->ProgressBar->show();
         player->play();
    }else if(player->state()==QMediaPlayer::PausedState){
         ui->PlaypauseButton->setIcon(QIcon("../Imagenes/pause.png"));
         player->play();
         ui->RewindButton->setEnabled(true);
         ui->ForwardButton->setEnabled(true);
    }else{
         ui->PlaypauseButton->setIcon(QIcon("../Imagenes/play.png"));
         player->pause();
         ui->RewindButton->setEnabled(false);
         ui->ForwardButton->setEnabled(false);
    }
}

void MainWindow::on_RewindButton_clicked()
{
    qint64 duration = player->duration();
    qint64 pos = player->position();
    player->setPosition(pos-(duration/20));
}

void MainWindow::on_ForwardButton_clicked()
{
    qint64 duration = player->duration();
    qint64 pos = player->position();
    player->setPosition(pos+(duration/20));
}

void MainWindow::on_StopButton_clicked()
{
    if(camera->status()==QCamera::ActiveStatus){
        camera->stop();
        ui->StopButton->setEnabled(false);
        ui->statusBar->clearMessage();
    }else if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::PlayingState){
        player->stop();
        ui->StopButton->setEnabled(false);
        ui->statusBar->clearMessage();
        ui->ProgressBar->hide();
        ui->PlaypauseButton->setIcon(QIcon("../Imagenes/play.png"));
        ui->RewindButton->setEnabled(false);
        ui->ForwardButton->setEnabled(false);
    }
}

void MainWindow::on_WCameraButton_clicked()
{
    QList<QCameraInfo> devices = QCameraInfo::availableCameras();
    if(devices.size() == 0){
        QMessageBox::information(this, "Camera", "No hay camaras conectadas", QMessageBox::Ok);
    }else{
        QStringList deviceList;
        for(int i=0; i<devices.size(); i++){
            deviceList << devices[i].description();
        }
        QString SelectedName = QInputDialog::getItem(this, "Select a camera", "Cameras:", deviceList, SCamera);
        CameraName = "";
        CameraName.append(SelectedName);
    }
}

void MainWindow::updateProgressBar(qint64 position)
{
    ui->ProgressBar->setValue(static_cast<int>(position/1000));
}

void MainWindow::updateProgressBarRange(qint64 duration)
{
    ui->ProgressBar->setRange(0, duration/1000);
}

void MainWindow::updatePlayerPosition()
{
    int pos = ui->ProgressBar->sliderPosition();
    player->setPosition(static_cast<qint64>(pos*1000));
    player->play();
    ui->PlaypauseButton->setIcon(QIcon("../Imagenes/pause.png"));
    ui->RewindButton->setEnabled(true);
    ui->ForwardButton->setEnabled(true);
}

void MainWindow::pausePlayerPosition()
{
    player->pause();
}

void MainWindow::on_MuteButton_clicked()
{
    if(player->isMuted()){
        player->setMuted(false);
        player->setVolume(volume);
        ui->MuteButton->setIcon(QIcon("../Imagenes/unmute.png"));
        ui->VolumeBar->setValue(volume);
    }else{
        player->setMuted(true);
        ui->MuteButton->setIcon(QIcon("../Imagenes/mute.png"));
        ui->VolumeBar->setValue(0);
    }
}

void MainWindow::updateVolume()
{
    volume = ui->VolumeBar->sliderPosition();
    player->setVolume(volume);
}
