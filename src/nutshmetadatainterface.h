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
    void load(QList<NutshMetaData>);
    QList<NutshMetaData> actualContent() const;
    QList<NutshMetaData> totalContent() const;
    NutshMetaDataList* getListWidget();
    void setPath(const QString&);
    void refreshInterface(ContentType);
    void navigateByKey(QKeyEvent *event);
    void place(float coef);


public slots:

    void getDirMetaData(const QModelIndex&);
    void getDirMetaData(const QString&);
    void getWordMetaData(const QString&);

    void swapWidgets(const NutshMetaData&);
    void importerContent();
    void changeDisposition(ContentType);
    void reset();
    void reload();

signals:

    void contentTypeChanged(ContentType);

private:

    NutshComunicator* core;
    QList<NutshMetaData> metaList;
    NutshMetaDataList *metadatas;
    QPushButton *importer,
                *toBibliotheque;
    
    int indexSelected;

    ContentType contentType;


};

#endif // NUTSHMETADATAINTERFACE_H
