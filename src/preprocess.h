#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <QDebug>

#define REQUETE(q) QSqlQuery requete; if(!requete.exec(q)) { qDebug() << requete.lastError() << " | Q = " << requete.lastQuery(); }
#define QUERY(q) if(!query.exec(q)) { qDebug() << query.lastError() << " | \n\nQ = " << query.lastQuery() << "\n\n"; }
#define NB_CHAMPS_DATABASE 14
#define FORMATS_SUPPORTES "*.mp3" << "*.m4a" << "*.wma" << "*.ogg";
#define D(bug) qDebug() << bug;
#define WIDTH_LEFT 200

enum ContentType {

    Dir, Playlist, Entire, Empty
};

enum ContentTypeForLabel {

    Label, LineEdit, clickableLabel
};

enum InterfaceName {

    PlayingInterface, MetaDataInterface, ProgressInterface
};

enum Action {

    Repeat, Random, Normal
};

#endif // PREPROCESS_H
