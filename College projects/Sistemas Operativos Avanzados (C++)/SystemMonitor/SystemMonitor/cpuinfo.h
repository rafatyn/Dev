#ifndef CPUINFO_H
#define CPUINFO_H

#include <QObject>
#include <QFile>

class CpuInfo : public QObject
{
    Q_OBJECT
public:
    explicit CpuInfo(QObject *parent = 0);
    ~CpuInfo();

signals:

    void Readed(QString out);

public slots:

    void exec();

private:

    QFile *file;
};

#endif // CPUINFO_H
