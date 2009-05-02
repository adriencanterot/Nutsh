#define VERSION 2
#include "nutshupdater.h"
NutshUpdater::NutshUpdater()
{
    m_nouvelleMaj = new QLabel("Une nouvelle version est disponible");
    m_dlInfos = new QLabel;
    m_oui = new QPushButton("Telecharger");
    m_non = new QPushButton("Plus tard");

    m_principal = new QVBoxLayout;
    m_ouiNon = new QHBoxLayout;
    m_progressLayout = new QHBoxLayout;

    m_ouiNon->addWidget(m_oui);
    m_ouiNon->addWidget(m_non);

    m_principal->addWidget(m_nouvelleMaj);
    m_principal->addLayout(m_ouiNon);

    connect(m_oui, SIGNAL(clicked()), this, SLOT(launchUpdater()));

    this->setLayout(m_principal);
}
void NutshUpdater::launchUpdater() {
    m_download = new NutshMaJ;
    m_download->show();
}
bool NutshUpdater::isUpdate() {
    QUrl url("http://nutsh.googlecode.com/svn/trunk/src/nutshupdater.cpp");
    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();

    if (QFile::exists("version.txt")) {
        QFile::remove("version.txt");
        qDebug() << "file removed";
    }
    file = new QBuffer;
    if (!file->open(QIODevice::WriteOnly)) {
        delete file;
        file = 0;
    }
    maj = new QHttp;
    QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
    maj->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());

    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    maj->get(path, file);

    connect(maj, SIGNAL(done(bool)), this, SLOT(getResults(bool)));
    if(numeroVersion == VERSION) {
        return false;
    }
    else if(VERSION < numeroVersion) {
        return true;
    }
    else {
        return false;
    }

}
void NutshUpdater::getResults(bool error) {

    if(error) {
        qDebug() << "Une erreur est survenue";
    }
    else {
        file->close();
        file->open(QIODevice::ReadOnly);
        QString version = file->readLine();
        version.left(14);
        qDebug() << version;
        numeroVersion = version.toInt();
        qDebug() << numeroVersion;
    }
}

