#include "nutshplaylistitem.h"

NutshPlaylistItem::NutshPlaylistItem(QListWidget *parent) : QListWidgetItem(parent)
{
    id = -1;
    text = QString();
}

NutshPlaylistItem::NutshPlaylistItem(const QVariantList& values,QListWidget *parent) : QListWidgetItem(parent)
{
    id = values.value(0).toInt();
    text = values.value(1).toString();
    this->setText(text);
}

NutshPlaylistItem::NutshPlaylistItem(const QString& text,QListWidget *parent) : QListWidgetItem(parent)
{
    this->text = text;
    this->setText(this->text);
}
