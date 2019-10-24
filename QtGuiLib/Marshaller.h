#pragma once

#include "gcore/core.h"

#ifndef _MARSHALLER_TYPES
#define _MARSHALLER_TYPES

#define	DLL_TYPE __declspec(dllexport) int
#define	DLL_VOID __declspec(dllexport) void

/*----------------------------Strutures----------------------------*/
struct GraphPanelRange
{
	double Min, Max;
};

struct ColourStruct
{
   unsigned char Red, Green, Blue;
};

enum AxisStyle
{ 
   Linear, 
   Log 
};

enum XAxisUnit
{
   unit_x1,
   unit_x2
};

enum YAxisUnit
{
   unit_y1,
   unit_y2
};

struct GraphPanelStyle
{
   //XAxisUnit _xaxisUnit;
   //YAxisUnit _yaxisUnit;
   wchar_t *XAxisName;
   wchar_t *YAxisName;
   wchar_t *XAxisUnit;
   wchar_t *YAxisUnit;

   AxisStyle _xscaling;
   AxisStyle _yscaling;
   ColourStruct _axisColour;
};

/*----------------------------D-Types----------------------------*/
typedef int WINAPI MBResultDelegate(int);
typedef int WINAPI SetValue(int, double, wchar_t values[], int);
typedef int WINAPI GSetFocus(int, int);
typedef int WINAPI WheelRotate(int, int);
typedef void WINAPI CallActivator(int, int, int);
typedef void WINAPI ExitDelegate(void);
typedef void WINAPI VoidDelegate(void);
typedef void WINAPI VoidStringIntDelegate(wchar_t *_Param1, int _Param2);
typedef void WINAPI VoidStringRangeDelegate(wchar_t *_Param1, GraphPanelRange _Param2);

/*----------------------------Delegates----------------------------*/
extern VoidDelegate *VSyncCallback;
extern VoidStringIntDelegate *ResizeCallback;
extern VoidStringRangeDelegate *RerangeXCallback, *RerangeYCallback;

/*----------------------------Definitions----------------------------*/
extern	"C" DLL_TYPE putDevices(int uiType, int devType);
extern	"C" DLL_TYPE putVSync(LPVOID _VSync);
extern	"C" DLL_TYPE putResize(LPVOID _Resize);
extern	"C" DLL_TYPE putRerangeX(VoidStringRangeDelegate _ResizeXDelegate);
extern	"C" DLL_TYPE putRerangeY(VoidStringRangeDelegate _ResizeYDelegate);
extern	"C" DLL_TYPE setXRange(wchar_t* _Panel, GraphPanelRange _Range);
extern	"C" DLL_TYPE setYRange(wchar_t* _Panel, GraphPanelRange _Range);
extern	"C" DLL_TYPE setRestyle(int index, GraphPanelStyle _Style);
extern	"C" DLL_TYPE messageBox(wchar_t* caption, wchar_t* text);
extern	"C" DLL_TYPE run(wchar_t *str, LPVOID _Delegate, LPVOID _SetValue, LPVOID _WheelRotate, LPVOID _CallActivator, LPVOID _Exit, LPVOID _GSetFocus);
extern	"C" DLL_TYPE stop(void);
extern	"C" DLL_TYPE putCurrentIndexes(long PreviousPosition, long CurrentPosition);
extern	"C" DLL_TYPE putDataLayer(double *XData_, double *YData_);
extern	"C" DLL_TYPE putCurrentMenu(gsa::t::CurrentMenu *currentMenu_);
extern	"C" DLL_TYPE putCurrentData(gsa::t::CurrentData *currentData_, int index, int length);
extern	"C" DLL_TYPE putTableData(gsa::t::TablePanelData *tablePanelData, int index, int length);
extern	"C" DLL_TYPE putTablePanel(gsa::t::Table *tablePanel, int index);

#endif
