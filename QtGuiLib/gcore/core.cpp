// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#include "gcore/core.h"

TG::KeyPadParam::KeyPadParam(QObject *parent, QString name, TG::UnitTypes unitType, int value)
    : QObject(parent)
    , _name(name)
    , _unitType(unitType)
    , _value(value)
    , _text("")
    , _fieldType(TG::typeUndef)
    , _buttonNames(QStringList())
{
    ;
}

TG::KeyPadParam::KeyPadParam(const TG::KeyPadParam &keyPadParam)
    //: QObject(static_cast<QObject>(keyPadParam))
{
    *this = keyPadParam;
}

TG::KeyPadParam& TG::KeyPadParam::operator=(const TG::KeyPadParam &keyPadParam)
{
    _name = keyPadParam._name;
    _unitType = keyPadParam._unitType;
    _value = keyPadParam._value;
    _text = keyPadParam._text;
    _fieldType = keyPadParam._fieldType;
    _buttonNames.clear();
    _buttonNames = keyPadParam._buttonNames;

    return *this;
}

//TG::KeyPadParam::KeyPadParam(TG::KeyPadParam KeyPadParam)
//    //: QObject(KeyPadParam)
//{
//    name = KeyPadParam.name;
//    unitType = KeyPadParam.unitType;
//    value = KeyPadParam.value;
//}

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

void SAItem::createChildren(QSharedPointer<Core::SAItem> &parent, QMap<TG::Button, QSharedPointer<Core::SAItem> > &childern)
{
    QMap<TG::Button, QSharedPointer<Core::SAItem> >::iterator it(childern.begin());
    while(it != childern.end()) {
        addChild(QSharedPointer<Core::SAItem>( new SAItem(parent, (*it)->button(), (*it)->name(), (*it)->type()) ));
        ++it;
    }
}

} // namespace Gm

