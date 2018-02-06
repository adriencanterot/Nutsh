#ifndef NUTSHCOMUNICATOR_H
#define NUTSHCOMUNICATOR_H
#define STAGING

//core
#include "sqlmanager.h"
#include "indexer.h"
#include <QLayout>
#include <QMainWindow>
#include <QSplitter>
#include <QStatusBar>
#include <QSystemTrayIcon>

//macros
#include "preprocess.h"

//Interfaces
#include "playlistinterface.h"
#include "searchlineinterface.h"
#include "metadatainterface.h"
#include "driveinterface.h"
#include "playinginterface.h"
#include "progressinterface.h"
#include "updater.h"
#include "subinterfaces.h"
#include "dailysonginterface.h"
#include "systemtrayicon.h"
#include "playbox.h"
#include "editinterface.h"

class Core : public QObject
{

    Q_OBJECT

public:

    Core(QMainWindow*);

    QWidget *initInterfaces();

    MetadataInterface *metadatainterface();
    //DriveInterface *driveinterface();
    PlaylistInterface *playlistinterface();
    SearchlineInterface *searchlineinterface();
    class PlayingInterface *playinginterface();
    class ProgressInterface *progressinterface();
    class Playbox *playbox();
    SystemtrayIcon *systemtrayicon();
    Updater *updater();
    SqlManager* getSqlControl();
    EditInterface* editinterface();
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
    SystemtrayIcon *m_tray;

    SqlManager *sqlControl;

    PlaylistInterface *m_playlistinterface;
    SearchlineInterface *m_searchlineinterface;
    //DriveInterface *m_driveinterface;
    MetadataInterface *m_metadatainterface;
    class PlayingInterface *m_playinginterface;
    class ProgressInterface *m_progressinterface;
//    Updater *m_updater;
    NutshBoutonRevenir *m_boutonrevenir;
    class Playbox *m_playbox;
    EditInterface *m_editinterface;
    InterfaceName m_interface;

};
#endif
