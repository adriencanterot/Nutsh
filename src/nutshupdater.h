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
#include "nutshmaj.h"
#include <QBuffer>


class NutshUpdater : public QDialog
{
    Q_OBJECT
public:
    NutshUpdater();
    bool isUpdate();
public slots:
    void launchUpdater();
    void getResults(bool);


private:
    QLabel* m_nouvelleMaj, *m_dlInfos;
    QPushButton *m_oui, *m_non;
    QVBoxLayout *m_principal;
    QHBoxLayout *m_ouiNon, *m_progressLayout;
    NutshMaJ* m_download;
    QBuffer* file;
    QHttp* maj;
    int i, o;
};

#endif // NUTSHUPDATER_H
