#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QProgressBar>
#include <QFileDialog>
#include "nutshinstallationwizard.h"
#include "nutshindexer.h"

NutshInstallationWizard::NutshInstallationWizard()
{
    qRegisterMetaType<ProgressionInfo>("ProgressionInfo");
    this->addPage(new PageIntro);
    this->addPage(new PageImportMedia);
    this->addPage(new PageConclusion);
    this->setButtonText(QWizard::NextButton, "Suivant");
    this->setButtonText(QWizard::BackButton, "Pr�c�dent");
    this->setButtonText(QWizard::FinishButton, "Terminer");
    this->setButtonText(QWizard::CancelButton, "Annuler");
#ifdef Q_WS_MAC
    this->setWizardStyle(ModernStyle);
#endif
}

void NutshInstallationWizard::accept() {

    QDialog::accept();
}

PageIntro::PageIntro() {

    license = new QLabel("Bienvenue dans l'assistant d'installation de Nutsh! cet assistant va vous guider pour : \n\n- Ajouter des morceaux\n- Apprendre bri�vement comment se servir de Nutsh!\n\nCliquez sur suivant pour continuer.", this);
    license->setWordWrap(true);
}

PageImportMedia::PageImportMedia() {

    principal = new QVBoxLayout(this);
    import = new QLabel("Pour bien fonctionner, vous devez indiquer �  Nutsh o� se trouvent vos m�dias, choisissez le dossier contenant vos m�dias : ", this);
    import->setWordWrap(true);

    enCours = new QLabel;
    attention = new QLabel;
    m_progression = new QProgressBar;
    parcourir = new QPushButton("Parcourir...");
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

    dirName = QFileDialog::getExistingDirectory(this, "Dossier de vos m�dias", "/");

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
    qDebug() << informations.phrase;

}

PageConclusion::PageConclusion() {

    conclusion = new QLabel("Tout vos morceaux ont �t� import�s dans votre biblioth�que\nAppuyez sur Terminer pour commencer �  vous servir de Nutsh", this);
}

void NutshInstallationWizard::reject() {
    qApp->quit();
}
