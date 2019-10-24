// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define WIN32_LEAN_AND_MEAN

//#include <QtWidgets\QApplication>
//#include <QtWidgets\QMainWindow>
//#include <QtWidgets\QTableWidgetItem>
//#include <QtWidgets\QDesktopWidget>
//#include <QtCore\QTimer>
//#include <QtCore\QTime>
//#include <QtGui\QScreen>
//#include <QtGui\QKeyEvent>

//#define NOMINMAX
#undef min
#undef max

#include <QtCharts\QChart>
#include <QtCharts\QChartView>
#include <QtCharts\QLineSeries>
#include <QtCharts\QCategoryAxis>
#include <QtCharts\QChartGlobal>
#include <QtCharts\QValueAxis>

#include <QtCore\QTimer>
#include <QtCore\QTime>
#include <QtCore\QDir>
//#include <QtCore\QLogger>
#include <QtCore\QLogging.h>

#include <QtGui\QScreen>
#include <QtGui\QKeyEvent>
#include <QtGui\QShowEvent>
#include <QtGui\QSurfaceFormat>

#include <QtMultimedia\QAudioDeviceInfo>
#include <QtMultimedia\QAudioInput>

#include <QtWidgets\QApplication>
#include <QtWidgets\QMainWindow>
#include <QtWidgets\QTableWidgetItem>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QGroupBox>
#include <QtWidgets\QLineEdit>
#include <QtWidgets\QTextEdit>
#include <QtWidgets\QOpenGLWidget>
#include <QtWidgets\QRadioButton>
#include <QtWidgets\QShortcut>
#include <QtWidgets\QSplitter>
#include <QtWidgets\QSizePolicy>

#include <QRect>

#ifdef Q_OS_WIN
#include <QtPlatformHeaders\QWindowsWindowFunctions>
#endif
//#include <boost/regex.hpp>
//#include <boost/asio.hpp>

#include "ui_mainwindow.h"

//#include "../gmain/mainmenu2.h"
//#include "../gmain/mainmenu3.h"
//#include "../gkeypad/keypad.h"
//#include "../gkeypad/keypadanalog.h"
//#include "../gmenu/menutop.h"
//#include "../gmenu/menubottom.h"
#include "gcore/core.h"
#include "gmenu/menufreq.h"
#include "gmenu/gmenupage.h"
#include "gscreen/gmainscreen.h"

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;
class QAudioInput;
class MainScreen;
class MenuItem;

//namespace Core {
//class Controller;
//} // namespace Core

//namespace Ui {
//class MainWindow;
//}

namespace Main {

class KeyPressEater;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

   //void addItem(QWidget *page_1, QVBoxLayout *verticalLayout_2, QString type, QString name);
   //void addItems(QWidget *page_1, QVBoxLayout *verticalLayout_2, QString type, QStringList names, int index);

   //void resizeEvent(QResizeEvent* event);

   //enum class ViewConfiguration { Solo, DVertical, DHorizontal, TLeftVertical, TRightVertical, TTopHorizontal, TBottomHorizontal, Quadro };
   //enum class PanelPosition { Solo, Left, Right, Top, Bottom, LeftTop, LeftBottom, RightTop, RightBottom, Disabled };

   void initScreenWidget(const gsa::t::ViewConfiguration &viewConfiguration, const gsa::t::GuiPanel guiPanels[], const int &length);
   void freeScreenWidget(const gsa::t::ViewConfiguration &viewConfiguration);
   void setGsaIcon(QPushButton *, const QString &path);
   void setModeName(QString text);
   int findIndex(const gsa::t::GuiPanel guiPanels[], int position);
   void addPanelWidget(const gsa::t::GuiPanel guiPanels[], int index, QSplitter *splitterTemp);
   //void clearCurrentTab(void);
   void setCurrentTab(const gsa::t::ViewConfiguration &viewConfiguration, const gsa::t::GuiPanel guiPanels[], const int &length, bool add = true);
   void FillIndexes(void);

   //void init(void);
   //void free(void);
   //void init2(void);
   //void free2(void);
   void init3(void);
   void free3(void);

   void PipeClient(void);

   void stop(void);
   //void putArray(void* data);
   //void putData(double *_XData, double *_YData);
   //void putDataStr(gsa::t::GraphPanelData *_Data);
   void putCurrentIndexes(int PreviousPosition, int CurrentPosition);
   void putCurrentMenu(gsa::t::CurrentMenu *_currentMenu);
   void putCurrentData(gsa::t::CurrentData *_currentData, int index, int length);
   void putTableData(gsa::t::TablePanelData *tablePanelData, int index, int length);
   void putTablePanel(gsa::t::Table *tablePanel, int index);
   void putCarriage(gsa::t::CurrentData *_Data, int index);
   void GetRgb(const std::wstring &color, int &r, int &g, int &b);
   void GetValue(const std::wstring &param, double &value);
   void putTheme(gsa::t::Theme *_theme);
   //void changeData(int item, double value, wchar_t* unit);
   void changeDataEmit(int item, double value, wchar_t* unit);
   void uiPropertyChangedEmit(int item, int type, int value);

   bool showModeMeasView(void);

   void wheelEvent(QWheelEvent * event);

   void keyPadPress(const int &keyCode, quint32 nativeModifiers, const int &key);

   void currentDown(bool bWheel = false);
   void currentUp(bool bWheel = false);
   void StopThreads(void);
   bool isStop(void) { return _stop; }

   MenuItem* getItemRbw(void);
   MenuItem* getItemByName(const QString &name);

   std::map<std::wstring, gsa::t::FontIndex> &fontindexes() { return _fontindexes; }
   std::map<std::wstring, gsa::t::ColorIndex> &colorindexes() { return _colorindexes; }
   std::map<std::wstring, gsa::t::SizeIndex> &sizeindexes() { return _sizeindexes; }
   std::map<std::wstring, gsa::t::IndentIndex> &indentindexes() { return _indentindexes; }

public slots:
   void changeData(int item, double value, wchar_t* unit);
   void uiPropertyChanged(int item, int type, int value);
   void serverConnected(void);
   void serverDisconnected(void);

   void slotIndexChanged(int index);
   void keyPadPressed(int keyCode, quint32 nativeModifiers, int key);
   void keyProcess(gsa::t::ItemInfo &itemInfo);
   bool keyCheck(int keyCode, quint32 nativeModifiers, int key);

   void slotPutTablePanel(int index);
   void slotPutTableDat(int index, int length);
   void slotPutCurrentMenu(void);

//public slots:
   void clickedPlusButton(void);
   void clickedModeMeasView(void);
   void clickedSystemParams(void);
   void tabSelected(int);
   void clickExit(void);
   void resizeEvent ( QResizeEvent * event );
   void moveEvent(QMoveEvent * event);
   void closeEvent( QCloseEvent *event );
   void show(void);
   void showMaximized(void);
   void showFullScreen(void);
   void showNormal(void);
   //void processTimer(void);
   //void Updated(void);
   //void SkUpdated(void);
   //void PeriodUpdated(void);

   void buttonESC();

   //void MySlot(wchar_t* _caption, wchar_t* _text);
   void slotMessageBox(wchar_t* _caption, wchar_t* _text);
   void slotSetMarker(int index, QString text, QColor color);

signals:
   void signalKeyPadPress(int keyCode, quint32 nativeModifiers, int key);
   void signalChangeData(int item, double value, wchar_t* unit);
   void signalUiPropertyChanged(int item, int type, int value);
   void signalPutCurrentMenu(void);
   void signalPutTablePanel(int index);
   void signalPutTableDat(int index, int length);

//signals:
   void buttonClicked();
   void dataChanged();
   void signalEditForm();
   void signalEditAntenn();
   void nameChange(QString name);

//signals:
   //void amptChanged(TG::AmptParam&);
   void freqChanged(TG::FreqParam&);
   void amptChanged(TG::AmptParam&);
   void bwChanged(TG::BwParam&);
   void sweepChanged(TG::SweepParam&);
   void inputChanged(TG::InputParam&);
   //void displayChanged(TG::DisplayParam&);
   void markerChanged(TG::MarkerParam&);
   void traceChanged(TG::TraceParam&);

   void menuChanged(TG::IndexMenu&);
   void menuItemEdit(QString);
   void menuSingleCont(void);
   void menuSingleRestart(void);
   void menuExit(void);

   void screenStateChanged(TG::ScreenStates);

protected:
   bool keypres(QKeyEvent *keyevent);
   //bool eventFilter(QObject *obj, QEvent *event);

public:
   int m_Period;
   Ui::MainWindow *ui;
   MainScreen *_mainScreen;
   gsa::t::CurrentMenu *_currentMenu;
   gsa::t::Table *_tablePanel;
   gsa::t::TablePanelData *_tablePanelData;

   struct TabParams
   {
      gsa::t::ViewConfiguration _type;
      gsa::t::GuiPanel *_guiPanels;
      int _length;
      int _currentMode;
      int _currentMeas;
      int _currentView;
      int _currentMenuPage;
      QWidget *widget;
   };

private:
   bool _draw;
   //QChart *_chart;
   VChart *_chart;
   QChartView *_chartView;
   bool _stop;
   QSplitter *_splitterScreenWidget;
   QSplitter *_splitterHorizontal;
   QSplitter *_splitterHorizontal2;
   QSplitter *_splitterVertical;
   QWidget *_table;
   QPushButton *_plusButton;
   QFrame *_frameSplitterScreenWidget;

   QLineSeries *m_series;
   //gsa::t::XYValue* m_values;
   //QLineSeries *m_series, *m_SkipedSeries, *m_PeriodSeries;
   //QVector <QPointF> *m_Vector, *m_SkipedVector, *m_PeriodVector;
   //bool m_bUpdated, m_bSkUpdated, m_bPeriodUpdated;
   //int m_Skiped, m_Position;
   //int m_Blinker;
   QShortcut *_keyMode;
   QShortcut *_keySystem;
   QShortcut *_keyExit;
   gsa::t::ViewConfiguration _type;
   TabParams _tabParams;
   std::map<int, TabParams> _tabs;
   int _currentMode;
   int _currentMeas;
   int _currentView;
   int _currentMenuPage;

   ////MainMenu2 *_mainMenu;
   //Menu::MainMenu3 *_mainMenu;
   //Menu::MenuTop *_menuTop;
   //Menu::MenuBottom *_menuBottom;
   Menu::MenuFreq* _menuFreq;
   int _length;
   MenuPage *_menuPages[gsa::t::maxPad];
   std::map<std::string, MenuPage *> _stringMenuPages;
   std::map<int, QLabel *> _labels;
   std::map<int, int> _visibles;
   std::map<std::wstring, gsa::t::FontIndex> _fontindexes;
   std::map<std::wstring, gsa::t::ColorIndex> _colorindexes;
   std::map<std::wstring, gsa::t::SizeIndex> _sizeindexes;
   std::map<std::wstring, gsa::t::IndentIndex> _indentindexes;
   int _labelHeight;

   ////QMessageBox *_msgBox;
   //Pad::KeyPad *_keypad;
   //Pad::KeyPadAnalog *_keypadanalog;
   //gsa::core::Controller *_controller;
   gsa::core::Controller *_controller;
   //int _currentPos;
   //int _number;
   //QByteArray _text;
   //float _time;

   //std::map<gsa::t::KeyInfo, int> _keys;
   std::map<gsa::t::KeyInfo, gsa::t::ItemInfo> _keys;

   KeyPressEater *m_keyPressEater;
   void keyPressed(QKeyEvent *_pEvent);

   XYSeriesIODevice *m_device;
   QAudioInput *m_audioInput;
   int realPageIndex;

   virtual bool nativeEvent(const QByteArray &_EventType, void *_Message, long *_Result);

   friend class KeKeyPressEater;

};

class KeyPressEater : public QObject
{
   Q_OBJECT

public:
   KeyPressEater(MainWindow *mainWindow, gsa::core::Controller *controller) { 
      _mainWindow = mainWindow; 
      _controller = controller; 
   } 

protected:
   bool eventFilter(QObject *obj, QEvent *event);

   MainWindow *_mainWindow;
   gsa::core::Controller *_controller;

};

} // namespace Main

#endif // MAINWINDOW_H

