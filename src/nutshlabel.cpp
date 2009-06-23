#include "nutshlabel.h"
#include "nutshcomunicator.h"


NutshLabel::NutshLabel(NutshComunicator* corePath, const QString& text)
{
    this->setText(text);
    core = corePath;
}

void NutshLabel::setType(ContentTypeForLabel newType) {

    contentType = newType;
}

void NutshLabel::mousePressEvent(QMouseEvent *event) {

    if(event->button() == Qt::LeftButton && text() != "") {

        core->swapInterface(Playing);
        event->accept();

    } else {

        event->ignore();
    }
}

NutshEditLabel::NutshEditLabel(const QString& text, QWidget *parent) : QWidget(parent) {

    contentType = labelType;

    label = new QLabel(text, this);
    label->show();
    lineEdit = new QLineEdit(text, this);
    lineEdit->hide();

    principal = new QHBoxLayout;
    principal->addWidget(label);
    principal->addWidget(lineEdit);

    this->setLayout(principal);
    this->setFixedSize(label->width()+15, label->height()+15);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(saveChanges()));

    this->setFixedSize(300, this->height()+10);
}

void NutshEditLabel::mouseDoubleClickEvent(QMouseEvent* event) {


    if(event->button() == Qt::LeftButton && contentType == labelType) {

        label->hide();
        lineEdit->show();
        lineEdit->setFocus();
        lineEdit->selectAll();
        contentType = lineEditType;
        event->accept();

    } else {

        event->ignore();
    }
}

void NutshEditLabel::saveChanges() {

    contentType = labelType;
    lineEdit->hide();
    label->setText(lineEdit->text());
    label->show();
    emit returnPressed(lineEdit->text());
}

QString NutshEditLabel::text() const {

    if(contentType == lineEditType) {

        return lineEdit->text();

    } else {

        return label->text();
    }
}

void NutshEditLabel::setText(const QString &text) {

    lineEdit->setText(text);
    label->setText(text);
}

