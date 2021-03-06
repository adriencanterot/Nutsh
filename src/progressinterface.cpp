#include "progressinterface.h"
#include "core.h"

ProgressInterface::ProgressInterface(Core* corePath)
{
    qDebug() << "Initializing ProgressInterface...";
    core = corePath;
    //Widgets


    m_progress = new QProgressBar(this);
    qRegisterMetaType<ProgressionInfo>("ProgressionInfo");
    m_cancel = new QPushButton("", this);
    m_label = new QLabel("                                                                                                                                    ", this);
    m_cancel->setProperty("cancelButton", true);
    m_cancel->setToolTip(tr("Arr�ter l'importation"));

}


bool ProgressInterface::isActive() {
    //est actif si il y a une importation en cours

    if(m_progress->value() != 0) {

        active = true;

    } else {

        active = false;

    }

    return active;
}

void ProgressInterface::setValue(int i) {

    m_progress->setValue(i);

    if(m_progress->maximum() != 0 && m_progress->value() == m_progress->maximum()) { // si l'importation est finie, affichage de l'interface nutshdriveinterface

        this->finished();
    }

}

void ProgressInterface::setMaximum(int i) {

    m_progress->setMaximum(i);
}

void ProgressInterface::visible(bool visible) {
    //affiche cette interface au lieu de nutshdriveinterface

    if(visible) {
        this->show();
        core->metadatainterface()->getListWidget()->resize(core->metadatainterface()->getListWidget()->width(), 210);
        active = true;
    } else {
        core->metadatainterface()->getListWidget()->resize(core->metadatainterface()->getListWidget()->width(), 260);
        this->hide();
    }
}

void ProgressInterface::updateWidget(ProgressionInfo informations) {
    // met � jour le widget (� chaque tour de boucle du thread

    if(informations.style == searching) {
        this->setValue(informations.progression);
        this->setMaximum(0);

    } else if( informations.style == progression) {
        this->setValue(informations.progression);
        this->setMaximum(informations.maximum);

    }
    this->setText(informations.phrase);

}

void ProgressInterface::import(const QString& path) {

    scan = new Indexer(path);
    connect(scan, SIGNAL(loopEnded()), core->metadatainterface(), SLOT(reload()));
    connect(scan, SIGNAL(updateBar(ProgressionInfo)), this, SLOT(updateWidget(ProgressionInfo)));
    connect(scan, SIGNAL(fatalError(QString)), this, SLOT(stopWhy(QString)));
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    scan->start();

    this->visible(true);
}

void ProgressInterface::finished() {

        if(scan != NULL) {

            scan->forceQuit();
        }
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(reset()));
}

void ProgressInterface::stopWhy(const QString &why) {

    scan->forceQuit();
    QMessageBox::critical(core->initInterfaces(), tr("Erreur"), why);
    this->reset();
}

void ProgressInterface::reset() {

    m_progress->setValue(0);
    this->visible(false);
}

void ProgressInterface::cancel() {
    if(scan != NULL) {
        scan->forceQuit();
    }
    this->reset();
}

void ProgressInterface::place(float coef) {

    m_cancel->move(360, 3);
    m_label->move(0, 20);
}

void ProgressInterface::setText(const QString& text) {
    m_label->setText(text);
}
