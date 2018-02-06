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
#include "metadata.h"
#include "playlistlist.h"

class Core;

class PlaylistInterface : public QWidget
{

    Q_OBJECT

public:

    PlaylistInterface(Core* corePath, QWidget* parent = 0);
    void refresh();
    void initButtons();
    void sigandslots();
    void setNewName(QString&);
    void place(float coef);
    PlaylistList* elements();
    void newListFromContent(QList<Metadata>);
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

    PlaylistList *liste;
    Core *core;
    QSqlQuery superQuery;

    //dialogues.
    QVBoxLayout *layoutNommerListe;
    QPushButton *ok;
    QLineEdit *nomTable;

};

#endif // NUTSHPLAYLISTINTERFACE_H
