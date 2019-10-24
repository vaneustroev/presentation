// Copyright (C) 2016 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 25.04.2016
//

#ifndef CONTROLLERVXI11_H
#define CONTROLLERVXI11_H

#include <QtWidgets\QWidget>
#include <QtCore\QMutex>
#include <QtCore\QByteArray>
#include <QtCore\QBuffer>
#include <QtCore\QThread>
#include <QtCore\QMutex>

#include <vector>

#include "../gcore/data.h"
#include "../gcore/core.h"
#include "../gcore/vxi11interfacelib.h"

#define VXI11LIB

#ifdef VXI11LIB

#endif

namespace Core {

class ControllerVxi11Thread;

class ControllerVxi11 : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerVxi11(QWidget *parent = 0);
    ~ControllerVxi11();

    SESSION session(int index);
    int Init(QString ipAddress1, QString ipAddress2, TG::DeviceType type1, TG::DeviceType type2);
    int Free(void);
    int initDevice(int index, QString ipAddress, TG::DeviceType type);
    int freeDevice(int index);
    int stop(void);
    int Authentication(SESSION &ses_2_1);
    void setDeviceType(int index, TG::DeviceType type);
    void Emit(QString command, int number, double data);
    void setSlaveModeActive(bool bSlaveModeActive) {_bSlaveModeActive = bSlaveModeActive;}
    bool slaveModeActive(void) {return _bSlaveModeActive;}

    void __test(void);
    bool dataReady(int index) {return _dataReadyRules[index];}
    void setDataReady(bool dataReady, int index) {_dataReadyRules[index] = dataReady;}

    void getData(std::vector<double> &values, int index=0);
    void getFreqParam(TG::FreqParam &freqParam, int index=0);
    void putFreqParam(TG::FreqParam &freqParam, int index=0);
    void putFreqSpanParam(TG::FreqParam &freqParam, int index=0);
    void getSweepParam(TG::SweepParam &sweepParam, int index=0);
    void putSweepParam(TG::SweepParam &sweepParam, int index=0);
    void getAmptParam(TG::AmptParam &amptParam, int index=0);
    void putAmptParam(TG::AmptParam &amptParam, int index=0);

    void getBwParam(TG::BwParam &bwParam, int index=0);
    void putBwParam(TG::BwParam &bwParam, int index=0);
    void putRbwParam(TG::BwParam &bwParam, int index=0);
    void putVbwParam(TG::BwParam &bwParam, int index=0);

    void getDetectorsParam(TG::DetectorParam &detectorParam, int index=0);
    void putDetectorsParam(TG::DetectorParam &detectorParam, int index=0);
    void putDetectorParam(int trace, TG::TypeDetector &detectorParam, int index=0);
    void putDetectorAutoParam(int trace, TG::TypeDetector &typeDetector, int index=0);

    void getDisplayParam(TG::DisplayParam &displayParam, int index=0);
    void putDisplayParam(TG::DisplayParam &displayParam, int index=0);

    void getMarkerParam(TG::MarkerParam &markerParam, int index=0);
    void putMarkerParam(TG::MarkerParam &markerParam, int index=0);
    void putAllMarkersOff(TG::MarkerParam &markerParam, int index=0);

signals:
    void freqChanged(TG::FreqParam&);
    void amptChanged(TG::AmptParam&);
    void bwChanged(TG::BwParam&);
    void sweepChanged(TG::SweepParam&);
    void inputChanged(TG::InputParam&);
    void displayChanged(TG::DisplayParam&);
    void markerChanged(TG::MarkerParam&);
    void traceChanged(TG::TraceParam&);

private:
    Core::ControllerVxi11Thread *_controllerVxi11Thread;
    QThread *_thread;

    int iError;
    bool _bSlaveModeActive;

    QString _addresses[NUMBEROFDEVICES];
    SESSION _sessions[NUMBEROFDEVICES];
    TG::DeviceType _types[NUMBEROFDEVICES];
//    SESSION _session;
//    SESSION _session2;
//    SESSION ses_1_1;
//    //SESSION ses_1_2;
//    SESSION ses_2_1;

    QMutex	_mutex;

    int _maxTraces;
    //QString _paramSweepTime;
    //QString _paramSweepPoints;
    //QString _paramUnitPow;
    //QString _paramDisplayTraceY;
    //QString _paramDisplayTraceYrlevel;
    ////TG::AmptYAxis _yAxis;
    QString _paramSweepTimes[NUMBEROFDEVICES];
    QString _paramSweepPointses[NUMBEROFDEVICES];
    QString _paramUnitPowes[NUMBEROFDEVICES];
    QString _paramDisplayTraceYes[NUMBEROFDEVICES];
    QString _paramDisplayTraceYrleveles[NUMBEROFDEVICES];
    QString _paramDataFormates[NUMBEROFDEVICES];

    int iClientId;
    QByteArray g_qbaSignatureStepOne;
    QByteArray g_qbaSignatureStepTwo;
    QByteArray g_qbaSignatureStepThree;

    char _login[256];
    char _password[256];
    unsigned char digestL[16]; // массивы для MD5 хешей логина и пароля
    unsigned char digestP[16]; // массивы для MD5 хешей логина и пароля

    //bool _pointsChanged;
    //bool _detectorsChanged;
    //bool _displayChanged;
    //bool _dataReady;
    //bool _traceChanged;

    bool _pointsChangedRules[NUMBEROFDEVICES];
    bool _detectorsChangedRules[NUMBEROFDEVICES];
    bool _displayChangedRules[NUMBEROFDEVICES];
    bool _dataReadyRules[NUMBEROFDEVICES];
    bool _traceChangedRules[NUMBEROFDEVICES];

};

class ControllerVxi11Thread : public QObject
{
    Q_OBJECT

public:
    explicit ControllerVxi11Thread(ControllerVxi11 *controllerVxi11 = 0);
    ~ControllerVxi11Thread();

signals:
    void finished(); // сигнал о завершении  работы

public slots:
    void process(); // запускает
    void stop(); // останавливает

private:
    ControllerVxi11 *_controllerVxi11;
    bool _stop;
    double _time;
};

} // namespace Core

#endif // CONTROLLERVXI11_H

