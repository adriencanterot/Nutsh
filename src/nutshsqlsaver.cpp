#include "nutshsqlsaver.h"
#define d(bug) qDebug(bug)

NutshSqlSaver::NutshSqlSaver()
{
    QSqlQuery requete;

    requete.exec("SELECT * FROM bibliotheque");


    while(requete.next()) { //création de la liste des verifications.

        metadatas.append(requete.value(7).toString());
    }
}
void NutshSqlSaver::inserer(NutshMetaData meta, const QString &table) {
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

        if(meta.getCheminImage().isEmpty()) {
            meta.setCheminImage("Sans image");
        }

        if(meta.getDuree().isNull()) {
            meta.setDuree(QTime(1, 1, 1, 1));
        }

        query = QString("INSERT INTO `%1` (artiste, album, titre, date, genre, description, track, chemin, cheminImage, duree, enregistrement, derniereLecture, compteur) VALUES(\"%2\", \"%3\", \"%4\", \"\", \"%5\", \"%6\", \"\", \"%7\", \"%8\", \"%9\", \"%10\", \"\", \"\")")
                .arg(NutshSqlSaver::sqlStringFormat(table))
                .arg(meta.getArtiste())
                .arg(meta.getAlbum())
                .arg(meta.getTitre())
                .arg(meta.getGenre())
                .arg(meta.getDescription())
                .arg(meta.getChemin())
                .arg(meta.getCheminImage())
                .arg(meta.getDuree().toString())
                .arg(meta.getDateEnregistrement().toString());

        //execution de la requete
            if(!requete.exec(query)) {
                qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
            }
}
void NutshSqlSaver::inserer(QList<NutshMetaData> meta, const QString &table) {
    //insertion de multiple metadonnees

    QSqlQuery requete;
    QString query;
    for (int i = 0;i<meta.count();i++) {

         /* ---- complete une métadonnée si certains champs sont vide ----*/
        meta.value(i).setSavingDate(QDateTime::currentDateTime());

        if(meta.value(i).getArtiste().isEmpty()) {
            meta.value(i).setArtiste("Sans artiste");
        }

        if(meta.value(i).getAlbum().isEmpty()) {
            meta.value(i).setAlbum("Sans album");
        }

        if(meta.value(i).getTitre().isEmpty()) {
            meta.value(i).setTitre("Sans titre");
        }

        if(meta.value(i).getDate().isEmpty()) {
            meta.value(i).setDate("Sans Date");
        }

        if(meta.value(i).getGenre().isEmpty()) {
            meta.value(i).setGenre("Sans genre");
        }

        if(meta.value(i).getDescription().isEmpty()) {
            meta.value(i).setDescription(" ");
        }

        if(meta.value(i).getCheminImage().isEmpty()) {
            meta.value(i).setCheminImage("Sans image");
        }

        if(meta.value(i).getDuree().isNull()) {
            meta.value(i).setDuree(QTime(1, 1, 1, 1));
        }


        query = QString("INSERT INTO `%1` (artiste, album, titre, date, genre, description, track, chemin, cheminImage, duree, enregistrement, derniereLecture, compteur) VALUES(\"%2\", \"%3\", \"%4\", \"\", \"%5\", \"%6\", \"\", \"%7\", \"%8\", \"%9\", \"%10\", \"\", \"\")")
                .arg(NutshSqlSaver::sqlStringFormat(table))
                .arg(meta.value(i).getArtiste())
                .arg(meta.value(i).getAlbum())
                .arg(meta.value(i).getTitre())
                .arg(meta.value(i).getGenre())
                .arg(meta.value(i).getDescription())
                .arg(meta.value(i).getChemin())
                .arg(meta.value(i).getCheminImage())
                .arg(meta.value(i).getDuree().toString())
                .arg(meta.value(i).getDateEnregistrement().toString());

        //execution de la requete

       if(!requete.exec(query)) {
           qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
        }
   }
}

bool NutshSqlSaver::trouverDansTable(const QString &query, const NutshMetaData &recherche) {
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

void NutshSqlSaver::update(const NutshMetaData &nouveau, const NutshMetaData &ancien,  const QString &table) {
    //Mise a jour d'une metadonnee
    QSqlQuery requete;
    requete.exec("UPDATE "+table+" SET morceau = \""+nouveau.getTitre()+"\", artiste = \""+nouveau.getArtiste()+"\", album = \""+nouveau.getAlbum()+"\", dateCreation = \""+nouveau.getDate()+"\", genre = \""+nouveau.getGenre()+"\", description = \""+nouveau.getDescription()+"\", track = \""+nouveau.getTrack()+"\", chemin = \""+nouveau.getChemin()+"\", cheminImage = \""+nouveau.getCheminImage()+"\" WHERE artiste = \""+ancien.getArtiste()+"\", morceau = \""+ancien.getTitre()+"\" ");

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

    requete.exec("create table bibliotheque ( id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, artiste text, album text, titre text, date text, genre text, description text, track text, chemin text, cheminImage text, duree text, enregistrement text, derniereLecture text, compteur text)");


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
QList<NutshMetaData> NutshSqlSaver::getMetaDatas(const QString &query) {

    //retourne la liste de métadonnée selon une requete

    QList<NutshMetaData> metaList;
    REQUETE(query);

    QVariantList cache;

    while(requete.next()) {

        for(int i = 0;i<NB_CHAMPS_DATABASE-1;i++) {

            cache.append(requete.value(i));
        }

        metaList.append(NutshMetaData(cache));
        cache.clear();
    }
    return metaList;
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
