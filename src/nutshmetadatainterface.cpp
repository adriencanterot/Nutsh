#include "nutshmetadatainterface.h"
#include "nutshcomunicator.h"

NutshMetaDataInterface::NutshMetaDataInterface(NutshComunicator* corePath)
{

    //init & alloc
    core = corePath;

    layout = new QVBoxLayout;
    optionsLayout = new QHBoxLayout;
    metadatas = new NutshMetaDataList;
    importer = new QPushButton("importer le contenu de cette liste");
    toBibliotheque = new QPushButton("Revenir a la bibliotheque");
    nouvelleListe = new QPushButton(QString::fromUtf8("Ces résultats dans une playlist"));

    //placement
    layout->addWidget(metadatas);
    layout->addLayout(optionsLayout);

    optionsLayout->addWidget(importer);
    optionsLayout->addWidget(toBibliotheque);
    optionsLayout->addWidget(nouvelleListe);

    importer->hide();
    toBibliotheque->hide();
    nouvelleListe->hide();

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

        emit contentTypeChanged(SearchResults);
        metadatas->topLevelItem(0)->setSelected(true);
    }
}



void NutshMetaDataInterface::sigandslots() {

    connect(metadatas, SIGNAL(clicked(NutshMetaData)), this, SLOT(swapWidgets(NutshMetaData)));
    connect(importer, SIGNAL(clicked()), this, SLOT(importerContent()));
    connect(this, SIGNAL(contentTypeChanged(ContentType)), this, SLOT(changeDisposition(ContentType)));
    connect(toBibliotheque, SIGNAL(clicked()), this, SLOT(reset()));
    connect(nouvelleListe, SIGNAL(clicked()), core->playlistinterface(), SLOT(addListeFromSearch()));
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

    NutshSqlSaver::inserer(metaList, "bibliotheque");
}

void NutshMetaDataInterface::reset() {

    metaList.clear();
    metaList = NutshSqlSaver::getMetaDatas("SELECT * FROM bibliotheque");
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
            nouvelleListe->hide();
            break;

        case Playlist: //si le contenu vient d'une playlist
            importer->hide();
            toBibliotheque->show();
            nouvelleListe->hide();
            this->swapToList();
            break;

         case SearchResults: //si le contenu vient d'une recherche (n'efface pas les autre boutons)
            nouvelleListe->show();


        case Empty: // si il n'y a pas de contenu
            importer->hide();
            break;
        }
}

void NutshMetaDataInterface::refreshInterface(ContentType type) {

    emit this->contentTypeChanged(type);
}




