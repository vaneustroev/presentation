// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

// guiUnman.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <vector>

#include <thread>
#include <mutex>

#include "guiUnman.h"

#include "../gmain/mainwindow.h"

GuiObject guiObject; //pB
std::mutex g_mutex;

Main::MainWindow *mainWindow(nullptr);
QWaitCondition bufferNotEmpty;
//QWaitCondition bufferNotFull;
QMutex mutex;

void message(void)
{
   QMessageBox msgBox;

   msgBox.setText("The document has been modified.");
   msgBox.setInformativeText("Do you want to save your changes?");
   msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
   msgBox.setDefaultButton(QMessageBox::Save);

   int ret = msgBox.exec();
}

DWORD WINAPI ThreadProc(LPVOID _hostParameters)
{
   bool exit(false);
   //MBParameter *hostParameters(static_cast<MBParameter *>(_hostParameters));
   MBParameter *hostParameters((MBParameter *)_hostParameters);

   int argc(0);
   char **argv(NULL);

   int l_Result;
   wchar_t *l_pMessage = new wchar_t[500];
   wchar_t *l_pDigit = new wchar_t[10];
   l_pMessage[0] = 0;

   //p_App = new QApplication(argc, argv);
   QApplication _qApp(argc, argv);
   //QApplication a(argc, argv);

   //message();

   mainWindow = new Main::MainWindow();
   if (mainWindow == nullptr) {
      message();
   }
   else {
      mainWindow->grabGesture(Qt::PanGesture);
      mainWindow->grabGesture(Qt::PinchGesture);

      //std::wstringstream ss;
      //ss << L"!!!!!! _currentMenu->length == " << hostParameters->_currentMenu->length << "  capacity == " << hostParameters->_currentMenu->capacity;
      //MessageBox(NULL, ss.str().c_str(), L"Error", MB_OK);

      //int fdim[] = { 10 };

      mainWindow->putCurrentMenu(hostParameters->_currentMenu);

      mainWindow->init3();

      QDesktopWidget *desktop(QApplication::desktop());
      mainWindow->setGeometry(desktop->screenGeometry(0));

      mainWindow->setWindowModality(Qt::ApplicationModal);
      mainWindow->setWindowState(Qt::WindowMaximized | Qt::WindowFullScreen);

      mainWindow->setVisible(true);

      _qApp.exec();

      mainWindow->free3();

      hostParameters->_Exit();
   }

   //Main::MainWindow w;
   //QDesktopWidget *desktop(QApplication::desktop());
   //w.setGeometry(desktop->screenGeometry(0));

   ////#ifndef Q_OS_WIN
   //////w.setWindowState(Qt::WindowState(Qt::WindowFullScreen | windowState()));
   ////w.setWindowState(Qt::WindowFullScreen | w.windowState());
   ////#endif // Q_OS_WIN

   ////QScreen *workScreen = qApp->screens().at(qApp->screens().length()-1);
   //////w.windowHandle()->setScreen(qApp->screens().at(qApp->screens().length()-1));
   ////QWindow *wnd = w.windowHandle();
   ////w.windowHandle()->setScreen(workScreen);
   ////w.showFullScreen();
   //w.show();

   //return _qApp.exec();
   //_qApp.exec();



   //hostParameters = static_cast<MBParameter *>(_hostParameters);
   //l_Result = MessageBox(NULL, hostParameters->_Message, L"Message!", MB_OKCANCEL | MB_ICONINFORMATION);

   //l_Result = hostParameters->_Deleagate(l_Result);
   ////wcscat_s(l_pMessage, 500, L"В консольном окне введено: ");
   //wcscat_s(l_pMessage, 500, L"Return value : ");
   //_itow_s(l_Result, l_pDigit, sizeof(wchar_t) * 10, 10);
   //wcscat_s(l_pMessage, 500, l_pDigit);

   //l_Result = MessageBox(NULL, l_pMessage, L"Message!", MB_OK | MB_ICONINFORMATION);

   //if (hostParameters->_Exit != NULL)
   //	hostParameters->_Exit();

   //while (!exit)
   //{
   //	eventTypes type = guiObject.event();

   //	if (type  == eventTypes::eventStopApp) {
   //		exit = true;
   //	}
   //	//if (hostParameters->_Exit != NULL)
   //	//	hostParameters->_Exit();
   //}

   //message();

   //hostParameters = static_cast<MBParameter *>(_hostParameters);
   //l_Result = MessageBox(NULL, hostParameters->_Message, L"Message!", MB_OKCANCEL | MB_ICONINFORMATION);

   //delete p_App;

   delete [] l_pMessage;
   delete [] l_pDigit;

   return 0;
}

//__van__ 2019.08.08 
int main(int argc, char *argv[])
{
  g_Parameter._Deleagate = nullptr;   //MBResultDelegate *
  g_Parameter._SetValue = nullptr;    //SetValue *
  g_Parameter._WheelRotate = nullptr; //WheelRotate *
  g_Parameter._CallActivator = nullptr; //CallActivator *
  g_Parameter._Exit = nullptr;        //ExitDelegate *
  g_Parameter._GSetFocus = nullptr;   //GSetFocus *

  g_Parameter._Message = nullptr;     //wchar_t *

  _currentMenu.length = 0;
  _currentMenu.lengthScreen = 0;
  _currentMenu.capacity = 0;
  _currentMenu.indexMode = 0;
  _currentMenu.indexMeas = 0;
  _currentMenu.indexView = 0;
  _currentMenu.nameMode = L"nameMode";
  _currentMenu.nameMeas = L"nameMeas";
  _currentMenu.nameView = L"nameView";
  for (int i = 0; i < gsa::t::maxPad; i++) {
    _currentMenu.pads[i].capacity = 0;
    _currentMenu.pads[i].length = 0;
    _currentMenu.screenPads[i].capacity = 0;
    _currentMenu.screenPads[i].length = 0;
  }

  g_Parameter._currentMenu = &_currentMenu; //gsa::t::CurrentMenu *
  g_Parameter._modeMeasView;                //std::unique_ptr<gsa::t::ModeMeasView> 
  g_Parameter._tablePanelData = nullptr;    //gsa::t::TablePanelData *
  g_Parameter._tablePanel = nullptr;        //gsa::t::Table *

  g_Parameter._currentStyle.XAxisName = L"XAxisName";
  g_Parameter._currentStyle.YAxisName = L"YAxisName";
  g_Parameter._currentStyle.XAxisUnit = L"XAxisUnit";
  g_Parameter._currentStyle.YAxisUnit = L"YAxisUnit";
  g_Parameter._currentStyle._xscaling = AxisStyle::Linear;
  g_Parameter._currentStyle._yscaling = AxisStyle::Linear;
  g_Parameter._currentStyle._axisColour.Red = 128;
  g_Parameter._currentStyle._axisColour.Green = 128;
  g_Parameter._currentStyle._axisColour.Blue = 128;

  themeFont.type = 1;
  themeFont.description = L"description";
  themeFont.family = L"family";
  themeFont.size = 24;
  themeFont.style = L"normal";
  themeFont.color = L"ff00ff";
  themeItem.type = 1;
  themeItem.description = L"description";
  themeItem.value = L"0f3f3f";
  for (int i = 0; i < gsa::t::maxThemeFont; i++) {
    _theme.themeFonts[i] = themeFont;
  }
  for (int i = 0; i < gsa::t::maxThemeItem; i++) {
    _theme.themeItems[i] = themeItem;
  }
  g_Parameter._theme = &_theme; //gsa::t::Theme *

  LPVOID _hostParameters(static_cast<LPVOID>(&g_Parameter));
  MBParameter *hostParameters((MBParameter *)_hostParameters);

  QApplication _qApp(argc, argv);

  mainWindow = new Main::MainWindow();
  if (mainWindow == nullptr) {
    message();
  }
  else {
    mainWindow->grabGesture(Qt::PanGesture);
    mainWindow->grabGesture(Qt::PinchGesture);

    mainWindow->putCurrentMenu(hostParameters->_currentMenu);

    mainWindow->init3();

    QDesktopWidget *desktop(QApplication::desktop());
    mainWindow->setGeometry(desktop->screenGeometry(0));

    mainWindow->setWindowModality(Qt::ApplicationModal);
    mainWindow->setWindowState(Qt::WindowMaximized | Qt::WindowFullScreen);

    mainWindow->setVisible(true);

    _qApp.exec();

    mainWindow->free3();

    if (hostParameters->_Exit != nullptr)
      hostParameters->_Exit();
  }
}

GuiObject::GuiObject()
{
}

GuiObject::~GuiObject()
{
}

void GuiObject::putEvent(eventTypes type)
{
	std::lock_guard<std::mutex> lock(g_mutex);

	_type = type;
}

eventTypes GuiObject::event(void)
{
	std::lock_guard<std::mutex> lock(g_mutex);

	return _type;
}

