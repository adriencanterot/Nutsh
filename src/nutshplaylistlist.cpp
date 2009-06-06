
#include "nutshplaylistlist.h"
#include "nutshcomunicator.h"

NutshPlaylistList::NutshPlaylistList(NutshComunicator* corePath, QWidget *parent) : QListWidget(parent) {

    this->setAcceptDrops(true);
    core = corePath;
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(showContent(QModelIndex)));

}

 void NutshPlaylistList::dragEnterEvent(QDragEnterEvent *event) {
     //accepte l'�v�nement quand la souris entre dans la liste

     event->accept();
 }



void NutshPlaylistList::dragMoveEvent(QDragMoveEvent *event) {
    // s�l�ctionne l'�l�ment � la position du curseur

    if(this->itemAt(event->pos()) != NULL) {

        this->itemAt(event->pos())->setSelected(true);
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshPlaylistList::dropEvent(QDropEvent* event) {
    //ins�re les metadonn�es s�l�ctionn�es dans la liste � la position du curseur

    event->accept();

    core->getSqlControl()->inserer(core->metadatainterface()->getListWidget()->selectedMetadatas(), this->itemAt(event->pos())->text());
}

void NutshPlaylistList::showContent(const QModelIndex &index) {
    // affiche le contenu d'une liste de lecture dans l'interface nutshmetadatainterface

    core->metadatainterface()->load(
            core->getSqlControl()->getMetaDatas(NutshSqlSaver::sqlStringFormat(index.data().toString()))
            );

    core->metadatainterface()->refreshInterface(Playlist);
}
