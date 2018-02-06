#include "metadatainterface.h"
#include "core.h"

MetadataInterface::MetadataInterface(Core* corePath)
{
    qDebug() << "Initializing MetadataInterface...";
    //init & alloc
    core = corePath;
    contentType = Entire;
    searchResults = new QLabel;
    core->bar()->addPermanentWidget(searchResults);

    indexSelected = 0;
    metadatas = new MetadataList(core);
    metadatas->setParent(this);
    importer = new QPushButton(tr("Importer"), this);
    //placement
    importer->hide();
    entireList = core->getSqlControl()->getMetaDatas();
    this->load(entireList);
}


void MetadataInterface::getDirMetaData(const QModelIndex &directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

//    if(!QDir(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()))
//        .entryList(filtre).isEmpty()) {
//
//        this->setPath(QDir::toNativeSeparators(core->driveinterface()->getDir()->path()+"/"+directory.data().toString()));
//    }
}

void MetadataInterface::getDirMetaData(const QString &directory) {

    QStringList filtre;
    filtre << FORMATS_SUPPORTES;

    if(!QDir(directory).entryList(filtre).isEmpty()) {

        core->swapInterface(MetaDataInterface);
        this->setPath(QDir::toNativeSeparators(directory));

    } else {

        core->swapInterface(PlayingInterface);
    }
}

void MetadataInterface::getWordMetaData(const QString &word){

    metadatas->clearList();
    indexSelected = 0; // remet à zero le comtpeur pour l'index au clavier.
    int o = 0;
    QList<Metadata> knowDominant = entireList;
    QList<Metadata> results;
    searchResultType dominant = dominantType(knowDominant, word);
    
    for(int i = 0;i < entireList.count();i++) {

        if(entireList.value(i).contains(word) != Nothing) {
            if(dominant == Song) {
                o++;
                if(o > 20) { break; }
            }
            results.append(entireList.value(i));
        }
    }

    metadatas->load(results);


    searchResults->setText(QString("%1 resultats").arg(metadatas->count()));

    if(metadatas->count() < 5 && metadatas->count() != 0) {
        metadatas->setIconSize(QSize(metadatas->height()/(metadatas->count())-22,metadatas->height()/(metadatas->count())-22));
    }
    if(!metadatas->isEmpty()) {

        metadatas->item(0)->setSelected(true);
        metadatas->setCurrentItem(metadatas->item(0));
    }
}



void MetadataInterface::sigandslots() {

    connect(metadatas, SIGNAL(clicked(Metadata)), this, SLOT(swapWidgets(Metadata)));
    connect(importer, SIGNAL(clicked()), this, SLOT(importerContent()));
    connect(this, SIGNAL(contentTypeChanged(ContentType)), this, SLOT(changeDisposition(ContentType)));
}



void MetadataInterface::swapWidgets(Metadata data) {

    core->swapInterface(PlayingInterface);
    core->playinginterface()->load(data);
    core->playinginterface()->load(metadatas->getItems());
}

void MetadataInterface::load(QList<Metadata> liste) {

    metaList = liste;

    metadatas->clearList();
    metadatas->load(liste);
}

QList<Metadata> MetadataInterface::actualContent() const {

    return metadatas->getItems();
}

void MetadataInterface::setPath(const QString &chemin) {

    QStringList filter;
    filter << FORMATS_SUPPORTES;
    QDirIterator path(chemin, filter);
    metaList.clear();

    while(path.hasNext()) {

        Metadata cache(path.next());
        metaList.append(cache);
    }

    if(!metaList.isEmpty()) {

        core->swapInterface(MetaDataInterface);
    }

    emit contentTypeChanged(Dir);
    contentType = Dir;

    metadatas->load(metaList);
}

void MetadataInterface::importerContent() {

    for(int i = 0;i<metaList.count();i++){
        core->getSqlControl()->inserer(metaList.value(i));
    }
}

void MetadataInterface::reset() {

    metaList.clear();
    metadatas->setContenttype(Entire);
    metaList = core->getSqlControl()->getMetaDatas();
    this->load(metaList);
    emit contentTypeChanged(Entire);
    contentType = Entire;
}

MetadataList* MetadataInterface::getListWidget() {

    return metadatas;
}


void MetadataInterface::changeDisposition(ContentType type) {

    switch(type) {

        case Dir: //modifications de cette interface si le contenu vient d'un dossier
            importer->show();

            break;

        case Entire: //si le contenu est toute la bibliotheque
            importer->hide();
            core->swapInterface(MetaDataInterface);
            break;

        case Playlist: //si le contenu vient d'une playlist
            importer->hide();
            core->swapInterface(MetaDataInterface);
            break;
        case Playbox:
            core->swapInterface(MetaDataInterface);
            break;
        case Empty: // si il n'y a pas de contenu
            importer->hide();
            break;
        }

    metadatas->setContenttype(type);
}

void MetadataInterface::refreshInterface(ContentType type) {

    emit this->contentTypeChanged(type);
    contentType = type;
    metadatas->setContenttype(type);

}

void MetadataInterface::navigateByKey(QKeyEvent *event) {

    switch(event->key()) {

        case Qt::Key_Return:
            core->playinginterface()->load(this->getListWidget()->getItems().value(indexSelected));
            core->playinginterface()->load(this->getListWidget()->getItems());
            core->swapInterface(PlayingInterface);
            break;

        case Qt::Key_Down:

            if(this->getListWidget()->item(indexSelected+1) != NULL) {

                this->indexSelected = this->getListWidget()->row(this->getListWidget()->currentItem());
                this->getListWidget()->item(indexSelected)->setSelected(false);
                this->indexSelected++;
                this->getListWidget()->setCurrentItem(this->getListWidget()->item(indexSelected));
                this->getListWidget()->currentItem()->setSelected(true);

            }
            break;

        case Qt::Key_Up:

            if(this->getListWidget()->item(indexSelected-1) != NULL) {

                this->indexSelected = this->getListWidget()->row(this->getListWidget()->currentItem());
                this->getListWidget()->currentItem()->setSelected(false);
                this->indexSelected--;
                this->getListWidget()->setCurrentItem(this->getListWidget()->item(indexSelected));
                this->getListWidget()->currentItem()->setSelected(true);

            }
            break;
        }
    }

void MetadataInterface::place(float coef) {

    this->setStyleSheet("min-width : 200px;");
}

QList<Metadata> MetadataInterface::totalContent() const {

    return metaList;
}

void MetadataInterface::reload() {

    if(contentType == Entire) {


        metaList = core->getSqlControl()->getMetaDatas();
        entireList = metaList;
    }

}
searchResultType MetadataInterface::dominantType(QList<Metadata> liste, const QString& word) const {
    int artists = 0;
    int albums = 0;
    int songs = 0;

    if(word.length() < 4 || core->dictionnary().contains(word, Qt::CaseInsensitive)) {
        return Song;
    }

    for(int i = 0;i<liste.count();i++) {

        if(liste.value(i).contains(word) == Song) {
            songs++;
        }
        else if(liste.value(i).contains(word) == Album) {
            albums++;
        }
        else if(liste.value(i).contains(word) == Artist) {
            artists++;
        }
    }

    if(songs <= artists && albums <= artists) {
        return Artist;

    } else if(songs <= albums) {
        return Album;

    } else {
        return Song;
    }
}

