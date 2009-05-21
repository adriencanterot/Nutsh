#include "nutshlecteur.h"
#ifdef Q_WS_MAC

NutshLecteur::NutshLecteur() {

    sortieAudio = new Phonon::AudioOutput(Phonon::MusicCategory);
    sortieVideo = new Phonon::AudioOutput(Phonon::VideoCategory);

    Phonon::createPath(this, sortieAudio);
    avancement = new Phonon::SeekSlider(this);
}
/*    //Jouer une musique directement
    this->setCurrentSource(source);
    this->play();
}
void NutshLecteur::setSourceVideo(Phonon::MediaSource source, Phonon::VideoWidget *widget) {
    //Joue une video directement (le widgetVideo doit etre initialise)
    this->stop();
    this->setCurrentSource(source);
    Phonon::createPath(this, sortieVideo);
    Phonon::createPath(this, widget);
    this->play();
}
void NutshLecteur::jouerMusiqueOuVideo(Phonon::MediaSource adresse, Phonon::VideoWidget *widget) {
    //Determine de quel type est le fichier, et le joue
    if(this->isMusique(Phonon::MediaSource(adresse)))
        this->setSourceMusique(Phonon::MediaSource(adresse));
    else if(this->isVideo(Phonon::MediaSource(adresse)))
        this->setSourceVideo(Phonon::MediaSource(adresse), widget);
    else
	qDebug() << "Impossible de definir le type de fichier";
}*/

bool NutshLecteur::isMusique(NutshMetaData& data) {

    //return false si la mediasource est une video
    Phonon::MediaObject music0video;
    music0video.setCurrentSource(Phonon::MediaSource(data.getChemin()));

    if(!music0video.hasVideo())

        return true;

    else

        return false;
}

bool NutshLecteur::isVideo(NutshMetaData& data) {

    //return false si la mediasource est une video
    Phonon::MediaObject music0video;
    music0video.setCurrentSource(Phonon::MediaSource(data.getChemin()));

    if(music0video.hasVideo())

        return true;

    else

        return false;
}

bool NutshLecteur::isPlaying() {

    if(this->state() == Phonon::PlayingState) {

        return true;

    } else {

        return false;
    }
}

void NutshLecteur::setSource(const NutshMetaData& source) {

    this->setCurrentSource(Phonon::MediaSource(source.getChemin()));
}

void NutshLecteur::setSources(const QList<NutshMetaData> &sources) {

    for(int i = 0;i<sources.count();i++) {

        this->enqueue(Phonon::MediaSource(sources.value(i).getChemin()));
    }
}

bool NutshLecteur::isPaused() {

    if(this->state() == Phonon::PausedState) {

        return true;

    } else {

        return false;
    }
}

Phonon::SeekSlider* NutshLecteur::getPosSlider() {

    return avancement;
}

#endif
#ifdef Q_WS_WIN

#include "nutshlecteur.h"

NutshLecteur::NutshLecteur() {

    FSOUND_Init(44100, 64, 0);
    m_channel = FSOUND_ALL;
    avancement = new QSlider(Qt::Horizontal);
    time = new QTimer;
    m_state = Stopped;
    m_media = NULL;
    m_updateFrequency = 1000;

    connect(time, SIGNAL(timeout()), this, SLOT(updateSlider()));
    connect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
}

void NutshLecteur::setSource(const NutshMetaData& source) {

    if(m_media != NULL) {

        FSOUND_Stream_Close(m_media);
        m_state = Stopped;

        disconnect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
        avancement->setValue(0);
        m_channel = 0;
        time->stop();
    }

    m_media = FSOUND_Stream_Open(source.getChemin().toAscii().constData(), 0, 0, 0);
    m_channel = FSOUND_Stream_Play(FSOUND_FREE, m_media);

    FSOUND_SetSurround(m_channel, true);

    m_state = Stopped;
    avancement->setMaximum(FSOUND_Stream_GetLengthMs(m_media));
    time->start(m_updateFrequency);
    m_source = source.getChemin();
}

bool NutshLecteur::isPaused() {

    if(m_state == Paused) {

        return true;

    } else {

        return false;
    }
}

bool NutshLecteur::isPlaying() {

    if(m_state == Playing) {

        return true;

    } else {

        return false;
    }
}

void NutshLecteur::play() {

    if(m_state == Paused) {

        FSOUND_SetPaused(m_channel, false);

    } else if(m_state == Stopped) {

        m_channel = FSOUND_Stream_Play(FSOUND_FREE, m_media);
    }

    m_state = Playing;
    time->start(m_updateFrequency);
}

void NutshLecteur::pause() {

    time->stop();

    FSOUND_SetPaused(m_channel, true);

    m_state = Paused;
}

void NutshLecteur::stop() {

    FSOUND_Stream_Stop(m_media);

    m_state = Stopped;
    time->stop();
    avancement->setSliderPosition(0);
}

QSlider* NutshLecteur::getPosSlider() {

    return avancement;
}

void NutshLecteur::updateSlider() {

    QObject::disconnect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
    avancement->setSliderPosition(avancement->sliderPosition()+m_updateFrequency);

    emit tick(avancement->sliderPosition()+m_updateFrequency);

    if(avancement->sliderPosition() == avancement->maximum()) {

        emit finished();
        emit aboutToFinish();
    }

    QObject::connect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));

}

void NutshLecteur::setPos(int pos) {

    FSOUND_Stream_SetTime(m_media, pos);
}

#endif
