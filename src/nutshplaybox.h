#ifndef NUTSHPLAYBOX_H
#define NUTSHPLAYBOX_H

#include <QWidget>
#include "preprocess.h"
class NutshMetaData;

class NutshComunicator;
class NutshPlaybox : public QWidget
{
public:
    NutshPlaybox(NutshComunicator*);
    void place(float);
    void add(const QList<NutshMetaData>);
    void add(NutshMetaData);
    void showcontent();
    void mouseReleaseEvent(QMouseEvent *);
    void dropEvent(QDropEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void isPlaybox(bool);
    void playing(NutshMetaData&);
    NutshMetaData next();
    bool isEmpty();

private:
    NutshComunicator* core;
    QList<NutshMetaData> fileattente;
    int compteur;
};

#endif // NUTSHPLAYBOX_H
