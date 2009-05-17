#include "nutshsearchlineinterface.h"
#include "nutshcomunicator.h"
#include <QDebug>

NutshSearchLineInterface::NutshSearchLineInterface(NutshComunicator* corePath)
{
    core = corePath;
    searchLine = new QLineEdit;
    organisation = new QVBoxLayout;
    organisation->addWidget(searchLine);
    this->setLayout(organisation);
    qDebug() << "NutshSearchLineInterface : initialized";
}

void NutshSearchLineInterface::sigandslots() {
    connect(searchLine, SIGNAL(textChanged(QString)), this, SLOT(showResults(QString)));
}
void NutshSearchLineInterface::showResults(QString query) {
    
    if(searchLine->text() != "") {
        core->metadatainterface()->getWordMetaData(query);
        core->metadatainterface()->swapToList();
    }
    else {

        core->playinginterface()->swapToPlay();
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

