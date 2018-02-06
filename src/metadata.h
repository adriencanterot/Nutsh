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

class Metadata : public QObject
{
    Q_OBJECT

public:
    Metadata();
    //depuis une requete SQL
    Metadata(const QVariantList&);
    //depuis un fichier
    Metadata(const QString&);
    searchResultType contains(const QString&);
    bool isDefault();
    Metadata(const Metadata &m);
    Metadata operator=(const Metadata &m);
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
    int getlocalid() const;
    bool operator==(const Metadata&);
    QDebug operator<<(const Metadata&);
    bool isValid();
    Provenance location() const;

    virtual ~Metadata();

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
    void setLocalid(int);


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
            id,
            local_id;

        int duree;
        Provenance m_location;

        TagLib::FileRef file;

};

#endif // NUTSHMETADATA_H
