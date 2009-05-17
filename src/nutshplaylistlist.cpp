
#include "nutshplaylistlist.h"
#include "nutshcomunicator.h"

NutshPlaylistList::NutshPlaylistList(NutshComunicator* corePath, QWidget *parent) : QListWidget(parent) {

    this->setAcceptDrops(true);
    core = corePath;
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(showContent(QModelIndex)));

}

 void NutshPlaylistList::dragEnterEvent(QDragEnterEvent *event) {

     event->accept();
 }



void NutshPlaylistList::dragMoveEvent(QDragMoveEvent *event) {

    this->itemAt(event->pos())->setSelected(true);
    event->accept();
}

void NutshPlaylistList::dropEvent(QDropEvent* event) {

    event->accept();

    NutshSqlSaver::inserer(core->metadatainterface()->getListWidget()->selectedMetadatas(), this->itemAt(event->pos())->text());
    qDebug() << "Successfull!";
}

void NutshPlaylistList::showContent(QModelIndex index) {

    core->metadatainterface()->load(
            NutshSqlSaver::getMetaDatas("SELECT * FROM "+index.data().toString())
            );
    emit core->metadatainterface()->refreshInterface(Playlist);
}
