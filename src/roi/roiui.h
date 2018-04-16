#ifndef ROI_H
#define ROI_H

#include <QWidget>
#include "ui_roi.h"


class ROIui : public QWidget, public Ui::ROI
{
    Q_OBJECT

public:
    explicit ROIui(QWidget *parent = 0);

private:

};

#endif // ROI_H
