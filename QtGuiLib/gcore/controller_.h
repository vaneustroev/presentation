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
//#include "../gcore/controllervxi11.h"

//#include <../gpxa/PXAUserPreset/controllerpresets.h>
//#include <../gpxa/PXA_AntennEditor/controllerantenn.h>
//#include <../gpxa/PXAUserPreset/measuresettings.h>

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

//class IWidget : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit IWidget(QWidget *parent = 0);
//    virtual ~IWidget();

//    virtual void menuItemEdit(QString text) = 0;
//};

namespace gsa
{

	//extern QString logFileName;
	extern Core::Controller *controller;

}

namespace Core {

class Controller : public QWidget
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0, int number = 401, float min=0.0, float max=1.0, float step=1.0);
    ~Controller();

//public:
//
//    void StopThreads(void);
//    void __test(void);
//
//    void fillPreset(void);
//    void applyPreset(void);
//    void resetPreset(void);
//
//    void getVxi11Data(std::vector<double> &values);
//    //ControllerVxi11 *controllerVxi11() {return _controllerVxi11;}
//
//    //void reset(void);
//    QStringList &newText(void);
//    QStringList &stringList(void);
//    QStringList &currentText(const bool &inputText=false);
//    QStringList &currentXAxisUnits(void);
//    QStringList &currentYAxisUnits(void);
//
//    void acquire(void);
//    void release(void);
//
//    //void setDataArray(const boost::container::vector<float> dataArray);
//    //boost::container::vector<float> dataArray() const;
//    void setDataArray(const std::vector<double> dataArray);
//    std::vector<double> dataArray() const;
//
//    void setCurrentData(const float data);
//    float currentData(void) const;
//
//    void setCurrent(const int &current);
//    int &current(void) const;
//
//    void setNumber(const int &number);
//    int &number(void) const;
//
//    void setScreenState(TG::ScreenStates screenStates=TG::stateFreqCenter);
//    TG::ScreenStates screenState(void) {return _screenStates;}
//
//    void clearKeyPad(void);
//    void setKeyPad(const char &keypad);
//    void setKeyPadBkSp(void);
//    QByteArray &keyPad(void);
//
//    void pushButtonKeyPad(void);
//    void popButtonKeyPad(void);
//
//    void pushButton(const TG::Button &button, const bool &root, const TG::Moving &moving);
//    void setButton(const TG::Button &button);
//    TG::Button &button(void);
//    void buttonEnter(void);
//
//    void buttonKey(const TG::Button &button);
//
//    void loadMainParam();
//    void saveMainParam();
//    void loadAmptParam(TG::AmptParam &amptParam);
//    void saveAmptParam(TG::AmptParam &amptParam);
//
//    void initConverters(void);
//    void redrawTexts(void);
//
//    void initDisplayLine(void);
//    void setDisplayLine(const double &line, bool volt, bool first, bool vxi11);
//    void setChangedDisplayLine(int index=-1);
//    TG::DisplayLine *displayLines(void) {return &_displayLine;}
//    const bool &dispayLineOn(void) {return _displayParam._on;}
//    //const double &dispayLine(void) {return _displayParam._line;}
//    void setDisplayLog(bool displayLog = true);
//    bool displayLog(void) {return _amptParam.displayLog;}
//
//    void setDisplayLineOn(double line);
//    void setDisplayLineOff(void);
//    double setDisplayLineUnit2Volt(double unit);
//    double setDisplayLineVolt2Unit(double volt);
//    QString displayLineUnit(void);
//    QString dispayLineText(void);
//
//    bool displayLineIncMax(void);
//    double displayLineInc(double unit);
//    bool displayLineDecMin(void);
//    double displayLineDec(double unit);
//
//    double displayLineVolt2Index(double volt);
//    double displayLineIndex2Volt(double index);
//
//    void fractionAndExponent(double &fraction, double &exponent);
//    QString unitTexts(double &exponent);
//
//    void currentDown(bool bWheel=false);
//    void currentUp(bool bWheel=false);
//
//    void setSweep(const double &time, bool vxi11);
//    const double &sweep(void);
//    void setSweepAuto(bool hard=true);
//    const bool &sweepAuto(void);
//    void setSweepUnit(const TG::SweepUnits &sweepUnit) {_sweepUnit = sweepUnit;}
//    const TG::SweepUnits &sweepUnit(void) {return _sweepUnit;}
//    QString sweepUnitText(TG::SweepUnits sweepUnit=TG::sw_s) {if(sweepUnit==TG::sw_Undef) sweepUnit=_sweepUnit; return _sweepUnitsText[sweepUnit];}
//
//    void setBwUnit(const TG::FreqUnits &bwUnit);
//    const TG::FreqUnits &bwUnit(void) {return _bwUnit;}
//    QString bwUnitText(TG::FreqUnits bwUnit=TG::fr_Undef) {if(bwUnit==TG::fr_Undef) bwUnit=_bwUnit; return _freqUnitText[bwUnit];}
//    void setResBw(double &rbw, bool vxi11);
//    const double &resBw(void) {return _rbw;}
//    void setVideoBw(double &vbw, bool vxi11);
//    const double &videoBw(void) {return _vbw;}
//    const bool &resBwAuto(void) {return _bwParam._autoRbw;}
//    const bool &videoBwAuto(void) {return _bwParam._autoVbw;}
//    void setResBwAuto(bool hard=true); //setAutoRbw(void);
//    void setVideoBwAuto(bool hard=true); //setAutoVbw(void);
//
//    void setVbw3dbRbw(const double &value);
//    const double &vbw3dbRbw(void) {return _vbw3dbRbw;}
//    void setSpan3dbRbw(const double &value);
//    const double &span3dbRbw(void) {return _span3dbRbw;}
//    void setRbwFilterBw(const double &value);
//    const double &rbwFilterBw(void) {return _rbwFilterBw;}
//
//    void initYAxisRefLevl(void);
//    void initRefLevl(void);
//    void setRefLevl(double refLevl);
//    //{
//    //    _refLevl = refLevl;
//    //    _amptParam.refLevl = refLevl;
//    //    emit amptChanged(_amptParam);
//    //}
//    const double &refLevl(void) {
//        return _refLevl;
//    }
//    void setRefLevlUnit(const TG::RefLevlUnit &refLevlUnit);
//    //{
//    //    _refLevlUnit = refLevlUnit;
//    //    _amptParam.refLevlUnit = refLevlUnit;
//    //    //emit amptChanged(_amptParam);
//    //}
//    const TG::RefLevlUnit &refLevlUnit(void) {return _refLevlUnit;}
//    QString refLevlUnitText(void) {return _refLevlUnitText[_refLevlUnit];}
//
//    void setRefLevlOffset(const float &refLevlOffset) {
//        _refLevlOffset = refLevlOffset;
//        _amptParam.refLevlOffset = refLevlOffset;
//        emit amptChanged(_amptParam);
//    }
//    const double &refLevlOffset(void) {
//        return _refLevlOffset;
//    }
//
//    //void setYAxisScale(double yAxisScale) {_yAxisScale = yAxisScale;}
//    //double yAxisScale(void) {return _yAxisScale;}
//    void setScaleDev(double scaleDev) {_amptParam.scaleDev = scaleDev;}
//    double scaleDev(void) {return _amptParam.scaleDev;}
//    QString scaleDevUnitText(void) {return _amptParam.scaleDevUnitText;}
//    //QString scaleDevUnitText(void) {return _refLevlUnitText[_amptParam.scaleDevUnit];}
//
//    void putFreqParams(void);
//    void putAmptParams(void);
//    void putSweepParams(void);
//    void putBwParams(void);
//    void putDisplayParams(void);
//
    void setFreqUnit(const TG::FreqUnits &freqUnit); // {_freqUnit = freqUnit;}
//    const TG::FreqUnits &freqUnit(void) {return _freqUnit;}
//    QString freqUnitText(TG::FreqUnits freqUnit=TG::fr_Undef) {if(freqUnit==TG::fr_Undef) freqUnit=_freqUnit; return _freqUnitText[freqUnit];}

    void setFreqCenter(const double &freqCenter); // {_freqCenter = freqCenter;}
    const double &freqCenter(void) {return _freqCenter;}
    void setFreqSpan(const double &freqSpan); // {_freqSpan = freqSpan;}
    const double &freqSpan(void) {return _freqSpan;}
    void setFreqStep(const double &freqStep); // {_freqStep = freqStep;}
    const double &freqStep(void) {return _freqStep;}
    void setFreqStart(double freqStart); // {_freqStart = freqStart;}
    const double &freqStart(void) {return _freqStart;}
    void setFreqStop(double freqStop); // {_freqStop = freqStop;}
    const double &freqStop(void) {return _freqStop;}
    void setFreqOffset(const double &freqOffset) {_freqOffset = freqOffset;}
    const double &freqOffset(void) {return _freqOffset;}

//    //void setSpan(const float &span) {_span = span;}
//    //const float &span(void) {return _span;}
//
//    void setInputPreamp(const double &inputPreamp) {_inputPreamp = inputPreamp;}
//    const double &inputPreamp(void) {return _inputPreamp;}
//    //void setInputPreampUnit(const double &inputPreampUnit) {_inputPreampUnit = inputPreampUnit;}
//    QString inputPreampUnitText(void) {return "dB";}
//    void setInputAntenna(const bool &antenna); // {_antenna = antenna;}
//    const bool &inputAntenna(void) {return _antenna;}
//
//    //const EmulatorDigital2 *spectrumAnalyzer(void);
//    //void setSpectrumAnalyzer(const EmulatorDigital2 *emulatorDigital);
//    const EmulatorDigital2 *emulatorDigital2(void);
//    void setEmulatorDigital2(const EmulatorDigital2 *emulatorDigital);
//    const EmulatorDigital3 *emulatorDigital3(void);
//    void setEmulatorDigital3(const EmulatorDigital3 *emulatorDigital);
//
//    int internalEmulator(void) const {return _internalEmulator;}
//    void setInternalEmulator(const int internalEmulator) {_internalEmulator = internalEmulator;}
//
//    void setScreenWidget(const ScreenWidget *screenWidget);
//    ScreenWidget *screenWidget(void) const {return _screenWidget;}
//
//    void initMarkers(void);
//    void readMarkers(TG::MarkerParam &markerParam);
//    void writeMarkers(TG::MarkerParam &markerParam);
//    void setAllMarkersOff(void);
//    void setChangedMarkers(int index=-1);
//
//    void setMarker(const double &marker);
//    const float &marker(void);
//    //int currentMarker(void) (marker;)
//    void setMarkerToFreq(TG::MarkerToFreqType markerToFreqType);
//    //void setMarkers(const ScreenWidget *screenWidget) {_screenWidget = const_cast<ScreenWidget *>(screenWidget);}
//    //boost::container::map<int, TG::MarkerItem> *markers(void) {return &_markerArray;}
//    void setMarkers(TG::MarkerParam &markerParam);
//    std::map<int, TG::MarkerItem> *markers(void) {return &_markerArray;}
//    //boost::container::map<int, TG::MarkerItem> &markers(void) {return _markerArray;}
//    TG::MarkerType activeMarkerState(void);
//    void setActiveMarker(const int &activeMarker) {_activeMarker = activeMarker;}
//    int activeMarker(void) {return _activeMarker;}
//    void setValueMarker(const double &value) {_markerCurrent = value;}
//    double valueMarker(void);
//
//    void setMainMenu(const Menu::MainMenu3 *mainMenu);
//    Menu::MainMenu3 *mainMenu(void) const {return _mainMenu;}
//
//    const double &data(const TG::ScreenItemType &type);
//    const QString &unit(const TG::ScreenItemType &type);
//
//    void peakSearch(TG::PeakSearchType type);
//    int findNextPeak(void);
//    int findNextPkRight(void);
//    int findNextPkLeft(void);
//    int findMinSearch(void);
//    int findPkPkSearch(void);
//
//    void setIpAddress(const QString &ipAddress) {_ipAddress1 = ipAddress;}
//    const QString &ipAddress(void) {return _ipAddress1;}
//
//    static void testFunction(const std::pair<int, TG::MarkerItem> &p ) { Q_UNUSED(p); }
//
    int KeyPad(const TG::KeyPadParam &keyPadParam);
//    void pressButton(QString &button);
//    //int menuTopInput(void);
    void getSelection(TG::UnitTypes &type, int &index, double &value);
//    void getSelection(TG::UnitTypes &type, int &index, QString &text);
//    bool keyPadFlag(void) {return _keyPad;}
//
//    void userPreset(void);
//    void editAntenn(void);
//
//    const TG::SweepStates &sweepState(void) {return _sweepStates;}
//    void setSweepState(const TG::SweepStates &sweepStates);
//    void restartSweep(void);
//
//    void setFreq(void);
//    void setAmpt(void);
//    void setSweep(void);
//
//    double value0(void) {return _value0;}
//
//    void setAmptYAxis(const TG::AmptYAxis &yAxis);
//    TG::AmptYAxis &amptYAxis(void); // {return _amptParam.yAxis;}
//
//    void setActiveTrace(const int &activetrace);
//    int activeTrace(void);
//
//    void setTypeTrace(const TG::TypeTrace &typeTrace);
//    const TG::TypeTrace &typeTrace(void);
//    std::vector<TG::TypeTrace> &typeTraces(void);
//
//    void setTypeDetector(const TG::TypeDetector &typeDetector, bool hard=true);
//    const TG::TypeDetector &typeDetector(void);
//    std::vector<TG::TypeDetector> &typeDetectors(void);
//
//    void setAutoDetector(void);
//    void setAllAutoDetector(void);
//    bool autoDetector(void);
//    std::vector<bool> &autoDetectors(void);
//
//    void setFullSpan(bool hard=true);
//    void setZeroSpan(bool hard=true);
//
//    //void setNumber(const int &number) {
//    //    QMutexLocker ml(&mutex);
//    //    _number = number;
//    //}
//    //const int &number(void) {return _number;}
//
//    void restart(void);
//
//    void setDebug(int debug) {_debug = debug;}
//    int debug() {return _debug;}
//
//signals:
//    void buttonClicked();
//    void dataChanged();
//    void signalEditForm();
//    void signalEditAntenn();
//    void nameChange(QString name);
//
//signals:
//    void freqChanged(TG::FreqParam&);
//    void amptChanged(TG::AmptParam&);
//    void bwChanged(TG::BwParam&);
//    void sweepChanged(TG::SweepParam&);
//    void inputChanged(TG::InputParam&);
//    void displayChanged(TG::DisplayParam&);
//    void markerChanged(TG::MarkerParam&);
//    void traceChanged(TG::TraceParam&);
//
//    void menuChanged(TG::IndexMenu&);
//    void menuItemEdit(QString);
//    void menuSingleCont(void);
//    void menuSingleRestart(void);
//    void menuExit(void);
//
//    void screenStateChanged(TG::ScreenStates);
//
//public slots:
//    //void changeData();
//    void ShowAntennForm(void);
//    void presetsChanged(void);
//    void presetsReseted(void);
//    void keyPadPressed(int keyCode, quint32 nativeModifiers);
//
//private:
//    void initXAxisUnits(void);
//    void initYAxisUnits(void);
//
//private:
//    QSettings *_settings;
//    QSemaphore _sem;
//
//    int _internalEmulator;
//    //boost::container::vector<float> _dataArray;
//    std::vector<double> _dataArray2;
//    std::vector<double> _dataArray3;
//
//    //Core::ControllerVxi11 *_controllerVxi11;
//    Core::IEmulatorDigital *_iemulatorDigital;
//    Core::EmulatorDigital2 *_emulatorDigital2;
//    Core::EmulatorDigital3 *_emulatorDigital3;
//    Core::EmulatorAnalog *_emulatorAnalog;
//    ScreenWidget *_screenWidget;
//    Menu::MainMenu3 *_mainMenu;
    Pad::KeyPadNew2 *_keyPadNew2;

//    QThread *_threadEmulator2;
//    QThread *_threadEmulator3;
//    GData *_data;
//    //MenuTopInput *_menuTopInput;
//
//    int _number;
//    int _current;
//    int _activeTrace;
//    TG::Button _button;
//    QByteArray _keypad;
//    int _currentKeyPad;
//    int _bwIndex;
//
//    bool _zeroSpan;
    bool _keyPad;

//    double _value0;
//    double _temp;
//    double _time;
    double _freqCenter;
    double _freqSpan;
    double _freqStart;
    double _freqStop;
    double _freqStep;
    double _freqOffset;

//    double _inputPreamp;
//    bool _antenna;
//
//    double _rbw;
//    double _vbw;
//    double _vbw3dbRbw;
//    double _span3dbRbw;
//    double _rbwFilterBw;
//
//    //float _relativeValue;
//    double _refLevl;
//    double _refLevlOffset;
//    double _yAxisScale;
//    double _atten;
//    double _markerCurrent;
//    double _displayLineCurrent;
//    int _activeMarker;
//    int _maxMarker;
//    int _nextPeak;
//    int _nextPeakRight;
//    int _nextPeakLeft;
//    int _minSearch;
//    int _debug;
    QPoint _position;
//    QString _ipAddress1;
//    QString _ipAddress2;
//    TG::DeviceType _type1;
//    TG::DeviceType _type2;
//
//    TG::ScreenStates _screenStates;
//
//    TG::Exps _expFreq;
//    TG::Exps _expSweep;
//    TG::Exps _expBw;
//
//    TG::FreqUnits _freqUnit;
//    TG::FreqUnits _spanUnit;
//    TG::SweepUnits _sweepUnit;
//    TG::FreqUnits _bwUnit;
//    TG::AmptUnits _bwUnitAmpt;
//    TG::RefLevlUnit _refLevlUnit;
//    TG::Ref2LevlUnit _ref2LevlUnit;
//    TG::Ref2LevlUnit _attenUnit;
//    TG::SweepStates _sweepStates;
//    //QVector<TG::TraceModes> _traceModes;
//    std::vector<TG::TypeTrace> _typeTraces;
//    std::vector<TG::TypeDetector> _typeDetectors;
//    std::vector<bool> _autoDetectors;
//    int _maxTraces;
//
//    TG::FreqParam _freqParam;
//    TG::AmptParam _amptParam;
//    TG::SweepParam _sweepParam;
//    TG::BwParam _bwParam;
//    TG::DetectorParam _detectorsParam;
//    TG::DisplayParam _displayParam;
//    TG::MarkerParam _markerParam;
//
//    QMap<TG::FreqUnits, double> freqCoeff;
//    QMap<TG::SweepUnits, double> sweepCoeff;
//    //QMap<TG::FreqUnits, double> refLvlCoeff;
//    QVector<double> _bwStep;
//    QMap<double, QString> _unitText;
//    QMap<QString, double> _unitExponent;

    QMap<TG::Exps, double> _expValue;

//    QMap<TG::FreqUnits, QString> _freqUnitText;
//    QMap<TG::AmptUnits, QString> _amptUnitText;
//    QMap<TG::SweepUnits, QString> _sweepUnitsText;
//    QMap<TG::Ref2LevlUnit, QString> _ref2LevlUnitText;
//    //QMap<TG::Ref3LevlUnit, QString> _ref3LevlUnitText;
//    QMap<TG::RefLevlUnit, QString> _refLevlUnitText;
//
//    QMap<TG::FreqUnits, TG::Exps> _convertFreqUnit;
//    QMap<TG::SweepUnits, TG::Exps> _convertSweepUnit;
//
//    QMap<TG::Button, QMap<TG::Button, int> > _params;
//    QStringList _stringlist;
//    QStringList _xAxisUnits;
//    QStringList _yAxisUnits;
//    QStack<TG::Button> _buttonStack;
//    //boost::container::map<int, TG::MarkerItem> _markerArray;
//    std::map<int, TG::MarkerItem> _markerArray;
//    TG::DisplayLine _displayLine;
//
//    //Table::ControllerPresets *ctrl;
//    ////ControllerAntenn *ctr_ant;
//    //Table::MeasureSettings sett;

};

} // namespace Core

#endif // CONTROLLER

