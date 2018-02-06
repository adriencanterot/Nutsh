#include "systemtrayicon.h"

SystemtrayIcon::SystemtrayIcon(QObject *parent) : QSystemTrayIcon(parent)
{
    menu = new QMenu;
    this->setContextMenu(menu);
    this->show();
}
