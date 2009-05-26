#ifndef NUTSHPLAYLISTLIST_H
#define NUTSHPLAYLISTLIST_H

#include <QListWidget>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QModelIndex>
#include "nutshsqlsaver.h"
#include "preprocess.h"

class NutshComunicator;
class NutshPlaylistList : public QListWidget
{
    Q_OBJECT

public:
    NutshPlaylistList(NutshComunicator*, QWidget *parent = 0);

public slots:

    void showContent(const QModelIndex&);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent* event);

private:
    NutshComunicator* core;
};

#endif // NUTSHPLAYLISTLIST_H
