#include "metadata.h"
#include "sqlmanager.h"
using namespace TagLib;

Metadata::Metadata()
{

    compteur = -1;
    id = -1;
    local_id = -1;
    m_location = fromNowhere;
}

Metadata::Metadata(const Metadata &m) {

    artiste = m.artiste;
    album = m.album;
    titre = m.titre;
    id = m.id;
    local_id = m.local_id;

    date = m.date;
    genre = m.genre;
    description = m.description;
    track = m.track;

    chemin = m.chemin;

    duree = m.duree;

    metaData = m.metaData;

    enregistrement = m.enregistrement;
    compteur = m.compteur;
    derniereLecture = m.derniereLecture;
    file = m.file;

    m_location = m.m_location;

}

Metadata::Metadata(const QString &source) {


    file = FileRef(source.toAscii().constData());

    if(!file.isNull()) {

        artiste = file.tag()->artist().toCString(true);
        album = file.tag()->album().toCString(true);
        titre = file.tag()->title().toCString(true);
        date = file.tag()->year();
        description = file.tag()->comment().toCString(true);
        genre = file.tag()->genre().toCString(true);
        track = file.tag()->track();
        duree = file.audioProperties()->length();
        compteur = 0;
        m_location = fromPlaylist;
        chemin = source;
    }
}

Metadata::Metadata(const QVariantList &resultatLigne) {

    /* Initialisation depuis un resulat SQL
      generalement depuis une sortie,
      vers des widget (voir schema dans ressources)
      */

    this->id = resultatLigne.value(0).toInt();

    artiste = resultatLigne.value(1).toString();
    album = resultatLigne.value(2).toString();
    titre = resultatLigne.value(3).toString();

    date = resultatLigne.value(4).toString();
    genre = resultatLigne.value(5).toString();
    description = resultatLigne.value(6).toString();
    track = resultatLigne.value(7).toInt();

    chemin = resultatLigne.value(8).toString();

    duree = resultatLigne.value(10).toInt();
    enregistrement = resultatLigne.value(11).toDateTime();
    derniereLecture = resultatLigne.value(12).toDateTime();
    compteur = resultatLigne.value(13).toInt();

    for (int i = 0;i<resultatLigne.count();i++) {

        //initialisation d'une QStringList contenant tout les resultats;
        metaData.append(resultatLigne.value(i).toString());
    }

    m_location = fromPlaylist;
    local_id = -1;

}

void Metadata::setSavingDate(const QDateTime &dateEnregistrement) {

    enregistrement = dateEnregistrement;
    metaData.append(enregistrement.toString());
}

searchResultType Metadata::contains(const QString &str) {

    if(titre.contains(str, Qt::CaseInsensitive)) {
        return Song;
    }
    if(artiste.contains(str, Qt::CaseInsensitive)) {
         return Artist;
    }
    if(album.contains(str, Qt::CaseInsensitive)) {
        return Album;
    }

    else {
        return Nothing;
    }

}

/* Toute les methodes accesseuses */

QString Metadata::getArtiste() const {

    return artiste;
}

QString Metadata::getAlbum() const {

    return album;
}

QString Metadata::getTitre() const {

    return titre;
}

QString Metadata::getDate() const {

    return date;
}

QString Metadata::getGenre() const {

    return genre;
}

QString Metadata::getDescription() const {

    return description;
}

QDateTime Metadata::getDateEnregistrement() const {

    return enregistrement;
}

QString Metadata::getChemin() const {

    return chemin;
}

int Metadata::getCompteur() const {

    return compteur;
}

int Metadata::getDuree() const {

    return duree;
}

//QString Metadata::getCheminImage() const {
//
//    return cheminImage;
//}

Metadata Metadata::operator=(const Metadata &m) {

    artiste = m.artiste;
    album = m.album;
    titre = m.titre;
    id = m.id;
    local_id = m.local_id;

    date = m.date;
    genre = m.genre;
    description = m.description;
    track = m.track;

    chemin = m.chemin;

    duree = m.duree;
    metaData = m.metaData;
    enregistrement = m.enregistrement;
    compteur = m.compteur;
    derniereLecture = m.derniereLecture;
    file = m.file;
    m_location = m.m_location;

    return *this;
}

QStringList Metadata::getAllMetaDatas() {

    metaData.append(artiste);
    metaData.append(album);
    metaData.append(titre);

    metaData.append(date);
    metaData.append(genre);
    metaData.append(description);
    metaData.append(QString(track));
    metaData.append(QString("%1").arg(duree));

    metaData.append(chemin);

    return metaData;
}

int Metadata::getTrack() const {

    return track;
}

QDateTime Metadata::getDerniereLecture() const {

    return derniereLecture;
}


bool Metadata::operator==(const Metadata& m) {
    
    if(id == m.id) {
      return true;
  } else {
      return false;
  }
}


void Metadata::setArtiste(const QString &a) {

    artiste = a;

    SqlManager::updateColumn("artiste", artiste, id);

    FileRef f(chemin.toAscii().constData());
    Tag *t = f.file()->tag();

    t->setArtist(artiste.toUtf8().constData());

    f.save();
}

void Metadata::setAlbum(const QString &a) {

    album = a;
    SqlManager::updateColumn("album", album, id);

    FileRef f(chemin.toAscii().constData());
    Tag *t = f.file()->tag();

    t->setAlbum(album.toUtf8().constData());

    f.save();
}

void Metadata::setTitre(const QString &nt) { //nt -> new title

    titre = nt;
    SqlManager::updateColumn("titre", titre, id);

    FileRef f(chemin.toAscii().constData());
    Tag *t = f.file()->tag(); // t -> tag

    t->setTitle(titre.toUtf8().constData());

    f.save();
}

void Metadata::setDate(const QString &d) {

    date = d;
}

void Metadata::setGenre(const QString &g) {

    genre = g;
}

void Metadata::setDescription(const QString &d) {

    description = d;
}

void Metadata::setDateEnregistrement(const QDateTime &d) {

    enregistrement = d;

}

void Metadata::setChemin(const QString &c) {

    chemin = c;

    //ajoute le chemin en plus de celui existant [a faire]
}

void Metadata::setArtwork(const QPixmap &c) {

}

void Metadata::setDuree(const int d) {

    duree = d;
}

void Metadata::setAllMetaDatas(const QStringList &m) {

    metaData = m;
}

void Metadata::setCompteur(int t) {

    SqlManager::updateColumn("compteur", QString("%1").arg(t), this->id);
    compteur = t;

}

void Metadata::setTrack(int t) {

    track = t;
}

void Metadata::setDerniereLecture(const QDateTime& date) {

    SqlManager::updateColumn("derniereLecture", date.toString(), this->id);
    derniereLecture = date;
}

int Metadata::getId() const {

    return id;
}

QPixmap Metadata::getArtwork() const {

    if(QFile::exists(this->getChemin())) {

        MPEG::File file(this->getChemin().toAscii().constData());
        ID3v2::Tag *tag = file.ID3v2Tag();
        ID3v2::FrameList l = tag->frameList("APIC");

        QImage image;

        if(l.isEmpty())
            return QPixmap(":/img/images/sans-image.png", "png").scaled(130, 130);

        ID3v2::AttachedPictureFrame *f =
            static_cast<ID3v2::AttachedPictureFrame *>(l.front());

        image.loadFromData((const unsigned char *) f->picture().data(), f->picture().size());

        if(image.isNull())
            return QPixmap(":/img/images/sans-image.png", "png").scaled(130, 130);
        else
            return QPixmap::fromImage(image).scaled(130, 130);

    } else {

        return QPixmap(":/img/images/sans-image.png", "png").scaled(130, 130);
    }

}

Metadata::~Metadata() {
}

void Metadata::setId(int newId) {

    id = newId;
}

bool Metadata::isValid() {

    return !file.isNull();
}

bool Metadata::isDefault() {

    if(this->titre == "Sans titre" && this->album == "Sans album" && this->artiste == "Sans artiste") {
        return true;
    } else {
        return false;
    }
}

QDebug Metadata::operator<<(const Metadata& meta) {
    //return QDebug(&QString("Metadata(\"%1\" - \"%2\" - \"%3\")").arg(meta.getTitre()).arg(meta.getAlbum()).arg(meta.getArtiste()));
}

Provenance Metadata::location() const {
    return m_location;
}
void Metadata::setLocation(Provenance newLocation) {
    this->m_location = newLocation;
}

void Metadata::setLocalid(int id) {
    this->local_id = id;
}

int Metadata::getlocalid() const {
    return this->local_id;
}
