#include "nutshplaybox.h"
#include "nutshcomunicator.h"

NutshPlaybox::NutshPlaybox(NutshComunicator* corePath)
{
    core = corePath;
    this->setText("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Vide&nbsp;</font>");
    this->setAcceptDrops(true);
    this->setProperty("playbox", true);
    o = 0;
    m_right_click = new QMenu;
    m_right_click->addAction(tr("Nouvelle liste à partir de la playbox"), core->playlistinterface(), SLOT(newListFromContent()));
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

    if(fileattente.contains(meta)) {

        fileattente.removeOne(meta); // supression du morceau si il existe deja, pour eviter les confusions
    }

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

        if(fileattente.contains(meta)) {

            fileattente.removeOne(meta);
        }
        meta.setLocation(fromPlaybox);
        fileattente.append(meta);
        o = fileattente.lastIndexOf(core->playinginterface()->current());
        this->setText(QString("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    %1</font>").arg(fileattente.count()));

    } else if (meta.location() == fromPlaybox) {

        o = fileattente.lastIndexOf(core->playinginterface()->current());

    }

}

NutshMetaData NutshPlaybox::next() {

    if(o == fileattente.count()-1) {

        return NutshMetaData();
    }
    o = fileattente.lastIndexOf(core->playinginterface()->current())+1;
    return fileattente.value(o); // base de 0 donc équivalent à o +1
}


NutshMetaData NutshPlaybox::previous() {

    if(o == 0) {

        return NutshMetaData();
    }

    o = fileattente.lastIndexOf(core->playinginterface()->current())-1;
    return fileattente.value(o); // base de 0 donc équivalent à o -1
}

NutshMetaData NutshPlaybox::random() {
    return fileattente.value((qrand() % (fileattente.count() - 1 +1) + 0));
}

bool NutshPlaybox::isEmpty() {

    return false;
}

QList<NutshMetaData> NutshPlaybox::getFileattente() const {
    return fileattente;
}
