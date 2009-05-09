#include "nutshindexer.h"
#include "nutshcomunicator.h"

Indexer::Indexer(QString path, QString table) {

    chemin = path;
    m_table = table;
    filtre << FORMATS_SUPPORTES;
}

void Indexer::run() {

    int total = 0;
    QStringList filePaths;

    iterator = new QDirIterator(chemin, filtre, QDir::NoFilter, QDirIterator::Subdirectories);

    while(iterator->hasNext()) {

        filePaths.append(iterator->next());
        total++;
        emit updateBar(total, 0);
    }

    emit updateBar(0, 0);

    for(int i = 1;i<filePaths.count();i++) {

        NutshSqlSaver::inserer(NutshMetaData(filePaths.value(i)), m_table);
        qDebug() <<  filePaths.count();

        emit updateBar(i+1, total);
    }

    this->exec();
    connect(this, SIGNAL(finished()), this, SLOT(quit()));
}

NutshIndexer::NutshIndexer(NutshComunicator* corePath)
{

    core = corePath;

    //Construction de l'objet
    filtre = new QStringList();
    *filtre << FORMATS_SUPPORTES;
    listeFichier = new QStringList();
    //init filtre


}

bool NutshIndexer::trouver(QString chaine, QStringList *recherche) {

    bool ok;

    for(int i = 0;i<recherche->count();i++) {

        if(recherche->value(i) == chaine || chaine.contains("..", Qt::CaseInsensitive)) {

            ok = true;
	    break;

        } else {

            ok = false;
	}
    }

    return ok;
}

void NutshIndexer::indexer(QString chemin, QString table) {

    core->progressinterface()->swapToProgress();
    core->progressinterface()->setTopLabelText("Scan en cours");
    core->progressinterface()->setMaximum(0);

    Indexer* scan = new Indexer(chemin, table);
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
