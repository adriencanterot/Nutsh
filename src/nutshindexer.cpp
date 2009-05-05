#include "nutshindexer.h"

Indexer::Indexer(QProgressDialog* dialogue, QString path, QString table) {
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

NutshIndexer::NutshIndexer()
{
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
	}
	else {
	    ok = false;
	}
    }
    return ok;
}
void NutshIndexer::indexer(QString chemin, QProgressDialog *progress, QString table) {
    progression = progress;
    progression->setLabelText("scan en cours");
    progression->setMaximum(1);
    progression->setMinimum(0);

    Indexer* scan = new Indexer(progression, chemin, table);
    QObject::connect(scan, SIGNAL(updateBar(int,int)), this, SLOT(updateBar(int,int)));
    scan->start();

}
QList<NutshMetaData> NutshIndexer::sortie() {
    return metaDataList;
}
void NutshIndexer::updateBar(int current, int total) {
    if(total == 0 && current != 0) {
        progression->setLabelText(QString("%1 fichiers trouves").arg(current));
        progression->setValue(current);
        progression->setMaximum(0);
    }
    else if(total == 0 && current == 0) {
        progression->setLabelText("Ajout dans la bibliotheque");
        progression->setValue(0);
    }
    else {

        progression->setMaximum(total);
        progression->setValue(current);
        progression->setLabelText(QString("%1 / %2 morceaux ajoutes").arg(current).arg(total));
    }
}
