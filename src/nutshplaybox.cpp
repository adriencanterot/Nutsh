#include "nutshplaybox.h"
#include "nutshcomunicator.h"

NutshPlaybox::NutshPlaybox(NutshComunicator* corePath)
{
    core = corePath;
    this->setProperty("playbox", true);
}
void NutshPlaybox::place(float coef) {
    this->resize(160, 35);
    this->move(0, 240);
}
