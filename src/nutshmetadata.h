#ifndef NUTSHMETADATA_H
#define NUTSHMETADATA_H

#include <QDateTime>
#include <fileref.h>
#include <tag.h>
#include <QUrl>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QVariantList>

class NutshMetaData
{
public:
    NutshMetaData();
    //depuis une requete SQL
    NutshMetaData(QVariantList);
    //depuis un fichier
    NutshMetaData(QString);
    bool contains(QString);
    NutshMetaData(const NutshMetaData &m);
    NutshMetaData operator=(const NutshMetaData &m);
    //Charger a partir d'un QVariantList
    void load(QVariantList);
    void setSavingDate(QDateTime);
    QString stringListToString(QStringList);
    QString getArtiste();
    QString getAlbum();
    QString getTitre();
    QString getDate();
    QString getGenre();
    QString getDescription();
    QDateTime getDateEnregistrement();
    QString getChemin();
    QString getCheminImage();
    QTime getDuree();
    QStringList getAllMetaDatas();
    int getCompteur();
    int getTrack();


    void setArtiste(QString);
    void setAlbum(QString);
    void setTitre(QString);
    void setDate(QString);
    void setGenre(QString);
    void setDescription(QString);
    void setDateEnregistrement(QDateTime);
    void setChemin(QString);
    void setCheminImage(QString);
    void setDuree(QTime);
    void setAllMetaDatas(QStringList);
    void setCompteur(int);
    void setTrack(int);
    bool operator==(const NutshMetaData&);

private :
        QString artiste, album, titre, date, genre, description, chemin, cheminImage;
	QTime duree;
	QStringList metaData;
	QDateTime enregistrement, derniereLecture;
        int compteur, track;

};

#endif // NUTSHMETADATA_H
