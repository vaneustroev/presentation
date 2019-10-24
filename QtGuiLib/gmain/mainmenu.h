// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MAINMENU
#define MAINMENU

//#define WIN32_LEAN_AND_MEAN

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Menu
{

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

signals:
    //void dataChanged(void);

public slots:
    void changeData();

public:
    void setController(Core::Controller *controller, const float &time);
    Core::Controller *controller(void);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Core::Controller *_controller;
};

} // namespace Menu

#endif // MAINMENU

