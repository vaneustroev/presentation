//#pragma once

// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef CONTROLLER
#define CONTROLLER

#include <QtWidgets\QDialog>
#include <QtWidgets\QWidget>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QMessageBox>
#include <QtCore\QList>
#include <QtCore\QVector>
#include <QtCore\QQueue>
#include <QtCore\QSettings>
#include <QtCore\QStringList>
#include <QtCore\QThread>
#include <QtCore\QStack>
#include <QtCore\QMutex>
#include <QtCore\QMap>
#include <QtCore\QString>
#include <QtCore\QSemaphore>
//#include <qlogging.h>

#include <iostream>
#include <map>
#include <vector>
//#include <boost/iostreams/concepts.hpp>
//#include <boost/iostreams/stream.hpp>
//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>

//#include "emulatordigital.h"
//#include "emulatordigital2.h"
//#include "emulatoranalog.h"
#include "../gcore/data.h"
#include "../gcore/core.h"
//#include "screenwidget.h"

namespace Menu {
	class MainMenu2;
	class MainMenu3;
}
namespace Pad {
	class KeyPadNew2;
}
namespace Core {
	class EmulatorDigital;
	class EmulatorDigital2;
	class EmulatorDigital3;
	class IEmulatorDigital;
	class EmulatorAnalog;
}
//namespace Screen {
class ScreenWidget;
//}

class GData;
//class MenuTopInput;

namespace gsa
{
	//extern QString logFileName;
	extern core::Controller *controller;
}

namespace gsa {

namespace core {

   class Controller : public QWidget
   {
      Q_OBJECT

   public:
      explicit Controller(QWidget *parent = 0, int number = 401, float min = 0.0, float max = 1.0, float step = 1.0);
      ~Controller();

      void setFreqUnit(const TG::FreqUnits &freqUnit); 
      void setFreqCenter(const double &freqCenter); // {_freqCenter = freqCenter;}
      const double &freqCenter(void) { return _freqCenter; }
      void setFreqSpan(const double &freqSpan); // {_freqSpan = freqSpan;}
      const double &freqSpan(void) { return _freqSpan; }
      void setFreqStep(const double &freqStep); // {_freqStep = freqStep;}
      const double &freqStep(void) { return _freqStep; }
      void setFreqStart(double freqStart); // {_freqStart = freqStart;}
      const double &freqStart(void) { return _freqStart; }
      void setFreqStop(double freqStop); // {_freqStop = freqStop;}
      const double &freqStop(void) { return _freqStop; }
      void setFreqOffset(const double &freqOffset) { _freqOffset = freqOffset; }
      const double &freqOffset(void) { return _freqOffset; }

      int KeyPad(const TG::KeyPadParam &keyPadParam, int unitindex);
      void getSelection(TG::UnitTypes &type, int &index, double &value);
      void Double2String(QString &str, double value);

      Pad::KeyPadNew2 *keyPadNew2() {return _keyPadNew2;}

      bool _keyPad;

      double _freqCenter;
      double _freqSpan;
      double _freqStart;
      double _freqStop;
      double _freqStep;
      double _freqOffset;

      QPoint _position;
      QMap<TG::Exps, double> _expValue;

   private:
      Pad::KeyPadNew2 *_keyPadNew2;
   };

} // namespace core

} // namespace gsa

#endif // CONTROLLER

