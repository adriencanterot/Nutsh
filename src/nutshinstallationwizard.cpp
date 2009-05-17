#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QProgressBar>
#include <QFileDialog>
#include "nutshinstallationwizard.h"
#include "nutshindexer.h";

NutshInstallationWizard::NutshInstallationWizard()
{
    this->addPage(new PageIntro);
    this->addPage(new PageImportMedia);
    this->addPage(new PageConclusion);
}

void NutshInstallationWizard::accept() {

    QDialog::accept();
}

PageIntro::PageIntro() {

    license = new QLabel(QString::fromUtf8("Bienvenue dans l'assistant d'installation de Nutsh! cet assistant va vous guider pour \n\nAjouter des morceaux\nApprendre brièvement comment se servir de Nutsh!\n\nClickez sur suivant pour continuer."), this);
    license->setWordWrap(true);
}

PageImportMedia::PageImportMedia() {

    principal = new QVBoxLayout(this);

    import = new QLabel(QString::fromUtf8("Pour bien fonctionner, vous devez indiquer à Nutsh! où se trouvent vos médias, choisissez le dossier contenant vos médias : "), this);
    import->setWordWrap(true);

    enCours = new QLabel;
    progression = new QProgressBar;
    parcourir = new QPushButton("Parcourir...");

    principal->addWidget(import);
    principal->addWidget(parcourir, Qt::AlignLeft);

    connect(parcourir, SIGNAL(clicked()), this, SLOT(getDirName()));

    this->setLayout(principal);
}

void PageImportMedia::getDirName() {

    dirName = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Dossier de vos médias"), "/");

    parcourir->hide();
    principal->addWidget(progression);
    principal->addWidget(enCours);

    Indexer *scan = new Indexer(dirName, "bibliotheque");
    connect(scan, SIGNAL(updateBar(int, int)), this, SLOT(updateBar(int, int)));
    scan->start();
}

void PageImportMedia::updateBar(int current, int total) {

    progression->setMaximum(total);
    progression->setValue(current);

    enCours->setText(QString("%1/%2").arg(current).arg(total));

    if(current >0 && total == current) {
        
        enCours->setText(QString::fromUtf8("Vos médias ont étés importés"));
    }


}

PageConclusion::PageConclusion() {

    conclusion = new QLabel(QString::fromUtf8("Tout vos morceaux ont été importé dans votre bibliothèque\nAppuyez sur \"Done\" pour commencer à vous servir de Nutsh!"), this);
}
