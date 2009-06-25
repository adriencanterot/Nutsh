#include "nutshmetadatainterface.h"
#include "nutshcomunicator.h"

NutshMetaDataInterface::NutshMetaDataInterface(NutshComunicator* corePath)
{
    //init & alloc
    core = corePath;
    this->setStyleSheet("border : 1px solid black");

    indexSelected = 0;
    metadatas = new NutshMetaDataList(core);
    metadatas->setParent(this);
    importer = new QPushButton("Importer", this);
    toBibliotheque = new QPushButton("Bibliothèque", this);
    this->setStyleSheet("min-height : 240px;");

    //placement
    importer->hide();
    toBibliotheque->hide();

    this->load(core->getSqlControl()->getMetaDatas("bibliotheque"));

    qDebug() << "NutshMetaDataInterface : initialized";
}


void NutshMetaDataInterface::getDirMetaData(const QModelIndex &directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

//    if(!QDir(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()))
//        .entryList(filtre).isEmpty()) {
//
//        this->setPath(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()));
//    }
}

void NutshMetaDataInterface::getDirMetaData(const QString &directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

    if(!QDir(directory).entryList(filtre).isEmpty()) {

        core->swapInterface(MetaData);
        this->setPath(QDir::toNativeSeparators(directory));

    } else {

        core->swapInterface(Playing);
    }
}

void NutshMetaDataInterface::getWordMetaData(const QString &word){

    metadatas->clearList();

    for(int i = 0;i<metaList.count();i++) {

        if(metaList.value(i).contains(word)) {

            metadatas->append(metaList.value(i));
        }
    }
    if(!metadatas->isEmpty()) {

        metadatas->topLevelItem(0)->setSelected(true);
        metadatas->setCurrentItem(metadatas->topLevelItem(0));
    }
}



void NutshMetaDataInterface::sigandslots() {

    connect(metadatas, SIGNAL(clicked(NutshMetaData)), this, SLOT(swapWidgets(NutshMetaData)));
    connect(importer, SIGNAL(clicked()), this, SLOT(importerContent()));
    connect(this, SIGNAL(contentTypeChanged(ContentType)), this, SLOT(changeDisposition(ContentType)));
    connect(toBibliotheque, SIGNAL(clicked()), this, SLOT(reset()));
}



void NutshMetaDataInterface::swapWidgets(const NutshMetaData &data) {

    core->swapInterface(Playing);
    core->playinginterface()->load(data);
    core->playinginterface()->load(metadatas->getItems());
}

void NutshMetaDataInterface::load(QList<NutshMetaData> liste) {

    metaList = liste;

    metadatas->clearList();
    metadatas->load(liste);
}

QList<NutshMetaData> NutshMetaDataInterface::actualContent() const {

    return metadatas->getItems();
}

void NutshMetaDataInterface::setPath(const QString &chemin) {

    QStringList filter;
    filter << FORMATS_SUPPORTES;
    QDirIterator path(chemin, filter);
    metaList.clear();

    while(path.hasNext()) {

        NutshMetaData cache(path.next());
        metaList.append(cache);
    }

    if(!metaList.isEmpty()) {

        core->swapInterface(MetaData);
    }

    emit contentTypeChanged(Dir);

    metadatas->load(metaList);
}

void NutshMetaDataInterface::importerContent() {

    core->getSqlControl()->inserer(metaList, "bibliotheque");
}

void NutshMetaDataInterface::reset() {

    metaList.clear();
    metaList = core->getSqlControl()->getMetaDatas("bibliotheque");
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
            core->swapInterface(MetaData);
            break;


        case Empty: // si il n'y a pas de contenu
            importer->hide();
            break;
        }
}

void NutshMetaDataInterface::refreshInterface(ContentType type) {

    emit this->contentTypeChanged(type);
}

void NutshMetaDataInterface::navigateByKey(QKeyEvent *event) {

    switch(event->key()) {

        case Qt::Key_Return:
            core->playinginterface()->load(this->getListWidget()->getItems().value(indexSelected));
            core->playinginterface()->load(this->getListWidget()->getItems());
            core->swapInterface(Playing);
            break;

        case Qt::Key_Down:

            if(this->getListWidget()->topLevelItem(indexSelected+1) != NULL) {

                this->indexSelected = this->getListWidget()->indexOfTopLevelItem(this->getListWidget()->currentItem());
                this->getListWidget()->topLevelItem(indexSelected)->setSelected(false);
                this->indexSelected++;
                this->getListWidget()->setCurrentItem(this->getListWidget()->topLevelItem(indexSelected));
                this->getListWidget()->currentItem()->setSelected(true);

                qDebug() << this->indexSelected << this->getListWidget()->indexOfTopLevelItem(this->getListWidget()->currentItem());

            }
            break;

        case Qt::Key_Up:

            if(this->getListWidget()->topLevelItem(indexSelected-1) != NULL) {

                this->indexSelected = this->getListWidget()->indexOfTopLevelItem(this->getListWidget()->currentItem());
                this->getListWidget()->currentItem()->setSelected(false);
                this->indexSelected--;
                this->getListWidget()->setCurrentItem(this->getListWidget()->topLevelItem(indexSelected));
                this->getListWidget()->currentItem()->setSelected(true);

                qDebug() << this->indexSelected << this->getListWidget()->indexOfTopLevelItem(this->getListWidget()->currentItem());

            }
            break;
        }
    }

void NutshMetaDataInterface::place(float coef) {

    this->move(160, 90);
    this->setStyleSheet("min-width : 440px;");
}

QList<NutshMetaData> NutshMetaDataInterface::totalContent() const {

    return metaList;
}

