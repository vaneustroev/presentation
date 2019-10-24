// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef UNITTIME_H
#define UNITTIME_H

#include <QtWidgets\QWidget>

namespace Ui {
class UnitTime;
}

namespace Pad {

class UnitTime : public QWidget
{
    Q_OBJECT

public:
    explicit UnitTime(QWidget *parent = 0);
    ~UnitTime();

private:
    Ui::UnitTime *ui;
};

} // namespace Pad

#endif // UNITTIME_H

