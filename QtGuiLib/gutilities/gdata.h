// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef GDATA_H
#define GDATA_H

//#define WIN32_LEAN_AND_MEAN

#include <string>

#include <iostream>
#include <boost/regex.hpp>
//#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>

#include <QtWidgets\QApplication>
#include <QtWidgets\QMainWindow>
#include <QtWidgets\QTableWidgetItem>
#include <QtWidgets\QDesktopWidget>
#include <QTimer>
#include <QTime>
#include <QScreen>

#include "gcore/core.h"

namespace Core {

#ifdef Q_OS_LINUX
#else
#endif

#ifdef Q_OS_LINUX

class BaseItem
{
public:
    BaseItem() {;}
    ~BaseItem() {;}

public:
    virtual const int &test(const int &) const = 0;
};

class ItemSweep : public BaseItem
{
public:
    ItemSweep() : _param(0) {;}
    ~ItemSweep() {;}

public:
    const int &test(const int &) const override final //c++11
    {
        std::cout << "ItemSweep::test()" << std::endl;
        return _param;
    }

private:
    int _param;
};

class ItemFrequency : public BaseItem
{
public:
    ItemFrequency() : _param(0) {;}
    ~ItemFrequency() {;}

public:
    const int &test(const int &) const override
    {
        std::cout << "ItemFrequency::test()" << std::endl;
        return _param;
    }

private:
    int _param;
};

#else
#endif

class GData
{
public:
    GData();
    ~GData();

    //boost::container::vector<float> *dataArray(void) {return _dataArray;}
    //boost::container::vector<float> *dataArrayPrev(void) {return _dataArrayPrev;}
    //boost::container::vector<int> *indexArray(void) {return _indexArray;}

    //void setDataArray(boost::container::vector<float> *dataArray) {_dataArray = dataArray;}
    //void setDataArrayPrev(boost::container::vector<float> *dataArrayPrev) {_dataArrayPrev = dataArrayPrev;}
    //void setIndexArray(boost::container::vector<int> *indexArray) {_indexArray = indexArray;}

    boost::container::vector<float> *dataArray(void);
    boost::container::vector<float> *dataArrayPrev(void);
    boost::container::vector<int> *indexArray(void);

    void setDataArray(boost::container::vector<float> *dataArray);
    void setDataArrayPrev(boost::container::vector<float> *dataArrayPrev);
    void setIndexArray(boost::container::vector<int> *indexArray);

    static void testFunction(const std::pair<int, TG::MarkerItem> &p ) { Q_UNUSED(p); }

private:
    std::map<int, TG::MarkerItem> _markerArray;

    boost::container::vector<float> *_dataArray;
    boost::container::vector<float> *_dataArrayPrev;
    boost::container::vector<int> *_indexArray;

    char *_ch;

};

} // namespace Core

#endif // GDATA_H

