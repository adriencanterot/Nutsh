#ifndef NUTSHPLAYLISTITEM_H
#define NUTSHPLAYLISTITEM_H

#include <QListWidgetItem>

class NutshPlaylistItem : public QListWidgetItem
{
public:
    NutshPlaylistItem(QListWidget* parent = 0);
    NutshPlaylistItem(const QVariantList&, QListWidget* parent = 0);
    NutshPlaylistItem(const QString&, QListWidget* parent = 0);

private:
    int id;
    QString text;
};

#endif // NUTSHPLAYLISTITEM_H
