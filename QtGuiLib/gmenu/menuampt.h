// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUAMPT_H
#define MENUAMPT_H

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
class MenuAmpt;
}

//class IWidget : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit IWidget(QWidget *parent = 0);
//    virtual ~IWidget();

//    virtual void menuItemEdit(QString text) = 0;
//};

namespace Menu
{

class MenuAmpt : public IMenu
{
    Q_OBJECT

public:
    explicit MenuAmpt(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuAmpt();

public:
    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::AmptParam &amptParam);
    void fillButtonNames(void);

public slots:
    void slotCurrentIndexChanged(int index);
    void buttonScaleLog();
    void buttonScaleLin();

private:
    Ui::MenuAmpt *ui;

private:
    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    //bool _keyPad;
    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    //std::map<int, TG::AmptYAxis> _yaxisIndex;

};

} // namespace M

#endif // MENUAMPT_H

