// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUSWEEP_H
#define MENUSWEEP_H

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
class MenuSweep;
}

namespace Menu
{

class MenuSweep : public IMenu
{
    Q_OBJECT

public:
    explicit MenuSweep(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuSweep();

    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::SweepParam &sweepParam);
    void fillButtonNames(void);
    void menuSingleCont(void);
    void menuSingleRestart(void);

public slots:
    void clickSweepAuto(void);
    void clickSweepContinuous(void);
    void clickSweepSingle(void);
    void buttonRestart(void);

private:
    Ui::MenuSweep *ui;

    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;
    int _single;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUSWEEP_H

