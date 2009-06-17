#include "nutshplayinginterface.h"
#include "nutshcomunicator.h"

NutshPlayingInterface::NutshPlayingInterface(NutshComunicator* corePath)
{
    core = corePath;

    currentItem = 0;
    //init media
    media = new NutshLecteur;
    //init & alloc widgets

    droite = new QWidget(this);
    droite->resize(600, 350);
    gauche = new QWidget(this);
    gauche->resize(600, 350);

    //init & alloc command buttons

    boutonPrecedent = new QPushButton("", droite);
    boutonPrecedent->setProperty("boutonPrecedent", true);
    boutonPrecedent->move(10, 30);

    boutonSuivant = new QPushButton("", droite);
    boutonSuivant->setProperty("boutonSuivant", true);
    boutonSuivant->move(120, 30);

    boutonStop = new QPushButton("", droite);
    boutonStop->setProperty("boutonStop", true);
    boutonStop->move(180, 30);

    boutonRevenir = new QPushButton("", droite);
    boutonRevenir->setProperty("boutonRevenir", true);
    boutonRevenir->move(550, 80);

    boutonPlayPause = new QPushButton("", droite);
    boutonPlayPause->setProperty("boutonPlayPause", true);
    boutonPlayPause->move(60, 15);

    //init & alloc controls
    tempsLabel = new NutshLabel(core, "00:00");
    tempsLabel->setParent(droite);
    tempsLabel->move(450, 110);
    tempsLabel->setStyleSheet("font-size: 22px;");

    //init & alloc labels

    titre = new NutshEditLabel("Sans Titre", droite);
    titre->move(190, 110);
    artiste = new NutshEditLabel("Sans Artiste", droite);
    artiste->move(190, 140);
    album = new NutshEditLabel("Sans Album", droite);
    album->move(190, 170);

    titre->setStyleSheet("font-size: 20px;");
    artiste->setStyleSheet("font-size: 20px;");
    album->setStyleSheet("font-size: 20px;");

    artwork = new NutshLabel(core);
    artwork->setParent(gauche);

    artisteCP = new NutshLabel(core, "");
    titreCP = new NutshLabel(core, "");
    tempsLabelCP = new NutshLabel(core, "");

    core->bar()->addPermanentWidget(artisteCP);
    core->bar()->addPermanentWidget(titreCP);
    core->bar()->addPermanentWidget(tempsLabelCP);

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
    connect(artiste, SIGNAL(returnPressed(QString)), &current, SLOT(setArtiste(QString)));
    connect(album, SIGNAL(returnPressed(QString)), &current, SLOT(setAlbum(QString)));
    connect(titre, SIGNAL(returnPressed(QString)), &current, SLOT(setTitre(QString)));
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

    qDebug() <<  currentItem;

    if (currentItem == 0) {

        boutonPrecedent->setDisabled(true);
    }

    if(currentItem == playlist.count()-1) {

        boutonSuivant->setDisabled(true);
    }
}

void NutshPlayingInterface::swapToPlay() {

    core->metadatainterface()->hide();

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
