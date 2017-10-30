#include "readfile.h"

ReadFile::ReadFile(QObject *parent) : QObject(parent)
{
    Nack = false;
}

void ReadFile::Read(QString Dir, QString Name)
{
    TimePause = 0;
    mutex.lock();

    QDirIterator it(Dir, QDir::NoDot | QDir::NoDotDot | QDir::Hidden | QDir::Files | QDir::Dirs,
                    QDirIterator::Subdirectories);

    QProcess du(this);
    du.setProgram("/usr/bin/du");
    QStringList arguments;
    arguments << "-bsc" << Dir;
    du.setArguments(arguments);
    du.start();

    du.waitForStarted();
    QByteArray OutDu;
    while(du.waitForReadyRead()){
        OutDu.append(du.readAllStandardOutput());
    }
    OutDu.remove(OutDu.indexOf("\t"), OutDu.size() - OutDu.indexOf("\t"));

    emit UpdateTotalSize(OutDu.toLongLong());

    emit Send(QByteArray("Directory size: ").append(QString(OutDu)));

    seq = 0;

    while(it.hasNext()){
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        if(fileInfo.isFile()){
            ActualFile = new QFile(fileInfo.absoluteFilePath());
            if(ActualFile->open(QIODevice::ReadOnly)){

                QByteArray perm = ConvPermision(ActualFile->permissions());

                emit Send(QByteArray("File Path: ")
                          .append(Name)
                          .append("/")
                          .append(ActualFile->fileName().remove(0, Dir.lastIndexOf("/")+1))
                          .append(" Total size: ")
                          .append(QString::number(ActualFile->size()))
                          .append(" Permision:")
                          .append(perm));

                int FilePos = 0;

                emit UpdateTotalFileSize(ActualFile->size());
                emit UpdateName(ActualFile->fileName().remove(0, ActualFile->fileName().lastIndexOf("/")+1));

                DataBuffer.clear();

                while(FilePos < ActualFile->size()){
                    DataBuffer.push_back(QPair<qint64, qint64>(seq, ActualFile->pos()));

                    QByteArray fileData = ActualFile->read(FILESIZEREAD);

                    int FileBlockPos = 0;

                    while(FileBlockPos < fileData.size()){
                        QByteArray fileBlock(fileData);

                        if((FileBlockPos+FILESIZESEND) < fileData.size()){
                            fileBlock.remove(FileBlockPos+FILESIZESEND, fileBlock.size() - (FileBlockPos+FILESIZESEND));
                        }

                        fileBlock.remove(0, FileBlockPos);

                        QByteArray message;
                        message.append("Seq:").append(QByteArray ().setNum(seq)).append("/").append(fileBlock);
                        seq++;

                        emit Send(message);

                        FileBlockPos += FILESIZESEND;
                        emit UpdateCurrentFileSizeRW(fileBlock.size());
                        emit UpdateCurrentSizeRW(fileBlock.size());

                        SendPause->wait(&mutex, TimePause);

                        qApp->processEvents();

                        if(Nack){
                            Nack = false;
                            emit UpdateCurrentSizeRW(-(FileBlockPos + (FilePos - ActualFile->pos())));
                            FileBlockPos = FILESIZEREAD;
                            emit UpdateTotalFileSize(ActualFile->size());
                            emit UpdateCurrentFileSizeRW(ActualFile->pos());
                        }
                    }

                    if(ActualFile->pos() == ActualFile->size()){
                        SendPause->wait(&mutex);
                    }

                    FilePos = ActualFile->pos();
                }


            }
        }else if(fileInfo.isDir()){
            emit Send(QByteArray("Add directory"));
            emit UpdateCurrentSizeRW(4096);
        }
    }

    emit Send(QByteArray("Sended"));

    mutex.unlock();
}

void ReadFile::UpdatePauseTime(ulong msec)
{
    TimePause = msec;
}

void ReadFile::NACK(QString data)
{
    qint64 sequ = data.remove(0, data.indexOf(":")+1).toLongLong();

    bool found = false;

    if(DataBuffer.size() != 1){
        for(int i=0; i<DataBuffer.size()-1 && !found; i++){
            if(sequ >= DataBuffer[i].first && sequ < DataBuffer[i+1].first){
                found = true;
                seq = DataBuffer[i].first;
                ActualFile->seek(DataBuffer[i].second);
                DataBuffer.remove(i+1, DataBuffer.size() - (i+1));
            }else if(i+1 == (DataBuffer.size()-1)){
                seq = DataBuffer[i+1].first;
                ActualFile->seek(DataBuffer[i+1].second);
            }
        }
    }else{
        seq = DataBuffer[0].first;
        ActualFile->seek(DataBuffer[0].second);
    }

    Nack = true;
    TimePause += 1;
    SendPause->wakeAll();
}

QByteArray ReadFile::ConvPermision(QFileDevice::Permissions perm)
{
    QByteArray permisions;

    if(perm & QFile::ReadOwner){
        permisions.append("r");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::WriteOwner){
        permisions.append("w");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::ExeOwner){
        permisions.append("x");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::ReadGroup){
        permisions.append("r");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::WriteGroup){
        permisions.append("w");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::ExeGroup){
        permisions.append("x");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::ReadOther){
        permisions.append("r");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::WriteOther){
        permisions.append("w");
    }else{
        permisions.append("-");
    }

    if(perm & QFile::ExeOther){
        permisions.append("x");
    }else{
        permisions.append("-");
    }

    return permisions;
}

void ReadFile::setWaitCondition(QWaitCondition &WCondition)
{
    SendPause = &WCondition;
}
