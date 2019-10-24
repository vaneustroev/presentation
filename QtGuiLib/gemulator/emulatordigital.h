// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef EMULATORDIGITAL
#define EMULATORDIGITAL

//#include <boost/container/vector.hpp>
#include <vector>

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QList>
#include <QVector>
#include <QQueue>
#include <QStringList>

#include <QElapsedTimer>
#include <QtTest/QTest>

namespace Core {
class Controller;
} // namespace Core

namespace Core {

class EmulatorDigital : public QWidget
{
    Q_OBJECT

public:
    //explicit EmulatorDigital(QWidget *parent = 0, Controller *controller=0);
    explicit EmulatorDigital(Core::Controller *controller=0, int number=401);
    ~EmulatorDigital();

public:
    //void setDataArray(const boost::container::vector<float> dataArray);
    //boost::container::vector<float> dataArray() const;
    void setDataArray(const std::vector<float> dataArray);
    std::vector<float> dataArray() const;

    void setCurrentData(const float data);
    float currentData(void) const;

    void setCurrent(const int &current);
    int &current(void) const;

    void setTimer(const float &time);
    const float &timer(void);

signals:
    void buttonClicked();
    void dataChanged();

    void finished(); 	/* сигнал о завершении  работы эмулятора */

public slots:
    void processTimer(void);

    void process(); /*  запускает эмулятор */
    void stop(); /*  останавливает эмулятор */

private:
    //QPushButton *myButton;
    //boost::container::vector<float> _dataArray;
    //boost::container::vector<float> _dataArray1;
    //boost::container::vector<float> _dataArray2;
    std::vector<float> _dataArray;
    std::vector<float> _dataArray1;
    std::vector<float> _dataArray2;
    int _currentArray;
    QTimer *_timer;
    Core::Controller *_controller;

    float _min;
    float _max;
    int _number;
    int _current;
    float _coefficient;
    float _time;
    QElapsedTimer _elapsedTimer;
    qint64 _nanoSec;
    int _CycleNumber;
};

} // namespace Core

#endif // EMULATORDIGITAL

