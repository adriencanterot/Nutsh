#include "playbox.h"
#include "core.h"

Playbox::Playbox(Core* corePath)
{
    core = corePath;
    this->setText("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Vide&nbsp;</font>");
    this->setAcceptDrops(true);
    this->setProperty("playbox", true);
    o = 0;
    m_right_click = new QMenu;
    m_right_click->addAction(tr("Nouvelle liste à partir de la playbox"), core->playlistinterface(), SLOT(newListFromContent()));
}
void Playbox::place(float coef) {
    this->resize(160, 35);
    this->move(0, 240);
}
void Playbox::add(QList<Metadata> liste) {

    for(int i = 0;i<liste.count();i++) {
        this->add(liste.value(i));
    }
}
void Playbox::add(Metadata meta) {

    if(fileattente.contains(meta)) {

        fileattente.removeOne(meta); // supression du morceau si il existe deja, pour eviter les confusions
    }

    meta.setLocation(fromPlaybox);
    fileattente.append(meta);
    this->setText(QString("<font color = '#DEDEDE'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    %1</font>").arg(fileattente.count()));

}
void Playbox::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        this->showcontent();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        m_right_click->popup(QWidget::mapToGlobal(event->pos()));
        event->accept();
    }


}
void Playbox::showcontent() {
    this->isPlaybox(true);
    core->metadatainterface()->refreshInterface(ContentType::Playbox);
    core->metadatainterface()->load(fileattente);


}

void Playbox::dropEvent(QDropEvent *event) {


    this->add(core->metadatainterface()->getListWidget()->selectedMetadatas());
    this->setStyleSheet("background-color : white; border : 1px solid black");
    event->accept();
}
void Playbox::dragEnterEvent(QDragEnterEvent *event) {
    this->setStyleSheet("background-color : #93CB8E; border : 1px solid green");
    event->accept();
}
void Playbox::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
}
void Playbox::dragLeaveEvent(QDragLeaveEvent *event) {
    this->setStyleSheet("background-color : white; border : 1px solid black");
    event->accept();

}
void Playbox::isPlaybox(bool yon) {
    if(yon) {
        this->setStyleSheet("background-color : #6BB7E5; border : 1px solid blue");


    } else {
        this->setStyleSheet("background-color : white; border : 1px solid black");

    }
}
void Playbox::playing(Metadata &meta) {

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

Metadata Playbox::next() {

    if(o == fileattente.count()-1) {

        return Metadata();
    }
    o = fileattente.lastIndexOf(core->playinginterface()->current())+1;
    return fileattente.value(o); // base de 0 donc équivalent à o +1
}


Metadata Playbox::previous() {

    if(o == 0) {

        return Metadata();
    }

    o = fileattente.lastIndexOf(core->playinginterface()->current())-1;
    return fileattente.value(o); // base de 0 donc équivalent à o -1
}

Metadata Playbox::random() {
    return fileattente.value((qrand() % (fileattente.count() - 1 +1) + 0));
}

bool Playbox::isEmpty() {

    return false;
}

QList<Metadata> Playbox::getFileattente() const {
    return fileattente;
}
