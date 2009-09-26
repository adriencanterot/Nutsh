#ifndef DAILYSONGINTERFACE_H
#define DAILYSONGINTERFACE_H

#include <QWidget>
class NutshComunicator;

class DailySongInterface : public QWidget
{
public:
    DailySongInterface(NutshComunicator*);

private:
    NutshComunicator* core;
};

#endif // DAILYSONGINTERFACE_H
