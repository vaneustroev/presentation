// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <vector>
//#include <boost/container/vector.hpp>
//#include <boost/chrono.hpp>

//#include "gcore/controller.h"
//#include "gcore/core.h"

#include "guiUnman.h"
//#include "gmenu/gmenupage.h"
#include "gmenu/gmenuitem.h"

MenuItem::MenuItem(QWidget *parent, int itemIndex, int currentIndex, MenuPage*menuPage, QGroupBox *groupBox)
   : QLineEdit(parent)
   , _focus(false)
   , _itemIndex(itemIndex)
   , _currentIndex(currentIndex)
   , _menuPage(menuPage)
   , _groupBox(groupBox)
{
   this->setObjectName(QStringLiteral("item"));

   //_itemIndex = itemIndex;
   //_currentIndex = currentIndex;
   //_menuPage = menuPage;
}

MenuItem::~MenuItem()
{
   ;
}

void MenuItem::setFocus(Qt::FocusReason reason)
{
   int i(0);
}

void MenuItem::setFocus(void)
{
   int i(0);
}

void MenuItem::focusInEvent(QFocusEvent* e)
{
   if (e->reason() == Qt::MouseFocusReason) {
      // The mouse trigerred the event
      ;
   }
   else {
      ;
   }

   // You might also call the parent method.
   QLineEdit::focusInEvent(e);
}

void MenuItem::doWheelEvent(int delta)
{
   QRegExp rx("[ ]");
   QString value = text();
   QStringList valueParams = value.split(rx, QString::SkipEmptyParts);
   if (valueParams.size() == 2)
   {
      //_keyPadParam._fieldType = TG::typeFreqSpan;
      //_keyPadParam._value = valueParams[0].toDouble() + delta;
      //int index(currentIndex());

      //wcscpy(_unit, (wchar_t*)_keyPadParam._buttonNames[index].toStdWString().c_str());

      //setText(QString("%1 %2").arg((int)_keyPadParam._value).arg(_keyPadParam._buttonNames[index]));
      //g_Parameter._SetValue(itemIndex(), _keyPadParam._value, _unit, index);

      if(_menuPage == nullptr) 
         g_Parameter._WheelRotate(itemIndex(), delta);
      else
         g_Parameter._WheelRotate(_menuPage->itemIndex(), delta);
   }

}

void MenuItem::wheelEvent(QWheelEvent * event)
{
   //event->delta() can be negative or positive
   //this->setText("Delta Value: " + QString::number(event->delta()));

   QPoint numPixels = event->pixelDelta();
   QPoint numDegrees = event->angleDelta() / 8;
   QString delta = QString::number(event->delta());
   //QPoint numS;
   //QPoint numSteps;

   if (!numPixels.isNull()) {
      //numS = numPixels / 15;
      //scrollWithPixels(numPixels);
   }
   else if (!numDegrees.isNull()) {
      //numSteps = numDegrees / 15;
      //scrollWithDegrees(numSteps);
   }

   doWheelEvent(event->delta());

   event->accept();
};

//int MenuItem::init(const gsa::t::GuiPad &guiPad)
//{
//   ;
//}

MenuPushButton::MenuPushButton(QWidget *parent, int itemIndex, QGroupBox *groupBox)
   : QPushButton(parent)
   , _itemIndex(itemIndex)
   , _groupBox(groupBox)
{
   this->setObjectName(QStringLiteral("item"));

   //_itemIndex = itemIndex;
}

MenuPushButton::~MenuPushButton()
{
   ;
}

MenuRadioButton::MenuRadioButton(QWidget *parent, int itemIndex, int index, QGroupBox *groupBox)
   : QRadioButton(parent)
   , _itemIndex(itemIndex)
   , _index(index)
   , _groupBox(groupBox)
{
   this->setObjectName(QStringLiteral("item"));

   //_itemIndex = itemIndex;
   //_index = index;
}

MenuRadioButton::~MenuRadioButton()
{
   ;
}

MenuComboBox::MenuComboBox(QWidget *parent, int itemIndex, QGroupBox *groupBox)
   : QComboBox(parent)
   , _itemIndex(itemIndex)
   , _groupBox(groupBox)
{
   this->setObjectName(QStringLiteral("item"));

   //_itemIndex = itemIndex;
}

MenuComboBox::~MenuComboBox()
{
   int i = 0;
}

MenuColorSelector::MenuColorSelector(QWidget *parent, int itemIndex, QGroupBox *groupBox)
   : Color_Selector(parent)
   , _itemIndex(itemIndex)
   , _groupBox(groupBox)
{
   this->setObjectName(QStringLiteral("item"));

   //_itemIndex = itemIndex;
}

MenuColorSelector::~MenuColorSelector()
{
   ;
}

