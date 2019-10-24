#pragma once

//#define NOMINMAX
#undef min
#undef max

#include <array>

#include <QtCharts\QChart>
#include <QtCharts\QChartView>
#include <QtCharts\QLineSeries>
#include <QtCharts\QAreaSeries>
#include <QtCharts\QCategoryAxis>
#include <QtCharts\QChartGlobal>
#include <QtCharts\QValueAxis>
#include <QtCharts\QLogValueAxis>

#include <QtCore\QObject>
#include <QtCore\QTimer>
#include <QtCore\QTime>

#include <QSemaphore>
#include <QThread>

#include <QtGui\QScreen>
#include <QtGui\QKeyEvent>
#include <QtGui\QShowEvent>
#include <QtGui\QSurfaceFormat>

#include <QtMultimedia\QAudioDeviceInfo>
#include <QtMultimedia\QAudioInput>

#include <QtWidgets\QDialog>
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
#include <QtWidgets\QGraphicsItem>
#include <QtWidgets\QAbstractGraphicsShapeItem>
#include <QtWidgets\QGraphicsSimpleTextItem>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QSplitter>

#include <QResizeEvent>
#include <QFont>

#ifdef Q_OS_WIN
#include <QtPlatformHeaders\QWindowsWindowFunctions>
#endif
//#include <boost/regex.hpp>
//#include <boost/asio.hpp>

#include "gcore/core.h"
#include "gscreen/dialogitemcombobox.h"
//#include "gmain/mainwindow.h"
#include "Marshaller.h"

#define HTML_TEXT

#ifdef HTML_TEXT
#else
#endif

//#define TEMP1

#ifdef TEMP1
#endif // TEMP1

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QAreaSeries;
class QChart;
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//QT_CHARTS_BEGIN_NAMESPACE
//class QXYSeries;
//QT_CHARTS_END_NAMESPACE
//
//QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;
class QAudioInput;

class Callout;
class ScreenTextItem;
//class Main::MainWindow;

class DialogItemTablePanel;

namespace Main {

   class MainWindow;
   extern const int _numberTrace;

}

class VSplitter : public QSplitter
{
   Q_OBJECT

public:
   VSplitter(QWidget *parent = nullptr)
      : QSplitter(parent)
   {
      ;
   }

   //void moveSplitter(int pos, int index) override;
   void resizeEvent(QResizeEvent *ev)
   {
      //ev->Resize();
      //ev->GraphicsSceneResize();
      int i = 0;
   }
   void changeEvent(QEvent *ev)
   {
      //ev->Resize();
      //ev->GraphicsSceneResize();
      int i = 0;
   }

};

class VChart : public QChart
{
   Q_OBJECT

public:
   VChart(QWidget *parent = nullptr) { ; }

public slots:
   void showEvent(QShowEvent * event);

};

class VChartView : public QChartView
{
   Q_OBJECT

public:
   VChartView(QChart *chart, QWidget *parent = Q_NULLPTR)
      : QChartView(chart)
      , _stop(false)
      , _callout(nullptr)
   {
      _chart = chart;
      _mainWindow = (Main::MainWindow *)parent;
   }
   void setStop() { _stop = false; }
   bool stop() { return _stop; };

   void mousePressEvent(QMouseEvent *event);

   void setLeftBottomText(ScreenTextItem *leftBottomText) { _leftBottomText = leftBottomText; }
   void setRightBottomText(ScreenTextItem *rightBottomText) { _rightBottomText = rightBottomText; }

   //void setScreenBottoms(std::map<gsa::t::GuiScreenPad *, std::array<ScreenTextItem *, 16> > &screenBottoms) {
   void setScreenBottoms(std::map<gsa::t::GuiScreenPad *, std::array<gsa::t::IScreenItem *, 16> > &screenBottoms) {
      _screenBottoms.clear();
      _screenBottoms = screenBottoms;
   }

public slots:
   //void showEvent(QShowEvent * event);
   void keepCallout();
   void tooltip(QPointF point, bool state);

private:
   bool _stop;
   QChart *_chart;
   Callout *_callout;
   QList<Callout *> _callouts;

   ScreenTextItem *_leftBottomText;
   ScreenTextItem *_rightBottomText;
   //std::map<gsa::t::GuiScreenPad *, std::array<ScreenTextItem *, 16> > _screenBottoms;
   std::map<gsa::t::GuiScreenPad *, std::array<gsa::t::IScreenItem *, 16> > _screenBottoms;

   Main::MainWindow *_mainWindow;
};

#ifdef HTML_TEXT 
class ScreenTextItem : public QGraphicsTextItem, public gsa::t::IScreenItem 
#else 
class ScreenTextItem : public QGraphicsSimpleTextItem, public gsa::t::IScreenItem 
#endif 
{
   //Q_OBJECT

public:
   ScreenTextItem(QGraphicsItem *parent = nullptr);
   ~ScreenTextItem();

   void mousePressEvent(QGraphicsSceneMouseEvent *event);

   void setType(QString type) override { _type = type; };
   QString &type(void) override { return _type; };

   void setIndex(int index) override { _index = index; }
   int index(void) override { return _index; }

   void setPosition(const QPoint &point) override { _point = point; setPos(qreal(point.x()), qreal(point.y())); };
   QPoint &position(void) override { return _point; };

   void setLocation(gsa::t::GuiLocation location) override { _location = location; };
   gsa::t::GuiLocation &location(void) override { return _location; };

   //setVisible already exist in Qt 
   void setGsaVisible(bool visible = true) override { _visible = visible; }
   bool gsaVisible(void) override { return _visible; }

   void setName(QString name) override { _name = name; };
   QString &name(void) override { return _name; };

   void setNames(QStringList names) override { _names = names; };
   QStringList &names(void) override { return _names; };

   void setUnit(QString unit) { _unit = unit; };
   QString &unit(void) { return _unit; };

   void setValue(double value) { _value = value; }
   double value(void) { return _value; }

private:
   gsa::t::GuiLocation _location;
   QStringList _names;
   QString _name;
   QString _unit;
   QString _type;
   int _index;
   QPoint _point;
   bool _visible;
   double _value;

};

class PowerSpanSeries : public QLineSeries
{
   Q_OBJECT

public:
   PowerSpanSeries(QObject *parent = nullptr);
   //PowerSpanSeries(QWidget *parent);
   ~PowerSpanSeries();

   QAreaSeries *areaSeries() { return _areaSeries; }
   void setAreaSeries(QAreaSeries *areaSeries) { _areaSeries = areaSeries; }

private:
   QAreaSeries *_areaSeries;

};

class MainScreen : public QWidget
{
   Q_OBJECT

public:
   MainScreen(QWidget *parent, QWidget *appWidget);
   ~MainScreen();

   enum class SeriesType { line = 0, area = 1, power = 2 };

   //int init(QChart **chart, QChartView **chartView);
   int init(VChart **chart, QChartView **chartView, int index, const gsa::t::ThemeFont &font_, const gsa::t::ThemeFont &fontAxis_);
   //void initArray(QLineSeries **m_series, QVector <QPointF> **m_Vector, int index);
   void initArrayNew(const gsa::t::ThemeFont &font_);
   //void initAxis(QLineSeries **series);
   void initAxisNew(const gsa::t::ThemeFont &font_);
   void changeAxises(QLineSeries **series);
   void putCurrentData(gsa::t::CurrentData *data, int m_Period, int index, int length);
   void putTableData(gsa::t::TablePanelData *tablePanelData, int index, int length);
   void putTablePanel(gsa::t::Table *tablePanel, int index);
   void changeData(int item, double value);
   //QAreaSeries *CreateSeries(const MainScreen::SeriesType &type);
   QAbstractSeries *CreateSeries(const int &index, const MainScreen::SeriesType &type);

   void __TestHtmlText(int32_t index);

   //void vrangeChangedX(qreal min, qreal max, bool setrange = false);
   //void vrangeChangedY(qreal min, qreal max, bool setrange = false);
   void vrangeChangedXEmit(qreal min, qreal max, bool setrange = false);
   void vrangeChangedYEmit(qreal min, qreal max, bool setrange = false);

   void setRestyle(int _index, GraphPanelStyle _style);
   void messageBox(wchar_t* _caption, wchar_t* _text);
   void myResizeCallback(wchar_t *name, QRect *rect = nullptr, bool bForce = false);
   void setActiveFont(void);

   void createScreenPage(gsa::t::GuiScreenPad *screenPads);
   void changeData(int item, double value, wchar_t* unit);
   //void setMenuPages(MenuPage *menuPages[]);
   //bool SetPosition(ScreenTextItem *plotInfoTextItem, int index, const gsa::t::GuiLocation &guiLocation, qreal &x, qreal &y);
   bool SetPosition(gsa::t::IScreenItem *plotInfoTextItem, int index, qreal &x, qreal &y, qreal &width, qreal &height);
   //void Double2String(QString &str, double value);

   void OpenItem(ScreenTextItem *item);
   void fillComboBox(gsa::t::GuiScreenPad *screenPad, int index);
   void fillEditBox(gsa::t::GuiScreenPad *screenPad, int index);
   QWidget *fillTablePanel(QWidget *parent, gsa::t::Table *tablePanel, int index, QGridLayout *gridLayout);
   DialogItemTablePanel *dialogItemTablePanel(gsa::t::Table *tablePanel);

   //void putTheme(gsa::t::Theme *_theme);

   void setCentralRect(const QRect &rect);

   void setExit(void) { _exit = true; }

private:
   gsa::t::CurrentData *_data;

   gsa::t::XYValue* m_values;

   bool _exit;
   QSemaphore _semaphore;

   //QChart *_chart;
   //QChartView *_chartView;
   VChart *_chart;
   VChartView *_chartView;
   //Main::MainWindow *_mainWindow;
   Main::MainWindow *_parentWindow;
   Main::MainWindow *_appWidget;
   //QDialog *_dialog;
   DialogItemComboBox *_dialog;

   bool _axisLog;
   //QValueAxis *_axisX;
   //QValueAxis *_axisY;
   QAbstractAxis *_axisX;
   QAbstractAxis *_axisY;
   QAbstractAxis *_axisLogX;
   QAbstractAxis *_axisLogY;
   QAbstractAxis *_axisActiveX;
   QAbstractAxis *_axisActiveY;

   //QLineSeries *_series;
   //QVector <QPointF> *_vector;
   //QLineSeries *m_series;
   //QVector <QPointF> *m_Vector;
   //QMap<int, QLineSeries *> _arrayseries;
   QMap<int, QAbstractSeries *> _arrayseries;
   //van_2019_01_25
   //QAreaSeries *_areaSeries;
   //PowerSpanSeries *_areaSeries;
   //QMap<int, QVector <QPointF> *> _vectors;
   //QLineSeries *_carrigeSeries;
   //QLineSeries *_markerSeries;
   //QMap<int, QLineSeries *> _markerseries;
   //QMap<int, QVector <QPointF> *> _markervectors;
   QOpenGLWidget *m_GLWidget;
   int m_Skiped;
   int m_Position;
   int m_Blinker;
   int _chartWidth;
   int _plotWidth;
   int _chartViewHeight;
   int _offsetIndexMarker;
   //int _numberTrace;
   //int _numberMarker;
   qreal _xmin;
   qreal _xmax;
   qreal _ymin;
   qreal _ymax;
   qreal _yminLinear;
   qreal _ymaxLinear1;
   std::map<QObject*, bool> _updated;
   //QGraphicsSimpleTextItem *_freqText;
   //QGraphicsSimpleTextItem *_valueText;
   //QGraphicsSimpleTextItem *_anyText;

#ifdef HTML_TEXT
   QMap<int, QGraphicsTextItem *> _anyTextes;
#else
   QMap<int, QGraphicsSimpleTextItem *> _markerTextes;
#endif
   QMap<int, QGraphicsSimpleTextItem *> _freqTextes;
   QMap<int, QGraphicsSimpleTextItem *> _valueTextes;
   //QGraphicsSimpleTextItem *_leftBottomText;
   //QGraphicsSimpleTextItem *_rightBottomText;
   ScreenTextItem *_leftBottomText;
   ScreenTextItem *_rightBottomText;
   //std::array<ScreenTextItem *, 16> _screenBottoms;
   //std::map<gsa::t::GuiScreenPad *, std::array<ScreenTextItem *, 16> > _screenBottoms;
   //std::map<gsa::t::GuiScreenPad *, std::array<DialogItemComboBox *, 16> > _screenComboBoxes;
   std::map<gsa::t::GuiScreenPad *, std::array<gsa::t::IScreenItem *, 16> > _screenBottoms;
   std::map<gsa::t::Table *, gsa::t::IScreenItem * > _screenTablePanels;
   gsa::t::Table *_tablePanel;
   QStringList _names;
   QRect _centralRect;
   gsa::t::ThemeFont _font;

   std::map<std::wstring, gsa::t::FontIndex> _fontindexes;
   std::map<std::wstring, gsa::t::ColorIndex> _colorindexes;
   std::map<std::wstring, gsa::t::SizeIndex> _sizeindexes;
   std::map<std::wstring, gsa::t::IndentIndex> _indentindexes;

   QVector <QPointF> vector_[24]; //[Main::_numberTrace];

   QLineSeries *___series___;

protected:
   void resizeEvent(QResizeEvent * event);
   void moveEvent(QMoveEvent * event);

   GraphPanelStyle m_CurrentStyle;

public slots:

   void vrangeChangedX(qreal min, qreal max, bool setrange); // = false);
   void vrangeChangedY(qreal min, qreal max, bool setrange); // = false);

   void on_rangeChangedX(qreal min, qreal max);
   void on_rangeChangedY(qreal min, qreal max);

   void Updated(void);
   void Swaped(void);
   void Sized(void);

   void slotPutCurrentData(int m_Period, int index, int length);
   void slotRestyle(int _Index);

   void callDialog(void);

   void tablePanelIndexChangedExpd(int index, int flag);

signals:

   //void MySignal(wchar_t* _caption, wchar_t* _text);
   void signalSetMarker(int index, QString text, QColor);
   void signalMessageBox(wchar_t* _caption, wchar_t* _text);
   void signalPutCurrentData(int m_Period, int index, int length);

   void signalVrangeChangedX(qreal min, qreal max, bool setrange);
   void signalVrangeChangedY(qreal min, qreal max, bool setrange);
   void signalRestyle(int _Index);

   void tablePanelIndexChanged(int, int);

};

