#include "lshwworker.h"

LshwWorker::LshwWorker(QObject *parent) : QObject(parent)
{
    myProcess = new QProcess(this);
    myProcess->start("/usr/bin/lshw -json");
}

LshwWorker::~LshwWorker()
{
    delete myProcess;
}

void LshwWorker::exec()
{
    QByteArray out;
    if(myProcess->waitForStarted()){
        while(myProcess->waitForReadyRead()){
            out.append(myProcess->readAllStandardOutput());
        }
    }else{
        out = "Lshw error: ";
        out.append(myProcess->errorString());
    }
    emit Readed(out);
}


