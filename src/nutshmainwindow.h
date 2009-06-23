#ifndef NUTSHMAINWINDOW_H
#define NUTSHMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtSql>
#include <QToolBar>
#include <QTextEdit>
#include <QThread>
#include <QFile>
#include <QtGui>
#include <QCommonStyle>
#include "nutshlecteur.h"
#include "nutshindexer.h"
#include "nutshcomunicator.h"
#include "nutshinstallationwizard.h"

class style : public QPlastiqueStyle
{
        Q_OBJECT
        public:
                style();
                void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
                void polish(QWidget *widget);
                void unpolish(QWidget *widget);
                void drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const;
};

class NutshMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    NutshMainWindow(QWidget *parent = 0);

private :

    NutshComunicator* path;
    //core

};

#endif // NUTSHMAINWINDOW_H
