#ifndef PROGRESSWINDOW_H
#define PROGRESSWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class ProgressWindow;
}

class ProgressWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgressWindow(QWidget *parent = 0);
    ~ProgressWindow();

private:
    Ui::ProgressWindow *ui;

    //Var propiedades
    QString Name;
    qint64 FileSize, CurrentFileRW, TotalSize, CurrentTotalRW;

public:

    //Setters
    void setName(QString name);
    void setTotalFileSize(qint64 size);
    void setCurrentFileRW(qint64 size);
    void setTotalSize(qint64 size);
    void setCurrentTotalRW(qint64 size);


    //Getters
    inline QString getName() { return Name; }
    inline qint64 getTotalFileSize() { return FileSize; }
    inline qint64 getCurrentFileRW() { return CurrentFileRW; }
    inline qint64 getTotalSize() { return TotalSize; }
    inline qint64 getCurrentTotalRW() { return CurrentTotalRW; }

signals:
    //Señal para cerrar la ventana
    void Terminated();
};

#endif // PROGRESSWINDOW_H
