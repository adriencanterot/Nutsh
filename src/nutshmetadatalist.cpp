#include "nutshmetadatalist.h"

NutshMetaDataList::NutshMetaDataList() {

    this->setColumnCount(4);

    QStringList headerMetaData;
    headerMetaData << "Titre" << "Artiste" << "Album" << "Annee" << "chemin";

    this->setHeaderLabels(headerMetaData);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitSignal(QModelIndex)));
    this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);

}

void NutshMetaDataList::append(NutshMetaData data) {

    QStringList viewCacheItem;
    viewCacheItem << data.getTitre() << data.getArtiste() << data.getAlbum() << data.getDate() << data.getChemin();

    QTreeWidgetItem* cacheItem = new QTreeWidgetItem(viewCacheItem);
    this->addTopLevelItem(cacheItem);
    items.append(data);
}

void NutshMetaDataList::emitSignal(QModelIndex metaIndex) {

    emit clicked(items.value(metaIndex.row()));
}

QList<NutshMetaData> NutshMetaDataList::getItems() const {

    return items;
}

bool NutshMetaDataList::isEmpty() {

    if (items.isEmpty()) {

        return true;

    } else {

        return false;
    }
}

void NutshMetaDataList::load(QList<NutshMetaData> liste) {

    this->clearList();
    this->setColumnHidden(4, true);

    for(int i = 0;i<liste.count();i++) {

        this->append(liste.value(i));
    }

    if(liste.count() != 0) {

        this->topLevelItem(0)->setSelected(true);
    }
}
void NutshMetaDataList::clearList() {

    this->clear();
    items.clear();
}

NutshMetaData NutshMetaDataList::getItem(int index) const {

    return items.value(index);
}

QList<NutshMetaData> NutshMetaDataList::selectedMetadatas() const{

    QList<NutshMetaData> itemsToReturn;
    qDebug() << this->selectedItems().count();

    for(int i = 0;i<items.count();i++) {

        if(this->topLevelItem(i)->isSelected()) {

            itemsToReturn.append(items.value(i));
        }

    }

    return itemsToReturn;
}

void NutshMetaDataList::keyPressEvent(QKeyEvent* event) {

    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {

        event->accept();
        emit clicked(items.value(0));

    } else {

        event->ignore();
    }
}

