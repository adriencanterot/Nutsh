#ifndef NUTSHSQLSAVER_H
#define NUTSHSQLSAVER_H

#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include "nutshmetadata.h"
#include "preprocess.h"
#include "nutshinstallationwizard.h"

class NutshSqlSaver
{
    public:
	NutshSqlSaver();

        bool trouverDansTable(const NutshMetaData&);
        bool tableExists(const QString&);
        bool connect();
        bool nouvelleListe(const QString&);

        void completeMetaData(NutshMetaData&);
        void inserer(QList<NutshMetaData>, const QString&);
        void inserer(NutshMetaData, const QString&);
        void destroy(NutshMetaData);
        void destroyFromList(NutshMetaData, const QString&);
        insertError inserer(NutshMetaData);
        void update(const NutshMetaData&);
        void savePath(const QString& path);
        void played(NutshMetaData&);
        void remove(const QString&);
        void rename(const QString&, const QString&);
        QStringList getPlaylists();


        static void updateColumn(const QString &key, const QString &value, int it);
        static QString addSlashes(const QString&);
        static QString sqlStringFormat(const QString&);
        static QString normalStringFormat(const QString&);

        QVariantList modelNutshMetaData(const NutshMetaData&);
        QList<NutshMetaData> getMetaDatas(const QString& listName = QString());
        QList<NutshMetaData> getResults(const QString&);
        QList<NutshMetaData> getLastImport(int);
        QList<NutshMetaData> getMostReaden(int);
        QList<NutshMetaData> getLastReaden(int);
        QStringList getFolderList();

        QString crypt(const QString&);
        int getListId(const QString& listName);

    private:
        QStringList metadatas;
};
#endif // NUTSHSQLSAVER_H
