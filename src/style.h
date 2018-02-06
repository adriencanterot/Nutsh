#ifndef NUTSHSTYLE_H
#define NUTSHSTYLE_H

#include <QCommonStyle>
#include <QPlastiqueStyle>
#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QPushButton>

class Style : public QPlastiqueStyle
{
        Q_OBJECT
        public:
                Style();
                void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
                void polish(QWidget *widget);
                void unpolish(QWidget *widget);
                void drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const;
};

#endif // NUTSHSTYLE_H
