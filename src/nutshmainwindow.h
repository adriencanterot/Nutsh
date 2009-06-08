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
#include "nutshlecteur.h"
#include "nutshindexer.h"
#include "nutshcomunicator.h"
#include "nutshinstallationwizard.h"

class NutshMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    NutshMainWindow(QWidget *parent = 0);

private :

    NutshComunicator* path;
    //core

};

#endif // NUTSHMAINWINDOW_H
