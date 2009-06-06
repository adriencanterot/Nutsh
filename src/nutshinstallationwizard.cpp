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

    license = new QLabel(QString::fromUtf8("Bienvenue dans l'assistant d'installation de Nutsh! cet assistant va vous guider pour \n\nAjouter des morceaux\nApprendre bri�vement comment se servir de Nutsh!\n\nCliquez sur suivant pour continuer."), this);
    license->setWordWrap(true);
}

PageImportMedia::PageImportMedia() {

    principal = new QVBoxLayout(this);

    import = new QLabel(QString::fromUtf8("Pour bien fonctionner, vous devez indiquer �  Nutsh! o� se trouvent vos m�dias, choisissez le dossier contenant vos m�dias : "), this);
    import->setWordWrap(true);

    enCours = new QLabel;
    attention = new QLabel;
    progression = new QProgressBar;
    parcourir = new QPushButton("Parcourir...");

    principal->addWidget(import);
    principal->addWidget(attention);
    principal->addWidget(parcourir, Qt::AlignLeft);

    connect(parcourir, SIGNAL(clicked()), this, SLOT(getDirName()));

    this->setLayout(principal);
}

void PageImportMedia::getDirName() {

    dirName = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Dossier de vos m�dias"), "/");

    parcourir->hide();
    attention->hide();

    principal->addWidget(progression);
    principal->addWidget(enCours);

    enCours->show();
    progression->show();

    Indexer *scan = new Indexer(dirName);
    connect(scan, SIGNAL(updateBar(int, int)), this, SLOT(updateBar(int, int)));
    connect(scan, SIGNAL(fatalError(QString)), this, SLOT(resetAction(QString)));
    progression->setMaximum(0);
    scan->start();
}

void PageImportMedia::resetAction(QString message) {

    attention->setText("<span style = 'color:red;'><strong>"+message+"</strong></span>");
    attention->setWordWrap(true);
    parcourir->show();
    progression->hide();
    attention->show();
    enCours->hide();
}

void PageImportMedia::updateBar(int current, int total) {

    progression->setMaximum(total);
    progression->setValue(current);

    enCours->setText(QString("%1/%2").arg(current).arg(total));

    if(current >0 && total == current) {
        
        enCours->setText(QString::fromUtf8("Vos m�dias ont �t� import�s"));
    }


}

PageConclusion::PageConclusion() {

    conclusion = new QLabel(QString::fromUtf8("Tout vos morceaux ont �t� import�s dans votre biblioth�que\nAppuyez sur \"Done\" pour commencer �  vous servir de Nutsh!"), this);
}
