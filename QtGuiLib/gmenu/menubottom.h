// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUBOTTOM_H
#define MENUBOTTOM_H

#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuBottom;
}

namespace Menu
{

class MenuBottom : public QWidget
{
    Q_OBJECT

public:
    explicit MenuBottom(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuBottom();

private:
    Ui::MenuBottom *ui;

    Core::Controller *_controller;
};

} // namespace M

#endif // MENUBOTTOM_H

