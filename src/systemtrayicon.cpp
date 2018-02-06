#include "nutshsystemtrayicon.h"

NutshSystemTrayIcon::NutshSystemTrayIcon(QObject *parent) : QSystemTrayIcon(parent)
{
    menu = new QMenu;
    this->setContextMenu(menu);
    this->show();
}
