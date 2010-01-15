#include "nutshcomunicator.h"
#include "nutshplaylistinterface.h"

NutshPlayListInterface::NutshPlayListInterface(NutshComunicator* corePath, QWidget *parent) : QWidget(parent)
{
    qDebug() << "Initializing NutshPlayListInterface...";

    core = corePath;
    this->setFixedWidth(WIDTH_LEFT);
    liste = new NutshPlaylistList(core, this);
    refresh();
    initButtons();
}

void NutshPlayListInterface::refresh(){
    //ajoute les playlist dans la liste de lecture (enl�ve les anciennes).

    liste->clear();

    liste->addItem(tr("Biblioth�que"));
    liste->addItem(tr("Les plus �cout�es"));
    liste->addItem(tr("Les derni�res ajout�es"));
    liste->addItem(tr("�cout�es r�cemment"));
    liste->addItems(core->getSqlControl()->getPlaylists());

}

void NutshPlayListInterface::initButtons() {

    nouvelleListe = new QPushButton("", this);
    nouvelleListe->setToolTip(tr("Cr�er une playlist"));
    nouvelleListe->setProperty("newPlaylistButton", true);

    importer = new QPushButton("", this);
    importer->setToolTip(tr("Importer un dossier musical"));
    importer->setProperty("importButton", true);
}


void NutshPlayListInterface::nouvelleTable() {
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

void NutshPlayListInterface::sigandslots() {

    connect(nouvelleListe, SIGNAL(clicked()), this, SLOT(nouvelleTable()));
    connect(importer, SIGNAL(clicked()), this, SLOT(importWindow()));
}

void NutshPlayListInterface::importWindow() {
    //importation de m�dias dans la biblioth�que

    QString path = QFileDialog::getExistingDirectory(this, "", "/");

    core->progressinterface()->import(path);
}

void NutshPlayListInterface::addListeFromSearch() {
    //ajoute les r�sultats de la recherche dans une nouvelle playlsit
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

void NutshPlayListInterface::addLastRead() {
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

void NutshPlayListInterface::setNewName(QString &old) {
    // si la liste n'a pas de nom le nom est Sans titre + i

    int numbAfterList = 0;

    for(int i =0;i<liste->count();i++) {

        if(liste->item(i)->text().contains(tr("sans titre"), Qt::CaseInsensitive)) {

            numbAfterList++; //si le morceau trouv� contient "Sans Titre" on rajoute un nombre pour ne pas avoir le m�me nom
        }
    }

    old = QString(tr("Sans titre %1")).arg(numbAfterList);
}

void NutshPlayListInterface::place(float coef) {

    coef = 0;
    liste->move(0, 100);

    int x = 40;
    int y = 299;

    nouvelleListe->move(x, y);
    importer->move(x + 36, y);
}
NutshPlaylistList* NutshPlayListInterface::elements() {
    return liste;
}

