// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef EMULATORANALOG
#define EMULATORANALOG

//#include <boost/container/vector.hpp>
#include <vector>

#include <QtWidgets\QWidget>
#include <QtWidgets\QPushButton>
#include <QTimer>

namespace Core {
class Controller;
} // namespace Core

namespace Core {

class EmulatorAnalog : public QWidget
{
    Q_OBJECT

public:
    //explicit EmulatorAnalog(QWidget *parent = 0, Controller *controller=0);
    explicit EmulatorAnalog(Core::Controller *controller=0);
    ~EmulatorAnalog();

public:
    //void setDataArray(const boost::container::vector<double> &dataArray);
    //boost::container::vector<double> &dataArray() const;
    void setDataArray(const std::vector<double> &dataArray);
    std::vector<double> &dataArray() const;

    void setCurrentData(const double &data);
    double &currentData(void) const;

signals:
    void buttonClicked();
    void dataChanged();


public slots:
    void processTimer(void);

private:
    QPushButton *myButton;
    //boost::container::vector<double> _dataArray;
    std::vector<double> _dataArray;
    QTimer *_timer;
    Core::Controller *_controller;
};

} // namespace Core

#endif // EMULATORANALOG

