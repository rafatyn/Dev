#include "configfile.h"

ConfigFile::ConfigFile(QObject *parent) : QObject(parent)
{

}

int ConfigFile::ReadConfigFile(QString fileUrl)
{
    config.clear();

    QFile file(fileUrl);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray fileInfo = file.readAll();

        while(fileInfo.indexOf("#") != -1){
            fileInfo.remove(fileInfo.indexOf("#"), (fileInfo.indexOf("\n")+1) - fileInfo.indexOf("#"));
        }

        while(fileInfo.indexOf("\t") != -1){
            fileInfo.remove(fileInfo.indexOf("\t"), 1);
        }

        qint64 sectionBegin = fileInfo.indexOf("[", 0);

        while(sectionBegin != -1){
            qint64 sectionEnd = fileInfo.indexOf("]", sectionBegin+1);

            if(sectionEnd != -1){
                QByteArray section;
                for(int i=sectionBegin+1; i<sectionEnd; i++){
                    section.push_back(fileInfo[i]);
                }

                sectionBegin = fileInfo.indexOf("[", sectionBegin+1);

                qint64 keyBegin = sectionEnd+2;
                qint64 keyEnd = fileInfo.indexOf("=", keyBegin);
                qint64 valueBegin = keyEnd+1;
                qint64 valueEnd = fileInfo.indexOf("\n", valueBegin);
                qint64 cond = sectionBegin;
                if(sectionBegin == -1)
                    cond = fileInfo.size();

                while(keyBegin != -1 && keyEnd != -1 && valueBegin != -1 && valueEnd != -1 && valueEnd < cond){
                    QByteArray key;
                    for(int i=keyBegin; i<keyEnd; i++){
                        key.push_back(fileInfo[i]);
                    }

                    QByteArray value;
                    for(int i=valueBegin; i<valueEnd; i++){
                        value.push_back(fileInfo[i]);
                    }

                    bool found = false;
                    for(int i=0; i<config.size(); i++){
                        if(config[i].first == section){
                            found = true;
                            config[i].second.push_back(QPair<QString,QString>(key,value));
                        }
                    }

                    if(!found){
                        config.push_back(QPair<QString,QVector<QPair<QString,QString> > >
                                         (section,QVector<QPair<QString,QString>>
                                         (1,QPair<QString,QString>(key,value))));
                    }

                    keyBegin = valueEnd+1;
                    keyEnd = fileInfo.indexOf("=", keyBegin);

                    valueBegin = keyEnd+1;
                    valueEnd = fileInfo.indexOf("\n", valueBegin);
                }
            }
        }

        file.close();

        if(fileUrl != "/etc/Clientr.conf"){
            if(!WriteConfigFile(config))
                return 0;

            return 1;
        }else{
            return 0;
        }
    }else{
        return 1;
    }
}

int ConfigFile::WriteConfigFile(QVector<QPair<QString, QVector<QPair<QString, QString> > > > data)
{
    QFile ConfFile("/etc/Client.conf");
    if(ConfFile.open(QIODevice::WriteOnly)){
        ConfFile.resize(0);
        for(int i=0; i<data.size(); i++){
            if(data[i].second.size() > 0){
                ConfFile.write(QByteArray("[").append(data[i].first).append("]\n"));
                for(int j=0; j<data[i].second.size(); j++){
                    ConfFile.write(QByteArray("").append(data[i].second[j].first)
                                   .append("=")
                                   .append(data[i].second[j].second)
                                   .append("\n"));
                }
            }
        }

        return 0;
    }else{
        return 1;
    }
}

QString ConfigFile::getValue(QString section, QString key)
{
    for(int i=0; i<config.size(); i++){
        if(config[i].first == section){
            for(int j=0; j<config[i].second.size(); j++){
                if(config[i].second[j].first == key)
                    return config[i].second[j].second;
            }
        }
    }

    return QString("Not Found");
}
