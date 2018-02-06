#ifndef NUTSHPLAYINGINTERFACE_H
#define NUTSHPLAYINGINTERFACE_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include "metadata.h"
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QDrag>
#include <QXmlStreamReader>
#include <QHttp>
#include <QBuffer>
#include "label.h"
#include "player.h"

class Core;
class Label;
class NutshEditLabel;
class PlayingInterface : public QWidget
{
    Q_OBJECT
public:
    PlayingInterface(Core*);
    void sigandslots();
    bool load(Metadata);
    void load(QList<Metadata>);
    void setStatus();
    QWidget* getActionsButtons();
    void pauseByKey(QKeyEvent*);
    QList<Metadata> getLastRead() const;
    Metadata current();
    void place(float coef);
    bool isPlaying();

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
    Core* core;

    QPushButton *boutonPlayPause,
                *boutonStop,
                *boutonPrecedent,
                *boutonSuivant,
                *boutonRepeat,
                *boutonRandom;

    class NutshEditLabel *artiste,
           *album,
           *titre;

    class Label *tempsLabel,
           *tempsLabelCP,
           *artisteCP,
           *titreCP,
           *artwork;

    QWidget *actionsButtons;

    QList<Metadata> playlist;
    QList<Metadata> lastRead;
    
    int currentId;
    bool tickCompteur;
    Metadata currentMeta;
    Player *media;

    QBuffer to;

    Action nextAction;
};

#endif // NUTSHPLAYINGINTERFACE_H
