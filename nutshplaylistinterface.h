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
#include "preprocess.h"
#include "nutshmetadata.h"
class NutshComunicator;
class NutshPlayListInterface : public QWidget
{
    Q_OBJECT
public:
    NutshPlayListInterface(NutshComunicator* corePath, QWidget* parent = 0);
    void refresh();
    void initButtons();
    void sigandslots();

private slots :
    void addListe();
    void nouvelleTable();
    void importWindow();

private :

    QPushButton *nouvelleListe, *nouvelleListeMagique, *importer;
    QListWidget *liste;
    QVBoxLayout *layout;
    QHBoxLayout *layoutBouton;
    QListWidgetItem *nouvelElement;
    NutshComunicator *core;
    QSqlQuery superQuery;

    //dialogues.
    QDialog *nommerListe;
    QVBoxLayout *layoutNommerListe;
    QPushButton *ok;
    QLineEdit *nomTable;
};

#endif // NUTSHPLAYLISTINTERFACE_H
