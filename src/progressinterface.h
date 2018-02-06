#ifndef NUTSHPROGRESSINTERFACE_H
#define NUTSHPROGRESSINTERFACE_H

#include <QWidget>
#include <QProgressBar>
#include <QPushButton>
#include "metadata.h"
#include "sqlmanager.h"
#include "indexer.h"

class Core;
class ProgressInterface : public QWidget
{
    Q_OBJECT

public:

    ProgressInterface(Core*);

    void import(const QString& path);

    void setMaximum(int);
    void setValue(int);
    void setText(const QString&);

    bool isActive();

    void visible(bool visible);

    void place(float coef);

public slots:
    void finished();
    void updateWidget(ProgressionInfo);
    void reset();
    void stopWhy(const QString& why);
    void cancel();
private:
    Core* core;

    QObject *m_receiver;
    QLabel *m_label;
    const char* m_member;

    QProgressBar *m_progress;

    QPushButton *m_cancel;

    QString m_stopMessage;
    Indexer* scan;
    bool active;
};

#endif // NUTSHPROGRESSINTERFACE_H
