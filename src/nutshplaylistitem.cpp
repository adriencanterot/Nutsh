#include "playlistitem.h"

PlaylistItem::PlaylistItem(QListWidget *parent) : QListWidgetItem(parent)
{
    id = -1;
    text = QString();
}

PlaylistItem::PlaylistItem(const QVariantList& values,QListWidget *parent) : QListWidgetItem(parent)
{
    id = values.value(0).toInt();
    text = values.value(1).toString();
    this->setText(text);
}

PlaylistItem::PlaylistItem(const QString& text,QListWidget *parent) : QListWidgetItem(parent)
{
    this->text = text;
    this->setText(this->text);
}
