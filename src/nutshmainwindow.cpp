#include "nutshmainwindow.h"


NutshMainWindow::NutshMainWindow(QWidget *parent)
    : QMainWindow(parent) {

    //cr�ation du core
    path = new NutshComunicator;

    this->setCentralWidget(path->initInterfaces()); // affichage du widget Central
    this->setStatusBar(path->bar());
    this->resize(600, 350);

    setUnifiedTitleAndToolBarOnMac(true);

    this->setWindowTitle("Nutsh!");
    path->searchlineinterface()->activate();
    this->show();

    qDebug("NutshMainWindow : Fin de l'initialisation de l'interface");
}
