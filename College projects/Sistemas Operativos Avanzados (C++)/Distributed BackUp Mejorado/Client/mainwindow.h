#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFileDialog>
#include <QLocale>
#include <QIcon>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QDateTime>


#include "progresswindow.h"
#include "readfile.h"
#include "login.h"
#include "configfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, quint16 clientPort = 0, QString serverAddress = "", quint16 serverPort = 0, QString sourceDir = "", QString destinationDir = "");
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

    void on_ImportButton_clicked();

    void on_ExportButton_clicked();

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
    void Name(QChar option, QString name, QString pass);

    void Insert(QString name, qint64 size);

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
    bool TryRegister;

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

    QSqlDatabase db;
    QSqlTableModel *model;
    QVector<QString> Querys;
    void sortHandler(int index);

    //Asigna los valores del archivo de configuracion
    void setConfigFile(QString fileUrl);

    ConfigFile Configurationini;
signals:
    //Enviar directorio
    void SendS(QString Dir, QString Name);

    //Control de congestion
    void UpdateSendMsecs(ulong msec);
    void NACK(QString data);
};

#endif // MAINWINDOW_H
