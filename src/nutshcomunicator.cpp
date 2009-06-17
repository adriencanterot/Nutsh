 #include "nutshcomunicator.h"

NutshComunicator::NutshComunicator()
{

    m_bar = new QStatusBar;

    m_central = new QWidget;

    //création de l'objet de control sur la base de donnée
    sqlControl = new NutshSqlSaver;
    sqlControl->connect();
    m_searchlineinterface = new NutshSearchLineInterface(this);
    m_playlistinterface = new NutshPlayListInterface(this);
    m_metadatainterface = new NutshMetaDataInterface(this);
    m_driveinterface = new NutshDriveInterface(this);

    m_metadatainterface->setParent(m_central);

    m_searchlineinterface->setParent(m_central);

    m_playlistinterface->setParent(m_central);

    //m_driveinterface->setParent(m_central);

    qDebug() << "NutshComunicator : Transimission de toutes les interfaces a NutshMainWindow";

    m_searchlineinterface->setFocus();

    m_playlistinterface->sigandslots();
    m_searchlineinterface->sigandslots();
    m_metadatainterface->sigandslots();
    m_driveinterface->sigandslots();

    //création du scanner pour les médias

    afterLaunch();
}

void NutshComunicator::afterLaunch() {

    m_playinginterface = new NutshPlayingInterface(this);
    m_progressinterface = new NutshProgressInterface(this);

    m_playinginterface->setFixedSize(600, 350);
    m_playinginterface->setParent(m_central);
    //m_playinginterface->setStyleSheet("background-color: blue;");

    m_progressinterface->setFixedSize(600, 350);
    m_progressinterface->setParent(m_central);
    m_progressinterface->move(200, 300);

    //m_playinginterface->hide();
    //m_progressinterface->hide();

    scanner = new NutshIndexer(this);
    m_updater = new NutshUpdater(this);

    m_updater->setParent(m_central);
    m_updater->hide();

    m_playinginterface->sigandslots();
}
QWidget *NutshComunicator::initInterfaces() {
    //mise en places dans les layouts et envoi dans la fenêtre principale.
    return m_central;
}

/* ----------Fonctions retournant les interfaces pour communiquer entre les différentes parties du programme -------*/
NutshMetaDataInterface* NutshComunicator::metadatainterface() {

    return m_metadatainterface;
}

NutshDriveInterface* NutshComunicator::driveinterface() {

    return m_driveinterface;
}

NutshSearchLineInterface* NutshComunicator::searchlineinterface() {

    return m_searchlineinterface;
}

NutshPlayListInterface* NutshComunicator::playlistinterface() {

    return m_playlistinterface;
}

NutshPlayingInterface* NutshComunicator::playinginterface() {

    return m_playinginterface;
}

NutshProgressInterface* NutshComunicator::progressinterface() {

    return m_progressinterface;
}


NutshIndexer* NutshComunicator::scannerAccess() {

    return scanner;
}

void NutshComunicator::setStatus(const QString &status) {

    m_bar->showMessage(status);
}

QStatusBar* NutshComunicator::bar() {

    return m_bar;
}

NutshSqlSaver* NutshComunicator::getSqlControl() {

    return sqlControl;
}

