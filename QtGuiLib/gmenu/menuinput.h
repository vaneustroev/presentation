// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUINPUT_H
#define MENUINPUT_H

//#include <boost/container/map.hpp>
#include <map>

#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuInput;
}

namespace Menu
{

class MenuInput : public IMenu
{
    Q_OBJECT

public:
    explicit MenuInput(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuInput();

public:
    //void KeyPad(TG::UnitTypes unitType = TG::unitUndef, QString name = QString(""));
    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::InputParam &inputParam);
    void fillButtonNames(void);

public slots:
    //void KeyPad(void);
    void EditCorrectionClicked();
    void nameChanged(QString name);

private slots:
    void clickCorrectionOn(void);
    void clickCorrectionOff(void);

private:
    Ui::MenuInput *ui;

private:
    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUINPUT_H
