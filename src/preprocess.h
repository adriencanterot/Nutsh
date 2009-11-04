#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <QDebug>

#define REQUETE(q) QSqlQuery requete; if(!requete.exec(q)) { qDebug() << requete.lastError() << " | Q = " << requete.lastQuery(); }
#define QUERY(q) if(!query.exec(q)) { qDebug() << query.lastError() << " | \n\nQ = " << query.lastQuery() << "\n\n"; }
#define NB_CHAMPS_DATABASE 14
#ifdef Q_WS_WIN
#define FORMATS_SUPPORTES "*.mp3" << "*.wma" << "*.ogg";
#else
#define FORMATS_SUPPORTES "*.mp3" << "*.m4a" << "*.wma" << "*.ogg";
#endif
#define D(bug) qDebug() << bug;
#define WIDTH_LEFT 200
#define CHAR_NUM_LIST 52

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

enum progressionStyle {
    progression, searching
};

enum insertError {
    AlreadyExists, CantDecodeTag, SqlError, NoError
};

struct ProgressionInfo {
    int progression;
    int maximum;
    QString phrase;
    progressionStyle style;
};

#endif // PREPROCESS_H
