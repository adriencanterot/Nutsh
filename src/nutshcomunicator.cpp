 #include "nutshcomunicator.h"

NutshComunicator::NutshComunicator()
{

    m_bar = new QStatusBar;

    m_central = new QWidget;

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

    m_updater = new NutshUpdater(this);

    m_updater->setParent(m_central);
    m_updater->hide();

    m_playinginterface->sigandslots();

    this->place(1);
}
QWidget *NutshComunicator::initInterfaces() {
    //mise en places dans les layouts et envoi dans la fen�tre principale.
    return m_central;
}

void NutshComunicator::swapInterface(InterfaceName name) {

    switch(name) {

        case Playing :

        this->metadatainterface()->hide();
        this->playinginterface()->show();
        this->m_boutonrevenir->setAction(MetaData); //l'inverse de l'actuelle
        break;

        case MetaData:

        this->playinginterface()->hide();
        this->metadatainterface()->show();
        this->m_boutonrevenir->setAction(Playing);// ^
        break;
    }
}

void NutshComunicator::place(float coef) {

    coef = 1;

    m_progressinterface->move(190, 310);
    m_progressinterface->resize(400, 40);
    m_metadatainterface->move(161, 115);

    m_playinginterface->place(coef);
    m_metadatainterface->place(coef);
    m_progressinterface->place(coef);
    m_playlistinterface->place(coef);
    m_searchlineinterface->place(coef);
    m_boutonrevenir->place(coef);
}

void NutshComunicator::scanFolders() {

    NutshIndexer* indexer = new NutshIndexer(this->getSqlControl()->getFolderList(), this);
    indexer->start();
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

