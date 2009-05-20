#ifndef NUTSHSQLSAVER_H
#define NUTSHSQLSAVER_H

#include <QtSql>
#include <QString>
#include <QDir>
#include <QDesktopServices>
#include "nutshmetadata.h"
#include "preprocess.h"
#include "nutshinstallationwizard.h"

class NutshSqlSaver
{
    public:
	NutshSqlSaver();
        void inserer(NutshMetaData, QString);
        bool trouverDansTable(QString, NutshMetaData);
        bool tableExists(QString);
        void completeMetaData(NutshMetaData incomplete);
        void inserer(QList<NutshMetaData>, QString);
        QList<NutshMetaData> getMetaDatas(QString);
        void update(NutshMetaData, NutshMetaData, QString);
        QString stringListToString(QStringList);
        bool nouvelleListe(QString);
        static QString sqlStringFormat(QString);
        static QString normalStringFormat(QString);
        bool connect();
        QList<NutshMetaData> getResults(QString);

    private:
        QStringList metadatas;
};
#endif // NUTSHSQLSAVER_H
