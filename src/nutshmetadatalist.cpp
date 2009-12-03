#include "nutshmetadatalist.h"
#include "nutshcomunicator.h"

NutshMetaDataList::NutshMetaDataList(NutshComunicator* corePath) {

    core = corePath;
    property = true;
    this->setProperty("leftside", false);
    this->setAlternatingRowColors(true);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitSignal(QModelIndex)));
    this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);
    this->setIconSize(QSize(30,30));
    this->resize(440, 253);

}

void NutshMetaDataList::append(NutshMetaData data) {


    /******Redimmensionnement des titres ******/
    QString titre = data.getTitre();
    if(titre.size() > CHAR_NUM_LIST) { titre.resize(CHAR_NUM_LIST);titre.append("..."); }
    QString artistealbum = data.getArtiste() + " | " + data.getAlbum();
    if(artistealbum.size() > CHAR_NUM_LIST) { artistealbum.resize(CHAR_NUM_LIST);artistealbum.append("..."); }

    QString sdata = QString("%1 \n %3")
                    .arg(titre)
                    .arg(artistealbum);
    QListWidgetItem* item = new QListWidgetItem(QIcon(":img/images/sans-image.png"), sdata);
    /***************-----------------********/
    if(this->count() < 5) {
        item->setIcon(data.getArtwork());

    } else {
        this->setIconSize(QSize(30,30));
    }
    QFont font;
    font.setBold(true);
    item->setFont(font);
    this->addItem(item);
    items.append(data);
}

void NutshMetaDataList::emitSignal(QModelIndex metaIndex) {

    emit clicked(items.value(metaIndex.row()));
}

QList<NutshMetaData> NutshMetaDataList::getItems() const {

    return items;
}

bool NutshMetaDataList::isEmpty() {

    return items.empty(); // empty?
}

void NutshMetaDataList::load(QList<NutshMetaData> liste) {

    this->indexSelected = 0;
    this->clearList();

    for(int i = 0;i<liste.count();i++) {
        qDebug() << i;
        this->append(liste.value(i));
    }

    if(liste.count() != 0) {

        this->item(0)->setSelected(true);
        this->setCurrentItem(this->item(0));
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

    for(int i = 0;i<items.count();i++) {

        if(this->item(i)->isSelected()) {

            itemsToReturn.append(items.value(i));
        }

    }

    return itemsToReturn;
}

void NutshMetaDataList::keyPressEvent(QKeyEvent* event) {

    core->metadatainterface()->navigateByKey(event);

}

