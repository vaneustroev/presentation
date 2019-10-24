// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 14.09.2017
//

#ifndef MENUFREQ_H
#define MENUFREQ_H

//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>
#include <map>
#include <vector>

#include <QtWidgets\QWidget>
#include <QtWidgets\QDialog>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuFreq;
}

namespace Menu
{

class MenuFreq : public IMenu
{
    Q_OBJECT

public:
    explicit MenuFreq(QWidget *parent = 0, gsa::core::Controller *controller = 0);
    ~MenuFreq();

public slots:
    //void KeyPad(void);

public:
    //void KeyPad(TG::UnitTypes unitType = TG::unitUndef, QString name = QString(""));
    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::FreqParam &freqParam);
    void fillButtonNames(void);

private slots:
    void clickSweptSpan(void);
    void clickFullSpan(void);
    void clickZeroSpan(void);

private:
    Ui::MenuFreq *ui;

private:
    gsa::core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Menu

#endif // MENUFREQ_H

