#include "sqlmanager.h"
#define d(bug) qDebug(bug)

SqlManager::SqlManager()
{
}
void SqlManager::inserer(Metadata meta,  const QString& listName) {

    if(meta.getId() < 0) {

        this->inserer(meta);
        meta.setId(metadatas.count());
    }

    QSqlQuery requete;

    if(!requete.exec(QString("INSERT INTO relationships VALUES( %2, %1)")
                 .arg(meta.getId())
                 .arg(crypt(listName))
                 )) {
        qDebug() << requete.lastError() << requete.lastQuery();
    }

    qDebug() << requete.lastQuery();
}

void SqlManager::inserer(QList<Metadata> meta, const QString& listName) {
    //insertion de multiple metadonnees
    for(unsigned int i = 0;i<static_cast<unsigned int>(meta.count());i++) {

        this->inserer(meta.value(i), listName);
    }
}

bool SqlManager::trouverDansTable(const Metadata &recherche) {
    //Rechercher une valeur dans un table :

    if(metadatas.contains(recherche.getChemin(), Qt::CaseSensitive)) {

        return true;

    } else {

        return false;
    }


}
void SqlManager::completeMetaData(Metadata &incomplete) {

    //enregistrement de la date avant l'enregistrement;
    incomplete.setSavingDate(QDateTime::currentDateTime());
}

void SqlManager::update(const Metadata &nouveau) {
    //Mise a jour d'une metadonnee
    QSqlQuery requete;

    if(!
       requete.exec(QString("UPDATE bibliotheque SET artiste = %2, album = %3, titre = %4 WHERE id = %1")
                    .arg(nouveau.getId())
                    .arg(nouveau.getArtiste())
                    .arg(nouveau.getAlbum())
                    .arg(nouveau.getTitre())
                    ))
    {
        qDebug() << requete.lastError() << requete.lastQuery();

    }
}
bool SqlManager::nouvelleListe(const QString &tableName) {
    //cree une nouvelle liste
    bool etat = true;

    QSqlQuery requete;

    if(!requete.exec("INSERT INTO listeDeLecture (name) VALUES (\""+SqlManager::sqlStringFormat(tableName)+"\")")){

        qDebug() << requete.lastError() << " | Q = " << requete.lastQuery();
        etat = false;
    }

    return etat;
}

bool SqlManager::connect() {
    //connexion à la base de donnée (ne doit être exécuté qu'une seule fois dans le code.

    QString MusicDir = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);

    //creation du dossier NutshConfig qui contient la base de donnee
    QDir verification(MusicDir);
    bool wizard = false;

    if(!verification.exists("NutshConfig")|| !QFile::exists(MusicDir+"/NutshConfig/NutshDB")) {

        verification.mkdir("NutshConfig");
        wizard = true;

    }

    QSqlDatabase NutshDB = QSqlDatabase::addDatabase("QSQLITE");

    NutshDB.setHostName("localhost");
    NutshDB.setDatabaseName(QDir::toNativeSeparators(MusicDir+"/NutshConfig/NutshDB"));
    NutshDB.setUserName("root");
    NutshDB.setPassword("");

    NutshDB.open();

    if(!NutshDB.open()) { // si il n'arrive pas à ouvrir la base de donnée

        qDebug() << "SqlManager : " << NutshDB.lastError();

    }


    //crée les tables obligatoires si elles n'existent pas

    QSqlQuery requete;

    requete.exec("create table bibliotheque ( id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, artiste text, album text, titre text, date date, genre text, description text, track integer, chemin text, playlists text, duree text, enregistrement datetime, derniereLecture datetime, compteur integer)");
    requete.exec("CREATE TABLE listeDeLecture (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, name text, ordre text)");
    requete.exec("CREATE TABLE path_list (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, path text)");
    requete.exec("CREATE TABLE relationships (playlist_id text, music_id INTEGER)");

    requete.exec("SELECT * FROM bibliotheque");

    while(requete.next()) { //création de la liste des verifications.

        metadatas.append(requete.value(1).toString()+requete.value(2).toString()+requete.value(3).toString());
    }


    if(wizard == true) { // affichage de l'assistant d'installation si le dossier n'était pas créé

        InstallationWizard Wizard;
        Wizard.exec();
    }

    return NutshDB.open();
}

QString SqlManager::normalStringFormat(const QString &param) {
    // converstion des chaines de caractères au format SQL vers normal
    QString operation = param;
    operation.replace("__replaced", " ");
    operation.replace("'_replaced", "\"");
    operation.replace("slash_replaced", "/");
    operation.replace("arobase_replaced", "@");
    operation.replace("diese_replaced", "#");
    operation.replace("dollar_replaced", "$");
    operation.replace("pourcent_replaced", "%");
    operation.replace("interrogation_replaced", "?");
    operation.replace("and_replaced", "&");
    operation.replace("etoile_replaced", "*");
    operation.replace("parentheseouv_replaced", "(");
    operation.replace("parentheseferm_replaced", ")");
    operation.replace("egal_replaced", "=");
    operation.replace("plus_replaced", "+");
    return operation;
}

QString SqlManager::sqlStringFormat(const QString &param) {
    // convertion des chaines de caractères au format normal vers SQL (pour insertion dans les tables)
    QString operation(param);
    operation.replace(" ", "__replaced");
    operation.replace("\"", "'_replaced");
    operation.replace("/", "slash_replaced");
    operation.replace("@", "arobase_replaced");
    operation.replace("#", "diese_replaced");
    operation.replace("$", "dollar_replaced");
    operation.replace("%", "pourcent_replaced");
    operation.replace("?", "interrogation_replaced");
    operation.replace("&", "and_replaced");
    operation.replace("*", "etoile_replaced");
    operation.replace("(", "parentheseouv_replaced");
    operation.replace(")", "parentheseferm_replaced");
    operation.replace("=", "egal_replaced");
    operation.replace("+", "plus_replaced");
    return operation;
}
QList<Metadata> SqlManager::getMetaDatas(const QString& listName) {

    //retourne la liste de métadonnée selon une requete

        QList<Metadata> metaList;
        QVariantList cache;

        QSqlQuery requete;
    if(listName != QString()){
        if(!requete.exec(QString("SELECT * FROM bibliotheque INNER JOIN relationships ON relationships.music_id = bibliotheque.id WHERE (relationships.playlist_id = %1)").arg(crypt(listName)))) {
            qDebug() << requete.lastError() << requete.lastQuery();
        }
    } else {
        if(!requete.exec(QString("SELECT * FROM bibliotheque"))) {
            qDebug() << requete.lastError() << requete.lastQuery();
        }
    }

   while(requete.next()) {
       for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {

           cache.append(requete.value(i));
       }
       metaList.append(Metadata(cache));
       cache.clear();
   }

   return metaList;
}

bool SqlManager::tableExists(const QString &tblName) {
    // vérifie si une table existe
    bool ok = false;
    QString q = "SELECT tbl_name FROM sqlite_master";
    REQUETE(q);

    while(requete.next()) {

        if(QString(requete.value(0).toString()).contains(tblName, Qt::CaseInsensitive)) { // si la table existe

            ok = true;
            break;
        }
    }
    return ok;
}

insertError SqlManager::inserer(Metadata meta) {

        //completion des metadata, pour la date.
    QSqlQuery requete;
    QString query;

    /* ---- complete une métadonnée si certains champs sont vide ----*/
        this->completeMetaData(meta);

        if(!meta.isValid()) {

            return CantDecodeTag;
        }

        if(meta.getArtiste().isEmpty()) {
            meta.setArtiste(QObject::tr("Sans artiste"));
        }

        if(meta.getAlbum().isEmpty()) {
            meta.setAlbum(QObject::tr("Sans album"));
        }

        if(meta.getTitre().isEmpty()) {
            meta.setTitre(QObject::tr("Sans titre"));
        }

        if(meta.getDate().isEmpty()) {
            meta.setDate(QObject::tr("Sans Date"));
        }

        if(meta.getGenre().isEmpty()) {
            meta.setGenre(QObject::tr("Sans genre"));
        }

        if(meta.getDescription().isEmpty()) {
            meta.setDescription(" ");
        }



        query = QString("INSERT INTO bibliotheque (artiste, album, titre, date, genre, description, track, chemin, duree, enregistrement, derniereLecture, compteur) VALUES(\"%1\", \"%2\", \"%3\", \"\", \"%4\", \"%5\", \"\", \"%6\", \"%7\", \"%8\", \"\", \"%9\")")
                .arg(addSlashes(meta.getArtiste()))
                .arg(addSlashes(meta.getAlbum()))
                .arg(addSlashes(meta.getTitre()))
                .arg(meta.getGenre())
                .arg(addSlashes(meta.getDescription()))
                .arg(addSlashes(meta.getChemin()))
                .arg(meta.getDuree())
                .arg(meta.getDateEnregistrement().toString())
                .arg(meta.getCompteur()
                     );

        //execution de la requete
        if(!metadatas.contains(QString(meta.getArtiste()+meta.getAlbum()+meta.getTitre())) || meta.isDefault()) {// vérifie si la métadonnée n'existe pas déjà

            if(!requete.exec(query)) {
                qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
                return SqlError;
            }
            metadatas.append(meta.getArtiste()+meta.getAlbum()+meta.getTitre());

        } else {
            return AlreadyExists;
        }

        return NoError;
   }

QVariantList SqlManager::modelMetadata(const Metadata& meta) {

    // retourne en forme de ligne de résultat SQL une métadonnée

    QSqlQuery requete;
    QVariantList model;

    requete.exec(QString("SELECT * FROM bibliotheque WHERE id = %1").arg(meta.getId()));

    while(requete.next()) {

        model.append(requete.next());
    }

    return model;
}

QString SqlManager::crypt(const QString& toCrypt) {

    //retourne le hash d'un QString

    QByteArray crypted;
    crypted.append(toCrypt);

    return QString("%1").arg(qHash(crypted));
}

void SqlManager::updateColumn(const QString& key, const QString& value, int id) {

    QSqlQuery requete;

    if(!
       requete.exec(QString("UPDATE bibliotheque SET %1 = \"%2\" WHERE id = %3")
                 .arg(key)
                 .arg(value)
                 .arg(id)
                ))
    {
        qDebug() << requete.lastError() << requete.lastQuery();
    }
}

void SqlManager::savePath(const QString& path) {

    QSqlQuery requete;
    QStringList pathList = this->getFolderList();

    if(!pathList.contains(path)) {

        if(!requete.exec(QString("INSERT INTO path_list (path) VALUES(\"%1\")").arg(path))) {

            qDebug() << "Impossible de sauvegarder le nom du fichier";
        }
    }
}

QStringList SqlManager::getFolderList() {

    QSqlQuery requete;
    QStringList pathList;

    if(!requete.exec("SELECT path FROM path_list")) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }

    while(requete.next()) {

        pathList.append(requete.value(0).toString());
    }
    return pathList;
}

QList<Metadata> SqlManager::getLastImport(int display) {

    QSqlQuery requete;
    QList<Metadata> liste;
    QVariantList cache;
    if(!requete.exec(QString("SELECT * FROM bibliotheque ORDER BY enregistrement LIMIT 0, %1").arg(display))) {
        qDebug() << requete.lastError()<< requete.lastQuery();
    }

    while(requete.next()) {
        for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {
            cache.append(requete.value(i));
        }
        liste.append(Metadata(cache));
        cache.clear();
    }

    return liste;
}

QList<Metadata> SqlManager::getMostReaden(int display) {

        QList<Metadata> metaList;
        QVariantList cache;

        REQUETE(QString("SELECT * FROM bibliotheque ORDER BY compteur  DESC LIMIT 0, %1").arg(display));

        while(requete.next()) {

            for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {

                cache.append(requete.value(i));
            }

            metaList.append(Metadata(cache));
            cache.clear();
        }

        return metaList;
}

QList<Metadata> SqlManager::getLastReaden(int display) {

    QSqlQuery requete;
    QList<Metadata> liste;
    QVariantList cache;
    if(!requete.exec(QString("SELECT * FROM bibliotheque ORDER BY derniereLecture DESC LIMIT 0, %1").arg(display))) {
        qDebug() << requete.lastError()<< requete.lastQuery();
    }

    while(requete.next()) {
        for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {
            cache.append(requete.value(i));
        }
        liste.append(Metadata(cache));
        cache.clear();
    }

    return liste;
}


void SqlManager::played(Metadata& meta) {

    meta.setCompteur(meta.getCompteur()+1);
    meta.setDerniereLecture(QDateTime::currentDateTime());
}

QStringList SqlManager::getPlaylists() {


    QStringList playlists;
    QSqlQuery requete;
    requete.exec("SELECT * FROM listeDeLecture");

    while(requete.next()) {
        playlists.append(SqlManager::normalStringFormat(requete.value(1).toString()));
    }

    return playlists;
}

void SqlManager::rename(const QString& nouveau, const QString& listName) {

    QSqlQuery requete;

    if(!requete.exec(QString("UPDATE relationships SET playlist_id = \"%1\" WHERE playlist_id = \"%2\"").arg(SqlManager::sqlStringFormat(crypt(nouveau))).arg(SqlManager::sqlStringFormat(crypt(listName))))) {
        qDebug() << requete.lastError() << requete.lastQuery();
    }

    if(!requete.exec(QString("UPDATE listeDeLecture SET name = \"%1\" WHERE name = \"%2\"").arg(SqlManager::sqlStringFormat(nouveau)).arg(SqlManager::sqlStringFormat(listName)))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }

    qDebug() << "here";

}

void SqlManager::remove(const QString &listName) {

    QSqlQuery requete;

    if(!requete.exec(QString("DELETE FROM listeDeLecture WHERE name = \"%1\"").arg(SqlManager::sqlStringFormat(listName)))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }
    if(!requete.exec(QString("DELETE FROM relationships WHERE playlist_id = %1").arg(crypt(listName)))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }

}

QString SqlManager::addSlashes(const QString &withslashes) {

    QString replaced = withslashes;
    replaced.replace('\"', "");
    replaced.replace("'", "");
    return replaced;
}
int SqlManager::getListId(const QString &listName) {
    QSqlQuery requete;
    int retour = 0;
    requete.exec(QString("SELECT id FROM listDeLecture WHERE name = \"%1\""));
    while(requete.next()) retour = requete.value(0).toInt();
    return retour;
}

void SqlManager::destroy(Metadata data) {
    QSqlQuery requete;
    if(!requete.exec(QString("DELETE FROM bibliotheque WHERE id = %1").arg(data.getId()))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }

    if(!requete.exec(QString("DELETE FROM relationships WHERE music_id = %1").arg(data.getId()))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }
}

void SqlManager::destroyFromList(Metadata data, const QString& listname) {

    QSqlQuery requete;

    if(!requete.exec(QString("DELETE FROM relationships WHERE music_id = %1 AND playlist_id = %2").arg(data.getId()).arg(crypt(listname)))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }
}
