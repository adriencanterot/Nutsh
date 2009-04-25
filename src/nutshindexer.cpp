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
void NutshIndexer::indexer(QString chemin) {
    int i = 0;
    iterator = new QDirIterator(chemin, *filtre, QDir::NoFilter, QDirIterator::Subdirectories);
    while(iterator->hasNext()) {
        i++;
        metaDataList.append(NutshMetaData(iterator->next()));
        qDebug() << i;
    }
    qDebug() << i;


}
QList<NutshMetaData> NutshIndexer::sortie() {
    return metaDataList;
}
