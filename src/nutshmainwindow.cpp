#include "nutshmainwindow.h"

NutshMainWindow::NutshMainWindow(QWidget *parent)
    : QMainWindow(parent) {

    path = new NutshComunicator;

    this->setCentralWidget(path->initInterfaces());
    this->setStatusBar(path->bar());
    this->setFixedSize(650, 300);

    setUnifiedTitleAndToolBarOnMac(true);

    this->setWindowTitle("Nutsh!");
    path->searchlineinterface()->activate();
    this->show();

    NutshInstallationWizard wizard;
    wizard.exec();



    qDebug("NutshMainWindow : Fin de l'initialisation de l'interface");
}
