#ifndef NUTSHPLAYBOX_H
#define NUTSHPLAYBOX_H

#include <QWidget>

class NutshComunicator;
class NutshPlaybox : public QWidget
{
public:
    NutshPlaybox(NutshComunicator*);
    void place(float);
private:
    NutshComunicator* core;
};

#endif // NUTSHPLAYBOX_H
