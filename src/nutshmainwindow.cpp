#include "nutshmainwindow.h"


NutshMainWindow::NutshMainWindow(QWidget *parent)
    : QMainWindow(parent) {

    //création du core
    path = new NutshComunicator;

    this->setCentralWidget(path->initInterfaces()); // affichage du widget Central
    this->setStatusBar(path->bar());
    this->setFixedSize(650, 300);

    setUnifiedTitleAndToolBarOnMac(true);

    this->setWindowTitle("Nutsh!");
    path->searchlineinterface()->activate();
    this->show();

    path->afterLaunch();

    qDebug("NutshMainWindow : Fin de l'initialisation de l'interface");
}
