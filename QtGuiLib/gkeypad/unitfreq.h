// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef UNITFREQ_H
#define UNITFREQ_H

#include <QtWidgets\QPushButton>
#include <QtWidgets\QWidget>

//#include "gcore/controller.h"
#include "gcore/core.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class UnitFreq;
}

namespace Pad {

class UnitFreq : public QWidget
{
    Q_OBJECT

public:
    explicit UnitFreq(QWidget *parent = 0);
    ~UnitFreq();

public slots:
    void clickedGHz(void);
    void clickedMHz(void);
    void clickedkHz(void);
    void clickedHz(void);

signals:
    void clickedUnit(TG::UnitTypes, int);

private:
    Ui::UnitFreq *ui;
};

} // namespace Pad

#endif // UNITFREQ_H

