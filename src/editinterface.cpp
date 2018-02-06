#include "nutsheditinterface.h"
#include "nutshcomunicator.h"


NutshEditInterface::NutshEditInterface(NutshComunicator *corePath)
{
    core = corePath;

    this->setSource(QUrl("/Users/adrien/Nutsh/qml/editinterface.qml"));
    this->setAutoFillBackground(true);


}

void NutshEditInterface::place(float coef) {
    this->setFixedSize(440, 280);
    this->move(160, 72);

}

void NutshEditInterface::edit(NutshMetaData meta) {
    m_meta = meta;

    this->show();

}

void NutshEditInterface::finish() {

    this->hide();
    core->metadatainterface()->load(core->metadatainterface()->getListWidget()->getItems());
    core->metadatainterface()->getListWidget()->scrollToItem(core->metadatainterface()->getListWidget()->item(this->m_meta.getlocalid()));
}

void NutshEditInterface::edit() {

    this->edit(core->metadatainterface()->getListWidget()->getItem(core->metadatainterface()->getListWidget()->row(core->metadatainterface()->getListWidget()->currentItem()))); // get metadata to edit
}
