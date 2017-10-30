#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QQueue>
#include <QPair>
#include <QWaitCondition>
#include <QMutex>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread(QQueue <QString> &queue, QMutex &Fmutex);
    ~MyThread();

protected:
    void run() override;

signals:
    void QueueEmpty();

private:
    QQueue <QString>* dataqueue;
    QMutex* mutex;
    bool exit;

public slots:

    void exitWhile();
};

#endif // MYTHREAD_H
