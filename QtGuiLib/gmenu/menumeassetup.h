// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUMEASSETUP_H
#define MENUMEASSETUP_H

//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>
#include <map>
#include <vector>

#include <QtWidgets\QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuMeasSetup;
}

namespace Menu
{

class MenuMeasSetup : public IMenu
{
    Q_OBJECT

public:
    explicit MenuMeasSetup(QWidget *parent = 0, gsa::core::Controller *controller = 0);
    ~MenuMeasSetup();

    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::MeasSetupParam &measSetupParam);

private:
    Ui::MenuMeasSetup *ui;

    //Core::Controller *_controller;
	gsa::core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUMEASSETUP_H

