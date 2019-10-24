// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUTOPINPUT_H
#define MENUTOPINPUT_H

#include <QDialog>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuTopInput;
}

namespace Menu
{

class MenuTopInput : public QDialog
{
    Q_OBJECT

public:
    explicit MenuTopInput(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuTopInput();

public slots:
    void slotRFCouplingAc(void);
    void slotRFCouplingDc(void);

private:
    Ui::MenuTopInput *ui;

    Core::Controller *_controller;
};

} // namespace M

#endif // MENUTOPINPUT_H
