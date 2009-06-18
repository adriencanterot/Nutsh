#ifndef NUTSHCOMUNICATOR_H
#define NUTSHCOMUNICATOR_H

//core
#include "nutshsqlsaver.h"
#include "nutshindexer.h"
#include <QLayout>
#include <QSplitter>
#include <QStatusBar>

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

class NutshComunicator : public QObject
{

    Q_OBJECT

public:

    NutshComunicator();

    QWidget *initInterfaces();

    NutshMetaDataInterface *metadatainterface();
    NutshDriveInterface *driveinterface();
    NutshPlayListInterface *playlistinterface();
    NutshSearchLineInterface *searchlineinterface();
    NutshPlayingInterface *playinginterface();
    NutshProgressInterface *progressinterface();
    NutshUpdater *updater();
    NutshSqlSaver* getSqlControl();

    void afterLaunch();

    NutshIndexer *scannerAccess();

    void setStatus(const QString&);
    QStatusBar* bar();

public slots:
    void swapInterface(InterfaceName);


private:

    QWidget *m_central;
    QStatusBar* m_bar;

    NutshSqlSaver *sqlControl;

    NutshIndexer *scanner;
    NutshPlayListInterface *m_playlistinterface;
    NutshSearchLineInterface *m_searchlineinterface;
    NutshDriveInterface *m_driveinterface;
    NutshMetaDataInterface *m_metadatainterface;
    NutshPlayingInterface *m_playinginterface;
    NutshProgressInterface *m_progressinterface;
    NutshUpdater *m_updater;
    NutshBoutonRevenir *m_boutonRevenir;

};
#endif
