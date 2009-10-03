#include "nutshprogressinterface.h"
#include "nutshcomunicator.h"

NutshProgressInterface::NutshProgressInterface(NutshComunicator* corePath)
{
    qDebug() << "Initializing NutshProgressInterface...";
    core = corePath;
    //Widgets


    m_progress = new QProgressBar(this);
    qRegisterMetaType<ProgressionInfo>("ProgressionInfo");
    m_cancel = new QPushButton("", this);
    m_label = new QLabel("                                                                                  ", this);
    m_cancel->setProperty("cancelButton", true);
    m_cancel->setToolTip("Arrêter l'importation");

}


bool NutshProgressInterface::isActive() {
    //est actif si il y a une importation en cours

    if(m_progress->value() != 0) {

        active = true;

    } else {

        active = false;

    }

    return active;
}

void NutshProgressInterface::setValue(int i) {

    m_progress->setValue(i);

    if(m_progress->maximum() != 0 && m_progress->value() == m_progress->maximum()) { // si l'importation est finie, affichage de l'interface nutshdriveinterface

        this->finished();
    }

}

void NutshProgressInterface::setMaximum(int i) {

    m_progress->setMaximum(i);
}

void NutshProgressInterface::swapToProgress() {
    //affiche cette interface au lieu de nutshdriveinterface

    this->show();
    active = true;
}

void NutshProgressInterface::updateWidget(ProgressionInfo informations) {
    // met à jour le widget (à chaque tour de boucle du thread

    if(informations.style == searching) {
        this->setValue(informations.progression);
        this->setMaximum(0);

    } else if( informations.style == progression) {
        this->setValue(informations.progression);
        this->setMaximum(informations.maximum);

    }
    this->setText(informations.phrase);

}

void NutshProgressInterface::import(const QString& path) {

    scan = new Indexer(path);
    connect(scan, SIGNAL(loopEnded()), core->metadatainterface(), SLOT(reload()));
    connect(scan, SIGNAL(updateBar(ProgressionInfo)), this, SLOT(updateWidget(ProgressionInfo)));
    connect(scan, SIGNAL(fatalError(QString)), this, SLOT(stopWhy(QString)));
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    scan->start();

    this->show();
}

void NutshProgressInterface::finished() {

        if(scan != NULL) {

            scan->forceQuit();
        }
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(reset()));
}

void NutshProgressInterface::stopWhy(const QString &why) {

    scan->forceQuit();
    QMessageBox::critical(core->initInterfaces(), "Erreur", why);
    this->reset();
}

void NutshProgressInterface::reset() {

    m_progress->setValue(0);
    this->hide();
}

void NutshProgressInterface::cancel() {
    if(scan != NULL) {
        scan->forceQuit();
    }
    this->reset();
}

void NutshProgressInterface::place(float coef) {

    m_cancel->move(360, 3);
    m_label->move(0, 20);
}

void NutshProgressInterface::setText(const QString& text) {
    m_label->setText(text);
}
