#include "editinterface.h"
#include "core.h"


EditInterface::EditInterface(Core *corePath)
{
    core = corePath;

    this->setSource(QUrl("/Users/adrien/Nutsh/qml/editinterface.qml"));
    this->setAutoFillBackground(true);


}

void EditInterface::place(float coef) {
    this->setFixedSize(440, 280);
    this->move(160, 72);

}

void EditInterface::edit(Metadata meta) {
    m_meta = meta;

    this->show();

}

void EditInterface::finish() {

    this->hide();
    core->metadatainterface()->load(core->metadatainterface()->getListWidget()->getItems());
    core->metadatainterface()->getListWidget()->scrollToItem(core->metadatainterface()->getListWidget()->item(this->m_meta.getlocalid()));
}

void EditInterface::edit() {

    this->edit(core->metadatainterface()->getListWidget()->getItem(core->metadatainterface()->getListWidget()->row(core->metadatainterface()->getListWidget()->currentItem()))); // get metadata to edit
}
