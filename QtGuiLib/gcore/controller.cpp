// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

// controller.cpp

#include <math.h>

#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QApplication>

#include "gmain/main.h"
#include "gcore/controller.h"

#include "gemulator/emulatordigital.h"
#include "gemulator/emulatordigital2.h"
#include "gemulator/emulatordigital3.h"
#include "gemulator/emulatoranalog.h"
#include "gmain/mainmenu2.h"
#include "gmain/mainmenu3.h"
#include "gscreen/screenwidget.h"
#include "gkeypad/keypadnew2.h"

#ifdef Q_OS_LINUX
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <pthread.h>
#endif

#define MAX_FREQ 3000000000L

//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wformat-security"
//#pragma GCC diagnostic pop

namespace gsa
{

   //QString logFileName("");
   core::Controller *controller(nullptr);

}

//IWidget::IWidget(QWidget *parent)
//    : QWidget(parent)
//{
//    ;
//}

//IWidget::~IWidget()
//{
//    ;
//}

namespace gsa {

namespace core {

   Controller::Controller(QWidget *parent, int number, float min, float max, float step)
      : QWidget(parent)
      , _keyPadNew2(nullptr)
      , _keyPad(false)
      , _position(200, 200)
   {
      gsa::controller = this;

      QDesktopWidget *desktop(QApplication::desktop());
      QRect rect = desktop->screenGeometry(0);

      _keyPadNew2 = new Pad::KeyPadNew2(parent);
      _keyPadNew2->move(rect.x() + 100, rect.y() + 100);
   }

   Controller::~Controller()
   {
   }

   void Controller::setFreqUnit(const TG::FreqUnits &freqUnit)
   {
   }

   void Controller::setFreqCenter(const double &freqCenter)
   {
      if (_freqStart + freqCenter - _freqCenter < 0) {
         _freqCenter = freqCenter;
         _freqStart = 0;
         _freqSpan = (_freqCenter - _freqStart) * 2;
         _freqStop = (_freqCenter - _freqStart) * 2;
      }
      else {
         _freqStart = _freqStart + freqCenter - _freqCenter;
         _freqStop = _freqStop + freqCenter - _freqCenter;
         _freqCenter = freqCenter;
      }
   }

   void Controller::setFreqSpan(const double &freqSpan)
   {
      if (_freqCenter - freqSpan / 2 < 0) {
         _freqSpan = _freqCenter * 2;
         _freqStart = _freqCenter - _freqSpan / 2;
         _freqStop = _freqCenter + _freqSpan / 2;
      }
      else {
         _freqStart = _freqCenter - freqSpan / 2;
         _freqStop = _freqCenter + freqSpan / 2;
         _freqSpan = freqSpan;
      }
   }

   void Controller::setFreqStart(double freqStart)
   {
      if (freqStart < 0) {
         freqStart = 0;
      }
      else if (freqStart > _freqStop) {
         freqStart = _freqStop;
      }
      _freqSpan = _freqStop - freqStart;
      _freqCenter = freqStart + (_freqStop - freqStart) / 2;
      _freqStart = freqStart;
   }

   void Controller::setFreqStop(double freqStop)
   {
      if (freqStop < 0) {
         freqStop = 0;
      }
      else if (freqStop < _freqStart) {
         freqStop = _freqStart;
      }
      _freqSpan = freqStop - _freqStart;
      _freqCenter = _freqStart + (freqStop - _freqStart) / 2;
      _freqStop = freqStop;
   }

   void Controller::setFreqStep(const double &freqStep)
   {
      _freqStep = freqStep;
   }

   int Controller::KeyPad(const TG::KeyPadParam &keyPadParam, int unitindex)
   {
      _keyPad = true;

      _keyPadNew2->setParams(keyPadParam, unitindex);
      int ret(_keyPadNew2->exec());
      _position = _keyPadNew2->pos();

      _keyPad = false;

      return ret;
   }

   void Controller::getSelection(TG::UnitTypes &type, int &index, double &value)
   {
      _keyPadNew2->getSelection(type, index, value);
   }

   void Controller::Double2String(QString &str, double value)
   {
      QString strValue(QString("%1").arg(value, 0, 'f'));
      QString strCut(QString("%1").arg(value, 0, 'f'));
      int index = strValue.indexOf(".");
      //if (strValue.length() > 9)
      if (index > 6)
         strCut = QString(strValue.toStdString().substr(0, index).c_str());
      else if (strValue.length() > 10)
         strCut = QString(strValue.toStdString().substr(0, 11).c_str());

      //QString strCut(QString("%1").arg((long long)value));

      str = strCut;
   }

} // namespace core

} // namespace gsa

