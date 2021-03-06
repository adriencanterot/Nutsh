#ifndef NUTSHDRIVEINTERFACE_H
#define NUTSHDRIVEINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLayout>
#include <QDir>
#include <QTimer>
#include <QThread>

class SearchDrivesThread : public QThread {

    Q_OBJECT

public:
    SearchDrivesThread();
    void run();

public slots:
    void emitNewDrive();

signals:
    void newDrive();

private:
    bool loopRunning;

};

class Core;
class DriveInterface : public QWidget
{
    Q_OBJECT
public:

    DriveInterface(Core* corePath);

    QListWidget* getDeviceList();
    QDir* getDir();

    void sigandslots();

public slots :

    void changeDir(QModelIndex);
    void precedent();
    void swapToDrives();
    void refresh();

private :

    Core* core;

    QListWidget* deviceList;
    QDir* dir;
    QPushButton *boutonPrecedent;
    int place;

    SearchDrivesThread *newDrive;
};

#endif // NUTSHDRIVEINTERFACE_H
