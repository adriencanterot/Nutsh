#include "NutshSqlSaver.h"
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

    QSqlQuery requete;
    QString allLists;

    if(!requete.exec(QString("SELECT playlists FROM bibliotheque WHERE id = %1").arg(meta.getId()))) {

        qDebug() << requete.lastError() << requete.lastQuery();
    }

    while(requete.next()) {

        qDebug() << requete.value(0);
        allLists.append(QString("%1;%2;").arg(requete.value(0).toString()).arg(crypt(liste)));
    }


    if(!requete.exec(QString("UPDATE bibliotheque SET playlists = '%1' WHERE id = %2")
                 .arg(allLists)
                 .arg(meta.getId())
                 )) {
        qDebug() << requete.lastError() << requete.lastQuery();
    }
}
void NutshSqlSaver::inserer(QList<NutshMetaData> meta, const QString &table) {
    //insertion de multiple metadonnees
    for(unsigned int i = 0;i<meta.count();i++) {

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

    } else {

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

    requete.exec("create table bibliotheque ( id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, artiste text, album text, titre text, date text, genre text, description text, track text, chemin text, playlists text, duree text, enregistrement text, derniereLecture text, compteur text)");


    requete.exec("CREATE TABLE listeDeLecture (name text, ordre text)");


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

            for(int i = 0;i<NB_CHAMPS_DATABASE-1;i++) {

                cache.append(requete.value(i));
            }

            metaList.append(NutshMetaData(cache));
            cache.clear();
        }

        return metaList;

    } else {

        while(requete.next()) {

            if(requete.value(9).toString().contains(crypt(listName))) {

                for(int i = 0;i<NB_CHAMPS_DATABASE-1;i++) {

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
            qDebug() << requete.value(0).toString();
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


        if(meta.getDuree().isNull()) {
            meta.setDuree(QTime(1, 1, 1, 1));
        }

        query = QString("INSERT INTO bibliotheque (artiste, album, titre, date, genre, description, track, chemin, duree, enregistrement, derniereLecture, compteur) VALUES(\"%1\", \"%2\", \"%3\", \"\", \"%4\", \"%5\", \"\", \"%6\", \"%7\", \"%8\", \"\", \"\")")
                .arg(meta.getArtiste())
                .arg(meta.getAlbum())
                .arg(meta.getTitre())
                .arg(meta.getGenre())
                .arg(meta.getDescription())
                .arg(meta.getChemin())
                .arg(meta.getDuree().toString())
                .arg(meta.getDateEnregistrement().toString()
                     );

        //execution de la requete
        if(!metadatas.contains(meta.getArtiste()+meta.getAlbum()+meta.getTitre())) {// vérifie si la métadonnée n'existe pas déjà

            if(!requete.exec(query)) {
                qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
            }

        } else {

            qDebug() << "La métadonnée existe déjà";
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
       requete.exec(QString("UPDATE bibliotheque SET %2 = \"%3\" WHERE id = %1")
                 .arg(id)
                 .arg(key)
                 .arg(value)
                ))
    {
        qDebug() << requete.lastError() << requete.lastQuery();
    }
}
