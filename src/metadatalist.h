#ifndef NUTSHMETADATALIST_H
#define NUTSHMETADATALIST_H

#include <QListWidget>
#include <QDir>
#include <QDirIterator>
#include "metadata.h"
#include "preprocess.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QMenu>
class Core;
class MetadataList : public QListWidget
{
    Q_OBJECT
public:
    MetadataList(Core*);
    void load(QList<Metadata>);
    void append(QList<Metadata>);
    QList<Metadata> getItems() const;
    QList<Metadata> selectedMetadatas() const;
    Metadata getItem(int index) const;
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
    void append(Metadata);
    void loadNext(int value);
    void destroy();
    void destroyFromList();

signals:
    Metadata clicked(Metadata);
private:
    QMenu *context;
    QList<Metadata> items;
    int indexSelected;
    Core *core;
    bool property;
    int wheelPosition;
    QPoint eventpos;
    ContentType contenttype;
};

#endif // NUTSHMETADATALIST_H
