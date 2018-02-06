#ifndef NUTSHUPDATER_H
#define NUTSHUPDATER_H

#include <QWidget>
#include <QProgressDialog>
#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#include <QFileInfo>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include "maj.h"
#include <QBuffer>
#include <QVariant>

class Core;
class Updater : public QWidget
{
    Q_OBJECT
public:
    Updater(Core*);
    bool isUpdate();
    bool waitForSignal(QObject*, const char*);
    void swapToUpdater();

public slots:
    void launchUpdater();
    void getResults(bool);


private:
    Core* core;

    QLabel *m_nouvelleMaj,
           *m_dlInfos;

    QPushButton *m_oui,
                *m_non;

    QVBoxLayout *m_principal;

    QHBoxLayout *m_ouiNon,
                *m_progressLayout;

    NutshMaJ* m_download;

    QBuffer* file;
    QHttp* maj;

    int i,
        o,
        numeroVersion;
};

#endif // NUTSHUPDATER_H
