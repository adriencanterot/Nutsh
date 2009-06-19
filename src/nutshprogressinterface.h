#ifndef NUTSHPROGRESSINTERFACE_H
#define NUTSHPROGRESSINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QLayout>
#include <QPushButton>
#include <QThread>
#include "nutshmetadata.h"
#include "nutshsqlsaver.h"
#include "nutshindexer.h"

class NutshComunicator;
class NutshProgressInterface : public QWidget
{
    Q_OBJECT

public:

    NutshProgressInterface(NutshComunicator*);

    void import(const QString& path);

    void setMaximum(int);
    void setValue(int);

    bool isActive();

    void swapToProgress();
    void finished();

public slots:
    void updateWidget(int, int);
    void reset();
    void stopWhy(const QString& why);

private:
    NutshComunicator* core;

    QObject *m_receiver;
    const char* m_member;

    QLabel *m_right,
           *m_left,
           *m_top,
           *m_bottom;

    QProgressBar *m_progress;

    QPushButton *m_cancel;

    QString m_stopMessage;
    Indexer* scan;
    bool active;
};

#endif // NUTSHPROGRESSINTERFACE_H
