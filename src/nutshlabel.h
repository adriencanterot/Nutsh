#ifndef NUTSHLABEL_H
#define NUTSHLABEL_H

#include <QWidget>
#include "preprocess.h"
#include "nutshmetadata.h"
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

class NutshComunicator;
class NutshLabel : public QLabel
{
public:
    NutshLabel(NutshComunicator*, const QString& text = "");
    void setType(ContentTypeForLabel);
    void mousePressEvent(QMouseEvent* event);

private:

    ContentTypeForLabel contentType;
    NutshComunicator* core;
};

class NutshEditLabel : public QWidget {

    Q_OBJECT

    public:

    NutshEditLabel(const QString &text = QString(), QWidget *parent = 0);

    void mouseDoubleClickEvent(QMouseEvent* event);
    void setText(const QString &text);
    QString text() const;
    QString fit(const QString& text);

    public slots:

    void saveChanges();

    signals:

    void returnPressed(QString);

    private:

    QHBoxLayout *principal;
    QString content;

    QLabel *label;
    QLineEdit *lineEdit;

    enum Type {

        labelType, lineEditType
            };

    Type contentType;
};


#endif // NUTSHLABEL_H
