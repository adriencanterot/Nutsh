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
class NutshComunicator;
class Indexer: public QThread {
    Q_OBJECT
    public:
        Indexer(const QString&);
        void run();
        void import();

    public slots:
        void forceQuit();

    signals:
        void stopper(bool);
        void fatalError(QString);
        void updateBar(ProgressionInfo);
        void loopEnded();

    private:
        NutshSqlSaver* saver;
        QDirIterator* iterator;
        QString chemin;
        QStringList filtre;
        bool loopRunning;

};

class NutshIndexer : public QThread {

    public:
    NutshIndexer(const QStringList& pathList, NutshComunicator*);
    void run();

    private:
    QStringList m_pathList;
    QList<Indexer*> threadList;
    NutshComunicator* core;
};



#endif // NUTSHINDEXER_H
