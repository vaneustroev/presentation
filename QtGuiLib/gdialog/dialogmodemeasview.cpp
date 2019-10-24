// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file   dialogsystemsettings2.cpp
// Created: 12.04.2017
//

#include "dialogmodemeasview.h"
#include "ui_dialogmodemeasview.h"

#include "guiUnman.h"

DialogModeMeasView::DialogModeMeasView(QWidget *parent) 
   : QDialog(parent)
   , ui(new Ui::DialogModeMeasView)
   , _currentMode(g_Parameter._currentMenu->indexMode)
   , _currentMeas(g_Parameter._currentMenu->indexMeas)
   , _currentView(g_Parameter._currentMenu->indexView)
   , _pcaption(std::unique_ptr<wchar_t[]>(new wchar_t[1024]))
   , _ptext(std::unique_ptr<wchar_t[]>(new wchar_t[1024]))
{
   ui->setupUi(this);

   //std::unique_ptr<wchar_t*>  _ptext;

   connect(ui->listWidgetModes, SIGNAL(currentRowChanged(int)), this, SLOT(rowChangedModes(int)));
   connect(ui->listWidgetMeases, SIGNAL(currentRowChanged(int)), this, SLOT(rowChangedMeases(int)));
   connect(ui->listWidgetViewes, SIGNAL(currentRowChanged(int)), this, SLOT(rowChangedViewes(int)));

   connect(ui->buttonHelp, SIGNAL(clicked()), this, SLOT(clickedHelp()));
   connect(ui->buttonExit, SIGNAL(clicked()), this, SLOT(clickedExit()));
   connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(clickedCancel()));
   connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(clickedOk()));

   g_Parameter._currentMenu->indexMode;
   g_Parameter._currentMenu->indexMeas;
   g_Parameter._currentMenu->indexView;

   fillCurrentMode(_currentMode);
   fillCurrentMeas(_currentMeas);
   fillCurrentView(_currentView);

   ui->listWidgetModes->setCurrentRow(_currentMode);
   ui->listWidgetMeases->setCurrentRow(_currentMeas);
   ui->listWidgetViewes->setCurrentRow(_currentView);

   //QStringList listModes;
   //QStringList listMeases;
   //QStringList listViewes;

   //for (int i = 0; i < g_Parameter._modeMeasView->length; i++) {
   //   listModes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].name);
   //   for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].length; j++) {
   //      listMeases << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name);
   //      for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].length; k++) {
   //         listViewes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name);
   //      }
   //   }
   //}

   //ui->listWidgetModes->clear();
   //ui->listWidgetMeases->clear();
   //ui->listWidgetViewes->clear();

   //ui->listWidgetModes->addItems(listModes);
   //ui->listWidgetMeases->addItems(listMeases);
   //ui->listWidgetViewes->addItems(listViewes);

   //ui->listModes;
   //ui->listMeases;
   //ui->listViewes;

   //// Create model
   //QStringListModel *modelModes = new QStringListModel(this);
   //QStringListModel *modelMeases = new QStringListModel(this);
   //QStringListModel *modelViewes = new QStringListModel(this);
   //// Make data
   //QStringList listModes;
   //QStringList listMeases;
   //QStringList listViewes;
   ////List << "Clair de Lune" << "Reverie" << "Prelude";

   //for (int i = 0; i < g_Parameter._modeMeasView->length; i++) {
   //   listModes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].name);
   //   for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].length; j++) {
   //      listMeases << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name);
   //      for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].length; k++) {
   //         listViewes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name);
   //      }
   //   }
   //}
   //// Populate our model
   //modelModes->setStringList(listModes);
   //modelMeases->setStringList(listMeases);
   //modelViewes->setStringList(listViewes);

   //// Glue model and view together
   //ui->listModes->setModel(modelModes);
   //ui->listMeases->setModel(modelMeases);
   //ui->listViewes->setModel(modelViewes);

    //QPushButton *button1 = new QPushButton(this);
    //QPushButton *button2 = new QPushButton(this);
    //ui->stackedSystem->addWidget(button1);
    //ui->stackedSystem->addWidget(button2);
    //ui->stackedSystem->setCurrentIndex(2);
}

DialogModeMeasView::~DialogModeMeasView()
{
    delete ui;
}

void DialogModeMeasView::fillCurrentMode(int current)
{
   QStringList listModes;
   for (int i = 0; i < g_Parameter._modeMeasView->length; i++) {
      listModes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[i].name);
   }
   _currentMode = current;

   ui->listWidgetModes->clear();
   ui->listWidgetModes->addItems(listModes);

   if (listModes.size() == 0) {
      ui->buttonOk->setDisabled(true);
   }
   else {
      ui->buttonOk->setEnabled(true);
   }
}

void DialogModeMeasView::fillCurrentMeas(int current)
{
   QStringList listMeases;
   for (int j = 0; j < g_Parameter._modeMeasView->guiModes[_currentMode].length; j++) {
      listMeases << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[_currentMode].guiMeases[j].name);
   }
   _currentMeas = current;

   ui->listWidgetMeases->clear();
   ui->listWidgetMeases->addItems(listMeases);

   if (listMeases.size() == 0) {
      ui->buttonOk->setDisabled(true);
   }
   else {
      ui->buttonOk->setEnabled(true);
   }
}

void DialogModeMeasView::fillCurrentView(int current)
{
   QStringList listViewes;
   for (int k = 0; k < g_Parameter._modeMeasView->guiModes[_currentMode].guiMeases[_currentMeas].length; k++) {
      listViewes << QString::fromWCharArray(g_Parameter._modeMeasView->guiModes[_currentMode].guiMeases[_currentMeas].guiViewes[k].name);
   }
   _currentView = current;

   ui->listWidgetViewes->clear();
   ui->listWidgetViewes->addItems(listViewes);

   if (listViewes.size() == 0) {
      ui->buttonOk->setDisabled(true);
   }
   else {
      ui->buttonOk->setEnabled(true);
   }
}

/*
void DialogSystemSettings2::clickedSystem(void)
{
    ui->stackedSystem->setCurrentIndex(0);
}

void DialogSystemSettings2::clickedConfig(void)
{
    ui->stackedSystem->setCurrentIndex(1);
}

void DialogSystemSettings2::clickedUserInterface(void)
{
    ui->stackedSystem->setCurrentIndex(2);
}

void DialogSystemSettings2::clickedPowerOn(void)
{
    ui->stackedSystem->setCurrentIndex(3);
}

void DialogSystemSettings2::clickedRestoreDefault(void)
{
    ui->stackedSystem->setCurrentIndex(4);
}

void DialogSystemSettings2::clickedAlignments(void)
{
    ui->stackedSystem->setCurrentIndex(5);
}

void DialogSystemSettings2::clickedLicensing(void)
{
    ui->stackedSystem->setCurrentIndex(6);
}

void DialogSystemSettings2::clickedSecurity(void)
{
    ui->stackedSystem->setCurrentIndex(7);
}

void DialogSystemSettings2::clickedDiagnostics(void)
{
    ui->stackedSystem->setCurrentIndex(8);
}

void DialogSystemSettings2::clickedService(void)
{
    ui->stackedSystem->setCurrentIndex(9);
}*/

void DialogModeMeasView::clickedHelp(void)
{
    ;
}

void DialogModeMeasView::clickedExit(void)
{
    this->close();
}

void DialogModeMeasView::clickedCancel()
{
   this->close();
}

void DialogModeMeasView::clickedOk()
{
   int indexMode( ui->listWidgetModes->currentRow());
   int indexMeas( ui->listWidgetMeases->currentRow());
   int indexView( ui->listWidgetViewes->currentRow());

   if (indexMode < 0 || indexMeas < 0 || indexView < 0) 
   {
      QString _caption("ERROR!");
      QString _text("Need select all items!");

      _caption.toWCharArray(_pcaption.get());
      _text.toWCharArray(_ptext.get());
      *(_pcaption.get() + _caption.length()) = 0;
      *(_ptext.get() + _text.length()) = 0;

      mainWindow->_mainScreen->messageBox(_pcaption.get(), _ptext.get() );

      return;
   }

   QString text(QString("%1 / %2 / %3").arg(
      ui->listWidgetModes->item(indexMode)->text()).arg(
      ui->listWidgetMeases->item(indexMeas)->text()).arg(
      ui->listWidgetViewes->item(indexView)->text()) );

   mainWindow->setModeName(text);

   g_Parameter._CallActivator(indexMode, indexMeas, indexView);

//   mainWindow->_mainScreen->myResizeCallback(g_Parameter._modeMeasView->guiModes[indexMode].guiMeases[indexMeas].guiViewes[indexView].guiPanels[0].name, true);

   this->close();
}

void DialogModeMeasView::rowChangedModes(int currentRow)
{
   _currentMode = currentRow;
   //fillCurrentMeas(0);
   fillCurrentMeas(_currentMeas);
}

void DialogModeMeasView::rowChangedMeases(int currentRow)
{
   _currentMeas = currentRow;
   //fillCurrentView(0);
   fillCurrentView(_currentView);
}

void DialogModeMeasView::rowChangedViewes(int currentRow)
{
   _currentView = currentRow;
}

