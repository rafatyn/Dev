#include "users.h"

Users::Users(QObject *parent) : QObject(parent)
{
    myProcess = new QProcess(this);
    myProcess->start("/usr/bin/w -h");
}

Users::~Users()
{
    delete myProcess;
}

void Users::exec()
{
    QByteArray out;
    if(myProcess->waitForStarted()){

        while(myProcess->waitForReadyRead()){
            out.append(myProcess->readAllStandardOutput());
        }

        QString usu(out);

        int finName, finLine;

        while(usu.indexOf("\n", finLine) != -1){
            finName = usu.indexOf(" ");
            finLine = usu.indexOf("\n", finLine);
            usu.remove(finName,finLine-finName);
        }

        emit Readed(usu);
    }else{
        out = "Users error: ";
        out.append(myProcess->errorString());

        emit Readed(QString(out));
    }
}
