#ifndef NUTSHMETADATA_H
#define NUTSHMETADATA_H

#include <fileref.h>
#include <mpegfile.h>
#include <tag.h>
#include <id3v2header.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QVariantList>
#include <QPixmap>
#include <QImage>
#include <QFile>
#include "preprocess.h"

class NutshMetaData : public QObject
{
    Q_OBJECT

public:
    NutshMetaData();
    //depuis une requete SQL
    NutshMetaData(const QVariantList&);
    //depuis un fichier
    NutshMetaData(const QString&);
    searchResultType contains(const QString&);
    bool isDefault();
    NutshMetaData(const NutshMetaData &m);
    NutshMetaData operator=(const NutshMetaData &m);
    //Charger a partir d'un QVariantList
    void setSavingDate(const QDateTime&);
    QString getArtiste() const;
    QString getAlbum() const;
    QString getTitre() const;
    QString getDate() const;
    QString getGenre() const;
    QString getDescription() const;
    QDateTime getDateEnregistrement() const;
    QDateTime getDerniereLecture() const;
    QString getChemin() const;
    QPixmap getArtwork() const;
    int getDuree() const;
    QStringList getAllMetaDatas();
    int getCompteur() const;
    int getTrack() const;
    int getId() const;
    bool operator==(const NutshMetaData&);
    QDebug operator<<(const NutshMetaData&);
    bool isValid();
    Provenance location() const;

    virtual ~NutshMetaData();

    public slots:
    void setArtiste(const QString&);
    void setAlbum(const QString&);
    void setTitre(const QString&);
    void setDate(const QString&);
    void setGenre(const QString&);
    void setDescription(const QString&);
    void setDateEnregistrement(const QDateTime&);
    void setDerniereLecture(const QDateTime&);
    void setChemin(const QString&);
    void setArtwork(const QPixmap&);
    void setDuree(const int);
    void setAllMetaDatas(const QStringList&);
    void setCompteur(int);
    void setTrack(int);
    void setId(int);
    void setLocation(const Provenance);


private :
        QString artiste,
                album,
                titre,
                date,
                genre,
                description,
                chemin;

	QStringList metaData;

        QDateTime enregistrement,
                  derniereLecture;

        int compteur,
            track,
            id;

        int duree;
        Provenance m_location;

        TagLib::FileRef file;

};

#endif // NUTSHMETADATA_H
