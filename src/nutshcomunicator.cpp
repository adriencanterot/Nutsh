 #include "nutshcomunicator.h"

NutshComunicator::NutshComunicator()
{

    m_bar = new QStatusBar;

    m_central = new QWidget;
    m_principal = new QHBoxLayout;
    m_gauche = new QVBoxLayout;
    m_droite = new QVBoxLayout;
    m_splitter = new QHBoxLayout;


    //cr�ation de l'objet de control sur la base de donn�e
    sqlControl = new NutshSqlSaver;
    sqlControl->connect();
    m_searchlineinterface = new NutshSearchLineInterface(this);
    m_playlistinterface = new NutshPlayListInterface(this);
    m_metadatainterface = new NutshMetaDataInterface(this);
    m_driveinterface = new NutshDriveInterface(this);

    m_gauche->addWidget(m_playlistinterface);
    m_gauche->addWidget(m_driveinterface);

    m_droite->addWidget(m_searchlineinterface);
    m_droite->addWidget(m_metadatainterface);

    m_splitter->addLayout(m_gauche);
    m_splitter->addLayout(m_droite);

    m_principal->addLayout(m_splitter);
    m_central->setLayout(m_principal);

    qDebug() << "NutshComunicator : Transimission de toutes les interfaces a NutshMainWindow";

    m_searchlineinterface->setFocus();

    m_playlistinterface->sigandslots();
    m_searchlineinterface->sigandslots();
    m_metadatainterface->sigandslots();
    m_driveinterface->sigandslots();

    //cr�ation du scanner pour les m�dias
}

void NutshComunicator::afterLaunch() {

    m_playinginterface = new NutshPlayingInterface(this);
    m_progressinterface = new NutshProgressInterface(this);
    scanner = new NutshIndexer(this);
    m_updater = new NutshUpdater(this);

    m_playinginterface->sigandslots();

}
QWidget *NutshComunicator::initInterfaces() {
    //mise en places dans les layouts et envoi dans la fen�tre principale.
    return m_central;
}

/* ----------Fonctions retournant les interfaces pour communiquer entre les diff�rentes parties du programme -------*/
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

QVBoxLayout *NutshComunicator::droite() {

    return m_droite;
}

QVBoxLayout *NutshComunicator::gauche() {

    return m_gauche;
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

