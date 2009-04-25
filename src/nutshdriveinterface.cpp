#include "nutshdriveinterface.h"
#include "nutshcomunicator.h"

NutshDriveInterface::NutshDriveInterface(NutshComunicator* corePath)
{
    this->setFixedWidth(250);
    //alloc & init
    core = corePath;
    layout = new QVBoxLayout;
    deviceList = new QListWidget;
    dir = new QDir("/Volumes/");
    boutonPrecedent = new QPushButton("Precedent");

    //positionnement
    layout->addWidget(deviceList);
    layout->addWidget(boutonPrecedent);
    this->setLayout(layout);

    //config
    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
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
}
void NutshDriveInterface::precedent(){
    dir->cdUp();
    this->refresh();
    if(dir->path() == "/Volumes") {
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
