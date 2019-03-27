#include "inputdialog.h"


InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(this->pbAccept, SIGNAL(released()), this, SLOT(accept()));
    connect(this->pbReject, SIGNAL(released()), this, SLOT(reject()));
    connect(this->inputText, SIGNAL(textChanged(QString)), this, SLOT(updateOKButtonState()));
    pbAccept->setDisabled(true);
    QRegExp regExp("[a-z0-9]{1,16}");
    inputText->setValidator(new QRegExpValidator(regExp, this));
}

void InputDialog::updateOKButtonState()
{
    pbAccept->setDisabled(inputText->text().isEmpty());
}


