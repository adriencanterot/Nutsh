 #include "nutshcomunicator.h"

NutshComunicator::NutshComunicator(QMainWindow *parent = 0)
{

    m_bar = new QStatusBar;
    m_parent = parent;
    m_central = new QWidget;
    m_tray = new NutshSystemTrayIcon(this->getParent());
    m_tray->setIcon(qApp->windowIcon());
    m_tray->show();


    //cr�ation de l'objet de control sur la base de donn�e
    sqlControl = new NutshSqlSaver;
    sqlControl->connect();
    m_searchlineinterface = new NutshSearchLineInterface(this);
    m_playlistinterface = new NutshPlayListInterface(this);
    m_metadatainterface = new NutshMetaDataInterface(this);
//    m_driveinterface = new NutshDriveInterface(this);

    m_metadatainterface->setParent(m_central);
    m_searchlineinterface->setParent(m_central);
    m_playlistinterface->setParent(m_central);

    //m_driveinterface->setParent(m_central);

    m_searchlineinterface->setFocus();

    m_playlistinterface->sigandslots();
    m_searchlineinterface->sigandslots();
    m_metadatainterface->sigandslots();
//    m_driveinterface->sigandslots();

    //cr�ation du scanner pour les m�dias

    afterLaunch();
    qDebug() << "NutshComunicator : Transimission de toutes les interfaces a NutshMainWindow";
}

void NutshComunicator::afterLaunch() {

    m_playinginterface = new NutshPlayingInterface(this);
    m_progressinterface = new NutshProgressInterface(this);

    m_playinginterface->getActionsButtons()->setParent(m_central);

    m_playinginterface->setParent(m_central);

    m_boutonrevenir = new NutshBoutonRevenir(m_central);
    connect(m_boutonrevenir, SIGNAL(clicked(InterfaceName)), this, SLOT(swapInterface(InterfaceName)));

    m_progressinterface->setParent(m_central);

    m_playinginterface->hide();
    m_progressinterface->hide();

//    m_updater = new NutshUpdater(this);

//    m_updater->setParent(m_central);
//    m_updater->hide();

    m_playinginterface->sigandslots();

    this->place(1);
    m_metadatainterface->setFixedWidth(100);
    m_metadatainterface->getListWidget()->setFixedWidth(
            m_metadatainterface->getListWidget()->width()-100
            );
}
QWidget *NutshComunicator::initInterfaces() {
    //mise en places dans les layouts et envoi dans la fen�tre principale.
    return m_central;
}

void NutshComunicator::swapInterface(InterfaceName name) {

    switch(name) {

        case PlayingInterface :

        this->metadatainterface()->hide();
        this->playinginterface()->show();
        this->m_boutonrevenir->setAction(MetaDataInterface); //l'inverse de l'actuelle
        break;

        case MetaDataInterface:

        this->playinginterface()->hide();
        this->metadatainterface()->show();
        this->m_boutonrevenir->setAction(PlayingInterface);// ^
        break;
    }
}

void NutshComunicator::place(float coef) {

    coef = 1;
    m_metadatainterface->place(0);
    m_progressinterface->move(190, 290);
    m_progressinterface->resize(400, 60);
    m_metadatainterface->move(161, 90);

    m_playinginterface->place(coef);

    m_progressinterface->place(coef);
    m_playlistinterface->place(coef);
    m_searchlineinterface->place(coef);
    m_boutonrevenir->place(coef);
}

void NutshComunicator::scanFolders() {

#ifndef STAGING
    NutshIndexer* indexer = new NutshIndexer(this->getSqlControl()->getFolderList(), this);
    indexer->start();
#endif
}
/* ----------Fonctions retournant les interfaces pour communiquer entre les diff�rentes parties du programme -------*/
NutshMetaDataInterface* NutshComunicator::metadatainterface() {

    return m_metadatainterface;
}

//NutshDriveInterface* NutshComunicator::driveinterface() {
//
//    return m_driveinterface;
//}

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

void NutshComunicator::setStatus(const QString &status) {

    m_bar->showMessage(status);
}

QStatusBar* NutshComunicator::bar() {

    return m_bar;
}

NutshSqlSaver* NutshComunicator::getSqlControl() {

    return sqlControl;
}

QMainWindow* NutshComunicator::getParent() {
    return m_parent;
}

NutshSystemTrayIcon* NutshComunicator::systemtrayicon() {
    return m_tray;
}


