#include "nutshlecteur.h"

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
    }
    else {
        return false;
    }
}
void NutshLecteur::setSource(NutshMetaData& source) {
    this->setCurrentSource(Phonon::MediaSource(source.getChemin()));
}
void NutshLecteur::setSources(QList<NutshMetaData> sources) {
    for(int i = 0;i<sources.count();i++) {
        this->enqueue(Phonon::MediaSource(sources.value(i).getChemin()));
    }
}
bool NutshLecteur::isPaused() {
    if(this->state() == Phonon::PausedState) {
        return true;
    }
    else {
        return false;
    }
}
Phonon::SeekSlider* NutshLecteur::getProgressbar() {
    return avancement;
}
