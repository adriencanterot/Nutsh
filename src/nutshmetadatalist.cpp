#include "nutshmetadatalist.h"

NutshMetaDataList::NutshMetaDataList() {
    this->setColumnCount(4);
    QStringList headerMetaData;
    headerMetaData << "Titre" << "Artiste" << "Album" << "Annee" << "chemin";
    this->setHeaderLabels(headerMetaData);
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitSignal(QModelIndex)));

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
QList<NutshMetaData> NutshMetaDataList::getItems() {
    return items;
}
bool NutshMetaDataList::isEmpty() {
    if (items.isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}
void NutshMetaDataList::load(QList<NutshMetaData> liste) {
    this->clearList();
    this->setColumnHidden(4, true);

    for(int i = 0;i<liste.count();i++) {
        this->append(liste.value(i));
    }
}
void NutshMetaDataList::clearList() {
    this->clear();
    items.clear();
}
