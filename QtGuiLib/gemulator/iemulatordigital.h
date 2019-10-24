// Copyright (C) 2016 GAMMA All Rights Reserved.
// Author: van
//
// @file
// Created: 16.05.2016
//

#ifndef IEMULATORDIGITAL_H
#define IEMULATORDIGITAL_H

#include <QObject>

#include "gcore/core.h"

namespace Core {

class IEmulatorDigital : public QObject
{
    Q_OBJECT

public:
    IEmulatorDigital();
    virtual ~IEmulatorDigital();

    virtual int &current(void) const = 0;
    virtual void restartSweep(void) = 0;
    virtual void setActiveTrace(const int &activeTrace) = 0;
    virtual void setTypeTrace(const TG::TypeTrace &typeTrace) = 0;
    virtual void fillTypeTraces(const std::vector<TG::TypeTrace> &typeTraces) = 0;
};

} // namespace Core

#endif // IEMULATORDIGITAL_H

