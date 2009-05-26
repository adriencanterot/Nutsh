#ifndef NUTSHMAJ_H
#define NUTSHMAJ_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QPushButton>
#include <QProgressBar>
#include <QHttp>
#include <QUrl>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QProcess>
#include <QDir>
#include <QTimer>
#include <QApplication>

/* Note pour Linux :
   Cette partie du code est assez specifique a chaque OS, je te laisse donc le soin de t'occuper du code, je vais te guider au maximum :) pour les fonctions quitAndStartNutsh() et startNutsh();, il faut reecrire (c'est guide), sinon, dans ce header, il y a une petite define a modifier */

#define SIZE_LABEL 1000

#ifdef Q_WS_MAC
#define PLATFORM_PATH QDir::current().path()+"/Nutsh.app/Contents/MacOS/Nutsh"
#endif

#ifdef Q_WS_WIN
#define PLATFORM_PATH QDir::toNativeSeparators(QDir::currentPath()+"\tmpNutsh.exe")
#endif

#ifdef Q_WS_X11
#define PLATFORM_PATH QDir::currentPath() // +? : regarde les modeles au dessus, ils indiquent pour chaque plateforme le chemin absolu de l'executable (avec QDir enfin tu sauras reconnaitre :)
#endif
class NutshComunicator;
class NutshMaJ : public QWidget
{
    Q_OBJECT

public:
    NutshMaJ(NutshComunicator*);
public slots:
    void telecharger();
    void quitAndStartNutsh();
    void updProgress(int, int);
    void startNutsh();

private:

    NutshComunicator* core;
    QPushButton *m_cancel;
    QHttp* m_download;
    QFile* file;
    int i, o;
};

#endif // NUTSHMAJ_H
