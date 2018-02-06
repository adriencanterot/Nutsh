#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QProgressBar>
#include <QFileDialog>
#include "installationwizard.h"
#include "indexer.h"

InstallationWizard::InstallationWizard()
{
    qRegisterMetaType<ProgressionInfo>("ProgressionInfo");
    this->addPage(new PageIntro);
    this->addPage(new PageImportMedia);
    this->addPage(new PageConclusion);
    this->setButtonText(QWizard::NextButton, tr("Suivant"));
    this->setButtonText(QWizard::BackButton, tr("Précédent"));
    this->setButtonText(QWizard::FinishButton, tr("Terminer"));
    this->setButtonText(QWizard::CancelButton, tr("Annuler"));
#ifdef Q_WS_MAC
    this->setWizardStyle(ModernStyle);
#endif
}

void InstallationWizard::accept() {

    QDialog::accept();
}

PageIntro::PageIntro() {

    license = new QLabel(tr("Bienvenue dans l'assistant d'installation de Nutsh! cet assistant va vous guider pour : \n\n- Ajouter des morceaux\n- Apprendre brièvement comment se servir de Nutsh!\n\nCliquez sur suivant pour continuer."), this);
    license->setWordWrap(true);
}

PageImportMedia::PageImportMedia() {

    principal = new QVBoxLayout(this);
    import = new QLabel(tr("Pour bien fonctionner, vous devez indiquer à  Nutsh où se trouvent vos médias, choisissez le dossier contenant vos médias : "), this);
    import->setWordWrap(true);

    enCours = new QLabel;
    attention = new QLabel;
    m_progression = new QProgressBar;
    parcourir = new QPushButton(tr("Parcourir..."));
    parcourir->resize(100, parcourir->height());

    principal->addWidget(import);
    principal->addWidget(attention);
    principal->addWidget(parcourir, Qt::AlignLeft);
    parcourir->setFixedWidth(100);

    connect(parcourir, SIGNAL(clicked()), this, SLOT(getDirName()));

    this->setLayout(principal);
    registerField("parcourir", parcourir);

}

void PageImportMedia::getDirName() {

    dirName = QFileDialog::getExistingDirectory(this, tr("Dossier de vos médias"), "/");

    parcourir->hide();
    attention->hide();

    principal->addWidget(m_progression);
    principal->addWidget(enCours);

    enCours->show();
    m_progression->show();

    Indexer *scan = new Indexer(dirName);
    connect(scan, SIGNAL(updateBar(ProgressionInfo)), this, SLOT(updateBar(ProgressionInfo)));
    connect(scan, SIGNAL(fatalError(QString)), this, SLOT(resetAction(QString)));
    m_progression->setMaximum(0);
    scan->start();
    complete = true;
}

void PageImportMedia::resetAction(QString message) {

    attention->setText("<span style = 'color:red;'><strong>"+message+"</strong></span>");
    attention->setWordWrap(true);
    parcourir->show();
    m_progression->hide();
    attention->show();
    enCours->hide();
}

void PageImportMedia::updateBar(ProgressionInfo informations) {

    if(informations.style == searching) {
        m_progression->setValue(informations.progression);
        m_progression->setMaximum(0);

    } else if( informations.style == progression) {
        m_progression->setValue(informations.progression);
        m_progression->setMaximum(informations.maximum);

    }
    enCours->setText(informations.phrase);

}

PageConclusion::PageConclusion() {

    conclusion = new QLabel(tr("Tout vos morceaux ont été importés dans votre bibliothèque\nAppuyez sur Terminer pour commencer à  vous servir de Nutsh"), this);
}

void InstallationWizard::reject() {
    qApp->quit();
}
