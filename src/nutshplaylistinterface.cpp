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
    //ajoute les playlist dans la liste de lecture (enlève les anciennes).

    REQUETE("SELECT name FROM listeDeLecture");
    liste->clear();

    liste->addItem("Bibliothèque");
    liste->addItem("Les plus écoutées");
    liste->addItem("Les dernières ajoutées");
    liste->addItem("Écoutées récemment");
        while(requete.next()){
    liste->addItem(NutshSqlSaver::normalStringFormat(requete.value(0).toString()));
    //ajout au format normal dans la liste
        }

}

void NutshPlayListInterface::initButtons() {

    nouvelleListe = new QPushButton("", this);
    nouvelleListe->setToolTip("Créer une playlist");
    nouvelleListe->setProperty("newPlaylistButton", true);

    importer = new QPushButton("", this);
    importer->setToolTip("Importer un dossier musical");
    importer->setProperty("importButton", true);
}

void NutshPlayListInterface::addListe() {
    //nouvelle liste de lecture avec nom.

    nommerListe = new QDialog(this);
    layoutNommerListe = new QVBoxLayout;
    ok = new QPushButton("ok");
    nomTable = new QLineEdit;

    layoutNommerListe->addWidget(nomTable);
    layoutNommerListe->addWidget(ok);
    nommerListe->setLayout(layoutNommerListe);

    connect(ok, SIGNAL(clicked()), nommerListe, SLOT(accept()));
    connect(nommerListe, SIGNAL(accepted()), this, SLOT(nouvelleTable()));

    nommerListe->exec();
}

void NutshPlayListInterface::nouvelleTable() {
    //nouvelle liste de lecture.

    QString nom = nomTable->text();
    
    if(nom.isEmpty()) {

        setNewName(nom); //si le nom est vide, nouveau nom
    }

    core->getSqlControl()->nouvelleListe(nom);
    this->refresh();
}

void NutshPlayListInterface::sigandslots() {

    connect(nouvelleListe, SIGNAL(clicked()), this, SLOT(addListe()));
    connect(importer, SIGNAL(clicked()), this, SLOT(importWindow()));
}

void NutshPlayListInterface::importWindow() {
    //importation de médias dans la bibliothèque

    QString path = QFileDialog::getExistingDirectory(this, "", "/");

    core->progressinterface()->import(path);
}

void NutshPlayListInterface::addListeFromSearch() {
    //ajoute les résultats de la recherche dans une nouvelle playlsit

    QString listName = QInputDialog::getText(this, "Nouvelle Liste", "Le nom de votre liste");

    if(listName.isEmpty()) {

        setNewName(listName); // si le nom est vide, nouveau nom.
    }

    core->getSqlControl()->nouvelleListe(listName);
    core->getSqlControl()->inserer(core->metadatainterface()->getListWidget()->getItems(), listName);
    this->refresh();
}

void NutshPlayListInterface::addLastRead() {
    //rajoute les derniers morceaux lu dans une nouvelle playlist

    QString listName = QInputDialog::getText(this, "Nouvelle Liste", "Le nom de votre liste");

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

        if(liste->item(i)->text().contains("sans titre", Qt::CaseInsensitive)) {

            numbAfterList++; //si le morceau trouvé contient "Sans Titre" on rajoute un nombre pour ne pas avoir le même nom
        }
    }

    old = QString("Sans titre %1").arg(numbAfterList);
}

void NutshPlayListInterface::place(float coef) {

    coef = 0;

    liste->move(0, 100);

    int x = 40;
    int y = 299;

    nouvelleListe->move(x, y);
    importer->move(x + 36, y);
}


