#include "nutshprogressinterface.h"
#include "nutshcomunicator.h"

ImporterThread::ImporterThread(const QList<NutshMetaData> &aImporter, const QString &tableName, NutshComunicator* corePath) {

    core = corePath;
    metaList = aImporter;
    loopRunning = false;
    m_tableName = tableName;
}

void ImporterThread::run() {
    //execute le thread

    loopRunning = true;

    for(int i = 0;i<this->metaList.count();i++) { // insère les métadonnées de la liste

        core->getSqlControl()->inserer(metaList.value(i), m_tableName);
        emit updateBar(i+1, metaList.count());

        if(loopRunning == false) { // si une action forceQuit() est demandée, stopper la boucle

            break;
        }
    }

    connect(this, SIGNAL(finished()), this, SLOT(quit()));

    this->exec();
}

void ImporterThread::forceQuit() {
    //arrête la boucle

    loopRunning = false;
    this->quit();
    this->terminate();
}

NutshProgressInterface::NutshProgressInterface(NutshComunicator* corePath)
{
    core = corePath;
    //Widgets

    this->setFixedWidth(core->driveinterface()->width());

    m_progress = new QProgressBar(this);
    m_right = new QLabel(this);
    m_left = new QLabel(this);
    m_top = new QLabel(this);
    m_bottom = new QLabel(this);

    m_cancel = new QPushButton("Arreter");

    //Layouts
    m_principal = new QVBoxLayout(this);
    m_progressLayout = new QHBoxLayout(this);
    m_infosLayout = new QHBoxLayout(this);


    //positionnement
    m_progressLayout->addWidget(m_left);
    m_progressLayout->addWidget(m_progress);
    m_progressLayout->addWidget(m_right);

    m_infosLayout->addWidget(m_bottom);
    m_infosLayout->addWidget(m_cancel);

    m_principal->addWidget(m_top);
    m_principal->addLayout(m_progressLayout);
    m_principal->addLayout(m_infosLayout);

    this->setLayout(m_principal);

    core->searchlineinterface()->setFocus();

}

/* ------- Texte des labels Haut/Bas/Gauche/Droite ---------*/

void NutshProgressInterface::setTopLabelText(const QString &text) {

    m_top->setText(text);
}

void NutshProgressInterface::setBottomLabelText(const QString &text) {

    m_bottom->setText(text);
}

void NutshProgressInterface::setRightLabelText(const QString &text) {

    m_right->setText(text);
}

void NutshProgressInterface::setLeftLabelText(const QString &text) {

    m_left->setText(text);
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

        qDebug() << m_progress->value() << m_progress->maximum();

        this->finished();
    }

}

void NutshProgressInterface::setMaximum(int i) {

    m_progress->setMaximum(i);
}

void NutshProgressInterface::swapToProgress() {
    //affiche cette interface au lieu de nutshdriveinterface

    core->driveinterface()->hide();

    this->show();
    active = true;
}
void NutshProgressInterface::stopAction(QObject* receiver, const char* method) {
    //met l'action pour arrêter la progression

    m_receiver = receiver;
    m_member = method;

    connect(m_cancel, SIGNAL(clicked()), this, SLOT(finished()));
}

void NutshProgressInterface::setCancelButtonText(const QString& text) {
    //texte du bouton Cancel

    m_cancel->setText(text);
}

void NutshProgressInterface::updateWidget(int current, int total) {
    // met à jour le widget (à chaque tour de boucle du thread

    this->setValue(current);
    this->setMaximum(total);

    this->setBottomLabelText(QString("%1/%2").arg(current).arg(total));


}

void NutshProgressInterface::import(const QList<NutshMetaData> &metaList, const QString &table) {
    //importe le contenu d'une liste de métadonnée avec progression affichée

    disconnect(m_cancel, SIGNAL(clicked()), m_receiver, m_member); //annuler l'effet de stopAction
    this->swapToProgress();
    this->setTopLabelText("Importation...");

    /*creation du Thread*/
    scan = new ImporterThread(metaList, table, core);

    m_receiver = scan;
    m_member = SLOT(forceQuit());

    connect(scan, SIGNAL(updateBar(int,int)), this, SLOT(updateWidget(int,int)));
    connect(m_cancel, SIGNAL(clicked()), m_receiver, m_member);
    connect(m_cancel, SIGNAL(clicked()), core->driveinterface(), SLOT(swapToDrives()));

    scan->start();

}

void NutshProgressInterface::finished() {

        if(scan != NULL) {

            scan->forceQuit();
        }


        this->setTopLabelText(QString("%1 morceaux importés").arg(m_progress->value()));
        this->completeBar();
        disconnect(m_cancel, SIGNAL(clicked()), m_receiver, m_member);
        connect(m_cancel, SIGNAL(clicked()), core->driveinterface(), SLOT(swapToDrives()));
        m_cancel->setText("Terminé");
}

void NutshProgressInterface::reset() {

    this->setTopLabelText("");
    this->setBottomLabelText("");

    this->setRightLabelText("");
    this->setLeftLabelText("");

    this->m_cancel->setText("Arrêter");
}

void NutshProgressInterface::completeBar() {

}
