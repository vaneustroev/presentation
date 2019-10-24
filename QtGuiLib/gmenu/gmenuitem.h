#pragma once

//#define NOMINMAX
#undef min
#undef max

#include <QtCharts\QChart>
#include <QtCharts\QChartView>
#include <QtCharts\QLineSeries>
#include <QtCharts\QCategoryAxis>
#include <QtCharts\QChartGlobal>
#include <QtCharts\QValueAxis>

#include <QtCore\QObject>
#include <QtCore\QTimer>
#include <QtCore\QTime>

#include <QtGui\QScreen>
#include <QtGui\QKeyEvent>
#include <QtGui\QShowEvent>

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
#include <QtWidgets\QPushButton>
#include <QtWidgets\QOpenGLWidget>
#include <QtWidgets\QRadioButton>
#include <QtWidgets\QComboBox>

#include <QtGui\QSurfaceFormat>

#ifdef Q_OS_WIN
#include <QtPlatformHeaders\QWindowsWindowFunctions>
#endif
//#include <boost/regex.hpp>
//#include <boost/asio.hpp>

#include "gcore/core.h"
#include "gcolor/color_selector.hpp"

class MenuPage;

class MenuItem : public QLineEdit
{
   Q_OBJECT

public:
   MenuItem(QWidget *parent, int itemIndex, int currentIndex, MenuPage*menuPage, QGroupBox *groupBox);
   ~MenuItem();

   int itemIndex(void) { return _itemIndex; }
   QGroupBox *groupBox() { return _groupBox; }
   int currentIndex(void) { return _currentIndex; }
   void setButtonNames(QStringList &buttonNames) { 
      _keyPadParam._buttonNames.clear(); 
      _keyPadParam._buttonNames = buttonNames; 
   }
   QStringList &buttonNames(void) {
      return _keyPadParam._buttonNames;
   }
   TG::KeyPadParam &keyPadParam(void) { return _keyPadParam; }

   void setName(wchar_t *name) { wcscpy(_name, name); }
   wchar_t *name(void) { return _name; }

   void setFocus(Qt::FocusReason reason);
   void setFocus(void);

   bool processFocus(void) { return _focus; }
   void setProcessFocus(bool focus) { _focus = focus; }

   void wheelEvent(QWheelEvent * event);
   void doWheelEvent(int delta);

   TG::KeyPadParam _keyPadParam;

protected:
   void focusInEvent(QFocusEvent *e);
   //{
   //   QLineEdit::focusInEvent(e);
   //   deselect();
   //}

private:
   int _itemIndex;
   int _currentIndex;
   bool _focus;
   MenuPage *_menuPage;
   QGroupBox *_groupBox;

   //TG::KeyPadParam _keyPadParam;
   wchar_t _unit[1024];
   wchar_t _name[1024];

public slots :

};

class MenuPushButton : public QPushButton
{
   Q_OBJECT

public:
   MenuPushButton(QWidget *parent, int itemIndex, QGroupBox *groupBox);
   ~MenuPushButton();

   int itemIndex(void) { return _itemIndex; }
   QGroupBox *groupBox() { return _groupBox; }

private:
   int _itemIndex;
   QGroupBox *_groupBox;

public slots :

};

class MenuRadioButton : public QRadioButton
{
   Q_OBJECT

public:
   MenuRadioButton(QWidget *parent, int itemIndex, int index, QGroupBox *groupBox);
   ~MenuRadioButton();

   int itemIndex(void) { return _itemIndex; }
   QGroupBox *groupBox() { return _groupBox; }
   int index(void) { return _index; }

private:
   int _itemIndex;
   int _index;
   QGroupBox *_groupBox;

public slots :

};

class MenuComboBox : public QComboBox
{
   Q_OBJECT

public:
   MenuComboBox(QWidget *parent, int itemIndex, QGroupBox *groupBox);
   ~MenuComboBox();

   int itemIndex(void) { return _itemIndex; }
   QGroupBox *groupBox() { return _groupBox; }

private:
   int _itemIndex;
   QGroupBox *_groupBox;

public slots :

};

class MenuColorSelector : public Color_Selector
{
   Q_OBJECT

public:
   MenuColorSelector(QWidget *parent, int itemIndex, QGroupBox *groupBox);
   ~MenuColorSelector();

   int itemIndex(void) { return _itemIndex; }
   QGroupBox *groupBox() { return _groupBox; }

private:
   int _itemIndex;
   QGroupBox *_groupBox;

   public slots :

};

