#ifndef NUTSHPLAYINGINTERFACE_H
#define NUTSHPLAYINGINTERFACE_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include "nutshmetadata.h"
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QDrag>
#include <QXmlStreamReader>
#include <QHttp>
#include <QBuffer>
#include "nutshlabel.h"
#include "nutshlecteur.h"

class NutshComunicator;
class NutshPlayingInterface : public QWidget
{
    Q_OBJECT
public:
    NutshPlayingInterface(NutshComunicator*);
    void sigandslots();
    void load(const NutshMetaData&);
    void load(const QList<NutshMetaData>&);
    void setStatus();
    QWidget* getActionsButtons();
    void pauseByKey(QKeyEvent*);
    QList<NutshMetaData> getLastRead() const;
    void place(float coef);

public slots:
    void next();
    void whatsNext();
    void previous();
    void playPause();
    void tick(qint64 time);
    void stop();
    void random();
    void repeat();
    void daily();


private:
    NutshComunicator* core;

    QPushButton *boutonPlayPause,
                *boutonStop,
                *boutonPrecedent,
                *boutonSuivant,
                *boutonRepeat,
                *boutonRandom;

    NutshEditLabel *artiste,
           *album,
           *titre;

    NutshLabel *tempsLabel,
           *tempsLabelCP,
           *artisteCP,
           *titreCP,
           *artwork;

    QWidget *actionsButtons;

    QList<NutshMetaData> playlist;
    QList<NutshMetaData> lastRead;
    
    int currentItem;
    bool tickCompteur;
    NutshMetaData current;
    NutshLecteur *media;

    QBuffer to;

    Action nextAction;
};

#endif // NUTSHPLAYINGINTERFACE_H
