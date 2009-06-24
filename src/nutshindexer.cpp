#include "nutshindexer.h"
#include "nutshcomunicator.h"

Indexer::Indexer(const QString& path) {

    chemin = path;
    filtre << FORMATS_SUPPORTES;
    this->setTerminationEnabled(true);
    loopRunning = true;
    saver = new NutshSqlSaver;
    saver->savePath(path);
    connect(this, SIGNAL(finished()), this, SLOT(quit()));
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(forceQuit()));
}

void Indexer::run() {

    int total = 0;
    QStringList filePaths;
    emit updateBar(1, 0) ;

    iterator = new QDirIterator(chemin, filtre, QDir::NoFilter, QDirIterator::Subdirectories);

    while(iterator->hasNext()) {

        filePaths.append(iterator->next());
        total++;

        emit updateBar(total, 0);

        if(loopRunning == false) {

            break;
        }
    }

    if(filePaths.count() == 0) {

        emit fatalError("Aucun fichier trouvé dans le dossier spécifié");
    }

    emit updateBar(0, 0);



    for(int i = 0;i<filePaths.count();i++) {

        NutshMetaData data(filePaths.value(i));
        saver->inserer(data);
        emit updateBar(i+1, total);

        if(loopRunning == false || filePaths.count() == 0 || i == filePaths.count()) {

            break;
        }

    }
    emit loopEnded();

    this->exec();
}
void Indexer::forceQuit() {

    loopRunning = false;
    this->terminate();
}

NutshIndexer::NutshIndexer(const QStringList& pathList, NutshComunicator* corePath) {

    m_pathList = pathList;
    core = corePath;
    connect(this, SIGNAL(finished()), this, SLOT(quit()));
}

void NutshIndexer::run() {

    for(int i = 0; i<m_pathList.count();i++) {

        threadList.append(new Indexer(m_pathList.value(i)));
    }

    for(int i = 0;i<threadList.count();i++) {

        connect(threadList.value(i), SIGNAL(loopEnded()), core->metadatainterface(), SLOT(reset()));
        threadList.value(i)->start();
    }

    this->exec();
}
