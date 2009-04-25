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
    QVBoxLayout *droite();
    NutshIndexer *scannerAccess();
    void setStatus(QString);
    QStatusBar* bar();

private:
    QHBoxLayout *m_principal, *m_splitter;
    QWidget *m_central;
    QVBoxLayout *m_gauche, *m_droite;
    QStatusBar* m_bar;
    NutshIndexer *scanner;
    NutshPlayListInterface *m_playlistinterface;
    NutshSearchLineInterface *m_searchlineinterface;
    NutshDriveInterface *m_driveinterface;
    NutshMetaDataInterface *m_metadatainterface;
    NutshPlayingInterface *m_playinginterface;
};
#endif
