#include "nutshplayinginterface.h"
#include "nutshcomunicator.h"

NutshPlayingInterface::NutshPlayingInterface(NutshComunicator* corePath)
{
    qDebug() << "Initializing NutshPlayingInterface...";
    core = corePath;
    tickCompteur = true;

    currentItem = 0;
    nextAction = Normal;
    //init media
    media = new NutshLecteur;
    //init & alloc widgets

    actionsButtons = new QWidget;

    //init & alloc command buttons

    boutonPrecedent = new QPushButton("", actionsButtons);
    boutonPrecedent->setProperty("boutonPrecedent", true);

    boutonSuivant = new QPushButton("", actionsButtons);
    boutonSuivant->setProperty("boutonSuivant", true);

    boutonStop = new QPushButton("", actionsButtons);
    boutonStop->setProperty("boutonStop", true);

    boutonRandom = new QPushButton("", actionsButtons);
    boutonRandom->setProperty("boutonRandom", true);
    boutonRandom->setCheckable(true);


    boutonRepeat = new QPushButton("", actionsButtons);
    boutonRepeat->setProperty("boutonRepeat", true);
    boutonRepeat->setCheckable(true);


    boutonPlayPause = new QPushButton("", actionsButtons);
    boutonPlayPause->setProperty("boutonPlay", true);

    //init & alloc controls
    tempsLabel = new NutshLabel(core, "00:00");
    tempsLabel->setParent(this);
    tempsLabel->setStyleSheet("font-size: 22px;");

    //init & alloc labels

    titre = new NutshEditLabel("Sans Titre", this);
    artiste = new NutshEditLabel("Sans Artiste", this);
    album = new NutshEditLabel("Sans Album", this);
    titre->setStyleSheet("font-size: 20px;");
    artiste->setStyleSheet("font-size: 20px;");
    album->setStyleSheet("font-size: 20px;");

    artwork = new NutshLabel(core);
    artwork->setStyleSheet("min-width: 130px; min-height: 130px;");
    artwork->setParent(this);

    artisteCP = new NutshLabel(core, "");
    titreCP = new NutshLabel(core, "");
    tempsLabelCP = new NutshLabel(core, "");

    core->bar()->addPermanentWidget(artisteCP);
    core->bar()->addPermanentWidget(titreCP);
    core->bar()->addPermanentWidget(tempsLabelCP);

    media->getPosSlider()->setParent(this);
    media->getVolumeSlider()->setParent(this);

    QHttp *request = new QHttp;
    connect(request, SIGNAL(done(bool)), this, SLOT(daily()));
    request->get("http://www.freezik.fr/journalier.php", &to);
}
void NutshPlayingInterface::sigandslots() {

    connect(boutonPlayPause, SIGNAL(clicked()), this, SLOT(playPause()));
    connect(boutonStop, SIGNAL(clicked()), this, SLOT(stop()));
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(media, SIGNAL(finished()), this, SLOT(playPause()));
    connect(boutonPrecedent, SIGNAL(clicked()), this, SLOT(previous()));
    connect(boutonSuivant, SIGNAL(clicked()), this, SLOT(next()));
    connect(media, SIGNAL(finished()), this, SLOT(whatsNext()));
    connect(artiste, SIGNAL(returnPressed(QString)), &current, SLOT(setArtiste(QString)));
    connect(album, SIGNAL(returnPressed(QString)), &current, SLOT(setAlbum(QString)));
    connect(titre, SIGNAL(returnPressed(QString)), &current, SLOT(setTitre(QString)));
    connect(boutonRepeat, SIGNAL(clicked()), this, SLOT(repeat()));
    connect(boutonRandom, SIGNAL(clicked()), this, SLOT(random()));
}
void NutshPlayingInterface::load(const NutshMetaData &data) {

    if(data.getId() != -1) { // si la métadonnée n'est pas vide

        currentItem = 0;
        qDebug() << data.getId();

        tickCompteur = true;
        artwork->setPixmap(data.getArtwork());
        titre->setText("Sans Titre");
        album->setText("Sans Album");
        artiste->setText("Sans Artiste");

        if(!data.getTitre().isEmpty()) {

            titre->setText(data.getTitre().left(30));
        }

        if(!data.getAlbum().isEmpty()) {

            album->setText(data.getAlbum().left(30));
        }

        if(!data.getArtiste().isEmpty()) {

            artiste->setText(data.getArtiste().left(30));
        }

        current = data;
        lastRead.append(data);
        if(lastRead.count() >= 5) lastRead.removeLast();

        currentItem = this->playlist.indexOf(current);
        media->setSource(data);
        media->play();
        boutonPlayPause->setStyleSheet("background-image: url(\":/img/images/pause.png\");");
        this->setStatus();
    } else {
        core->swapInterface(MetaDataInterface);
    }
}

void NutshPlayingInterface::load(const QList<NutshMetaData> &metaList) {

    boutonPrecedent->setEnabled(true);
    boutonSuivant->setEnabled(true);
    playlist = metaList;

    if (currentItem == 0) {

        boutonPrecedent->setDisabled(true);
    }

    if(currentItem == playlist.count()-1) {

        boutonSuivant->setDisabled(true);
    }
}

void NutshPlayingInterface::tick(qint64 time) {

     QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
     tempsLabel->setText(displayTime.toString("mm:ss"));
     tempsLabelCP->setText(displayTime.toString("mm:ss"));

     if(tickCompteur == true && (time/1000) == (current.getDuree())/2) {

         core->getSqlControl()->played(current);
         qDebug() << "Media played" <<  current.getCompteur() << "time(s)";
         tickCompteur = false;
     }
 }

void NutshPlayingInterface::next() {

    if(this->currentItem == playlist.count()-2) {

        boutonSuivant->setDisabled(true);

    } else {

        boutonSuivant->setEnabled(true);
    }

    if(nextAction == Random) {
        whatsNext();
        return;
    }
    boutonPrecedent->setEnabled(true);

    this->currentItem = this->playlist.indexOf(current)+1;
    this->load(playlist.value(this->currentItem));
}

void NutshPlayingInterface::previous() {

    if(this->currentItem == 1) {

        boutonPrecedent->setDisabled(true);
    } else {

        boutonPrecedent->setEnabled(true);
    }

    int cacheCurrentItem = this->currentItem-1;

    this->load(playlist.value(cacheCurrentItem));
    this->currentItem = cacheCurrentItem;

    boutonSuivant->setEnabled(true);
}

void NutshPlayingInterface::setStatus() {

    artisteCP->setText(artiste->text());
    titreCP->setText(titre->text());

}

void NutshPlayingInterface::pauseByKey(QKeyEvent* event) {

    if(event->key() == Qt::Key_Space) {

        this->playPause();
    }
}

QList<NutshMetaData> NutshPlayingInterface::getLastRead() const{

    return lastRead;
}

QWidget* NutshPlayingInterface::getActionsButtons() {

    return actionsButtons;
}

void NutshPlayingInterface::playPause() {

    if(media->isPlaying()) {

        boutonPlayPause->setStyleSheet("background-image: url(\":/img/images/play.png\");");
        media->pause();

    } else {

        boutonPlayPause->setStyleSheet("background-image: url(\":/img/images/pause.png\");");
        media->play();
    }
}

void NutshPlayingInterface::stop() {

    media->stop();
    boutonPlayPause->setStyleSheet("background-image: url(\":/img/images/play.png\")");
}

void NutshPlayingInterface::place(float coef){

    coef = 0;

    this->move(160, 115);
    this->setFixedWidth(440);
    boutonPrecedent->move(10, 30);
    boutonSuivant->move(120, 30);
    boutonStop->move(180, 30);
    boutonPlayPause->move(60, 15);
    boutonRandom->move(25, 60);
    boutonRepeat->move(110, 60);
    boutonRepeat->setFixedSize(30, 20);
    boutonRandom->setFixedSize(30, 20);

    tempsLabel->move(310, 110);
    titre->move(180, 10);
    artiste->move(180, 40);
    album->move(180, 70);
    artwork->move(40, 0);
    actionsButtons->resize(200, 100);
    media->getPosSlider()->move(40, 150);
    media->getPosSlider()->resize(330, 15);
    media->getVolumeSlider()->move(180, 110);
}

void NutshPlayingInterface::random() {

    if(boutonRandom->isChecked()) {

        nextAction = Random;
        boutonRepeat->setChecked(false);

    } else if(!boutonRandom->isChecked()) {

        nextAction = Normal;
    }
}

void NutshPlayingInterface::repeat() {

    if(boutonRepeat->isChecked()) {

        nextAction = Repeat;
        boutonRandom->setChecked(false);

    } else if(!boutonRepeat->isChecked()) {

        nextAction = Normal;
    }
}

void NutshPlayingInterface::whatsNext() {

    switch(nextAction) {

        case Repeat:
        this->load(current);
        break;

        case Random:
        this->load(core->metadatainterface()->totalContent().value(
                (qrand() % (core->metadatainterface()->totalContent().count() - 0 +1) + 0)
                ));
        break;

        case Normal:
        this->next();
        break;

    }
}

void NutshPlayingInterface::daily() {
}
