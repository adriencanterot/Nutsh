#include "nutshmetadatainterface.h"
#include "nutshcomunicator.h"

NutshMetaDataInterface::NutshMetaDataInterface(NutshComunicator* corePath)
{

    //init & alloc
    core = corePath;

    layout = new QVBoxLayout;
    metadatas = new NutshMetaDataList;
    importer = new QPushButton("importer le contenu de cette liste");

    //placement
    layout->addWidget(metadatas);
    layout->addWidget(importer);

    importer->hide();

    this->setLayout(layout);

    this->load(NutshSqlSaver::getMetaDatas("SELECT * FROM bibliotheque"));

    qDebug() << "NutshMetaDataInterface : initialized";
}

void NutshMetaDataInterface::getSqlMetaData(QString query) {

}

void NutshMetaDataInterface::getDirMetaData(QModelIndex directory) {

    this->setPath(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()));

    if(!metadatas->isEmpty()) {

        this->swapToList();
        importer->show();
    }
}

void NutshMetaDataInterface::getDirMetaData(QString directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

    if(!QDir(directory).entryList(filtre).isEmpty()) {

        this->swapToList();
        this->setPath(QDir::toNativeSeparators(directory));

        importer->show();
    } else {

        core->playinginterface()->swapToPlay();
    }
}

void NutshMetaDataInterface::getWordMetaData(QString word){

    metadatas->clearList();

    for(int i = 0;i<metaList.count();i++) {

        if(metaList.value(i).contains(word)) {

            metadatas->append(metaList.value(i));
        }
    }
}



void NutshMetaDataInterface::sigandslots() {

    connect(metadatas, SIGNAL(clicked(NutshMetaData)), this, SLOT(swapWidgets(NutshMetaData)));
    connect(importer, SIGNAL(clicked()), this, SLOT(importerContent()));
}



void NutshMetaDataInterface::swapWidgets(NutshMetaData data) {

    core->playinginterface()->swapToPlay();
    core->playinginterface()->load(data);
    core->playinginterface()->load(metadatas->getItems());
}

void NutshMetaDataInterface::swapToList() {

    core->playinginterface()->hide();
    core->droite()->removeWidget(core->playinginterface());

    core->droite()->addWidget(core->metadatainterface());
    core->metadatainterface()->show();
}

void NutshMetaDataInterface::load(QList<NutshMetaData> liste) {

    metaList = liste;

    metadatas->clearList();
    metadatas->load(liste);
}

QList<NutshMetaData> NutshMetaDataInterface::actualContent() {

    return metadatas->getItems();
}

void NutshMetaDataInterface::setPath(QString chemin) {

    QStringList filter;
    filter << FORMATS_SUPPORTES;
    QDirIterator path(chemin, filter);
    metaList.clear();

    while(path.hasNext()) {

        NutshMetaData cache(path.next());
        metaList.append(cache);
    }

    if(!metaList.isEmpty()) {

        this->swapToList();
    }

    metadatas->load(metaList);
}

void NutshMetaDataInterface::importerContent() {

    NutshSqlSaver::inserer(metaList, "bibliotheque");
}

void NutshMetaDataInterface::reset() {

    metaList.clear();
    metaList = NutshSqlSaver::getMetaDatas("SELECT * FROM bibliotheque");
}
