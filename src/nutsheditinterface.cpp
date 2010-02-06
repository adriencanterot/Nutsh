#include "nutsheditinterface.h"
#include "nutshcomunicator.h"

NutshEditInterface::NutshEditInterface(NutshComunicator *corePath)
{
    core = corePath;
    this->setProperty("editinterface", true);
    m_artiste = new QLabel(tr("Artiste : "), this);
    m_album = new QLabel(tr("Album : "), this);
    m_titre = new QLabel(tr("Titre : "), this);

    m_editartiste = new QLineEdit(this);
    m_editalbum = new QLineEdit(this);
    m_edittitre = new QLineEdit(this);

    m_confirm = new QPushButton("Modifier", this);
    m_cancel = new QPushButton("Annuler",this);
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(hide()));
    connect(m_confirm, SIGNAL(clicked()), this, SLOT(finish()));

}

void NutshEditInterface::place(float coef) {
    this->setFixedSize(440, 280);
    this->move(170, 80);
    m_artiste->move(0, 50);
    m_album->move(0, 100);

    m_editalbum->move(70, 100);
    m_edittitre->move(70, 0);
    m_editartiste->move(70, 50);

    m_confirm->move(200, 150);
    m_cancel->move(280, 150);
}

void NutshEditInterface::edit(NutshMetaData meta) {
    m_meta = meta;
    m_editartiste->setText(meta.getArtiste());
    m_editalbum->setText(meta.getAlbum());
    m_edittitre->setText(m_meta.getTitre());
    this->show();

}

void NutshEditInterface::finish() {
    m_meta.setArtiste(m_editartiste->text());
    m_meta.setAlbum(m_editalbum->text());
    m_meta.setTitre(m_edittitre->text());
    this->hide();
    core->metadatainterface()->load(core->metadatainterface()->getListWidget()->getItems());
    core->metadatainterface()->getListWidget()->scrollToItem(core->metadatainterface()->getListWidget()->item(this->m_meta.getlocalid()));
}
