#include "nutshsqlsaver.h"
#define d(bug) qDebug(bug)

NutshSqlSaver::NutshSqlSaver()
{
    QSqlQuery requete;

    requete.exec("SELECT * FROM bibliotheque");


    while(requete.next()) { //création de la liste des verifications.

        metadatas.append(requete.value(1).toString()+requete.value(2).toString()+requete.value(3).toString());
    }
}
void NutshSqlSaver::inserer(NutshMetaData meta, const QString &liste) {

    if(meta.getId() < 0) {

        this->inserer(meta);
        meta.setId(metadatas.count());
    }

    QSqlQuery requete;
    QString allLists;

    if(!requete.exec(QString("SELECT playlists FROM bibliotheque WHERE id = %1").arg(meta.getId()))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }

    while(requete.next()) {

        allLists.append(QString("%1;%2;").arg(requete.value(0).toString()).arg(crypt(liste)));
    }


    if(!requete.exec(QString("UPDATE bibliotheque SET playlists = '%1' WHERE id = %2")
                 .arg(allLists)
                 .arg(meta.getId())
                 )) {
        qDebug() << requete.lastError() << requete.lastQuery();
    }

    qDebug() << requete.lastQuery();
}

void NutshSqlSaver::inserer(QList<NutshMetaData> meta, const QString &table) {
    //insertion de multiple metadonnees
    for(unsigned int i = 0;i<static_cast<unsigned int>(meta.count());i++) {

        this->inserer(meta.value(i), table);
    }
}

bool NutshSqlSaver::trouverDansTable(const NutshMetaData &recherche) {
    //Rechercher une valeur dans un table :

    if(metadatas.contains(recherche.getChemin(), Qt::CaseSensitive)) {

        return true;

    } else {

        return false;
    }


}
void NutshSqlSaver::completeMetaData(NutshMetaData &incomplete) {

    //enregistrement de la date avant l'enregistrement;
    incomplete.setSavingDate(QDateTime::currentDateTime());
}

void NutshSqlSaver::update(const NutshMetaData &nouveau,  const QString &table) {
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
bool NutshSqlSaver::nouvelleListe(const QString &tableName) {
    //cree une nouvelle liste
    bool etat = true;

    QSqlQuery requete;

    if(!requete.exec("INSERT INTO listeDeLecture VALUES (\""+NutshSqlSaver::sqlStringFormat(tableName)+"\", \"\")")){

        qDebug() << requete.lastError() << " | Q = " << requete.lastQuery();
        etat = false;
    }

    return etat;
}

bool NutshSqlSaver::connect() {
    //connexion à la base de donnée (ne doit être exécuté qu'une seule fois dans le code.

    QString MusicDir = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);

    //creation du dossier NutshConfig qui contient la base de donnee
    QDir verification(MusicDir);
    bool wizard = false;

    if(!verification.exists("NutshConfig")) {

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

        qDebug() << "NutshSqlSaver : " << NutshDB.lastError();

    }


    //crée les tables obligatoires si elles n'existent pas

    QSqlQuery requete;

    requete.exec("create table bibliotheque ( id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, artiste text, album text, titre text, date date, genre text, description text, track integer, chemin text, playlists text, duree text, enregistrement date, derniereLecture date, compteur integer)");


    requete.exec("CREATE TABLE listeDeLecture (name text, ordre text)");
    requete.exec("CREATE TABLE path_list (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, path text)");


    if(wizard == true) { // affichage de l'assistant d'installation si le dossier n'était pas créé

        NutshInstallationWizard Wizard;
        Wizard.exec();
    }

    return NutshDB.open();
}

QString NutshSqlSaver::normalStringFormat(const QString &param) {
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

QString NutshSqlSaver::sqlStringFormat(const QString &param) {
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
QList<NutshMetaData> NutshSqlSaver::getMetaDatas(const QString &listName) {

    //retourne la liste de métadonnée selon une requete

        QList<NutshMetaData> metaList;
        QVariantList cache;

        REQUETE("SELECT * FROM bibliotheque");

    if(listName == "bibliotheque"){
        while(requete.next()) {

            for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {

                cache.append(requete.value(i));
            }
            metaList.append(NutshMetaData(cache));
            cache.clear();
        }

        return metaList;

    } else {

        while(requete.next()) {

            if(requete.value(9).toString().contains(crypt(NutshSqlSaver::normalStringFormat(listName)))) {

                for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {

                        cache.append(requete.value(i));
                }

                metaList.append(NutshMetaData(cache));
                cache.clear();
            }
        }

        return metaList;
    }


}

bool NutshSqlSaver::tableExists(const QString &tblName) {
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

void NutshSqlSaver::inserer(NutshMetaData meta) {

        //completion des metadata, pour la date.
    QSqlQuery requete;
    QString query;

    /* ---- complete une métadonnée si certains champs sont vide ----*/
        this->completeMetaData(meta);

        if(!meta.isValid()) {

            return;
        }

        if(meta.getArtiste().isEmpty()) {
            meta.setArtiste("Sans artiste");
        }

        if(meta.getAlbum().isEmpty()) {
            meta.setAlbum("Sans album");
        }

        if(meta.getTitre().isEmpty()) {
            meta.setTitre("Sans titre");
        }

        if(meta.getDate().isEmpty()) {
            meta.setDate("Sans Date");
        }

        if(meta.getGenre().isEmpty()) {
            meta.setGenre("Sans genre");
        }

        if(meta.getDescription().isEmpty()) {
            meta.setDescription(" ");
        }



        query = QString("INSERT INTO bibliotheque (artiste, album, titre, date, genre, description, track, chemin, duree, enregistrement, derniereLecture, compteur) VALUES(\"%1\", \"%2\", \"%3\", \"\", \"%4\", \"%5\", \"\", \"%6\", \"%7\", \"%8\", \"\", \"%9\")")
                .arg(meta.getArtiste())
                .arg(meta.getAlbum())
                .arg(meta.getTitre())
                .arg(meta.getGenre())
                .arg(meta.getDescription())
                .arg(meta.getChemin())
                .arg(meta.getDuree())
                .arg(meta.getDateEnregistrement().toString())
                .arg(meta.getCompteur()
                     );

        //execution de la requete
        if(!metadatas.contains(meta.getArtiste()+meta.getAlbum()+meta.getTitre())) {// vérifie si la métadonnée n'existe pas déjà

            if(!requete.exec(query)) {
                qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
            }

        } else {

            metadatas.append(meta.getArtiste()+meta.getAlbum()+meta.getTitre());
        }
   }

QVariantList NutshSqlSaver::modelNutshMetaData(const NutshMetaData& meta) {

    // retourne en forme de ligne de résultat SQL une métadonnée

    QSqlQuery requete;
    QVariantList model;

    requete.exec(QString("SELECT * FROM bibliotheque WHERE id = %1").arg(meta.getId()));

    while(requete.next()) {

        model.append(requete.next());
    }

    return model;
}

QString NutshSqlSaver::crypt(const QString& toCrypt) {

    //retourne le hash d'un QString

    QByteArray crypted;
    crypted.append(toCrypt);

    return QString("%1").arg(qHash(crypted));
}

void NutshSqlSaver::updateColumn(const QString& key, const QString& value, int id) {

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

void NutshSqlSaver::savePath(const QString& path) {

    QSqlQuery requete;
    QStringList pathList = this->getFolderList();

    if(!pathList.contains(path)) {

        if(!requete.exec(QString("INSERT INTO path_list (path) VALUES(\"%1\")").arg(path))) {

            qDebug() << "Impossible de sauvegarder le nom du fichier";
        }
    }
}

QStringList NutshSqlSaver::getFolderList() {

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

QList<NutshMetaData> NutshSqlSaver::getLastImport(int display) {

    QSqlQuery requete;
    QList<NutshMetaData> liste;
    QVariantList cache;
    if(!requete.exec(QString("SELECT * FROM bibliotheque ORDER BY enregistrement LIMIT 0, %1").arg(display))) {
        qDebug() << requete.lastError()<< requete.lastQuery();
    }

    while(requete.next()) {
        for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {
            cache.append(requete.value(i));
        }
        liste.append(NutshMetaData(cache));
        cache.clear();
    }

    return liste;
}

QList<NutshMetaData> NutshSqlSaver::getMostReaden(int display) {

        QList<NutshMetaData> metaList;
        QVariantList cache;

        REQUETE(QString("SELECT * FROM bibliotheque ORDER BY compteur  DESC LIMIT 0, %1").arg(display));

        while(requete.next()) {

            for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {

                cache.append(requete.value(i));
            }

            metaList.append(NutshMetaData(cache));
            cache.clear();
        }

        return metaList;
}

QList<NutshMetaData> NutshSqlSaver::getLastReaden(int display) {

    QSqlQuery requete;
    QList<NutshMetaData> liste;
    QVariantList cache;
    if(!requete.exec(QString("SELECT * FROM bibliotheque ORDER BY derniereLecture DESC LIMIT 0, %1").arg(display))) {
        qDebug() << requete.lastError()<< requete.lastQuery();
    }

    while(requete.next()) {
        for(int i = 0;i<NB_CHAMPS_DATABASE;i++) {
            cache.append(requete.value(i));
        }
        liste.append(NutshMetaData(cache));
        cache.clear();
    }

    return liste;
}


void NutshSqlSaver::played(NutshMetaData& meta) {

    meta.setCompteur(meta.getCompteur()+1);
    meta.setDerniereLecture(QDateTime::currentDateTime());
}
