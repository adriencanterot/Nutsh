#ifndef NUTSHPLAYBOX_H
#define NUTSHPLAYBOX_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include "preprocess.h"
#include "nutshmetadata.h"

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
    QList<NutshMetaData> getFileattente() const;
    bool isEmpty();

private:
    NutshComunicator* core;
    QList<NutshMetaData> fileattente;
    int compteur;
    QLabel* m_numbers_elements;
    QMenu* m_right_click;
};

#endif // NUTSHPLAYBOX_H
