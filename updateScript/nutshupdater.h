#include <QtCore/QCoreApplication>
#include <QObject>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QTimer>

class NutshUpdate : public QObject
{
    Q_OBJECT
    public:
        NutshUpdate();

    public slots:
        void afterTimer();
};
