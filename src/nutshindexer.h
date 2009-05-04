#ifndef NUTSHINDEXER_H
#define NUTSHINDEXER_H

#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QStringList>
#include <QtGui/QProgressDialog>
#include <QThread>
#include "nutshmetadata.h"
#include "nutshsqlsaver.h"
#include "preprocess.h"

class Indexer: public QThread {
    Q_OBJECT
    public:
        Indexer(QProgressDialog*, QString, QString);
        void run();
    signals:
        void updateBar(int, int);

    private:
        QDirIterator* iterator;
        QString chemin, table;
        QStringList filtre;

};
class NutshIndexer : public QObject
{
        Q_OBJECT
    public:
        NutshIndexer();
	QList<NutshMetaData> sortie();
        void indexer(QString, QProgressDialog*, QString);
    private slots:
        void updateBar(int, int);
    protected :
	bool trouver(QString, QStringList*);

    private :
        QProgressDialog* progression;
        QDirIterator *iterator;
        QStringList *listeFichier, *filtre;
	QList<NutshMetaData> metaDataList;
};

#endif // NUTSHINDEXER_H
