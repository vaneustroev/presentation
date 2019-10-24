// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef EMULATOR
#define EMULATOR

//#include <boost/container/vector.hpp>
#include <vector>

#include <QWidget>
#include <QPushButton>

namespace Core {

class Emulator : public QWidget
{
    Q_OBJECT

public:
    explicit Emulator(QWidget *parent = 0);
    ~Emulator();

public:
    //void setDataArray(const boost::container::vector<double> &dataArray);
    //boost::container::vector<double> &dataArray() const;
    void setDataArray(const std::vector<double> &dataArray);
    std::vector<double> &dataArray() const;

    void setCurrentData(const double &data);
    double &currentData(void) const;

signals:
    void buttonClicked();

private:
    QPushButton *myButton;

    //boost::container::vector<double> _dataArray;
    std::vector<double> _dataArray;
};

} // namespace Core

#endif // EMULATOR

