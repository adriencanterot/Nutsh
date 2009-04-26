#ifndef NUTSHSQLSAVER_H
#define NUTSHSQLSAVER_H

#include <QtSql>
#include <QString>
#include <QDir>
#include <QDesktopServices>
#include "nutshmetadata.h"
#include "preprocess.h"

class NutshSqlSaver
{
    public:
	NutshSqlSaver();
        static void inserer(NutshMetaData, QString);
        static bool trouverDansTable(QString, NutshMetaData);
        static void completeMetaData(NutshMetaData incomplete);
        static void inserer(QList<NutshMetaData>, QString);
        static QList<NutshMetaData> getMetaDatas(QString);
        static void update(NutshMetaData, NutshMetaData, QString);
        QString stringListToString(QStringList);
        static bool nouvelleListe(QString);
        static QString sqlStringFormat(QString);
        static QString normalStringFormat(QString);
        static bool connect();
        static QList<NutshMetaData> getResults(QString);

    private :
};
#endif // NUTSHSQLSAVER_H
