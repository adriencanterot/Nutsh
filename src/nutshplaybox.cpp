#include "nutshplaybox.h"
#include "nutshcomunicator.h"

NutshPlaybox::NutshPlaybox(NutshComunicator* corePath)
{
    core = corePath;
    m_numbers_elements = new QLabel(QString("<font color = '#DEDEDE'>0</font>"), this);
    m_numbers_elements->setProperty("playbox-count", true);
    m_numbers_elements->setStyleSheet("border :none;");
    m_numbers_elements->move(68, 3);
    this->setAcceptDrops(true);
    this->setProperty("playbox", true);
    compteur = 0;
    m_right_click = new QMenu;
    m_right_click->addAction("Nouvelle liste à partir de la playbox", core->playlistinterface(), SLOT(newListFromContent()));
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
    qDebug() << "Add" << this->compteur << fileattente.count();
    meta.setLocation(fromPlaybox);
    fileattente.append(meta);
    m_numbers_elements->setText(QString("<font color = '#DEDEDE'>%1</font>").arg(fileattente.count()));

}

void NutshPlaybox::showcontent() {
    this->isPlaybox(true);
    core->metadatainterface()->reset();
    core->metadatainterface()->load(fileattente);
    qDebug() << "showContent" << this->compteur << fileattente.count();


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
    qDebug() << "dropEvent" << this->compteur << fileattente.count();

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
    compteur++;
    qDebug() << "Playing" << this->compteur << fileattente.count();

}

NutshMetaData NutshPlaybox::next() {
    compteur++;
    for(int i = 0;i<fileattente.count();i++) {
        qDebug() << fileattente.value(i).getTitre();
    }
    qDebug() << "Titre" << fileattente.value(compteur-1).getTitre();
    qDebug() << "Next" << this->compteur << fileattente.count();

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
