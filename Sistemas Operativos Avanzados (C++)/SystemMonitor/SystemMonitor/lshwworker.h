#ifndef LSHWWORKER_H
#define LSHWWORKER_H

#include <QObject>
#include <QProcess>

class LshwWorker : public QObject
{
    Q_OBJECT
public:
    explicit LshwWorker(QObject *parent = 0);
    ~LshwWorker();

signals:

    void Readed(QByteArray out);

public slots:

    void exec();

private:

    QProcess *myProcess;
};

#endif // LSHWWORKER_H
