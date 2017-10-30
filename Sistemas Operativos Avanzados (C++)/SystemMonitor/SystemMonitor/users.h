#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QProcess>
#include <QRegularExpression>

class Users : public QObject
{
    Q_OBJECT
public:
    explicit Users(QObject *parent = 0);
    ~Users();

signals:

    void Readed(QString out);

public slots:

    void exec();

private:

    QProcess *myProcess;
};

#endif // USERS_H
