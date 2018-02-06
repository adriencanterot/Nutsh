#ifndef NUTSHPLAYLISTLIST_H
#define NUTSHPLAYLISTLIST_H

#include <QListWidget>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QModelIndex>
#include "sqlmanager.h"
#include "preprocess.h"
#include <QMenu>

class Core;
class PlaylistList : public QListWidget
{
    Q_OBJECT

public:
    PlaylistList(Core*, QWidget *parent = 0);
    int currentElementId();

public slots:

    void showContent(const QModelIndex&);
    void remove();
    void rename();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    Core* core;
    QMenu *popup;
};

#endif // NUTSHPLAYLISTLIST_H
