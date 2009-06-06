#ifndef NUTSHMETADATA_H
#define NUTSHMETADATA_H

#include <QDateTime>
#include <fileref.h>
#include <mpegfile.h>
#include <tag.h>
#include <id3v2header.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include <QUrl>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QVariantList>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QWidget>
#include <QFile>

class NutshMetaData
{
public:
    NutshMetaData();
    //depuis une requete SQL
    NutshMetaData(const QVariantList&);
    //depuis un fichier
    NutshMetaData(const QString&);
    bool contains(const QString&);
    NutshMetaData(const NutshMetaData &m);
    NutshMetaData operator=(const NutshMetaData &m);
    //Charger a partir d'un QVariantList
    void setSavingDate(const QDateTime&);
    QString stringListToString(const QStringList&);
    QString getArtiste() const;
    QString getAlbum() const;
    QString getTitre() const;
    QString getDate() const;
    QString getGenre() const;
    QString getDescription() const;
    QDateTime getDateEnregistrement() const;
    QString getChemin() const;
    QPixmap getArtwork() const;
    QTime getDuree() const;
    QStringList getAllMetaDatas();
    int getCompteur() const;
    int getTrack() const;
    int getId() const;


    void setArtiste(const QString&);
    void setAlbum(const QString&);
    void setTitre(const QString&);
    void setDate(const QString&);
    void setGenre(const QString&);
    void setDescription(const QString&);
    void setDateEnregistrement(const QDateTime&);
    void setChemin(const QString&);
//    void setCheminImage(const QString&);
    void setDuree(const QTime&);
    void setAllMetaDatas(const QStringList&);
    void setCompteur(int);
    void setTrack(int);
    bool operator==(const NutshMetaData&);

private :
        QString artiste, album, titre, date, genre, description, chemin, cheminImage;
	QTime duree;
	QStringList metaData;
	QDateTime enregistrement, derniereLecture;
        int compteur, track, id;

};

#endif // NUTSHMETADATA_H
