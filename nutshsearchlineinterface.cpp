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
        core->playinginterface()->hide();
        core->droite()->removeWidget(core->playinginterface());
        core->droite()->addWidget(core->metadatainterface());
        core->metadatainterface()->show();
    }
    else {
        core->metadatainterface()->hide();
        core->droite()->removeWidget(core->metadatainterface());
        core->droite()->addWidget(core->playinginterface());
        core->playinginterface()->show();
    }
}

