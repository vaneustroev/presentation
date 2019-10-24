// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file   dialogsystemsettings2.cpp
// Created: 12.04.2017
//

#include "dialogitemcombobox.h"
#include "ui_DialogItemComboBox.h"

#include "guiUnman.h"

DialogItemComboBox::DialogItemComboBox(QWidget *parent, wchar_t* _caption, wchar_t* _text)
   : QDialog(parent)
   , ui(new Ui::DialogItemComboBox)
   //, _currentMode(g_Parameter._currentMenu->indexMode)
   //, _currentMeas(g_Parameter._currentMenu->indexMeas)
   //, _currentView(g_Parameter._currentMenu->indexView)
   //, _timer(nullptr)
{
   ui->setupUi(this);

   //this->setWindowTitle(QString::fromWCharArray(_caption));
   //ui->label->setText(QString::fromWCharArray(_text));

   //setWindowFlags(Qt::FramelessWindowHint);

   //_timer = new QTimer();
   //_timer->setInterval(5000);

   //connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

   connect(ui->modes, SIGNAL(currentIndexChanged(int)), this, SLOT(IndexChangedExpd(int)));
   connect(ui->modes, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(IndexChangedExpd(const QString &)));

   //_timer->start();
}

DialogItemComboBox::~DialogItemComboBox()
{
   //delete _timer;
   delete ui;
}

void DialogItemComboBox::keyPressEvent(QKeyEvent * event_)
{
   //if (event_->key() == Qt::Key_Enter || event_->key() == Qt::Key_Return)
   if (event_->key() == Qt::Key_Escape)
      return;
   QDialog::keyPressEvent(event_);
}

//void DialogItemComboBox::updateTime()
//{
//   //ui->label->setText(QTime::currentTime().toString()); 
//   _timer->stop();
//
//   delete _timer;
//
//   QDialog::accept();
//}

void DialogItemComboBox::setNames(QStringList names) 
{ 
   _names = names; 
   ui->modes->insertItems(0, _names); 
}; 

QStringList &DialogItemComboBox::names(void) 
{ 
   return _names; 
}; 

void DialogItemComboBox::IndexChangedExpd(int index) 
{ 
   index = index;

   if (index >= 0) {
      double value((double)index);
      wcscpy(_text, L"TRUE");
      g_Parameter._SetValue(_itemIndex, value, _text, index);
   }
   else {
      int i = 0;
   }
}
 
void DialogItemComboBox::IndexChangedExpd(const QString &name)
{
   int index = _names.indexOf(name);
   index = index;
}

void DialogItemComboBox::tablePanelIndexChangedExpd(int index, int flag)
{
   if (index == 0) {
      flag = flag;
      ui->modes->setCurrentIndex(index);
   }
}

