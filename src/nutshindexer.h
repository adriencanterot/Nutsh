#ifndef NUTSHINDEXER_H
#define NUTSHINDEXER_H

#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QStringList>
#include "nutshmetadata.h"
#include "preprocess.h"


class NutshIndexer
{
    public:
        NutshIndexer();
	QList<NutshMetaData> sortie();
        void indexer(QString);
    protected :
	bool trouver(QString, QStringList*);

    private :
        QDirIterator *iterator;
        QStringList *listeFichier, *filtre;
	QList<NutshMetaData> metaDataList;
};

#endif // NUTSHINDEXER_H