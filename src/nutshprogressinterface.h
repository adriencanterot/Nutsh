#ifndef NUTSHPROGRESSINTERFACE_H
#define NUTSHPROGRESSINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QLayout>

class NutshComunicator;
class NutshProgressInterface : public QWidget
{

public:

    NutshProgressInterface(NutshComunicator*);

    void setTopLabelText(const QString&);
    void setBottomLabelText(const QString&);
    void setRightLabelText(const QString&);
    void setLeftLabelText(const QString&);

    void setMaximum(int);
    void setValue(int);

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
    QHBoxLayout *m_progressLayout;
    bool active;
};

#endif // NUTSHPROGRESSINTERFACE_H
