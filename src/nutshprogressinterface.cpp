#include "nutshprogressinterface.h"
#include "nutshcomunicator.h"

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
        qDebug() << m_progress->value() << m_progress->maximum();
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

    connect(m_cancel, SIGNAL(clicked()), receiver, method);
}

void NutshProgressInterface::setCancelButtonText(const QString& text) {

    m_cancel->setText(text);
}


