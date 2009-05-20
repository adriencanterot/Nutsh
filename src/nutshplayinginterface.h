#ifndef NUTSHPLAYINGINTERFACE_H
#define NUTSHPLAYINGINTERFACE_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include "nutshmetadata.h"
#include <QMouseEvent>
#include <QDrag>

#include "nutshlecteur.h"

class NutshComunicator;
class NutshPlayingInterface : public QWidget
{
    Q_OBJECT
public:
    NutshPlayingInterface(NutshComunicator*);
    void sigandslots();
    void load(NutshMetaData);
    void load(QList<NutshMetaData>);
    void setStatus();
    void pauseByKey(QKeyEvent*);
    QList<NutshMetaData> getLastRead();

public slots:
    void next();
    void previous();
    void playPause();
    void tick(qint64 time);
    void stop();
    void swapToPlay();


private:
    NutshComunicator* core;

    QPushButton *boutonPlayPause,
                *boutonStop,
                *boutonPrecedent,
                *boutonSuivant,
                *boutonRevenir;

    QLabel *artiste,
           *album,
           *titre,
           *tempsLabel,
           *tempsLabelCP,
           *artisteCP,
           *titreCP;

    QSplitter *central;

    QHBoxLayout *commandButtons,
                *infoLabels,
                *titreLabel,
                *controls;

    QVBoxLayout *principal,
                *positionnerDroite;

    QWidget *droite,
            *gauche;

    QList<NutshMetaData> playlist;
    QList<NutshMetaData> lastRead;
    
    int currentItem;
    NutshMetaData current;
    NutshLecteur *media;
};

#endif // NUTSHPLAYINGINTERFACE_H
