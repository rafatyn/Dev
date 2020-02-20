#ifndef READFILE_H
#define READFILE_H

#include <QObject>
#include <QProcess>
#include <QDirIterator>
#include <QTimer>
#include <QWaitCondition>
#include <QMutex>
#include <QVector>
#include <QApplication>

#define FILESIZEREAD   1048576
#define FILESIZESEND      1024

class ReadFile : public QObject
{
    Q_OBJECT
public:
    explicit ReadFile(QObject *parent = 0);
    inline ~ReadFile(){}

signals:

    //Enviar
    void Send(QByteArray out);

    //Barra de progreso
    void UpdateTotalSize(qint64 size);
    void UpdateTotalFileSize(qint64 size);
    void UpdateCurrentSizeRW(qint64 size);
    void UpdateCurrentFileSizeRW(qint64 size);
    void UpdateName(QString name);
    void insert(QString name, qint64 size);

public slots:

    //Lectura del arbol de directorios
    void Read(QString Dir, QString Name);

    //Control de congestion
    void UpdatePauseTime(ulong msec);
    void NACK(QString data);

private:

    //Control de congestion
    QMutex mutex;
    QWaitCondition *SendPause;
    ulong TimePause;
    qint64 seq;
    QFile *ActualFile;
    QVector<QPair<qint64, qint64> > DataBuffer;
    bool Nack;

    //Permisos
    QByteArray ConvPermision(QFile::Permissions perm);

public:
    //Asignar la var de condicion
    void setWaitCondition(QWaitCondition &WCondition);
};

#endif // READFILE_H
