// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef EMULATORDIGITAL2
#define EMULATORDIGITAL2

//#include <boost/container/vector.hpp>
#include <vector>

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QList>
#include <QVector>
#include <QQueue>
#include <QStringList>
#include <QSettings>
#include <QMutex>
#include <QtTest/QTest>

#include "gcore/core.h"
#include "gemulator/iemulatordigital.h"

namespace Core {
class Controller;
}
//namespace Screen {
class ScreenWidget;
//}

namespace Core {

class EmulatorDigital2 : public IEmulatorDigital //QObject
{
    Q_OBJECT

public:
    //explicit EmulatorDigital2(Controller *controller=0);
    explicit EmulatorDigital2(Core::Controller *controller, int number=501, double time=500.0, float min=0.0, float max=1.0, float step=1.0);
    ~EmulatorDigital2();

    int &current(void) const;
    void restartSweep(void);
    void setActiveTrace(const int &activeTrace);
    void setTypeTrace(const TG::TypeTrace &typeTrace);
    void fillTypeTraces(const std::vector<TG::TypeTrace> &typeTraces);

public:
//    void setDataArray(const boost::container::vector<float> dataArray);
//    boost::container::vector<float> dataArray() const;

//    const boost::container::vector<float> *dataArray() const {return &_dataArray1;}
//    const boost::container::vector<float> *dataArrayPrev() const {return &_dataArrayPrev;}
//    const boost::container::vector<int> *indexArray() const {return &_indexArray;}
    const std::vector<double> *dataArray1() const {return &_dataArray1;}
    const std::vector<double> *dataArrayPrev1() const {return &_dataArrayPrev1;}
    const std::vector<double> *dataTrace1() const {return &_dataTrace1;}
    const std::vector<double> *dataTrace2() const {return &_dataTrace2;}
    const std::vector<double> *dataTrace3() const {return &_dataTrace3;}
    const std::vector<double> *dataTrace4() const {return &_dataTrace4;}
    const std::vector<double> *dataTrace5() const {return &_dataTrace5;}
    const std::vector<double> *dataTrace6() const {return &_dataTrace6;}
    const std::vector<double> *dataTracePrev1() const {return &_dataTracePrev1;}
    const std::vector<double> *dataTracePrev2() const {return &_dataTracePrev2;}
    const std::vector<double> *dataTracePrev3() const {return &_dataTracePrev3;}
    const std::vector<double> *dataTracePrev4() const {return &_dataTracePrev4;}
    const std::vector<double> *dataTracePrev5() const {return &_dataTracePrev5;}
    const std::vector<double> *dataTracePrev6() const {return &_dataTracePrev6;}
    const std::vector<int> *indexArray() const {return &_indexArray;}

    void setCurrentData(const float data);
    float currentData(void) const;

    void setCurrent(const int &current);

    void setTimer(const float &time);
    const float &timer(void);

    void setSweepState(const TG::SweepStates &sweepStates);

    void setScreenWidget(const ScreenWidget *screenWidget) {_screenWidget = const_cast<ScreenWidget *>(screenWidget);}
    const ScreenWidget *screenWidget(void) {return _screenWidget;}

    void setMin(const double &min) {
        QMutexLocker ml(&mutex);
        _min = min;
    }
    const double &min_(void) {return _min;}

    void setMax(const double &max) {
        QMutexLocker ml(&mutex);
        _max = max;
    }
    const double &max_(void) {return _max;}

    void setNumber(const int &number) {
        QMutexLocker ml(&mutex);
        _number = number;
    }
    const int &number(void) {return _number;}

    void reset(void);

signals:
    void buttonClicked();
    void dataChanged();

    void finished(); 	/* сигнал о завершении  работы эмулятора */

public slots:
    void processTrace(void);
    void processTimer(void);

    void process(); /* запускает эмулятор */
    void stop(); /* останавливает эмулятор */

private:
    //boost::container::vector<float> _dataArray1;
    //boost::container::vector<float> _dataArrayPrev;
    //boost::container::vector<int> _indexArray;
    std::vector<double> _dataArray2;
    std::vector<double> _dataArrayPrev2;
    std::vector<double> _dataArray1;
    std::vector<double> _dataArrayPrev1;
    std::vector<double> _dataTrace1;
    std::vector<double> _dataTracePrev1;
    std::vector<double> _dataTrace2;
    std::vector<double> _dataTracePrev2;
    std::vector<double> _dataTrace3;
    std::vector<double> _dataTracePrev3;
    std::vector<double> _dataTrace4;
    std::vector<double> _dataTracePrev4;
    std::vector<double> _dataTrace5;
    std::vector<double> _dataTracePrev5;
    std::vector<double> _dataTrace6;
    std::vector<double> _dataTracePrev6;
    //int _currentArray;
    std::vector<int> _indexArray;
    std::vector<double> _dataTraceSum;
    std::vector<int> _dataCountSum;
    std::vector<std::vector<double>*> _dataTraces;
    std::vector<std::vector<double>*> _dataTracesPrev;
    std::vector<TG::TypeTrace> _typeTraces;
    QTimer *_timer;
    int _maxTraces;
    int _activeTrace;
    Core::Controller *_controller;
    ScreenWidget *_screenWidget;
    TG::SweepStates _sweepStates;

    double _min;
    double _max;
    double _step;
    double _minimum;
    double _maximum;
    double _curval;
    double _valuedev;
    int _number;
    int _begin;
    int _current;
    //int _total;
    double _time;
    bool _stop;
    bool ___temp___27febr;
    //bool _reset;
    //bool _push;
    //bool _overlay;
    int _overlay;
    QMutex mutex;
};

} // namespace Core

#endif // EMULATORDIGITAL2

