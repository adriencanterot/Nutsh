#ifndef NUTSHMETADATAINTERFACE_H
#define NUTSHMETADATAINTERFACE_H

#include <QWidget>
#include <QTreeWidget>
#include <QLayout>
#include <QDir>
#include <QList>
#include <QPushButton>
#include "nutshmetadata.h"
#include "nutshmetadatalist.h"
#include <QtSql>
#include "preprocess.h"
class NutshComunicator;
class NutshMetaDataInterface : public QWidget
{
    Q_OBJECT
public:
    NutshMetaDataInterface(NutshComunicator*);
    void sigandslots();
    void swapToList();
    void load(QList<NutshMetaData>);
    QList<NutshMetaData> actualContent();
    void setPath(QString);
    void reset();
public slots:
    void getSqlMetaData(QString);
    void getDirMetaData(QModelIndex);
    void getDirMetaData(QString);
    void getWordMetaData(QString);
    void swapWidgets(NutshMetaData);
    void importerContent();
private:
    NutshComunicator* core;
    QList<NutshMetaData> metaList;
    QVBoxLayout *layout;
    NutshMetaDataList *metadatas;
    QPushButton* importer;

};

#endif // NUTSHMETADATAINTERFACE_H
