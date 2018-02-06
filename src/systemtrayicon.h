#ifndef NUTSHSYSTEMTRAYICON_H
#define NUTSHSYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>

class SystemtrayIcon : public QSystemTrayIcon
{
public:
    SystemtrayIcon(QObject* parent = 0);

private:
    QMenu* menu;
};

#endif // NUTSHSYSTEMTRAYICON_H
