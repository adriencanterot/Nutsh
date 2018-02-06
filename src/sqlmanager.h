#ifndef NUTSHSQLSAVER_H
#define NUTSHSQLSAVER_H

#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include "metadata.h"
#include "preprocess.h"
#include "installationwizard.h"

class SqlManager
{
    public:
	SqlManager();

        bool trouverDansTable(const Metadata&);
        bool tableExists(const QString&);
        bool connect();
        bool nouvelleListe(const QString&);

        void completeMetaData(Metadata&);
        void inserer(QList<Metadata>, const QString&);
        void inserer(Metadata, const QString&);
        void destroy(Metadata);
        void destroyFromList(Metadata, const QString&);
        insertError inserer(Metadata);
        void update(const Metadata&);
        void savePath(const QString& path);
        void played(Metadata&);
        void remove(const QString&);
        void rename(const QString&, const QString&);
        QStringList getPlaylists();


        static void updateColumn(const QString &key, const QString &value, int it);
        static QString addSlashes(const QString&);
        static QString sqlStringFormat(const QString&);
        static QString normalStringFormat(const QString&);

        QVariantList modelMetadata(const Metadata&);
        QList<Metadata> getMetaDatas(const QString& listName = QString());
        QList<Metadata> getResults(const QString&);
        QList<Metadata> getLastImport(int);
        QList<Metadata> getMostReaden(int);
        QList<Metadata> getLastReaden(int);
        QStringList getFolderList();

        QString crypt(const QString&);
        int getListId(const QString& listName);

    private:
        QStringList metadatas;
};
#endif // NUTSHSQLSAVER_H
