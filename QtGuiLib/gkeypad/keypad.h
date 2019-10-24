// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>

//#include "gcore/controller.h"
#include "gcore/core.h"

namespace Core {
class Controller;
} // namespace Core

//class MainMenu2;

namespace Ui {
class KeyPad;
}

namespace Pad {

class KeyPad : public QWidget
{
    Q_OBJECT

public:
    explicit KeyPad(QWidget *parent = 0, Core::Controller *controller = 0); //, MainMenu2 *mainMenu = 0);
    ~KeyPad();

public slots:
    void buttonKey0();
    void buttonKey1();
    void buttonKey2();
    void buttonKey3();
    void buttonKey4();
    void buttonKey5();
    void buttonKey6();
    void buttonKey7();
    void buttonKey8();
    void buttonKey9();
    void buttonKeyUp();
    void buttonKeyBackSpace();
    void buttonKeyEnter();
    void buttonKeyESC();

    void buttonUnit1();
    void buttonUnit2();
    void buttonUnit3();
    void buttonUnit4();

    void buttonKeyDot();
    void buttonKeyDown();

    //void slot_sliderMoved(int);
    void slot_actionTriggered(int action);
    void slot_rangeChanged(int min, int max);
    void slot_sliderMoved(int value);
    void slot_sliderPressed();
    void slot_sliderReleased();
    void slot_valueChanged(int value);

private:
    Ui::KeyPad *ui;

    Core::Controller *_controller;
    //MainMenu2 *_mainMenu;
    int _Min;
    int _Max;
    int _rangeMin;
    int _rangeMax;
    int _value;
};

} // namespace Pad

#endif // KEYPAD_H
