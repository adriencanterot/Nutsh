#include "core.h"
#include "nutshplaylistinterface.h"

PlaylistInterface::PlaylistInterface(Core* corePath, QWidget *parent) : QWidget(parent)
{
    qDebug() << "Initializing PlaylistInterface...";

    core = corePath;
    this->setFixedWidth(WIDTH_LEFT);
    liste = new PlaylistList(core, this);
    refresh();
    initButtons();
}

void PlaylistInterface::refresh(){
    //ajoute les playlist dans la liste de lecture (enlève les anciennes).

    liste->clear();

    liste->addItem(tr("Bibliothèque"));
    liste->addItem(tr("Les plus écoutées"));
    liste->addItem(tr("Les dernières ajoutées"));
    liste->addItem(tr("Écoutées récemment"));
    liste->addItems(core->getSqlControl()->getPlaylists());

}

void PlaylistInterface::initButtons() {

    nouvelleListe = new QPushButton("", this);
    nouvelleListe->setToolTip(tr("Créer une playlist"));
    nouvelleListe->setProperty("newPlaylistButton", true);

    importer = new QPushButton("", this);
    importer->setToolTip(tr("Importer un dossier musical"));
    importer->setProperty("importButton", true);
}


void PlaylistInterface::nouvelleTable() {
    //nouvelle liste de lecture.
    bool ok;
    QString nom = QInputDialog::getText(this, tr("Nouvelle Liste"), tr("Le nom de votre liste"), QLineEdit::Normal, QString(), &ok);
    if(!ok) { return; }

    if(nom.isEmpty()) {

        setNewName(nom); //si le nom est vide, nouveau nom
    }

    core->getSqlControl()->nouvelleListe(nom);
    this->refresh();
}

void PlaylistInterface::sigandslots() {

    connect(nouvelleListe, SIGNAL(clicked()), this, SLOT(nouvelleTable()));
    connect(importer, SIGNAL(clicked()), this, SLOT(importWindow()));
}

void PlaylistInterface::importWindow() {
    //importation de médias dans la bibliothèque

    QString path = QFileDialog::getExistingDirectory(this, "", "/");

    core->progressinterface()->import(path);
}

void PlaylistInterface::addListeFromSearch() {
    //ajoute les résultats de la recherche dans une nouvelle playlsit
    bool ok;
    QString listName = QInputDialog::getText(this, tr("Nouvelle Liste"), tr("Le nom de votre liste"), QLineEdit::Normal, core->searchlineinterface()->value(), &ok);
    if(!ok) { return; }
    if(listName.isEmpty()) {

        setNewName(listName); // si le nom est vide, nouveau nom.
    }

    core->getSqlControl()->nouvelleListe(listName);
    core->getSqlControl()->inserer(core->metadatainterface()->getListWidget()->getItems(), listName);
    this->refresh();
}

void PlaylistInterface::addLastRead() {
    //rajoute les derniers morceaux lu dans une nouvelle playlist
    bool ok;
    QString listName = QInputDialog::getText(this, tr("Nouvelle Liste"), tr("Le nom de votre liste"), QLineEdit::Normal, QString(), &ok);
    if(!ok) { return; }

    if(listName.isEmpty()) {

        setNewName(listName); // si le nom est vide, nouveau nom.
    }

    core->getSqlControl()->nouvelleListe(listName);

    core->getSqlControl()->inserer(core->playinginterface()->getLastRead(), listName);
    this->refresh();
}

void PlaylistInterface::setNewName(QString &old) {
    // si la liste n'a pas de nom le nom est Sans titre + i

    int numbAfterList = 0;

    for(int i =0;i<liste->count();i++) {

        if(liste->item(i)->text().contains(tr("sans titre"), Qt::CaseInsensitive)) {

            numbAfterList++; //si le morceau trouvé contient "Sans Titre" on rajoute un nombre pour ne pas avoir le même nom
        }
    }

    old = QString(tr("Sans titre %1")).arg(numbAfterList);
}

void PlaylistInterface::place(float coef) {

    coef = 0;
    liste->move(0, 100);

    int x = 40;
    int y = 299;

    nouvelleListe->move(x, y);
    importer->move(x + 36, y);
}
PlaylistList* PlaylistInterface::elements() {
    return liste;
}

void PlaylistInterface::newListFromContent(QList<Metadata> liste) {
    bool ok;
    QString listName = QInputDialog::getText(this, tr("Nouvelle Liste"), tr("Le nom de votre liste"), QLineEdit::Normal, QString(), &ok);
    if(!ok) { return; }

    if(listName.isEmpty()) {

        setNewName(listName); // si le nom est vide, nouveau nom.
    }

    core->getSqlControl()->nouvelleListe(listName);
    core->getSqlControl()->inserer(liste, listName);
    this->refresh();
}
void PlaylistInterface::newListFromContent() {
    this->newListFromContent(core->playbox()->getFileattente());
}

QString PlaylistInterface::current() const {
    return liste->currentItem()->text();
}
