#include "nutshsqlsaver.h"
#define d(bug) qDebug(bug)

NutshSqlSaver::NutshSqlSaver()
{
    /*//construction de l'objet
    MusicDir = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);
    //creation du dossier NutshConfig qui contient la base de donnee
    qDebug() << "MusicDir = " << MusicDir;
    verification = new QDir(MusicDir);
    if(!verification->exists("NutshConfig")) {
        verification->mkdir("NutshConfig");
    }
    if(!this->connect()) {
        qDebug() << "NutshSqlSaver : connexion a la database echouee";
    }
    else {
        qDebug() << "NutshSqlSaver : connexion a la database reussie";
    }
    qDebug()<<"NutshSqlSaver : initialized";*/
}
void NutshSqlSaver::inserer(NutshMetaData meta, QString table) {
    //completion des metadata, pour la date.
    QSqlQuery requete;
    QString query;
        NutshSqlSaver::completeMetaData(meta);

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


        query = "INSERT INTO "+table+" VALUES(\""+meta.getArtiste()+"\", \""+meta.getAlbum()+"\", \""+meta.getTitre()+"\", \"nope\", \""+meta.getGenre()+"\", \""+meta.getDescription()+"\", \"0\", \""+meta.getChemin()+"\", \""+meta.getCheminImage()+"\", \""+meta.getDuree().toString()+"\", \""+meta.getDateEnregistrement().toString()+"\", \"no\", \"no\")";

        //execution de la requete
        if(!NutshSqlSaver::trouverDansTable("SELECT * FROM "+table, meta)) {

            if(!requete.exec(query)) {
                qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
            }

    }
}
void NutshSqlSaver::inserer(QList<NutshMetaData> meta, QString table) {
    //insertion de multiple metadonnees

    qDebug() << meta.count();
    QSqlQuery requete;
    QString query;
    for (int i = 0;i<meta.count();i++) {
        NutshSqlSaver::completeMetaData(meta.value(i));

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


        query = "INSERT INTO "+table+" VALUES(\""+meta.value(i).getArtiste()+"\", \""+meta.value(i).getAlbum()+"\", \""+meta.value(i).getTitre()+"\", \"nope\", \""+meta.value(i).getGenre()+"\", \""+meta.value(i).getDescription()+"\", \"0\", \""+meta.value(i).getChemin()+"\", \""+meta.value(i).getCheminImage()+"\", \""+meta.value(i).getDuree().toString()+"\", \""+meta.value(i).getDateEnregistrement().toString()+"\", \"no\", \"no\")";

        //execution de la requete
        if(!NutshSqlSaver::trouverDansTable("SELECT * FROM "+table, meta.value(i))) {

            if(!requete.exec(query)) {
                qDebug() << requete.lastError() << "  \nQ= " << requete.lastQuery() << " ou alors la metadonnee existe deja dans la table";
            }
        }
        qDebug() << meta.value(i).getTitre() << "insere";
    }
}

bool NutshSqlSaver::trouverDansTable(QString query, NutshMetaData recherche) {
    //Rechercher une valeur dans un table :
    QSqlQuery requete;
    bool ok = false;
    requete.exec(query);
    while(requete.next()) {

            if(requete.value(0/*1er resultat du select*/).toString() == recherche.getArtiste() && requete.value(1/*2e resultat*/) == recherche.getAlbum() && requete.value(2)/*3e resultat*/ == recherche.getTitre()) {
                ok = true;
                break;
            }
            else {
                ok = false;
            }
    }
    return ok;
}
void NutshSqlSaver::completeMetaData(NutshMetaData incomplete) {
    //enregistrement de la date avant l'enregistrement;
    incomplete.setSavingDate(QDateTime::currentDateTime());
}
QString NutshSqlSaver::stringListToString(QStringList liste) {
    QString chaineRetour;
    for (int i = 0;i<liste.count();i++) {
        chaineRetour.append(liste.value(i));
    }
    return chaineRetour;
}
void NutshSqlSaver::update(NutshMetaData nouveau, NutshMetaData ancien,  QString table) {
    //Mise a jour d'une metadonnee
    QSqlQuery requete;
    requete.exec("UPDATE "+table+" SET morceau = \""+nouveau.getTitre()+"\", artiste = \""+nouveau.getArtiste()+"\", album = \""+nouveau.getAlbum()+"\", dateCreation = \""+nouveau.getDate()+"\", genre = \""+nouveau.getGenre()+"\", description = \""+nouveau.getDescription()+"\", track = \""+nouveau.getTrack()+"\", chemin = \""+nouveau.getChemin()+"\", cheminImage = \""+nouveau.getCheminImage()+"\" WHERE artiste = \""+ancien.getArtiste()+"\", morceau = \""+ancien.getTitre()+"\" ");

}
bool NutshSqlSaver::nouvelleListe(QString tableName) {
    bool etat = true;
    QSqlQuery requete;
    requete.exec("CREATE TABLE listeDeLecture (name text, ordre text)");
    if(!requete.exec("create table "+NutshSqlSaver::sqlStringFormat(tableName)+" ( artiste text, album text, titre text, date text, genre text, description text, track text, chemin text, cheminImage text, duree text, enregistrement text, derniereLecture text, compteur text)")){
        qDebug() << requete.lastError() << " | Q = " << requete.lastQuery();
        etat = false;
    }
    if(!requete.exec("INSERT INTO listeDeLecture VALUES (\""+tableName+"\", \"\")")){
        qDebug() << requete.lastError() << " | Q = " << requete.lastQuery();
        etat = false;
    }
    return etat;
}
bool NutshSqlSaver::connect() {
    QString MusicDir = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);

    //creation du dossier NutshConfig qui contient la base de donnee
    QDir verification(MusicDir);

    if(!verification.exists("NutshConfig")) {

        verification.mkdir("NutshConfig");
    }

    QSqlDatabase NutshDB = QSqlDatabase::addDatabase("QSQLITE");
    NutshDB.setHostName("localhost");
    NutshDB.setDatabaseName(QDir::toNativeSeparators(MusicDir+"/NutshConfig/NutshDB"));
    NutshDB.setUserName("root");
    NutshDB.setPassword("");
    if(!NutshDB.open()) {
        qDebug() << "NutshSqlSaver : " << NutshDB.lastError();
    }
    QSqlQuery requete;
    requete.exec("create table bibliotheque ( artiste text, album text, titre text, date text, genre text, description text, track text, chemin text, cheminImage text, duree text, enregistrement text, derniereLecture text, compteur text)");
    requete.exec("CREATE TABLE listeDeLecture (name text, ordre text)");
    return NutshDB.open();
}

QString NutshSqlSaver::normalStringFormat(QString param) {
    QString operation = param;
    operation.replace("__replaced", " ");
    operation.replace("'_replaced", "\"");
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
QString NutshSqlSaver::sqlStringFormat(QString param) {
    QString operation(param);
    operation.replace(" ", "__replaced");
    operation.replace("\"", "'_replaced");
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
QList<NutshMetaData> NutshSqlSaver::getMetaDatas(QString query) {
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
bool NutshSqlSaver::tableExists(QString tblName) {
    bool ok = false;
    QString q = "SELECT tbl_name FROM sqlite_master";
    REQUETE(q);
    while(requete.next()) {
        if(QString(requete.value(0).toString()).contains(tblName, Qt::CaseInsensitive)) {
            ok = true;
            qDebug() << requete.value(0).toString();
            break;
        }
    }
    return ok;
}
