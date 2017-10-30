#include "cpuinfo.h"

CpuInfo::CpuInfo(QObject *parent) : QObject(parent)
{
    file = new QFile("/proc/cpuinfo");
}

CpuInfo::~CpuInfo()
{
    delete file;
}

void CpuInfo::exec()
{
    QByteArray out;
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)){
        out = file->readAll();

        emit Readed(QString(out));
    }else{
        out = "Cpu Info error: ";
        out.append(file->errorString());
    }
    emit Readed(QString(out));
}
