#include "nutshprogressinterface.h"
#include "nutshcomunicator.h"

NutshProgressInterface::NutshProgressInterface(NutshComunicator* corePath)
{
    core = corePath;
    //Widgets


    m_progress = new QProgressBar(this);
    m_progress->move(0, 0);

    m_right = new QLabel(this);
    m_left = new QLabel(this);
    m_top = new QLabel(this);
    m_bottom = new QLabel(this);

    m_cancel = new QPushButton("", this);
    m_cancel->setProperty("cancelButton", true);
    m_cancel->setToolTip("Arr�ter l'importation");
    m_cancel->move(360, 3);

}

/* ------- Texte des labels Haut/Bas/Gauche/Droite ---------*/


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

void NutshProgressInterface::updateWidget(int current, int total) {
    // met � jour le widget (� chaque tour de boucle du thread

    if(total == 0 && current != 0) {

        this->setMaximum(0);
        this->setValue(current);

    } else if(total == 0 && current == 0) {
        this->setValue(0);

    } else {

        this->setMaximum(total);
        this->setValue(current);
    }



}

void NutshProgressInterface::import(const QString& path) {

    scan = new Indexer(path);
    connect(scan, SIGNAL(updateBar(int, int)), this, SLOT(updateWidget(int, int)));
    connect(scan, SIGNAL(fatalError(QString)), this, SLOT(stopWhy(QString)));
    connect(m_cancel, SIGNAL(clicked()), scan, SLOT(forceQuit()));
    scan->start();
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
}

