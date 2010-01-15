#include "nutshplaybox.h"
#include "nutshcomunicator.h"

NutshPlaybox::NutshPlaybox(NutshComunicator* corePath)
{
    core = corePath;
    this->setAcceptDrops(true);
    this->setProperty("playbox", true);
    compteur = 0;
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

}

void NutshPlaybox::showcontent() {
    this->isPlaybox(true);
    core->metadatainterface()->reset();
    core->metadatainterface()->load(fileattente);
    qDebug() << "showContent" << this->compteur << fileattente.count();


}
void NutshPlaybox::mouseReleaseEvent(QMouseEvent *event) {
    this->showcontent();
    event->accept();

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
