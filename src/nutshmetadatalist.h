#ifndef NUTSHMETADATALIST_H
#define NUTSHMETADATALIST_H

#include <QTreeWidget>
#include <QDir>
#include <QDirIterator>
#include "nutshmetadata.h"
#include "preprocess.h"
#include <QKeyEvent>

class NutshMetaDataList : public QTreeWidget
{
    Q_OBJECT
public:
    NutshMetaDataList();
    void append(NutshMetaData);
    void load(QList<NutshMetaData>);
    QList<NutshMetaData> getItems() const;
    QList<NutshMetaData> selectedMetadatas() const;
    NutshMetaData getItem(int index) const;
    void clearList();
    bool isEmpty();

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void emitSignal(QModelIndex);

signals:
    NutshMetaData clicked(NutshMetaData);
private:
    QList<NutshMetaData> items;
};

#endif // NUTSHMETADATALIST_H
