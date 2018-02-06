#include "label.h"
#include "core.h"


Label::Label(Core* corePath, const QString& text)
{
    this->setText(text);
    core = corePath;
}

void Label::setType(ContentTypeForLabel newType) {

    contentType = newType;
}

void Label::mousePressEvent(QMouseEvent *event) {

    if(event->button() == Qt::LeftButton && text() != "") {

        core->swapInterface(PlayingInterface);
        event->accept();

    } else {

        event->ignore();
    }
}

NutshEditLabel::NutshEditLabel(const QString& text, QWidget *parent) : QWidget(parent) {

    contentType = labelType;

    content = text;

    label = new QLabel(content, this);
    label->show();
    lineEdit = new QLineEdit(content, this);
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
    content = lineEdit->text();
    label->setText(content);
    label->show();
    label->setText(fit(lineEdit->text()));
    emit returnPressed(content);
}

QString NutshEditLabel::text() const {
    return content;
}

void NutshEditLabel::setText(const QString &text) {

    content = text;
    lineEdit->setText(content);
    label->setText(fit(content));
}

QString NutshEditLabel::fit(const QString& text) {

    QString fitted = text;
    if(fitted.size() > 23) {
        fitted.resize(20);
        fitted.append("...");
        return fitted;

    } else {
        return fitted;
    }
}

