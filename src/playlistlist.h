#ifndef NUTSHPLAYLISTLIST_H
#define NUTSHPLAYLISTLIST_H

#include <QListWidget>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QModelIndex>
#include "nutshsqlsaver.h"
#include "preprocess.h"
#include <QMenu>

class NutshComunicator;
class NutshPlaylistList : public QListWidget
{
    Q_OBJECT

public:
    NutshPlaylistList(NutshComunicator*, QWidget *parent = 0);
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
    NutshComunicator* core;
    QMenu *popup;
};

#endif // NUTSHPLAYLISTLIST_H
