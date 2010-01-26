#include "nutshplaybox.h"
#include "nutshcomunicator.h"

NutshPlaybox::NutshPlaybox(NutshComunicator* corePath)
{
    core = corePath;
    this->setText("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Vide&nbsp;</font>");
    this->setAcceptDrops(true);
    this->setProperty("playbox", true);
    compteur = 0;
    m_right_click = new QMenu;
    m_right_click->addAction(tr("Nouvelle liste à partir de la playbox"), core->playlistinterface(), SLOT(newListFromContent()));
    m_right_click->addAction(tr("Ajouter à la playlist..."));
}
void NutshPlaybox::place(float coef) {
    this->resize(160, 35);
    this->move(0, 240);
}
void NutshPlaybox::add(QList<NutshMetaData> liste) {

    for(int i = 0;i<liste.count();i++) {
        this->add(liste.value(i));
    }
}
void NutshPlaybox::add(NutshMetaData meta) {
    meta.setLocation(fromPlaybox);
    fileattente.append(meta);
    this->setText(QString("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    %1</font>").arg(fileattente.count()));

}

void NutshPlaybox::showcontent() {
    this->isPlaybox(true);
    core->metadatainterface()->refreshInterface(Playbox);
    core->metadatainterface()->load(fileattente);


}
void NutshPlaybox::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        this->showcontent();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        m_right_click->popup(QWidget::mapToGlobal(event->pos()));
        event->accept();
    }


}
void NutshPlaybox::dropEvent(QDropEvent *event) {


    this->add(core->metadatainterface()->getListWidget()->selectedMetadatas());
    this->setStyleSheet("background-color : white; border : 1px solid black");
    event->accept();
}
void NutshPlaybox::dragEnterEvent(QDragEnterEvent *event) {
    this->setStyleSheet("background-color : #93CB8E; border : 1px solid green");
    event->accept();
}
void NutshPlaybox::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
}
void NutshPlaybox::dragLeaveEvent(QDragLeaveEvent *event) {
    this->setStyleSheet("background-color : white; border : 1px solid black");
    event->accept();

}
void NutshPlaybox::isPlaybox(bool yon) {
    if(yon) {
        this->setStyleSheet("background-color : #6BB7E5; border : 1px solid blue");


    } else {
        this->setStyleSheet("background-color : white; border : 1px solid black");

    }
}
void NutshPlaybox::playing(NutshMetaData &meta) {

    if(meta.location() == fromPlaylist) {
        meta.setLocation(fromPlaybox);
        fileattente.insert(compteur+1, meta);
        compteur = fileattente.lastIndexOf(meta);
        this->setText(QString("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    %1</font>").arg(fileattente.count()));
    } else if (meta.location() == fromPlaybox) {
        compteur = fileattente.indexOf(meta);
    }

}

NutshMetaData NutshPlaybox::next() {
    compteur++;
    return fileattente.value(compteur);
}


NutshMetaData NutshPlaybox::previous() {
    compteur--;
    return fileattente.value(compteur);
}

bool NutshPlaybox::isEmpty() {
    if(compteur == fileattente.count()) {
        return true;
    } else {
        return false;
    }
}

QList<NutshMetaData> NutshPlaybox::getFileattente() const {
    return fileattente;
}
