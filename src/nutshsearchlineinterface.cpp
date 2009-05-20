#include "nutshsearchlineinterface.h"
#include "nutshcomunicator.h"
#include <QDebug>

NutshSearchLineInterface::NutshSearchLineInterface(NutshComunicator* corePath)
{
    core = corePath;

    searchLine = new QLineEdit;
    nouvelleListe = new QPushButton("+", this);
    organisation = new QHBoxLayout;
    actionsPlus = new QMenu(this);
    nouvelleListe->setMenu(actionsPlus);
    organisation->addWidget(searchLine);
    organisation->addWidget(nouvelleListe);
    this->setLayout(organisation);
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
    
    if(searchLine->text() != "") {
        core->metadatainterface()->getWordMetaData(query);
        core->metadatainterface()->swapToList();

        if(core->metadatainterface()->getListWidget()->getItems().count() != 0) {

            nouvelleListe->setEnabled(true);
        }
    }
    else {

        core->playinginterface()->swapToPlay();
        nouvelleListe->setEnabled(false);
    }
}

void NutshSearchLineInterface::keyPressEvent(QKeyEvent* event) {

    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {

        event->accept();

        if(core->metadatainterface()->getListWidget()->getItems().count() != 0) {

            core->playinginterface()->load(
                    core->metadatainterface()->getListWidget()->getItems().value(0)
                    );

            core->playinginterface()->load(
                    core->metadatainterface()->getListWidget()->getItems()
                    );
            core->playinginterface()->swapToPlay();

        }
    } else if (event->key() == Qt::Key_Space) {

        core->playinginterface()->pauseByKey(event);

    } else {

        event->ignore();
    }
}

void NutshSearchLineInterface::activate() {

    searchLine->setFocus();
}

