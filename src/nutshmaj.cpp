#include "nutshmaj.h"

NutshMaJ::NutshMaJ(QWidget *parent)
    : QWidget(parent)
{
    m_progress = new QProgressBar;
    m_cancel = new QPushButton("Arreter");
    m_principal = new QVBoxLayout;
    m_dlInfos = new QLabel("000ko / 000ko");
    m_actionLayout = new QHBoxLayout;
    m_actionLayout->addWidget(m_dlInfos);
    m_actionLayout->addWidget(m_cancel);
    m_principal->addWidget(m_progress);
    m_principal->addLayout(m_actionLayout);
    this->telecharger();

    this->setLayout(m_principal);
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(quitAndStartNutsh()));
}

void NutshMaJ::telecharger() {
#ifdef Q_WS_MAC
    QUrl url("http://telecharger.nutsh.com/last/miseajour/nutsh-05");
#endif
#ifdef Q_WS_WIN
    QUrl url("http://telecharger.nutsh.com/last/miseajour/nutsh-05.exe");
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
    QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
    m_download->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());

    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    m_download->get(path, file);
    connect(m_download, SIGNAL(dataReadProgress(int,int)), this, SLOT(updProgress(int,int)));

    connect(m_download, SIGNAL(done(bool)), this, SLOT(quitAndStartNutsh()));

}
void NutshMaJ::updProgress(int current, int done) {
    m_dlInfos->setText(QString("%1ko / %2ko").arg(current/SIZE_LABEL).arg(done/SIZE_LABEL));
    m_progress->setMaximum(done);
    m_progress->setValue(current);
}

void NutshMaJ::quitAndStartNutsh() {
#ifdef Q_WS_MAC
    file->setPermissions(QFile::ExeUser);
    file->close();
    QDir actual("");
    qDebug() << actual.absolutePath();
    system("chmod 777 nutsh-05");
    system("./nutsh-05");
#endif
#ifdef Q_WS_WIN
    QProcess nutsh;
    qDebug() << QDir::toNativeSeparators(QDir::currentPath()+"/nutsh-05.exe");
    nutsh.startDetached(QDir::toNativeSeparators("nutsh-05.exe"));
    QApplication::exit(0);
#endif
}
