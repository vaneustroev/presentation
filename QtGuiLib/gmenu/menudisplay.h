// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUDISPLAY_H
#define MENUDISPLAY_H

//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>
#include <map>
#include <vector>

#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"
#include "gcore/data.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuDisplay;
}

namespace Menu
{

class MenuDisplay : public IMenu
{
    Q_OBJECT

public:
    explicit MenuDisplay(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuDisplay();

    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::DisplayParam &displayParam);
    void fillButtonNames(void);

private slots:
    void clickDisplayLineOn(void);
    void clickDisplayLineOff(void);

private:
    Ui::MenuDisplay *ui;

    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUDISPLAY_H

