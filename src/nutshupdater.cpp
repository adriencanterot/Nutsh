#define VERSION 4

#include "nutshupdater.h"
#include "nutshcomunicator.h"

NutshUpdater::NutshUpdater(NutshComunicator *corePath)
{

    core = corePath;

    m_nouvelleMaj = new QLabel(tr("Une nouvelle version est disponible"));
    m_dlInfos = new QLabel;
    m_oui = new QPushButton(tr("Telecharger"));
    m_non = new QPushButton(tr("Plus tard"));

    m_principal = new QVBoxLayout;
    m_ouiNon = new QHBoxLayout;
    m_progressLayout = new QHBoxLayout;

    m_ouiNon->addWidget(m_oui);
    m_ouiNon->addWidget(m_non);

    m_principal->addWidget(m_nouvelleMaj);
    m_principal->addLayout(m_ouiNon);

    connect(m_oui, SIGNAL(clicked()), this, SLOT(launchUpdater()));
    connect(m_non, SIGNAL(clicked()), this, SLOT(close()));

    this->setLayout(m_principal);

    if(this->isUpdate()) {

        this->swapToUpdater();
    }
}

void NutshUpdater::launchUpdater() {

    m_download = new NutshMaJ(core);

    this->close();
}

bool NutshUpdater::waitForSignal(QObject *object, const char *signal)
{

    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    QObject::connect(object, signal, &loop, SLOT(quit()));
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    timer.start(5000);
    loop.exec();

    return timer.isActive();
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

    this->waitForSignal(maj, SIGNAL(done(bool)));

    if(numeroVersion == VERSION) {

      return false;

  } else if(VERSION < numeroVersion) {

      qDebug() <<  VERSION << numeroVersion;
        return true;
    } else {

        return false;
    }

}

void NutshUpdater::getResults(bool error) {

    if(error) {

        qDebug() << "Une erreur est survenue (pas de connextion internet?)";

    } else {

        file->close();
        file->open(QIODevice::ReadOnly);

        QString version = file->readLine();
        QString sansRetourLigne = version.right(2);
        qDebug() << sansRetourLigne;

        bool * ok = new bool;
        ok = false;
        this->numeroVersion = sansRetourLigne.toInt(ok);
        file->close();

        if(ok) { qDebug() << "great"; }
    }
}

void NutshUpdater::swapToUpdater() {

    qDebug() << "Hidden";

    this->show();
}
