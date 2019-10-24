// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: van
//
// @file   dialogsystemsettings2.h
// Created: 12.04.2017
//

#ifndef DIALOGMODEMEASVIEW_H
#define DIALOGMODEMEASVIEW_H

#include <memory>

#include <QtWidgets\QDialog>
#include <QtWidgets\QListView>
#include <QtWidgets\QListWidget>
#include <QtCore\QStringListModel>
#include <QtCore\QStringList>

namespace Ui {
class DialogModeMeasView;
}

class DialogModeMeasView : public QDialog
{
   Q_OBJECT

public:
   explicit DialogModeMeasView(QWidget *parent = 0);
   ~DialogModeMeasView();

   void fillCurrentMode(int current);
   void fillCurrentMeas(int current);
   void fillCurrentView(int current);

public slots:
   //void clickedSystem(void);
   //void clickedConfig(void);
   //void clickedUserInterface(void);
   //void clickedPowerOn(void);
   //void clickedRestoreDefault(void);
   //void clickedAlignments(void);
   //void clickedLicensing(void);
   //void clickedSecurity(void);
   //void clickedDiagnostics(void);
   //void clickedService(void);
   void clickedHelp(void);
   void clickedExit(void);
   void clickedCancel(void);
   void clickedOk(void);

   //void clickedModes(void);
   //void clickedMeases(void);
   //void clickedViewes(void);
   void rowChangedModes(int currentRow);
   void rowChangedMeases(int currentRow);
   void rowChangedViewes(int currentRow);

   int currentMode(void) { return _currentMode; }
   int currentMeas(void) { return _currentMeas; }
   int currentView(void) { return _currentView; }

private:
   int _currentMode;
   int _currentMeas;
   int _currentView;

   std::unique_ptr<wchar_t[]>  _pcaption;
   std::unique_ptr<wchar_t[]>  _ptext;

private:
    Ui::DialogModeMeasView *ui;
};

#endif // DIALOGMODEMEASVIEW_H

