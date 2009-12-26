#ifndef NUTSHPLAYBOX_H
#define NUTSHPLAYBOX_H

#include <QWidget>
class NutshMetaData;

class NutshComunicator;
class NutshPlaybox : public QWidget
{
public:
    NutshPlaybox(NutshComunicator*);
    void place(float);
    void add(const QList<NutshMetaData>&);
    void showcontent();
    void mouseReleaseEvent(QMouseEvent *);
    void dropEvent(QDropEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
private:
    NutshComunicator* core;
    QList<NutshMetaData> fileattente;
};

#endif // NUTSHPLAYBOX_H
