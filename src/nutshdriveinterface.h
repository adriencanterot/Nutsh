#ifndef NUTSHDRIVEINTERFACE_H
#define NUTSHDRIVEINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLayout>
#include <QDir>

class NutshComunicator;
class NutshDriveInterface : public QWidget
{
    Q_OBJECT
public:

    NutshDriveInterface(NutshComunicator* corePath);

    void refresh();

    QListWidget* getDeviceList();
    QDir* getDir();

    void sigandslots();
    void swapToDrives();

public slots :

    void changeDir(QModelIndex);
    void precedent();

private :

    NutshComunicator* core;

    QListWidget* deviceList;
    QDir* dir;
    QVBoxLayout *layout;
    QPushButton *boutonPrecedent;
    int place;
};

#endif // NUTSHDRIVEINTERFACE_H
