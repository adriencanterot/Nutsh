#include "subinterfaces.h"

NutshBoutonRevenir::NutshBoutonRevenir(QWidget* parent) : QPushButton(parent) {

    interfaceName = MetaDataInterface;
    connect(this, SIGNAL(clicked()), this, SLOT(emitClicked()));
    this->setToolTip(tr("Changer d'affichage"));
    this->setProperty("boutonRevenir", true);
}

void NutshBoutonRevenir::emitClicked() {

    emit clicked(interfaceName);
}

void NutshBoutonRevenir::setAction(InterfaceName newName) {

    this->interfaceName = newName;
}

void NutshBoutonRevenir::place(float coef) {

    this->move(550, 20);
}
