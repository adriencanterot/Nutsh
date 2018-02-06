#ifndef NUTSHPLAYBOX_H
#define NUTSHPLAYBOX_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include "preprocess.h"
#include "metadata.h"

class Core;
class Playbox : public QLabel
{
public:
    Playbox(Core*);
    void place(float);
    void add(const QList<Metadata>);
    void add(Metadata);
    void showcontent();
    void mouseReleaseEvent(QMouseEvent *);
    void dropEvent(QDropEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void isPlaybox(bool);
    void playing(Metadata&);
    Metadata next();
    Metadata previous();
    Metadata random();
    QList<Metadata> getFileattente() const;
    bool isEmpty();


private:
    Core* core;
    QList<Metadata> fileattente;
    int o;
    QMenu* m_right_click;
};

#endif // NUTSHPLAYBOX_H
