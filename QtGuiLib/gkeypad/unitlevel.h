// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef UNITLEVEL_H
#define UNITLEVEL_H

#include <QWidget>

namespace Ui {
class UnitLevel;
}

namespace Pad {

class UnitLevel : public QWidget
{
    Q_OBJECT

public:
    explicit UnitLevel(QWidget *parent = 0);
    ~UnitLevel();

private:
    Ui::UnitLevel *ui;
};

} // namespace Pad

#endif // UNITLEVEL_H

