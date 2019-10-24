// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUBW_H
#define MENUBW_H

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
class MenuBw;
}

namespace Menu
{

class MenuBw : public IMenu
{
    Q_OBJECT

public:
    explicit MenuBw(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuBw();

    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::BwParam &bwParam);
    void fillButtonNames(void);

private slots:
    void clickRbwAuto(void);
    void clickRbwMan(void);
    void clickVbwAuto(void);
    void clickVbwMan(void);

private:
    Ui::MenuBw *ui;

    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUBW_H
