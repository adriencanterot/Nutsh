#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <QDebug>
#include <QFile>

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
#define CHAR_NUM_LIST 50
#define RUNNING_WORDS QString("the ");
#define MAX_ELEMENT_SHOWN 500
#ifdef Q_OS_WIN
#define FMOD
#else
#define PHONON
#endif

enum ContentType {

    Dir, Playlist, Entire, Playbox, Empty
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
enum searchResultType {
    Song = 0, Artist =1, Album = 2, Nothing = 3
};
enum State{
    Playing, Paused, Stopped
};

enum Provenance {
    fromPlaybox, fromPlaylist, fromWeb, fromNowhere
};


#endif // PREPROCESS_H
