#ifndef DAILYSONGINTERFACE_H
#define DAILYSONGINTERFACE_H

#include <QWidget>
class Core;

class DailySongInterface : public QWidget
{
public:
    DailySongInterface(Core*);

private:
    Core* core;
};

#endif // DAILYSONGINTERFACE_H
