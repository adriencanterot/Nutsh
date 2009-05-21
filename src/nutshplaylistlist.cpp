
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

    if(this->itemAt(event->pos()) != NULL) {

        this->itemAt(event->pos())->setSelected(true);
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshPlaylistList::dropEvent(QDropEvent* event) {

    event->accept();

    core->getSqlControl()->inserer(core->metadatainterface()->getListWidget()->selectedMetadatas(), this->itemAt(event->pos())->text());
}

void NutshPlaylistList::showContent(const QModelIndex &index) {

    core->metadatainterface()->load(
            core->getSqlControl()->getMetaDatas("SELECT * FROM "+NutshSqlSaver::sqlStringFormat(index.data().toString()))
            );

    core->metadatainterface()->refreshInterface(Playlist);
}
