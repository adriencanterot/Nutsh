#ifndef NUTSHLECTEUR_H
#define NUTSHLECTEUR_H
#include <QMessageBox>
#include <QtDebug>
#include <QSlider>
#include "metadata.h"
#include <QTimer>
#include "preprocess.h"

#ifdef PHONON
#include <Phonon>

/* Cree un lecteur heritant du media object (pour lui rajouter des options) */
class Player : public Phonon::MediaObject
{
public:
    Player();
    //void setSourceMusique(Phonon::MediaSource source);
    //void setSourceVideo(Phonon::MediaSource source, Phonon::VideoWidget *widget);
    /*void jouerMusiqueOuVideo(Phonon::MediaSource adresse, Phonon::VideoWidget *widget);*/
    bool isMusique(Metadata&);
    bool isVideo(Metadata&);
    bool isPlaying();
    bool isPaused();
    void setSource(const Metadata&);
    void setSources(const QList<Metadata>&);
    Phonon::SeekSlider *getPosSlider();
    Phonon::VolumeSlider *getVolumeSlider();

private :
    Phonon::AudioOutput *sortieAudio;
    Phonon::AudioOutput *sortieVideo;
    Phonon::SeekSlider *avancement;
    Phonon::VolumeSlider *volume;
};
#endif
#ifdef FMOD
#include <fmod.h>
class Player : public QObject
{
    Q_OBJECT
public:
    Player();
    //void setSourceMusique(Phonon::MediaSource source);
    //void setSourceVideo(Phonon::MediaSource source, Phonon::VideoWidget *widget);
    /*void jouerMusiqueOuVideo(Phonon::MediaSource adresse, Phonon::VideoWidget *widget);*/
    bool isPlaying();
    bool isPaused();
    void setSource(const Metadata&);
    QSlider *getPosSlider();
    QSlider *getVolumeSlider();

public slots:
    void play();
    void pause();
    void stop();

private slots:
    void setPos(int);
    void updateSlider();
    void setVolume(int);

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
    QSlider *volume;
    int m_updateFrequency;
    State m_state;

};
#endif
#ifdef FMODeX
#include <fmod.hpp>
class Player : public QObject {
    Q_OBJECT
public:
    Player();
    void setSource(const Metadata&);
    bool isPlaying();
    bool isPaused();
    QSlider *getPosSlider();
    QSlider *getVolumeSlider();

public slots:
    void play();
    void pause();
    void stop();

private slots:
    void setPos(int);
    void updateSlider();
    void setVolume(int);

signals:
    qint64 tick(qint64);
    void aboutToFinish();
    void finished();
private:
    FMOD::System* system;
    FMOD::Channel* channel;
    FMOD::Sound* sound;
    FMOD_RESULT result;
    QSlider* m_avancement;
    QSlider* m_volume;
    int m_updatefrequence;
    QTimer *timer;
    State m_state;
};
#endif
#endif // NUTSHLECTEUR_H
