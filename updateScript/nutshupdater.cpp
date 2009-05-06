#include "nutshupdater.h"
NutshUpdate::NutshUpdate() {

    QTimer::singleShot(1000, this, SLOT(afterTimer()));
    QTimer::singleShot(1001, qApp, SLOT(quit()));
}
void NutshUpdate::afterTimer() {
    QFile *file = new QFile("Nutsh.exe");
    if(!file->open(QIODevice::ReadWrite)) {
        qDebug() << "1st step" << file->errorString();
    }
    QFile* tmpFile = new QFile("tmpNutsh.exe");
    if(!tmpFile->open(QIODevice::ReadOnly)) {
        qDebug() << "2nd step" << file->errorString();
    }
    file->setPermissions(QFile::ExeOther|QFile::ExeGroup);
    file->close();
    if(!file->remove()) {
        qDebug() << "3rd step" << file->errorString();
    }
    if(!tmpFile->rename("Nutsh.exe")) {

        qDebug() << "4th step" << tmpFile->errorString();
    }
    QProcess::startDetached("Nutsh.exe");
}
