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
    informations.phrase = QString("Recherche de morceaux en cours...");
    emit updateBar(informations);

    iterator = new QDirIterator(chemin, filtre, QDir::NoFilter, QDirIterator::Subdirectories);

    while(iterator->hasNext()) {

        if(loopRunning == false) {
            return;

        }

        filePaths.append(iterator->next());
        total++;
        ProgressionInfo informations;
        informations.phrase = QString("%1 morceaux trouvés").arg(total);
        informations.style = searching;
        emit updateBar(informations);
    }

    if(loopRunning == false) {
        return;
    }

    if(filePaths.count() == 0) {

        emit fatalError("Aucun fichier trouvé dans le dossier spécifié");
    }

    QString noerror("0 medias importés"), alreadyexists("0 existent déjà"), error("aucune erreur");
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
                noerror = QString("%1 medias importés").arg(i-a-o);
            break;
            case SqlError:
                qDebug() << "SqlError";
                o = o+1;
                error = QString("%1 erreurs").arg(o);
            break;
            case CantDecodeTag:
                qDebug() << "CantDecodeTag";
                o = o+1;
                error = QString("%1 erreurs").arg(o);
            break;
            case AlreadyExists:
                qDebug() << "AlreadyExists";
                a = a+1;
                qDebug() << a;
                alreadyexists = QString("%1 doublons").arg(a);
            break;
        }
        ProgressionInfo informations;
        informations.progression = i+1;
        informations.maximum = total;
        informations.phrase = QString("%1, %2").arg(noerror).arg(alreadyexists);
        qDebug() << informations.phrase;
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
