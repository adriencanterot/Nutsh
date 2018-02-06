 #include "core.h"

Core::Core(QMainWindow *parent)
{

    m_dictionnary << "the " << "the";
    m_bar = new QStatusBar;
    m_parent = parent;
    m_central = new QWidget;
    m_tray = new SystemtrayIcon(this->getParent());
    m_tray->setIcon(qApp->windowIcon());
    m_tray->show();
    this->m_interface = MetaDataInterface;


    //création de l'objet de control sur la base de donnée
    sqlControl = new SqlManager;
    sqlControl->connect();
    m_searchlineinterface = new SearchlineInterface(this);
    m_playlistinterface = new PlaylistInterface(this);
    m_editinterface = new EditInterface(this);
    m_metadatainterface = new MetadataInterface(this);
//    m_driveinterface = new DriveInterface(this);

    m_metadatainterface->setParent(m_central);
    m_searchlineinterface->setParent(m_central);
    m_playlistinterface->setParent(m_central);

    //m_driveinterface->setParent(m_central);

    m_searchlineinterface->setFocus();

    m_playlistinterface->sigandslots();
    m_searchlineinterface->sigandslots();
    m_metadatainterface->sigandslots();
//    m_driveinterface->sigandslots();

    //création du scanner pour les médias

    afterLaunch();
    qDebug() << "Core : Transimission de toutes les interfaces a MainWindow";
}

void Core::afterLaunch() {

    m_playinginterface = new class PlayingInterface(this);
    m_progressinterface = new class ProgressInterface(this);
    m_playbox = new class Playbox(this);
    m_playbox->setParent(m_central);

    m_playinginterface->getActionsButtons()->setParent(m_central);

    m_playinginterface->setParent(m_central);

    m_boutonrevenir = new NutshBoutonRevenir(m_central);
    connect(m_boutonrevenir, SIGNAL(clicked(InterfaceName)), this, SLOT(swapInterface(InterfaceName)));

    m_progressinterface->setParent(m_central);
    m_editinterface->setParent(m_central);

    m_playinginterface->hide();
    m_progressinterface->hide();
    m_editinterface->hide();

//    m_updater = new Updater(this);

//    m_updater->setParent(m_central);
//    m_updater->hide();

    m_playinginterface->sigandslots();

    this->place(1);

}
QWidget *Core::initInterfaces() {
    //mise en places dans les layouts et envoi dans la fenêtre principale.
    return m_central;
}

void Core::swapInterface(InterfaceName name) {

    this->m_interface = name;

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

void Core::place(float coef) {

    coef = 1;
    m_metadatainterface->place(0);
    m_progressinterface->move(190, 290);
    m_progressinterface->resize(400, 60);
    m_metadatainterface->move(161, 76);

    m_playinginterface->place(coef);
    m_playbox->place(coef);

    m_progressinterface->place(coef);
    m_playlistinterface->place(coef);
    m_searchlineinterface->place(coef);
    m_boutonrevenir->place(coef);
    m_playbox->place(coef);
    m_editinterface->place(coef);

}

void Core::scanFolders() {

#ifndef STAGING
    Indexer* indexer = new Indexer(this->getSqlControl()->getFolderList(), this);
    indexer->start();
#endif
}
/* ----------Fonctions retournant les interfaces pour communiquer entre les différentes parties du programme -------*/
MetadataInterface* Core::metadatainterface() {

    return m_metadatainterface;
}

//DriveInterface* Core::driveinterface() {
//
//    return m_driveinterface;
//}

SearchlineInterface* Core::searchlineinterface() {

    return m_searchlineinterface;
}

PlaylistInterface* Core::playlistinterface() {

    return m_playlistinterface;
}

class PlayingInterface* Core::playinginterface() {

    return m_playinginterface;
}

class ProgressInterface* Core::progressinterface() {

    return m_progressinterface;
}

void Core::setStatus(const QString &status) {

    m_bar->showMessage(status);
}

QStatusBar* Core::bar() {

    return m_bar;
}

SqlManager* Core::getSqlControl() {

    return sqlControl;
}

QMainWindow* Core::getParent() {
    return m_parent;
}

SystemtrayIcon* Core::systemtrayicon() {
    return m_tray;
}
class Playbox* Core::playbox() {
    return m_playbox;
}

QStringList Core::dictionnary() {
    return m_dictionnary;
}

InterfaceName Core::interface() const {
    return m_interface;
}

EditInterface* Core::editinterface() {
    return m_editinterface;
}
