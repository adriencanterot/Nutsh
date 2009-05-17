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
    NutshMetaDataList* getListWidget();
    void setPath(QString);
    void refreshInterface(ContentType);


public slots:

    void getSqlMetaData(QString);
    void getDirMetaData(QModelIndex);
    void getDirMetaData(QString);
    void getWordMetaData(QString);

    void swapWidgets(NutshMetaData);
    void importerContent();
    void changeDisposition(ContentType);
    void reset();

signals:

    void contentTypeChanged(ContentType);

private:

    NutshComunicator* core;
    QList<NutshMetaData> metaList;
    QVBoxLayout *layout;
    QHBoxLayout * optionsLayout;
    NutshMetaDataList *metadatas;
    QPushButton *importer,
                *toBibliotheque,
                *nouvelleListe;


};

#endif // NUTSHMETADATAINTERFACE_H
