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

public slots :

    void addListe();
    void nouvelleTable();
    void importWindow();
    void addListeFromSearch();
    void addLastRead();

private :

    QPushButton *nouvelleListe, *nouvelleListeMagique, *importer;
    NutshPlaylistList *liste;
    QVBoxLayout *layout;
    QHBoxLayout *layoutBouton;
    NutshComunicator *core;
    QSqlQuery superQuery;

    //dialogues.
    QDialog *nommerListe;
    QVBoxLayout *layoutNommerListe;
    QPushButton *ok;
    QLineEdit *nomTable;

};

#endif // NUTSHPLAYLISTINTERFACE_H
