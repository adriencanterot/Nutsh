#ifndef NUTSHMETADATALIST_H
#define NUTSHMETADATALIST_H

#include <QListWidget>
#include <QDir>
#include <QDirIterator>
#include "nutshmetadata.h"
#include "preprocess.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QMenu>
class NutshComunicator;
class NutshMetaDataList : public QListWidget
{
    Q_OBJECT
public:
    NutshMetaDataList(NutshComunicator*);
    void load(QList<NutshMetaData>);
    void append(QList<NutshMetaData>);
    QList<NutshMetaData> getItems() const;
    QList<NutshMetaData> selectedMetadatas() const;
    NutshMetaData getItem(int index) const;
    void clearList();
    bool isEmpty();
    void navigateByKey(QKeyEvent *event);
    void wheelEvent(QWheelEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
    void setContenttype(ContentType);

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void emitSignal(QModelIndex);
    void append(NutshMetaData);
    void loadNext(int value);
    void destroy();
    void destroyFromList();

signals:
    NutshMetaData clicked(NutshMetaData);
private:
    QMenu *context;
    QList<NutshMetaData> items;
    int indexSelected;
    NutshComunicator *core;
    bool property;
    int wheelPosition;
    QPoint eventpos;
    ContentType contenttype;
};

#endif // NUTSHMETADATALIST_H
