#include "nutshplaybox.h"
#include "nutshcomunicator.h"

NutshPlaybox::NutshPlaybox(NutshComunicator* corePath)
{
    core = corePath;
    this->setProperty("playbox", true);
}
void NutshPlaybox::place(float coef) {
    this->resize(160, 35);
    this->move(0, 240);
}
void NutshPlaybox::add(const QList<NutshMetaData>& liste) {

    for(int i = 0;i<liste.count();i++) {
        fileattente.append(liste.value(i));
    }
}
void NutshPlaybox::showcontent() {
    core->metadatainterface()->load(fileattente);
}
void NutshPlaybox::mouseReleaseEvent(QMouseEvent *event) {
    this->showcontent();
    event->accept();

}
void NutshPlaybox::dropEvent(QDropEvent *event) {
    this->add(core->metadatainterface()->getListWidget()->selectedMetadatas());
    qDebug() << "dropped";
    event->accept();
}
void NutshPlaybox::dragEnterEvent(QDragEnterEvent *event) {
    this->setStyleSheet("background-color : #93CB8E; border : 1px solid green");
    qDebug() << "entered";
    event->accept();
}
void NutshPlaybox::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
}

