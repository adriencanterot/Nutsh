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

#define SIZE_LABEL 1000

#ifdef Q_WS_MAC
#define PLATFORM_PATH QDir::current().path()+"/Nutsh.app/Contents/MacOS/Nutsh"
#endif

#ifdef Q_WS_WIN
#define PLATFORM_PATH "tmpNutsh.exe"
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
