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
NutshMetaData::NutshMetaData(QString source) {
    FileRef file(source.toAscii());
    artiste = file.tag()->artist().toCString(true);
    album = file.tag()->album().toCString(true);
    titre = file.tag()->title().toCString(true);
    date = file.tag()->year();
    description = file.tag()->comment().toCString(true);
    genre = file.tag()->genre().toCString(true);
    track = file.tag()->track();
    chemin = source;

}
NutshMetaData::NutshMetaData(QVariantList resultatLigne) {
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
void NutshMetaData::load(QVariantList resultatLigne) {
    this->load(resultatLigne);
}
void NutshMetaData::setSavingDate(QDateTime dateEnregistrement) {
    enregistrement = dateEnregistrement;
    metaData.append(enregistrement.toString());
}
QString NutshMetaData::stringListToString(QStringList liste) {
    QString chaineRetour;
    for (int i = 0;i<liste.count();i++) {
	chaineRetour.append(liste.value(i));
        qDebug() << "NutshMetaData::stringListToString(QStringList liste) : " << i;
    }
    return chaineRetour;
}

bool NutshMetaData::contains(QString str) {
    if(artiste.contains(str, Qt::CaseInsensitive) ||
       album.contains(str, Qt::CaseInsensitive) ||
       titre.contains(str, Qt::CaseInsensitive)
        ) {
                return true;
            }
    else {
                return false;
            }
}

/* Toute les methodes accesseuses */
QString NutshMetaData::getArtiste() {
    return artiste;
}
QString NutshMetaData::getAlbum() {
    return album;
}
QString NutshMetaData::getTitre() {
    return titre;
}
QString NutshMetaData::getDate() {
    return date;
}
QString NutshMetaData::getGenre() {
    return genre;
}
QString NutshMetaData::getDescription() {
    return description;
}
QDateTime NutshMetaData::getDateEnregistrement() {
    return enregistrement;
}
QString NutshMetaData::getChemin() {
    return chemin;
}
int NutshMetaData::getCompteur() {
    return compteur;
}
QTime NutshMetaData::getDuree() {
    return duree;
}
QString NutshMetaData::getCheminImage() {
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
int NutshMetaData::getTrack() {
    return track;
}

bool NutshMetaData::operator==(const NutshMetaData& m) {
    
    if(chemin == m.chemin)
    {
        return true;
    }
    else {
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

void NutshMetaData::setArtiste(QString a) {
    artiste = a;
}
void NutshMetaData::setAlbum(QString a) {
    album = a;
}
void NutshMetaData::setTitre(QString t) {
    titre = t;
}
void NutshMetaData::setDate(QString d) {
    date = d;
}
void NutshMetaData::setGenre(QString g) {
    genre = g;
}
void NutshMetaData::setDescription(QString d) {
    description = d;
}
void NutshMetaData::setDateEnregistrement(QDateTime d) {
    enregistrement = d;
}
void NutshMetaData::setChemin(QString c) {
    chemin = c;
}
void NutshMetaData::setCheminImage(QString c) {
    cheminImage = c;
}
void NutshMetaData::setDuree(QTime d) {
    duree = d;
}
void NutshMetaData::setAllMetaDatas(QStringList m) {
    metaData = m;
}
void NutshMetaData::setCompteur(int t) {
    compteur = t;
}
void NutshMetaData::setTrack(int t) {
    track = t;
}
