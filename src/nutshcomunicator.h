#ifndef NUTSHCOMUNICATOR_H
#define NUTSHCOMUNICATOR_H
#define STAGING

//core
#include "nutshsqlsaver.h"
#include "nutshindexer.h"
#include <QLayout>
#include <QMainWindow>
#include <QSplitter>
#include <QStatusBar>
#include <QSystemTrayIcon>

//macros
#include "preprocess.h"

//Interfaces
#include "nutshplaylistinterface.h"
#include "nutshsearchlineinterface.h"
#include "nutshmetadatainterface.h"
#include "nutshdriveinterface.h"
#include "nutshplayinginterface.h"
#include "nutshprogressinterface.h"
#include "nutshupdater.h"
#include "nutshsubinterfaces.h"
#include "dailysonginterface.h"
#include "nutshsystemtrayicon.h"
#include "nutshplaybox.h"

class NutshComunicator : public QObject
{

    Q_OBJECT

public:

    NutshComunicator(QMainWindow*);

    QWidget *initInterfaces();

    NutshMetaDataInterface *metadatainterface();
    //NutshDriveInterface *driveinterface();
    NutshPlayListInterface *playlistinterface();
    NutshSearchLineInterface *searchlineinterface();
    NutshPlayingInterface *playinginterface();
    NutshProgressInterface *progressinterface();
    NutshPlaybox *playbox();
    NutshSystemTrayIcon *systemtrayicon();
    NutshUpdater *updater();
    NutshSqlSaver* getSqlControl();
    void place(float coef);
    void afterLaunch();

    void setStatus(const QString&);
    QStatusBar* bar();
    void scanFolders();
    QMainWindow* getParent();

public slots:
    void swapInterface(InterfaceName);


private:

    QWidget *m_central;
    QMainWindow *m_parent;
    QStatusBar* m_bar;
    NutshSystemTrayIcon *m_tray;

    NutshSqlSaver *sqlControl;

    NutshPlayListInterface *m_playlistinterface;
    NutshSearchLineInterface *m_searchlineinterface;
    //NutshDriveInterface *m_driveinterface;
    NutshMetaDataInterface *m_metadatainterface;
    NutshPlayingInterface *m_playinginterface;
    NutshProgressInterface *m_progressinterface;
//    NutshUpdater *m_updater;
    NutshBoutonRevenir *m_boutonrevenir;
    NutshPlaybox *m_playbox;

};
#endif
