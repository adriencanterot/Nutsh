#ifndef NUTSHEDITINTERFACE_H
#define NUTSHEDITINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeView>
#include "nutshmetadata.h"
#include "nutshmetadata.h"

class NutshComunicator;

class NutshEditInterface : public QDeclarativeView
{
Q_OBJECT
public:
    explicit NutshEditInterface(NutshComunicator*);
    void place(float);

signals:

public slots:
    void edit(NutshMetaData);
    void edit();
    void finish();

private:

    NutshComunicator* core;
    NutshMetaData m_meta;

};

#endif // NUTSHEDITINTERFACE_H
