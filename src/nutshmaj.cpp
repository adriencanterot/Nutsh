#include "nutshmaj.h"
#include "nutshcomunicator.h"

NutshMaJ::NutshMaJ(NutshComunicator* corePath)
{
    core = corePath;
    m_cancel = new QPushButton("Arreter");
    this->telecharger();

}

void NutshMaJ::telecharger() {

#ifdef Q_WS_MAC

    QUrl url("http://telecharger.nutsh.com/last/miseajour/Nutsh");

#endif

#ifdef Q_WS_WIN

    QUrl url("http://telecharger.nutsh.com/last/miseajour/Nutsh.exe");

#endif
#ifdef Q_WS_X11

    QUrl url("http://telecharger.nutsh.com/last/miseajour/Nutsh.exe");

#endif

    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();

    if (QFile::exists(PLATFORM_PATH)) {

        QFile::remove(PLATFORM_PATH);    }

    file = new QFile(PLATFORM_PATH);

    if (!file->open(QIODevice::WriteOnly)) {

        QMessageBox::information(this, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }

    m_download = new QHttp;
    connect(m_download, SIGNAL(done(bool)), this, SLOT(quitAndStartNutsh()));
    QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
    m_download->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());

    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    core->progressinterface()->swapToProgress();
    m_download->get(path, file);

    connect(m_download, SIGNAL(dataReadProgress(int,int)), this, SLOT(updProgress(int,int)));
    connect(m_download, SIGNAL(done(bool)), this, SLOT(quitAndStartNutsh()));

}

void NutshMaJ::updProgress(int current, int done) {

    core->progressinterface()->setMaximum(done);
    core->progressinterface()->setValue(current);
}

void NutshMaJ::quitAndStartNutsh() {

#ifdef Q_WS_MAC

    // lit d'abord la methode startNutsh()

    file->setPermissions(QFile::ExeOther|QFile::ExeUser);//met des permissions au fichier (encore eh oui, c'est pas tres propre
    file->close(); // ferme le fichier, sinon ca merde.

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));// quand le logiciel est sur le point de se quitter, execute la methode startNutsh qui va lancer la nouvelle instance
    QTimer::singleShot(2000, this, SLOT(startNutsh())); // Attends 2 sec, quand je le faisais instantanement, ca marchais pas :/
    QApplication::exit(0);  // quitte le programme.

    /* dans les 2 methodes que j'utilise pour lancer la nouvelle instance (le singleShot, l'application qui se quitte)
       je ne sais pas du tout quelle est celle qui marche, en effet, si les 2 devaient marcher, 2 instances seraient
       lancees, et ce n'est pas le cas, et tout cas, j'espere avoir ete assez clair, je suis desole mais je ne connais
       pas grand chose a linux, je m'en suis servi quelque temps pour du developpement Web, mais jamais pour du
       developpement en local :/ merci :) */

#endif

#ifdef Q_WS_WIN

    this->close();
    file->close();
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));
    QTimer::singleShot(100, qApp, SLOT(quit()));
    QApplication::quit();
#endif

#ifdef Q_WS_X11
    //ecrit ici le code pour linux d'apres les instructions pour la methode Mac
#endif
}

void NutshMaJ::startNutsh() {

#ifdef Q_WS_WIN

    QProcess nutsh;
    nutsh.startDetached(QDir::toNativeSeparators("updateScript.exe"));
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));

#endif

#ifdef Q_WS_MAC

   //je vais commenter cette partie la parce que je pense que c'est celle qui ressemble le plus a linux.


    QFile::setPermissions(PLATFORM_PATH, QFile::ExeUser|QFile::ExeGroup|QFile::ExeOther|QFile::ExeOwner);//met toutes les permissions pour le fichier pour qu'il puisse lancer le fichier telecharge
    QProcess::startDetached(PLATFORM_PATH);//lance le nouveau Nutsh, (ca ne pose pas de probleme a mac, d'ecraser un executable deja lance, ca evite le probleme du launcher, mais je sais pas si linux a besoin d'un launcher (comme pour windows par exemple)
    system(QString("chmod 777 "+PLATFORM_PATH).toAscii());//remet le chmod, je sais pas exactement quelle commande marche :|
    QApplication::exit(); // quitte cette instance avec l'autre programme lance.
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));

    //comme tu peux le constater, cette partie du code est carement bordelique, c'est vrai que j'ai mis du temps a la faire marcher, et quand ca a marcher, je me suis dit : on touche a rien ^^

#endif

#ifdef Q_WS_X11
    //ecrit ici le code pour linux d'apres les instructions pour la methode Mac
#endif
}
