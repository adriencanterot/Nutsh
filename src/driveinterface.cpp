#include "driveinterface.h"
#include "core.h"


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

DriveInterface::DriveInterface(Core* corePath)
{
    qDebug() << "Initializing DriveInterface...";
    this->setFixedWidth(WIDTH_LEFT);

    //alloc & init
    core = corePath;

    newDrive = new SearchDrivesThread;
    connect(newDrive, SIGNAL(newDrive()), this, SLOT(refresh()));
    newDrive->start();

    deviceList = new QListWidget(this);
    boutonPrecedent = new QPushButton("Precedent", this);
    dir = new QDir;

    dir->setPath("/Volumes");

#ifdef Q_WS_WIN
    dir->setPath("C:\\");
#endif

    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
    place = 0;

    boutonPrecedent->setDisabled(true);

}

void DriveInterface::refresh() {

    deviceList->clear();
    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
}

void DriveInterface::changeDir(QModelIndex item) {

    QString itemValue = item.data().toString();

    deviceList->clear();

    dir->setPath(QDir::toNativeSeparators(dir->path()+"/"+itemValue));
    deviceList->addItems(dir->entryList(QDir::AllDirs|QDir::NoDotAndDotDot));
    boutonPrecedent->setEnabled(true);

    place++;

}

void DriveInterface::precedent(){

    dir->cdUp();

    place--;

    this->refresh();

    if(place == 0) {

        boutonPrecedent->setDisabled(true);
    }

    core->metadatainterface()->reset();
    core->metadatainterface()->getDirMetaData(dir->path());
}

QListWidget* DriveInterface::getDeviceList() {

    return deviceList;
}

void DriveInterface::sigandslots() {

    connect(deviceList, SIGNAL(clicked(QModelIndex)), core->metadatainterface(), SLOT(getDirMetaData(QModelIndex)));
    connect(deviceList, SIGNAL(clicked(QModelIndex)), this, SLOT(changeDir(QModelIndex)));
    connect(boutonPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
}

QDir* DriveInterface::getDir() {

    return dir;
}

void DriveInterface::swapToDrives() {

    core->progressinterface()->hide();
    core->progressinterface()->reset();
    this->show();
}
