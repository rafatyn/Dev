#include "netstat.h"

NetStat::NetStat(QObject *parent) : QObject(parent)
{
    myProcess = new QProcess(this);
    myProcess->start("/bin/netstat -txu");
}

NetStat::~NetStat()
{
    delete myProcess;
}

void NetStat::exec()
{
    QByteArray out;
    if(myProcess->waitForStarted()){

        while(myProcess->waitForReadyRead()){
            out.append(myProcess->readAllStandardOutput());
        }
        QString tcp(out);

        int begTcpUdp = tcp.indexOf("Conexiones activas");
        int begTcp = tcp.indexOf("tcp");
        int begUdp = tcp.indexOf("udp");
        int begUnix = tcp.indexOf("Activar zócalos");

        if(begUdp != -1){
            tcp.remove(begUdp,tcp.size());
        }else{
            tcp.remove(begUnix,tcp.size());
        }
        tcp.remove(0,begTcpUdp);

        if(!tcp.contains("tcp")){
            tcp = "No hay conexiones Tcp";
        }

        emit Readed(tcp);

        QString udp(out);

        udp.remove(begUnix,udp.size());
        udp.remove(begTcp,begUdp);

        if(!udp.contains("udp")){
            udp = "No hay conexiones Udp";
        }

        emit Readed(udp);

        QString uunix(out);

        uunix.remove(0,begUnix);

        if(!udp.contains("unix",Qt::CaseSensitive)){
            udp = "No hay conexiones Unix";
        }

        emit Readed(uunix);
    }else{
        out = "Netstat error: ";
        out.append(myProcess->errorString());

        emit Readed(QString(out));
    }
}
