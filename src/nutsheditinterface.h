#ifndef NUTSHEDITINTERFACE_H
#define NUTSHEDITINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "nutshmetadata.h"
#include "nutshmetadata.h"

class NutshComunicator;

class NutshEditInterface : public QWidget
{
Q_OBJECT
public:
    explicit NutshEditInterface(NutshComunicator*);
    void place(float);

signals:

public slots:
    void edit(NutshMetaData);
    void finish();

private:

    NutshComunicator* core;
    QLabel *m_artiste,
           *m_album,
           *m_titre;

    QLineEdit *m_editartiste,
              *m_editalbum,
              *m_edittitre;

    NutshMetaData m_meta;

    QPushButton *m_confirm,
                *m_cancel;

};

#endif // NUTSHEDITINTERFACE_H
