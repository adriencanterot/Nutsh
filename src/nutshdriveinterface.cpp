#include "nutshdriveinterface.h"
#include "nutshcomunicator.h"


SearchDrivesThread::SearchDrivesThread() {

    loopRunning = false;
}

void SearchDrivesThread::run() {

    loopRunning = true;

    QTimer time;
    connect(&time, SIGNAL(timeout()), this, SLOT(emitNewDrive()));
    time.start(1500);

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quit()));
    this->exec();
}

void SearchDrivesThread::emitNewDrive() {

    emit newDrive();
}

NutshDriveInterface::NutshDriveInterface(NutshComunicator* corePath)
{
    this->setFixedWidth(WIDTH_LEFT);

    //alloc & init
    core = corePath;

    newDrive = new SearchDrivesThread;
    connect(newDrive, SIGNAL(newDrive()), this, SLOT(refresh()));
    newDrive->start();

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

void NutshDriveInterface::changeDir(QModelIndex &item) {

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


