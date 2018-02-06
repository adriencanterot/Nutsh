#include "nutshplaylistlist.h"
#include "nutshcomunicator.h"

NutshPlaylistList::NutshPlaylistList(NutshComunicator* corePath, QWidget *parent) : QListWidget(parent) {

    this->setAcceptDrops(true);
    core = corePath;
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(showContent(QModelIndex)));
    this->setProperty("leftside", true);
    popup = new QMenu;
    popup->addAction(tr("Supprimer"), this, SLOT(remove()));
    popup->addAction(tr("Renommer"), this, SLOT(rename()));


}

 void NutshPlaylistList::dragEnterEvent(QDragEnterEvent *event) {
     //accepte l'évènement quand la souris entre dans la liste

     event->accept();
 }



void NutshPlaylistList::dragMoveEvent(QDragMoveEvent *event) {
    // séléctionne l'élément à la position du curseur


    if(this->itemAt(event->pos()) != NULL && this->row(this->itemAt(event->pos())) > 3) {

        this->itemAt(event->pos())->setSelected(true);
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshPlaylistList::dropEvent(QDropEvent* event) {
    //insère les metadonnées séléctionnées dans la liste à la position du curseur

    if(this->itemAt(event->pos()) != NULL && this->row(this->itemAt(event->pos())) > 3) {

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
    core->playbox()->isPlaybox(false);

    switch(index.row()) {
        case 0 :
        core->metadatainterface()->changeDisposition(Entire);
        core->metadatainterface()->reset();
        if(core->searchlineinterface()->value() != "") {
            core->metadatainterface()->getWordMetaData(core->searchlineinterface()->value());
        }
        break;
        case 1 :
        core->metadatainterface()->changeDisposition(Playlist);
        core->metadatainterface()->load(core->getSqlControl()->getMostReaden(30));

        break;
        case 2 :
        core->metadatainterface()->changeDisposition(Playlist);
        core->metadatainterface()->load(core->getSqlControl()->getLastImport(30));

        break;
        case 3 :
        core->metadatainterface()->changeDisposition(Playlist);
        core->metadatainterface()->load(core->getSqlControl()->getLastReaden(30));

        break;
        default:
        core->metadatainterface()->changeDisposition(Playlist);

        core->metadatainterface()->load(
            core->getSqlControl()->getMetaDatas(this->currentItem()->text())
        );

        break;
    }

}

void NutshPlaylistList::mouseReleaseEvent(QMouseEvent *event) {

    if(event->button() == Qt::RightButton) {
        if(this->row(this->itemAt(event->pos())) > 3) {
            popup->popup(QWidget::mapToGlobal(event->pos()));
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        if(this->itemAt(event->pos())) {
            emit clicked(QModelIndex(this->indexAt(event->pos())));
            event->accept();
        } else {
            event->ignore();        
        }
    }
}

void NutshPlaylistList::remove() {
    core->getSqlControl()->remove(this->currentItem()->text());
    core->playlistinterface()->refresh();
    this->setCurrentItem(this->item(0));
    core->metadatainterface()->reset();
}

void NutshPlaylistList::rename() {
    bool ok;
    QString nom = QInputDialog::getText(this, tr("Renommer "), tr("Nouveau nom"),
                                        QLineEdit::Normal, this->currentItem()->text(), &ok);
    if(ok == false) { return; }

    core->getSqlControl()->rename(nom, this->currentItem()->text());
    core->playlistinterface()->refresh();
}


