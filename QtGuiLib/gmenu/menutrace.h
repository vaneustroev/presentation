// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUTRACE_H
#define MENUTRACE_H

#include <QWidget>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuTrace;
}

namespace Menu
{

class MenuTrace : public QWidget
{
    Q_OBJECT

public:
    explicit MenuTrace(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuTrace();

    //void menuItemEdit(QString text);
    //bool eventFilter(QObject* object, QEvent* event);
    void fillTypeTraces(const std::vector<TG::TypeTrace> &typeTraces);
    void fillTypeDetectors(const std::vector<TG::TypeDetector> &typeDetectors);
    void fillAutoDetectors(const std::vector<bool> &autoDetectors);
    void setTypeTrace(void);
    void setTypeDetector(void);
    void setAutoDetector(void);
    void setParam(TG::TraceParam &traceParam);

private slots:
    void slotCurrentIndexChanged(int index);
    void onActivated(int index);
    void clickTraceClear(void);
    void clickTraceAver(void);
    void clickTraceMax(void);
    void clickTraceMin(void);
    void clickTraceView(void);
    void clickTraceBlank(void);

    void clickDetectorApeak(void);
    void clickDetectorNegative(void);
    void clickDetectorPositive(void);
    void clickDetectorSample(void);
    void clickDetectorRms(void);

    void clickDetectorAuto(void);
    void clickDetectorMan(void);
    void clickDetectorAutoAll(void);

private:
    Ui::MenuTrace *ui;

    Core::Controller *_controller;

    std::vector<TG::TypeTrace> _typeTraces;
    std::vector<TG::TypeDetector> _typeDetectors;
    std::vector<bool> _autoDetectors;
};

} // namespace M

#endif // MENUTRACE_H

