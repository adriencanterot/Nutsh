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

class NutshMaJ : public QDialog
{
    Q_OBJECT

public:
    NutshMaJ(QWidget *parent = 0);
public slots:
    void telecharger();
    void quitAndStartNutsh();
    void updProgress(int, int);
    void startNutsh();

private:
    QLabel *m_dlInfos;
    QPushButton *m_cancel;
    QVBoxLayout *m_principal;
    QHBoxLayout *m_actionLayout;
    QProgressBar* m_progress;
    QHttp* m_download;
    QFile* file;
    int i, o;
};

#endif // NUTSHMAJ_H
