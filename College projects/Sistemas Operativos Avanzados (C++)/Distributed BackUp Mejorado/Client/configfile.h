#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QFile>
#include <iostream>

class ConfigFile : public QObject
{
    Q_OBJECT
public:
    explicit ConfigFile(QObject *parent = 0);

private:
    QVector<QPair<QString,QVector<QPair<QString,QString> > > > config;

public:
    int ReadConfigFile(QString fileUrl);
    int WriteConfigFile(QVector<QPair<QString,QVector<QPair<QString,QString> > > > data);
    QString getValue(QString section, QString key);

};

#endif // CONFIGFILE_H
