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
        void inserer(NutshMetaData);
        void update(const NutshMetaData&, const QString&);
        void savePath(const QString& path);


        static void updateColumn(const QString &key, const QString &value, int it);
        static QString sqlStringFormat(const QString&);
        static QString normalStringFormat(const QString&);

        QVariantList modelNutshMetaData(const NutshMetaData&);
        QList<NutshMetaData> getMetaDatas(const QString&);
        QList<NutshMetaData> getResults(const QString&);
        QStringList getFolderList();

        QString crypt(const QString&);

    private:
        QStringList metadatas;
};
#endif // NUTSHSQLSAVER_H
