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
    void place(float coef);
    void threatCommand(const QString&);
    QString value();

protected:
    void keyPressEvent(QKeyEvent*);

public slots:
    void showResults(QString);

private :
        QLineEdit* searchLine;
        NutshComunicator* core;
        QPushButton *nouvelleListe;
        QMenu* actionsPlus;
};

#endif // NUTSHSEARCHLINEINTERFACE_H
