#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFileDialog>
#include <QLocale>

#include "progresswindow.h"
#include "readfile.h"
#include "login.h"

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

    //UI slots
    //Conectar el socket
    void on_ConnectButton_clicked();

    //Leer datagramas del socket
    void Read();

    //Enviar directorio
    void on_SendFileButton_clicked();

    //Seleccionar directorios
    void on_SourceFindDirButton_clicked();
    void on_DestinationFindDirAddress_clicked();
    void on_SourceDirAddress_editingFinished();
    void on_DestinationDirAddress_editingFinished();

    //Modificar direccion del servidor
    void on_ServerAddress_editingFinished();

public slots:

    //Barra de progreso
    void UpdateCurrentTotalSizeRW(qint64 size);
    void UpdateCurrentSizeRW(qint64 size);
    void UpdateTotalSize(qint64 size);
    void UpdateFileSize(qint64 size);
    void UpdateName(QString name);

    //Enviar
    void Send(QByteArray out);

    //Cerrar cliente
    void TTerminated();

    //cambiar nombre
    void Name(QString name);

private:
    Ui::MainWindow *ui;

    //Socket Cliente
    QString UserName;
    QUdpSocket *Client;

    //Directorios
    QDir SourceDir;
    QDir DestinationDir;

    //Archivo de escritura
    QFile* ActualFile;

    //Clase de lectura
    ReadFile ReadF;
    QThread RThread;

    //Var de comprobacion
    bool ServerAddOk;
    bool canUpdateDir;
    bool canUpdateDDir;
    bool isReceiving;
    bool connected;
    bool Nack;

    bool perder;

    //Ventana de progreso
    ProgressWindow progressWindow;

    //Ventana de Login
    Login LogIn;

    //Control de congestion
    QVector<QPair<QByteArray, qint64> > PacketBuffer;
    qint64 RecieveSeq;
    QWaitCondition SendPause;

    //Permisos
    QFile::Permissions ConvPermision(QString perm);
signals:
    //Enviar directorio
    void SendS(QString Dir, QString Name);

    //Control de congestion
    void UpdateSendMsecs(ulong msec);
    void NACK(QString data);
};

#endif // MAINWINDOW_H
