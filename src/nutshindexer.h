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
#include "nutshmetadata.h"
#include "nutshsqlsaver.h"
#include "preprocess.h"


class NutshIndexer
{
    public:
        NutshIndexer();
	QList<NutshMetaData> sortie();
        void indexer(QString, QProgressDialog*, QString);
    protected :
	bool trouver(QString, QStringList*);

    private :
        QDirIterator *iterator;
        QStringList *listeFichier, *filtre;
	QList<NutshMetaData> metaDataList;
};

#endif // NUTSHINDEXER_H
