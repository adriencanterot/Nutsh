#ifndef NUTSHEDITINTERFACE_H
#define NUTSHEDITINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeView>
#include "metadata.h"
#include "metadata.h"

class Core;

class EditInterface : public QDeclarativeView
{
Q_OBJECT
public:
    explicit EditInterface(Core*);
    void place(float);

signals:

public slots:
    void edit(Metadata);
    void edit();
    void finish();

private:

    Core* core;
    Metadata m_meta;

};

#endif // NUTSHEDITINTERFACE_H
