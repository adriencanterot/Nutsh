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

class NutshComunicator;
class ImporterThread : public QThread {

    Q_OBJECT

public:
    ImporterThread(const QList<NutshMetaData>&, const QString&, NutshComunicator*);
    void run();

public slots:
    void forceQuit();

signals:
    void updateBar(int, int);

private:
    QList<NutshMetaData> metaList;
    bool loopRunning;
    QString m_tableName;
    NutshComunicator* core;

};

class NutshProgressInterface : public QWidget
{
    Q_OBJECT

public:

    NutshProgressInterface(NutshComunicator*);

    void setTopLabelText(const QString&);
    void setBottomLabelText(const QString&);
    void setRightLabelText(const QString&);
    void setLeftLabelText(const QString&);
    void setCancelButtonText(const QString&);
    void import(const QList<NutshMetaData>&, const QString&);

    void setMaximum(int);
    void setValue(int);
    void stopAction(QObject*, const char*);

    bool isActive();

    void swapToProgress();

public slots:
    void updateWidget(int, int);

private:
    NutshComunicator* core;

    ImporterThread* scan;

    QObject *m_receiver;
    const char* m_member;

    QLabel *m_right,
           *m_left,
           *m_top,
           *m_bottom;

    QProgressBar *m_progress;
    QVBoxLayout *m_principal;

    QHBoxLayout *m_progressLayout,
                *m_infosLayout;

    QPushButton *m_cancel;
    bool active;
};

#endif // NUTSHPROGRESSINTERFACE_H
