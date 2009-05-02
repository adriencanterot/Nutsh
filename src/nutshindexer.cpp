#include "nutshindexer.h"


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
void NutshIndexer::indexer(QString chemin, QProgressDialog *progression, QString table) {
    int total = 0;
    QStringList filePaths;
    progression->setLabelText("scan en cours");
    iterator = new QDirIterator(chemin, *filtre, QDir::NoFilter, QDirIterator::Subdirectories);
    while(iterator->hasNext()) {
        qDebug() << "...";
        filePaths.append(iterator->next());
        total++;
        progression->setLabelText(QString("%1 fichiers trouves").arg(total));
    }
    progression->setMaximum(total);
    progression->setLabelText("scan en cours");
    for(int i = 0;i<filePaths.count();i++) {
        NutshSqlSaver::inserer(NutshMetaData(iterator->next()), table);
        progression->setValue(i);
        progression->setLabelText(QString("%1 / %2 importes").arg(i).arg(total));
    }



}
QList<NutshMetaData> NutshIndexer::sortie() {
    return metaDataList;
}
