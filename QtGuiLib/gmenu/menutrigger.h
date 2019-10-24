// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUTRIGGER_H
#define MENUTRIGGER_H

//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>
#include <map>
#include <vector>

#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuTrigger;
}

namespace Menu
{

class MenuTrigger : public IMenu
{
    Q_OBJECT

public:
    explicit MenuTrigger(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuTrigger();

    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::TriggerParam &triggerParam);

private:
    Ui::MenuTrigger *ui;

    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUTRIGGER_H

