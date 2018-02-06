#ifndef NUTSHMAINWINDOW_H
#define NUTSHMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtSql>
#include <QToolBar>
#include <QTextEdit>
#include <QThread>
#include <QFile>
#include <QtGui>
#include "player.h"
#include "indexer.h"
#include "core.h"
#include "installationwizard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    //-----------MENUS------------//
    //void setupMenus();
    Core* path;
private :


/*

    //-----------MENUS------------//
    QMenu *fichier,
          *edition,
          *controles;

    QAction *ouvrir, //Fichier
            *importer,
            *derniersmorceaux,
            *resultats,
            *editermorceaux,
            *explorateur,
            *copier, //edition
            *coller,
            *toutselectionner,
            *supprimer,
            *lire, //controles
            *pause,
            *arreter,
            *suivant,
            *precedent,
            *repeat,
            *random;

    QMenuBar* menubar;
    */

};

#endif // NUTSHMAINWINDOW_H
