#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QWidget>
#include "ui_production.h"

class ProductionUi : public QWidget, Ui::production
{
    Q_OBJECT

public:
    explicit ProductionUi(QWidget *parent = 0);

private:

};

#endif // PRODUCTION_H
