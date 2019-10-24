#pragma once

//#define NOMINMAX
#undef min
#undef max

#include <QtCore\QCoreApplication>
#include <QtCore\QtGlobal>
#include <QtCore\QtDebug>

#include <QtGui>

#include <QtWidgets\QApplication>
#include <QtWidgets\QMainWindow>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QFormLayout>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QStackedWidget>
#include <QtWidgets\QTabWidget>
#include <QtWidgets\QTreeWidget>
#include <QtWidgets\QTableView>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QMessageBox>
#include <QtCharts\QChartView>
#include <QtCharts\QLineSeries>
#include <QtCharts\QCategoryAxis>

#include "gmain/mainwindow.h"
#include "Marshaller.h"

struct MBParameter
{
   MBResultDelegate *_Deleagate;
   SetValue *_SetValue;
   WheelRotate *_WheelRotate;
   CallActivator *_CallActivator;
   ExitDelegate *_Exit;
   GSetFocus *_GSetFocus;

   wchar_t *_Message;

   gsa::t::CurrentMenu *_currentMenu;
   //gsa::t::ModeMeasView *_modeMeasView;
   std::unique_ptr<gsa::t::ModeMeasView> _modeMeasView;
   gsa::t::TablePanelData *_tablePanelData;
   gsa::t::Table *_tablePanel;
   gsa::t::Theme *_theme;

   GraphPanelStyle _currentStyle;
};

extern MBParameter g_Parameter;

DWORD WINAPI ThreadProc(LPVOID _lpParameter);

enum class eventTypes
{
	eventStartApp,
	eventStopApp,
	eventFree
};

class GuiObject
{
public:
	GuiObject();
	~GuiObject();

	void putEvent(eventTypes);
	eventTypes event(void);

private:
	eventTypes _type;

};

//extern QApplication *p_App;

extern Main::MainWindow *mainWindow;

extern QWaitCondition bufferNotEmpty;
//QWaitCondition bufferNotFull;
extern QMutex mutex;

//__van__ 2019.08.08 
extern gsa::t::Theme _theme;
extern gsa::t::ThemeFont themeFont;
extern gsa::t::ThemeItem themeItem;
extern gsa::t::CurrentMenu _currentMenu;

