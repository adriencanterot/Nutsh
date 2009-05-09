#include "nutshdriveinterface.h"
#include "nutshcomunicator.h"

NutshDriveInterface::NutshDriveInterface(NutshComunicator* corePath)
{
    this->setFixedWidth(250);

    //alloc & init
    core = corePath;

    layout = new QVBoxLayout;
    deviceList = new QListWidget;
    boutonPrecedent = new QPushButton("Precedent");
    dir = new QDir;

    dir->setPath("/Volumes");

#ifdef Q_WS_WIN
    dir->setPath("C:\\");
#endif

    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
    place = 0;

    //positionnement
    layout->addWidget(deviceList);
    layout->addWidget(boutonPrecedent);
    this->setLayout(layout);
    boutonPrecedent->setDisabled(true);
    qDebug() << "NutshDriveInterface : initialized";

}

void NutshDriveInterface::refresh() {

    deviceList->clear();
    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
}

void NutshDriveInterface::changeDir(QModelIndex item) {

    QString itemValue = item.data().toString();

    deviceList->clear();

    dir->setPath(QDir::toNativeSeparators(dir->path()+"/"+itemValue));
    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
    boutonPrecedent->setEnabled(true);

    place++;

}

void NutshDriveInterface::precedent(){

    dir->cdUp();

    place--;

    this->refresh();

    if(place == 0) {

        boutonPrecedent->setDisabled(true);
    }

    core->metadatainterface()->reset();
    core->metadatainterface()->getDirMetaData(dir->path());
}

QListWidget* NutshDriveInterface::getDeviceList() {

    return deviceList;
}

void NutshDriveInterface::sigandslots() {

    connect(deviceList, SIGNAL(clicked(QModelIndex)), core->metadatainterface(), SLOT(getDirMetaData(QModelIndex)));
    connect(deviceList, SIGNAL(clicked(QModelIndex)), this, SLOT(changeDir(QModelIndex)));
    connect(boutonPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
}

QDir* NutshDriveInterface::getDir() {

    return dir;
}

void NutshDriveInterface::swapToDrives() {

    core->progressinterface()->hide();
    this->show();
}
