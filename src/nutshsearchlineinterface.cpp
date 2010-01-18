#include "nutshsearchlineinterface.h"
#include "nutshcomunicator.h"
#include <QDebug>

NutshSearchLineInterface::NutshSearchLineInterface(NutshComunicator* corePath)
{

    qDebug() << "Initializing NutshSearchLineInterface...";
    core = corePath;
    searchLine = new QLineEdit(this);
    searchLine->setProperty("searchLine", true);
    nouvelleListe = new QPushButton("", this);
    nouvelleListe->setProperty("nouvelleListe_nutshsearchlineinterface", true);

    //placement des boutons

    actionsPlus = new QMenu(this);
    nouvelleListe->setMenu(actionsPlus); // mise en place du menu pour le bouton "+"
}

void NutshSearchLineInterface::sigandslots() {

    connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(showResults(QString)));

    actionsPlus->addAction(tr("Resultats de la recherche dans une playlist"), core->playlistinterface(),
                           SLOT(addListeFromSearch()));

    actionsPlus->addAction(tr("5 derniers morceaux lu dans une liste de lecture"), core->playlistinterface(),
                           SLOT(addLastRead()));
}
void NutshSearchLineInterface::showResults(QString query) {
    
    if(searchLine->text() == "") {
        if(core->playinginterface()->isPlaying()) {
            core->swapInterface(PlayingInterface);
            return;
        } else {
            return;
        }

    }
    //affiche la liste des morceaux uniquement si il y a du texte entré

    if(searchLine->text().startsWith(":")) {
        this->threatCommand(searchLine->text().right(searchLine->text().count()-1));
    } else {

        core->metadatainterface()->getWordMetaData(query);
        core->swapInterface(MetaDataInterface);
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

    searchLine->move(240, 26);
    nouvelleListe->move(490, 26);
}

void NutshSearchLineInterface::threatCommand(const QString& command) {
    if(command == "last") {
        core->metadatainterface()->load(core->getSqlControl()->getLastReaden(1));
    }
    else if(command == "listened") {
        core->metadatainterface()->load(core->getSqlControl()->getMostReaden(1));
    } else {
    }
}

QString NutshSearchLineInterface::value() {
    return searchLine->text();
}

