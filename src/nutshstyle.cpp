#include "nutshstyle.h"

NutshStyle::NutshStyle()
{
}

void NutshStyle::polish(QWidget *widget)
{
        if (qobject_cast<QPushButton *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void NutshStyle::unpolish(QWidget *widget)
{
        if (qobject_cast<QPushButton *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

void NutshStyle::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    QRect r(rectangle);
    if(enabled){
        if(textRole == QPalette::ButtonText)
            painter->setPen(QPen(QColor(Qt::white)));
        else
            painter->setPen(QPen(Qt::black));
    }
    else
        painter->setPen(QPen(QColor(125, 125, 125)));

        r.setHeight(r.height()-8);
        painter->drawText(r, alignment, text);
}

void NutshStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
        int rectX, rectY, rectLong, rectLarg, rd;
        option->rect.getRect(&rectX, &rectY, &rectLong, &rectLarg);

        rectLong = rectLong - 2;
        rectLarg = rectLarg - 9;
        rectX = rectX + 1;
        rectY = rectY + 1;
        rd = 9;

        if(element == PE_PanelButtonCommand)
        {
                if(option->state & State_Enabled)
                {
                        QLinearGradient gradient;
                        gradient.setStart(0, rectLarg + 2);
                        gradient.setFinalStop(0, 0);
                        gradient.setSpread(QGradient::ReflectSpread);
                        gradient.setColorAt(1, QColor(248, 155, 28));
                        gradient.setColorAt(0, QColor(243, 116, 32));

                        painter->setRenderHint(QPainter::Antialiasing);
                        painter->save();
                        painter->setBrush(QBrush(gradient));
                        painter->setPen(Qt::NoPen);
                        painter->drawRoundedRect(rectX, rectY, rectLong, rectLarg, rd, rd, Qt::AbsoluteSize);
                }
                else
                {
                        painter->save();
                        painter->setPen(QColor(173, 178, 181));
                        painter->setBrush(QBrush(QColor(244, 244, 244)));
                        painter->drawRect(rectX, rectY, rectLong, rectLarg);
                        painter->restore();
                        painter->setPen(Qt::NoPen);
                        painter->drawRoundedRect(rectX, rectY, rectLong, rectLarg, rd, rd, Qt::AbsoluteSize);
                }
                if(option->state & State_MouseOver)
                {
                        QLinearGradient gradient;
                        gradient.setStart(0, rectLarg + 2);
                        gradient.setFinalStop(0, 0);
                        gradient.setSpread(QGradient::ReflectSpread);
                        gradient.setColorAt(1, QColor(238, 145, 18));
                        gradient.setColorAt(0, QColor(233, 106, 22));

                        painter->setRenderHint(QPainter::Antialiasing);
                        painter->save();
                        painter->setBrush(QBrush(gradient));
                        painter->setPen(Qt::NoPen);
                        painter->drawRoundedRect(rectX, rectY, rectLong, rectLarg, rd, rd, Qt::AbsoluteSize);
                }
                if(option->state & (State_Sunken | State_On))
                {
                        QLinearGradient gradient;
                        gradient.setStart(0, rectLarg + 2);
                        gradient.setFinalStop(0, 0);
                        gradient.setSpread(QGradient::ReflectSpread);
                        gradient.setColorAt(0, QColor(238, 145, 18));
                        gradient.setColorAt(1, QColor(233, 106, 22));

                        painter->setRenderHint(QPainter::Antialiasing);
                        painter->save();
                        painter->setBrush(QBrush(gradient));
                        painter->setPen(Qt::NoPen);
                        painter->drawRoundedRect(rectX, rectY, rectLong, rectLarg, rd, rd, Qt::AbsoluteSize);
                }
        }
}
