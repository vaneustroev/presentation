// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <float.h>
#include <algorithm>
//#include <boost/container/vector.hpp>
//#include <boost/chrono.hpp>

//#include "gcore/controller.h"
//#include "gcore/core.h"

//#include "gmain/xyseriesiodevice.h"

#include "gscreen/gmainscreen.h"
#include "guiUnman.h"

class Controller;

QT_CHARTS_USE_NAMESPACE

MainScreen::MainScreen(QWidget *parent)
	: QWidget(parent)
	, m_values(nullptr)
	, _chart(nullptr)
	, _chartView(nullptr)
	, _axisX(nullptr)
	, _axisY(nullptr)
	//, _series(nullptr)
	//, _vector(nullptr)
	, m_series(nullptr)
	, m_Vector(nullptr)
	, _carriageItem(nullptr)
	, m_bUpdated(true)
	, m_Skiped(0)
	, m_Position(0)
	, m_Blinker(0)
	, _chartWidth(0)
	, _plotWidth(0)
	, _x(0)
	, _y(0)
{
	//m_Period = 16666;

	this->setAttribute(Qt::WA_AcceptTouchEvents);
}

MainScreen::~MainScreen()
{
	QMap<int, QLineSeries *>::iterator it1 = _arrayseries.begin();
	while (it1 != _arrayseries.end() ) {
		delete (*it1);
		++it1;
	}
	QMap<int, QVector <QPointF> *>::iterator it2 = _vectors.begin();
	while (it2 != _vectors.end()) {
		delete (*it2);
		++it2;
	}
}

void MainScreen::initArray(QLineSeries **series, QVector <QPointF> **vectors, int index)
{
	//if ((*series) != nullptr) delete (*series);
	//if ((*vectors) != nullptr) delete (*vectors);

	QMap<int, QLineSeries *>::iterator it1 = _arrayseries.find(index);
	if (it1 != _arrayseries.end()) {
		delete (*it1);
	}
	QMap<int, QVector <QPointF> *>::iterator it2 = _vectors.begin();
	if (it2 != _vectors.end()) {
		delete (*it2);
	}

	(*series) = new QLineSeries;
	_chart->addSeries((*series));
	_chart->setAxisX(_axisX, (*series));
	_chart->setAxisY(_axisY, (*series));

	(*vectors) = new QVector<QPointF>(gsa::t::maxPoint);
	for (int l_N = 0; l_N < gsa::t::maxPoint; l_N++)
	{
		(*(*vectors))[l_N].setX(DBL_MAX);
		(*(*vectors))[l_N].setY(0);
	}

	_arrayseries[index] = m_series;
	_vectors[index] = m_Vector;
}

//int MainScreen::init(QChart **chart, QChartView **chartView)
int MainScreen::init(VChart **chart, QChartView **chartView, int index)
{
	//if (_chartView != nullptr) delete _chartView;
	//if (_chart != nullptr) delete _chart;
	//if (_axisX != nullptr) delete _axisX;
	//if (_axisY != nullptr) delete _axisY;

	//_chart = new QChart;
	if (_chart == nullptr) _chart = new VChart;
	if (_chartView == nullptr) _chartView = new QChartView(_chart);
	if (_axisX == nullptr) _axisX = new QValueAxis;
	if (_axisY == nullptr) _axisY = new QValueAxis;

	(*chart) = _chart;
	//_chart->size();
	//_chart->setMinimumSize(2048, 1024);

	//(*chartView) = new QChartView(_chart);
	(*chartView) = _chartView;

	//(*chartView)->setMinimumSize(800, 600);
	(*chartView)->setAttribute(Qt::WA_AcceptTouchEvents);

	//(*chartView)->setAttribute(Qt::WA_PaintOutsidePaintEvent, true);
	//(*chartView)->setAttribute(Qt::WA_PaintOnScreen, true);
	//(*chartView)->setAttribute(Qt::WA_PaintUnclipped, true);

	_axisX->setRange(0, gsa::t::maxPoint);
	_axisX->setLabelFormat("%g");
	_axisX->setTitleText("Frequency");

	_axisY->setRange(-50, 50);
	_axisY->setLabelFormat("%g");
	_axisY->setTitleText("Level");

	_chart->legend()->hide();
	_chart->setTitle("Spectrum analyzer");

	//m_series = new QLineSeries;
	//_chart->addSeries(m_series);
	//_chart->setAxisX(_axisX, m_series);
	//_chart->setAxisY(_axisY, m_series);
	//m_Vector = new QVector<QPointF>(gsa::t::maxPoint);
	//for (l_N = 0; l_N < gsa::t::maxPoint; l_N++)
	//{
	//	(*m_Vector)[l_N].setX(DBL_MAX);
	//	(*m_Vector)[l_N].setY(0);
	//}
	initArray(&m_series, &m_Vector, index);
	//_arrayseries[index] = m_series;
	//_vectors[index] = m_Vector;

	//_chart->grabGesture(Qt::TapGesture);//= 1,
	//_chart->grabGesture(Qt::TapAndHoldGesture);//= 2,
	//_chart->grabGesture(Qt::PanGesture);//= 3,
	//_chart->grabGesture(Qt::PinchGesture);//= 4,
	//_chart->grabGesture(Qt::SwipeGesture);//= 5,

	//_chart->grabGesture(Qt::PanGesture);
	//_chart->grabGesture(Qt::PinchGesture);

	//(*chartView)->setRubberBand(QChartView::HorizontalRubberBand);
	(*chartView)->setRubberBand(QChartView::VerticalRubberBand);
	(*chartView)->setRubberBand(QChartView::HorizontalRubberBand);
	(*chartView)->setRubberBand(QChartView::RectangleRubberBand);

	//connect(_chart->axis(), SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(on_rangeChanged(qreal, qreal)));
	connect(_chart->axisX(), SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(on_rangeChangedX(qreal, qreal)));
	connect(_chart->axisY(), SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(on_rangeChangedY(qreal, qreal)));

	QObject::connect(m_series, SIGNAL(pointsReplaced()), SLOT(Updated()));

	//v_openGl
	//если включить OpenGL, то почему-то перестают нормально работать некоторые органы управления, например QComboBox
	//m_series->setUseOpenGL(true);

	////ui->comboBox->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	////ui->comboBox->setFocusProxy((QWidget *)chartView);
	//ui->comboBox->setMaxVisibleItems(10);
	////ui->comboBox->setMinimumHeight(100);

	QGraphicsView::ViewportUpdateMode vp = _chartView->viewportUpdateMode();
	QGraphicsScene *scene_ = _chart->scene();
	QList<QGraphicsView *> views_ = scene_->views();
	int size2_ = views_.size();
	QList<QGraphicsItem *> items_ = _chartView->items();
	int size3_ = items_.size();
	QList<QGraphicsItem *> itemsChild0_ = items_.at(0)->childItems();
	QGraphicsItem * itemsParent0_ = items_.at(0)->parentItem();
	QGraphicsItem * itemsTopLevel_ = items_.at(0)->topLevelItem();
	QList<QGraphicsItem *> itemsChildTop_ = itemsTopLevel_->childItems();
	int sizeChild0_ = itemsChild0_.size();
	int sizeChildTop0_ = itemsChildTop_.size();

	QObject::connect(scene_, SIGNAL(changed(const QList<QRectF> &)), this, SLOT(sceneChanged(const QList<QRectF> &)));
	QObject::connect(scene_, SIGNAL(focusItemChanged(QGraphicsItem *, QGraphicsItem *, Qt::FocusReason )), this, SLOT(sceneFocusItemChanged(QGraphicsItem *, QGraphicsItem *, Qt::FocusReason)));
	QObject::connect(scene_, SIGNAL(sceneRectChanged(const QRectF &)), this, SLOT(sceneSceneRectChanged(const QRectF &)));
	QObject::connect(scene_, SIGNAL(selectionChanged()), this, SLOT(sceneSelectionChanged()));

	//void sceneFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason)
	//void sceneSceneRectChanged(const QRectF &rect)
	//void sceneSelectionChanged()

	//QRect rect_(30, 850, 30, 30);
	QRect rect_(30, 30, 30, 30);

	//_carriageItem = scene_->addRect(rect_);
	//QGraphicsRectItem *torsoItem = new QGraphicsRectItem(itemsTopLevel_);
	//_carriageItem = new QGraphicsRectItem(rect_, itemsTopLevel_);

	if (itemsChildTop_.size() > 0)
		//_carriageItem = new QGraphicsRectItem(rect_, itemsChildTop_[itemsChildTop_.size() - 1]);
		_carriageItem = new QGraphicsRectItem(rect_, itemsChildTop_[0]);
		//_carriageItem = new QGraphicsRectItem(rect_, itemsChildTop_[itemsChildTop_.size() / 2]);
		//_carriageItem = new QGraphicsRectItem(rect_, items_[0]);
		//_carriageItem = new QGraphicsRectItem(rect_, itemsChildTop_[13]);
		//1 don't work
		//7 don't work
		//8 
		//9  work
		//10 don't work
		//13 don't work
		//_carriageItem = new QGraphicsRectItem(rect_, itemsTopLevel_);
	else
		_carriageItem = nullptr;

	bool at = _carriageItem->isWidget();

	QGraphicsItem *itemsTopLevel2_ = items_.at(0)->topLevelItem();
	//_carriageItem = itemsTopLevel_->addRect(rect_);
	//views_[0]->findChild<int*>();
	QList<QGraphicsItem *> items2_ = scene_->views()[0]->items();
	int size5_ = items2_.size();

	int i(0);
	int aaa(0);
	bool aWidget(_carriageItem->isWidget());
	bool aWindow(_carriageItem->isWindow());
	bool aPanel(_carriageItem->isPanel());
	QList<QGraphicsItem *> items9_ = _chartView->items();
	for (auto itm : items9_) {
		aWidget = false;
		aWindow = false;
		aPanel = false;
		if (itm->isWidget()) {
			aWidget = true;
		}
		else if (itm->isWindow()) {
			aWindow = true;
		}
		else if (itm->isPanel()) {
			aWindow = true;
		}
		if (aWidget) {
			_carriageItem = itm;
		}
		aaa = itm->type();
		++i;
	}

	//QGraphicsItem *top = _carriageItem->topLevelItem();
	//for (int i = 0; i < 45; i++) {
	//	//_carriageItem->setRotation(1);
	//	_carriageItem->moveBy(10, 10);
	//}

	_chart->scene()->views()[0]->items().at(0)->topLevelItem();

	QStringList strings;
	std::for_each(items_.begin(), items_.end(), [&strings](QGraphicsItem *item) 
	{
		if (item->toGraphicsObject() != nullptr && item->toGraphicsObject()->metaObject() != nullptr) {
			strings.push_back(QString("type=%1 parent=%2 name=%3 class=%4 ").arg(item->type()).
				arg((long)(item->parentItem())).arg(QString(item->toGraphicsObject()->objectName())).arg(item->toGraphicsObject()->metaObject()->className()));
		}
		else {
			strings.push_back(QString("type=%1 parent=%2 p=%3 ").arg(item->type()).arg((long)(item->parentItem())).arg((long)item->toGraphicsObject()));
		}
	} );
	QStringList strings2;
	std::for_each(itemsChildTop_.begin(), itemsChildTop_.end(), [&strings2](QGraphicsItem *item) 
	{
		if (item->toGraphicsObject() != nullptr && item->toGraphicsObject()->metaObject() != nullptr ) {
			strings2.push_back(QString("type=%1 parent=%2 name=%3 class=%4 ").arg(item->type()).
				arg((long)(item->parentItem())).arg(QString(item->toGraphicsObject()->objectName())).arg(item->toGraphicsObject()->metaObject()->className()) );
		}
		else {
			strings2.push_back( QString("type=%1 parent=%2 p=%3 ").arg(item->type()).arg((long)(item->parentItem())).arg((long)item->toGraphicsObject()) );
		}
	} );

	int j(0);

	////v_openGl
	//int counter;
	//QSurfaceFormat surfaceFormat;
	//QList<QGraphicsView*> l_ViewList;
	//QList<QOpenGLWidget*> l_GLList;
	//int l_N;

	//l_ViewList = _chart->scene()->views();
	//l_GLList = l_ViewList[0]->findChildren<QOpenGLWidget *>();
	//m_GLWidget = l_GLList[0];
	//QObject::connect(m_GLWidget, SIGNAL(frameSwapped()), SLOT(Swaped()));
	//QObject::connect(m_GLWidget, SIGNAL(resized()), SLOT(Sized()));




	//////openGLWidget = (QOpenGLWidget *)chartView;
	//////surfaceFormat = openGLWidget->format();
	////surfaceFormat = ll[0]->format();

	////int si = surfaceFormat.swapInterval();

	//ui->horizontalLayout->addWidget(chartView);
	//ui->frameRight->raise();

	QSize _size2 = (*chartView)->size();

	VSyncCallback();

	return 0;
}

void MainScreen::vrangeChangedX(qreal min, qreal max, bool setrange)
{
	if(setrange) _chart->axisX()->setRange(min, max);
}

void MainScreen::vrangeChangedY(qreal min, qreal max, bool setrange)
{
	if (setrange) _chart->axisY()->setRange(min, max);
}

void MainScreen::on_rangeChangedX(qreal min, qreal max)
{
	return;

	wchar_t _Param1[1024];
	GraphPanelRange _Param2;
	_Param2.Min = min;
	_Param2.Max = max;

	if (RerangeXCallback != nullptr) {
		RerangeXCallback(_Param1, _Param2);
		//_chart->axisX()->setRange(min, max);
	}

	//if (scrolling) return;  // Scrolling causes range changes, but we don't have to do anything.

	//QChart *c = ui->chartView->chart();
	//QAbstractAxis *x = c->axisX();
	//qreal avg = (min + max) / 2.0;
	//bool range_fixed = false;

	///*
	//* Make sure the new range is sane; fix if not.
	//*/
	//if ((max - min) < 0.1) {    // Avoid overzooming
	//	min = avg - 0.05;
	//	max = avg + 0.05;
	//	range_fixed = true;
	//}

	//if (min < 0.0) { min = 0.0; range_fixed = true; }

	//if (max > 4.0) { max = 4.0; range_fixed = true; }

	//if (range_fixed) {
	//	x->setRange(min, max);    // will re-signal with the fixed range
	//	return;
	//}

	//qreal    vis_width = c->plotArea().width();
	//qreal    all_width = vis_width * (4.0 - 0.0) / (max - min);

	////    cerr << "range " << min << " ... " << max << " in " << vis_width << " pixels" << endl;
	////    cerr << "full width requires " << all_width << " pixels" << endl;;

	//if (max - min < 4.0) {
	//	//        cerr << "set scroll parameters" << endl;
	//	scrolling = true;
	//	ui->chartScroll->setMaximum(all_width - vis_width);
	//	sv = min / (4.0 - 0.0) * all_width;
	//	ui->chartScroll->setValue(sv);
	//	scrolling = false;
	//}
	//else {
	//	//        cerr << "disable scroll bar" << endl;
	//	scrolling = true;
	//	ui->chartScroll->setMaximum(0);
	//	ui->chartScroll->setValue(sv);
	//	scrolling = false;
	//}
}

void MainScreen::on_rangeChangedY(qreal min, qreal max)
{
	return;

	wchar_t _Param1[1024] = L"Spectrogram";
	GraphPanelRange _Param2;
	_Param2.Min = min;
	_Param2.Max = max;

	if (RerangeYCallback != nullptr) {
		RerangeYCallback(_Param1, _Param2);
		//_chart->axisY()->setRange(min, max);
	}
}

void MainScreen::Updated(void)
{
	m_bUpdated = true;
}

void MainScreen::Swaped(void)
{
	VSyncCallback();
}

void MainScreen::myResizeCallback(wchar_t *name)
{
	//int _chartWidth = _chart->plotArea().width();
	if (_chartWidth != _chart->plotArea().width()) {
		ResizeCallback(name, _chart->plotArea().width());
	}
}

void MainScreen::Sized(void)
{
	QSize size3 = _chartView->size();
	QSize size4 = size();
	//int _chartWidth = _chart->plotArea().width();
	//int i(0);

	if (_chartWidth != _chartView->size().width()) {
		_chartWidth = _chartView->size().width();
		int width = _chart->plotArea().width();
		ResizeCallback(L"Spectrogram", _chart->plotArea().width());
	}

	//endless cycle 
	if (_plotWidth != _chart->plotArea().width() ) {
		_plotWidth = _chart->plotArea().width();
		//ResizeCallback(L"Spectrogram", _chart->plotArea().width());
	}

	/*QRect l_Rect;
	QSize l_Size;
	QSizeF l_Sizef;
	l_Rect = m_GLWidget->geometry();
	l_Size = m_GLWidget->size();
	l_Size = m_GLWidget->maximumSize();
	l_Size = m_GLWidget->minimumSize();
	l_Sizef = _chart->preferredSize();
	l_Sizef = _chart->size();
	l_Sizef = _chart->maximumSize();
	l_Sizef = _chart->minimumSize();*/
}

void MainScreen::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event)

	QSize size1_ = event->size();
	QSize size2_ = size();

	QDesktopWidget *mydesk = QApplication::desktop();
	QSize size2 = mydesk->size();

	//QSize size3 = _chartView->size();
	//QSize size4 = _mainScreen->size();
}

void MainScreen::moveEvent(QMoveEvent * event)
{
	Q_UNUSED(event)

	//QSize size1_ = event->size();
	QSize size2_ = size();

	QDesktopWidget *mydesk = QApplication::desktop();
	QSize size2 = mydesk->size();

	//QSize size3 = _chartView->size();
	//QSize size4 = _mainScreen->size();
}

void MainScreen::changeData(int item, double value)
{
	//_mainScreen->changeData(item, value);
	int i(0);
}

void MainScreen::putCarriage(gsa::t::CurrentData *_Data, int m_Period, int index)
{
	//QWidget *window = (QWidget*)_chartView;
	//window->paintEngine();

	//QPainter* painter = new QPainter(window);
	////QPixmap pixmap1("\\images\\tile_1.png");

	////painter->drawPixmap(QPoint(0,0), pixmap1);  // this works
	//painter->setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
	//painter->drawLine(10, 10, 100, 500);
	//delete painter;

	//QPixmap pixmap(100, 100);
	//pixmap.fill(QColor("transparent"));

	//QPainter painter(&pixmap);
	//painter.setBrush(QBrush(Qt::black));
	//painter.drawRect(10, 10, 100, 100);

	//label.setPixmap(pixmap);

	//QList<QOpenGLWidget*> l_GLList;
	//l_GLList = _chartView->findChildren<QOpenGLWidget *>();

	//QList<QGraphicsRectItem *> rectItems = _chartView->findChildren<QGraphicsRectItem *>();
	//if (rectItems.size() > 0) {
	//	rectItems[0]->moveBy(1, 1);
	//}

	//_carriageItem->setRotation(10);
	//QGraphicsItem *top = _carriageItem->topLevelItem();
	//QGraphicsItem *top = _chart->scene()->views()[0]->items().at(0)->topLevelItem();
	//QList<QGraphicsItem *> itemsChildTop_ = top->childItems();
	//_carriageItem->moveBy(1, 1);

	//if(top != nullptr) top->setRotation(10);
}

void MainScreen::sceneChanged(const QList<QRectF> &region)
{
	int size_ = region.size();
}

void MainScreen::sceneFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason)
{
	int i(0);
}

void MainScreen::sceneSceneRectChanged(const QRectF &rect)
{
	int i(0);
}

void MainScreen::sceneSelectionChanged()
{
	int i(0);
}

void MainScreen::putCurrentData(gsa::t::CurrentData *_Data, int m_Period, int index)
{
	//if (m_bUpdated)
	//{
		int _size1 = _chart->scene()->views().size();
		if (_size1 > 0) {
			int _size2 = _chart->scene()->views()[0]->items().size();
			if (_size2 > 0) {


				//QGraphicsItem *top = _chart->scene()->views()[0]->items().at(0)->topLevelItem();
				//QList<QGraphicsItem *> itemsChildTop_ = top->childItems();
				//int _size = itemsChildTop_.size();
				//if (_size > 0) {
				//	QList<QGraphicsItem *> itemsChild_ = itemsChildTop_[0]->childItems();
				//	//itemsChildTop_[0]->moveBy(10, 10);
				//	//itemsChildTop_[2]->setRotation(0);
				//	//itemsChildTop_[0]->setScale(1);
				//	//itemsChildTop_[0]->setPos(300, 300);

				//	_x += 10;
				//	_y += 10;
				//	if (_x > 300) _x = 0;
				//	if (_y > 300) _y = 0;
				//	itemsChildTop_[0]->setPos(_x, _y);
				//	int size5 = _chart->scene()->views()[0]->items().size();
				//	if (size5 == 0) {
				//		int i(0);
				//	}
				//	bool active = itemsChildTop_[0]->isActive();

				//	_chart->scene()->update();

				//	//_carriageItem->setPos(10, 10);
				//	//itemsChild_[0]->setPos(0, 0);

				//	//QList<QGraphicsRectItem *> items123_ = scene_->findChildren<QGraphicsRectItem*>();
				//	//QGraphicsRectItem * item123_ = _chart->scene()->findChild<QGraphicsRectItem*>();
				//	//if (item123_) {
				//	//	item123_->setPos(10, 10);
				//	//}
				//	//else {
				//	//	int i(0);
				//	//}
				//	//itemsChildTop_[0]->setPos(10, 10);
				//	int i(0);
				//}
				//else {
				//	int i(0);
				//}

				//m_bUpdated = false;

				QGraphicsItem *top = _chart->scene()->views()[0]->items().at(0)->topLevelItem();
				QList<QGraphicsItem *> itemsChildTop_ = top->childItems();
				int _size = itemsChildTop_.size();
				if (_size > 0) {
					QList<QGraphicsItem *> itemsChild_ = itemsChildTop_[0]->childItems();
					//itemsChildTop_[0]->moveBy(10, 10);
					//itemsChildTop_[2]->setRotation(0);
					//itemsChildTop_[0]->setScale(1);
					//itemsChildTop_[0]->setPos(300, 300);

					_x += 10;
					_y += 10;
					if (_x > 400) _x = 0;
					if (_y > 400) _y = 0;
					itemsChildTop_[0]->setPos(_x, _y);
					//itemsChild_[0]->setPos(_x, _y);

					//_carriageItem->setPos(10, 10);
					//itemsChild_[0]->setPos(0, 0);

					//QList<QGraphicsRectItem *> items123_ = scene_->findChildren<QGraphicsRectItem*>();
					//QGraphicsRectItem * item123_ = _chart->scene()->findChild<QGraphicsRectItem*>();
					//if (item123_) {
					//	item123_->setPos(10, 10);
					//}
					//else {
					//	int i(0);
					//}
					//itemsChildTop_[0]->setPos(10, 10);
					int i(0);
				}
				else {
					int i(0);
				}



			}
		}
	//}

	VSyncCallback();

	return;




	int counter;
	QSurfaceFormat surfaceFormat;
	QList<QGraphicsView*> l_ViewList;
	QList<QOpenGLWidget*> l_GLList;

	if (m_values == nullptr) {
		m_values = new gsa::t::XYValue[gsa::t::maxPoint];
	}
	else
	{
		if (_arrayseries.size()==0 || _vectors.size()==0) {
			return;
		}
		else {
			QMap<int, QLineSeries *>::iterator it = _arrayseries.find(index);
			if (it == _arrayseries.end()) 
			{
				//m_series = new QLineSeries;
				//_chart->addSeries(m_series);
				//_chart->setAxisX(_axisX, m_series);
				//_chart->setAxisY(_axisY, m_series);
				//
				//m_Vector = new QVector<QPointF>(gsa::t::maxPoint);
				//for (int l_N = 0; l_N < gsa::t::maxPoint; l_N++)
				//{
				//	(*m_Vector)[l_N].setX(DBL_MAX);
				//	(*m_Vector)[l_N].setY(0);
				//}
				initArray(&m_series, &m_Vector, index);
				//_arrayseries[index] = m_series;
				//_vectors[index] = m_Vector;

				m_series->setUseOpenGL(true);
				l_ViewList = _chart->scene()->views();
				l_GLList = l_ViewList[0]->findChildren<QOpenGLWidget *>();
				m_GLWidget = l_GLList[0];
				QObject::connect(m_GLWidget, SIGNAL(frameSwapped()), SLOT(Swaped()));
				QObject::connect(m_GLWidget, SIGNAL(resized()), SLOT(Sized()));

				//_arrayseries[index] = m_series;
				//_vectors[index] = m_Vector;
			}
			else {
				m_series = _arrayseries[index];
				m_Vector = _vectors[index];
			}
		}

		if (m_Vector == nullptr || m_series == nullptr)
			return;

		m_Blinker = (m_Blinker + 1) % (1000000 / m_Period);

		for (counter = 0; counter < gsa::t::maxPoint; counter++)
//		for (counter = 0; counter < _Data->Length; counter++)
		{
			if(counter < _Data->Length)
				(*m_Vector)[counter].setX(_Data->Values[counter].XValue);
			else
				(*m_Vector)[counter].setX(DBL_MAX);
			(*m_Vector)[counter].setY(_Data->Values[counter].YValue);
		}

		if (m_bUpdated)
		{
			//(*m_SkipedVector)[m_Position].setX(m_Position);
			m_Skiped = 0;
			m_Position = (m_Position + 1) % gsa::t::maxPoint;

			//ui->labelPeriod->setText(QString::number(m_Period));

			//Sleep(32);

			QGraphicsItem *top = _chart->scene()->views()[0]->items().at(0)->topLevelItem();
			QList<QGraphicsItem *> itemsChildTop_ = top->childItems();
			int _size = itemsChildTop_.size();
			if (_size > 0) {
				QList<QGraphicsItem *> itemsChild_ = itemsChildTop_[0]->childItems();
				//itemsChildTop_[0]->moveBy(10, 10);
				//itemsChildTop_[2]->setRotation(0);
				//itemsChildTop_[0]->setScale(1);
				//itemsChildTop_[0]->setPos(300, 300);

				_x += 10;
				_y += 10;
				if (_x > 400) _x = 0;
				if (_y > 400) _y = 0;
				//itemsChildTop_[0]->setPos(_x, _y);
				itemsChild_[0]->setPos(_x, _y);

				//_carriageItem->setPos(10, 10);
				//itemsChild_[0]->setPos(0, 0);

				//QList<QGraphicsRectItem *> items123_ = scene_->findChildren<QGraphicsRectItem*>();
				//QGraphicsRectItem * item123_ = _chart->scene()->findChild<QGraphicsRectItem*>();
				//if (item123_) {
				//	item123_->setPos(10, 10);
				//}
				//else {
				//	int i(0);
				//}
				//itemsChildTop_[0]->setPos(10, 10);
				int i(0);
			}
			else {
				int i(0);
			}

			//Sleep(32);

			m_series->replace(*m_Vector);

			//if (m_bSkUpdated)
			//{
			//	m_SkipedSeries->replace(*m_SkipedVector);
			//	m_bSkUpdated = false;
			//}

			//if (m_bPeriodUpdated)
			//{
			//	m_PeriodSeries->replace(*m_PeriodVector);
			//	m_bPeriodUpdated = false;
			//}

			m_bUpdated = false;

			//_carriageItem->moveBy(10, 10);
		}
		else
		{
			counter = 0;
			m_Skiped++;
		}
	}

	VSyncCallback();

}

void VChart::showEvent(QShowEvent * event)
{
	QSizeF size1_ = this->size();
}

