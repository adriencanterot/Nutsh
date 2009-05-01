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

    m_download = new QHttp(this);
    m_downloadProgress = new QProgressDialog(this);
    m_downloadProgress->setLabel(m_dlInfos);

    connect(m_oui, SIGNAL(clicked()), this, SLOT(launchUpdater()));

    this->setLayout(m_principal);
}
void NutshUpdater::launchUpdater() {
#ifdef Q_WS_MAC
    system("./Updater");

#endif
}
