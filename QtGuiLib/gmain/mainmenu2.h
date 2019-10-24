// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MAINMENU2_H
#define MAINMENU2_H

//#define WIN32_LEAN_AND_MEAN

//#include <boost/container/map.hpp>
#include <map>
#include <memory>

#include <QtCore\QEvent>
#include <QtCore\QSharedPointer>
#include <QtCore\QMap>
#include <QtGui\QMouseEvent>
#include <QtWidgets\QWidget>
#include <QtWidgets\QMessageBox>

#include "../gcore/controller.h"
#include "../gcore/core.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MainMenu2;
}

namespace Menu
{

class MainMenu2 : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu2(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MainMenu2();

public slots:
    //void resizeEvent ( QResizeEvent * event );
    //void closeEvent( QCloseEvent *event );

    //void buttonSweep();
    //void buttonSingle();

    void buttonN0();
    void buttonN1();
    void buttonN2();
    void buttonN3();
    void buttonN4();
    void buttonN5();
    void buttonN6();
    void buttonN7();

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

    void clearMenus(QSharedPointer<Core::SAItem> item);
    void clearButtons(void);
    void setButtonTexts(const TG::Button &button);
    void setButtonStates(const TG::Button &button);
    void pushButton(const TG::Button &button);

    void buttonNN(const TG::Button &button);

    TG::Button &button(void) {return _menucurrent->button();}
    TG::Button &activeButton(void) {return _menucurrent->activeButton();}

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
    Ui::MainMenu2 *ui;

    Core::Controller *_controller;
    float _time;
    float _freq;

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

namespace Garbage {

class IGui
{
public:
    IGui();
    virtual ~IGui();

public:
    virtual void setMainMenu(void) = 0;

};

class SweepGui : public IGui
{
public:
    SweepGui(Menu::MainMenu2 *mainmenu) {_mainmenu = mainmenu;}
    ~SweepGui();

public:
    void setMainMenu(void){;}

private:
    Menu::MainMenu2 *_mainmenu;
};

} // namespace Garbage

#endif // MAINMENU2_H

