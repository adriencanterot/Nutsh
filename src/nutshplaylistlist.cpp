#include "nutshplaylistlist.h"
#include "nutshcomunicator.h"

NutshPlaylistList::NutshPlaylistList(NutshComunicator* corePath, QWidget *parent) : QListWidget(parent) {

    this->setAcceptDrops(true);
    core = corePath;
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(showContent(QModelIndex)));

}

 void NutshPlaylistList::dragEnterEvent(QDragEnterEvent *event) {
     //accepte l'évènement quand la souris entre dans la liste

     event->accept();
 }



void NutshPlaylistList::dragMoveEvent(QDragMoveEvent *event) {
    // séléctionne l'élément à la position du curseur

    if(this->itemAt(event->pos()) != NULL) {

        this->itemAt(event->pos())->setSelected(true);
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshPlaylistList::dropEvent(QDropEvent* event) {
    //insère les metadonnées séléctionnées dans la liste à la position du curseur

    if(this->itemAt(event->pos()) != NULL) {

        core->getSqlControl()->inserer(
                core->metadatainterface()->getListWidget()->selectedMetadatas(),
                this->itemAt(event->pos())->text()
                );
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshPlaylistList::showContent(const QModelIndex &index) {
    // affiche le contenu d'une liste de lecture dans l'interface nutshmetadatainterface
    switch(index.row()) {
        case 0 :
        core->metadatainterface()->load(core->getSqlControl()->getMostReaden(30));
        break;
        case 1 :
        core->metadatainterface()->load(core->getSqlControl()->getLastImport(30));
        break;
        case 2 :
        core->metadatainterface()->load(core->getSqlControl()->getLastReaden(30));
        break;
        default:
        core->metadatainterface()->load(
            core->getSqlControl()->getMetaDatas(NutshSqlSaver::sqlStringFormat(index.data().toString()))
        );
        break;
    }

    core->metadatainterface()->refreshInterface(Playlist);
}
