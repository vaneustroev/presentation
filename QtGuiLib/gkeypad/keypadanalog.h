// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef KEYPADANALOG_H
#define KEYPADANALOG_H

//#include <QWidget>

//namespace Ui {
//class KeyPadAnalog;
//}

//class KeyPadAnalog : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit KeyPadAnalog(QWidget *parent = 0);
//    ~KeyPadAnalog();

//private:
//    Ui::KeyPadAnalog *ui;
//};

#include <QWidget>

//#include "gcore/controller.h"
#include "gcore/core.h"

//class Controller;

namespace Ui {
class KeyPadAnalog;
}

namespace Pad {

class KeyPadAnalog : public QWidget
{
    Q_OBJECT

public:
    explicit KeyPadAnalog(QWidget *parent = 0, Core::Controller *controller = 0);
    ~KeyPadAnalog();

    void KeyPad(const TG::KeyPadParam &keyPadParam);
    void fillButtonNames(void);

public slots:
    //void resizeEvent ( QResizeEvent * event );
    //void closeEvent( QCloseEvent *event );

    void buttonSweep();
    //void buttonSingle();
    void buttonFreq();
    void buttonSpan();
    void buttonAmpt();
    void buttonMeas();
    void buttonRestart();
    void buttonTrace();
    void buttonBw();
    void buttonMarkerSet();
    void buttonMarkerMain();
    void buttonMarkerPeak();
    void buttonSave();
    void buttonPrint();
    void buttonMode();
    void buttonPreset();

    void buttonSystem();

    void buttonExit();

private:
    Ui::KeyPadAnalog *ui;

    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;
    QString text;

    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

};

} // namespace Pad

#endif // KEYPADANALOG_H

