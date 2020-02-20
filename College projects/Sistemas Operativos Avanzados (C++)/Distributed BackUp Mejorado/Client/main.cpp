#include "mainwindow.h"
#include <QApplication>

bool CheckAddress(QString address)
{
    int C1, C2, C3, C4;
    int I1, I2, I3;

    I1 = address.indexOf(".");
    I2 = address.indexOf(".", I1+1);
    I3 = address.indexOf(".", I2+1);

    if((I1 == -1)||(I2 == -1)||(I3 == -1)){
        return false;
    }else{
        QString add(address);
        C1 = add.remove(I1, address.size()).toInt();
        add = address;
        C2 = add.remove(I2, address.size()).remove(0, I1).toInt();
        add = address;
        C3 = add.remove(I3, address.size()).remove(0, I2).toInt();
        add = address;
        C4 = add.remove(0, I3+1).toInt();

        if((C1 >= 0)&&(C1 <= 255)&&(C2 >= 0)&&(C2 <= 255)&&(C3 >= 0)&&(C3 <= 255)&&(C4 >= 0)&&(C4 <= 255)){
            return true;
        }

        return false;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool error = false;
    quint16 clientPort = 0, serverPort = 0;
    QString serverAddress = "", sourceDir = "", destinationDir = "";

    for(int i=1; i<argc && !error; i++){
        if(QString(argv[i]) == "-cp"){
            if(i+1 < argc){
                if(atoi(argv[i+1]) >= 1024 && atoi(argv[i+1]) <= 65535){
                    clientPort = atoi(argv[i+1]);
                }else{
                    std::cout << "Invalid port, port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
                    error = true;
                }
            }else{
                std::cout << "Port needed: -cp [port], port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
                error = true;
            }
            i++;
        }else if(QString(argv[i]) == "-sp"){
            if(i+1 < argc){
                if(atoi(argv[i+1]) >= 1024 && atoi(argv[i+1]) <= 65535){
                    serverPort = atoi(argv[i+1]);
                }else{
                    std::cout << "Invalid port, port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
                    error = true;
                }
            }else{
                std::cout << "Port needed: -sp [port], port has to be greater or equal than 1024 and lesser or equal 65535" << std::endl;
                error = true;
            }
            i++;
        }else if(QString(argv[i]) == "-sa"){
            if(i+1 < argc){
                if(CheckAddress(argv[i+1]))
                    serverAddress = argv[i+1];
            }else{
                std::cout << "Ipv4 needed: -sa [address]" << std::endl;
                error = true;
            }
            i++;
        }else if(QString(argv[i]) == "-ds"){
            if(i+1 < argc){
                sourceDir = argv[i+1];
            }else{
                std::cout << "Source directory path needed: -sa [address]" << std::endl;
                error = true;
            }
            i++;
        }else if(QString(argv[i]) == "-dd"){
            if(i+1 < argc){
                destinationDir = argv[i+1];
            }else{
                std::cout << "Destination directory path needed: -sa [address]" << std::endl;
                error = true;
            }
            i++;
        }else if(QString(argv[i]) == "--help"){
            std::cout << "Usage: -cp [Client Port] -sp [Server Port] -sa [Server Address]"
                         "\n\t-ds [Source Directory Path] -dd [Destination Directory Path]" << std::endl;
            error = true;
        }else{
            std::cout << "Unrecognized option " << argv[i] << std::endl << "Usage: -cp [Client Port] -sp [Server Port] -sa [Server Address]"
                                                                           "\n\t-ds [Source Directory Path] -dd [Destination Directory Path]" << std::endl;
            error = true;
        }
    }

    if(!error){
        MainWindow w(0, clientPort, serverAddress, serverPort, sourceDir, destinationDir);
        w.show();

        return a.exec();
    }
}
