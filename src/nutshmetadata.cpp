#include "nutshmetadata.h"
#include "nutshsqlsaver.h"
using namespace TagLib;

NutshMetaData::NutshMetaData()
{

    compteur = 0;
    id = 0;
}

NutshMetaData::NutshMetaData(const NutshMetaData &m) {

    artiste = m.artiste;
    album = m.album;
    titre = m.titre;
    id = m.id;

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
}

NutshMetaData::NutshMetaData(const QString &source) {


    FileRef file(source.toAscii().constData());

    if(!file.isNull()) {

        artiste = file.tag()->artist().toCString(true);
        album = file.tag()->album().toCString(true);
        titre = file.tag()->title().toCString(true);
        date = file.tag()->year();
        description = file.tag()->comment().toCString(true);
        genre = file.tag()->genre().toCString(true);
        track = file.tag()->track();

        chemin = source;
    }
}

NutshMetaData::NutshMetaData(const QVariantList &resultatLigne) {

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

    duree = resultatLigne.value(10).toTime();
    enregistrement = resultatLigne.value(11).toDateTime();
    derniereLecture = resultatLigne.value(12).toDateTime();
    compteur = resultatLigne.value(13).toInt();

    for (int i = 0;i<resultatLigne.count();i++) {

        //initialisation d'une QStringList contenant tout les resultats;
	metaData.append(resultatLigne.value(i).toString());
    }

}

void NutshMetaData::setSavingDate(const QDateTime &dateEnregistrement) {

    enregistrement = dateEnregistrement;
    metaData.append(enregistrement.toString());
}

QString NutshMetaData::stringListToString(const QStringList &liste) {

    QString chaineRetour;

    for (int i = 0;i<liste.count();i++) {

        chaineRetour.append(liste.value(i));
        qDebug() << "NutshMetaData::stringListToString(QStringList liste) : " << i;
    }

    return chaineRetour;
}

bool NutshMetaData::contains(const QString &str) {

    if(artiste.contains(str, Qt::CaseInsensitive) ||
       album.contains(str, Qt::CaseInsensitive) ||
       titre.contains(str, Qt::CaseInsensitive)
        ) {

                return true;

            } else {

                return false;
            }
}

/* Toute les methodes accesseuses */

QString NutshMetaData::getArtiste() const {

    return artiste;
}

QString NutshMetaData::getAlbum() const {

    return album;
}

QString NutshMetaData::getTitre() const {

    return titre;
}

QString NutshMetaData::getDate() const {

    return date;
}

QString NutshMetaData::getGenre() const {

    return genre;
}

QString NutshMetaData::getDescription() const {

    return description;
}

QDateTime NutshMetaData::getDateEnregistrement() const {

    return enregistrement;
}

QString NutshMetaData::getChemin() const {

    return chemin;
}

int NutshMetaData::getCompteur() const {

    return compteur;
}

QTime NutshMetaData::getDuree() const {

    return duree;
}

//QString NutshMetaData::getCheminImage() const {
//
//    return cheminImage;
//}

NutshMetaData NutshMetaData::operator=(const NutshMetaData &m) {

    artiste = m.artiste;
    album = m.album;
    titre = m.titre;
    id = m.id;

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

    return *this;
}

QStringList NutshMetaData::getAllMetaDatas() {

    metaData.append(artiste);
    metaData.append(album);
    metaData.append(titre);

    metaData.append(date);
    metaData.append(genre);
    metaData.append(description);
    metaData.append(QString(track));
    metaData.append(duree.toString());

    metaData.append(chemin);

    return metaData;
}

int NutshMetaData::getTrack() const {

    return track;
}

bool NutshMetaData::operator==(const NutshMetaData& m) {
    
    if(id == m.id)
    {
      return true;

    } else {

        return false;
    }
}


void NutshMetaData::setArtiste(const QString &a) {

    artiste = a;

    NutshSqlSaver::updateColumn("artiste", artiste, id);

    FileRef f(chemin.toAscii().constData());
    Tag *t = f.file()->tag();

    t->setArtist(artiste.toUtf8().constData());

    f.save();
}

void NutshMetaData::setAlbum(const QString &a) {

    album = a;
    NutshSqlSaver::updateColumn("album", album, id);

    FileRef f(chemin.toAscii().constData());
    Tag *t = f.file()->tag();

    t->setAlbum(album.toUtf8().constData());

    f.save();
}

void NutshMetaData::setTitre(const QString &nt) { //nt -> new title

    titre = nt;
    NutshSqlSaver::updateColumn("titre", titre, id);

    FileRef f(chemin.toAscii().constData());
    Tag *t = f.file()->tag(); // t -> tag

    t->setTitle(titre.toUtf8().constData());

    f.save();
}

void NutshMetaData::setDate(const QString &d) {

    date = d;
}

void NutshMetaData::setGenre(const QString &g) {

    genre = g;
}

void NutshMetaData::setDescription(const QString &d) {

    description = d;
}

void NutshMetaData::setDateEnregistrement(const QDateTime &d) {

    enregistrement = d;

}

void NutshMetaData::setChemin(const QString &c) {

    chemin = c;

    //ajoute le chemin en plus de celui existant [a faire]
}

void NutshMetaData::setArtwork(const QPixmap &c) {

}

void NutshMetaData::setDuree(const QTime &d) {

    duree = d;
}

void NutshMetaData::setAllMetaDatas(const QStringList &m) {

    metaData = m;
}

void NutshMetaData::setCompteur(int t) {

    compteur = t;
}

void NutshMetaData::setTrack(int t) {

    track = t;
}

int NutshMetaData::getId() const {

    return id;
}

QPixmap NutshMetaData::getArtwork() const {

    if(QFile::exists(this->getChemin())) {

        MPEG::File file(this->getChemin().toAscii().constData());
        ID3v2::Tag *tag = file.ID3v2Tag();

        ID3v2::FrameList l = tag->frameList("APIC");

        QImage image;

        if(l.isEmpty())
            return QPixmap::fromImage(image);

        ID3v2::AttachedPictureFrame *f =
            static_cast<ID3v2::AttachedPictureFrame *>(l.front());

        image.loadFromData((const unsigned char *) f->picture().data(), f->picture().size());

        return QPixmap::fromImage(image).scaled(130, 130);

    } else {

        return QPixmap();
    }

}

NutshMetaData::~NutshMetaData() {
}

void NutshMetaData::setId(int newId) {

    id = newId;
}

bool NutshMetaData::isValid() {

    if(file.isNull()) {

        return false;
    } else {
        return true;
    }
}
