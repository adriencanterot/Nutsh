#ifndef NUTSHINDEXER_H
#define NUTSHINDEXER_H

#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QStringList>
#include <QThread>
#include "nutshmetadata.h"
#include "nutshsqlsaver.h"
#include "preprocess.h"

class Indexer: public QThread {
    Q_OBJECT
    public:
        Indexer(const QString&, const QString&);
        void run();

    public slots:
        void forceQuit();

    signals:
        void stopper(bool);
        void fatalError(QString);
        void updateBar(int, int);

    private:
        NutshSqlSaver* saver;
        QDirIterator* iterator;
        QString chemin, m_table;
        QStringList filtre;
        bool loopRunning;

};
class NutshComunicator;
class NutshIndexer : public QObject
{
        Q_OBJECT
    public:
        NutshIndexer(NutshComunicator* corePath);
        QList<NutshMetaData> sortie() const ;
        void indexer(const QString&, const QString&);
    private slots:
        void updateBar(int, int);
        void cancelAction();
        void showMessage(QString);

    private :
        NutshComunicator* core;
        QDirIterator *iterator;
        QStringList *listeFichier, *filtre;
	QList<NutshMetaData> metaDataList;
        Indexer* scan;
};

#endif // NUTSHINDEXER_H
