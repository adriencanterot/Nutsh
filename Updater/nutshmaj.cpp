#include "nutshmaj.h"

NutshMaJ::NutshMaJ(QWidget *parent)
    : QWidget(parent)
{
    m_progress = new QProgressBar;
    m_cancel = new QPushButton("Arreter");
    m_principal = new QVBoxLayout;
    m_dlInfos = new QLabel("0000ko / 0000ko");
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

    QUrl url("http://telecharger.nutsh.com/last/maj/nutsh-05");
    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();

    if (QFile::exists("../../../nutsh-05")) {
        QFile::remove("nutsh-05");
        qDebug() << "file removed";
    }

    file = new QFile("../../../nutsh-05");
    file->setPermissions(QFile::WriteOther);
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
    if(i <= current) {
        i+= SIZE_LABEL;
        m_dlInfos->setText(QString("%1ko / %2ko").arg(current/SIZE_LABEL).arg(done/SIZE_LABEL));
    }
    m_progress->setMaximum(done);
    m_progress->setValue(current);
}

void NutshMaJ::quitAndStartNutsh() {
#ifdef Q_WS_MAC
    file->setPermissions(QFile::ExeOwner);
    QProcess nutsh;
    nutsh.startDetached("/Developer/Projets/TheNutsh!Project/source/nutsh-05/bin/nutsh-05.app/Contents/MacOS/nutsh-05");
    qDebug() << nutsh.error() << nutsh.state();
#endif
}
