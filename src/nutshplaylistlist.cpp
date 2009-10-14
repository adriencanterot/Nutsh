#include "nutshplaylistlist.h"
#include "nutshcomunicator.h"

NutshPlaylistList::NutshPlaylistList(NutshComunicator* corePath, QWidget *parent) : QListWidget(parent) {

    this->setAcceptDrops(true);
    core = corePath;
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(showContent(QModelIndex)));
    popup = new QMenu;
    popup->addAction("Supprimer", this, SLOT(remove()));
    popup->addAction("Renommer", this, SLOT(rename()));


}

 void NutshPlaylistList::dragEnterEvent(QDragEnterEvent *event) {
     //accepte l'�v�nement quand la souris entre dans la liste

     event->accept();
 }



void NutshPlaylistList::dragMoveEvent(QDragMoveEvent *event) {
    // s�l�ctionne l'�l�ment � la position du curseur


    if(this->itemAt(event->pos()) != NULL && this->row(this->itemAt(event->pos())) > 3) {

        this->itemAt(event->pos())->setSelected(true);
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshPlaylistList::dropEvent(QDropEvent* event) {
    //ins�re les metadonn�es s�l�ctionn�es dans la liste � la position du curseur

    if(this->itemAt(event->pos()) != NULL && this->row(this->itemAt(event->pos())) > 3) {

        core->getSqlControl()->inserer(
                core->metadatainterface()->getListWidget()->selectedMetadatas(),
                this->itemAt(event->pos())->text()
                );
        event->accept();

    } else {
        qDebug() << this->row(this->itemAt(event->pos()));
        event->ignore();
    }
}

void NutshPlaylistList::showContent(const QModelIndex &index) {
    // affiche le contenu d'une liste de lecture dans l'interface nutshmetadatainterface
    switch(index.row()) {
        case 0 :
        core->metadatainterface()->reset();
        break;
        case 1 :
        core->metadatainterface()->load(core->getSqlControl()->getMostReaden(30));
        break;
        case 2 :
        core->metadatainterface()->load(core->getSqlControl()->getLastImport(30));
        break;
        case 3 :
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

void NutshPlaylistList::mouseReleaseEvent(QMouseEvent *event) {

    if(event->button() == Qt::RightButton) {
        if(this->row(this->itemAt(event->pos())) > 3) {
            popup->popup(QWidget::mapToGlobal(event->pos()));
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        emit clicked(QModelIndex(this->indexAt(event->pos())));
        event->accept();
    }
}

void NutshPlaylistList::remove() {
    core->getSqlControl()->remove(this->currentItem()->text());
    core->playlistinterface()->refresh();
}

void NutshPlaylistList::rename() {
    bool ok;
    QString nom = QInputDialog::getText(this, "Renommer ", "Nouveau nom",
                                        QLineEdit::Normal, this->currentItem()->text(), &ok);
    if(ok == false) { return; }

    core->getSqlControl()->rename(nom, this->currentItem()->text());
    core->playlistinterface()->refresh();
}

