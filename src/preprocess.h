#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <QDebug>

#define REQUETE(q) QSqlQuery requete; if(!requete.exec(q)) { qDebug() << requete.lastError() << " | Q = " << requete.lastQuery(); }
#define QUERY(q) if(!query.exec(q)) { qDebug() << query.lastError() << " | \n\nQ = " << query.lastQuery() << "\n\n"; }
#define NB_CHAMPS_DATABASE 13
#define FORMATS_SUPPORTES "*.mp3" << "*.ogg" << "*.aac" << "*.m4u" << "*.m4a" << "*.m4v";
#define D(bug) qDebug() << bug;

#endif // PREPROCESS_H
