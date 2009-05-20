#include "nutshmetadatainterface.h"
#include "nutshcomunicator.h"

NutshMetaDataInterface::NutshMetaDataInterface(NutshComunicator* corePath)
{

    //init & alloc
    core = corePath;

    layout = new QVBoxLayout;
    optionsLayout = new QHBoxLayout;
    metadatas = new NutshMetaDataList;
    importer = new QPushButton("Importer");
    toBibliotheque = new QPushButton("Bibliothèque");

    //placement
    layout->addWidget(metadatas);
    layout->addLayout(optionsLayout);

    optionsLayout->addWidget(importer);
    optionsLayout->addWidget(toBibliotheque);
    optionsLayout->addSpacing(200);

    importer->hide();
    toBibliotheque->hide();

    this->setLayout(layout);

    this->load(core->getSqlControl()->getMetaDatas("SELECT * FROM bibliotheque"));


    qDebug() << "NutshMetaDataInterface : initialized";
}

void NutshMetaDataInterface::getSqlMetaData(QString query) {

}

void NutshMetaDataInterface::getDirMetaData(QModelIndex directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

    if(!QDir(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()))
        .entryList(filtre).isEmpty()) {

        this->setPath(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()));
    }
}

void NutshMetaDataInterface::getDirMetaData(QString directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

    if(!QDir(directory).entryList(filtre).isEmpty()) {

        this->swapToList();
        this->setPath(QDir::toNativeSeparators(directory));

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
    if(!metadatas->isEmpty()) {

        metadatas->topLevelItem(0)->setSelected(true);
    }
}



void NutshMetaDataInterface::sigandslots() {

    connect(metadatas, SIGNAL(clicked(NutshMetaData)), this, SLOT(swapWidgets(NutshMetaData)));
    connect(importer, SIGNAL(clicked()), this, SLOT(importerContent()));
    connect(this, SIGNAL(contentTypeChanged(ContentType)), this, SLOT(changeDisposition(ContentType)));
    connect(toBibliotheque, SIGNAL(clicked()), this, SLOT(reset()));
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

    emit contentTypeChanged(Dir);

    metadatas->load(metaList);
}

void NutshMetaDataInterface::importerContent() {

    core->getSqlControl()->inserer(metaList, "bibliotheque");
}

void NutshMetaDataInterface::reset() {

    metaList.clear();
    metaList = core->getSqlControl()->getMetaDatas("SELECT * FROM bibliotheque");
    this->load(metaList);
    emit contentTypeChanged(Entire);
}

NutshMetaDataList* NutshMetaDataInterface::getListWidget() {

    return metadatas;
}

void NutshMetaDataInterface::changeDisposition(ContentType type) {

    switch(type) {

        case Dir: //modifications de cette interface si le contenu vient d'un dossier
            importer->show();
            toBibliotheque->show();

            break;

        case Entire: //si le contenu est toute la bibliotheque
            importer->hide();
            toBibliotheque->hide();
            break;

        case Playlist: //si le contenu vient d'une playlist
            importer->hide();
            toBibliotheque->show();
            this->swapToList();
            break;


        case Empty: // si il n'y a pas de contenu
            importer->hide();
            break;
        }
}

void NutshMetaDataInterface::refreshInterface(ContentType type) {

    emit this->contentTypeChanged(type);
}
