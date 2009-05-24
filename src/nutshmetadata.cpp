#include "nutshmetadata.h"
using namespace TagLib;

NutshMetaData::NutshMetaData()
{

    compteur = 0;
}

NutshMetaData::NutshMetaData(const NutshMetaData &m) {

    artiste = m.artiste;
    album = m.album;
    titre = m.titre;

    date = m.date;
    genre = m.genre;
    description = m.description;
    track = m.track;

    chemin = m.chemin;
    cheminImage = m.cheminImage;

    duree = m.duree;

    metaData = m.metaData;

    enregistrement = m.enregistrement;
    compteur = m.compteur;
    derniereLecture = m.derniereLecture;
}

NutshMetaData::NutshMetaData(const QString &source) {

    FileRef file(source.toAscii().constData());

    artiste = file.tag()->artist().toCString(true);
    album = file.tag()->album().toCString(true);
    titre = file.tag()->title().toCString(true);
    date = file.tag()->year();
    description = file.tag()->comment().toCString(true);
    genre = file.tag()->genre().toCString(true);
    track = file.tag()->track();

    chemin = source;

}

NutshMetaData::NutshMetaData(const QVariantList &resultatLigne) {

    /* Initialisation depuis un resulat SQL
      generalement depuis une sortie,
      vers des widget (voir schema dans ressources)
      */

    artiste = resultatLigne.value(0).toString();
    album = resultatLigne.value(1).toString();
    titre = resultatLigne.value(2).toString();

    date = resultatLigne.value(3).toString();
    genre = resultatLigne.value(4).toString();
    description = resultatLigne.value(5).toString();
    track = resultatLigne.value(6).toInt();

    chemin = resultatLigne.value(7).toString();
    cheminImage = resultatLigne.value(8).toString();

    duree = resultatLigne.value(9).toTime();
    enregistrement = resultatLigne.value(10).toDateTime();
    derniereLecture = resultatLigne.value(11).toDateTime();
    compteur = resultatLigne.value(12).toInt();

    for (int i = 0;i<resultatLigne.count();i++) {

        //initialisation d'une QStringList contenant tout les resultats;
	metaData.append(resultatLigne.value(i).toString());
    }

}

void NutshMetaData::load(const QVariantList &resultatLigne) {

    this->load(resultatLigne);
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

QString NutshMetaData::getCheminImage() const {

    return cheminImage;
}

NutshMetaData NutshMetaData::operator=(const NutshMetaData &m) {

    artiste = m.artiste;
    album = m.album;
    titre = m.titre;

    date = m.date;
    genre = m.genre;
    description = m.description;
    track = m.track;

    chemin = m.chemin;
    cheminImage = m.cheminImage;

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
    
    if(chemin == m.chemin)
    {
      return true;

    } else {
//        qDebug() << "artiste " << artiste << " - " << m.artiste;
//        qDebug() << "titre " << titre << " - " << m.titre;
//        qDebug() << "date " << date << " - " << m.date;
//        qDebug() << "genre " << genre << " - " << m.genre;
//        qDebug() << "description " << description << " - " << m.description;
//        qDebug() << "track " << track << " - " << m.track;
//        qDebug() << "chemin " << chemin << " - " << m.chemin;
//        qDebug() << "cheminImage " << cheminImage << " - " << m.cheminImage;
//        qDebug() << "duree " << duree << " - " << m.duree;
//        qDebug() << "metaData " << metaData << " - " << m.metaData;
//        qDebug() << "enregistrement " << enregistrement << " - " << m.enregistrement;
//        qDebug() << "compteur " << compteur << " - " << m.compteur;
//        qDebug() << "derniereLecture " << derniereLecture << " - " << m.derniereLecture;

        return false;
    }
}


void NutshMetaData::setArtiste(const QString &a) {

    artiste = a;
}

void NutshMetaData::setAlbum(const QString &a) {

    album = a;
}

void NutshMetaData::setTitre(const QString &t) {

    titre = t;
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
}

void NutshMetaData::setCheminImage(const QString &c) {

    cheminImage = c;
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
