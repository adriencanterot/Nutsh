#ifndef NUTSHLECTEUR_H
#define NUTSHLECTEUR_H
#include <phonon>
#include <QMessageBox>
#include <QtDebug>
#include "nutshmetadata.h"

/* Cree un lecteur heritant du media object (pour lui rajouter des options) */
class NutshLecteur : public Phonon::MediaObject
{
public:
    NutshLecteur();
    //void setSourceMusique(Phonon::MediaSource source);
    //void setSourceVideo(Phonon::MediaSource source, Phonon::VideoWidget *widget);
    /*void jouerMusiqueOuVideo(Phonon::MediaSource adresse, Phonon::VideoWidget *widget);*/
    bool isMusique(NutshMetaData&);
    bool isVideo(NutshMetaData&);
    bool isPlaying();
    bool isPaused();
    void setSource(NutshMetaData&);
    void setSources(QList<NutshMetaData>);

private :
    Phonon::AudioOutput *sortieAudio;
    Phonon::AudioOutput *sortieVideo;
};

#endif // NUTSHLECTEUR_H
