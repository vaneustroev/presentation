// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUTOP_H
#define MENUTOP_H

#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuTop;
}

namespace Menu
{

class MenuTop : public QWidget
{
    Q_OBJECT

public:
    explicit MenuTop(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuTop();

public:
    bool eventFilter(QObject* object, QEvent* event);

public slots:
    void labelInput();

private:
    Ui::MenuTop *ui;

    Core::Controller *_controller;
};

} // namespace M

#endif // MENUTOP_H

