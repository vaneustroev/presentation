// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h" 
#include "Marshaller.h" 

#include "guiUnman.h" 

#include <iostream> 
#include <sstream> 
#include <vector> 
#include <thread> 

#include <locale.h> 
#include <process.h> 
#include <windows.h> 
#include <stdio.h> 
#include <time.h> 

MBParameter g_Parameter;
HANDLE mainThread;
bool modeMeasViewInit(false);
bool panelInit(false);
bool tablePanelInit(false);
bool menuInit(false);
bool styleInit(false);
bool themeInit(false);

//VoidDelegate *VSyncCallback;
//VoidStringIntDelegate *ResizeCallback;
//VoidStringRangeDelegate *RerangeXCallback, *RerangeYCallback;
//
//__van__ 2019.08.08 
VoidDelegate *VSyncCallback(nullptr);
VoidStringIntDelegate *ResizeCallback(nullptr);
VoidStringRangeDelegate *RerangeXCallback(nullptr), *RerangeYCallback(nullptr);

//__van__ 2019.08.08 
gsa::t::Theme _theme;
gsa::t::ThemeFont themeFont;
gsa::t::ThemeItem themeItem;
gsa::t::CurrentMenu _currentMenu;

//$(ProgramW6432)\dotnet\dotnet.exe
//$(OutDir)host.dll
//$(ProjectDir)

extern   "C"
{
   BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
   {
      switch (ul_reason_for_call)
      {
      case DLL_PROCESS_ATTACH:
         //p_App = NULL;
         VSyncCallback = NULL;
         ResizeCallback = NULL;
         RerangeXCallback = NULL;
         RerangeYCallback = NULL;
         break;

      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
         break;
      }
      return TRUE;
   }

   //D:\Qt\Qt5.9.1\5.9.1\msvc2017_64\include
   //D:\Qt\Qt5.9.1\5.9.1\msvc2017_64\lib
   //Qt5Widgetsd.lib;Qt5Cored.lib;Qt5Guid.lib;

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE putVSync(LPVOID _VSync)
   {
     //__van__ 2019.08.08 
     //if (VSyncCallback != nullptr)
     VSyncCallback = static_cast<VoidDelegate *>(_VSync);
     return 0;
   }

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE putDevices(int uiType, int devType)
   {
      return 0;
   }

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE putModeMeasView(gsa::t::ModeMeasView *_modeMeasView)
   {
      if (modeMeasViewInit == true) {
         for (int i = 0; i < g_Parameter._modeMeasView->capacity; i++) {
            for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) {
               for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
                  for (int l = 0; l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].capacity; l++) {
                     delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name;
                  }
                  delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name;
               }
               delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name;
            }
            delete[] g_Parameter._modeMeasView->guiModes[i].name;
         }
         delete[] g_Parameter._modeMeasView->name;
         //delete g_Parameter._modeMeasView;
         //g_Parameter._modeMeasView.reset(nullptr);
      }

      //g_Parameter._modeMeasView = new gsa::t::ModeMeasView;
      if (!g_Parameter._modeMeasView) {
         //g_Parameter._modeMeasView = std::unique_ptr<gsa::t::ModeMeasView>(new gsa::t::ModeMeasView);
         //g_Parameter._modeMeasView.reset(new gsa::t::ModeMeasView);
         g_Parameter._modeMeasView = std::make_unique<gsa::t::ModeMeasView>();
      }
      memcpy(g_Parameter._modeMeasView.get(), _modeMeasView, sizeof(gsa::t::ModeMeasView));
      g_Parameter._modeMeasView->name = new wchar_t[1024];
      //if ( !g_Parameter._modeMeasView->name ) 
      //   g_Parameter._modeMeasView->name = std::unique_ptr<wchar_t[]>(new wchar_t[1024]); 
      for (int i = 0; i < g_Parameter._modeMeasView->capacity; i++) { 
         //g_Parameter._modeMeasView->guiModes[i].name = new wchar_t[1024]; 
         if (i < g_Parameter._modeMeasView->length) { 
            g_Parameter._modeMeasView->guiModes[i].name = new wchar_t[1024]; 
            //if (!g_Parameter._modeMeasView->guiModes[i].name)
            //   g_Parameter._modeMeasView->guiModes[i].name = std::unique_ptr<wchar_t[]>(new wchar_t[1024]);
            wcscpy(g_Parameter._modeMeasView->guiModes[i].name, _modeMeasView->guiModes[i].name);
         }
         for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) {
            //g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name = new wchar_t[1024];
            if (j < g_Parameter._modeMeasView->guiModes[i].length ) 
            {
               g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name = new wchar_t[1024];
               if (_modeMeasView->guiModes[i].guiMeases[j].name != nullptr) {
                  wcscpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name, _modeMeasView->guiModes[i].guiMeases[j].name);
               }
               else {
                  memcpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name, "", sizeof(wchar_t) * 1024);
               }
            }
            for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
               //g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name = new wchar_t[1024];
               if (k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].length ) 
               {
                  g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name = new wchar_t[1024];
                  if (_modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name != nullptr) {
                     wcscpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name, _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name);
                  }
                  else {
                     memcpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name, "", sizeof(wchar_t) * 1024);
                  }
               }

               g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].type = _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].type;
               for (int l = 0; l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].capacity; l++) {
                  //g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name = new wchar_t[1024];
                  if (l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].length) 
                  {
                     g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].position = _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].position;
                     g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].type = _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].type;
                     g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name = new wchar_t[1024];
                     if (_modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name != nullptr) {
                        wcscpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name, _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name);
                     }
                     else {
                        memcpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name, "", sizeof(wchar_t) * 1024);
                     }
                  }
               }
            }
         }
      }

      modeMeasViewInit = true;

      return 0;
   }

   //--------------------------------------------------------------------------------------------------// 
   DLL_TYPE putTheme(gsa::t::Theme *_theme)
   {
      _theme = _theme;

      if (themeInit == true) {
         for (int i = 0; i < gsa::t::maxThemeFont; i++) {
            delete[] g_Parameter._theme->themeFonts[i].description;
            delete[] g_Parameter._theme->themeFonts[i].family;
            delete[] g_Parameter._theme->themeFonts[i].style;
            delete[] g_Parameter._theme->themeFonts[i].color;
         }
         for (int i = 0; i < gsa::t::maxThemeItem; i++) {
            delete[] g_Parameter._theme->themeItems[i].description;
            delete[] g_Parameter._theme->themeItems[i].value;
         }
         delete g_Parameter._theme;
      }

      //g_Parameter._theme->themeFonts = new gsa::t::ThemeFont[gsa::t::maxThemeFont];
      //g_Parameter._theme->themeItems = new gsa::t::ThemeItem[gsa::t::maxThemeItem];
      g_Parameter._theme = new gsa::t::Theme;
      for (int i = 0; i < gsa::t::maxThemeFont; i++) {
         g_Parameter._theme->themeFonts[i].description = new wchar_t[1024];
         g_Parameter._theme->themeFonts[i].family = new wchar_t[1024];
         g_Parameter._theme->themeFonts[i].style = new wchar_t[1024];
         g_Parameter._theme->themeFonts[i].color = new wchar_t[1024];

         if(_theme->themeFonts[i].description != nullptr)
            wcscpy(g_Parameter._theme->themeFonts[i].description, _theme->themeFonts[i].description);
         if (_theme->themeFonts[i].family != nullptr)
            wcscpy(g_Parameter._theme->themeFonts[i].family, _theme->themeFonts[i].family);
         if (_theme->themeFonts[i].description != nullptr)
            wcscpy(g_Parameter._theme->themeFonts[i].style, _theme->themeFonts[i].style);
         if (_theme->themeFonts[i].description != nullptr)
            wcscpy(g_Parameter._theme->themeFonts[i].color, _theme->themeFonts[i].color);

         g_Parameter._theme->themeFonts[i].size = _theme->themeFonts[i].size;
      }
      for (int i = 0; i < gsa::t::maxThemeItem; i++) {
         g_Parameter._theme->themeItems[i].description = new wchar_t[1024];
         g_Parameter._theme->themeItems[i].value = new wchar_t[1024];

         g_Parameter._theme->themeItems[i].type = _theme->themeItems[i].type;
         if(_theme->themeItems[i].description != nullptr)
            wcscpy(g_Parameter._theme->themeItems[i].description, _theme->themeItems[i].description);
         if (_theme->themeItems[i].value != nullptr)
            wcscpy(g_Parameter._theme->themeItems[i].value, _theme->themeItems[i].value);
      }

      if (themeInit) {
         mainWindow->putTheme(g_Parameter._theme);
      }

      themeInit = true;

      return 0;
   }

   //--------------------------------------------------------------------------------------------------// 
   DLL_TYPE putCurrentMenu(gsa::t::CurrentMenu *_currentMenu) 
   { 
      if (menuInit == true) { 
         for (int i = 0; i < g_Parameter._currentMenu->capacity; i++) { 
            for (int j = 0; j < g_Parameter._currentMenu->pads[i].capacity; j++) { 
               if (j < g_Parameter._currentMenu->pads[i].length)
               {
                  for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].guilist.capacity; k++) {
                     if (k < g_Parameter._currentMenu->pads[i].items[j].guilist.length)
                        delete[] g_Parameter._currentMenu->pads[i].items[j].guilist.names[k];
                  }
                  for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].capacity; k++) {
                     if (k < g_Parameter._currentMenu->pads[i].items[j].length)
                        delete[] g_Parameter._currentMenu->pads[i].items[j].units[k];
                  }
                  delete[] g_Parameter._currentMenu->pads[i].items[j].name;
                  delete[] g_Parameter._currentMenu->pads[i].items[j].type;
                  delete[] g_Parameter._currentMenu->pads[i].items[j].unit;
               }
               if (j < g_Parameter._currentMenu->screenPads[i].length)
               {
                  for (int k = 0; k < g_Parameter._currentMenu->screenPads[i].items[j].guilist.capacity; k++) {
                     if (k < g_Parameter._currentMenu->screenPads[i].items[j].guilist.length)
                        delete[] g_Parameter._currentMenu->screenPads[i].items[j].guilist.names[k];
                  }
                  for (int k = 0; k < g_Parameter._currentMenu->screenPads[i].items[j].capacity; k++) {
                     if (k < g_Parameter._currentMenu->screenPads[i].items[j].length)
                        delete[] g_Parameter._currentMenu->screenPads[i].items[j].units[k];
                  }
                  delete[] g_Parameter._currentMenu->screenPads[i].items[j].name;
                  delete[] g_Parameter._currentMenu->screenPads[i].items[j].type;
                  delete[] g_Parameter._currentMenu->screenPads[i].items[j].unit;
               }
            }
            if (i < g_Parameter._currentMenu->length)
            {
               delete[] g_Parameter._currentMenu->pads[i].name;
               delete[] g_Parameter._currentMenu->pads[i].tab;
            }
            if (i < g_Parameter._currentMenu->lengthScreen)
            {
               delete[] g_Parameter._currentMenu->screenPads[i].name;
               delete[] g_Parameter._currentMenu->screenPads[i].tab;
            }
         }
         delete[] g_Parameter._currentMenu->nameMode;
         delete[] g_Parameter._currentMenu->nameMeas;
         delete[] g_Parameter._currentMenu->nameView;

         delete g_Parameter._currentMenu;
      }

      g_Parameter._currentMenu = new gsa::t::CurrentMenu;
      memcpy(g_Parameter._currentMenu, _currentMenu, sizeof(gsa::t::CurrentMenu));
      g_Parameter._currentMenu->nameMode = new wchar_t[1024];
      g_Parameter._currentMenu->nameMeas = new wchar_t[1024];
      g_Parameter._currentMenu->nameView = new wchar_t[1024];
      wcscpy(g_Parameter._currentMenu->nameMode, _currentMenu->nameMode);
      wcscpy(g_Parameter._currentMenu->nameMeas, _currentMenu->nameMeas);
      wcscpy(g_Parameter._currentMenu->nameView, _currentMenu->nameView);
      for (int i = 0; i < g_Parameter._currentMenu->capacity; i++) 
      {
         if (i < g_Parameter._currentMenu->length) 
         {
            g_Parameter._currentMenu->pads[i].name = new wchar_t[1024];
            g_Parameter._currentMenu->pads[i].tab = new wchar_t[1024];
            wcscpy(g_Parameter._currentMenu->pads[i].name, _currentMenu->pads[i].name);
            wcscpy(g_Parameter._currentMenu->pads[i].tab, _currentMenu->pads[i].tab);
         }
         if (i < g_Parameter._currentMenu->lengthScreen)
         {
            g_Parameter._currentMenu->screenPads[i].name = new wchar_t[1024];
            g_Parameter._currentMenu->screenPads[i].tab = new wchar_t[1024];
            wcscpy(g_Parameter._currentMenu->screenPads[i].name, _currentMenu->screenPads[i].name);
            if(_currentMenu->screenPads[i].tab != nullptr)
               wcscpy(g_Parameter._currentMenu->screenPads[i].tab, _currentMenu->screenPads[i].tab);
         }
         for (int j = 0; j < g_Parameter._currentMenu->pads[i].capacity; j++)
         {
            //for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].capacity; k++) {
            //   g_Parameter._currentMenu->pads[i].items[j].units[k] = new wchar_t[1024];
            //}
            wchar_t *type = _currentMenu->pads[i].items[j].type;
            if (QString::fromWCharArray(type) == QString("ColourSelector")) {
               int i(0);
            }
            g_Parameter._currentMenu->pads[i].items[j].value = _currentMenu->pads[i].items[j].value;
            if (_currentMenu->pads[i].items[j].value != 0.0) {
               int i(0);
            }
            if (j < g_Parameter._currentMenu->pads[i].length) 
            {
               g_Parameter._currentMenu->pads[i].items[j].unit = new wchar_t[1024];
               g_Parameter._currentMenu->pads[i].items[j].name = new wchar_t[1024];
               g_Parameter._currentMenu->pads[i].items[j].type = new wchar_t[1024];

               if (_currentMenu->pads[i].items[j].unit != nullptr) {
                  wcscpy(g_Parameter._currentMenu->pads[i].items[j].unit, _currentMenu->pads[i].items[j].unit);
               }
               wcscpy(g_Parameter._currentMenu->pads[i].items[j].name, _currentMenu->pads[i].items[j].name);
               wcscpy(g_Parameter._currentMenu->pads[i].items[j].type, _currentMenu->pads[i].items[j].type);

               for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].capacity; k++) {
                  if (k < g_Parameter._currentMenu->pads[i].items[j].length) {
                     g_Parameter._currentMenu->pads[i].items[j].units[k] = new wchar_t[1024];
                     wcscpy(g_Parameter._currentMenu->pads[i].items[j].units[k], _currentMenu->pads[i].items[j].units[k]);
                  }
               }
               g_Parameter._currentMenu->pads[i].items[j].IsEnabled = _currentMenu->pads[i].items[j].IsEnabled;
               g_Parameter._currentMenu->pads[i].items[j].IsVisible = _currentMenu->pads[i].items[j].IsVisible;
            }
            if (j < g_Parameter._currentMenu->screenPads[i].length)
            {
               g_Parameter._currentMenu->screenPads[i].items[j].unit = new wchar_t[1024];
               g_Parameter._currentMenu->screenPads[i].items[j].name = new wchar_t[1024];
               g_Parameter._currentMenu->screenPads[i].items[j].type = new wchar_t[1024];

               if (_currentMenu->screenPads[i].items[j].unit != nullptr) {
                  wcscpy(g_Parameter._currentMenu->screenPads[i].items[j].unit, _currentMenu->screenPads[i].items[j].unit);
               }
               wcscpy(g_Parameter._currentMenu->screenPads[i].items[j].name, _currentMenu->screenPads[i].items[j].name);
               wcscpy(g_Parameter._currentMenu->screenPads[i].items[j].type, _currentMenu->screenPads[i].items[j].type);

               for (int k = 0; k < g_Parameter._currentMenu->screenPads[i].items[j].capacity; k++) {
                  if (k < g_Parameter._currentMenu->screenPads[i].items[j].length) {
                     g_Parameter._currentMenu->screenPads[i].items[j].units[k] = new wchar_t[1024];
                     wcscpy(g_Parameter._currentMenu->screenPads[i].items[j].units[k], _currentMenu->screenPads[i].items[j].units[k]);
                  }
               }
               g_Parameter._currentMenu->screenPads[i].items[j].IsEnabled = _currentMenu->screenPads[i].items[j].IsEnabled;
               g_Parameter._currentMenu->screenPads[i].items[j].IsVisible = _currentMenu->screenPads[i].items[j].IsVisible;
            }
            for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].guilist.capacity; k++) {
               if (k < g_Parameter._currentMenu->pads[i].items[j].guilist.length) {
                  g_Parameter._currentMenu->pads[i].items[j].guilist.names[k] = new wchar_t[1024];
                  wcscpy(g_Parameter._currentMenu->pads[i].items[j].guilist.names[k], _currentMenu->pads[i].items[j].guilist.names[k]);
               }
            }
            for (int k = 0; k < g_Parameter._currentMenu->screenPads[i].items[j].guilist.capacity; k++) {
               if (k < g_Parameter._currentMenu->screenPads[i].items[j].guilist.length) {
                  g_Parameter._currentMenu->screenPads[i].items[j].guilist.names[k] = new wchar_t[1024];
                  wcscpy(g_Parameter._currentMenu->screenPads[i].items[j].guilist.names[k], _currentMenu->screenPads[i].items[j].guilist.names[k]);
               }
            }
         }
      }

      g_Parameter._currentMenu->indexMode = _currentMenu->indexMode;
      g_Parameter._currentMenu->indexMeas = _currentMenu->indexMeas;
      g_Parameter._currentMenu->indexView = _currentMenu->indexView;

      if (menuInit) {
         mainWindow->putCurrentMenu(g_Parameter._currentMenu);
         //mainWindow->init3();
      }

      menuInit = true;

      return 0;
   }

   //--------------------------------------------------------------------------------------------------// 
   DLL_TYPE setRestyle(int _index, GraphPanelStyle _style)
   {
      if (styleInit == true)
      {
         delete[] g_Parameter._currentStyle.XAxisName;
         delete[] g_Parameter._currentStyle.YAxisName;
         delete[] g_Parameter._currentStyle.XAxisUnit;
         delete[] g_Parameter._currentStyle.YAxisUnit;
      }

      g_Parameter._currentStyle = _style;

      g_Parameter._currentStyle.XAxisName = new wchar_t[1024];
      g_Parameter._currentStyle.YAxisName = new wchar_t[1024];
      g_Parameter._currentStyle.XAxisUnit = new wchar_t[1024];
      g_Parameter._currentStyle.YAxisUnit = new wchar_t[1024];

      wcscpy(g_Parameter._currentStyle.XAxisName, _style.XAxisName);
      wcscpy(g_Parameter._currentStyle.YAxisName, _style.YAxisName);
      wcscpy(g_Parameter._currentStyle.XAxisUnit, _style.XAxisUnit);
      wcscpy(g_Parameter._currentStyle.YAxisUnit, _style.YAxisUnit);

      if (mainWindow)
         if (mainWindow->_mainScreen)
            mainWindow->_mainScreen->setRestyle(_index, _style);

      styleInit = true;

      return 0;
   }

   ////--------------------------------------------------------------------------------------------------//
   //DLL_TYPE putCurrentMenu(gsa::t::CurrentMenu *_currentMenu)
   //{
   //   if (menuInit == false) {
   //      g_Parameter._currentMenu = new gsa::t::CurrentMenu;
   //      for (int i = 0; i < _currentMenu->capacity; i++) {
   //         g_Parameter._currentMenu->pads[i].name = new wchar_t[1024];
   //         g_Parameter._currentMenu->pads[i].tab = new wchar_t[1024];
   //         for (int j = 0; j < _currentMenu->pads[i].capacity; j++) {
   //            g_Parameter._currentMenu->pads[i].items[j].unit = new wchar_t[1024];
   //            for (int k = 0; k < _currentMenu->pads[i].items[j].capacity; k++) {
   //               g_Parameter._currentMenu->pads[i].items[j].units[k] = new wchar_t[1024];
   //            }
   //            g_Parameter._currentMenu->pads[i].items[j].name = new wchar_t[1024];
   //            g_Parameter._currentMenu->pads[i].items[j].type = new wchar_t[1024];
   //            for (int k = 0; k < _currentMenu->pads[i].items[j].guilist.capacity; k++) {
   //               g_Parameter._currentMenu->pads[i].items[j].guilist.names[k] = new wchar_t[1024];
   //            }
   //         }
   //      }
   //      menuInit = true;
   //   }

   //   memcpy(g_Parameter._currentMenu, _currentMenu, sizeof(gsa::t::CurrentMenu));
   //   for (int i = 0; i < _currentMenu->capacity; i++) {
   //      if (i < _currentMenu->length) {
   //         memcpy(g_Parameter._currentMenu->pads[i].name, _currentMenu->pads[i].name, sizeof(wchar_t) * 1024);
   //         memcpy(g_Parameter._currentMenu->pads[i].tab, _currentMenu->pads[i].tab, sizeof(wchar_t) * 1024);
   //      }
   //      for (int j = 0; j < _currentMenu->pads[i].capacity; j++) {
   //         for (int k = 0; k < _currentMenu->pads[i].items[j].capacity; k++) {
   //            if (k < _currentMenu->pads[i].items[j].length) {
   //               memcpy(g_Parameter._currentMenu->pads[i].items[j].units[k], _currentMenu->pads[i].items[j].units[k], sizeof(wchar_t) * 1024);
   //            }
   //         }
   //         if (j < _currentMenu->pads[i].length) {
   //            memcpy(g_Parameter._currentMenu->pads[i].items[j].unit, _currentMenu->pads[i].items[j].unit, sizeof(wchar_t) * 1024);
   //            memcpy(g_Parameter._currentMenu->pads[i].items[j].name, _currentMenu->pads[i].items[j].name, sizeof(wchar_t) * 1024);
   //            memcpy(g_Parameter._currentMenu->pads[i].items[j].type, _currentMenu->pads[i].items[j].type, sizeof(wchar_t) * 1024);
   //         }
   //         for (int k = 0; k < _currentMenu->pads[i].items[j].guilist.capacity; k++) {
   //            if (k < _currentMenu->pads[i].items[j].guilist.length) {
   //               memcpy(g_Parameter._currentMenu->pads[i].items[j].guilist.names[k], _currentMenu->pads[i].items[j].guilist.names[k], sizeof(wchar_t) * 1024);
   //            }
   //         }
   //      }
   //   }

   //   return 0;
   //}

   DLL_TYPE putResize(LPVOID _Resize)
   {
     //__van__ 2019.08.08 
     //if (ResizeCallback != nullptr)
     ResizeCallback = static_cast<VoidStringIntDelegate *>(_Resize);
     return 0;
   }

   DLL_TYPE putRerangeX(VoidStringRangeDelegate _ResizeXDelegate)
   {
     //__van__ 2019.08.08 
     //if (RerangeXCallback != nullptr)
     RerangeXCallback = _ResizeXDelegate;
     return 0;
   }
   DLL_TYPE putRerangeY(VoidStringRangeDelegate _ResizeYDelegate)
   {
     //__van__ 2019.08.08 
     //if (RerangeYCallback != nullptr)
     RerangeYCallback = _ResizeYDelegate;
     return 0;
   }

   DLL_TYPE setXRange(wchar_t* _Panel, GraphPanelRange _Range)
   {
      //QString str(QString("INFO007 %1[%2]%3 / min=%4 max=%5 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg(_Range.Min).arg(_Range.Max));
      //qInfo(str.toStdString().c_str());
      //mainWindow->_mainScreen->on_rangeChangedX(_Range.Min, _Range.Max);
      mainWindow->_mainScreen->vrangeChangedXEmit(_Range.Min, _Range.Max, true);
      return 0;
   }

   DLL_TYPE setYRange(wchar_t* _Panel, GraphPanelRange _Range)
   {
      //QString str(QString("INFO007 %1[%2]%3 / min=%4 max=%5 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg(_Range.Min).arg(_Range.Max));
      //qInfo(str.toStdString().c_str());
      //mainWindow->_mainScreen->on_rangeChangedY(_Range.Min, _Range.Max);
      mainWindow->_mainScreen->vrangeChangedYEmit(_Range.Min, _Range.Max, true);
      return 0;
   }

   DLL_TYPE messageBox(wchar_t* _caption, wchar_t* _text)
   {
      mainWindow->_mainScreen->messageBox(_caption, _text);
      return 0;
   }

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE run(wchar_t *str, LPVOID _Delegate, LPVOID _SetValue, LPVOID _WheelRotate, LPVOID _CallActivator, LPVOID _Exit, LPVOID _GSetFocus)
   {
      wchar_t unit[128] = L"sdfsdsf";
      QString strUnit(QString::fromWCharArray(unit));

      //setlocale(LC_ALL, "rus");
      //setlocale(LC_ALL, "Russian");
      QString qstr;

      if (_Delegate == nullptr) {
         //int argc(0);
         //char *argv[16];
         //p_App = new QApplication(argc, argv);

         MessageBox(NULL, str, L"Error !!!", MB_OK);

         //delete p_App;
      }
      else {
         g_Parameter._Deleagate = (MBResultDelegate *)_Delegate;
         g_Parameter._SetValue = (SetValue *)_SetValue;
         g_Parameter._WheelRotate = (WheelRotate *)_WheelRotate;
         g_Parameter._CallActivator = (CallActivator *)_CallActivator;
         g_Parameter._Exit = (ExitDelegate *)_Exit;
         g_Parameter._GSetFocus = (GSetFocus *)_GSetFocus;
         /*
         g_Parameter._Deleagate = static_cast<MBResultDelegate *>(_Delegate);
         g_Parameter._SetValue = static_cast<SetValue *>(_SetValue);
         g_Parameter._WheelRotate = static_cast<WheelRotate *>(_WheelRotate);
         g_Parameter._CallActivator = static_cast<CallActivator *>(_CallActivator);
         g_Parameter._Exit = static_cast<ExitDelegate *>(_Exit);
         */
         g_Parameter._Message = str;

         //std::wstringstream ss;
         //ss << L"//////// _currentMenu->length == " << g_Parameter._currentMenu->length << "  capacity == " << g_Parameter._currentMenu->capacity;
         //MessageBox(NULL, ss.str().c_str(), L"Error", MB_OK);

         auto start = std::chrono::high_resolution_clock::now();

         mainThread = CreateThread(NULL, 0, ThreadProc, static_cast<LPVOID>(&g_Parameter), 0, NULL);
         //std::thread guiThread(ThreadProc);
         //auto handle = std::async(std::launch::async, ThreadProc, static_cast<LPVOID>(&g_Parameter) );
         //unsigned long result = handle.get();
         //handle.wait();
         auto dur = std::chrono::high_resolution_clock::now() - start;

         std::cout << "Simple: " << std::chrono::duration_cast<std::chrono::microseconds>(dur).count() << std::endl;

         //int l_Result;
         //l_Result = g_Parameter._Deleagate(l_Result);
      }
      return 0;
   }

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE stop(void)
   {
      //if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      //WaitForSingleObject(mainThread, INFINITE);
      //mainWindow->stop();

      if (modeMeasViewInit == true) {
         for (int i = 0; i < g_Parameter._modeMeasView->capacity; i++) {
            for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) {
               for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
                  delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name;
               }
               delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name;
            }
            delete[] g_Parameter._modeMeasView->guiModes[i].name;
         }
         delete[] g_Parameter._modeMeasView->name;
         //delete g_Parameter._modeMeasView;
         //g_Parameter._modeMeasView.reset(nullptr);
      }

      //if (panelInit == true) {
      //   delete g_Parameter._tablePanelData;
      //}

      if (panelInit == true) {
         //for (int i = 0; i < g_Parameter._modeMeasView->capacity; i++) {
         //   for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) {
         //      for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
         //         delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name;
         //      }
         //      delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name;
         //   }
         //   delete[] g_Parameter._modeMeasView->guiModes[i].name;
         //}
         //delete[] g_Parameter._modeMeasView->name;
         delete g_Parameter._tablePanelData;
      }

      if (menuInit == true) {
         for (int i = 0; i < g_Parameter._currentMenu->capacity; i++) {
            for (int j = 0; j < g_Parameter._currentMenu->pads[i].capacity; j++) {
               if (j < g_Parameter._currentMenu->pads[i].length)
               {
                  for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].guilist.capacity; k++) {
                     if (k < g_Parameter._currentMenu->pads[i].items[j].guilist.length)
                        delete[] g_Parameter._currentMenu->pads[i].items[j].guilist.names[k];
                  }
                  for (int k = 0; k < g_Parameter._currentMenu->pads[i].items[j].capacity; k++) {
                     if (k < g_Parameter._currentMenu->pads[i].items[j].length)
                        delete[] g_Parameter._currentMenu->pads[i].items[j].units[k];
                  }
                  delete[] g_Parameter._currentMenu->pads[i].items[j].name;
                  delete[] g_Parameter._currentMenu->pads[i].items[j].type;
                  delete[] g_Parameter._currentMenu->pads[i].items[j].unit;
               }
               if (j < g_Parameter._currentMenu->screenPads[i].length)
               {
                  for (int k = 0; k < g_Parameter._currentMenu->screenPads[i].items[j].guilist.capacity; k++) {
                     if (k < g_Parameter._currentMenu->screenPads[i].items[j].guilist.length)
                        delete[] g_Parameter._currentMenu->screenPads[i].items[j].guilist.names[k];
                  }
                  for (int k = 0; k < g_Parameter._currentMenu->screenPads[i].items[j].capacity; k++) {
                     if (k < g_Parameter._currentMenu->screenPads[i].items[j].length)
                        delete[] g_Parameter._currentMenu->screenPads[i].items[j].units[k];
                  }
                  delete[] g_Parameter._currentMenu->screenPads[i].items[j].name;
                  delete[] g_Parameter._currentMenu->screenPads[i].items[j].type;
                  delete[] g_Parameter._currentMenu->screenPads[i].items[j].unit;
               }
            }
            if (i < g_Parameter._currentMenu->length)
            {
               delete[] g_Parameter._currentMenu->pads[i].name;
               delete[] g_Parameter._currentMenu->pads[i].tab;
            }
            if (i < g_Parameter._currentMenu->lengthScreen)
            {
               delete[] g_Parameter._currentMenu->screenPads[i].name;
               delete[] g_Parameter._currentMenu->screenPads[i].tab;
            }
         }
         delete[] g_Parameter._currentMenu->nameMode;
         delete[] g_Parameter._currentMenu->nameMeas;
         delete[] g_Parameter._currentMenu->nameView;

         delete g_Parameter._currentMenu;
      }

      return 0;
   }

   ////--------------------------------------------------------------------------------------------------//
   //DLL_TYPE putArray(void* data)
   //{
   //   mainWindow->putArray(data);

   //   return 0;
   //}

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE putCurrentIndexes(long PreviousPosition, long CurrentPosition)
   {
      //mainWindow->putCurrentIndexes(PreviousPosition, CurrentPosition);

      return 0;
   }

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE putDataLayer(double *_XData, double *_YData)
   {
      //mainWindow->putCurrentIndexes(PreviousPosition, CurrentPosition);
      //if (mainWindow != nullptr)
      //   mainWindow->putData(_XData, _YData);

      return 0;
   }

   DLL_TYPE putCarriage(gsa::t::CurrentData *_currentData, int index)
   {
      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      //mainWindow->putCurrentIndexes(PreviousPosition, CurrentPosition);
      if (mainWindow != nullptr)
         mainWindow->putCarriage(_currentData, index);

      int l = 0;

      return 0;
   }

   DLL_TYPE putCurrentData(gsa::t::CurrentData *_currentData, int index, int length)
   {
      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      //mainWindow->putCurrentIndexes(PreviousPosition, CurrentPosition);
      if (mainWindow != nullptr)
         mainWindow->putCurrentData(_currentData, index, length);

      int l = 0;

      return 0;
   }

   DLL_TYPE putTableData(gsa::t::TablePanelData *tablePanelData, int index, int length)
   {
      //return 0;

      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      if (panelInit == true) {
         for (int i = 0; i < g_Parameter._tablePanelData->Length; i++) {
            //for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) {
            //   for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
            //      for (int l = 0; l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].capacity; l++) {
            //         delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name;
            //      }
            //      delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name;
            //   }
            //   delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name;
            //}
            delete[] g_Parameter._tablePanelData->Values[i].Value;
         }
         //delete[] g_Parameter._tablePanelData->name;
         delete g_Parameter._tablePanelData;
      }

      g_Parameter._tablePanelData = new gsa::t::TablePanelData;
      memcpy(g_Parameter._tablePanelData, tablePanelData, sizeof(gsa::t::TablePanelData));

      if (g_Parameter._tablePanelData->Length != length) g_Parameter._tablePanelData->Length = length;

      if (g_Parameter._tablePanelData->Length > 2) {
         int i = 0;
      }

      for (int i = 0; i < g_Parameter._tablePanelData->Length; i++)
      {
         g_Parameter._tablePanelData->Values[i].Value = new wchar_t[1024];
         wcscpy(g_Parameter._tablePanelData->Values[i].Value, tablePanelData->Values[i].Value);

         g_Parameter._tablePanelData->Values[i].TableID = tablePanelData->Values[i].TableID;
         g_Parameter._tablePanelData->Values[i].CellID = tablePanelData->Values[i].CellID;
         g_Parameter._tablePanelData->Values[i].Background = tablePanelData->Values[i].Background;
         g_Parameter._tablePanelData->Values[i].Foreground = tablePanelData->Values[i].Foreground;
      }

      panelInit = true;

      if (mainWindow != nullptr) {
         //putTablePanelData(tablePanelData);
         //mainWindow->putTableData(tablePanelData, index, length);
         mainWindow->putTableData(g_Parameter._tablePanelData, index, length);
      }

      return 0;
   }

   DLL_TYPE putTablePanel(gsa::t::Table *tablePanel, int index)
   {
      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      if (index == 1 && mainWindow != nullptr)
      {
         if (tablePanelInit == true) {
            //for (int i = 0; i < g_Parameter._tablePanelData->Length; i++) {
            for (int i = 0; i < gsa::t::maxCell; i++) {
               delete[] g_Parameter._tablePanel->Cells[i].Default.Value;
               g_Parameter._tablePanel->Cells[i].Default.Value = nullptr;
            }
            delete g_Parameter._tablePanel;
         }

         g_Parameter._tablePanel = new gsa::t::Table;

         memcpy(g_Parameter._tablePanel, tablePanel, sizeof(gsa::t::Table)); //gsa::t::maxCell
         //for (int i = 0; i < g_Parameter._tablePanelData->Length; i++)
         for (int i = 0; i < gsa::t::maxCell; i++)
         {
            if (tablePanel->Cells[i].Default.Value != nullptr) {
               g_Parameter._tablePanel->Cells[i].Default.Value = new wchar_t[1024];
               wcscpy(g_Parameter._tablePanel->Cells[i].Default.Value, tablePanel->Cells[i].Default.Value);
            }
            else {
               int iii = 0;
            }
            g_Parameter._tablePanel->Cells[i].Default.Background = tablePanel->Cells[i].Default.Background;
            g_Parameter._tablePanel->Cells[i].Default.Foreground = tablePanel->Cells[i].Default.Foreground;

            g_Parameter._tablePanel->Cells[i].Row = tablePanel->Cells[i].Row;
            g_Parameter._tablePanel->Cells[i].Column = tablePanel->Cells[i].Column;
            g_Parameter._tablePanel->Cells[i].RowSpan = tablePanel->Cells[i].RowSpan;
            g_Parameter._tablePanel->Cells[i].ColumnSpan = tablePanel->Cells[i].ColumnSpan;
         }

         tablePanelInit = true;

         mainWindow->putTablePanel(g_Parameter._tablePanel, index);
      }
      else {
         if(g_Parameter._tablePanel != nullptr)
            mainWindow->putTablePanel(g_Parameter._tablePanel, index);
         int i = 0;
      }

      return 0;
   }

   //--------------------------------------------------------------------------------------------------//
   DLL_TYPE putTablePanelData(gsa::t::TablePanelData *_tablePanelData)
   {
      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      //QString str(QString("INFO007 <<<>>> %1 ").arg(__FUNCTION__));
      //qInfo(str.toStdString().c_str());

      if (panelInit == true) {
         for (int i = 0; i < g_Parameter._tablePanelData->Length; i++) {
            //for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) {
            //   for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
            //      for (int l = 0; l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].capacity; l++) {
            //         delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name;
            //      }
            //      delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name;
            //   }
            //   delete[] g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name;
            //}
            delete[] g_Parameter._tablePanelData->Values[i].Value;
         }
         //delete[] g_Parameter._tablePanelData->name;
         delete g_Parameter._tablePanelData;
      }

      g_Parameter._tablePanelData = new gsa::t::TablePanelData;
      memcpy(g_Parameter._tablePanelData, _tablePanelData, sizeof(gsa::t::TablePanelData));
      if (g_Parameter._tablePanelData->Length > 2) {
         int i = 0;
      }
      for (int i = 0; i < g_Parameter._tablePanelData->Length; i++)
      {
         g_Parameter._tablePanelData->Values[i].Value = new wchar_t[1024];
         wcscpy(g_Parameter._tablePanelData->Values[i].Value, _tablePanelData->Values[i].Value);

         g_Parameter._tablePanelData->Values[i].TableID = _tablePanelData->Values[i].TableID;
         g_Parameter._tablePanelData->Values[i].CellID = _tablePanelData->Values[i].CellID;
         g_Parameter._tablePanelData->Values[i].Background = _tablePanelData->Values[i].Background;
         g_Parameter._tablePanelData->Values[i].Foreground = _tablePanelData->Values[i].Foreground;

         //for (int j = 0; j < g_Parameter._modeMeasView->guiModes[i].capacity; j++) 
         //{
         //   if (j < g_Parameter._modeMeasView->guiModes[i].length)
         //   {
         //      g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name = new wchar_t[1024];
         //      if (_modeMeasView->guiModes[i].guiMeases[j].name != nullptr) {
         //         wcscpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name, _modeMeasView->guiModes[i].guiMeases[j].name);
         //      }
         //      else {
         //         memcpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].name, "", sizeof(wchar_t) * 1024);
         //      }
         //   }
         //   for (int k = 0; k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].capacity; k++) {
         //      //g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name = new wchar_t[1024];
         //      if (k < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].length)
         //      {
         //         g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name = new wchar_t[1024];
         //         if (_modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name != nullptr) {
         //            wcscpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name, _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name);
         //         }
         //         else {
         //            memcpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].name, "", sizeof(wchar_t) * 1024);
         //         }
         //      }

         //      for (int l = 0; l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].capacity; l++) {
         //         //g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name = new wchar_t[1024];
         //         if (l < g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].length)
         //         {
         //            g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name = new wchar_t[1024];
         //            if (_modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name != nullptr) {
         //               wcscpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name, _modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name);
         //            }
         //            else {
         //               memcpy(g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name, "", sizeof(wchar_t) * 1024);
         //            }
         //         }
         //      }
         //   }
         //}
      }

      panelInit = true;

      return 0;
   }

   DLL_TYPE uiPropertyChanged(int item, int type, int value)
   {
      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      if (mainWindow != nullptr)
         mainWindow->uiPropertyChangedEmit(item, type, value);

      return 0;
   }

   DLL_TYPE changeData(int item, double value, wchar_t* unit)
   {
      if (mainWindow == nullptr || mainWindow->isStop()) return 1;

      //mainWindow->putCurrentIndexes(PreviousPosition, CurrentPosition);
      if (mainWindow != nullptr)
         mainWindow->changeDataEmit(item, value, unit);

      int l = 0;

      return 0;
   }
}

