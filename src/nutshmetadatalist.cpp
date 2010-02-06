#include "nutshmetadatalist.h"
#include "nutshcomunicator.h"

NutshMetaDataList::NutshMetaDataList(NutshComunicator* corePath) {

    core = corePath;
    property = true;
    this->setProperty("leftside", false);
    this->setAlternatingRowColors(true);
    contenttype = Entire;

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitSignal(QModelIndex)));
    connect(this->verticalScrollBar(), SIGNAL(sliderMoved(int)), this, SLOT(loadNext(int)));
    this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);
    this->setIconSize(QSize(34,34));
    this->resize(440, 253);
    context = new QMenu(this);

    eventpos = QPoint();

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
        this->setIconSize(QSize(34,34));
    }
    QFont font;
    font.setBold(true);
    item->setFont(font);
    this->addItem(item);



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
    this->wheelPosition = 0;
    for(int i = 0;i<liste.count();i++) {
        items.append(liste.value(i));
        items.last().setLocalid(i);
    }

    for(int i = 0;i<liste.count();i++) {

        liste.value(i).setLocalid(i);

        this->append(liste.value(i));
        if(this->count() >= MAX_ELEMENT_SHOWN) {
            break;
        }
    }

    if(liste.count() != 0) {

        this->item(0)->setSelected(true);
        this->setCurrentItem(this->item(0));
    }

    context->clear();
    if(this->contenttype == Entire) {
        context->addAction(tr("Supprimer"), this, SLOT(destroy()));
    } else if(this->contenttype == Playlist) {
        context->addAction(tr("Supprimer de la liste"), this, SLOT(destroyFromList()));
    }

}
void NutshMetaDataList::clearList() {

    this->clear();
    items.clear();
    this->setIconSize(QSize(34, 34));
}

NutshMetaData NutshMetaDataList::getItem(int index) const {

    return items.value(index);
}

QList<NutshMetaData> NutshMetaDataList::selectedMetadatas() const{

    QList<NutshMetaData> itemsToReturn;

    for(int i = 0;i<this->count();i++) {

        if(this->item(i)->isSelected()) {

            itemsToReturn.append(items.value(i));
        }

    }

    return itemsToReturn;
}

void NutshMetaDataList::keyPressEvent(QKeyEvent* event) {

    core->metadatainterface()->navigateByKey(event);

}
void NutshMetaDataList::loadNext(int value) {

    if(value >= this->verticalScrollBar()->maximum()) {

        this->append(this->items.mid(this->count(), MAX_ELEMENT_SHOWN));
    }
}
void NutshMetaDataList::append(QList<NutshMetaData> liste ) {

    for(int i = 0;i<liste.count();i++) {

        liste.value(i).setLocalid(i);
        this->append(liste.value(i));

    }

}
void NutshMetaDataList::wheelEvent(QWheelEvent *event) {

    if(core->interface() != MetaDataInterface) {
        return;
    }

    if(event->orientation() == Qt::Vertical) {
        if(event->delta() < 0) {
            if(this->wheelPosition < this->verticalScrollBar()->maximum()) this->wheelPosition += (this->count()/50)+1; else this->loadNext(this->verticalScrollBar()->maximum());

        } else {
            if(this->wheelPosition > this->verticalScrollBar()->minimum()) this->wheelPosition -= (this->count()/50)+1;
        }
            this->verticalScrollBar()->setValue((this->wheelPosition));
    }

}

void NutshMetaDataList::mouseReleaseEvent(QMouseEvent *event) {

    eventpos = event->pos();
    if(event->button() == Qt::RightButton) {
        context->popup(QWidget::mapToGlobal(event->pos()));
    }
}

void NutshMetaDataList::destroy() {
    core->getSqlControl()->destroy(items.value(this->row(this->itemAt(eventpos))));
    this->takeItem(this->row(this->itemAt(eventpos)));
    items.removeOne(items.value(this->row(this->itemAt(eventpos))));
}

void NutshMetaDataList::destroyFromList() {
    core->getSqlControl()->destroyFromList(items.value(this->row(this->itemAt(eventpos))), core->playlistinterface()->current());
    this->takeItem(this->row(this->itemAt(eventpos)));
    items.removeOne(items.value(this->row(this->itemAt(eventpos))));
}

void NutshMetaDataList::setContenttype(ContentType type) {
    this->contenttype = type;
}
