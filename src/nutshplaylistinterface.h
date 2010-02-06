#ifndef NUTSHPLAYLISTINTERFACE_H
#define NUTSHPLAYLISTINTERFACE_H

#include <QWidget>
#include <QtSql>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include <QLineEdit>
#include <QFileDialog>
#include <QInputDialog>
#include "preprocess.h"
#include "nutshmetadata.h"
#include "nutshplaylistlist.h"

class NutshComunicator;

class NutshPlayListInterface : public QWidget
{

    Q_OBJECT

public:

    NutshPlayListInterface(NutshComunicator* corePath, QWidget* parent = 0);
    void refresh();
    void initButtons();
    void sigandslots();
    void setNewName(QString&);
    void place(float coef);
    NutshPlaylistList* elements();
    void newListFromContent(QList<NutshMetaData>);
    QString current() const;
public slots :

    void nouvelleTable();
    void importWindow();
    void addListeFromSearch();
    void addLastRead();
    void newListFromContent();

private :

    QPushButton *nouvelleListe,
                *nouvelleListeMagique,
                *importer;

    NutshPlaylistList *liste;
    NutshComunicator *core;
    QSqlQuery superQuery;

    //dialogues.
    QVBoxLayout *layoutNommerListe;
    QPushButton *ok;
    QLineEdit *nomTable;

};

#endif // NUTSHPLAYLISTINTERFACE_H
