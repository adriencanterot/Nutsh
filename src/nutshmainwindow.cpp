#include "nutshmainwindow.h"


NutshMainWindow::NutshMainWindow(QWidget *parent)
    : QMainWindow(parent) {

    //création du core
    path = new NutshComunicator;

    //this->setupMenus();
    this->setCentralWidget(path->initInterfaces()); // affichage du widget Central
    this->setStatusBar(path->bar());
    this->setFixedSize(600, 350);

    setUnifiedTitleAndToolBarOnMac(true);

    this->setWindowTitle("Nutsh!");
    path->searchlineinterface()->activate();
    this->show();
    path->scanFolders();
    this->show();
    path->metadatainterface()->setStyleSheet("min-width : 440px;");
    qDebug("NutshMainWindow : Fin de l'initialisation de l'interface");
}

/*void NutshMainWindow::setupMenus() {

    //FICHIER
    ouvrir = new QAction("Ouvrir", this);
    importer = new QAction("Importer", this);
    derniersmorceaux = new QAction("5 derniers morceaux dans une liste de lecture", this);
    resultats = new QAction("Résultats de la recherche dans une liste de lecture", this);
    editermorceaux = new QAction("Modifier les tags", this);
    explorateur = new QAction("Afficher dans l'explorateur", this);

    //EDITER
    copier = new QAction("Copier", this);
    coller = new QAction("Coller", this);
    toutselectionner = new QAction("Tout sélectionner", this);
    supprimer = new QAction("Supprimer", this);

    //CONTROLES
    lire = new QAction("Lire", this);
    pause = new QAction("Mettre en pause", this);
    arreter = new QAction("Arrêter", this);
    suivant = new QAction("Suivant", this);
    precedent = new QAction("Précédent", this);
    repeat = new QAction("Répéter", this);
    repeat->setCheckable(true);
    random = new QAction("Lecture aléatoire", this);
    random->setCheckable(true);

    fichier = this->menuBar()->addMenu("Fichier");
    fichier->addAction(ouvrir);
    fichier->addAction(importer);
    fichier->addSeparator();
    fichier->addAction(derniersmorceaux);
    fichier->addAction(resultats);
    fichier->addSeparator();
    fichier->addAction(editermorceaux);
    fichier->addAction(explorateur);

    edition = this->menuBar()->addMenu("Édition");
    edition->addAction(copier);
    edition->addAction(coller);
    edition->addSeparator();
    edition->addAction(toutselectionner);
    edition->addAction(supprimer);

    controles = this->menuBar()->addMenu("Contrôles");
    controles->addAction(lire);
    controles->addAction(pause);
    controles->addAction(arreter);
    controles->addSeparator();
    controles->addAction(suivant);
    controles->addAction(precedent);
    controles->addSeparator();
    controles->addAction(repeat);
    controles->addAction(random);

}*/
