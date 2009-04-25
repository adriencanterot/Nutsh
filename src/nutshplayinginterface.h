#ifndef NUTSHPLAYINGINTERFACE_H
#define NUTSHPLAYINGINTERFACE_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include "nutshmetadata.h"
#include <phonon>
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
    void swapToPlay();
    void setStatus();
public slots:
    void next();
    void previous();
    void playPause();
    void tick(qint64 time);
    void stop();
private:
    NutshComunicator* core;
    QPushButton *boutonPlayPause, *boutonStop, *boutonPrecedent, *boutonSuivant;
    QLabel *artiste, *album, *titre, *tempsLabel, *tempsLabelCP, *artisteCP, *titreCP;
    QSplitter *central;
    QHBoxLayout *commandButtons, *infoLabels, *titreLabel, *controls;
    QVBoxLayout *principal, *positionnerDroite;
    QWidget *droite, *gauche;
    QList<NutshMetaData> playlist;
    int currentItem;
    NutshMetaData current;
    NutshLecteur *media;
    Phonon::SeekSlider *avancement;
};

#endif // NUTSHPLAYINGINTERFACE_H
