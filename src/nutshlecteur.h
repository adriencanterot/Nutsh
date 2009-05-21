#ifndef NUTSHLECTEUR_H
#define NUTSHLECTEUR_H
#include <QMessageBox>
#include <QtDebug>
#include <QSlider>
#include "nutshmetadata.h"
#include <QTimer>
#include "preprocess.h"

#ifdef Q_WS_MAC
#include <phonon>
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
    void setSource(const NutshMetaData&);
    void setSources(const QList<NutshMetaData>&);
    Phonon::SeekSlider *getPosSlider();

private :
    Phonon::AudioOutput *sortieAudio;
    Phonon::AudioOutput *sortieVideo;
    Phonon::SeekSlider *avancement;
};
#endif
#ifdef Q_WS_WIN
#include <fmod.h>
enum State{
    Playing, Paused, Stopped
        };


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
    void setSource(const NutshMetaData&);
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
    void aboutToFinish();
    void finished();


private :
    FSOUND_STREAM *m_media;
    int m_channel;
    QString m_source;
    QTimer* time;
    QSlider *avancement;
    int m_updateFrequency;
    State m_state;

};
#endif
#endif // NUTSHLECTEUR_H
