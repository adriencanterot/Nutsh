#ifndef NUTSHSEARCHLINEINTERFACE_H
#define NUTSHSEARCHLINEINTERFACE_H

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QtSql>
#include <QPushButton>
#include <QMenu>
#include "nutshmetadata.h"

class NutshComunicator;
class NutshSearchLineInterface : public QWidget
{
    Q_OBJECT
public:
    NutshSearchLineInterface(NutshComunicator*);
    void sigandslots();
    void activate();

protected:
    void keyPressEvent(QKeyEvent*);

public slots:
    void showResults(QString);

private :
        QLineEdit* searchLine;
        QHBoxLayout* organisation;
        NutshComunicator* core;
        QPushButton *nouvelleListe;
        QMenu* actionsPlus;
};

#endif // NUTSHSEARCHLINEINTERFACE_H
