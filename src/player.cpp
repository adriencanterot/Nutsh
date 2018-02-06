#include "player.h"
#ifdef PHONON

Player::Player() {

    sortieAudio = new Phonon::AudioOutput(Phonon::MusicCategory);
    sortieVideo = new Phonon::AudioOutput(Phonon::VideoCategory);

    Phonon::createPath(this, sortieAudio);
    avancement = new Phonon::SeekSlider(this);
    volume = new Phonon::VolumeSlider(sortieAudio);
}
/*    //Jouer une musique directement
    this->setCurrentSource(source);
    this->play();
}
void Player::setSourceVideo(Phonon::MediaSource source, Phonon::VideoWidget *widget) {
    //Joue une video directement (le widgetVideo doit etre initialise)
    this->stop();
    this->setCurrentSource(source);
    Phonon::createPath(this, sortieVideo);
    Phonon::createPath(this, widget);
    this->play();
}
void Player::jouerMusiqueOuVideo(Phonon::MediaSource adresse, Phonon::VideoWidget *widget) {
    //Determine de quel type est le fichier, et le joue
    if(this->isMusique(Phonon::MediaSource(adresse)))
        this->setSourceMusique(Phonon::MediaSource(adresse));
    else if(this->isVideo(Phonon::MediaSource(adresse)))
        this->setSourceVideo(Phonon::MediaSource(adresse), widget);
    else
	qDebug() << "Impossible de definir le type de fichier";
}*/

bool Player::isMusique(Metadata& data) {

    //return false si la mediasource est une video
    Phonon::MediaObject music0video;
    music0video.setCurrentSource(Phonon::MediaSource(data.getChemin()));

    if(!music0video.hasVideo())

        return true;

    else

        return false;
}

bool Player::isVideo(Metadata& data) {

    //return false si la mediasource est une video
    Phonon::MediaObject music0video;
    music0video.setCurrentSource(Phonon::MediaSource(data.getChemin()));

    if(music0video.hasVideo())

        return true;

    else

        return false;
}

bool Player::isPlaying() {

    if(this->state() == Phonon::PlayingState) {

        return true;

    } else {

        return false;
    }
}

void Player::setSource(const Metadata& source) {

    this->setCurrentSource(Phonon::MediaSource(source.getChemin()));
}

void Player::setSources(const QList<Metadata> &sources) {

    for(int i = 0;i<sources.count();i++) {

        this->enqueue(Phonon::MediaSource(sources.value(i).getChemin()));
    }
}

bool Player::isPaused() {

    if(this->state() == Phonon::PausedState) {

        return true;

    } else {

        return false;
    }
}

Phonon::SeekSlider* Player::getPosSlider() {

    return avancement;
}

Phonon::VolumeSlider *Player::getVolumeSlider() {

    return volume;
}

#endif
#ifdef FMOD

#include "player.h"

Player::Player() {

    FSOUND_Init(44100, 64, 0);
    m_channel = FSOUND_ALL;
    avancement = new QSlider(Qt::Horizontal);
    volume = new QSlider(Qt::Horizontal);
    volume->setValue(100);
    time = new QTimer;
    m_state = Stopped;
    m_media = NULL;
    m_updateFrequency = 1000;

    connect(time, SIGNAL(timeout()), this, SLOT(updateSlider()));
    connect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
    connect(volume, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
}

void Player::setSource(const Metadata& source) {

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
    FSOUND_SetVolume(FSOUND_ALL, volume->value()*2.55);
}

bool Player::isPaused() {

    if(m_state == Paused) {

        return true;

    } else {

        return false;
    }
}

bool Player::isPlaying() {

    if(m_state == Playing) {

        return true;

    } else {

        return false;
    }
}

void Player::play() {

    if(m_state == Paused) {

        FSOUND_SetPaused(m_channel, false);

    } else if(m_state == Stopped) {

        m_channel = FSOUND_Stream_Play(FSOUND_FREE, m_media);
    }

    m_state = Playing;
    time->start(m_updateFrequency);
    FSOUND_SetVolume(FSOUND_ALL, volume->value()*2.55);
}

void Player::pause() {

    time->stop();

    FSOUND_SetPaused(m_channel, true);

    m_state = Paused;
}

void Player::stop() {

    FSOUND_Stream_Stop(m_media);

    m_state = Stopped;
    time->stop();
    avancement->setSliderPosition(0);
}

QSlider* Player::getPosSlider() {

    return avancement;
}

void Player::updateSlider() {

    QObject::disconnect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
    avancement->setSliderPosition(avancement->sliderPosition()+m_updateFrequency);

    emit tick(avancement->sliderPosition()+m_updateFrequency);

    if(avancement->sliderPosition() == avancement->maximum()) {

        emit finished();
        emit aboutToFinish();
    }

    QObject::connect(avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));

}

void Player::setPos(int pos) {

    FSOUND_Stream_SetTime(m_media, pos);
}

QSlider *Player::getVolumeSlider() {

    return volume;
}

void Player::setVolume(int volume) {

    FSOUND_SetVolume(FSOUND_ALL, volume*2.55);
}

#endif
#ifdef FMODeX
Player::Player() {

    this->result = FMOD::System_Create(&system);
    this->result = system->init(1, FMOD_INIT_NORMAL, 0);

    m_avancement = new QSlider(Qt::Horizontal);
    m_volume = new QSlider(Qt::Horizontal);

    timer = new QTimer;
    this->channel = 0;
    m_updatefrequence = 1000;

    connect(timer, SIGNAL(timeout()), this, SLOT(updateSlider()));
    connect(m_avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
    connect(m_volume, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
}
void Player::setSource(const Metadata& data) {

    this->result = this->system->createSound(data.getChemin().toAscii(), (FMOD_MODE)(FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM), 0, &sound);
    this->result = this->system->playSound(FMOD_CHANNEL_FREE, this->sound, false, &channel);

    unsigned int lenght = 0;
    this->sound->getLength(&lenght, FMOD_TIMEUNIT_MS);
    m_avancement->setMaximum(lenght);
}

void Player::play() {

    this->channel->setPaused(false);
    timer->start(m_updatefrequence);
}

void Player::pause() {

    this->channel->setPaused(true);
    timer->stop();
}

void Player::stop() {

    timer->stop();
    this->channel->stop();
    m_avancement->setValue(0);
}

void Player::setPos(int pos) {

    this->channel->setPosition(pos, FMOD_TIMEUNIT_MS);
}

void Player::updateSlider() {

    QObject::disconnect(m_avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));

    m_avancement->setSliderPosition(m_avancement->sliderPosition()+m_updatefrequence);
    emit tick(m_avancement->sliderPosition()+m_updatefrequence);


    if(m_avancement->sliderPosition() == m_avancement->maximum()) {

        emit finished();
        emit aboutToFinish();
    }

    QObject::connect(m_avancement, SIGNAL(valueChanged(int)), this, SLOT(setPos(int)));
}
void Player::setVolume(int volume) {

    this->channel->setVolume(volume*2.55);

}

bool Player::isPlaying() {

    bool playing;
    channel->getPaused(&playing);
    return !playing;
}
bool Player::isPaused() {

    bool playing;
    this->result = channel->getPaused(&playing);

    return playing;
}

QSlider* Player::getPosSlider() {

    return m_avancement;
}

QSlider* Player::getVolumeSlider() {

    return m_volume;
}

#endif
