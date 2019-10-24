// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MAINMENU3_H
#define MAINMENU3_H

//#define WIN32_LEAN_AND_MEAN

//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>
#include <map>
#include <vector>

#include <QtWidgets\QWidget>
#include <QtWidgets\QPushButton>

//#include "gcore/controller.h"
#include "gcore/data.h"
#include "gcore/core.h"

namespace Core {
class Controller;
} // namespace Core

//#include "gmenu/menuampt.h"
//#include "gmenu/menubw.h"
//#include "gmenu/menudisplay.h"
//#include "gmenu/menufreq.h"
//#include "gmenu/menuinput.h"
//#include "gmenu/menuoutput.h"
//#include "gmenu/menumarker.h"
//#include "gmenu/menumeassetup.h"
//#include "gmenu/menupeaksearch.h"
//#include "gmenu/menusweep.h"
//#include "gmenu/menutrace.h"
//#include "gmenu/menutrigger.h"
//#include "gmenu/menuusermenu.h"

//class MenuAmpt;
//class MenuBw;
//class MenuDisplay;
//class MenuFreq;
//class MenuInput;
//class MenuOutput;
//class MenuMarker;
//class MenuMeasSetup;
//class MenuPeakSearch;
//class MenuSweep;
//class MenuTrace;
//class MenuTrigger;
//class MenuUserMenu;

namespace Ui {
class MainMenu3;
}

namespace Menu
{

class MenuAmpt;
class MenuBw;
class MenuDisplay;
class MenuFreq;
class MenuInput;
class MenuOutput;
class MenuMarker;
class MenuMeasSetup;
class MenuPeakSearch;
class MenuSweep;
class MenuTrace;
class MenuTrigger;
class MenuUserMenu;

class MainMenu3 : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu3(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MainMenu3();

public slots:
    void slotIndexChanged(int index);
    void slotAmptChanged(TG::AmptParam &);
    void slotFreqChanged(TG::FreqParam &);
    void slotBwChanged(TG::BwParam &);
    void slotSweepChanged(TG::SweepParam &);
    void slotInputChanged(TG::InputParam &);
    void slotDisplayChanged(TG::DisplayParam &);
    void slotMarkerChanged(TG::MarkerParam &);
    void slotTraceChanged(TG::TraceParam &);
    void slotMenuChanged(TG::IndexMenu &);
    void slotMenuItemEdit(QString);
    void slotMenuSingleCont(void);
    void slotMenuSingleRestart(void);
    //void slotMenuExit(void);

public:
    void FillMaps(void);
    void setStyleSheetButton(const TG::Button &button, const TG::ButtonType &type);
    void MenuFillFreq(void);
    void MenuFillSpan(void);
    void MenuFillAmpt(void);
    void MenuFillBW(void);
    void MenuFillSweep(void);
    void MenuFillTrace(void);
    void MenuFillMarkerSet(void);
    void MenuFillMarkerMain(void);
    void MenuFillMarkerPeak(void);
    void MenuFillSavePrinter(void);

    const TG::MenuType &type(void) {return _menuType;}
    const TG::IndexMenu &indexMenu(void) {return _indexMenu;}

    void clearMenus(QSharedPointer<Core::SAItem> item);
    void clearButtons(void);
    void setButtonTexts(const TG::Button &button);
    void setButtonStates(const TG::Button &button);
    void pushButton(const TG::Button &button);

    void buttonNN(const TG::Button &button);

    TG::Button &button(void) {if(_menucurrent == nullptr) return _button; else return _menucurrent->button();}
    TG::Button &activeButton(void) {if(_menucurrent == nullptr) return _button; else return _menucurrent->activeButton();}

    //void buttonNumber(const TG::Button &button);
    void buttonKeyPad(const TG::Button &button);
    void buttonKey(const TG::Button &button);

    void setCurrentMenuItem(const TG::Button &button, const bool &root, const TG::Moving &moving);
    //void setParentMenuItem(const TG::Button &button);
    //void setActiveMenu(const TG::Button &button);
    //void setRootMenu() {_menucurrent = _menuroot;}
    QSharedPointer<Core::SAItem> &menuCurrent(void) {
        //TG::Button _button1 = _menucurrent->button();
        //TG::Button _button2 = _menucurrent->activeButton();
        return _menucurrent;
    }

public:
    //void setState();

private:
    Ui::MainMenu3 *ui;

    Core::Controller *_controller;
    float _time;
    float _freq;
    //boost::container::map<TG::IndexMenu, TG::IndexMenu> indexes;
    std::map<TG::IndexMenu, TG::IndexMenu> indexes;

    TG::MenuType _menuType;
    TG::IndexMenu _indexMenu;

    MenuAmpt *_menuAmpt;
    MenuBw *_menuBw;
    MenuDisplay *_menuDisplay;
    MenuFreq *_menuFreq;
    MenuInput *_menuInput;
    MenuOutput *_menuOutput;
    MenuMarker *_menuMarker;
    MenuMeasSetup *_menuMeasSetup;
    MenuPeakSearch *_menuPeakSearch;
    MenuSweep *_menuSweep;
    MenuTrace *_menuTrace;
    MenuTrigger *_menuTrigger;
    MenuUserMenu *_menuUserMenu;

    TG::Button _button;
    //boost::container::map<TG::Button, QPushButton *> _buttonMap;
    //boost::container::map<TG::Button, TG::FreqUnits> _freqUnit;
    //boost::container::map<TG::Button, TG::SweepUnits> _sweepUnit;
    //boost::container::map<TG::Button, TG::RefLevlUnit> _refLevlUnit;
    //boost::container::map<TG::ButtonType, QString> _styleSheets;
    std::map<TG::Button, QPushButton *> _buttonMap;
    std::map<TG::Button, TG::FreqUnits> _freqUnit;
    std::map<TG::Button, TG::SweepUnits> _sweepUnit;
    std::map<TG::Button, TG::RefLevlUnit> _refLevlUnit;
    std::map<TG::ButtonType, QString> _styleSheets;
    QSharedPointer<Core::SAItem> _menuroot;
    QSharedPointer<Core::SAItem> _menucurrent;
    QSharedPointer<Core::SAItem> _itemHz;

    //QStringList _stringlist;

    int _spanvalue;

};

} // namespace Menu

#endif // MAINMENU3_H
