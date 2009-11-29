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

void Indexer::import() {
        int total = 0;
    QStringList filePaths;
    ProgressionInfo informations;
    informations.style = searching;
    informations.phrase = QString(tr("Recherche de morceaux en cours..."));
    emit updateBar(informations);

    iterator = new QDirIterator(chemin, filtre, QDir::NoFilter, QDirIterator::Subdirectories);

    while(iterator->hasNext()) {

        if(loopRunning == false) {
            return;

        }

        filePaths.append(iterator->next());
        total++;
        ProgressionInfo informations;
        informations.phrase = QString(tr("%1 morceaux trouv�s")).arg(total);
        informations.style = searching;
        emit updateBar(informations);
    }

    if(loopRunning == false) {
        return;
    }

    if(filePaths.count() == 0) {

        emit fatalError(tr("Aucun fichier trouv� dans le dossier sp�cifi�"));
    }

    QString noerror(tr("0 medias import�s")), alreadyexists(tr("0 existent d�j�")), error(tr("aucune erreur"));
    int o = 0; //nombre d'erreurs
    int a = 0;
    for(int i = 0;i<filePaths.count();i++) {

        if(loopRunning == false || filePaths.count() == 0 || i == filePaths.count()) {

            return;
        }

        NutshMetaData data(filePaths.value(i));
        errorcode = saver->inserer(data);


        switch(errorcode) {

            case NoError:
                qDebug() << "NoError";
                noerror = QString(tr("%1 medias import�s")).arg(i-a-o);
            break;
            case SqlError:
                qDebug() << "SqlError";
                o = o+1;
                error = QString(tr("%1 erreurs")).arg(o);
            break;
            case CantDecodeTag:
                qDebug() << "CantDecodeTag";
                o = o+1;
                error = QString(tr("%1 erreurs")).arg(o);
            break;
            case AlreadyExists:
                qDebug() << "AlreadyExists";
                a = a+1;
                alreadyexists = QString(tr("%1 doublons")).arg(a);
            break;
        }
        ProgressionInfo informations;
        informations.progression = i+1;
        informations.maximum = total;
        informations.phrase = QString("%1, %2").arg(noerror).arg(alreadyexists);
        informations.style = progression;

        emit updateBar(informations);

    }
    emit loopEnded();
}

void Indexer::run() {

    import();    

}
void Indexer::forceQuit() {
    loopRunning = false;
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

        connect(threadList.value(i), SIGNAL(loopEnded()), core->metadatainterface(), SLOT(reload()));
        threadList.value(i)->start();
    }
}
