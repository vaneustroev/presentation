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

   //_timer->start();
}

DialogItemComboBox::~DialogItemComboBox()
{
   //delete _timer;
   delete ui;
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

