#include "nutshcomunicator.h"
#include "nutshplaylistinterface.h"

NutshPlayListInterface::NutshPlayListInterface(NutshComunicator* corePath, QWidget *parent) : QWidget(parent)
{

    core = corePath;

    this->setFixedWidth(WIDTH_LEFT);

    layout = new QVBoxLayout;
    layoutBouton = new QHBoxLayout;
    liste = new NutshPlaylistList(core, this);

    refresh();

    initButtons();

    //placement

    layout->addWidget(liste);
    layoutBouton->addWidget(nouvelleListe);
    layoutBouton->addWidget(importer);
    layout->addLayout(layoutBouton);
    this->setLayout(layout);


    qDebug() << "NutshPlaylistInterface : initialized";

}

void NutshPlayListInterface::refresh() {
    //ajoute les playlist dans la liste de lecture (enlève les anciennes).

    REQUETE("SELECT name FROM listeDeLecture");
    liste->clear();

    while(requete.next()) {

        liste->addItem(NutshSqlSaver::normalStringFormat(requete.value(0).toString())); //ajout au format normal dans la liste
    }

}

void NutshPlayListInterface::initButtons() {

    nouvelleListe = new QPushButton("nouvelle");
    nouvelleListe->setToolTip("creer une nouvelle playlist");

    importer = new QPushButton("Importer");
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

    core->progressinterface()->setMaximum(0);
    core->progressinterface()->setTopLabelText("Scan du dossier en cours...");

    core->scannerAccess()->indexer(path);
    core->metadatainterface()->reset();
}

void NutshPlayListInterface::addListeFromSearch() {
    //ajoute les résultats de la recherche dans une nouvelle playlsit

    QString listName = QInputDialog::getText(this, "Nouvelle Liste", "Le nom de votre liste");

    if(listName.isEmpty()) {

        setNewName(listName); // si le nom est vide, nouveau nom.
    }

    core->getSqlControl()->nouvelleListe(listName);
    core->progressinterface()->import(core->metadatainterface()->getListWidget()->getItems(), listName);
    this->refresh();
}

void NutshPlayListInterface::addLastRead() {
    //rajoute les derniers morceaux lu dans une nouvelle playlist

    QString listName = QInputDialog::getText(this, "Nouvelle Liste", "Le nom de votre liste");

    if(listName.isEmpty()) {

        setNewName(listName); // si le nom est vide, nouveau nom.
    }

    core->getSqlControl()->nouvelleListe(listName);

    core->progressinterface()->import(core->playinginterface()->getLastRead(), listName);
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


