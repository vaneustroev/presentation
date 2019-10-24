// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef SCREEN2WIDGET_H
#define SCREEN2WIDGET_H

//#define WIN32_LEAN_AND_MEAN

#include <QPainter>
#include <QPaintEvent>
#include <QtWidgets/QWidget>

//#include "gcore/controller.h"

namespace Core {
class Controller;
} // namespace Core

//namespace Screen {

class Screen2Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Screen2Widget(QWidget *parent = 0);
    ~Screen2Widget();

signals:
    //void dataChanged(void);

public slots:
    void changeData();

public:
    void setController(Core::Controller *controller, const float &time);
    Core::Controller *controller(void);

protected:
    void paintEvent(QPaintEvent *event);
    //{
    //    Q_UNUSED(event)
    //
    //    QPainter painter(this);
    //    //painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    //    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap));
    //    painter.drawLine(10, 10, 10, 200);
    //}

private:
    Core::Controller *_controller;
};

//} // namespace Screen

#endif // SCREEN2WIDGET_H

