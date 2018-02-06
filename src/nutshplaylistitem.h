#ifndef NUTSHPLAYLISTITEM_H
#define NUTSHPLAYLISTITEM_H

#include <QListWidgetItem>

class PlaylistItem : public QListWidgetItem
{
public:
    PlaylistItem(QListWidget* parent = 0);
    PlaylistItem(const QVariantList&, QListWidget* parent = 0);
    PlaylistItem(const QString&, QListWidget* parent = 0);

private:
    int id;
    QString text;
};

#endif // NUTSHPLAYLISTITEM_H
