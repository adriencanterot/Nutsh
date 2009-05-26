#ifndef NUTSHINSTALLATIONWIZARD_H
#define NUTSHINSTALLATIONWIZARD_H

#include <QWizard>
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
        void updateBar(int, int);
        void resetAction(QString);

    private:
        QLabel *import,
               *enCours,
               *attention;

        QPushButton* parcourir;
        QVBoxLayout *principal;
        QProgressBar *progression;
        QString dirName;
};

class PageConclusion : public QWizardPage
{

    public:
        PageConclusion();

    public:
        QLabel *conclusion;
};

class NutshInstallationWizard : public QWizard
{

public:
    NutshInstallationWizard();
    void accept();
};

#endif // NUTSHINSTALLATIONWIZARD_H
