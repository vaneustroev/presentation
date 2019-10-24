// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file   dialogsystemsettings2.cpp
// Created: 12.04.2017
//

#include "dialogmessage.h"
#include "ui_dialogmessage.h"

#include "guiUnman.h"

DialogMessage::DialogMessage(QWidget *parent, wchar_t* _caption, wchar_t* _text)
   : QDialog(parent)
   , ui(new Ui::DialogMessage)
   //, _currentMode(g_Parameter._currentMenu->indexMode)
   //, _currentMeas(g_Parameter._currentMenu->indexMeas)
   //, _currentView(g_Parameter._currentMenu->indexView)
   , _timer(nullptr)
{
   ui->setupUi(this);

   this->setWindowTitle(QString::fromWCharArray(_caption));
   ui->label->setText(QString::fromWCharArray(_text));

   //setWindowFlags(Qt::FramelessWindowHint);

   _timer = new QTimer();
   _timer->setInterval(5000);

   connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

   _timer->start();
}

DialogMessage::~DialogMessage()
{
   delete _timer;
   delete ui;
}

void DialogMessage::updateTime()
{
   //ui->label->setText(QTime::currentTime().toString()); 
   _timer->stop();

   delete _timer;

   QDialog::accept();
}

//void DialogModeMeasView::fillCurrentMode(int current)
//{
//	QStringList listModes;
//	for (int i = 0; i < g_Parameter._modeMeasView->length; i++) {
//		listModes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].name);
//	}
//	_currentMode = current;
//
//	ui->listWidgetModes->clear();
//	ui->listWidgetModes->addItems(listModes);
//
//	if (listModes.size() == 0) {
//		ui->buttonOk->setDisabled(true);
//	}
//	else {
//		ui->buttonOk->setEnabled(true);
//	}
//}
//
//void DialogModeMeasView::fillCurrentMeas(int current)
//{
//	QStringList listMeases;
//	for (int j = 0; j < g_Parameter._modeMeasView->guiModes[_currentMode].length; j++) {
//		listMeases << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[_currentMode].guiMeases[j].name);
//	}
//	_currentMeas = current;
//
//	ui->listWidgetMeases->clear();
//	ui->listWidgetMeases->addItems(listMeases);
//
//	if (listMeases.size() == 0) {
//		ui->buttonOk->setDisabled(true);
//	}
//	else {
//		ui->buttonOk->setEnabled(true);
//	}
//}
//
//void DialogModeMeasView::fillCurrentView(int current)
//{
//	QStringList listViewes;
//	for (int k = 0; k < g_Parameter._modeMeasView->guiModes[_currentMode].guiMeases[_currentMeas].length; k++) {
//		listViewes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[_currentMode].guiMeases[_currentMeas].guiViewes[k].name);
//	}
//	_currentView = current;
//
//	ui->listWidgetViewes->clear();
//	ui->listWidgetViewes->addItems(listViewes);
//
//	if (listViewes.size() == 0) {
//		ui->buttonOk->setDisabled(true);
//	}
//	else {
//		ui->buttonOk->setEnabled(true);
//	}
//}

//void DialogModeMeasView::clickedHelp(void)
//{
//	;
//}
//
//void DialogModeMeasView::clickedExit(void)
//{
//	this->close();
//}
//
//void DialogModeMeasView::clickedCancel()
//{
//	this->close();
//}
//
//void DialogModeMeasView::clickedOk()
//{
//	int indexMeas(ui->listWidgetMeases->currentRow());
//	int indexView(ui->listWidgetViewes->currentRow());
//	indexMeas < 0 ? indexMeas = 0 : indexMeas;
//	indexView < 0 ? indexView = 0 : indexView;
//	g_Parameter._CallActivator(indexMeas, indexView);
//
//	this->close();
//}
//
//void DialogModeMeasView::rowChangedModes(int currentRow)
//{
//	_currentMode = currentRow;
//	//fillCurrentMeas(0);
//	fillCurrentMeas(_currentMeas);
//}
//
//void DialogModeMeasView::rowChangedMeases(int currentRow)
//{
//	_currentMeas = currentRow;
//	//fillCurrentView(0);
//	fillCurrentView(_currentView);
//}
//
//void DialogModeMeasView::rowChangedViewes(int currentRow)
//{
//	_currentView = currentRow;
//}
//
