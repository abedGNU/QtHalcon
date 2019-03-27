#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include "ui_inputdialog.h"

class InputDialog : public QDialog, public Ui::InputDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = 0);

public slots:
    void updateOKButtonState();

private:

};

#endif // INPUTDIALOG_H
