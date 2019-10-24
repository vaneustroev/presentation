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
#include <QtWidgets\QOpenGLWidget>
#include <QtWidgets\QRadioButton>

#include <QtGui\QSurfaceFormat>

#ifdef Q_OS_WIN
#include <QtPlatformHeaders\QWindowsWindowFunctions>
#endif
//#include <boost/regex.hpp>
//#include <boost/asio.hpp>

#include "gcore/core.h"

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
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

class VChart : public QChart
{
	Q_OBJECT

public:
	VChart(QWidget *parent = nullptr) {;}

public slots:
	void showEvent(QShowEvent * event);

};

class MainScreen : public QWidget
{
	Q_OBJECT

public:
	MainScreen(QWidget *parent);
	~MainScreen();

	//int init(QChart **chart, QChartView **chartView);
	int init(VChart **chart, QChartView **chartView, int index);
	void initArray(QLineSeries **m_series, QVector <QPointF> **m_Vector, int index);
	void putCurrentData(gsa::t::CurrentData *_Data, int m_Period, int index);
	void putCarriage(gsa::t::CurrentData *_Data, int m_Period, int index);
	void changeData(int item, double value);

	void sceneChanged(const QList<QRectF> &region);
	void sceneFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason);
	void sceneSceneRectChanged(const QRectF &rect);
	void sceneSelectionChanged();

	void vrangeChangedX(qreal min, qreal max, bool setrange = false);
	void vrangeChangedY(qreal min, qreal max, bool setrange = false);
	void myResizeCallback(wchar_t *name);

private:
	gsa::t::XYValue* m_values;

	//QChart *_chart;
	VChart *_chart;
	QChartView *_chartView;
	QValueAxis *_axisX;
	QValueAxis *_axisY;
	//QLineSeries *_series;
	//QVector <QPointF> *_vector;
	QLineSeries *m_series;
	QVector <QPointF> *m_Vector;
	QMap<int, QLineSeries *> _arrayseries;
	QMap<int, QVector <QPointF> *> _vectors;
	QOpenGLWidget *m_GLWidget;
	//QGraphicsRectItem *_carriageItem;
	QGraphicsItem *_carriageItem;
	bool m_bUpdated;
	int m_Skiped; 
	int m_Position;
	int m_Blinker;
	int _chartWidth;
	int _plotWidth;
	int _x;
	int _y;

protected:
	void resizeEvent(QResizeEvent * event);
	void moveEvent(QMoveEvent * event);

public slots:

	void on_rangeChangedX(qreal min, qreal max);
	void on_rangeChangedY(qreal min, qreal max);

	void Updated(void);
	void Swaped(void);
	void Sized(void);

};

