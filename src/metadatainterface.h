#ifndef NUTSHMETADATAINTERFACE_H
#define NUTSHMETADATAINTERFACE_H

#include <QWidget>
#include <QTreeWidget>
#include <QLayout>
#include <QDir>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include "metadata.h"
#include "metadatalist.h"
#include <QtSql>
#include "preprocess.h"
class Core;
class MetadataInterface : public QWidget
{
    Q_OBJECT

public:
    MetadataInterface(Core*);
    void sigandslots();
    void load(QList<Metadata>);
    QList<Metadata> actualContent() const;
    QList<Metadata> totalContent() const;
    searchResultType dominantType(QList<Metadata>, const QString&) const;
    MetadataList* getListWidget();
    void setPath(const QString&);
    void refreshInterface(ContentType);
    void navigateByKey(QKeyEvent *event);
    void place(float coef);


public slots:

    void getDirMetaData(const QModelIndex&);
    void getDirMetaData(const QString&);
    void getWordMetaData(const QString&);

    void swapWidgets(Metadata);
    void importerContent();
    void changeDisposition(ContentType);
    void reset();
    void reload();

signals:

    void contentTypeChanged(ContentType);

private:

    Core* core;
    QList<Metadata> metaList;
    QList<Metadata> entireList;
    MetadataList *metadatas;
    QPushButton *importer;
    QLabel *searchResults;
    
    int indexSelected;
    int nbresults;

    ContentType contentType;


};

#endif // NUTSHMETADATAINTERFACE_H
