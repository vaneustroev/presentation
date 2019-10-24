// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

// controller.cpp

//#include <QtWidgets>
//#include <QtOpenGL>

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic pop

namespace gsa
{

	//QString logFileName("");
	Core::Controller *controller(nullptr);

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

namespace Core {

Controller::Controller(QWidget *parent, int number, float min, float max, float step)
    : QWidget(parent)
    //, _settings(new QSettings( "./gsa.ini", QSettings::IniFormat ))
    //, _sem(1)
    //, _internalEmulator(0)
    //, _iemulatorDigital(nullptr)
    //, _emulatorDigital2(nullptr)
    //, _emulatorDigital3(nullptr)
    //, _emulatorAnalog(nullptr)
    //, _mainMenu(nullptr)
    //, _threadEmulator2(nullptr)
    //, _threadEmulator3(nullptr)
    , _keyPadNew2(nullptr)
    ////, _controllerVxi11(nullptr)
    //, _number(number)
    //, _current(0)
    //, _activeTrace(0)
    //, _button(TG::button00)
    //, _currentKeyPad(0)
    //, _bwIndex(0)
    //, _zeroSpan(false)
    , _keyPad(false)
    //, _value0(1.0)
    //, _time(0.0)
    ////, _value0(((max-min)*step)/10.0)
    //, _freqCenter(750.0)
    //, _freqSpan(1500.0)
    //, _freqStart(_freqCenter - _freqSpan/2)
    //, _freqStop(_freqCenter + _freqSpan/2)
    //, _freqStep((_freqStop-_freqStart)/40)
    //, _freqOffset(0.0)
    //, _inputPreamp(0.0)
    //, _antenna(false)
    //, _rbw(1.0)
    //, _vbw(1.0)
    //, _vbw3dbRbw(1.0)
    //, _span3dbRbw(1.0)
    //, _rbwFilterBw(1.0)
    //, _refLevl(0.0)
    //, _refLevlOffset(0.0)
    //, _yAxisScale(200.0)
    //, _atten(0.0)
    //, _markerCurrent(0.0)
    //, _displayLineCurrent(0.0)
    //, _activeMarker(0)
    //, _maxMarker(4)
    //, _nextPeak(0)
    //, _nextPeakRight(0)
    //, _nextPeakLeft(0)
    //, _minSearch(0)
    //, _debug(0)
    , _position(200, 200)
    ////, _ipAddress("192.168.70.35")
    //, _screenStates(TG::stateFreqCenter)
    //, _expFreq(TG::exp_M)
    //, _expSweep(TG::exp_m)
    //, _expBw(TG::exp_M)
    //, _freqUnit(TG::fr_MHz)
    //, _spanUnit(TG::fr_MHz)
    //, _sweepUnit(TG::sw_ms)
    //, _bwUnit(TG::fr_kHz)
    //, _bwUnitAmpt(TG::ampt_dB)
    //, _refLevlUnit(TG::ref_dBm)
    //, _ref2LevlUnit(TG::ref2_dBm)
    //, _attenUnit(TG::ref2_dB)
    //, _sweepStates(TG::sweepContinuous)
    ////, _traceModes(TG::traceClear)
    //, _maxTraces(6)
{
    gsa::controller = this;
    //setDebug(256);

    //_sem.acquire(1);

    //initConverters();

    ////qInfo("Step 001 ");
    //loadMainParam();
    //loadAmptParam(_amptParam);

    ////TG::MarkerType type = this->markers()->at(0).type2;
    ////Q_UNUSED(type)

    //if(_internalEmulator != 0) {

    //    _time = 500.0;

    //    _freqParam._expFreq = _expFreq;
    //    _freqParam._center = _freqCenter * _expValue[_expFreq];
    //    _freqParam._span = _freqSpan * _expValue[_expFreq];
    //    _freqParam._start = _freqStart * _expValue[_expFreq];
    //    _freqParam._stop = _freqStop * _expValue[_expFreq];
    //    _freqParam._step = _freqStep * _expValue[_expFreq];

    //    _freqParam._zeroSpan = _zeroSpan;

    //    _sweepParam._time = _time * _expValue[_expSweep];
    //    _sweepParam._points = _number;

    //    _bwParam.resBw = _rbw * _expValue[_convertFreqUnit[_bwUnit]];
    //    _bwParam.videoBw = _vbw * _expValue[_convertFreqUnit[_bwUnit]];

    //    _displayParam._volt = 0.236;

    //    _bwParam._autoRbw = 0.0;
    //    _bwParam._autoVbw = 0.0;

    //    _displayParam._on = true;
    //    _sweepParam._auto = true;
    //    //_activeTrace;
    //    //_autoDetectors[_activeTrace];
    //    //TG::DetectorParam detectorParam;
    //    //detectorParam._typeDetectors.push_back(TG::detectorApeak);
    //    //detectorParam._autoDetectors.push_back(true);
    //    //_autoDetectors.clear();
    //    //_autoDetectors = _detectorsParam._autoDetectors;
    //    //_autoDetectors[_activeTrace];

    //    initMarkers();

    //} else {

    //    ////qInfo("Step 002 ");
    //    //_controllerVxi11 = new ControllerVxi11();
    //    //if(_controllerVxi11->Init(_ipAddress)) {
    //    //    //qInfo("Step 003 ");
    //    //    _controllerVxi11->Free();
    //    //    delete _controllerVxi11;
    //    //    _controllerVxi11 = nullptr;
    //    //}
    //    //if(_controllerVxi11 != nullptr) {
    //    //    //qInfo("Step 004 ");

    //    //    _controllerVxi11->getFreqParam(_freqParam);
    //    //    _controllerVxi11->getAmptParam(_amptParam);
    //    //    _controllerVxi11->getSweepParam(_sweepParam);
    //    //    _controllerVxi11->getBwParam(_bwParam);
    //    //    _controllerVxi11->getDetectorsParam(_detectorsParam);
    //    //    _controllerVxi11->getDisplayParam(_displayParam);
    //    //    _controllerVxi11->getMarkerParam(_markerParam);

    //    //    //double fraction( _freqParam.center );
    //    //    //double exponent( 0.0 );
    //    //    //fractionAndExponent(fraction, exponent);
    //    //    //QString unitText = _unitText[exponent];

    //    //    _freqParam._expFreq = _expFreq;
    //    //    _freqCenter = _freqParam._center / _expValue[_expFreq];
    //    //    _freqSpan = _freqParam._span / _expValue[_expFreq];
    //    //    _freqStart = _freqParam._start / _expValue[_expFreq];
    //    //    _freqStop = _freqParam._stop / _expValue[_expFreq];
    //    //    _freqStep = _freqParam._step / _expValue[_expFreq];

    //    //    _zeroSpan = _freqParam._zeroSpan;

    //    //    //_sweepParam._time;
    //    //    //_number;

    //    //    //exponent = 0.0;
    //    //    //fractionAndExponent(_freqParam.center, exponent);
    //    //    //exponent = 0.0;
    //    //    //fractionAndExponent(_freqParam.span, exponent);
    //    //    //exponent = 0.0;
    //    //    //fractionAndExponent(_freqParam.start, exponent);
    //    //    //exponent = 0.0;
    //    //    //fractionAndExponent(_freqParam.stop, exponent);

    //    //    //double fsweep1 = _sweepParam._time;
    //    //    //double fsweep2 = _expValue[_expSweep];
    //    //    _time = _sweepParam._time / _expValue[_expSweep];
    //    //    _number = _sweepParam._points;

    //    //    _rbw = _bwParam.resBw / _expValue[_convertFreqUnit[_bwUnit]];
    //    //    _vbw = _bwParam.videoBw / _expValue[_convertFreqUnit[_bwUnit]];

    //    //    _autoDetectors.clear();
    //    //    _autoDetectors = _detectorsParam._autoDetectors;
    //    //    _typeDetectors.clear();
    //    //    _typeDetectors = _detectorsParam._typeDetectors;

    //    //    //qInfo("Step 005 ");
    //    //    initMarkers();
    //    //    readMarkers(_markerParam);
    //    //    setDisplayLine(_displayParam._volt, true, true, false);
    //    //}
    //}

    //qInfo("Step 006 ");
    _keyPadNew2 = new Pad::KeyPadNew2(parent); //(this);
    QDesktopWidget *desktop(QApplication::desktop());
    QRect rect = desktop->screenGeometry(0);
    //_keyPadNew2->move(_position.x(), _position.y());
    _keyPadNew2->move(rect.x()+100, rect.y()+100);

    ////_params[TG::buttonFreq][TG::button00];
    ////connect(_emulatorDigital2, SIGNAL(dataChanged()), this, SLOT(changeData()));

    ////_emulatorDigital = new EmulatorDigital(this, _number);
    //_emulatorAnalog = new Core::EmulatorAnalog(this);
    ////_dataArray1 = _emulatorDigital->dataArray();

    ////qInfo("Step 007 ");
    //initXAxisUnits();
    //initYAxisUnits();
    //initDisplayLine();

    ////qInfo("Step 008 ");
    //if(_internalEmulator != 0) {

    //    _emulatorDigital2 = new EmulatorDigital2(this, _number, _time, min, max, step);
    //    _iemulatorDigital = _emulatorDigital2;
    //    _iemulatorDigital->fillTypeTraces(_typeTraces);
    //    _dataArray2 = *(_emulatorDigital2->dataArray1());
    //    _threadEmulator2 = new QThread;
    //    _emulatorDigital2->moveToThread(_threadEmulator2);

    //    //qInfo("Step 009 ");
    //    connect(_threadEmulator2, SIGNAL(started()), _emulatorDigital2, SLOT(process()));
    //    connect(_emulatorDigital2, SIGNAL(finished()), _threadEmulator2, SLOT(quit()));

    //    //pid_t tid;
    //    //tid = syscall(SYS_gettid);
    //    //pthread_t pth = pthread_self();

    //    //QString str = QString("while() 2 tid=%1 %2 ").arg(tid).arg(pth);
    //    //qInfo(str.toStdString().c_str());

    //    _threadEmulator2->start();

    //} else {

    //    //if(_controllerVxi11 != nullptr) {
    //    //    _emulatorDigital3 = new EmulatorDigital3(this, _number, min, max, step);
    //    //    _iemulatorDigital = _emulatorDigital3;
    //    //    _iemulatorDigital->fillTypeTraces(_typeTraces);
    //    //    _dataArray3 = *(_emulatorDigital3->dataArray1());
    //    //    _threadEmulator3 = new QThread;
    //    //    _emulatorDigital3->moveToThread(_threadEmulator3);

    //    //    //qInfo("Step 010 ");
    //    //    connect(_threadEmulator3, SIGNAL(started()), _emulatorDigital3, SLOT(process()));
    //    //    //connect(_emulatorDigital3, SIGNAL(finished()), _threadEmulator3, SLOT(quit()));
    //    //    //connect(_emulatorDigital3, SIGNAL(finished()), _threadEmulator3, SLOT(terminate()));

    //    //    _threadEmulator3->start();

    //    //}
    //}

    ////qInfo("Step 011 ");
    //fillPreset();

    //////ControllerPresets
    ////#ifdef Q_OS_LINUX
    //////ctrl = new ControllerPresets( "//home//andy//", sett); //user preset
    ////ctrl = new Table::ControllerPresets( "//home//van//", sett); //user preset
    ////#else
    ////ctrl = new Table::ControllerPresets( "c:\\", sett);
    ////#endif
    //////connect( ui->pushButton, SIGNAL(clicked()), this, SLOT(save()));
    ////connect( this, SIGNAL(signalEditForm()), ctrl, SLOT(ShowEditForm())); //user preset

    //////ControllerAntenn
    ////#ifdef Q_OS_LINUX
    ////    //ctr_ant = new ControllerAntenn( "//home//andy//"); //input corr Edit Correction
    ////#else
    ////    //ctr_ant = new ControllerAntenn( "d:\\");
    ////#endif
    ////    //connect( ui->actionAntennEdit, SIGNAL(triggered()), ctr_ant, SLOT(ShowEditForm()));
    ////    //connect( this, SIGNAL(signalEditAntenn()), ctr_ant, SLOT(ShowEditForm())); //edit antenn
    //connect( this, SIGNAL(signalEditAntenn()), this, SLOT(ShowAntennForm())); //edit antenn

    ////connect( ctrl, SIGNAL(presetsChange()), this, SLOT(presetsChanged()));
    ////connect( ctrl, SIGNAL(presetsReset()), this, SLOT(presetsReseted()));

    ////qInfo("Step 012 ");
}

Controller::~Controller()
{
    //_emulatorDigital2->stop();

    //if(_internalEmulator != 0) {
    //    _threadEmulator2->wait(2000);

    //    delete _threadEmulator2;
    //    delete _emulatorDigital2;
    //} else {
    //    //if(_controllerVxi11 != nullptr) {
    //    //    _threadEmulator3->wait(2000);

    //    //    delete _threadEmulator3;
    //    //    delete _emulatorDigital3;

    //    //    writeMarkers(_markerParam);

    //    //    _freqParam._expFreq = _expFreq;
    //    //    _freqParam._center = _freqCenter * _expValue[_expFreq];
    //    //    _freqParam._span = _freqSpan * _expValue[_expFreq];
    //    //    _freqParam._start = _freqStart * _expValue[_expFreq];
    //    //    _freqParam._stop = _freqStop * _expValue[_expFreq];
    //    //    _freqParam._selectFreq = TG::unselFreq;

    //    //    _controllerVxi11->putFreqParam(_freqParam);
    //    //    _controllerVxi11->putSweepParam(_sweepParam);
    //    //    _controllerVxi11->putBwParam(_bwParam);
    //    //    //_controllerVxi11->putDetectorsParam(_detectorsParam);
    //    //    //_controllerVxi11->putDisplayParam(_displayParam);
    //    //    _controllerVxi11->putMarkerParam(_markerParam);

    //    //    delete _controllerVxi11;
    //    //}
    //}

    //saveAmptParam(_amptParam);
    //saveMainParam();

    //delete _settings;

}

//void Controller::acquire(void)
//{
//    _sem.acquire(1);
//}
//
//void Controller::release(void)
//{
//    _sem.release(1);
//}
//
//void Controller::__test(void)
//{
//    //_emulatorDigital2 = new EmulatorDigital2(this, 100, 1, 100, 1);
//    //_iemulatorDigital = _emulatorDigital2;
//    //_iemulatorDigital->fillTypeTraces(_typeTraces);
//    //_dataArray2 = *(_emulatorDigital2->dataArray1());
//    //_threadEmulator2 = new QThread;
//    //_emulatorDigital2->moveToThread(_threadEmulator2);
//
//    //qInfo("Step 009 ");
//    //connect(_threadEmulator2, SIGNAL(started()), _emulatorDigital2, SLOT(process()));
//    //connect(_emulatorDigital2, SIGNAL(finished()), _threadEmulator2, SLOT(quit()));
//
//    //_threadEmulator2->start();
//}
//
//void Controller::StopThreads(void)
//{
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->stop();
//
//    if(_internalEmulator != 0) {
//        if(_emulatorDigital2!=nullptr) _emulatorDigital2->stop();
//    } else {
//        if(_emulatorDigital3!=nullptr) _emulatorDigital3->stop();
//    }
//
//    if(_threadEmulator3 != nullptr) _threadEmulator3->quit();
//
//    //qInfo("INFO004 ");
//
//    //QTest::qSleep(300);
//
//    QCoreApplication::exit(0);
//}
//
//void Controller::userPreset(void)
//{
//    //sett.SetMeasMode( source.GetMeasMode() );
//
//    //sett.SetCentralFreqMHz( _freqCenter );
//    //sett.SetStartFreqMHz( _freqStart );
//    //sett.SetStopFreqMHz( _freqStop );
//    //sett.SetSpanFreqMHz( _freqSpan );
//    //sett.SetStepFreqMHz( _freqStep );
//
//    //sett.SetAmptRelativeValue(_refLevl);
//    ////sett.SetAmptRelativeValue(_refLevlOffset);
//
//    //sett.SetSweepTime(_sweepParam._time);
//
//    //sett.SetResBw(_rbw);
//    //sett.SetVideoBw(_vbw);
//    //sett.SetDisplayLineVolt(_displayLineCurrent);
//
//    emit signalEditForm();
//}
//
//void Controller::fillPreset(void)
//{
//    //sett.SetSettingsName("Name");
//    //sett.SetMeasMode(Table::spectrum);
//
//    //sett.SetCentralFreqMHz(_freqParam._center / _expValue[_expFreq]);
//    //sett.SetStartFreqMHz(_freqParam._start / _expValue[_expFreq]);
//    //sett.SetStopFreqMHz(_freqParam._stop / _expValue[_expFreq]);
//    //sett.SetSpanFreqMHz(_freqParam._span / _expValue[_expFreq]);
//    //sett.SetStepFreqMHz(_freqParam._step / _expValue[_expFreq]);
//
//    //sett.SetAmptRelativeValue(_amptParam.relativeValue);
//    //sett.SetSweepTime(_sweepParam._time);
//    //sett.SetResBw(_bwParam.resBw);
//    //sett.SetVideoBw(_bwParam.videoBw);
//    //sett.SetDisplayLineVolt(_displayParam._volt);
//
//    //sett.SetMarkers(_markerParam._markers);
//    _detectorsParam;
//}
//
//void Controller::applyPreset(void)
//{
//    //QString name = sett.GetSettingsName();
//    //Table::ModeMeas spectrum = sett.GetMeasMode();
//
//    //_freqParam._expFreq = _expFreq;
//    //_freqParam._center = sett.GetCentralFreqMHz() * _expValue[_expFreq];
//    //_freqParam._start = sett.GetStartFreqMHz() * _expValue[_expFreq];
//    //_freqParam._stop = sett.GetStopFreqMHz() * _expValue[_expFreq];
//    //_freqParam._span = sett.GetSpanFreqMHz() * _expValue[_expFreq];
//    //_freqParam._step = sett.GetStepFreqMHz() * _expValue[_expFreq];
//
//    //_amptParam.relativeValue = sett.GetAmptRelativeValue();
//    //_sweepParam._time = sett.GetSweepTime();
//    //_bwParam.resBw = sett.GetResBw();
//    //_bwParam.videoBw = sett.GetVideoBw();
//    //_displayParam._volt = sett.GetDisplayLineVolt();
//
//    //_markerParam._markers = sett.GetMarkers();
//    _detectorsParam;
//}
//
//void Controller::resetPreset(void)
//{
//    //QString name = sett.GetSettingsName();
//    //ModeMeas spectrum = sett.GetMeasMode();
//
//    _freqParam._expFreq = _expFreq;
//    _freqParam._center = 1500; //sett.GetCentralFreqMHz() * _expValue[_expFreq];
//    _freqParam._start = 0; //sett.GetStartFreqMHz() * _expValue[_expFreq];
//    _freqParam._stop = 3000; //sett.GetStopFreqMHz() * _expValue[_expFreq];
//    _freqParam._span = 3000; //sett.GetSpanFreqMHz() * _expValue[_expFreq];
//    _freqParam._step = 10; //sett.GetStepFreqMHz() * _expValue[_expFreq];
//
//    _amptParam.relativeValue = 0.236; //sett.GetAmptRelativeValue();
//    _sweepParam._time = 0.5; //sett.GetSweepTime();
//    _bwParam.resBw = 3; //sett.GetResBw();
//    _bwParam.videoBw = 3; //sett.GetVideoBw();
//    _displayParam._volt = 0.236; //sett.GetDisplayLine();
//
//    //_markerParam._markers = sett.GetMarkers();
//    _detectorsParam;
//}
//
//void Controller::initConverters(void)
//{
//    _freqUnitText[TG::fr_Undef] = QString("");
//    _freqUnitText[TG::fr_GHz] = QString("GHz");
//    _freqUnitText[TG::fr_MHz] = QString("MHz");
//    _freqUnitText[TG::fr_kHz] = QString("kHz");
//    _freqUnitText[TG::fr_Hz] = QString("Hz");
//
//    _amptUnitText[TG::ampt_Undef] = QString("");
//    _amptUnitText[TG::ampt_dB] = QString("dB");
//
//    freqCoeff[TG::fr_Undef] = 1e+0;
//    freqCoeff[TG::fr_GHz] = 1e+9;
//    freqCoeff[TG::fr_MHz] = 1e+6;
//    freqCoeff[TG::fr_kHz] = 1e+3;
//    freqCoeff[TG::fr_Hz] = 1e+0;
//
//    //sweepCoeff[TG::sw_Undef] = 1e+0;
//    sweepCoeff[TG::sw_ks] = 1e+3;
//    sweepCoeff[TG::sw_s] = 1e+0;
//    sweepCoeff[TG::sw_ms] = 1e-3;
//    sweepCoeff[TG::sw_mks] = 1e-6;
//    sweepCoeff[TG::sw_ns] = 1e-9;
//
//    _bwStep.push_back(1.0);
//    _bwStep.push_back(3.0);
//    _bwStep.push_back(10.0);
//    _bwStep.push_back(100.0);
//    _bwStep.push_back(200.0);
//    _bwStep.push_back(300.0);
//    _bwStep.push_back(1000.0);
//    _bwStep.push_back(3000.0);
//    _bwStep.push_back(10000.0);
//
//    _bwIndex = _bwStep.length()-1;
//    _rbw = _bwStep[_bwIndex];
//    _vbw = _bwStep[_bwIndex];
//    _bwUnit = TG::fr_kHz;
//
//    _sweepUnitsText[TG::sw_Undef] = QString("");
//    _sweepUnitsText[TG::sw_ks] = QString("ks");
//    _sweepUnitsText[TG::sw_s] = QString("s");
//    _sweepUnitsText[TG::sw_ms] = QString("ms");
//    _sweepUnitsText[TG::sw_mks] = QString("mks");
//    _sweepUnitsText[TG::sw_ns] = QString("ns");
//
//    _ref2LevlUnitText[TG::ref2_Undef] = QString("");
//    _ref2LevlUnitText[TG::ref2_dB] = QString("dB");
//    _ref2LevlUnitText[TG::ref2_dBm] = QString("dBm");
//    _ref2LevlUnitText[TG::ref2_dBmV] = QString("dBmV");
//    _ref2LevlUnitText[TG::ref2_dBmkV] = QString("dBmkV");
//    _ref2LevlUnitText[TG::ref2_dBmkA] = QString("dBmkA");
//    _ref2LevlUnitText[TG::ref2_Watts] = QString("Watts");
//    _ref2LevlUnitText[TG::ref2_Volts] = QString("Volts");
//    _ref2LevlUnitText[TG::ref2_Amps] = QString("Amps");
//
//    //_ref3LevlUnitText[TG::ref2_Undef] = QString("");
//    //_ref3LevlUnitText[TG::ref2_dBmV] = QString("dBmV");
//    //_ref3LevlUnitText[TG::ref2_dBmkV] = QString("dBmkV");
//    //_ref3LevlUnitText[TG::ref2_Volts] = QString("Volts");
//    //_ref3LevlUnitText[TG::ref2_Watts] = QString("Watts");
//
//    //_refLevlUnitText[TG::ref_Undef] = QString("");
//    //_refLevlUnitText[TG::ref_dBm] = QString("dBm");
//    //_refLevlUnitText[TG::ref_ndBm] = QString("-dBm");
//    //_refLevlUnitText[TG::ref_m] = QString("m");
//    //_refLevlUnitText[TG::ref_mk] = QString("mk");
//    //_refLevlUnitText[TG::ref_n] = QString("n");
//
//    _refLevlUnitText[TG::ref_Undef] = QString("");
//    _refLevlUnitText[TG::ref_dBm] = QString("dBm");
//    _refLevlUnitText[TG::ref_dBmV] = QString("dBmV");
//    _refLevlUnitText[TG::ref_Watt] = QString("W");
//    _refLevlUnitText[TG::ref_Volt] = QString("V");
//
//    _unitText[9.0] = "G";
//    _unitText[6.0] = "M";
//    _unitText[3.0] = "k";
//    _unitText[0.0] = "";
//    _unitText[-3.0] = "m";
//    _unitText[-6.0] = "mk";
//    _unitText[-9.0] = "n";
//    _unitText[-12.0] = "p";
//    _unitText[-15.0] = "f";
//    _unitText[-18.0] = "a";
//    _unitText[-21.0] = "z";
//    _unitText[-24.0] = "y";
//
//    _unitExponent["G"] = 9.0;
//    _unitExponent["M"] = 6.0;
//    _unitExponent["k"] = 3.0;
//    _unitExponent[""] = 0.0;
//    _unitExponent["m"] = -3.0;
//    _unitExponent["mk"] = -6.0;
//    _unitExponent["n"] = -9.0;
//    _unitExponent["p"] = -12.0;
//    _unitExponent["f"] = -15.0;
//    _unitExponent["a"] = -18.0;
//    _unitExponent["z"] = -21.0;
//    _unitExponent["y"] = -24.0;
//
//    _expValue[TG::exp_G] = 1e+9;
//    _expValue[TG::exp_M] = 1e+6;
//    _expValue[TG::exp_k] = 1e+3;
//    _expValue[TG::exp_] = 1e+0;
//    _expValue[TG::exp_m] = 1e-3;
//    _expValue[TG::exp_mk] = 1e-6;
//    _expValue[TG::exp_n] = 1e-9;
//    _expValue[TG::exp_p] = 1e-12;
//    _expValue[TG::exp_f] = 1e-15;
//    _expValue[TG::exp_a] = 1e-18;
//    _expValue[TG::exp_z] = 1e-21;
//    _expValue[TG::exp_y] = 1e-24;
//
//    _convertFreqUnit[TG::fr_GHz] = TG::exp_G;
//    _convertFreqUnit[TG::fr_MHz] = TG::exp_M;
//    _convertFreqUnit[TG::fr_kHz] = TG::exp_k;
//    _convertFreqUnit[TG::fr_Hz] = TG::exp_;
//
//    _convertSweepUnit[TG::sw_ks] = TG::exp_k;
//    _convertSweepUnit[TG::sw_s] = TG::exp_;
//    _convertSweepUnit[TG::sw_ms] = TG::exp_m;
//    _convertSweepUnit[TG::sw_mks] = TG::exp_mk;
//    _convertSweepUnit[TG::sw_ns] = TG::exp_n;
//
//    for(int i=0; i<_maxTraces; i++) {
//        _typeTraces.push_back(TG::traceBlank);
//    }
//    _typeTraces[0] = TG::traceClear;
//
//    for(int i=0; i<_maxTraces; i++) {
//        _typeDetectors.push_back(TG::detectorApeak);
//    }
//    for(int i=0; i<_maxTraces; i++) {
//        _autoDetectors.push_back(false);
//    }
//}
//
//void Controller::loadMainParam()
//{
//    //_settings->setPath();
//
//    _internalEmulator = _settings->value("Main/InternalEmulator", _internalEmulator).toInt();
//    //_ipAddress = _settings->value("Main/IpAddress", _ipAddress).toString();
//    _debug = _settings->value("Main/Debug", _debug).toInt();
//
//    //saveMainParam();
//    //int i(0);
//}
//
//void Controller::saveMainParam()
//{
//    _settings->setValue("Main/InternalEmulator", _internalEmulator);
//    //_settings->setValue("Main/IpAddress", _ipAddress);
//    _settings->setValue("Main/Debug", _debug);
//}
//
//void Controller::loadAmptParam(TG::AmptParam &amptParam)
//{
//    QString DisplayScale = _settings->value("Amplitude/DisplayScale", "Log").toString();
//    if(DisplayScale == QString("Log")) {
//        //amptParam.amptMode = TG::amptModeLog;
//        amptParam.displayLog = true;
//    } else if(DisplayScale == QString("Lin")) {
//        //amptParam.amptMode = TG::amptModeLin;
//        amptParam.displayLog = false;
//    }
//
//    amptParam.yAxis = static_cast<TG::AmptYAxis>(_settings->value("Amplitude/YAxis", "3").toInt());
//    if(amptParam.yAxis < 0) amptParam.yAxis = TG::yAxisdBm;
//    else if(amptParam.yAxis > 3) amptParam.yAxis = TG::yAxisVolt;
//
//    amptParam.relativeUnit = TG::relativeVolt;
//    //amptParam.relativeValueHard = pow(1.0 * 1e-3 * 50.0, 0.5);
//    //amptParam.relativeValue = amptParam.relativeValueHard;
//    amptParam.relativeValue = pow(1.0 * 1e-3 * 50.0, 0.5); //Convert from 1 mWatt to Volt
//    amptParam.relativeValue = _settings->value("Amplitude/RelativeValue", QString("%1").arg(amptParam.relativeValue, 0, 'f', 15)).toDouble();
//
//    amptParam.scaleDev = 20.0;
//    amptParam.scaleDevUnitText = QString("dB");
//
//    double ftemp = 10.0*(double)log10(((double)pow(amptParam.relativeValue, 2.0) / 50.0)/1e-3);
//    Q_UNUSED(ftemp)
//
//    initRefLevl();
//    initYAxisUnits();
//
//}
//
//void Controller::saveAmptParam(TG::AmptParam &amptParam)
//{
//    QString DisplayScale("Log");
//    //if(amptParam.amptMode == TG::amptModeLog) {
//    if(amptParam.displayLog == true) {
//        DisplayScale = QString("Log");
//    //} else if(amptParam.amptMode == TG::amptModeLin) {
//    } else if(amptParam.displayLog == false) {
//        DisplayScale = QString("Lin");
//    }
//    _settings->setValue("Amplitude/DisplayScale", DisplayScale);
//
//    _settings->setValue("Amplitude/YAxis", QString("%1").arg(static_cast<TG::AmptYAxis>(amptParam.yAxis)));
//
//    _settings->setValue("Amplitude/RelativeValue", QString("%1").arg(amptParam.relativeValue, 0, 'f', 15));
//    if( amptParam.relativeUnit == TG::relativeVolt ) {
//        _settings->setValue("Amplitude/RelativeUnit", QString("%1").arg("Volt"));
//    } else if( amptParam.relativeUnit == TG::relativeWatt ) {
//        _settings->setValue("Amplitude/RelativeUnit", QString("%1").arg("Watt"));
//    }
//}
//
//void Controller::setScreenWidget(const ScreenWidget *screenWidget)
//{
//    _screenWidget = const_cast<ScreenWidget *>(screenWidget);
//    setAmptYAxis(_amptParam.yAxis);
//
//    //double unitMax = _screenWidget->unitUp();
//    //double unitMin = _screenWidget->unitDown();
//    setDisplayLine(_displayParam._volt, true, true, false);
//
//    _screenWidget->fillTypeTraces(_typeTraces);
//
//}
//
//void Controller::setInputAntenna(const bool &antenna)
//{
//    _antenna = antenna;
//
//    _screenWidget->setInputAntenna(_antenna);
//}
//
//void Controller::getVxi11Data(std::vector<double> &values)
//{
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->getData(values);
//}
//
//QStringList &Controller::newText(void)
//{
//    _stringlist.clear();
//
//    if(_mainMenu == nullptr) return _stringlist;
//
//    QSharedPointer<SAItem> menuitem;
//
//    menuitem = _mainMenu->menuCurrent()->parent();
//
//    //TG::Button button1 = menuitem->activeButton();
//    //std::string text = menuitem->child(menuitem->activeButton())->text();
//
//    _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//    _stringlist.push_back(QString("%1").arg(keyPad().toStdString().c_str()));
//
//    return _stringlist;
//}
//
//QStringList &Controller::stringList(void)
//{
//    return _stringlist;
//}
//
//QStringList &Controller::currentXAxisUnits(void)
//{
//    return _xAxisUnits;
//}
//
//QStringList &Controller::currentYAxisUnits(void)
//{
//    return _yAxisUnits;
//}
//
//QStringList &Controller::currentText(const bool &inputText)
//{
//    _stringlist.clear();
//
//    if(_mainMenu == nullptr) return _stringlist;
//
//    QSharedPointer<SAItem> menuitem;
//    if(inputText) {
//        menuitem = _mainMenu->menuCurrent()->parent();
//    } else {
//        menuitem = _mainMenu->menuCurrent();
//    }
//
//    _stringlist.clear();
//    if(menuitem == nullptr) return _stringlist;
//
//    _button = menuitem->activeButton();
//
//    //TG::Button _button1 = menuitem->button();
//    //TG::Button _button2 = menuitem->activeButton();
//    //TG::Types type1 = menuitem->type();
//    //TG::Types type2 = menuitem->child(menuitem->activeButton())->type();
//
//    if(menuitem->children().find(menuitem->activeButton())==menuitem->children().end()) {
//        return _stringlist;
//    }
//
//    std::string name1 = menuitem->child(menuitem->activeButton())->name();
//    Q_UNUSED(name1)
//
//    //QString str( QString("name1=%1 ").arg(name1.c_str()) );
//    //qInfo(str.toStdString().c_str());
//    //QMessageLogger("QT_MESSAGELOG_FILE", 0, "QT_MESSAGELOG_FUNC").info;
//
//    TG::Button button2 = menuitem->button();
//    TG::Button button3 = menuitem->parent()->button();
//    Q_UNUSED(button2)
//    Q_UNUSED(button3)
//
//    if(menuitem->button() == TG::buttonFreq || menuitem->parent()->button() == TG::buttonFreq) {
//        QString unit;
//        unit = _freqUnitText[_freqUnit];
//        switch(_button)
//        {
//        case TG::button01: //center
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_freqCenter, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button02: //CF step
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_freqStep, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button03: //start
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_freqStart, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button04: //stop
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_freqStop, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button05: //Freq Offset
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_freqOffset, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button00:
//        case TG::button06:
//        case TG::button07:
//
//        case TG::buttonUndef:
//        case TG::buttonFreq:
//        case TG::buttonSpan:
//        case TG::buttonAmpt:
//        case TG::buttonBW:
//        case TG::buttonSweep:
//        case TG::buttonTrace:
//        case TG::buttonMarker:
//        case TG::buttonMarkerMain:
//        case TG::buttonMarkerPeak:
//        case TG::buttonSave:
//        case TG::buttonPrint:
//        case TG::buttonMeas:
//        case TG::buttonRestart:
//            break;
//        }
//    } else if(menuitem->button() == TG::buttonSpan || menuitem->parent()->button() == TG::buttonSpan) {
//        QString unit;
//        unit = _freqUnitText[_freqUnit];
//        switch(_button)
//        {
//        case TG::button01: //MANUAL \nSPAN
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str())); //("Span"));
//            _stringlist.push_back(QString("%1 %2").arg(_freqSpan, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button02: //FULL \nSPAN
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str())); //("Span"));
//            _stringlist.push_back(QString("%1 %2").arg(_freqSpan, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button03: //ZERO \nSPAN
//            //_stringlist.push_back(QString("%1").arg("Span"));
//            //_stringlist.push_back(QString("%1 %2").arg(_freqStart).arg(freqUnitText[_freqUnit]));
//            break;
//        case TG::button04: //LAST \nSPAN
//            //_stringlist.push_back(QString("%1").arg("Span"));
//            //_stringlist.push_back(QString("%1 %2").arg(_freqStop).arg(freqUnitText[_freqUnit]));
//            break;
//        case TG::button00:
//        case TG::button05:
//        case TG::button06:
//        case TG::button07:
//
//        case TG::buttonUndef:
//        case TG::buttonFreq:
//        case TG::buttonSpan:
//        case TG::buttonAmpt:
//        case TG::buttonBW:
//        case TG::buttonSweep:
//        case TG::buttonTrace:
//        case TG::buttonMarker:
//        case TG::buttonMarkerMain:
//        case TG::buttonMarkerPeak:
//        case TG::buttonSave:
//        case TG::buttonPrint:
//        case TG::buttonMeas:
//        case TG::buttonRestart:
//            break;
//        }
//    } else if(menuitem->button() == TG::buttonAmpt || menuitem->parent()->button() == TG::buttonAmpt) {
//        QString unit;
//        //unit = freqUnitText[_freqUnit];
//        unit = _refLevlUnitText[_refLevlUnit];
//        switch(_button)
//        {
//        case TG::button01: //REF
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str())); //("Ref Level"));
//            _stringlist.push_back(QString("%1 %2").arg(_refLevl, 0, 'f', 2).arg(unit));
//            break;
//        case TG::button02: //RANGE
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str())); //("Input Att"));
//            _stringlist.push_back(QString("%1 %2").arg(_refLevl, 0, 'f', 2).arg(unit));
//            break;
//        case TG::button03: //UNIT
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str())); //("Scal/Div"));
//            _stringlist.push_back(QString("%1 %2").arg(_refLevl, 0, 'f', 2).arg(unit));
//            break;
//        case TG::button04: //REF \nOFFSET
//            //_stringlist.push_back(QString("%1").arg("Span"));
//            //_stringlist.push_back(QString("%1 %2").arg(_freqStop).arg(freqUnitText[_freqUnit]));
//            break;
//        case TG::button05: //REF \nINPUT
//            //_stringlist.push_back(QString("%1").arg("Span"));
//            //_stringlist.push_back(QString("%1 %2").arg(_freqStop).arg(freqUnitText[_freqUnit]));
//            break;
//        case TG::button00:
//        case TG::button06:
//        case TG::button07:
//
//        case TG::buttonUndef:
//        case TG::buttonFreq:
//        case TG::buttonSpan:
//        case TG::buttonAmpt:
//        case TG::buttonBW:
//        case TG::buttonSweep:
//        case TG::buttonTrace:
//        case TG::buttonMarker:
//        case TG::buttonMarkerMain:
//        case TG::buttonMarkerPeak:
//        case TG::buttonSave:
//        case TG::buttonPrint:
//        case TG::buttonMeas:
//        case TG::buttonRestart:
//            break;
//        }
//    } else if(menuitem->button() == TG::buttonSweep || menuitem->parent()->button() == TG::buttonSweep) {
//        QString unit;
//        unit = _sweepUnitsText[_sweepUnit];
//        _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//        _stringlist.push_back(QString("%1 %2").arg(_time, 0, 'f', 3).arg(unit));
//
//    } else if(menuitem->button() == TG::buttonBW || menuitem->parent()->button() == TG::buttonBW) {
//        QString unit;
//        unit = _freqUnitText[_bwUnit];
//        switch(_button)
//        {
//        case TG::button01: //RBW
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_rbw, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button02: //RBW
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_rbw, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button03: //VBW
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_vbw, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button04: //VBW
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            _stringlist.push_back(QString("%1 %2").arg(_vbw, 0, 'f', 4).arg(unit));
//            break;
//        case TG::button05:
//            break;
//        case TG::button06:
//            break;
//        case TG::button00:
//        case TG::button07:
//
//        case TG::buttonUndef:
//        case TG::buttonFreq:
//        case TG::buttonSpan:
//        case TG::buttonAmpt:
//        case TG::buttonBW:
//        case TG::buttonSweep:
//        case TG::buttonTrace:
//        case TG::buttonMarker:
//        case TG::buttonMarkerMain:
//        case TG::buttonMarkerPeak:
//        case TG::buttonSave:
//        case TG::buttonPrint:
//        case TG::buttonMeas:
//        case TG::buttonRestart:
//            break;
//        }
//
//    } else if(  menuitem->button() == TG::buttonMarkerMain || menuitem->parent()->button() == TG::buttonMarkerMain ||
//                menuitem->button() == TG::buttonMarker || menuitem->parent()->button() == TG::buttonMarker) {
//        //if(menuitem->parent()->button() == TG::buttonMarkerMain) {
//        //    menuitem = menuitem->parent();
//        //}
//        //TG::Button button1 = menuitem->activeButton();
//        //TG::Button button2 = menuitem->parent()->activeButton();
//        //std::string str = menuitem->child(menuitem->activeButton())->text();
//        if(menuitem->child(menuitem->activeButton())->text().size()>0) {
//            QString unit;
//            unit = _freqUnitText[_freqUnit];
//            //TG::Button button1 = menuitem->activeButton();
//            _stringlist.push_back(QString("%1").arg(menuitem->child(menuitem->activeButton())->text().c_str()));
//            if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                _markerCurrent = _markerArray[_activeMarker].v2 - _markerArray[_activeMarker].v1;
//            } else {
//                _markerCurrent = _markerArray[_activeMarker].v1;
//            }
//            _stringlist.push_back(QString("%1 %2").arg(_markerCurrent, 0, 'f', 3).arg(unit));
//        }
//    }
//
//    return _stringlist;
//}
//
////void Controller::setDataArray(const boost::container::vector<float> dataArray)
//void Controller::setDataArray(const std::vector<double> dataArray)
//{
//    if(_internalEmulator != 0) {
//        _dataArray2 = dataArray;
//    } else {
//        _dataArray3 = dataArray;
//    }
//}
//
////boost::container::vector<float> Controller::dataArray() const
//std::vector<double> Controller::dataArray() const
//{
//    if(_internalEmulator != 0) {
//        return _dataArray2;
//    } else {
//        return _dataArray3;
//    }
//}
//
//void Controller::setCurrentData(const float data)
//{
//    if(_internalEmulator != 0) {
//        _dataArray2[_current] = data;
//    } else {
//        _dataArray3[_current] = data;
//    }
//}
//
//float Controller::currentData(void) const
//{
//    if(_internalEmulator != 0) {
//        return _dataArray2[_current];
//    } else {
//        return _dataArray3[_current];
//    }
//}
//
//void Controller::setCurrent(const int &current)
//{
//    _current = current;
//}
//
//int &Controller::current(void) const
//{
//    return const_cast<int&>(_current);
//}
//
//void Controller::setNumber(const int &number)
//{
//    _number = number;
//
//    if(_internalEmulator != 0) {
//        _emulatorDigital2->setNumber(_number);
//    } else {
//        _emulatorDigital3->setNumber(_number);
//    }
//}
//
//int &Controller::number(void) const
//{
//    return const_cast<int&>(_number);
//}
//
//void Controller::setScreenState(TG::ScreenStates screenStates)
//{
//    _screenStates = screenStates;
//
//    emit screenStateChanged(_screenStates);
//}
//
//void Controller::clearKeyPad(void)
//{
//    _keypad.clear();
//    _currentKeyPad = 0;
//}
//
//void Controller::setKeyPad(const char &keypad)
//{
//    _keypad[_currentKeyPad++] = keypad;
//}
//
//void Controller::setKeyPadBkSp(void)
//{
//    int index(_keypad.size());
//    if(index > 0 ) {
//        _keypad.remove(index-1, 1);
//        _currentKeyPad--;
//    }
//}
//
//QByteArray &Controller::keyPad(void)
//{
//    return _keypad;
//}
//
//void Controller::pushButtonKeyPad(void)
//{
//    _freqUnit = TG::fr_Undef;
//    _spanUnit = TG::fr_Undef;
//    _sweepUnit = TG::sw_s; //sw_Undef;
//
//    if(_mainMenu == nullptr) return;
//
//    if(_buttonStack.length() == 0) {
//        _buttonStack.push_back(_mainMenu->activeButton());
//        pushButton(_mainMenu->activeButton(), false, TG::lvlDown);
//    } else {
//        pushButton(_mainMenu->activeButton(), false, TG::lvlCurrent);
//    }
//}
//
//void Controller::popButtonKeyPad(void)
//{
//    if(_buttonStack.length() > 0) {
//        pushButton(_buttonStack.pop(), false, TG::lvlUp);
//    }
//}
//
//void Controller::setButton(const TG::Button &button)
//{
//    _button = button;
//
//    //if(_mainMenu) _mainMenu->setButtons(_state);
//}
//
//TG::Button &Controller::button(void)
//{
//    return _button;
//}
//
//void Controller::pushButton(const TG::Button &button, const bool &root, const TG::Moving &moving)
//{
//    if(_mainMenu == nullptr) return;
//
//    if(_screenWidget) {
//        TG::Button buttonparent(TG::buttonUndef);
//        if(_mainMenu->menuCurrent().isNull() == false) buttonparent = _mainMenu->menuCurrent()->button();
//        //bool flag2 = _mainMenu->menuCurrent()->parent().isNull();
//        //TG::Button button1 = _mainMenu->menuCurrent()->parent()->button();
//        _screenWidget->setScreenNames(button, buttonparent);
//    }
//    if(_mainMenu) {
//        _mainMenu->setCurrentMenuItem(button, root, moving);
//        _mainMenu->setButtonTexts(button);
//        _mainMenu->setButtonStates(button);
//        _mainMenu->pushButton(_mainMenu->activeButton());
//        QTest::qSleep(10);
//    }
//}
//
//void Controller::buttonEnter(void)
//{
//    if(_mainMenu == nullptr) return;
//
//    if(_mainMenu) {
//        //QSharedPointer<SAItem> menuitem = _mainMenu->menuCurrent();
//        //_mainMenu->buttonNN(menuitem->activeButton());
//        _mainMenu->buttonNN(_mainMenu->menuCurrent()->activeButton());
//    }
//}
//
//void Controller::redrawTexts(void)
//{
//    screenWidget()->redrawText();
//}
//
//void Controller::initMarkers(void)
//{
//    double time = _sweepParam._time / _number;
//
//    TG::MarkerItem markerItem;
//    markerItem.changed = false;
//    markerItem.drawn1 = false;
//    markerItem.drawn2 = false;
//    markerItem.type2 = TG::mrkStandart;
//    if(_zeroSpan) {
//        markerItem.v1 = time * ((_number*1)/4 + 8);
//        markerItem.v2 = time * ((_number*1)/4 + 16);
//        markerItem.x1 = ((markerItem.v1) / (_sweepParam._time))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_sweepParam._time))*(0.8*2);
//    } else {
//        markerItem.v1 = 110.0;
//        markerItem.v2 = 260.0;
//        markerItem.x1 = ((markerItem.v1) / (_freqStop-_freqStart))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_freqStop-_freqStart))*(0.8*2);
//    }
//    markerItem.x1prev = markerItem.x1;
//    markerItem.x2prev = markerItem.x2;
//    markerItem.r = 1.0;
//    markerItem.g = 0.0; //0.2;
//    markerItem.b = 0.0; //0.2;
//    _markerArray[0] = markerItem;
//
//    markerItem.type2 = TG::mrkOff;
//    if(_zeroSpan) {
//        markerItem.v1 = time * ((_number*2)/4 + 8);
//        markerItem.v2 = time * ((_number*2)/4 + 16);
//        markerItem.x1 = ((markerItem.v1) / (_sweepParam._time))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_sweepParam._time))*(0.8*2);
//    } else {
//        markerItem.v1 = 410.0;
//        markerItem.v2 = 460.0;
//        markerItem.x1 = ((markerItem.v1) / (_freqStop-_freqStart))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_freqStop-_freqStart))*(0.8*2);
//    }
//    markerItem.x1prev = markerItem.x1;
//    markerItem.x2prev = markerItem.x2;
//    markerItem.r = 0.2;
//    markerItem.g = 1.0;
//    markerItem.b = 0.2;
//    _markerArray[1] = markerItem;
//
//    if(_zeroSpan) {
//        markerItem.v1 = time * ((_number*3)/4 - 8);
//        markerItem.v2 = time * ((_number*3)/4 - 16);
//        markerItem.x1 = ((markerItem.v1) / (_sweepParam._time))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_sweepParam._time))*(0.8*2);
//    } else {
//        markerItem.v1 = 610.0;
//        markerItem.v2 = 660.0;
//        markerItem.x1 = ((markerItem.v1) / (_freqStop-_freqStart))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_freqStop-_freqStart))*(0.8*2);
//    }
//    markerItem.x1prev = markerItem.x1;
//    markerItem.x2prev = markerItem.x2;
//    markerItem.r = 0.2;
//    markerItem.g = 0.2;
//    markerItem.b = 1.0;
//    _markerArray[2] = markerItem;
//
//    if(_zeroSpan) {
//        markerItem.v1 = time * ((_number*3)/4 + 8);
//        markerItem.v2 = time * ((_number*3)/4 + 16);
//        markerItem.x1 = ((markerItem.v1) / (_sweepParam._time))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_sweepParam._time))*(0.8*2);
//    } else {
//        markerItem.v1 = 810.0;
//        markerItem.v2 = 860.0;
//        markerItem.x1 = ((markerItem.v1) / (_freqStop-_freqStart))*(0.8*2);
//        markerItem.x2 = ((markerItem.v2) / (_freqStop-_freqStart))*(0.8*2);
//    }
//    markerItem.x1prev = markerItem.x1;
//    markerItem.x2prev = markerItem.x2;
//    markerItem.r = 1.0;
//    markerItem.g = 0.2;
//    markerItem.b = 1.0;
//    _markerArray[3] = markerItem;
//
//    TG::MarkerType type = this->markers()->at(0).type2;
//    //boost::container::map<int, TG::MarkerItem> *markers(this->markers());
//    std::map<int, TG::MarkerItem> *markers(this->markers());
//
//    Q_UNUSED(type)
//    Q_UNUSED(markers)
//
//}
//
//void Controller::readMarkers(TG::MarkerParam &markerParam)
//{
//    //double time = _sweepParam._time / _number;
//
//#ifdef Q_OS_LINUX
//    int size = std::min(markerParam._markers.size(), _markerArray.size());
//#else
//    int size = std::min(markerParam._markers.size(), _markerArray.size());
//#endif
//
//    for(int i=0; i<size; i++) {
//        if(_zeroSpan) {
//            _markerArray[i].v1 = markerParam._markers[i];
//            _markerArray[i].v2 = markerParam._markers[i];
//            _markerArray[i].x1 = (0.8-(-0.8))*( (_markerArray[i].v1) / (_sweepParam._time) );
//            _markerArray[i].x2 = (0.8-(-0.8))*( (_markerArray[i].v2) / (_sweepParam._time) );
//        } else {
//            _markerArray[i].v1 = markerParam._markers[i] / _expValue[_expFreq];
//            _markerArray[i].v2 = markerParam._markers[i] / _expValue[_expFreq];
//            _markerArray[i].x1 = (0.8-(-0.8))*( (_markerArray[i].v1-_freqStart) / (_freqStop-_freqStart) );
//            _markerArray[i].x2 = (0.8-(-0.8))*( (_markerArray[i].v2-_freqStart) / (_freqStop-_freqStart) );
//        }
//        _markerArray[i].x1prev = _markerArray[i].x1;
//        _markerArray[i].x2prev = _markerArray[i].x2;
//
//        //_markerArray[i].drawn1 = markerParam._states[i];
//        if(markerParam._states[i] == true) {
//            _markerArray[i].type2 = TG::mrkStandart;
//        }
//    }
//}
//
//void Controller::writeMarkers(TG::MarkerParam &markerParam)
//{
//#ifdef Q_OS_LINUX
//    int size = std::min(markerParam._markers.size(), _markerArray.size());
//#else
//    int size = std::min(markerParam._markers.size(), _markerArray.size());
//#endif
//
//    for(int i=0; i<size; i++) {
//        if(_zeroSpan) {
//            markerParam._markers[i] = _markerArray[i].v1;
//        } else {
//            markerParam._markers[i] = _markerArray[i].v1 * _expValue[_expFreq];
//        }
//        //markerParam._markers[i] = _markerArray[i].v2 * _expValue[_expFreq];
//        //_markerArray[i].x1 = (0.8-(-0.8))*( (_markerArray[i].v1-_freqStart) / (_freqStop-_freqStart) );
//        //_markerArray[i].x2 = (0.8-(-0.8))*( (_markerArray[i].v2-_freqStart) / (_freqStop-_freqStart) );
//        //_markerArray[i].x1prev = _markerArray[i].x1;
//        //_markerArray[i].x2prev = _markerArray[i].x2;
//
//        if(_markerArray[i].type2 == TG::mrkStandart) {
//            markerParam._states[i] = true;
//        } else {
//            markerParam._states[i] = false;
//        }
//    }
//}
//
//void Controller::setAllMarkersOff(void)
//{
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putAllMarkersOff(_markerParam);
//
//#ifdef Q_OS_LINUX
//    int size = std::min(_markerParam._markers.size(), _markerArray.size());
//#else
//    int size = std::min(_markerParam._markers.size(), _markerArray.size());
//#endif
//    for(int i=0; i<size; i++) {
//        _markerArray[i].type2 = TG::mrkOff;
//    }
//
//    screenWidget()->redraw();
//}
//
//void Controller::setMarkers(TG::MarkerParam &markerParam)
//{
//    int length = markerParam._markers.size();
//    for(int i=0; i<length; i++) {
//        _markerArray[i].v1 = markerParam._markers[i];
//    }
//}
//
//void Controller::setChangedMarkers(int index)
//{
//    if(index < 0) {
//        //boost::container::map<int, TG::MarkerItem>::iterator it(_markerArray.begin());
//        std::map<int, TG::MarkerItem>::iterator it(_markerArray.begin());
//        while(it!=_markerArray.end()) {
//            it->second.changed = true;
//            //bool drawn1 = it->second.drawn1;
//            //bool drawn2 = it->second.drawn1;
//            ++it;
//        }
//    } else {
//        _markerArray.at(index).changed = true;
//    }
//}
//
//void Controller::initDisplayLine(void)
//{
//    //double unitMax(0.0);
//    //double unitMin(0.0);
//    //ScreenWidget *screenWidget_ = screenWidget();
//    //if(screenWidget_ != nullptr) {
//    //    unitMax = screenWidget_->unitUp();
//    //    unitMin = screenWidget_->unitDown();
//    //}
//
//    _displayLine.changed = false;
//    _displayLine.drawn1 = false;
//    _displayLine._unit = 0.0; //90.0;
//    //_displayLine.y1 = ((_displayLine.v1) / (_freqStop-_freqStart))*(0.8*2);
//    //_displayLine.y1prev = _displayLine.y1;
//    _displayLine.r = 1.0;
//    _displayLine.g = 0.5;
//    _displayLine.b = 0.1;
//}
//
////void Controller::setDisplayLine(const double &line, bool first, bool volt, bool vxi11)
//void Controller::setDisplayLine(const double &line, bool volt, bool first, bool vxi11)
//{
//    if(screenWidget() != nullptr)
//    {
//        if( volt ) {
//            _displayLine._unit = setDisplayLineVolt2Unit(line);
//            _displayParam._volt = line;
//        } else {
//            _displayLine._unit = line;
//            _displayParam._volt = setDisplayLineUnit2Volt(line);
//        }
//
//        if( first==true) _displayLine._unitPrev = _displayLine._unit;
//
//        //if( vxi11 == true && _controllerVxi11 != NULL ) {
//        //    _displayParam._on = true;
//        //    _controllerVxi11->putDisplayParam(_displayParam);
//        //}
//    }
//}
//
//void Controller::setChangedDisplayLine(int index)
//{
//    Q_UNUSED(index)
//
//    //if(index < 0) {
//    //    boost::container::map<int, TG::MarkerItem>::iterator it(_markerArray.begin());
//    //    while(it!=_markerArray.end()) {
//    //        it->second.changed = true;
//    //        //bool drawn1 = it->second.drawn1;
//    //        //bool drawn2 = it->second.drawn1;
//    //        ++it;
//    //    }
//    //} else {
//    //    _markerArray.at(index).changed = true;
//    //}
//
//    _displayLine.changed = true;
//}
//
//double Controller::setDisplayLineUnit2Volt(double unit)
//{
//    switch(_amptParam.yAxis) //from other (dBm) to volt
//    {
//    case TG::yAxisdBm:
//        //line = 10*log10( (pow(_displayParam._volt, 2.0) / 50.0 ) / 1e-3 );
//        if(fabs(unit) < 1e-15) unit = 0.0;
//        _displayParam._volt = pow( 50.0*pow(10.0, 0.1*unit)*1e-3, 0.5 );
//        break;
//    case TG::yAxisdBmV:
//        //line = 20.0*log10( (_displayParam._volt) / 1e-3 );
//        _displayParam._volt = 1e-3*pow(10.0, 0.05*unit);
//        break;
//    case TG::yAxisWatt:
//        //line = pow(_displayParam._volt, 2.0) / 50.0;
//        _displayParam._volt = pow( unit*50.0, 0.5 );
//        break;
//    case TG::yAxisVolt:
//        //line = _displayParam._volt;
//        _displayParam._volt = unit;
//        break;
//    case TG::yAxisUndef:
//    default:
//        _displayParam._volt = 0;
//        break;
//    }
//
//    return _displayParam._volt;
//}
//
//double Controller::setDisplayLineVolt2Unit(double volt)
//{
//    double unit(0.0);
//
//    _displayParam._volt = volt;
//
//    switch(_amptParam.yAxis) //from volt to other (dBm)
//    {
//    case TG::yAxisdBm:
//        unit = 10*log10( (pow(_displayParam._volt, 2.0) / 50.0 ) / 1e-3 );
//        if(fabs(unit) < 1e-12) unit = 0.0;
//        break;
//    case TG::yAxisdBmV:
//        unit = 20.0*log10( (_displayParam._volt) / 1e-3 );
//        break;
//    case TG::yAxisWatt:
//        unit = pow(_displayParam._volt, 2.0) / 50.0;
//        break;
//    case TG::yAxisVolt:
//        unit = _displayParam._volt;
//        break;
//    case TG::yAxisUndef:
//    default:
//        unit = 0.0;
//        break;
//    }
//
//    return unit;
//}
//
//void Controller::setDisplayLineOn(double line)
//{
//    _displayParam._volt = setDisplayLineUnit2Volt(line);
//
//    //switch(_amptParam.yAxis) //from other (dBm) to volt
//    //{
//    //case TG::yAxisdBm: //0: //dBm
//    //    //line = 10*log10( (pow(_displayParam._volt, 2.0) / 50.0 ) / 1e-3 );
//    //    if(fabs(line) < 1e-15) line = 0.0;
//    //    _displayParam._volt = pow( 50.0*pow(10.0, 0.1*line)*1e-3, 0.5 );
//    //    break;
//    //case TG::yAxisdBmV: //1: //dBmV
//    //    //line = 20.0*log10( (_displayParam._volt) / 1e-3 );
//    //    _displayParam._volt = 1e-3*pow(10.0, 0.05*line);
//    //    break;
//    //case TG::yAxisWatt: //2: //Watt
//    //    //line = pow(_displayParam._volt, 2.0) / 50.0;
//    //    _displayParam._volt = pow( line*50.0, 0.5 );
//    //    break;
//    //case TG::yAxisVolt: //3: //Volt
//    //    //line = _displayParam._volt;
//    //    _displayParam._volt = line;
//    //    break;
//    //case TG::yAxisUndef:
//    //default:
//    //    line = 0;
//    //    break;
//    //}
//
//    _displayParam._on = true;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putDisplayParam(_displayParam);
//}
//
//void Controller::setDisplayLineOff(void)
//{
//    _displayParam._on = false;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putDisplayParam(_displayParam);
//}
//
//QString Controller::displayLineUnit(void)
//{
//    QString unit("");
//
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm:
//        unit = QString("dBm");
//        break;
//    case TG::yAxisdBmV:
//        unit = QString("dBmV");
//        break;
//    case TG::yAxisWatt:
//        unit = QString("W");
//        break;
//    case TG::yAxisVolt:
//        unit = QString("V");
//        break;
//    case TG::yAxisUndef:
//    default:
//        break;
//    }
//
//    return unit;
//}
//
//QString Controller::dispayLineText(void)
//{
//    //double line(0.0);
//    //QString unit("");
//
//    //line = setDisplayLineVolt2Unit(_displayParam._volt);
//    //unit = displayLineUnit();
//
//    //switch(_amptParam.yAxis) //from volt to other (dBm)
//    //{
//    //case TG::yAxisdBm: //0: //dBm
//    //    //line = 10*log10( (pow(_displayParam._volt, 2.0) / 50.0 ) / 1e-3 );
//    //    unit = QString("dBm");
//    //    //if(fabs(line) < 1e-12) line = 0.0;
//    //    break;
//    //case TG::yAxisdBmV: //1: //dBmV
//    //    //line = 20.0*log10( (_displayParam._volt) / 1e-3 );
//    //    unit = QString("dBmV");
//    //    break;
//    //case TG::yAxisWatt: //2: //Watt
//    //    //line = pow(_displayParam._volt, 2.0) / 50.0;
//    //    unit = QString("W");
//    //    break;
//    //case TG::yAxisVolt: //3: //Volt
//    //    //line = _displayParam._volt;
//    //    unit = QString("V");
//    //    break;
//    //case TG::yAxisUndef:
//    //default:
//    //    //line = 0;
//    //    unit = QString("");
//    //    break;
//    //}
//
//    //QString value = QString("%1 %2").arg(line).arg(unit);
//    //return value;
//
//    return QString("%1 %2").arg(setDisplayLineVolt2Unit(_displayParam._volt)).arg(displayLineUnit());
//}
//
//bool Controller::displayLineIncMax(void)
//{
//    _displayLineCurrent;
//    _amptParam.relativeValue;
//    double refLevl_ = refLevl();
//
//    bool incMax(false);
//
//    //_displayLineCurrent += refLevl()/10.0;
//    double unit(refLevl());
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm:
//        if(_displayLineCurrent * 10 < refLevl()) incMax = true;
//        break;
//    case TG::yAxisdBmV:
//        if(_displayLineCurrent * 10 < refLevl()) incMax = true;
//        break;
//    case TG::yAxisWatt:
//        if(_displayLineCurrent * 10 < refLevl()) incMax = true;
//        break;
//    case TG::yAxisVolt:
//        break;
//    case TG::yAxisUndef:
//    default:
//        break;
//    }
//
//    return incMax;
//}
//
//double Controller::displayLineInc(double unit)
//{
//    int _displayLineIndex;
//    double value( 0.0 );
//
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm: //0: //dBm
//    {
//        if(_amptParam.displayLog == true) {
//            value = ( refLevl() - _displayLineIndex*_amptParam.scaleDev );
//        } else {
//            value = ( 10*log10( (pow(_amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * _displayLineIndex), 2.0) / 50.0 ) / 1e-3 ) );
//        }
//        break;
//    }
//    case TG::yAxisdBmV: //1: //dBmV
//    {
//        if(_amptParam.displayLog == true) {
//            value = ( refLevl() - _displayLineIndex*_amptParam.scaleDev );
//        } else {
//            value = ( 20.0*log10( (_amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * _displayLineIndex)) / 1e-3 ) );
//        }
//        break;
//    }
//    case TG::yAxisWatt: //2: //Watt
//    {
//        if(_amptParam.displayLog == true) {
//            value = ( refLevl() * pow(10.0, -0.1*_displayLineIndex*_amptParam.scaleDev) );
//        } else {
//            value = ( pow(_amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * _displayLineIndex), 2.0) / 50.0 );
//        }
//        break;
//    }
//    case TG::yAxisVolt: //3: //Volt
//    {
//        if(_amptParam.displayLog == true) {
//            value = ( refLevl() * pow(10.0, -0.05*_displayLineIndex*_amptParam.scaleDev) );
//        } else {
//            value = ( _amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * _displayLineIndex) );
//        }
//        break;
//    }
//
//    }
//
//    return value;
//}
//
//bool Controller::displayLineDecMin(void)
//{
//    _displayLineCurrent;
//    _amptParam.relativeValue;
//    double refLevl_ = refLevl();
//
//    bool decMin(false);
//    return decMin;
//}
//
//double Controller::displayLineDec(double unit)
//{
//    return _refLevl;
//}
//
//double Controller::displayLineVolt2Index(double volt)
//{
//    _displayLineCurrent += refLevl()/10.0;
//    return _refLevl;
//}
//
//double Controller::displayLineIndex2Volt(double index)
//{
//    return _refLevl;
//}
//
//void Controller::currentDown(bool bWheel)
//{
//    if(_mainMenu == nullptr) return;
//
//    if(_mainMenu) {
//        if(_mainMenu->type()==TG::menuOld) {
//            TG::Button activeButton = _mainMenu->menuCurrent()->activeButton();
//            if(_mainMenu->menuCurrent()->children().find(activeButton) != _mainMenu->menuCurrent()->children().end()) {
//                TG::Types type2 = _mainMenu->menuCurrent()->child(activeButton)->type();
//                Q_UNUSED(type2)
//                switch(_mainMenu->menuCurrent()->child(activeButton)->type())
//                {
//                case TG::typeUndef:
//                case TG::typeUnit:
//                case TG::typeReturn:
//                case TG::typeRefLevl:
//                case TG::typeRefLevlOffset:
//                    break;
//                case TG::typeMarker:
//                case TG::typeMarkerPeak:
//                case TG::typeToMarker:
//                {
//                    if(_markerCurrent > (_freqStop-_freqStart)/10.0) {
//                        _markerCurrent -= (_freqStop-_freqStart)/10.0;
//                        if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                            _markerArray[_activeMarker].v2 = _markerCurrent;
//                            _markerArray[_activeMarker].x2 = ((_markerArray[_activeMarker].v2) / (_freqStop-_freqStart))*(0.8*2);
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//                        }
//                        setChangedMarkers();
//                    }
//                    break;
//                }
//                case TG::typeSweep:
//                {
//                    if(_time > 10.0) {
//                        _time -= 10.0;
//                        setSweep(_time, true);
//                    }
//                    clearKeyPad();
//                    break;
//                }
//                case TG::typeFreqCenter:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    if(_freqCenter > freqStep) {
//                        //_freqCenter -= freqStep;
//                        float freqCenter = _freqCenter - freqStep;
//                        setFreqCenter(freqCenter);
//                    }
//                    break;
//                }
//                case TG::typeFreqSpan:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    if(_freqSpan > freqStep) {
//                        //_freqSpan -= freqStep;
//                        float freqSpan = _freqSpan - freqStep;
//                        setFreqSpan(freqSpan);
//                    }
//                    break;
//                }
//                case TG::typeFreqStart:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    if(_freqStart > freqStep) {
//                        //_freqStart -= freqStep;
//                        float freqStart = _freqStart - freqStep;
//                        setFreqStart(freqStart);
//                    }
//                    break;
//                }
//                case TG::typeFreqStop:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    if(_freqStop > freqStep && _freqStop > _freqStart + freqStep) {
//                        //_freqStop -= freqStep;
//                        float freqStop = _freqStop - freqStep;
//                        setFreqStop(freqStop);
//                    }
//                    break;
//                }
//                case TG::typeFreqOffset:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    if(_freqOffset > freqStep) {
//                        _freqOffset -= freqStep;
//                    }
//                    break;
//                }
//                case TG::typeFreqStep:
//                {
//                    double freqStep(10.0);
//                    if(bWheel) freqStep = 1.0;
//                    if(_freqStep > freqStep) {
//                        _freqStep -= freqStep;
//                    }
//                    break;
//                }
//                case TG::typeResBw:
//                {
//                    if(_bwIndex > 0)
//                        _bwIndex--;
//                    _rbw = _bwStep[_bwIndex];
//                    _vbw = _bwStep[_bwIndex];
//                    break;
//                }
//                case TG::typeVideoBw:
//                {
//                    if(_bwIndex > 0)
//                        _bwIndex--;
//                    _rbw = _bwStep[_bwIndex];
//                    _vbw = _bwStep[_bwIndex];
//                    break;
//                }
//                }
//
//                screenWidget()->redraw();
//            }
//        } else if(_mainMenu->type()==TG::menuNew) {
//            if(_mainMenu->indexMenu() == TG::indexMarker) {
//                if(_zeroSpan) {
//                    if(_markerCurrent - _sweepParam._time/22.0 > 0 ) {
//                        _markerCurrent -= _sweepParam._time/22.0;
//                        if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1) / (_sweepParam._time));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                            _markerArray[_activeMarker].v2 = _markerCurrent;
//                            _markerArray[_activeMarker].x2 = (0.8-(-0.8))*((_markerArray[_activeMarker].v2) / (_sweepParam._time));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1) / (_sweepParam._time));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1) / (_sweepParam._time));
//                        }
//
//                        if(_markerArray[_activeMarker].x1 == _markerArray[_activeMarker].x1prev) {
//                            _markerArray[_activeMarker].drawn1 = true;
//                        }
//                        if(_markerArray[_activeMarker].x2 == _markerArray[_activeMarker].x2prev) {
//                            _markerArray[_activeMarker].drawn2 = true;
//                        }
//
//                        setChangedMarkers(_activeMarker);
//
//                        TG::MarkerParam markerParam;
//                        emit markerChanged(markerParam);
//                        if(_internalEmulator==0) emit dataChanged();
//                    }
//                } else {
//                    if(_markerCurrent - (_freqStop-_freqStart)/22.0 > _freqStart ) {
//                        _markerCurrent -= (_freqStop-_freqStart)/22.0;
//                        if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1-_freqStart) / (_freqStop-_freqStart));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                            _markerArray[_activeMarker].v2 = _markerCurrent;
//                            _markerArray[_activeMarker].x2 = (0.8-(-0.8))*((_markerArray[_activeMarker].v2-_freqStart) / (_freqStop-_freqStart));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1-_freqStart) / (_freqStop-_freqStart));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1-_freqStart) / (_freqStop-_freqStart));
//                        }
//
//                        if(_markerArray[_activeMarker].x1 == _markerArray[_activeMarker].x1prev) {
//                            _markerArray[_activeMarker].drawn1 = true;
//                        }
//                        if(_markerArray[_activeMarker].x2 == _markerArray[_activeMarker].x2prev) {
//                            _markerArray[_activeMarker].drawn2 = true;
//                        }
//
//                        setChangedMarkers(_activeMarker);
//
//                        TG::MarkerParam markerParam;
//                        emit markerChanged(markerParam);
//                        if(_internalEmulator==0) emit dataChanged();
//                    }
//                }
//            } else if(_mainMenu->indexMenu() == TG::indexDisplay) {
//                double refLevlTemp1 = refLevl();
//                double refLevlTemp2 = _displayLineCurrent;
//                double refLevlTemp3 = refLevl() / 10.0;
//                //convert()
//                //if(_displayLineCurrent > 10.0) {
//                //    _displayLineCurrent -= 10.0;
////                if(_displayLineCurrent > refLevl() / 10.0) {
////                    _displayLineCurrent -= refLevl() / 10.0;
//                if(_displayLineCurrent > displayLineDecMin()) {
//                    _displayLineCurrent -= displayLineDec(_displayLineCurrent);
//
//                    _displayLine._unit = _displayLineCurrent;
//                    //_displayLine.y1 = ((_displayLine.v1) / (_freqStop-_freqStart))*(0.8*2);
//
//                    if(_displayLine._unit == _displayLine._unitPrev) {
//                        _displayLine.drawn1 = true;
//                    }
//
//                    setChangedDisplayLine(_displayLineCurrent);
//
//                    TG::DisplayParam displayParam;
//                    displayParam._flags = 0xffff;
//                    emit displayChanged(displayParam);
//                }
//            }
//        }
//    }
//}
//
//void Controller::currentUp(bool bWheel)
//{
//    if(_mainMenu == nullptr) return;
//
//    if(_mainMenu) {
//        if(_mainMenu->type()==TG::menuOld) {
//            TG::Button activeButton = _mainMenu->menuCurrent()->activeButton();
//            //if(_mainMenu->menuCurrent()->children().find(TG::button01) != _mainMenu->menuCurrent()->children().end()) {
//            //    switch(_mainMenu->menuCurrent()->child(TG::button01)->type())
//            if(_mainMenu->menuCurrent()->children().find(activeButton) != _mainMenu->menuCurrent()->children().end()) {
//                switch(_mainMenu->menuCurrent()->child(activeButton)->type())
//                {
//                case TG::typeUndef:
//                case TG::typeUnit:
//                case TG::typeReturn:
//                case TG::typeRefLevl:
//                case TG::typeRefLevlOffset:
//                    break;
//                case TG::typeMarker:
//                case TG::typeMarkerPeak:
//                case TG::typeToMarker:
//                {
//                    _markerCurrent += 10.0;
//                    if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//                        _markerArray[_activeMarker].v1 = _markerCurrent;
//                        _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//                    } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                        _markerArray[_activeMarker].v2 = _markerCurrent;
//                        _markerArray[_activeMarker].x2 = ((_markerArray[_activeMarker].v2) / (_freqStop-_freqStart))*(0.8*2);
//                    } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//                        _markerArray[_activeMarker].v1 = _markerCurrent;
//                        _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//                    } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//                        _markerArray[_activeMarker].v1 = _markerCurrent;
//                        _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//                    }
//                    setChangedMarkers();
//                    break;
//                }
//                case TG::typeSweep:
//                {
//                    _time += 10.0;
//                    setSweep(_time, true);
//                    clearKeyPad();
//                    break;
//                }
//                case TG::typeFreqCenter:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    //_freqCenter += freqStep;
//                    float freqCenter = _freqCenter + freqStep;
//                    setFreqCenter(freqCenter);
//                    break;
//                }
//                case TG::typeFreqSpan:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    //_freqSpan += freqStep;
//                    float freqSpan = _freqSpan + freqStep;
//                    setFreqSpan(freqSpan);
//                    break;
//                }
//                case TG::typeFreqStart:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    if(_freqStart < _freqStop - freqStep) {
//                        //_freqStart += freqStep;
//                        float freqStart = _freqStart + freqStep;
//                        setFreqStart(freqStart);
//                    }
//                    break;
//                }
//                case TG::typeFreqStop:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    //_freqStop += freqStep;
//                    float freqStop = _freqStop + freqStep;
//                    setFreqStop(freqStop);
//                    break;
//                }
//                case TG::typeFreqOffset:
//                {
//                    double freqStep(_freqStep);
//                    if(bWheel) freqStep = (_freqStop-_freqStart)/400;
//                    _freqOffset += freqStep;
//                    break;
//                }
//                case TG::typeFreqStep:
//                {
//                    double freqStep(10.0);
//                    if(bWheel) freqStep = 1.0;
//                    _freqStep += freqStep;
//                    break;
//                }
//                case TG::typeResBw:
//                {
//                    if(_bwIndex < _bwStep.length()-1)
//                        _bwIndex++;
//                    _rbw = _bwStep[_bwIndex];
//                    _vbw = _bwStep[_bwIndex];
//                    break;
//                }
//                case TG::typeVideoBw:
//                {
//                    if(_bwIndex < _bwStep.length()-1)
//                        _bwIndex++;
//                    _rbw = _bwStep[_bwIndex];
//                    _vbw = _bwStep[_bwIndex];
//                    break;
//                }
//                }
//
//                screenWidget()->redraw();
//            }
//        } else if(_mainMenu->type()==TG::menuNew) {
//            if(_mainMenu->indexMenu() == TG::indexMarker) {
//                if(_zeroSpan) {
//                    if(_markerCurrent + (_sweepParam._time)/22.0 < _sweepParam._time ) {
//                        _markerCurrent += (_sweepParam._time)/22.0;
//                        if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1) / (_sweepParam._time));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                            _markerArray[_activeMarker].v2 = _markerCurrent;
//                            _markerArray[_activeMarker].x2 = (0.8-(-0.8))*((_markerArray[_activeMarker].v2) / (_sweepParam._time));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1) / (_sweepParam._time));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1) / (_sweepParam._time));
//                        }
//
//                        if(_markerArray[_activeMarker].x1 == _markerArray[_activeMarker].x1prev) {
//                            _markerArray[_activeMarker].drawn1 = true;
//                        }
//                        if(_markerArray[_activeMarker].x2 == _markerArray[_activeMarker].x2prev) {
//                            _markerArray[_activeMarker].drawn2 = true;
//                        }
//
//                        setChangedMarkers(_activeMarker);
//
//                        TG::MarkerParam markerParam;
//                        emit markerChanged(markerParam);
//                        if(_internalEmulator==0) emit dataChanged();
//                    }
//                } else {
//                    if(_markerCurrent + (_freqStop-_freqStart)/22.0 < _freqStop ) {
//                        _markerCurrent += (_freqStop-_freqStart)/22.0;
//                        if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1-_freqStart) / (_freqStop-_freqStart));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//                            _markerArray[_activeMarker].v2 = _markerCurrent;
//                            _markerArray[_activeMarker].x2 = (0.8-(-0.8))*((_markerArray[_activeMarker].v2-_freqStart) / (_freqStop-_freqStart));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1-_freqStart) / (_freqStop-_freqStart));
//                        } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//                            _markerArray[_activeMarker].v1 = _markerCurrent;
//                            _markerArray[_activeMarker].x1 = (0.8-(-0.8))*((_markerArray[_activeMarker].v1-_freqStart) / (_freqStop-_freqStart));
//                        }
//
//                        if(_markerArray[_activeMarker].x1 == _markerArray[_activeMarker].x1prev) {
//                            _markerArray[_activeMarker].drawn1 = true;
//                        }
//                        if(_markerArray[_activeMarker].x2 == _markerArray[_activeMarker].x2prev) {
//                            _markerArray[_activeMarker].drawn2 = true;
//                        }
//
//                        setChangedMarkers(_activeMarker);
//
//                        TG::MarkerParam markerParam;
//                        emit markerChanged(markerParam);
//                        if(_internalEmulator==0) emit dataChanged();
//                    }
//                }
//            } else if(_mainMenu->indexMenu() == TG::indexDisplay) {
//                //if(_displayLineCurrent < _freqStop-10) {
//                //    _displayLineCurrent += 10.0;
////                if(_displayLineCurrent < refLevl() - refLevl()/10) {
////                    _displayLineCurrent += refLevl()/10.0;
//                if(_displayLineCurrent < displayLineIncMax()) {
//                    _displayLineCurrent = displayLineInc(_displayLineCurrent);
//
//                    _displayLine._unit = _displayLineCurrent;
//                    //_displayLine.y1 = ((_displayLine.v1) / (_freqStop-_freqStart))*(0.8*2);
//
//                    if(_displayLine._unit == _displayLine._unitPrev) {
//                        _displayLine.drawn1 = true;
//                    }
//
//                    setChangedDisplayLine(_displayLineCurrent);
//
//                    TG::DisplayParam displayParam;
//                    displayParam._flags = 0xffff;
//                    emit displayChanged(displayParam);
//                } else {
//                    _displayLineCurrent = refLevl() - refLevl()/10;
//                }
//            }
//        }
//    } else {
//        ;
//    }
//}
//
//void Controller::setSweep(const double &time, bool vxi11)
//{
//    _time = time;
//
//    double timeTmp(_time * sweepCoeff[_sweepUnit] * 1e+3);
//
//    if(static_cast<int>(timeTmp) > 1)
//        ; //_time = time;
//    else
//        timeTmp = 1;
//
//    //double ftemp = _expValue[_convertSweepUnit[_sweepUnit]];
//    _sweepParam._time = _time * _expValue[_convertSweepUnit[_sweepUnit]];
//
//    //if( vxi11 == true && _controllerVxi11 != NULL ) {
//    //    _sweepParam._auto = false;
//    //    _controllerVxi11->putSweepParam(_sweepParam);
//    //}
//
//    if(_internalEmulator != 0) {
//        //_emulatorDigital->setTimer(_time);
//        _emulatorDigital2->setTimer(timeTmp);
//    } else {
//        _emulatorDigital3->setTimer(timeTmp);
//    }
//
//}
//
//const double &Controller::sweep(void)
//{
//    return _time;
//}
//
//void Controller::setSweepAuto(bool hard)
//{
//    _sweepParam._auto = true;
//    //if(hard == true && _controllerVxi11 != NULL)
//    //    _controllerVxi11->putSweepParam(_sweepParam);
//}
//
//const bool &Controller::sweepAuto(void)
//{
//    return _sweepParam._auto;
//}
//
//void Controller::setMarker(const double &marker)
//{
//    _markerCurrent = marker;
//
//    _markerArray[_activeMarker].v1 = _markerCurrent;
//    _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//
//}
//
//const float &Controller::marker(void)
//{
//    return _markerCurrent;
//}
//
//void Controller::setBwUnit(const TG::FreqUnits &bwUnit)
//{
//    _bwUnit = bwUnit;
//    _expBw = _convertFreqUnit[_bwUnit]; //_expValue[_convertFreqUnit[_bwUnit]];
//}
//
//void Controller::setResBw(double &rbw, bool vxi11)
//{
//    //double freqCoeff_ = freqCoeff[_bwUnit];
//
//    if(rbw * freqCoeff[_bwUnit] <= 10.0 * 1e+6) {
//        int dev(32767);
//        int _bwIndex(0);
//        for(int i=0; i<_bwStep.length(); i++) {
//            if(dev > labs((long)(_bwStep[i]-rbw))) {
//                dev = labs((long)(_bwStep[i]-rbw));
//                _bwIndex = i;
//            }
//        }
//        _rbw = _bwStep[_bwIndex];
//        _bwUnit = TG::fr_kHz;
//        _expBw = _convertFreqUnit[_bwUnit];
//        rbw = _rbw;
//
//        //if( vxi11 == true && _controllerVxi11 != NULL ) {
//        //    _bwParam.resBw = _rbw * _expValue[_convertFreqUnit[_bwUnit]];
//        //    _bwParam.selectBw = TG::selResBw;
//        //    _bwParam._autoRbw = false;
//        //    //_controllerVxi11->putBwParam(_bwParam);
//        //    _controllerVxi11->putRbwParam(_bwParam);
//
//        //    screenWidget()->redraw();
//        //}
//    }
//}
//
//void Controller::setVideoBw(double &vbw, bool vxi11)
//{
//    if(vbw * freqCoeff[_bwUnit] <= 10.0 * 1e+6) {
//        int dev(32767);
//        int imin(0);
//        for(int i=0; i<_bwStep.length(); i++) {
//            if(dev > labs((long)(_bwStep[i]-vbw))) {
//                dev = labs((long)(_bwStep[i]-vbw));
//                imin = i;
//            }
//        }
//        _vbw = _bwStep[imin];
//        _bwUnit = TG::fr_kHz;
//        _expBw = _convertFreqUnit[_bwUnit];
//        vbw = _vbw;
//
//        //if( vxi11 == true && _controllerVxi11 != NULL ) {
//        //    _bwParam.videoBw = _vbw * _expValue[_convertFreqUnit[_bwUnit]];
//        //    _bwParam.selectBw = TG::selVideoBw;
//        //    _bwParam._autoVbw = false;
//        //    //_controllerVxi11->putBwParam(_bwParam);
//        //    _controllerVxi11->putVbwParam(_bwParam);
//
//        //    screenWidget()->redraw();
//        //}
//    }
//}
//
//void Controller::setVbw3dbRbw(const double &value)
//{
//    _vbw3dbRbw = value;
//}
//
//void Controller::setSpan3dbRbw(const double &value)
//{
//    _span3dbRbw = value;
//}
//
//void Controller::setRbwFilterBw(const double &value)
//{
//    _rbwFilterBw = value;
//}
//
//void Controller::setResBwAuto(bool hard)
//{
//    _bwParam._autoRbw = true;
//    //if(hard == true && _controllerVxi11 != NULL)
//    //    _controllerVxi11->putRbwParam(_bwParam);
//
//    _rbw = _bwParam.resBw / _expValue[_convertFreqUnit[_bwUnit]];
//
//    screenWidget()->redraw();
//}
//
//void Controller::setVideoBwAuto(bool hard)
//{
//    _bwParam._autoVbw = true;
//    //if(hard == true && _controllerVxi11 != NULL)
//    //    _controllerVxi11->putVbwParam(_bwParam);
//
//    _vbw = _bwParam.videoBw / _expValue[_convertFreqUnit[_bwUnit]];
//
//    screenWidget()->redraw();
//}
//
//void Controller::putFreqParams(void)
//{
//    _freqParam._selectFreq = TG::selFreqCenter;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
//
//    _freqParam._selectFreq = TG::selFreqStart;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
//
//    _freqParam._selectFreq = TG::selFreqStop;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
//
//    //_freqParam._expFreq = _expFreq;
//    _freqCenter  = _freqParam._center / _expValue[_expFreq];
//    _freqSpan  = _freqParam._span / _expValue[_expFreq];
//    _freqStart  = _freqParam._start / _expValue[_expFreq];
//    _freqStop  = _freqParam._stop / _expValue[_expFreq];
//    _freqStep  = _freqParam._step / _expValue[_expFreq];
//
//    setFreq();
//}
//
//void Controller::putAmptParams(void)
//{
//    //_amptParam.relativeValue;
//
//    _amptParam._flags = TG::AmptParam::_ELEVEL;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putAmptParam(_amptParam);
//
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisUndef:
//    {
//        break;
//    }
//    case TG::yAxisdBm: //dBm
//    {
//        setRefLevl( 10.0*(double)log10(((double)pow(_amptParam.relativeValue, 2.0) / 50.0)*1e+3) );
//        break;
//    }
//    case TG::yAxisdBmV: //dBmV
//    {
//        setRefLevl( 20.0*log10((_amptParam.relativeValue*1e+3)/1.0) );
//        break;
//    }
//    case TG::yAxisWatt: //Watt
//    {
//        setRefLevl( pow(_amptParam.relativeValue, 2.0) / 50.0 );
//        break;
//    }
//    case TG::yAxisVolt: //Volt
//    {
//        setRefLevl( _amptParam.relativeValue );
//        break;
//    }
//    }
//
//    setAmptYAxis(_amptParam.yAxis);
//
//    setAmpt();
//}
//
//void Controller::putSweepParams(void)
//{
//    _sweepParam._time;
//
//    //_sweepParam._flags = TG::SweepParam::_ETIME;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putSweepParam(_sweepParam);
//
//    //double timeTmp(_sweepParam._time * sweepCoeff[_sweepUnit] * 1e+3);
//    //double timeTmp(_sweepParam._time / sweepCoeff[_sweepUnit]);
//    double timeTmp(_sweepParam._time / _expValue[_convertSweepUnit[_sweepUnit]]);
//
//    setSweep(timeTmp, true);
//    setSweep();
//}
//
//void Controller::putBwParams(void)
//{
//    //_bwParam.resBw;
//    //_bwParam.videoBw;
//
//    _bwParam._flags = TG::BwParam::_ERESBW;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putRbwParam(_bwParam);
//
//    _bwParam._flags = TG::BwParam::_EVIDEOBW;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putVbwParam(_bwParam);
//}
//
//void Controller::putDisplayParams(void)
//{
//    //_displayParam._volt;
//
//    _displayParam._flags = TG::DisplayParam::_ELINE;
//    //if(_controllerVxi11 != nullptr) _controllerVxi11->putDisplayParam(_displayParam);
//}

void Controller::setFreqUnit(const TG::FreqUnits &freqUnit)
{
    //_freqUnit = freqUnit;
    //_freqParam._expFreq = _expFreq = _convertFreqUnit[_freqUnit];
}

void Controller::setFreqCenter(const double &freqCenter)
{
    if(_freqStart + freqCenter - _freqCenter < 0) {
        _freqCenter = freqCenter;
        _freqStart = 0;
        _freqSpan = (_freqCenter - _freqStart)*2;
        _freqStop = (_freqCenter - _freqStart)*2;
    } else {
        _freqStart = _freqStart + freqCenter - _freqCenter;
        _freqStop = _freqStop + freqCenter - _freqCenter;
        _freqCenter = freqCenter;
    }

    //_freqParam._expFreq = _expFreq;
    //_freqParam._center = _freqCenter * _expValue[_expFreq];
    //_freqParam._span = _freqSpan * _expValue[_expFreq];
    //_freqParam._start = _freqStart * _expValue[_expFreq];
    //_freqParam._stop = _freqStop * _expValue[_expFreq];
    //_freqParam._selectFreq = TG::selFreqCenter;

    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
}

void Controller::setFreqSpan(const double &freqSpan)
{
    if(_freqCenter - freqSpan/2 < 0) {
        _freqSpan = _freqCenter*2;
        _freqStart = _freqCenter - _freqSpan/2;
        _freqStop = _freqCenter + _freqSpan/2;
    } else {
        _freqStart = _freqCenter - freqSpan/2;
        _freqStop = _freqCenter + freqSpan/2;
        _freqSpan = freqSpan;
    }

    //_freqParam._expFreq = _expFreq;
    //_freqParam._center = _freqCenter * _expValue[_expFreq];
    //_freqParam._span = _freqSpan * _expValue[_expFreq];
    //_freqParam._start = _freqStart * _expValue[_expFreq];
    //_freqParam._stop = _freqStop * _expValue[_expFreq];
    //_freqParam._selectFreq = TG::selFreqSpan;

    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
}

void Controller::setFreqStart(double freqStart)
{
    if(freqStart < 0) {
        freqStart = 0;
    } else if(freqStart > _freqStop) {
        freqStart = _freqStop;
    }
    _freqSpan = _freqStop - freqStart;
    _freqCenter = freqStart + (_freqStop - freqStart)/2;
    _freqStart = freqStart;

    //_freqParam._expFreq = _expFreq;
    //_freqParam._center = _freqCenter * _expValue[_expFreq];
    //_freqParam._span = _freqSpan * _expValue[_expFreq];
    //_freqParam._start = _freqStart * _expValue[_expFreq];
    //_freqParam._stop = _freqStop * _expValue[_expFreq];
    //_freqParam._selectFreq = TG::selFreqStart;

    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
}

void Controller::setFreqStop(double freqStop)
{
    if(freqStop < 0) {
        freqStop = 0;
    } else if(freqStop < _freqStart) {
        freqStop = _freqStart;
    }
    _freqSpan = freqStop - _freqStart;
    _freqCenter = _freqStart + (freqStop - _freqStart)/2;
    _freqStop = freqStop;

    //_freqParam._expFreq = _expFreq;
    //_freqParam._center = _freqCenter * _expValue[_expFreq];
    //_freqParam._span = _freqSpan * _expValue[_expFreq];
    //_freqParam._start = _freqStart * _expValue[_expFreq];
    //_freqParam._stop = _freqStop * _expValue[_expFreq];
    //_freqParam._selectFreq = TG::selFreqStop;

    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
}

void Controller::setFreqStep(const double &freqStep)
{
    _freqStep = freqStep;

    //_freqParam._expFreq = _expFreq;
    //_freqParam._step = _freqStep * _expValue[_expFreq];
    //_freqParam._selectFreq = TG::selFreqStep;

    //if(_controllerVxi11 != nullptr) _controllerVxi11->putFreqParam(_freqParam);
}

//void Controller::buttonKey(const TG::Button &button)
//{
//    //if(_mainMenu->menuCurrent()->children().find(TG::button01) != _mainMenu->menuCurrent()->children().end()) {
//    //QSharedPointer<SAItem> menuCurrent = _mainMenu->menuCurrent();
//
//    if(_mainMenu == nullptr) return;
//
//    TG::Types type( _mainMenu->menuCurrent()->child(button)->type() );
//    TG::Button buttinChild( _mainMenu->menuCurrent()->child(button)->button() );
//
//    switch(type)
//    {
//    case TG::typeRefLevl:
//    case TG::typeRefLevlOffset:
//        break;
//    case TG::typeFreqCenter:
//    {
//        break;
//    }
//    case TG::typeFreqStep:
//    {
//        break;
//    }
//    case TG::typeFreqStart:
//    {
//        break;
//    }
//    case TG::typeFreqStop:
//    {
//        break;
//    }
//    case TG::typeFreqOffset:
//    {
//        break;
//    }
//    case TG::typeFreqSpan:
//    {
//        break;
//    }
//    case TG::typeSweep:
//    {
//        break;
//    }
//    case TG::typeUnit:
//    {
//        break;
//    }
//    case TG::typeMarker:
//    {
////        if(buttinChild == TG::button01) {
////            if(_activeMarker < _maxMarker - 1) {
////                ++_activeMarker;
////            } else {
////                _activeMarker = 0;
////            }
////            drawMarkers();
////        } else if(buttinChild == TG::button02) {
////            if(_markerArray.find(_activeMarker) != _markerArray.end()) {
////                _markerArray[_activeMarker].type = TG::mrkStandart;
////                drawMarkers();
////            }
////        } else if(buttinChild == TG::button03) {
////            if(_markerArray.find(_activeMarker) != _markerArray.end()) {
////                _markerArray[_activeMarker].type = TG::mrkDelta;
////                drawMarkers();
////            }
////        } else if(buttinChild == TG::button06) {
////            if(_markerArray.find(_activeMarker) != _markerArray.end()) {
////                _markerArray[_activeMarker].type = TG::mrkOff;
////                drawMarkers();
////            }
////        }
//        break;
//    }
//    case TG::typeToMarker:
//    {
//        if(buttinChild == TG::button01) { //CF
//            _freqCenter = _markerArray[_activeMarker].v1;
//        } else if(buttinChild == TG::button02) { //CF Step
//            _freqStep = _markerArray[_activeMarker].v1;
//        } else if(buttinChild == TG::button03) { //CF Start
//            _freqStart = _markerArray[_activeMarker].v1;
//        } else if(buttinChild == TG::button04) { //CF Stop
//            _freqStop = _markerArray[_activeMarker].v1;
//        } else if(buttinChild == TG::button07) { //Ref Lvl
//            _refLevl = _markerArray[_activeMarker].v1;
//        }
//        setChangedMarkers();
//        break;
//    }
//    case TG::typeMarkerPeak:
//    {
//        if(buttinChild == TG::button01) { //Meas Tools >
//            _markerCurrent = 10.0;
//        } else if(buttinChild == TG::button02) { //Next Peak
//            _markerCurrent = findNextPeak();
//        } else if(buttinChild == TG::button03) { //Next Pk Right
//            _markerCurrent = findNextPkRight();
//        } else if(buttinChild == TG::button04) { //Next Pk Left
//            _markerCurrent = findNextPkLeft();
//        } else if(buttinChild == TG::button05) { //Min Search
//            _markerCurrent = findMinSearch();
//        } else if(buttinChild == TG::button06) { //Pk-Pk Search
//            _markerCurrent = findPkPkSearch();
//        }
//
//        if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//            _markerArray[_activeMarker].v1 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//            _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//        } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//            _markerArray[_activeMarker].v2 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//            _markerArray[_activeMarker].x2 = ((_markerArray[_activeMarker].v2) / (_freqStop-_freqStart))*(0.8*2);
//        } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//            _markerArray[_activeMarker].v1 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//            _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//        } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//            _markerArray[_activeMarker].v1 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//            _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//        }
//
//        setChangedMarkers();
//        break;
//    }
//    case TG::typeReturn:
//        break;
//    case TG::typeResBw:
//        break;
//    case TG::typeVideoBw:
//        break;
//    case TG::typeUndef:
//        break;
//    }
//}
//
//void Controller::setMarkerToFreq(TG::MarkerToFreqType markerToFreqType)
//{
//    switch(markerToFreqType)
//    {
//    case TG::markerToCenter:
//        //_freqCenter = _markerArray[_activeMarker].v1;
//        setFreqCenter(_markerArray[_activeMarker].v1);
//        screenWidget()->redraw();
//        break;
//    case TG::markerToStep:
//        _freqStep = _markerArray[_activeMarker].v1;
//        screenWidget()->redraw();
//        break;
//    case TG::markerToStart:
//        //_freqStart = _markerArray[_activeMarker].v1;
//        setFreqStart(_markerArray[_activeMarker].v1);
//        screenWidget()->redraw();
//        break;
//    case TG::markerToStop:
//        //_freqStop = _markerArray[_activeMarker].v1;
//        setFreqStop(_markerArray[_activeMarker].v1);
//        screenWidget()->redraw();
//        break;
//    case TG::markerToRefLvl:
//        break;
//    case TG::markerToSpan:
//        //_freqSpan = _markerArray[_activeMarker].v1;
//        setFreqSpan(_markerArray[_activeMarker].v1);
//        screenWidget()->redraw();
//        break;
//    }
//
//    //setChangedMarkers();
//
//}
//
////void Controller::setSpectrumAnalyzer(const EmulatorDigital2 *emulatorDigital2)
////{
////    _emulatorDigital2 = const_cast<EmulatorDigital2 *>(emulatorDigital2);
////}
//
////const EmulatorDigital2 *Controller::spectrumAnalyzer(void)
////{
////    return const_cast<EmulatorDigital2 *>(_emulatorDigital2);
////}
//
//void Controller::setEmulatorDigital2(const EmulatorDigital2 *emulatorDigital2)
//{
//    _emulatorDigital2 = const_cast<EmulatorDigital2 *>(emulatorDigital2);
//}
//
//const EmulatorDigital2 *Controller::emulatorDigital2(void)
//{
//    return const_cast<EmulatorDigital2 *>(_emulatorDigital2);
//}
//
//void Controller::setEmulatorDigital3(const EmulatorDigital3 *emulatorDigital3)
//{
//    _emulatorDigital3 = const_cast<EmulatorDigital3 *>(emulatorDigital3);
//}
//
//const EmulatorDigital3 *Controller::emulatorDigital3(void)
//{
//    return const_cast<EmulatorDigital3 *>(_emulatorDigital3);
//}
//
//TG::MarkerType Controller::activeMarkerState(void)
//{
//    if(_markerArray.find(_activeMarker) != _markerArray.end()) {
//        return _markerArray[_activeMarker].type2;
//    } else {
//        //return TG::mrkOff;
//        return TG::mrkStandart;
//    }
//}
//
//double Controller::valueMarker(void)
//{
//    double value;
//
//    if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//        value = _markerArray[_activeMarker].v1;
//    } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//        value = _markerArray[_activeMarker].v2;
//    } else if(_markerArray[_activeMarker].type2 == TG::mrkFixed) {
//        value = _markerArray[_activeMarker].v1;
//    } else if(_markerArray[_activeMarker].type2 == TG::mrkOff) {
//        value = _markerArray[_activeMarker].v1;
//    }
//
//    return value;
//}
//
//void Controller::peakSearch(TG::PeakSearchType type)
//{
//    if(type == TG::peakSearchNext) { //Next Peak
//        _markerCurrent = findNextPeak();
//    } else if(type == TG::peakSearchNextRight) { //Next Pk Right
//        _markerCurrent = findNextPkRight();
//    } else if(type == TG::peakSearchNextLeft) { //Next Pk Left
//        _markerCurrent = findNextPkLeft();
//    } else if(type == TG::peakSearchMin) { //Min Search
//        _markerCurrent = findMinSearch();
//    } else if(type == TG::peakSearchPeakPeak) { //Pk-Pk Search
//        _markerCurrent = findPkPkSearch();
//    }
//
//    if(_markerArray[_activeMarker].type2 == TG::mrkStandart) {
//        _markerArray[_activeMarker].v1 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//        _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//    } else if(_markerArray[_activeMarker].type2 == TG::mrkDelta) {
//        _markerArray[_activeMarker].v2 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//        _markerArray[_activeMarker].x2 = ((_markerArray[_activeMarker].v2) / (_freqStop-_freqStart))*(0.8*2);
//    } else if(_markerArray[_activeMarker].type2 == TG::mrkBand) {
//        _markerArray[_activeMarker].v1 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//        _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//    } else if(_markerArray[_activeMarker].type2 == TG::mrkSpan) {
//        _markerArray[_activeMarker].v1 = (_markerCurrent*(_freqStop-_freqStart))/_number;
//        _markerArray[_activeMarker].x1 = ((_markerArray[_activeMarker].v1) / (_freqStop-_freqStart))*(0.8*2);
//    }
//
//    //boost::container::map<int, TG::MarkerItem>::iterator it(_markerArray.begin());
//    std::map<int, TG::MarkerItem>::iterator it(_markerArray.begin());
//    while(it!=_markerArray.end()) {
//        if(it->second.type2 != TG::mrkOff) {
//            it->second.drawn1 = true;
//            it->second.drawn2 = true;
//        }
//        ++it;
//    }
//    if(_markerArray[_activeMarker].x1 == _markerArray[_activeMarker].x1prev) {
//        _markerArray[_activeMarker].drawn1 = true;
//    }
//    if(_markerArray[_activeMarker].x2 == _markerArray[_activeMarker].x2prev) {
//        _markerArray[_activeMarker].drawn2 = true;
//    }
//
//    setChangedMarkers();
//}
//
//const double &Controller::data(const TG::ScreenItemType &type)
//{
//    if(_mainMenu == nullptr) {
//        _temp = 0.0;
//        return _temp;
//    }
//
//    //if(_mainMenu) return 0.0;
//
//    switch(type)
//    {
//    case TG::screen_Top0Left:
//        return _refLevl;
//        //break;
//    case TG::screen_Top0Center:
//        return _atten;
//        //break;
////    case TG::screen_LeftTop0:
////        return _time;
////        //break;
//    case TG::screen_Bottom0Left:
//    {
//        if( (_screenStates == TG::stateFreqCenter)
//        ) {
//            return _freqCenter;
//        } else {
//            return _freqStart;
//        }
//        //if( (_mainMenu->button() == TG::buttonSpan) ||
//        //    (_mainMenu->button() == TG::buttonFreq && _mainMenu->activeButton() == TG::button01)
//        //) {
//        //    return _freqCenter;
//        //} else {
//        //    return _freqStart;
//        //}
//        //break;
//    }
//    case TG::screen_Bottom0Right:
//    {
//        if( (_screenStates == TG::stateFreqCenter)
//        ) {
//            return _freqSpan;
//        } else {
//            return _freqStop;
//        }
//        //if( (_mainMenu->button() == TG::buttonSpan) ||
//        //    (_mainMenu->button() == TG::buttonFreq && _mainMenu->activeButton() == TG::button01)
//        //) {
//        //    return _freqSpan;
//        //} else {
//        //    return _freqStop;
//        //}
//        //break;
//    }
//    case TG::screen_Bottom1Left:
//        return _rbw;
//        //break;
//    case TG::screen_Bottom1Center:
//        return _vbw;
//        //break;
//    case TG::screen_Bottom1Right:
//        return _time;
//        //break;
//    default:
//        return _time;
//        //break;
//    }
//
//    //return _time;
//}
//
//const QString &Controller::unit(const TG::ScreenItemType &type)
//{
//    switch(type)
//    {
//    case TG::screen_Top0Left:
//        return _ref2LevlUnitText[_ref2LevlUnit];
//    case TG::screen_Top0Center:
//        return _ref2LevlUnitText[_attenUnit];
//    //case TG::screen_LeftTop0:
//    //    return _sweepUnitsText[_sweepUnit];
//    case TG::screen_Bottom0Left:
//        return _freqUnitText[_freqUnit];
//    case TG::screen_Bottom0Right:
//        return _freqUnitText[_freqUnit];
//    //case TG::screen_Bottom0Left:
//    //    return freqUnitText[_freqUnit];
//    //case TG::screen_Bottom0Right:
//    //    return freqUnitText[_spanUnit];
//    case TG::screen_Bottom1Left:
//        return _freqUnitText[_bwUnit];
//    case TG::screen_Bottom1Center:
//        return _freqUnitText[_bwUnit];
//    case TG::screen_Bottom1Right:
//        return _sweepUnitsText[_sweepUnit];
//    default:
//        return _sweepUnitsText[_sweepUnit];
//    }
//}
//
//int Controller::findNextPeak(void)
//{
//    float fmax(0.0);
//    int i(0);
//    if(_internalEmulator != 0) {
//        for(i=0; i<_number; i++) {
//            if(fmax < _dataArray2[i]) {
//                fmax = _dataArray2[i];
//                _nextPeak = i;
//            }
//        }
//    } else {
//        for(i=0; i<_number; i++) {
//            if(fmax < _dataArray3[i]) {
//                fmax = _dataArray3[i];
//                _nextPeak = i;
//            }
//        }
//    }
//    return _nextPeak;
//}
//
//int Controller::findNextPkRight(void)
//{
//    float fmax(0.0);
//    int i(0);
//    if(_internalEmulator != 0) {
//        for(i=_nextPeak+1; i<_number; i++) {
//            if(fmax < _dataArray2[i]) {
//                fmax = _dataArray2[i];
//                _nextPeakRight = i;
//            }
//        }
//    } else {
//        for(i=_nextPeak+1; i<_number; i++) {
//            if(fmax < _dataArray3[i]) {
//                fmax = _dataArray3[i];
//                _nextPeakRight = i;
//            }
//        }
//    }
//    return _nextPeakRight;
//}
//
//int Controller::findNextPkLeft(void)
//{
//    float fmax(0.0);
//    int i(0);
//
//    if(_nextPeak == 0) findNextPeak();
//
//    if(_internalEmulator != 0) {
//        for(i=0; i<_nextPeak; i++) {
//            if(fmax < _dataArray2[i]) {
//                fmax = _dataArray2[i];
//                _nextPeakLeft = i;
//            }
//        }
//    } else {
//        for(i=0; i<_nextPeak; i++) {
//            if(fmax < _dataArray3[i]) {
//                fmax = _dataArray3[i];
//                _nextPeakLeft = i;
//            }
//        }
//    }
//    return _nextPeakLeft;
//}
//
//int Controller::findMinSearch(void)
//{
//    float fmin(1e+10);
//    int i(0);
//    if(_internalEmulator != 0) {
//        for(i=0; i<_number; i++) {
//            if(fmin > _dataArray2[i]) {
//                fmin = _dataArray2[i];
//                _minSearch = i;
//            }
//        }
//    } else {
//        for(i=0; i<_number; i++) {
//            if(fmin > _dataArray3[i]) {
//                fmin = _dataArray3[i];
//                _minSearch = i;
//            }
//        }
//    }
//    return _minSearch;
//}
//
//int Controller::findPkPkSearch(void)
//{
//    int i(0);
//    if(_internalEmulator != 0) {
//        for(i=0; i<_number; i++) {
//            _dataArray2[i];
//        }
//    } else {
//        for(i=0; i<_number; i++) {
//            _dataArray3[i];
//        }
//    }
//    return 10;
//}
//
//void Controller::setMainMenu(const Menu::MainMenu3 *mainMenu)
//{
//    _mainMenu = const_cast<Menu::MainMenu3 *>(mainMenu);
//
//    TG::FreqParam freqParam;
//    freqParam._center = _freqCenter;
//    freqParam._span = _freqSpan;
//    freqParam._start = _freqStart;
//    freqParam._stop = _freqStop;
//    freqParam._step = _freqStep;
//    freqParam._offset = _freqOffset;
//    freqParam._unitText = _freqUnitText[_freqUnit];
//
//    TG::BwParam bwParam;
//    bwParam.resBw = _rbw;
//    bwParam.videoBw = _vbw;
//    bwParam.vbw3dbRbw = _vbw3dbRbw;
//    bwParam.span3dbRbw = _span3dbRbw;
//    bwParam.rbwFilterBw = _rbwFilterBw;
//    bwParam.unitText = _freqUnitText[_bwUnit];
//    bwParam.unitAmptText = _amptUnitText[_bwUnitAmpt];
//
//    TG::SweepParam sweepParam;
//    sweepParam._time = _time;
//    sweepParam._unit = _sweepUnit;
//    sweepParam._unitText = _sweepUnitsText[_sweepUnit];
//
//    TG::InputParam inputParam;
//    TG::DisplayParam displayParam;
//
//    _amptParam._flags = 0xffff;
//    freqParam._flags = 0xffff;
//    bwParam._flags = 0xffff;
//    sweepParam._flags = 0xffff;
//    inputParam._flags = 0xffff;
//    displayParam._flags = 0xffff;
//
//    sweepParam._flags = sweepParam._flags & ~TG::SweepParam::_EPOINTS;
//    freqParam._flags = freqParam._flags & ~TG::FreqParam::_EFULLSPAN;
//
//    emit amptChanged(_amptParam); //delay 2 sec
//    emit freqChanged(freqParam);
//    emit bwChanged(bwParam); //delay 2 sec
//    emit sweepChanged(sweepParam);
//    emit inputChanged(inputParam);
//    emit displayChanged(displayParam);
//
////    _keyPadNew2 = new KeyPadNew2(parent); //(this);
////    _keyPadNew2->move(_position.x(), _position.y());
//}
//
//void Controller::setSweepState(const TG::SweepStates &sweepStates)
//{
//    _sweepStates = sweepStates;
//
//    if(_internalEmulator != 0) {
//        _emulatorDigital2->setSweepState(sweepStates);
//    } else {
//        _emulatorDigital3->setSweepState(sweepStates);
//    }
//
//    screenWidget()->redraw();
//}
//
//void Controller::restartSweep(void)
//{
//    if(_internalEmulator != 0) {
//        _emulatorDigital2->restartSweep();
//    } else {
//        _emulatorDigital3->restartSweep();
//    }
//
//    screenWidget()->redraw();
//}
//
//void Controller::setFreq(void)
//{
//    TG::FreqParam freqParam;
//    freqParam._center = _freqCenter;
//    freqParam._span = _freqSpan;
//    freqParam._start = _freqStart;
//    freqParam._stop = _freqStop;
//    freqParam._step = _freqStep;
//    freqParam._offset = _freqOffset;
//    freqParam._unitText = _freqUnitText[_freqUnit];
//
//    freqParam._flags = 0xffff;
//    emit freqChanged(freqParam);
//}
//
//void Controller::setAmpt(void)
//{
//    //TG::AmptParam amptParam;
//    //amptParam.refLevl = _freqCenter;
//
//    _amptParam._flags = 0xffff;
//    emit amptChanged(_amptParam);
//}
//
//void Controller::setSweep(void)
//{
//    TG::SweepParam sweepParam;
//    sweepParam._time = _time;
//    sweepParam._unit = _sweepUnit;
//    sweepParam._unitText = _sweepUnitsText[_sweepUnit];
//
//    sweepParam._flags = 0xffff;
//    sweepParam._flags = sweepParam._flags & ~TG::SweepParam::_EAUTO & ~TG::SweepParam::_EPOINTS;
//
//    emit sweepChanged(sweepParam);
//}
//
////void Controller::setAmptMode(const TG::AmptModes &amptMode)
////{
////    _amptParam.amptMode = amptMode;
////    screenWidget()->redraw();
//
////    _amptParam._flags = 0xffff;
////    emit amptChanged(_amptParam);
//
////    _emulatorDigital2->restartSweep();
//
////    screenWidget()->redraw();
////}
//
//void Controller::setDisplayLog(bool displayLog)
//{
//    //_amptParam.amptMode = amptMode;
//    _amptParam.displayLog = displayLog;
//
//    //screenWidget()->setDataLog(_amptParam.displayLog);
//    screenWidget()->setAmptYAxis(_amptParam.yAxis);
//    screenWidget()->setDisplayLog(_amptParam.displayLog);
//
//    initYAxisRefLevl();
//    initYAxisUnits();
//
//    _amptParam._flags = 0xffff;
//    emit amptChanged(_amptParam);
//    _iemulatorDigital->restartSweep();
//    //_emulatorDigital2->restartSweep();
//    screenWidget()->redraw();
//}
//
//void Controller::setRefLevlUnit(const TG::RefLevlUnit &refLevlUnit)
//{
//    _refLevlUnit = refLevlUnit;
//    _amptParam.refLevlUnit = refLevlUnit;
//    //_amptParam._flags = 0xffff;
//    //emit amptChanged(_amptParam);
//}
//
//void Controller::initRefLevl(void)
//{
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm: //0: //dBm
//    {
//        _refLevl = 10*log10( (pow(_amptParam.relativeValue, 2.0) / 50.0 ) / 1e-3 );
//        break;
//    }
//    case TG::yAxisdBmV: //1: //dBmV
//    {
//        _refLevl = 20.0*log10( (_amptParam.relativeValue) / 1e-3 );
//        break;
//    }
//    case TG::yAxisWatt: //2: //Watt
//    {
//        _refLevl = pow(_amptParam.relativeValue, 2.0) / 50.0;
//        break;
//    }
//    case TG::yAxisVolt: //3: //Volt
//    {
//        _refLevl = _amptParam.relativeValue;
//        break;
//    }
//    }
//}
//
//void Controller::setRefLevl(double refLevl)
//{
//    Q_UNUSED(_amptParam.relativeValue);
//
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisUndef:
//    {
//        break;
//    }
//    case TG::yAxisdBm: //dBm
//    {
//        if(fabs(refLevl) < 1e-15) refLevl = 0.0;
//        _amptParam.relativeValue = pow( 50.0*pow(10.0, 0.1*refLevl)*1e-3, 0.5 );
//        break;
//    }
//    case TG::yAxisdBmV: //dBmV
//    {
//        _amptParam.relativeValue = 1e-3*pow(10.0, 0.05*refLevl);
//        break;
//    }
//    case TG::yAxisWatt: //Watt
//    {
//        _amptParam.relativeValue = pow( refLevl*50.0, 0.5 );
//        break;
//    }
//    case TG::yAxisVolt: //Volt
//    {
//        _amptParam.relativeValue = refLevl;
//        break;
//    }
//    }
//    _refLevl = refLevl;
//    _amptParam.refLevl = refLevl;
//
//    //initYAxisParams();
//    initYAxisUnits();
//
//    _amptParam._flags = 0xffff;
//    emit amptChanged(_amptParam);
//
//    //_emulatorDigital2->restartSweep();
//    if(_iemulatorDigital != nullptr) _iemulatorDigital->restartSweep();
//    screenWidget()->redraw();
//
//}
//
//void Controller::setAmptYAxis(const TG::AmptYAxis &yAxis)
//{
//    _amptParam.yAxis = yAxis;
//
//    screenWidget()->setAmptYAxis(_amptParam.yAxis);
//    screenWidget()->setDisplayLog(_amptParam.displayLog);
//
//    initYAxisRefLevl();
//    initYAxisUnits();
//
//    _amptParam._flags = 0xffff;
//    emit amptChanged(_amptParam);
//
//    //_emulatorDigital2->restartSweep();
//    if(_iemulatorDigital != nullptr) _iemulatorDigital->restartSweep();
//    screenWidget()->redraw();
//
//}
//
//TG::AmptYAxis &Controller::amptYAxis(void)
//{
//    return _amptParam.yAxis;
//}
//
//void Controller::setActiveTrace(const int &activetrace)
//{
//    _activeTrace = activetrace;
//
//    //screenWidget()->setAmptYAxis(_amptParam.yAxis);
//    //screenWidget()->setDisplayLog(_amptParam.displayLog);
//
//    //initYAxisRefLevl();
//    //initYAxisUnits();
//
//    //_amptParam._flags = 0xffff;
//    //emit amptChanged(_amptParam);
//    //_emulatorDigital2->restartSweep();
//    if(_iemulatorDigital != nullptr) {
//        _iemulatorDigital->setActiveTrace(_activeTrace);
//    }
//
//    screenWidget()->setActiveTrace(_activeTrace);
//    screenWidget()->redraw();
//}
//
//int Controller::activeTrace(void)
//{
//    return _activeTrace;
//}
//
//void Controller::setTypeTrace(const TG::TypeTrace &typeTrace)
//{
//    _typeTraces[_activeTrace] = typeTrace;
//
//    if(_iemulatorDigital != nullptr) {
//        _iemulatorDigital->setTypeTrace(_typeTraces[_activeTrace]);
//    }
//
//    screenWidget()->setTypeTrace(typeTrace);
//    screenWidget()->redraw();
//}
//
//const TG::TypeTrace &Controller::typeTrace(void)
//{
//    return _typeTraces[_activeTrace];
//}
//
//std::vector<TG::TypeTrace> &Controller::typeTraces(void)
//{
//    return _typeTraces;
//}
//
//void Controller::setTypeDetector(const TG::TypeDetector &typeDetector, bool hard)
//{
//    _typeDetectors[_activeTrace] = typeDetector;
//
//    //if(hard == true && _controllerVxi11 != NULL)
//    //    _controllerVxi11->putDetectorParam(_activeTrace, _typeDetectors[_activeTrace]);
//
//    //if(_iemulatorDigital != nullptr) {
//    //    _iemulatorDigital->setTypeTrace(_typeTraces[_activeTrace]);
//    //}
//
//    //screenWidget()->setTypeTrace(typeTrace);
//    screenWidget()->redraw();
//}
//
//const TG::TypeDetector &Controller::typeDetector(void)
//{
//	if (_typeDetectors.size())
//	    return _typeDetectors[_activeTrace];
//	else
//		return TG::detectorSample;
//}
//
//std::vector<TG::TypeDetector> &Controller::typeDetectors(void)
//{
//    return _typeDetectors;
//}
//
//void Controller::setAutoDetector(void)
//{
//	TG::TypeDetector typeDetector;
//
//	if (_typeDetectors.size()) 
//	{
//		_autoDetectors[_activeTrace] = true;
//		//if (_controllerVxi11 != nullptr) _controllerVxi11->putDetectorAutoParam(_activeTrace, typeDetector);
//		_typeDetectors[_activeTrace] = typeDetector;
//
//		screenWidget()->redraw();
//	}
//}
//
//void Controller::setAllAutoDetector(void)
//{
//    TG::TypeDetector typeDetector;
//
//    for(int i=0; i<_maxTraces; i++) {
//        _autoDetectors[i] = true;
//        //if(_controllerVxi11 != nullptr) _controllerVxi11->putDetectorAutoParam(i, typeDetector);
//        _typeDetectors[i] = typeDetector;
//    }
//
//    screenWidget()->redraw();
//}
//
//bool Controller::autoDetector(void)
//{
//	if (_typeDetectors.size())
//		return _autoDetectors[_activeTrace];
//	else
//		return TG::detectorSample;
//}
//
//std::vector<bool> &Controller::autoDetectors(void)
//{
//	return _autoDetectors;
//}
//
//void Controller::setFullSpan(bool hard)
//{
//    _freqParam._fullSpan = true;
//    _freqParam._zeroSpan = false;
//
//    //if(hard == true && _controllerVxi11 != NULL) {
//    //    _controllerVxi11->putFreqSpanParam(_freqParam);
//    //    _controllerVxi11->getFreqParam(_freqParam);
//
//    //    _freqParam._expFreq = _expFreq;
//    //    _freqCenter = _freqParam._center / _expValue[_expFreq];
//    //    _freqSpan = _freqParam._span / _expValue[_expFreq];
//    //    _freqStart = _freqParam._start / _expValue[_expFreq];
//    //    _freqStop = _freqParam._stop / _expValue[_expFreq];
//    //    _freqStep = _freqParam._step / _expValue[_expFreq];
//    //}
//
//    screenWidget()->redraw();
//}
//
//void Controller::setZeroSpan(bool hard)
//{
//    _freqParam._fullSpan = false;
//    _freqParam._zeroSpan = true;
//
//    //if(hard == true && _controllerVxi11 != NULL) {
//    //    _controllerVxi11->putFreqSpanParam(_freqParam);
//    //    _controllerVxi11->getFreqParam(_freqParam);
//
//    //    _freqParam._expFreq = _expFreq;
//    //    _freqCenter = _freqParam._center / _expValue[_expFreq];
//    //    _freqSpan = _freqParam._span / _expValue[_expFreq];
//    //    _freqStart = _freqParam._start / _expValue[_expFreq];
//    //    _freqStop = _freqParam._stop / _expValue[_expFreq];
//    //    _freqStep = _freqParam._step / _expValue[_expFreq];
//    //}
//
//    screenWidget()->redraw();
//}
//
//void Controller::restart(void)
//{
//    if(_internalEmulator != 0) {
//        _emulatorDigital2->restartSweep();
//    } else {
//        _emulatorDigital3->restartSweep();
//    }
//
//    screenWidget()->redraw();
//}
//
//void Controller::initYAxisRefLevl(void)
//{
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm: //dBm
//    {
//        screenWidget()->setDataLog();
//        double ftemp = 10.0*(double)log10(((double)pow(_amptParam.relativeValue, 2.0) / 50.0)*1e+3);
//
//        setRefLevl( 10.0*(double)log10(((double)pow(_amptParam.relativeValue, 2.0) / 50.0)*1e+3) );
//        setRefLevlUnit(TG::ref_dBm);
//        if(_amptParam.displayLog == true) {
//            screenWidget()->setUnitUp(refLevl());
//            screenWidget()->setUnitDown(refLevl() - 10.0*_amptParam.scaleDev);
//        } else {
//            screenWidget()->setUnitUp( 10.0*log10((pow(_amptParam.relativeValue, 2.0) / 50.0)*1e+3) );
//            //screenWidget()->setUnitDown(0);
//            screenWidget()->setUnitDown( 10.0*log10((pow(_amptParam.relativeValue/1e+12, 2.0) / 50.0)*1e+3) ); //can't define null
//        }
//        break;
//    }
//    case TG::yAxisdBmV: //dBmV
//    {
//        screenWidget()->setDataLog();
//        setRefLevl( 20.0*log10((_amptParam.relativeValue*1e+3)/1.0) );
//        setRefLevlUnit(TG::ref_dBmV);
//        if(_amptParam.displayLog == true) {
//            screenWidget()->setUnitUp(refLevl());
//            screenWidget()->setUnitDown(refLevl() - 10.0*_amptParam.scaleDev);
//        } else {
//            screenWidget()->setUnitUp( 20.0*log10((_amptParam.relativeValue*1e+3)/1.0) );
//            //screenWidget()->setUnitDown(0);
//            screenWidget()->setUnitDown( 20.0*log10((_amptParam.relativeValue/1e+12*1e+3)/1.0) ); //can't define null
//        }
//        break;
//    }
//    case TG::yAxisWatt: //Watt
//    {
//        screenWidget()->setDataLog(false);
//        setRefLevl( pow(_amptParam.relativeValue, 2.0) / 50.0 );
//        setRefLevlUnit(TG::ref_Watt);
//        if(_amptParam.displayLog == true) {
//            screenWidget()->setUnitUp(refLevl());
//            screenWidget()->setUnitDown(refLevl() * pow(10.0, -0.1*10.0*_amptParam.scaleDev));
//        } else {
//            screenWidget()->setUnitUp( pow(_amptParam.relativeValue, 2.0) / 50.0 );
//            screenWidget()->setUnitDown(0);
//        }
//        break;
//    }
//    case TG::yAxisVolt: //Volt
//    {
//        screenWidget()->setDataLog(false);
//        setRefLevl( _amptParam.relativeValue );
//        setRefLevlUnit(TG::ref_Volt);
//        if(_amptParam.displayLog == true) {
//            screenWidget()->setUnitUp(refLevl());
//            screenWidget()->setUnitDown(refLevl() * pow(10.0, -0.05*10.0*_amptParam.scaleDev));
//        } else {
//            screenWidget()->setUnitUp( _amptParam.relativeValue );
//            screenWidget()->setUnitDown(0);
//        }
//        break;
//    }
//    }
//}
//
//void Controller::initXAxisUnits(void)
//{
//    for(int i=0; i<=10; i++) {
//        _xAxisUnits.push_back(QString("%1").arg((double)i*16, 0, 'f', 1));
//    }
//}
//
//void Controller::initYAxisUnits(void)
//{
//    _yAxisUnits.clear();
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm: //0: //dBm
//    {
//        if(_amptParam.displayLog == true) {
//            for(int i=0; i<=10; i++) {
//                double value( refLevl() - i*_amptParam.scaleDev );
//                _yAxisUnits.push_back(QString("%1 %2").arg(value, 0, 'f', 1).arg("dBm"));
//            }
//        } else {
//            for(int i=0; i<=10; i++) {
//                double value( 10*log10( (pow(_amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * i), 2.0) / 50.0 ) / 1e-3 ) );
//                if( i < 10 )
//                    _yAxisUnits.push_back(QString("%1 %2").arg(value, 0, 'f', 2).arg("dBm"));
//                else
//                    _yAxisUnits.push_back(QString(""));
//            }
//        }
//        break;
//    }
//    case TG::yAxisdBmV: //1: //dBmV
//    {
//        if(_amptParam.displayLog == true) {
//            for(int i=0; i<=10; i++) {
//                double value( refLevl() - i*_amptParam.scaleDev );
//                _yAxisUnits.push_back(QString("%1 %2").arg(value, 0, 'f', 1).arg("dBmV"));
//            }
//        } else {
//            for(int i=0; i<=10; i++) {
//                double value( 20.0*log10( (_amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * i)) / 1e-3 ) );
//                if( i < 10 )
//                    _yAxisUnits.push_back(QString("%1 %2").arg(value, 0, 'f', 1).arg("dBmV"));
//                else
//                    _yAxisUnits.push_back(QString(""));
//            }
//        }
//        break;
//    }
//    case TG::yAxisWatt: //2: //Watt
//    {
//        if(_amptParam.displayLog == true) {
//            for(int i=0; i<=10; i++) {
//                double value( refLevl() * pow(10.0, -0.1*i*_amptParam.scaleDev) );
//                double fraction( value );
//                double exponent(0.0);
//                fractionAndExponent(fraction, exponent);
//                QString unitText = _unitText[exponent];
//                _yAxisUnits.push_back(QString("%1 %2%3").arg(fraction, 0, 'f', 1).arg(unitText).arg("W"));
//            }
//        } else {
//            for(int i=0; i<=10; i++) {
//                double value( pow(_amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * i), 2.0) / 50.0 );
//                double fraction( value );
//                double exponent(0.0);
//                fractionAndExponent(fraction, exponent);
//                QString unitText = _unitText[exponent];
//                _yAxisUnits.push_back(QString("%1 %2%3").arg(fraction, 0, 'f', 1).arg(unitText).arg("W"));
//            }
//        }
//        break;
//    }
//    case TG::yAxisVolt: //3: //Volt
//    {
//        if(_amptParam.displayLog == true) {
//            for(int i=0; i<=10; i++) {
//                double value( refLevl() * pow(10.0, -0.05*i*_amptParam.scaleDev) );
//                double fraction( value );
//                double exponent(0.0);
//                fractionAndExponent(fraction, exponent);
//                QString unitText = _unitText[exponent];
//                _yAxisUnits.push_back(QString("%1 %2%3").arg(fraction, 0, 'f', 1).arg(unitText).arg("V"));
//            }
//        } else {
//            for(int i=0; i<=10; i++) {
//                double value( _amptParam.relativeValue - (( _amptParam.relativeValue / 10.0) * i) );
//                double fraction( value );
//                double exponent(0.0);
//                fractionAndExponent(fraction, exponent);
//                QString unitText = _unitText[exponent];
//                _yAxisUnits.push_back(QString("%1 %2%3").arg(fraction, 0, 'f', 1).arg(unitText).arg("V"));
//            }
//        }
//        break;
//    }
//
//    }
//
//    //for(int i=0; i<=10; i++) {
//    //    _yAxisUnits.push_back(QString("%1").arg(i*32, 0, 'f', 1));
//    //}
//
//}
//
//void Controller::fractionAndExponent(double &fraction, double &exponent)
//{
//    exponent = 0.0;
//
//    if(fraction == 0.0) return;
//
//    if(abs(static_cast<int>(fraction)) < 1.0) {
//        int temp = abs(static_cast<int>(exponent)) % 3;
//        while(abs(static_cast<int>(fraction)) < 1.0 || exponent == 0.0 || abs(static_cast<int>(exponent)) % 3 != 0) {
//            int temp1 = abs(static_cast<int>(exponent));
//            int temp2 = abs(static_cast<int>(exponent)) % 3;
//            fraction *= 10;
//            exponent--;
//            if( exponent < -256.0 ) {
//                int i(0);
//                break;
//            }
//        }
//    }
//    if(fabs(static_cast<double>(fraction)) > 999.0) {
//        double ftemp = fabs(static_cast<double>(fraction));
//        int temp = static_cast<int>(exponent) % 3;
//        while(fabs(static_cast<double>(fraction)) > 999.0 || exponent == 0.0 || static_cast<int>(exponent) % 3 != 0) {
//            fraction /= 10;
//            exponent++;
//        }
//    }
//}
//
//QString Controller::unitTexts(double &exponent)
//{
//    QString unitText;
//    switch(_amptParam.yAxis)
//    {
//    case TG::yAxisdBm: //0: //dBm
//    {
//        unitText = QString("dBm");
//        break;
//    }
//    case TG::yAxisdBmV: //1: //dBmV
//    {
//        unitText = QString("dBmV");
//        break;
//    }
//    case TG::yAxisWatt: //2: //Watt
//    {
//        unitText = QString("%1W").arg(_unitText[exponent]);
//        break;
//    }
//    case TG::yAxisVolt: //3: //Volt
//    {
//        unitText = QString("%1V").arg(_unitText[exponent]);
//        break;
//    }
//    }
//
//    return unitText;
//}

int Controller::KeyPad(const TG::KeyPadParam &keyPadParam)
{
    //KeyPadNew2 *keyPadNew2 = new KeyPadNew2(this, keyPadParam);
    ////keyPadNew2->setText("The document has been modified.");
    ////keyPadNew2->setInformativeText("Do you want to save your changes?");
    ////keyPadNew2->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    ////keyPadNew2->setDefaultButton(QMessageBox::Save);
    //keyPadNew2->move(position.x(), position.y());

    _keyPad = true;

    _keyPadNew2->setParams(keyPadParam);
    int ret( _keyPadNew2->exec() );
    _position = _keyPadNew2->pos();
    //keyPadParam = _keyPadNew2->params();

    _keyPad = false;

    return ret;

    //if(ret == QDialog::Accepted)
    //{
    //}
    //position = keyPadNew2->pos();
    //delete keyPadNew2;
}

//void Controller::pressButton(QString &button)
//{
//    _keyPadNew2->pressButton(button);
//}
//
////int Controller::menuTopInput(void)
////{
////    _menuTopInput = new MenuTopInput(this);
////    //_menuTopInput->setParams(keyPadParam);
////    int ret = _menuTopInput->exec();
////    //_position = _keyPadNew2->pos();
////    delete _menuTopInput;
//
////    return ret;
////}

void Controller::getSelection(TG::UnitTypes &type, int &index, double &value)
{
    _keyPadNew2->getSelection(type, index, value);
}

//void Controller::getSelection(TG::UnitTypes &type, int &index, QString &text)
//{
//    _keyPadNew2->getSelection(type, index, text);
//}
//
//void Controller::editAntenn(void)
//{
//    emit signalEditAntenn();
//}
//
//void Controller::ShowAntennForm()
//{
//    //ControllerAntenn.ShowEditWindow(); // move to my slot
//
//    //bool antennValid;
//    //QString antennName = ControllerAntenn.GetActiveAntennName( &antennValid ); //получить название активного оконечного устройства
//    //emit nameChange(antennName);
//
//    int i(0);
//    Q_UNUSED(i)
//}
//
//void Controller::presetsChanged(void)
//{
//    applyPreset();
//
//    putFreqParams();
//    putAmptParams();
//    putSweepParams();
//    putBwParams();
//    putDisplayParams();
//
//}
//
//void Controller::presetsReseted(void)
//{
//    resetPreset();
//
//    putFreqParams();
//    putAmptParams();
//    putSweepParams();
//    putBwParams();
//    putDisplayParams();
//
//}
//
//void Controller::keyPadPressed(int keyCode, quint32 nativeModifiers)
//{
//    TG::IndexMenu indexMenu;
//
//    if(keyCode == Qt::Key_F) { //qDebug("f");
//        indexMenu = TG::indexFreq;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_K) { //qDebug("k");
//        indexMenu = TG::indexMarker;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_H) { //qDebug("h");
//        indexMenu = TG::indexPeakSearch;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_P) { //qDebug("p");
//        indexMenu = TG::indexUserMenu;
//        emit menuChanged(indexMenu);
//
//    } else if(keyCode == Qt::Key_A) { //qDebug("a");
//        indexMenu = TG::indexAmpt;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_B) { //qDebug("b");
//        indexMenu = TG::indexBw;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_C) { //qDebug("c");
//        indexMenu = TG::indexTrace;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_U) { //qDebug("u");
//        indexMenu = TG::indexUserMenu;
//        emit menuChanged(indexMenu);
//
//    } else if(keyCode == Qt::Key_W) { //qDebug("w");
//        indexMenu = TG::indexSweep;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_T) { //qDebug("t");
//        indexMenu = TG::indexTrigger;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_I) { //qDebug("i");
//        indexMenu = TG::indexInput;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_L) { //qDebug("l");
//
//    } else if(keyCode == Qt::Key_S) { //qDebug("s");
//        indexMenu = TG::indexMeasSetup;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_D) { //qDebug("d");
//        indexMenu = TG::indexDisplay;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_U) { //qDebug("u");
//        indexMenu = TG::indexUserMenu;
//        emit menuChanged(indexMenu);
//    } else if(keyCode == Qt::Key_F2) { //qDebug("F2"); //Save
//
//    } else if(keyCode == Qt::Key_M) { //qDebug("m"); //MODE/Meas
//    } else if(keyCode == Qt::Key_F3) { //qDebug("F3"); //Single
//        indexMenu = TG::indexSweep;
//        emit menuChanged(indexMenu);
//        emit menuSingleCont();
//    } else if(keyCode == Qt::Key_R) { //qDebug("r"); //Restart
//        indexMenu = TG::indexSweep;
//        emit menuChanged(indexMenu);
//        emit menuSingleRestart();
//    } else if(keyCode == Qt::Key_Q) { //qDebug("q"); //Quick Save
//
//    } else if(keyCode == Qt::Key_Left) { //qDebug("Left");
//        currentDown();
//    } else if(keyCode == Qt::Key_Up) { //qDebug("Up");
//        currentUp();
//    } else if(keyCode == Qt::Key_Down) { //qDebug("Down");
//        currentDown();
//    } else if(keyCode == Qt::Key_Right) { //qDebug("Right");
//        currentUp();
//    //} else if(keyCode == Qt::Key_Enter) { //qDebug("Enter");
//    } else if(keyCode == Qt::Key_Return) { //qDebug("Enter");
//        emit menuItemEdit(QString("Enter"));
//
//    } else if(keyCode == Qt::Key_PageDown) { //qDebug("Page Down");
//        currentUp();
//    } else if(keyCode == Qt::Key_PageUp) { //qDebug("Page Up");
//        currentDown();
//
//    } else if(keyCode == Qt::Key_Escape) { //qDebug("Esc");
//        emit menuItemEdit(QString("Esc"));
//    } else if(keyCode == Qt::Key_F1) { //qDebug("F1"); //Help
//    } else if(keyCode == Qt::Key_F4) { //qDebug("F4"); //System
//
//    } else if(keyCode == Qt::Key_7) { //qDebug("7");
//        emit menuItemEdit(QString("7"));
//    } else if(keyCode == Qt::Key_8) { //qDebug("8");
//        emit menuItemEdit(QString("8"));
//    } else if(keyCode == Qt::Key_9) { //qDebug("9");
//        emit menuItemEdit(QString("9"));
//    } else if(keyCode == Qt::Key_Backspace) { //qDebug("Backspace");
//        emit menuItemEdit(QString("Backspace"));
//
//    } else if(keyCode == Qt::Key_4) { //qDebug("4");
//        emit menuItemEdit(QString("4"));
//    } else if(keyCode == Qt::Key_5) { //qDebug("5");
//        emit menuItemEdit(QString("5"));
//    } else if(keyCode == Qt::Key_6) { //qDebug("6");
//        emit menuItemEdit(QString("6"));
//    } else if(keyCode == Qt::Key_Delete) { //qDebug("Del");
//        emit menuItemEdit(QString("Delete"));
//
//    } else if(keyCode == Qt::Key_1) { //qDebug("1");
//        emit menuItemEdit(QString("1"));
//    } else if(keyCode == Qt::Key_2) { //qDebug("2");
//        emit menuItemEdit(QString("2"));
//    } else if(keyCode == Qt::Key_3) { //qDebug("3");
//        emit menuItemEdit(QString("3"));
//    } else if(keyCode == Qt::Key_Control) { //qDebug("Ctrl");
//
//    } else if(keyCode == Qt::Key_0) { //qDebug("0");
//        emit menuItemEdit(QString("0"));
//    } else if(keyCode == Qt::Key_B) { //qDebug(".");
//        emit menuItemEdit(QString("."));
//    } else if(keyCode == Qt::Key_C) { //qDebug("-");
//    } else if(keyCode == Qt::Key_Alt) { //qDebug("Left Alt");
//
//    } else if(keyCode == Qt::Key_ScrollLock) { //qDebug("Scroll lock");
//    } else if(keyCode == Qt::Key_NumLock) { //qDebug("Num lock");
//    } else if(keyCode == Qt::Key_Tab) { //qDebug("Tab");
//
//    } else if(keyCode == Qt::Key_X) { //qDebug("ctrl-x");
//        if(nativeModifiers == 0x14) {
//            StopThreads();
//        }
//    }
//}

} // namespace Core

//double TG::dBm2dB::convert(const double &value, const bool &antenna, const double &index, const double &number)
//{
//    double value_;
//
//    if(_controller == 0)
//        value_ = value;
//    else
//        value_ = value + _controller->refLevlOffset();
//        //value_ = value;
//
//    //if(_controller->amptMode()==TG::amptModeLog) {
//    //    value_ = 20.0*log10((value+_controller->refLevlOffset())/_controller->value0());
//    //} else {
//    //    value_ = (value+_controller->refLevlOffset());
//    //}
//
//    double freq(0.0);
//    double dbAntenn(0.0);
//    if(antenna) {
//        freq = (_stop - _start)*(index/number) + _start;
//        //dbAntenn = ControllerAntenn.GetActiveAntennKoef_dB(freq);
//    }
//
//    if(index == 150) {
//        int i(0);
//    }
//    if(dbAntenn >= 1 && dbAntenn < 2) {
//        int i(0);
//        Q_UNUSED(i);
//    } else if(dbAntenn >= 2 && dbAntenn < 3) {
//        int i(0);
//        Q_UNUSED(i);
//    } else if(dbAntenn >= 3 && dbAntenn < 4) {
//        int i(0);
//        Q_UNUSED(i);
//    }
//
//    switch(_controller->amptYAxis())
//    {
//    case TG::yAxisdBm:
//    {
//        //value_ = 10.0*log10((pow(value, 2.0)/50.0)*1e+3); //+_controller->refLevl();
//        value_ = 10.0*log10((pow(value, 2.0)/50.0)*1e+3) - _controller->inputPreamp() + dbAntenn; //+_controller->refLevl();
//        break;
//    }
//    case TG::yAxisdBmV:
//    {
//        //value_ = 20.0*log10((value)*1e+3); //-_controller->refLevl();
//        value_ = 20.0*log10((value)*1e+3) - _controller->inputPreamp() + dbAntenn; //-_controller->refLevl();
//        break;
//    }
//    case TG::yAxisWatt:
//    {
//        //value_ = pow(value, 2.0)/50.0; //+_controller->refLevl();
//        value_ = pow(value * pow(10.0, -0.05*_controller->inputPreamp()), 2.0)/50.0;
//        break;
//    }
//    case TG::yAxisVolt:
//    {
//        //value_ = value; //+_controller->refLevl();
//        value_ = value * pow(10.0, -0.05*_controller->inputPreamp());
//        break;
//    }
//    }
//
//    //if(_controller->amptYAxis()==TG::yAxisdBm) {
//    //    value_ = 20.0*log10((value+_controller->refLevlOffset())/_controller->value0());
//    //} else {
//    //    value_ = (value+_controller->refLevlOffset());
//    //}
//
//    return value_;
//}
//
