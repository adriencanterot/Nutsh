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
#include "metadata.h"
#include "sqlmanager.h"
#include "preprocess.h"
class Core;
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
        SqlManager* saver;
        insertError errorcode;
        QDirIterator* iterator;
        QString chemin;
        QStringList filtre;
        bool loopRunning;

};

class TIndexer : public QThread {

    public:
    TIndexer(const QStringList& pathList, Core*);
    void run();

    private:
    QStringList m_pathList;
    QList<Indexer*> threadList;
    Core* core;
};



#endif // NUTSHINDEXER_H
