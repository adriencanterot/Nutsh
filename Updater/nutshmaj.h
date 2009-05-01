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
#define SIZE_LABEL 1000


class NutshMaJ : public QWidget
{
    Q_OBJECT

public:
    NutshMaJ(QWidget *parent = 0);
public slots:
    void telecharger();
    void quitAndStartNutsh();
    void updProgress(int, int);
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
