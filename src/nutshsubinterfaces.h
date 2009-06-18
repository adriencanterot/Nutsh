#ifndef NUTSHSUBINTERFACES_H
#define NUTSHSUBINTERFACES_H

#include "preprocess.h"

#include <QPushButton>
#include <QVariant>

class NutshBoutonRevenir : public QPushButton {

    Q_OBJECT
public:

    NutshBoutonRevenir(QWidget *parent = 0);

public slots:
    void emitClicked();

signals:
    void clicked(InterfaceName);

private:

    InterfaceName interfaceName;
};

#endif // NUTSHSUBINTERFACES_H
