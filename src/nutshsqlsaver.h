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
        void inserer(NutshMetaData, const QString&);
        void inserer(NutshMetaData);
        bool trouverDansTable(const QString&, const NutshMetaData&);
        bool tableExists(const QString&);
        void completeMetaData(NutshMetaData&);
        void inserer(QList<NutshMetaData>, const QString&);
        QList<NutshMetaData> getMetaDatas(const QString&);
        void update(const NutshMetaData&, const QString&);
        bool nouvelleListe(const QString&);
        static QString sqlStringFormat(const QString&);
        static QString normalStringFormat(const QString&);
        QVariantList modelNutshMetaData(const NutshMetaData&);
        bool connect();
        QList<NutshMetaData> getResults(const QString&);
        QString crypt(const QString&);
        QString unCrypt(const QString&);

    private:
        QStringList metadatas;
};
#endif // NUTSHSQLSAVER_H
