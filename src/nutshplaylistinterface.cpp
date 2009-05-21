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

    if(!core->getSqlControl()->tableExists(NutshSqlSaver::sqlStringFormat("bibliotheque"))) {

        REQUETE("create table bibliotheque ( artiste text, album text, titre text, date text, genre text, description text, track text, chemin text, cheminImage text, duree text, enregistrement text, derniereLecture text, compteur text)");

    }

    if(!core->getSqlControl()->tableExists(NutshSqlSaver::sqlStringFormat("bibliotheque"))){

        REQUETE("CREATE TABLE listeDeLecture (name text, ordre text)");
    }
    //placement

    layout->addWidget(liste);
    layoutBouton->addWidget(nouvelleListe);
    layoutBouton->addWidget(importer);
    layout->addLayout(layoutBouton);
    this->setLayout(layout);


    qDebug() << "NutshPlaylistInterface : initialized";

}

void NutshPlayListInterface::refresh() {

    REQUETE("SELECT name FROM listeDeLecture");
    liste->clear();

    while(requete.next()) {

        liste->addItem(NutshSqlSaver::normalStringFormat(requete.value(0).toString()));
    }

}

void NutshPlayListInterface::initButtons() {

    nouvelleListe = new QPushButton("nouvelle");
    nouvelleListe->setToolTip("creer une nouvelle playlist");

    importer = new QPushButton("Importer");
}

void NutshPlayListInterface::addListe() {

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

    core->getSqlControl()->nouvelleListe(nomTable->text());
    this->refresh();
}

void NutshPlayListInterface::sigandslots() {

    connect(nouvelleListe, SIGNAL(clicked()), this, SLOT(addListe()));
    connect(importer, SIGNAL(clicked()), this, SLOT(importWindow()));
}

void NutshPlayListInterface::importWindow() {

    QString path = QFileDialog::getExistingDirectory(this, "", "/");
    core->progressinterface()->setMaximum(0);
    core->progressinterface()->setTopLabelText("Scan du dossier en cours...");
    core->scannerAccess()->indexer(path, "bibliotheque");
    core->metadatainterface()->reset();
}

void NutshPlayListInterface::addListeFromSearch() {

    QString listName = QInputDialog::getText(this, "Nouvelle Liste", "Le nom de votre liste");

    if(listName.isEmpty()) {

        setNewName(listName);
    }

    core->getSqlControl()->nouvelleListe(listName);
    core->progressinterface()->import(core->metadatainterface()->getListWidget()->getItems(), listName);
    this->refresh();
}

void NutshPlayListInterface::addLastRead() {

    QString listName = QInputDialog::getText(this, "Nouvelle Liste", "Le nom de votre liste");

    if(listName.isEmpty()) {

        setNewName(listName);
    }

    core->getSqlControl()->nouvelleListe(listName);

    core->progressinterface()->import(core->playinginterface()->getLastRead(), listName);
    this->refresh();
}

void NutshPlayListInterface::setNewName(QString &old) {

    int numbAfterList = 0;

    for(int i =0;i<liste->count();i++) {

        if(liste->item(i)->text().contains("sans titre", Qt::CaseInsensitive)) {

            numbAfterList++;
        }
    }

    old = QString("Sans titre %1").arg(numbAfterList);
}


