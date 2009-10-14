#ifndef NUTSHSYSTEMTRAYICON_H
#define NUTSHSYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>

class NutshSystemTrayIcon : public QSystemTrayIcon
{
public:
    NutshSystemTrayIcon(QObject* parent = 0);

private:
    QMenu* menu;
};

#endif // NUTSHSYSTEMTRAYICON_H
