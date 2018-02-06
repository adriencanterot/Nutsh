#ifndef NUTSHINSTALLATIONWIZARD_H
#define NUTSHINSTALLATIONWIZARD_H

#include <QWizard>
#include "preprocess.h"
class QLabel;
class QPushButton;
class QProgressBar;
class QFileDialog;
class QVBoxLayout;

class PageIntro : public QWizardPage
{
    public:
        PageIntro();

    private:
        QLabel* license;
};

class PageImportMedia : public QWizardPage
{

    Q_OBJECT

    public:
        PageImportMedia();
    public slots:
        void getDirName();
        void updateBar(ProgressionInfo informations);
        void resetAction(QString);

    private:
        QLabel *import,
               *enCours,
               *attention;

        QPushButton* parcourir;
        QVBoxLayout *principal;
        QProgressBar *m_progression;
        QString dirName;
        bool complete;
};

class PageConclusion : public QWizardPage
{

    public:
        PageConclusion();

    public:
        QLabel *conclusion;
};

class InstallationWizard : public QWizard
{
public:
    InstallationWizard();
    void accept();
    void reject();
};

#endif // NUTSHINSTALLATIONWIZARD_H
