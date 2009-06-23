#include "nutshsearchlineinterface.h"
#include "nutshcomunicator.h"
#include <QDebug>

NutshSearchLineInterface::NutshSearchLineInterface(NutshComunicator* corePath)
{
    core = corePath;

    searchLine = new QLineEdit(this);
    searchLine->setProperty("searchLine", true);
    nouvelleListe = new QPushButton("", this);
    nouvelleListe->setProperty("nouvelleListe_nutshsearchlineinterface", true);

    //placement des boutons

    actionsPlus = new QMenu(this);
    nouvelleListe->setMenu(actionsPlus); // mise en place du menu pour le bouton "+"

    qDebug() << "NutshSearchLineInterface : initialized";
}

void NutshSearchLineInterface::sigandslots() {

    connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(showResults(QString)));

    actionsPlus->addAction("Resultats de la recherche dans une playlist", core->playlistinterface(),
                           SLOT(addListeFromSearch()));

    actionsPlus->addAction("5 derniers morceaux lu dans une liste de lecture", core->playlistinterface(),
                           SLOT(addLastRead()));
}
void NutshSearchLineInterface::showResults(QString query) {
    
    if(searchLine->text() != "") { //affiche la liste des morceaux uniquement si il y a du texte entr�

        core->metadatainterface()->getWordMetaData(query);
        core->swapInterface(MetaData);


    } else { // sinon, affichage de l'interface "Play"

        core->swapInterface(Playing);
    }
}

void NutshSearchLineInterface::keyPressEvent(QKeyEvent* event) {

    core->metadatainterface()->navigateByKey(event);

    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {

        searchLine->selectAll();
    }
}

void NutshSearchLineInterface::activate() {

    searchLine->setFocus();
}

void NutshSearchLineInterface::place(float coef) {

    searchLine->move(280, 26);
    nouvelleListe->move(530, 26);
}

