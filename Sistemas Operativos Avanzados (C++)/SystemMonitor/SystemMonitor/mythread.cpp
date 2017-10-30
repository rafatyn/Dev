#include "mythread.h"

MyThread::MyThread(QQueue <QString> &queue, QMutex &Fmutex) :
    exit(false)
{
    dataqueue = &queue;
    mutex = &Fmutex;
}

MyThread::~MyThread()
{
}

void MyThread::run()
{
    while(!exit){
        QString parentpath("/sys/class/hwmon");
        QDir sensordir(parentpath);
        QStringList filter1;
        filter1 << "hwmon*";

        for(auto sensor: sensordir.entryList(filter1)){
            QString sensorpath = QString("%1/%2").arg(parentpath).arg(sensor);
            QDir eachsensor(sensorpath);
            filter1.clear();
            filter1 << "temp*" << "fan*" << "pwn*" << "in*" << "cpu*" << "curr*" << "power*";

            QString namepath = QString("%1/%2").arg(sensorpath).arg("name");
            QFile file(namepath);
            QString res;
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                QByteArray line = file.readAll();
                res = QString(line.remove(line.size()-1,2));
                res.append(":\n");
            }

            for(auto files: eachsensor.entryList(filter1)){
                QString filepath = QString("%1/%2").arg(sensorpath).arg(files);
                QFile file(filepath);

                if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                    QByteArray line = file.readAll();
                    if(line != ""){
                        QString Sline(line);
                        if(!line.endsWith("\n")){
                            Sline.append("\n");
                        }
                        QString aux = QString("\t %1 = %2").arg(files).arg(Sline);
                        res.append(aux);
                    }
                }
            }
            mutex->lock();
            dataqueue->append(res);
            mutex->unlock();
            emit QueueEmpty();

        }
        this->sleep(1);
    }
}

void MyThread::exitWhile()
{
    exit = true;
}
