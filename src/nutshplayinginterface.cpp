#include "nutshplayinginterface.h"
#include "nutshcomunicator.h"

NutshPlayingInterface::NutshPlayingInterface(NutshComunicator* corePath)
{
    core = corePath;

    currentItem = 0;
    //init media
    media = new NutshLecteur;
    //init & alloc widgets

    droite = new QWidget;
    gauche = new QWidget;

    //init & alloc command buttons
    boutonPlayPause = new QPushButton("Pause");
    boutonPrecedent = new QPushButton("|<<");
    boutonSuivant = new QPushButton(">>|");
    boutonStop = new QPushButton("Stop");
    boutonRevenir = new QPushButton("<-");

    //init & alloc controls
    tempsLabel = new QLabel("00:00");
    controls = new QHBoxLayout;
    controls->addWidget(media->getPosSlider());
    controls->addWidget(tempsLabel);



    commandButtons = new QHBoxLayout;
    commandButtons->addWidget(boutonPrecedent);
    commandButtons->addWidget(boutonStop);
    commandButtons->addWidget(boutonPlayPause);
    commandButtons->addWidget(boutonSuivant);

    //init & alloc labels

    artiste = new QLabel("Sans Artise");
    album = new QLabel("Sans Album");
    titre = new QLabel("Sans Titre");
    artwork = new QLabel(gauche);

    artisteCP = new QLabel("");
    titreCP = new QLabel("");
    tempsLabelCP = new QLabel("");

    core->bar()->addPermanentWidget(artisteCP);
    core->bar()->addPermanentWidget(titreCP);
    core->bar()->addPermanentWidget(tempsLabelCP);

    infoLabels = new QHBoxLayout;
    infoLabels->addWidget(artiste);
    infoLabels->addWidget(album);

    titreLabel = new QHBoxLayout;
    titreLabel->addWidget(titre);
    titreLabel->addStretch();
    titreLabel->addWidget(boutonRevenir);

    //positionnement
    positionnerDroite = new QVBoxLayout;
    positionnerDroite->addLayout(titreLabel);
    positionnerDroite->addLayout(infoLabels);
    positionnerDroite->addLayout(controls);
    positionnerDroite->addLayout(commandButtons);
    droite->setLayout(positionnerDroite);

    positionnerGauche = new QVBoxLayout;
    positionnerGauche->addWidget(artwork);
    gauche->setLayout(positionnerGauche);

    central = new QSplitter;
    central->addWidget(gauche);
    central->addWidget(droite);

    principal = new QVBoxLayout;
    principal->addWidget(central);

    this->setLayout(principal);


    qDebug() << "NutshPlayingInterface : initialized";
}
void NutshPlayingInterface::sigandslots() {

    connect(boutonPlayPause, SIGNAL(clicked()), this, SLOT(playPause()));
    connect(boutonStop, SIGNAL(clicked()), this, SLOT(stop()));
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(media, SIGNAL(finished()), this, SLOT(playPause()));
    connect(boutonPrecedent, SIGNAL(clicked()), this, SLOT(previous()));
    connect(boutonSuivant, SIGNAL(clicked()), this, SLOT(next()));
    connect(media, SIGNAL(aboutToFinish()), this, SLOT(next()));
    connect(boutonRevenir, SIGNAL(clicked()), core->metadatainterface(), SLOT(swapToList()));
}
void NutshPlayingInterface::load(const NutshMetaData &data) {

    currentItem = 0;
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

    if(lastRead.count() > 5) {

        lastRead.removeLast();
    }

    currentItem = 0;
    media->setSource(data);
    media->play();
    boutonPlayPause->setText("Pause");
    this->setStatus();
}

void NutshPlayingInterface::playPause() {

    if(media->isPlaying()) {

        media->pause();
        boutonPlayPause->setText("Play");

    } else {

        media->play();
        boutonPlayPause->setText("Pause");
    }
}

void NutshPlayingInterface::load(const QList<NutshMetaData> &metaList) {

    boutonPrecedent->setEnabled(true);
    boutonSuivant->setEnabled(true);
    playlist = metaList;
    currentItem = playlist.indexOf(current);

    if (currentItem == 0) {

        boutonPrecedent->setDisabled(true);
    }

    if(currentItem == playlist.count()-1) {

        boutonSuivant->setDisabled(true);
    }
}

void NutshPlayingInterface::swapToPlay() {

    core->metadatainterface()->hide();
    core->droite()->removeWidget(core->metadatainterface());

    core->droite()->addWidget(core->playinginterface());
    core->playinginterface()->show();
}

void NutshPlayingInterface::tick(qint64 time) {

    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

     tempsLabel->setText(displayTime.toString("mm:ss"));
     tempsLabelCP->setText(displayTime.toString("mm:ss"));
 }

void NutshPlayingInterface::next() {

    if(this->currentItem == playlist.count()-2) {

        boutonSuivant->setDisabled(true);

    } else {

        boutonSuivant->setEnabled(true);
    }

    int cacheCurrentItem = this->currentItem+1;
    boutonPrecedent->setEnabled(true);

    this->load(playlist.value(cacheCurrentItem));
    this->currentItem = cacheCurrentItem;
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

void NutshPlayingInterface::stop() {

    boutonPlayPause->setText("Play");
    media->stop();
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
