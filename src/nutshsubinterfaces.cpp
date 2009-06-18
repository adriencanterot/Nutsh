#include "nutshsubinterfaces.h"

NutshBoutonRevenir::NutshBoutonRevenir(QWidget* parent) : QPushButton(parent) {

    interfaceName = MetaData;
    this->move(550, 80);
    connect(this, SIGNAL(clicked()), this, SLOT(emitClicked()));
    this->setProperty("boutonRevenir", true);
}

void NutshBoutonRevenir::emitClicked() {

    switch(interfaceName) {

        case MetaData :
            interfaceName = Playing;
            break;

        case Playing :
            interfaceName = MetaData;
            break;
        }

    emit clicked(interfaceName);
}
