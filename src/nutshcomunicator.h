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
#include "nutsheditinterface.h"

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
    NutshEditInterface* editinterface();
    void place(float coef);
    void afterLaunch();
    QString getFileContent(const QString& path);

    void setStatus(const QString&);
    QStatusBar* bar();
    void scanFolders();
    QMainWindow* getParent();
    QStringList dictionnary();
    InterfaceName interface() const;

public slots:
    void swapInterface(InterfaceName);


private:

    QWidget *m_central;
    QMainWindow *m_parent;
    QStatusBar* m_bar;
    QStringList m_dictionnary;
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
    NutshEditInterface *m_editinterface;
    InterfaceName m_interface;

};
#endif
