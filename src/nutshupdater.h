#ifndef NUTSHUPDATER_H
#define NUTSHUPDATER_H

#include <QWidget>
#include <QProgressDialog>
#include <QDebug>
#include <QHttp>
#include <QFile>
#include <QMessageBox>
#include <QUrl>
#include <QFileInfo>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

class NutshUpdater : public QWidget
{
    Q_OBJECT
public:
    NutshUpdater();
    static bool isUpdate();
public slots:
    void launchUpdater();


private:
    QLabel* m_nouvelleMaj, *m_dlInfos;
    QPushButton *m_oui, *m_non;
    QVBoxLayout *m_principal;
    QHBoxLayout *m_ouiNon, *m_progressLayout;
    QProgressDialog *m_downloadProgress;
    QHttp* m_download;
    QFile* file;
    int i, o;
};

#endif // NUTSHUPDATER_H
