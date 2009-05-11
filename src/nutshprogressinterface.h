#ifndef NUTSHPROGRESSINTERFACE_H
#define NUTSHPROGRESSINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QLayout>
#include <QPushButton>

class NutshComunicator;
class NutshProgressInterface : public QWidget
{

public:

    NutshProgressInterface(NutshComunicator*);

    void setTopLabelText(const QString&);
    void setBottomLabelText(const QString&);
    void setRightLabelText(const QString&);
    void setLeftLabelText(const QString&);
    void setCancelButtonText(const QString&);

    void setMaximum(int);
    void setValue(int);
    void stopAction(QObject*, const char*);

    bool isActive();

    void swapToProgress();

private:
    NutshComunicator* core;

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
