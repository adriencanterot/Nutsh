#include "nutshprogressinterface.h"
#include "nutshcomunicator.h"

ImporterThread::ImporterThread(const QList<NutshMetaData> &aImporter, const QString &tableName, NutshComunicator* corePath) {

    core = corePath;
    metaList = aImporter;
    loopRunning = false;
    m_tableName = tableName;
}

void ImporterThread::run() {

    loopRunning = true;

    for(int i = 0;i<this->metaList.count();i++) {

        core->getSqlControl()->inserer(metaList.value(i), m_tableName);
        emit updateBar(i+1, metaList.count());

        if(loopRunning == false) {

            break;
        }
    }

    connect(this, SIGNAL(finished()), this, SLOT(quit()));

    this->exec();
}

void ImporterThread::forceQuit() {

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

    if(m_progress->value() != 0) {

        active = true;

    } else {

        active = false;

    }

    return active;
}

void NutshProgressInterface::setValue(int i) {

    m_progress->setValue(i);

    if(m_progress->maximum() != 0 && m_progress->value() == m_progress->maximum()) {
        core->driveinterface()->swapToDrives();
    }

}

void NutshProgressInterface::setMaximum(int i) {

    m_progress->setMaximum(i);
}

void NutshProgressInterface::swapToProgress() {

    core->driveinterface()->hide();
    core->gauche()->addWidget(this);

    this->show();
    active = true;
}
void NutshProgressInterface::stopAction(QObject* receiver, const char* method) {

    m_receiver = receiver;
    m_member = method;

    connect(m_cancel, SIGNAL(clicked()), receiver, method);
}

void NutshProgressInterface::setCancelButtonText(const QString& text) {

    m_cancel->setText(text);
}

void NutshProgressInterface::updateWidget(int current, int total) {

    this->setValue(current);
    this->setMaximum(total);

    this->setBottomLabelText(QString("%1/%2").arg(current).arg(total));


}

void NutshProgressInterface::import(const QList<NutshMetaData> &metaList, const QString &table) {

    disconnect(m_cancel, SIGNAL(clicked()), m_receiver, m_member); //annuler l'effet de stopAction

    this->swapToProgress();
    this->setTopLabelText("Importation...");

    /*creation du Thread*/
    scan = new ImporterThread(metaList, table, core);

    connect(scan, SIGNAL(updateBar(int,int)), this, SLOT(updateWidget(int,int)));
    connect(m_cancel, SIGNAL(clicked()), scan, SLOT(forceQuit()));
    connect(m_cancel, SIGNAL(clicked()), core->driveinterface(), SLOT(swapToDrives()));

    scan->start();

}



