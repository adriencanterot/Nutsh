#include "nutshcomunicator.h"
#include "nutshplaylistinterface.h"
NutshPlayListInterface::NutshPlayListInterface(NutshComunicator* corePath, QWidget *parent) : QWidget(parent)
{
    core = corePath;
    this->setFixedWidth(250);
    layout = new QVBoxLayout;
    layoutBouton = new QHBoxLayout;
    liste = new QListWidget;
    nouvelElement = new QListWidgetItem;
    refresh();
    initButtons();
//    REQUETE("create table bibliotheque ( artiste text, album text, titre text, date text, genre text, description text, track text, chemin text, cheminImage text, duree text, enregistrement text, derniereLecture text, compteur text)");
//    REQUETE("CREATE TABLE listeDeLecture (name text, ordre text)");
    //placement
    layout->addWidget(liste);
    layoutBouton->addWidget(nouvelleListe);
    layoutBouton->addWidget(nouvelleListeMagique);
    layoutBouton->addWidget(importer);
    layout->addLayout(layoutBouton);
    this->setLayout(layout);
    connect(nouvelleListe, SIGNAL(clicked()), this, SLOT(addListe()));
    qDebug() << "NutshPlaylistInterface : initialized";

}
void NutshPlayListInterface::refresh() {
    REQUETE("SELECT name FROM listeDeLecture");
    liste->clear();
    while(requete.next()) {
        liste->addItem(requete.value(0).toString());
    }
}
void NutshPlayListInterface::initButtons() {
    nouvelleListe = new QPushButton("new");
    nouvelleListe->setToolTip("creer une nouvelle playlist");
    nouvelleListeMagique = new QPushButton("magic");
    nouvelleListeMagique->setToolTip("Cree une nouvelle liste magique");
    importer = new QPushButton("add");
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
    NutshSqlSaver::nouvelleListe(nomTable->text());
    this->refresh();
}
void NutshPlayListInterface::sigandslots() {
    connect(nouvelleListe, SIGNAL(clicked()), this, SLOT(addListe()));
    connect(importer, SIGNAL(clicked()), this, SLOT(importWindow()));
}
void NutshPlayListInterface::importWindow() {
    QString path = QFileDialog::getExistingDirectory(this, "", "/");
    core->scannerAccess()->indexer(path);
    NutshSqlSaver::inserer(core->scannerAccess()->sortie(), "bibliotheque");
}
