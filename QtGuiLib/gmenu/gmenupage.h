#pragma once

//#define NOMINMAX
#undef min
#undef max

#include <map>
#include <string>

#include <QtCharts\QChart>
#include <QtCharts\QChartView>
#include <QtCharts\QLineSeries>
#include <QtCharts\QCategoryAxis>
#include <QtCharts\QChartGlobal>
#include <QtCharts\QValueAxis>

#include <QtCore\QObject>
#include <QtCore\QTimer>
#include <QtCore\QTime>
#include <QtCore\QEvent>

#include <QtGui\QScreen>
#include <QtGui\QKeyEvent>
#include <QtGui\QShowEvent>
//#include <QtGui\QtColorPicker>

#include <QtMultimedia\QAudioDeviceInfo>
#include <QtMultimedia\QAudioInput>

#include <QtWidgets\QApplication>
#include <QtWidgets\QMainWindow>
#include <QtWidgets\QTableWidgetItem>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QGroupBox>
#include <QtWidgets\QLineEdit>
#include <QtWidgets\QLabel>
#include <QtWidgets\QTextEdit>
#include <QtWidgets\QOpenGLWidget>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QRadioButton>

#include <QtGui\QSurfaceFormat>

//#include <ctype.h>

#ifdef Q_OS_WIN
#include <QtPlatformHeaders\QWindowsWindowFunctions>
#endif
//#include <boost/regex.hpp>
//#include <boost/asio.hpp>

#include "gcore/core.h"
#include "gcore/controller.h"
#include "gmenu/menumeassetup.h"
#include "gmenu/gmenuitem.h"

//class MenuMeasSetup;
//class MenuItem;

namespace Main {

   class MainWindow;
   extern const int _numberTrace;

}

class MenuPage : public QWidget
{
   Q_OBJECT

public:
   MenuPage(QWidget *parent, const gsa::t::GuiPad &guiPad, bool multi, gsa::core::Controller *controller);
   MenuPage(QWidget *parent = nullptr);
   ~MenuPage();

public:
   void addPage(const gsa::t::GuiPad &guiPad);

   bool eventFilter(QObject* object, QEvent* event);

   void fillButtonNames(wchar_t *units[32], int length);
   int KeyPad(TG::KeyPadParam &keyPadParam, QString &unit, int &index);
   int itemIndex(void);

   void uiPropertyChanged(int item, int type, int value);
   void keyProcess(gsa::t::ItemInfo &itemInfo);
   void changeData(int item, double value, wchar_t* unit);
   //void addItemsOld(const gsa::t::GuiPad &guiPad, const int& pageIndex, std::map<gsa::t::KeyInfo, int> &keys);
   void addItems(const gsa::t::GuiPad &guiPad, const int& pageIndex, std::map<gsa::t::KeyInfo, gsa::t::ItemInfo> &keys);
   int implGroupBegin(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem);
   void implGroupEnd(void);
   void implAddItemNew(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem);
   //void Double2String(QString &str, double value);
   void setCustomizing(void);

   int setSelect(int index);
   bool setNext(void);
   bool setCurrentField(void);

   void addSpacer(void);
   //wchar_t *caption(void) { 
   //   if (_guiPad != nullptr) return _guiPad->name; 
   //   else return _text; 
   //}
   const wchar_t *caption(void) {
      return _caption.toStdWString().c_str();
   }
   void doWheelEvent(int delta);

   MenuItem* getItemRbw(void);
   MenuItem* getItemByName(const QString &name);

public slots:
   void slotButton(void);
   void slotColorSelector(void);
   void slotRadioButton(bool checked = false);
   void doReturnPressed(void);
   void indexChanged(int index);
   void indexChanged(const QString& text);
   void slotColorSelected(QColor _color);

private:
   //void implAddItem(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem);
   //void implAddItems(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem);

private:
   gsa::core::Controller *_controller;
   //gsa::t::GuiPad *_guiPad;
   QString _caption;

   QTabWidget * _tabWidget;
   //std::map<std::string, QTabWidget *> _tabwidgets;
   QVBoxLayout *_verticalLayout;
   QVBoxLayout *_verticalLayout2;
   QGroupBox *_groupBoxTest;
   QVBoxLayout *_verticalLayout_2;
   QList<QObject*> lineEdits;
   QList<QObject*> pushButtons;
   QList<QObject*> radioButtons;
   QList<QObject*> comboBoxes;
   QList<QObject*> colorSelectores;

   int _itemIndex;
   QObject *currentMenuItem;
   QObject *currentMenuItemPrev;
   //Menu::MenuMeasSetup *_menuMeasSetup;

   //std::map<gsa::t::KeyInfo, int> keys;
   //std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
   TG::KeyPadParam _keyPadParam;
   wchar_t _text[1024];
   wchar_t _unit[1024];
   char ctext[1024];

   Main::MainWindow *_mainWindow;

public slots:

};

