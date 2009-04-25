#ifndef NUTSHLECTEUR_H
#define NUTSHLECTEUR_H
#include <phonon>
#include <QMessageBox>
#include <QtDebug>
#include "nutshmetadata.h"

#ifdef Q_WS_MAC
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
    Phonon::SeekSlider *getPos();

private :
    Phonon::AudioOutput *sortieAudio;
    Phonon::AudioOutput *sortieVideo;
    Phonon::SeekSlider *avancement;
};
#endif
#ifdef Q_WS_WIN
#include <fmod.h>
class NutshLecteur : public QObject
{
    Q_OBJECT
public:
    NutshLecteur();
    //void setSourceMusique(Phonon::MediaSource source);
    //void setSourceVideo(Phonon::MediaSource source, Phonon::VideoWidget *widget);
    /*void jouerMusiqueOuVideo(Phonon::MediaSource adresse, Phonon::VideoWidget *widget);*/
    bool isPlaying();
    bool isPaused();
    void setSource(NutshMetaData&);
    QSlider *getPosSlider();

public slots:
    void play();
    void pause();
    void stop();

private slots:
    void setPos(int);
    void updateSlider();

signals:
    qint64 tick(qint64);


private :
    FSOUND_STREAM *m_media;
    int m_channel;
    bool m_state;
    QString m_source;
    QTimer* time;
    QSlider *avancement;
    int m_updateFrequency;

};
#endif
#endif // NUTSHLECTEUR_H
