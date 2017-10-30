#ifndef NETSTAT_H
#define NETSTAT_H

#include <QObject>
#include <QProcess>

class NetStat : public QObject
{
    Q_OBJECT
public:
    explicit NetStat(QObject *parent = 0);
    ~NetStat();

signals:

    void Readed(QString out);

public slots:

    void exec();

private:

    QProcess *myProcess;
};

#endif // NETSTAT_H
