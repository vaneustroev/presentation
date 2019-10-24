// Copyright (C) 2016 GAMMA All Rights Reserved.
// Author: van
//
// @file
// Created: 08.06.2016
//

#ifndef DATA_H
#define DATA_H

#include <QtCore\QMap>
#include <QtCore\QObject>
#include <QtCore\QSharedPointer>
#include <QtCore\QStringList>

namespace Core {
class Controller;
} // namespace Core

namespace TG
{

class DisplayParam : public QObject
{
public:
    DisplayParam(void){;}
    ~DisplayParam(void){;}

    enum {
        _ELINE = 0x01,
    };
    unsigned int _flags;

    bool _on;
    double _volt;
    QString _unit;
    //TG::RefLevlUnit refLevlUnit;
    //QString unit;

};

} // namespace TG

#endif // DATA_H

