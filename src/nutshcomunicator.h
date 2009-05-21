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


class NutshComunicator
{
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

    QVBoxLayout *droite();
    QVBoxLayout *gauche();
    NutshIndexer *scannerAccess();

    void setStatus(const QString&);
    QStatusBar* bar();

private:

    QHBoxLayout *m_principal, *m_splitter;
    QWidget *m_central;
    QVBoxLayout *m_gauche, *m_droite;
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
};
#endif
