#include "nutshindexer.h"
#include "nutshcomunicator.h"

Indexer::Indexer(const QString& path, const QString &table) {

    chemin = path;
    m_table = table;
    filtre << FORMATS_SUPPORTES;
    this->setTerminationEnabled(true);
    loopRunning = true;
    saver = new NutshSqlSaver;
}

void Indexer::run() {

    int total = 0;
    QStringList filePaths;
    emit updateBar(0, 0) ;

    iterator = new QDirIterator(chemin, filtre, QDir::NoFilter, QDirIterator::Subdirectories);

    while(iterator->hasNext()) {

        filePaths.append(iterator->next());
        total++;

        emit updateBar(total, 0);

        if(loopRunning == false) {

            break;
        }
    }

    emit updateBar(0, 0);

    for(int i = 1;i<filePaths.count();i++) {

        saver->inserer(NutshMetaData(filePaths.value(i)), m_table);
        qDebug() <<  filePaths.count();


        emit updateBar(i+1, total);

        if(loopRunning == false) {

            break;
        }
    }

    connect(this, SIGNAL(finished()), this, SLOT(quit()));
    this->exec();
}
void Indexer::forceQuit() {

    loopRunning = false;
    this->terminate();
}

NutshIndexer::NutshIndexer(NutshComunicator* corePath)
{

    core = corePath;

    //Construction de l'objet
    filtre = new QStringList();
    *filtre << FORMATS_SUPPORTES;
    listeFichier = new QStringList();
    core->progressinterface()->stopAction(this, SLOT(cancelAction()));
    //init filtre


}

void NutshIndexer::indexer(const QString &chemin, const QString &table) {

    core->progressinterface()->swapToProgress();
    core->progressinterface()->setTopLabelText("Scan en cours");
    core->progressinterface()->setMaximum(0);

    scan = new Indexer(chemin, table);
    QObject::connect(scan, SIGNAL(updateBar(int,int)), this, SLOT(updateBar(int,int)));
    scan->start();

}

QList<NutshMetaData> NutshIndexer::sortie() {
    return metaDataList;
}

void NutshIndexer::updateBar(int current, int total) {

    if(total == 0 && current != 0) {

        core->progressinterface()->setBottomLabelText(QString("%1 fichiers trouves").arg(current));
        core->progressinterface()->setValue(current);
        core->progressinterface()->setMaximum(0);

    } else if(total == 0 && current == 0) {

        core->progressinterface()->setTopLabelText("Ajout dans la bibliotheque");
        core->progressinterface()->setValue(0);

    } else {

        core->progressinterface()->setMaximum(total);
        core->progressinterface()->setValue(current);
        core->progressinterface()->setBottomLabelText(QString("%1 / %2 morceaux ajoutes").arg(current).arg(total));
    }
}
void NutshIndexer::cancelAction() {

    scan->forceQuit();
    core->driveinterface()->swapToDrives();
}
