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
        Indexer(const QString&);
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
        QString chemin;
        QStringList filtre;
        bool loopRunning;

};

#endif // NUTSHINDEXER_H
