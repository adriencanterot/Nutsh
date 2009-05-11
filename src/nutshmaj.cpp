#include "nutshmaj.h"
#include "nutshcomunicator.h"

NutshMaJ::NutshMaJ(NutshComunicator* corePath)
{
    core = corePath;
    m_cancel = new QPushButton("Arreter");
    this->telecharger();

    core->progressinterface()->stopAction(this, SLOT(quitAndStartNutsh()));
}

void NutshMaJ::telecharger() {

#ifdef Q_WS_MAC

    QUrl url("http://telecharger.nutsh.com/last/miseajour/Nutsh");

#endif

#ifdef Q_WS_WIN

    QUrl url("http://telecharger.nutsh.com/last/miseajour/Nutsh.exe");

#endif

    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();

    if (QFile::exists(PLATFORM_PATH)) {

        QFile::remove(PLATFORM_PATH);
        qDebug() << "file removed";
    }

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

    core->progressinterface()->setTopLabelText("Telechargement en cours");
    core->progressinterface()->setBottomLabelText(QString("%1 / %2").arg(current/SIZE_LABEL).arg(done/SIZE_LABEL));
    core->progressinterface()->setMaximum(done);
    core->progressinterface()->setValue(current);
}

void NutshMaJ::quitAndStartNutsh() {

#ifdef Q_WS_MAC

    file->setPermissions(QFile::ExeOther|QFile::ExeUser);
    file->close();
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));
    QTimer::singleShot(2000, this, SLOT(startNutsh()));
    QApplication::exit(0);

#endif

#ifdef Q_WS_WIN

    this->close();
    file->close();
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));
    QTimer::singleShot(100, qApp, SLOT(quit()));
    QApplication::quit();
#endif
}

void NutshMaJ::startNutsh() {

#ifdef Q_WS_WIN

    QProcess nutsh;
    nutsh.startDetached(QDir::toNativeSeparators("updateScript.exe"));
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));

#endif

#ifdef Q_WS_MAC

    QFile::setPermissions(PLATFORM_PATH, QFile::ExeUser|QFile::ExeGroup|QFile::ExeOther|QFile::ExeOwner);
    QProcess nutsh;
    QProcess::startDetached(PLATFORM_PATH);
    system(QString("chmod 777 "+PLATFORM_PATH).toAscii());
    qDebug() << QDir::current().path();
    QApplication::exit();
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(startNutsh()));

#endif
}
