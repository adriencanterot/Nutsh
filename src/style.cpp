#include "nutshmainwindow.h"

style::style()
{
}

void style::polish(QWidget *widget)
{
	if (qobject_cast<QPushButton *>(widget))
	widget->setAttribute(Qt::WA_Hover, true);
}

void style::unpolish(QWidget *widget)
{
	if (qobject_cast<QPushButton *>(widget))
	widget->setAttribute(Qt::WA_Hover, false);
}

void style::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    if(enabled)
        painter->setPen(QPen(QColor(Qt::black)));
    else
        painter->setPen(QPen(QColor(125, 125, 125)));
        painter->drawText(rectangle, alignment, text);
}

void style::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
	int rectX, rectY, rectLong, rectLarg;
	option->rect.getRect(&rectX, &rectY, &rectLong, &rectLarg);

	rectLong = rectLong - 2;
	rectLarg = rectLarg - 2;
	rectX = rectX + 1;
	rectY = rectY + 1;

	if(element == PE_PanelButtonCommand)
	{
		if(option->state & State_Enabled)
		{
			QLinearGradient gradient;
			gradient.setStart(0, rectLarg + 2);
			gradient.setFinalStop(0, 0);
			gradient.setSpread(QGradient::ReflectSpread);
			gradient.setColorAt(0, Qt::white);
			gradient.setColorAt(0.5, QColor(233, 233, 233));
			gradient.setColorAt(1, Qt::white);

			painter->setRenderHint(QPainter::Antialiasing);
			painter->save();
			painter->setPen(QColor(Qt::black));
			painter->setBrush(QBrush(gradient));
			painter->drawRoundedRect(rectX, rectY, rectLong, rectLarg, 5, 5, Qt::AbsoluteSize);
			painter->restore();
			painter->setPen(QColor(250, 250, 250));
			painter->drawRoundedRect(rectX + 1, rectY + 1, rectLong, rectLarg, 5, 5, Qt::AbsoluteSize);
		}
		else
		{
			painter->save();
			painter->setPen(QColor(173, 178, 181));
			painter->setBrush(QBrush(QColor(244, 244, 244)));
			painter->drawRect(rectX, rectY, rectLong, rectLarg);
			painter->restore();
			painter->setPen(QColor(Qt::white));
			painter->drawRect(rectX + 1, rectY + 1, rectLong - 2, rectLarg - 2);
		}
		if(option->state & State_MouseOver)
		{
			QLinearGradient gradient;
			gradient.setStart(0, rectLarg + 2);
			gradient.setFinalStop(0, 0);
			gradient.setSpread(QGradient::ReflectSpread);
			gradient.setColorAt(0, QColor(203, 244, 246));
			gradient.setColorAt(0.5, QColor(129, 185, 243));
			gradient.setColorAt(1, QColor(203, 244, 246));

			painter->setRenderHint(QPainter::Antialiasing);
			painter->save();
			painter->setPen(QColor(Qt::black));
			painter->setBrush(QBrush(gradient));
			painter->drawRoundedRect(rectX, rectY, rectLong, rectLarg, 5, 5, Qt::AbsoluteSize);
			painter->restore();
			painter->setPen(QColor(250, 250, 250));
			painter->drawRoundedRect(rectX + 1, rectY + 1, rectLong, rectLarg, 5, 5, Qt::AbsoluteSize);
		}
		if(option->state & (State_Sunken | State_On))
		{
			QLinearGradient gradient;
			gradient.setStart(0, rectLarg + 2);
			gradient.setFinalStop(0, 0);
			gradient.setSpread(QGradient::ReflectSpread);
			gradient.setColorAt(0, QColor(196, 209, 219));
			gradient.setColorAt(0.25, QColor(147, 177, 200));
			gradient.setColorAt(0.5, QColor(105, 149, 183));
			gradient.setColorAt(0.75, QColor(137, 175, 200));
			gradient.setColorAt(1, QColor(178, 209, 219));

			painter->setRenderHint(QPainter::Antialiasing);
			painter->save();
			painter->setPen(QColor(Qt::black));
			painter->setBrush(QBrush(gradient));
			painter->drawRoundedRect(rectX + 1, rectY + 1, rectLong - 1, rectLarg - 1, 5, 5, Qt::AbsoluteSize);
			painter->restore();
			painter->setPen(QColor(150, 150, 150));
			painter->drawRoundedRect(rectX + 1, rectY + 2, rectLong - 1, rectLarg - 1, 5, 5, Qt::AbsoluteSize);
		}
	}
}
