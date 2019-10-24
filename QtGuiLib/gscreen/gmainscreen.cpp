// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
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
//#include <boost/container/vector.hpp>
//#include <boost/chrono.hpp>

//#include "gcore/controller.h"
//#include "gcore/core.h"

//#include "gmain/xyseriesiodevice.h"

#include "gscreen/gmainscreen.h"
#include "gscreen/gcallout.h"
#include "gdialog/dialogmessage.h"
#include "gdialog/dialogitemtablepanel.h"
#include "gmain/mainwindow.h"
#include "guiUnman.h"

class Controller;

QT_CHARTS_USE_NAMESPACE

const int Main::_numberTrace(24);

template< class InputIterator, class Function, class Predicate >
Function for_each_if(InputIterator first,
   InputIterator last,
   Predicate pred,
   Function f)
{
   for (; first != last; ++first)
   {
      if (pred(*first))
         f(*first);
   }

   return f;
};

void VChartView::mousePressEvent(QMouseEvent *event)
{
   QGraphicsItem *itemAt_ = this->itemAt(event->pos());

   if (itemAt_ != nullptr) {
      //if (itemAt_ == dynamic_cast<QGraphicsItem *>(_leftBottomText)) {
      //   MenuItem*item = _mainWindow->getItemRbw();
      //   QEvent _event(QEvent::MouseButtonPress);

      //   QCoreApplication::sendEvent((QObject*)(item), &_event);
      //}
      //else if (itemAt_ == dynamic_cast<QGraphicsItem *>(_rightBottomText)) {
      //   int i(0);
      //}
      //int i(0);

      for (auto item: _screenBottoms) {
         auto itObj = std::find_if(
         item.second.begin(), item.second.end(),
            [itemAt_](gsa::t::IScreenItem* itemScreen_) {
               if (dynamic_cast<ScreenTextItem *>(itemScreen_) != nullptr) {
                  return dynamic_cast<QGraphicsItem *>(itemScreen_) == itemAt_;
               }
               else if (dynamic_cast<DialogItemComboBox *>(itemScreen_) != nullptr) {
                  return false;
               }
               else {
                  return false;
               }
               //return itemScreen_ == itemAt_;
            }
         );
         if (itObj != item.second.end()) {
            if (dynamic_cast<ScreenTextItem *>(*itObj) != nullptr) {
               MenuItem*item = _mainWindow->getItemByName(dynamic_cast<ScreenTextItem *>(*itObj)->name());
               if (item != nullptr) {
                  QEvent _event(QEvent::MouseButtonPress);
                  QCoreApplication::sendEvent((QObject*)(item), &_event);
               }
            }
            else if (dynamic_cast<DialogItemComboBox *>(*itObj) != nullptr) {
               QString type = dynamic_cast<DialogItemComboBox *>(*itObj)->type();
               //MenuItem*item = _mainWindow->getItemByName(dynamic_cast<DialogItemComboBox *>(*itObj)->name());
               //if (item != nullptr) {
               //   QEvent _event(QEvent::MouseButtonPress);
               //   QCoreApplication::sendEvent((QObject*)(item), &_event);
               //}
            }
         }
         else {
            int i(0);
         }
      }
      //auto itObj = std::find_if(
      //   _screenBottoms.begin(), _screenBottoms.end(),
      //   [itemAt_](QGraphicsItem* p) { return p == itemAt_; }
      //);
      //if (itObj != _screenBottoms.end()) {
      //   if ((*itObj)->name() == QString("RBW")) {
      //      MenuItem*item = _mainWindow->getItemRbw();
      //      QEvent _event(QEvent::MouseButtonPress);

      //      QCoreApplication::sendEvent((QObject*)(item), &_event);
      //   }
      //}
      //else {
      //   int i(0);
      //}

   }

   int i(0);
}

ScreenTextItem::ScreenTextItem(QGraphicsItem *parent)
#ifdef HTML_TEXT 
   : QGraphicsTextItem(parent)
#else 
   : QGraphicsSimpleTextItem(parent)
#endif 
   , _name(QString(""))
   , _index(0)
   , _visible(false)
{
   QGraphicsItem *item1 = nullptr;
   QAbstractGraphicsShapeItem * item2 = nullptr;
   QGraphicsSimpleTextItem * item3 = nullptr;
}

ScreenTextItem::~ScreenTextItem()
{
   ;
}

void ScreenTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   int i(0);
}

PowerSpanSeries::PowerSpanSeries(QObject *parent)
   : QLineSeries(parent)
{
   ;
}

PowerSpanSeries::~PowerSpanSeries()
{
   ;
}

MainScreen::MainScreen(QWidget *parent, QWidget *appWidget)
   : QWidget(parent)
   , m_values(nullptr)
   , _exit(false)
   , _chart(nullptr)
   , _chartView(nullptr)
   , _axisLog(false)
   , _axisX(nullptr)
   , _axisY(nullptr)
   , _axisLogX(nullptr)
   , _axisLogY(nullptr)
   , _axisActiveX(nullptr)
   , _axisActiveY(nullptr)
   //, _carrigeSeries(nullptr)
   //, _markerSeries(nullptr)
   //, _series(nullptr)
   //, _vector(nullptr)
   //, m_series(nullptr)
   //, m_Vector(nullptr)
   , m_Skiped(0)
   , m_Position(0)
   , m_Blinker(0)
   , _chartWidth(0)
   , _plotWidth(0)
   , _chartViewHeight(0)
   , _offsetIndexMarker(7)
   //, _numberTrace(24)
   //, _numberMarker(6)
   , _xmin(0.0)
   , _xmax(0.0)
   , _ymin(0.0)
   , _ymax(0.0)
   , _yminLinear(0.0)
   , _ymaxLinear1(0.0)
   , _leftBottomText(nullptr)
   , _rightBottomText(nullptr)
{
   //m_Period = 16666;

   DWORD id = GetCurrentThreadId();

   //Main::MainWindow *_mainWindow(nullptr);
   _parentWindow = (Main::MainWindow *)parent;
   _appWidget = (Main::MainWindow *)appWidget;

   //connect(this, SIGNAL(signalSetMarker(int, QString, QColor)), _parentWindow, SLOT(slotSetMarker(int, QString, QColor))); //, Qt::QueuedConnection);
   //connect(this, SIGNAL(signalMessageBox(wchar_t*, wchar_t*)), _parentWindow, SLOT(slotMessageBox(wchar_t*, wchar_t*)), Qt::QueuedConnection);
   connect(this, SIGNAL(signalSetMarker(int, QString, QColor)), appWidget, SLOT(slotSetMarker(int, QString, QColor))); //, Qt::QueuedConnection);
   connect(this, SIGNAL(signalMessageBox(wchar_t*, wchar_t*)), appWidget, SLOT(slotMessageBox(wchar_t*, wchar_t*)), Qt::QueuedConnection);

   connect(this, SIGNAL(signalVrangeChangedX(qreal, qreal, bool)), this, SLOT(vrangeChangedX(qreal, qreal, bool)), Qt::QueuedConnection);
   connect(this, SIGNAL(signalVrangeChangedY(qreal, qreal, bool)), this, SLOT(vrangeChangedY(qreal, qreal, bool)), Qt::QueuedConnection);

   connect(this, SIGNAL(signalPutCurrentData(int, int, int)), this, SLOT(slotPutCurrentData(int, int, int)), Qt::QueuedConnection);
   connect(this, SIGNAL(signalRestyle(int)), this, SLOT(slotRestyle(int)), Qt::QueuedConnection);

   this->setAttribute(Qt::WA_AcceptTouchEvents);

   m_CurrentStyle.XAxisName = new wchar_t[1];
   m_CurrentStyle.XAxisUnit = new wchar_t[1];
   m_CurrentStyle.YAxisName = new wchar_t[1];
   m_CurrentStyle.YAxisUnit = new wchar_t[1];

   m_CurrentStyle.XAxisName[0] = 0;
   m_CurrentStyle.XAxisUnit[0] = 0;
   m_CurrentStyle.YAxisName[0] = 0;
   m_CurrentStyle.YAxisUnit[0] = 0;

   for (auto item : _screenBottoms) {
      for (int i = 0; i < item.second.size(); i++) {
         item.second[i] = nullptr;
      }
   }
   //for (auto item : _screenComboBoxes) {
   //   for (int i = 0; i < item.second.size(); i++) {
   //      item.second[i] = nullptr;
   //   }
   //}

   //gsa::t::IScreenItem *_iscreenItemText = _screenItemText;
   //gsa::t::IScreenItem *_iscreenItemCombo = _screenItemCombo;
   //QString typeText = dynamic_cast<ScreenTextItem *>(_iscreenItemText)->type();
   //ScreenTextItem *_screenItemCombo2 = dynamic_cast<ScreenTextItem *>(_iscreenItemCombo);

   int i(0);
}

MainScreen::~MainScreen()
{
   //QMap<int, QLineSeries *>::iterator it1 = _arrayseries.begin();
   QMap<int, QAbstractSeries *>::iterator it1 = _arrayseries.begin();
   while (it1 != _arrayseries.end() ) {
      delete (*it1);
      ++it1;
   }

   //van_2019_01_25
   //delete _areaSeries;

   //QMap<int, QVector <QPointF> *>::iterator it2 = _vectors.begin();
   //while (it2 != _vectors.end()) {
   //   delete (*it2);
   //   ++it2;
   //}
}

//void MainScreen::setMenuPages(MenuPage *menuPages[])
//{
//   ;
//}

void MainScreen::callDialog(void)
{
   //auto serie = qobject_cast<QLineSeries *>(sender());
   //QPen p = serie->pen();
   //p.setWidth(p.width() == 1 ? 5 : 1);
   //serie->setPen(p);

   //auto serie = qobject_cast<QLineSeries *>(sender());
   //if (qobject_cast<QObject *>(_rightBottomText) == sender()) {
   //   ;
   //}

   int i(0);

}

//bool MainScreen::SetPosition(ScreenTextItem *screenTextItem, int index, const gsa::t::GuiLocation &guiLocation, qreal &x, qreal &y)
bool MainScreen::SetPosition(gsa::t::IScreenItem *screenTextItem, int index, qreal &x, qreal &y, qreal &width, qreal &height)
{
   bool ret_(true);
   qreal y_offset(0.0);
   QRectF plotRect_(_chart->plotArea());
   //QRectF itemRect_(screenTextItem->boundingRect());
   QRectF itemRect_;
   gsa::t::GuiLocation &guiLocation( screenTextItem->location() );
   QPoint point_ = _chartView->pos();
   QRect rect_ = _chartView->geometry();

   if (dynamic_cast<ScreenTextItem *>(screenTextItem) != nullptr) {
      itemRect_ = dynamic_cast<ScreenTextItem *>(screenTextItem)->boundingRect();
      y_offset = plotRect_.y() / 8;
   }
   else if (dynamic_cast<DialogItemComboBox *>(screenTextItem) != nullptr) {
      itemRect_.setHeight(dynamic_cast<DialogItemComboBox *>(screenTextItem)->height());
      itemRect_.setWidth(dynamic_cast<DialogItemComboBox *>(screenTextItem)->width());
      int i(0);
   }
   else if (dynamic_cast<DialogItemTablePanel *>(screenTextItem) != nullptr) {
      itemRect_.setHeight(dynamic_cast<DialogItemTablePanel *>(screenTextItem)->height());
      itemRect_.setWidth(dynamic_cast<DialogItemTablePanel *>(screenTextItem)->width());
      guiLocation.horizontal = gsa::t::HorizontalType::undef;
      guiLocation.vertical = gsa::t::VerticalType::undef;
      //x = rect_.x(); // (plotRect_.x());
      //y = rect_.y(); // (plotRect_.y());
      //width = rect_.width(); // plotRect_.width();
      //height = rect_.height(); //plotRect_.height();
      x = _centralRect.x(); // (plotRect_.x());
      y = _centralRect.y(); // (plotRect_.y());
      width = _centralRect.width(); // plotRect_.width();
      height = _centralRect.height(); //plotRect_.height();
      int i(0);
   }

   switch (guiLocation.horizontal)
   {
   case gsa::t::HorizontalType::left:
      x = (plotRect_.x());
      break;
   case gsa::t::HorizontalType::middle:
      x = (plotRect_.x() + plotRect_.width()/2 - itemRect_.width()/2);
      break;
   case gsa::t::HorizontalType::right:
      x = (plotRect_.x() + plotRect_.width() - itemRect_.width());
      break;
   case gsa::t::HorizontalType::undef:
      //x = 0; // (plotRect_.x());
      break;
   }

   switch (guiLocation.vertical)
   {
   case gsa::t::VerticalType::top:
   {
      if (guiLocation.horizontal == gsa::t::HorizontalType::middle) {
         if (index == 0) {
            //y = plotRect_.y() / 8 + index * itemRect_.height();
            y = y_offset + index * itemRect_.height();
         }
         else {
            ret_ = false;
         }
      }
      else {
         //y = plotRect_.y() / 8 + index * itemRect_.height();
         y = y_offset + index * itemRect_.height();
      }
      break;
   }
   case gsa::t::VerticalType::bottom:
   {
      if (guiLocation.horizontal == gsa::t::HorizontalType::middle) {
         if (index == 0) {
            y = plotRect_.y() + plotRect_.height() + plotRect_.height() / 28 + (index + 1)* itemRect_.height();
         } 
         else {
            ret_ = false;
         }
      }
      else {
         y = plotRect_.y() + plotRect_.height() + plotRect_.height() / 28 + index * itemRect_.height();
      }
      break;
   }
   case gsa::t::VerticalType::undef:
   {
      //y = plotRect_.y();
      break;
   }
   }

   return ret_;
}

void MainScreen::changeData(int index, double value, wchar_t* unit) 
{ 
   for (auto item : _screenBottoms) 
   { 
      auto itObj = std::find_if( 
         item.second.begin(), item.second.end(), 
         [index](gsa::t::IScreenItem *p) { 
            if (p == nullptr) return false; 
            else return p->index() == index; 
         } 
      ); 

      if (itObj != item.second.end()) 
      { 
         if (dynamic_cast<ScreenTextItem *>(*itObj) != nullptr) { 
         } 
         else if (dynamic_cast<DialogItemComboBox *>(*itObj) != nullptr) { 
         } 

         //(*itObj)->setText(QString("Center 1 GHz\n%1 %2 %3 ").arg((*itObj)->name()).arg(value).arg(QString::fromWCharArray(unit)));
         //(*itObj)->setText(QString("%1 %2 %3 ").arg((*itObj)->name()).arg((long long)value).arg(QString::fromWCharArray(unit)));

         if (dynamic_cast<ScreenTextItem *>(*itObj) != nullptr) {
#ifdef HTML_TEXT

            gsa::t::Theme *_theme(g_Parameter._theme);
            std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
            std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
            std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
            std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

            gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
            gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

            for (auto &font : _theme->themeFonts) {
               if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
                  switch (_fontindexes[std::wstring(font.description)])
                  {
                  case gsa::t::FontIndex::PanelControl: font_ = font; break;
                  default: break;
                  }
               }
            }
            for (auto &item : _theme->themeItems) {
               if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                  switch (_colorindexes[std::wstring(item.description)])
                  {
                  case gsa::t::ColorIndex::PanelControl: item_ = item; break;
                  default: break;
                  }
               }
            }

            int r, g, b;
            _appWidget->GetRgb(item_.value, r, g, b);
            QColor cbackground(r, g, b);
            _appWidget->GetRgb(font_.color, r, g, b);
            QColor cfont(r, g, b);

            dynamic_cast<ScreenTextItem *>(*itObj)->setDefaultTextColor(cfont);

            if (dynamic_cast<ScreenTextItem *>(*itObj)->gsaVisible()) {
               dynamic_cast<ScreenTextItem *>(*itObj)->setPlainText(QString(""));
               QString value_;
               gsa::controller->Double2String(value_, value);
               //dynamic_cast<ScreenTextItem *>(*itObj)->setPlainText(QString("%1 %2 %3 ").arg(dynamic_cast<ScreenTextItem *>(*itObj)->name()).arg(value_).arg(QString::fromWCharArray(unit)));
               QString textNew(QString(
                  "<!DOCTYPE html>"
                  "<html>"
                  "<body>"
                  //"<p1 style=\"font-size:%1px; background-color: #ff0000; \">%2 %3 %4 </p1>"
                  //"<p1 style=\"font-size:%1px\">%2 %3 %4 </p1>"
                  //"<p1 style=\"font-size:%1px; background-color: RGB(%2, %3, %4); \">%5 %6 %7 </p1>"
                  //"<p1 style=\"font-size:%1px; background-color: #%2%3%4; \">%5 %6 %7 </p1>"
                  "<p1 style=\"height:170px; font-size:%1px; background-color: #%2%3%4; \">%5 %6 %7 </p1>"
                  "</body>"
                  "</html>"
               ).arg((int32_t)font_.size).arg(cbackground.red(), 2, 16, QChar('0')).arg(cbackground.green(), 2, 16, QChar('0')).arg(cbackground.blue(), 2, 16, QChar('0')).
                  arg(dynamic_cast<ScreenTextItem *>(*itObj)->name()).arg(value_).arg(QString::fromWCharArray(unit)) );
               dynamic_cast<ScreenTextItem *>(*itObj)->setHtml(textNew);
            }
            else {
               dynamic_cast<ScreenTextItem *>(*itObj)->setPlainText(QString(""));
            }
#else
            if (dynamic_cast<ScreenTextItem *>(*itObj)->gsaVisible()) {
               dynamic_cast<ScreenTextItem *>(*itObj)->setText(QString(""));
               QString strValue;
               gsa::controller->Double2String(strValue, value);
               dynamic_cast<ScreenTextItem *>(*itObj)->setText(QString("%1 %2 %3 ").arg(dynamic_cast<ScreenTextItem *>(*itObj)->name()).arg(strValue).arg(QString::fromWCharArray(unit)));
            }
            else {
               dynamic_cast<ScreenTextItem *>(*itObj)->setText(QString(""));
            }
#endif
         }
         else if (dynamic_cast<DialogItemComboBox *>(*itObj) != nullptr) {
            //if (dynamic_cast<DialogItemComboBox *>(*itObj)->gsaVisible()) {
            //   dynamic_cast<DialogItemComboBox *>(*itObj)->setText(QString(""));
            //   QString strValue;
            //   gsa::controller->Double2String(strValue, value);
            //   dynamic_cast<DialogItemComboBox *>(*itObj)->setText(QString("%1 %2 %3 ").arg(dynamic_cast<DialogItemComboBox *>(*itObj)->name()).arg(strValue).arg(QString::fromWCharArray(unit)));
            //}
            //else {
            //   dynamic_cast<DialogItemComboBox *>(*itObj)->setText(QString(""));
            //}
            gsa::t::Theme *_theme(g_Parameter._theme);
            std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
            std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
            std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
            std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

            gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
            gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

            for (auto &font : _theme->themeFonts) {
               if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
                  switch (_fontindexes[std::wstring(font.description)])
                  {
                  case gsa::t::FontIndex::ControlDropDownPanel: font_ = font; break;
                  default: break;
                  }
               }
            }
            for (auto &item : _theme->themeItems) {
               if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                  switch (_colorindexes[std::wstring(item.description)])
                  {
                  case gsa::t::ColorIndex::ControlDropDownPanel: item_ = item; break;
                  default: break;
                  }
               }
            }

            int r, g, b;
            _appWidget->GetRgb(item_.value, r, g, b);
            QColor cbackground(r, g, b);
            _appWidget->GetRgb(font_.color, r, g, b);
            QColor cfont(r, g, b);

            //dynamic_cast<ScreenTextItem *>(*itObj)->setDefaultTextColor(cfont);

            dynamic_cast<DialogItemComboBox *>(*itObj)->setStyleSheet(QString("%1 "
               "QWidget { " //"QComboBox { " 
               "background-color: rgb(%2, %3, %4); "
               "color: rgb(%5, %6, %7); "
               "} "
            ).arg(dynamic_cast<DialogItemComboBox *>(*itObj)->styleSheet()).arg(cbackground.red()).arg(cbackground.green()).arg(cbackground.blue()).
               arg(cfont.red()).arg(cfont.green()).arg(cfont.blue())
            );

         }
      }
      else {
      }
   }
   //for (auto item : _screenComboBoxes) 
   //{
   //   auto itObj = std::find_if(
   //      item.second.begin(), item.second.end(),
   //      [index](ScreenTextItem *p) {
   //         if (p == nullptr) return false;
   //         else return p->index() == index;
   //      }
   //   );
   //   if (itObj != item.second.end()) {
   //      //if ((*itObj)->gsaVisible()) {
   //      //   //(*itObj)->setText(QString(""));
   //      //   //QString strValue;
   //      //   //gsa::controller->Double2String(strValue, value);
   //      //   //(*itObj)->setText(QString("%1 %2 %3 ").arg((*itObj)->name()).arg(strValue).arg(QString::fromWCharArray(unit)));
   //      //}
   //      //else {
   //      //   //(*itObj)->setText(QString(""));
   //      //}
   //   }
   //}

   //auto itObj = std::find_if(
   //   _screenBottoms.begin(), _screenBottoms.end(),
   //   [item](ScreenTextItem *p) { 
   //      if (p == nullptr) return false; 
   //      else return p->index() == item; 
   //   }
   //);
   //if (itObj != _screenBottoms.end()) {
   //   if ((*itObj)->name() == QString("RBW")) {
   //      //(*itObj)->setText(QString("Center 1 GHz\n%1 %2 %3 ").arg((*itObj)->name()).arg(value).arg(QString::fromWCharArray(unit)));
   //   }
   //}
   //else {
   //}
   ////int i(0);
}

//void MainScreen::putTheme(gsa::t::Theme *_theme)
//{
//   for (auto &font: _theme->themeFonts) {
//      font.description;
//      ui->
//   }
//   for (auto &item : _theme->themeItems) {
//      switch (item.type)
//      {
//      case 0:
//         break;
//      case 1:
//         break;
//      case 2:
//         break;
//      default:
//         break;
//      }
//   }
//}

void MainScreen::OpenItem(ScreenTextItem *item)
{
   //if (item == nullptr)
   //{
   //   ;
   //}
   //else {
   //   Qt::WindowType windowType_ = _chart->windowType();
   //   VChart chart_;
   //   QChart chart2_;
   //   QChartView chartView_;

   //   QGraphicsScene *graphicsScene = item->scene();

   //   QGraphicsItem *graphicsItem1 = item->parentItem();
   //   QGraphicsItem *graphicsItem2 = item->topLevelItem();
   //   QGraphicsObject *graphicsObject = item->parentObject();
   //   QGraphicsWidget *graphicsWidget1 = item->parentWidget();
   //   QGraphicsWidget *graphicsWidget2 = item->topLevelWidget();
   //   QGraphicsWidget *graphicsWidget3 = item->window();
   //   QGraphicsItem *graphicsItem3 = item->panel();
   //}

   ////QDialog *dialog = new QDialog(_parentWindow);
   ////_dialog = new QDialog(_parentWindow);
   //_dialog = new DialogItemComboBox(_parentWindow);
   //_dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint); //Qt::WindowStaysOnTopHint
   //_dialog->setWindowModality(Qt::ApplicationModal); //NonModal, //WindowModal, 
   //_dialog->move(100, 100);
   ////_dialog->resize(400, 300);
   ////_dialog->setVisible(true);
   ////dialog->exec();
   //_dialog->show();
   ////_dialog->hide();
   ////_dialog->open();
   ////QPoint point(100, 100);
   ////_dialog->mapToParent(point);

   ////QPushButton *pushButton = new QPushButton(_dialog);
   //////QPushButton *pushButton = new QPushButton(graphicsItem1);
   ////pushButton->setObjectName(QStringLiteral("pushButton"));
   //////pushButton->setText(QApplication::translate("MainWindow", QString::fromWCharArray(screenPad->items[i].type).toStdString().c_str(), Q_NULLPTR));
   ////pushButton->setText(QApplication::translate("MainWindow", "Test", Q_NULLPTR));
}

void MainScreen::fillComboBox(gsa::t::GuiScreenPad *screenPad, int index)
{
   qreal x_;
   qreal y_;
   qreal width_;
   qreal height_;

   if (_screenBottoms.find(screenPad) == _screenBottoms.end())
   {
      std::array<gsa::t::IScreenItem *, 16> arr;
      for (size_t i = 0; i < arr.size(); i++) arr[i] = nullptr;
      _screenBottoms[screenPad] = arr;
   }

   if (index >= _screenBottoms[screenPad].size())
      return;

   fillTablePanel(_parentWindow, g_Parameter._tablePanel, 0, nullptr);

   DialogItemComboBox *widdgetItem_(nullptr);

   if (_screenBottoms[screenPad][index] == nullptr) 
   {
      QThread *thread = QThread::currentThread();

      widdgetItem_ = new DialogItemComboBox(_parentWindow);
      //widdgetItem_ = new DialogItemComboBox(_appWidget);
      widdgetItem_->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint); //Qt::WindowStaysOnTopHint
      //widdgetItem_->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //don't work
      widdgetItem_->setWindowModality(Qt::ApplicationModal); //NonModal, //WindowModal, 

      _screenBottoms[screenPad][index] = widdgetItem_;

      gsa::t::Theme *_theme(g_Parameter._theme);
      std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
      std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
      std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
      std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::ControlDropDownPanel: font_ = font; break;
            default: break;
            }
         }
      }
      for (auto &item : _theme->themeItems) {
         if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
            switch (_colorindexes[std::wstring(item.description)])
            {
            case gsa::t::ColorIndex::ControlDropDownPanel: item_ = item; break;
            default: break;
            }
         }
      }

      int r, g, b;
      _appWidget->GetRgb(item_.value, r, g, b);
      QColor cbackground(r, g, b);
      _appWidget->GetRgb(font_.color, r, g, b);
      QColor cfont(r, g, b);

      widdgetItem_->setStyleSheet(QString("%1 "
         "QWidget { " //"QComboBox { " 
         "background-color: rgb(%2, %3, %4); "
         "color: rgb(%5, %6, %7); "
         "} "
      //).arg(widdgetItem_->styleSheet()).arg(127).arg(127).arg(0)
      ).arg(widdgetItem_->styleSheet()).arg(cbackground.red()).arg(cbackground.green()).arg(cbackground.blue()).
         arg(cfont.red()).arg(cfont.green()).arg(cfont.blue())
      );
   }
   else {
      if (dynamic_cast<ScreenTextItem *>(_screenBottoms[screenPad][index]) == nullptr) {
         return;
      }
   }

   widdgetItem_ = dynamic_cast<DialogItemComboBox *>(_screenBottoms[screenPad][index]);

   widdgetItem_->setLocation(screenPad->items[index].guiLocation);
   SetPosition(widdgetItem_, index, x_, y_, width_, height_);

   int itemIndex(screenPad->items[index].itemIndex);
   widdgetItem_->setItemIndex(screenPad->items[index].itemIndex);

   //widdgetItem_->setText(QString(""));
   widdgetItem_->setLocation(screenPad->items[index].guiLocation);
   widdgetItem_->setGsaVisible(SetPosition(widdgetItem_, index, x_, y_, width_, height_));
   if (widdgetItem_->gsaVisible())
   {
      QString name_ = QString::fromWCharArray(screenPad->items[index].name);
      QString unit_ = QString::fromWCharArray(screenPad->items[index].unit);

      screenPad->items[index].units[0];
      screenPad->items[index].length;
      //QStringList names_;
      _names.clear();
      for (int i = 0; i < screenPad->items[index].length; i++) {
         _names.push_back(QString::fromWCharArray(screenPad->items[index].units[i]));
      }

      widdgetItem_->setName(name_);
      widdgetItem_->setNames(_names);
      //widdgetItem_->setUnit(unit_);
      //widdgetItem_->setValue(screenPad->items[index].value);
      widdgetItem_->setIndex(screenPad->items[index].itemIndex);
      //widdgetItem_->setPos(qreal(x_), qreal(y_));
      widdgetItem_->setPosition(QPoint(x_, y_));
      //widdgetItem_->setPosition(QPoint(x_, -50));

      QString strValue;
      gsa::controller->Double2String(strValue, screenPad->items[index].value);
      //widdgetItem_->setText(QString("%1 %2 %3 ").arg(name_).arg(strValue).arg(unit_));
      //widdgetItem_->setBrush(QColor(128, 128, 128));
      widdgetItem_->setFont(QFont("lucida", 14, QFont::Bold));

      //DialogItemTablePanel *widdgetItem2_ = dialogItemTablePanel(g_Parameter._tablePanel);
      //if (widdgetItem2_ != nullptr) {
      //   dialogItemTablePanel(g_Parameter._tablePanel)->setName(name_);
      //   dialogItemTablePanel(g_Parameter._tablePanel)->setNames(_names);
      //}

      connect(this, SIGNAL(tablePanelIndexChanged(int, int)), widdgetItem_, SLOT(tablePanelIndexChangedExpd(int, int)));
   }
   else {
      //widdgetItem_->setText(QString(""));
   }


   ////std::map<gsa::t::GuiScreenPad *, std::array<DialogItemComboBox *, 16> > _screenComboBoxes;
   //if (_screenBottoms[screenPad][index] == nullptr)
   //{
   //   ;
   //}
   //else {
   //   Qt::WindowType windowType_ = _chart->windowType();
   //   VChart chart_;
   //   QChart chart2_;
   //   QChartView chartView_;

   //   QGraphicsScene *graphicsScene = _screenBottoms[screenPad][index]->scene();

   //   QGraphicsItem *graphicsItem1 = _screenBottoms[screenPad][index]->parentItem();
   //   QGraphicsItem *graphicsItem2 = _screenBottoms[screenPad][index]->topLevelItem();
   //   QGraphicsObject *graphicsObject = _screenBottoms[screenPad][index]->parentObject();
   //   QGraphicsWidget *graphicsWidget1 = _screenBottoms[screenPad][index]->parentWidget();
   //   QGraphicsWidget *graphicsWidget2 = _screenBottoms[screenPad][index]->topLevelWidget();
   //   QGraphicsWidget *graphicsWidget3 = _screenBottoms[screenPad][index]->window();
   //   QGraphicsItem *graphicsItem3 = _screenBottoms[screenPad][index]->panel();
   //}

   ////QDialog *dialog = new QDialog(_parentWindow);
   ////_dialog = new QDialog(_parentWindow);
   //_dialog = new DialogItemComboBox(_parentWindow);
   //_dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint); //Qt::WindowStaysOnTopHint
   //_dialog->setWindowModality(Qt::ApplicationModal); //NonModal, //WindowModal, 
   //_dialog->move(100, 100);
   ////_dialog->resize(400, 300);
   ////_dialog->setVisible(true);
   ////dialog->exec();
   //_dialog->show();
   ////_dialog->hide();
   ////_dialog->open();
   ////QPoint point(100, 100);
   ////_dialog->mapToParent(point);

   ////QPushButton *pushButton = new QPushButton(_dialog);
   //////QPushButton *pushButton = new QPushButton(graphicsItem1);
   ////pushButton->setObjectName(QStringLiteral("pushButton"));
   //////pushButton->setText(QApplication::translate("MainWindow", QString::fromWCharArray(screenPad->items[i].type).toStdString().c_str(), Q_NULLPTR));
   ////pushButton->setText(QApplication::translate("MainWindow", "Test", Q_NULLPTR));
}

void MainScreen::fillEditBox(gsa::t::GuiScreenPad *screenPad, int index)
{
   qreal x_;
   qreal y_;
   qreal width_;
   qreal height_;

   //ScreenTextItem *itObj;

   //auto screenItem = std::find_if(
   //   _screenBottoms.begin(), _screenBottoms.end(),
   //   [screenPad](gsa::t::GuiScreenPad *pad) {
   //      if (pad == screenPad) return true;
   //      else return false;
   //   }
   //);
   //if (screenItem == _screenBottoms.end()) {
   //   std::array<gsa::t::IScreenItem *, 16> arr;
   //   _screenBottoms[screenPad] = arr;
   //   screenItem = _screenBottoms[screenPad];
   //}
   //else {
   //}

   if (_screenBottoms.find(screenPad) == _screenBottoms.end())
   {
      std::array<gsa::t::IScreenItem *, 16> arr;
      for (size_t i = 0; i < arr.size(); i++) arr[i] = nullptr;
      _screenBottoms[screenPad] = arr;
   }

   if (index >= _screenBottoms[screenPad].size())
      return;

   if (_screenBottoms[screenPad][index] == nullptr) {
      _screenBottoms[screenPad][index] = new ScreenTextItem(_chart);
   }
   else {
      if (dynamic_cast<ScreenTextItem *>(_screenBottoms[screenPad][index]) == nullptr) {
         return;
      }
   }

   //auto itObj = std::find_if(
   //   _screenBottoms[screenPad].begin(), _screenBottoms[screenPad].end(),
   //   [index](gsa::t::IScreenItem *item) {
   //      if (item == nullptr) {
   //         ;
   //      }
   //      if (dynamic_cast<ScreenTextItem *>(item) != nullptr) {
   //         return dynamic_cast<ScreenTextItem *>(item)->index() == index;
   //      }
   //      else if (dynamic_cast<DialogItemComboBox *>(item) != nullptr) {
   //         return dynamic_cast<DialogItemComboBox *>(item)->index() == index;
   //      }
   //   }
   //);

   //if (itObj == (*screenItem).second.end()) {
   //   return;
   //}
   //else {
   //   if (dynamic_cast<ScreenTextItem *>(*itObj) != nullptr) {
   //      dynamic_cast<ScreenTextItem *>(*itObj)->index();
   //   }
   //   else if (dynamic_cast<DialogItemComboBox *>(*itObj) != nullptr) {
   //      dynamic_cast<DialogItemComboBox *>(*itObj)->index();
   //   }

   //   if ((*itObj) == nullptr) {
   //      (*itObj) = new ScreenTextItem(_chart);
   //   }
   //}

   //if (dynamic_cast<ScreenTextItem *>(*itObj) != nullptr) {
   //}
   //else if (dynamic_cast<DialogItemComboBox *>(*itObj) != nullptr) {
   //}

   //if (_screenBottoms[screenPad][index] == nullptr) {
   //   _screenBottoms[screenPad][index] = new ScreenTextItem(_chart);
   //}

   ScreenTextItem *textItem_(dynamic_cast<ScreenTextItem *>(_screenBottoms[screenPad][index]));

#ifdef HTML_TEXT
   textItem_->setPlainText(QString(""));
#else
   textItem_->setText(QString(""));
#endif
   textItem_->setLocation(screenPad->items[index].guiLocation);
   textItem_->setGsaVisible(SetPosition(textItem_, index, x_, y_, width_, height_));
   if (textItem_->gsaVisible())
   {
      QString name_ = QString::fromWCharArray(screenPad->items[index].name);
      QString unit_ = QString::fromWCharArray(screenPad->items[index].unit);
      //const wchar_t *ch = name_.toStdWString().c_str();

      textItem_->setName(name_);
      textItem_->setUnit(unit_);
      textItem_->setValue(screenPad->items[index].value);
      textItem_->setIndex(screenPad->items[index].itemIndex);
      //textItem_->setPos(qreal(x_), qreal(y_));
      textItem_->setPosition(QPoint(x_, y_));

      QString value_;
      gsa::controller->Double2String(value_, screenPad->items[index].value);
      //textItem_->setText(QString("%1 %2 %3 ").arg(_name).arg((long long)screenPad->items[index].value).arg(_unit));
#ifdef HTML_TEXT
      //textItem_->setPlainText(QString("%1 %2 %3 ").arg(name_).arg(value_).arg(unit_));
      //textItem_->setDefaultTextColor(QColor(128, 128, 128));
      //textItem_->setFont(QFont("lucida", 24, QFont::Bold));
#else
      textItem_->setText(QString("%1 %2 %3 ").arg(name_).arg(value_).arg(unit_));
      textItem_->setBrush(QColor(128, 128, 128));
      textItem_->setFont(QFont("lucida", 14, QFont::Bold));
#endif

      //return;

      gsa::t::Theme *_theme(g_Parameter._theme);
      std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
      std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
      std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
      std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::PanelControl: font_ = font; break;
            default: break;
            }
         }
      }
      for (auto &item : _theme->themeItems) {
         if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
            switch (_colorindexes[std::wstring(item.description)])
            {
            case gsa::t::ColorIndex::PanelControl: item_ = item; break; 
            default: break; 
            } 
         } 
      } 

      int r, g, b;
      _appWidget->GetRgb(item_.value, r, g, b);
      QColor cbackground(r, g, b);
      _appWidget->GetRgb(font_.color, r, g, b);
      QColor cfont(r, g, b);

      textItem_->setDefaultTextColor(cfont);

      //RGB(249, 201, 16)
      QString textNew(QString(
         "<!DOCTYPE html>" 
         "<html>" 
         "<body>" 
         //"<p1 style=\"font-size:%1px; background-color: #ff0000; \">%2 %3 %4 </p1>" 
         //"<p1 style=\"font-size:%1px\">%2 %3 %4 </p1>" 
         //"<p1 style=\"font-size:%1px; background-color: RGB(%2, %3, %4); \">%5 %6 %7 </p1>" 
         //"<p1 style=\"font-size:%1px; background-color: rgb(0, 0, 255); \">%2 %3 %4 </p1>" 
         //"<p1 style=\"font-size:%1px; background-color: #%2%3%4; \">%5 %6 %7 </p1>"
         "<p1 style=\"height:170px; font-size:%1px; background-color: #%2%3%4; \">%5 %6 %7 </p1>"
         "</body>"
         "</html>" 
      ).arg((int32_t)font_.size).arg(cbackground.red(), 2, 16, QChar('0')).arg(cbackground.green(), 2, 16, QChar('0')).arg(cbackground.blue(), 2, 16, QChar('0')).
         arg(name_).arg(value_).arg(unit_));
      textItem_->setHtml(textNew);
      //textItem_->setHtml(QString("%1 %2 %3 ").arg(name_).arg(value_).arg(unit_));
   }
   else {
      //textItem_->setText(QString(""));
   }
}

DialogItemTablePanel *MainScreen::dialogItemTablePanel(gsa::t::Table *tablePanel)
{
   return dynamic_cast<DialogItemTablePanel *>(_screenTablePanels[tablePanel]);
}

void MainScreen::tablePanelIndexChangedExpd(int index, int flag)
{
   index = index;

   //double value((double)index);
   //wcscpy(_text, L"TRUE");
   //g_Parameter._SetValue(_itemIndex, value, _text, index);

   emit tablePanelIndexChanged(index, flag);
}

QWidget *MainScreen::fillTablePanel(QWidget *parent, gsa::t::Table *tablePanel, int index, QGridLayout *gridLayout)
{ 
   qreal x_; 
   qreal y_; 
   qreal width_; 
   qreal height_; 

   _tablePanel = tablePanel;

   QString str(QString("INFO0077 %1 _tablePanel = %2 _screenTablePanels=%3 ").arg(__FUNCTION__).arg((long long)tablePanel, 0, 16).arg(_screenTablePanels.size()));
   qInfo(str.toStdString().c_str());

   if (tablePanel == nullptr) return nullptr;

   if (_screenTablePanels.find(tablePanel) == _screenTablePanels.end())
   {
      //std::array<gsa::t::IScreenItem *, 16> arr;
      //for (size_t i = 0; i < arr.size(); i++) arr[i] = nullptr;
      //_screenTablePanels[tablePanel] = index;
   }

   //if (index >= _screenTablePanels[tablePanel].size())
   //   return;

   //DialogItemComboBox *widdgetItem_(nullptr);
   DialogItemTablePanel *widdgetItem_(nullptr);

   if (_screenTablePanels.find(tablePanel) == _screenTablePanels.end() || _screenTablePanels[tablePanel] == nullptr)
   {
      QThread *thread = QThread::currentThread();

      //widdgetItem_ = new DialogItemComboBox(_parentWindow);
      //widdgetItem_ = new DialogItemTablePanel(nullptr);
      //widdgetItem_ = new DialogItemTablePanel(_parentWindow, gridLayout, _tablePanel);
      widdgetItem_ = new DialogItemTablePanel(parent, _appWidget, gridLayout, _tablePanel);

      gsa::t::Theme *_theme(g_Parameter._theme);
      std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
      std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
      std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
      std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

      for (auto &themeItem : _theme->themeItems) {
         switch (themeItem.type)
         {
         case 0:
         {
            if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) {
               switch (_colorindexes[std::wstring(themeItem.description)])
               {
               case gsa::t::ColorIndex::DisplayArea: //Display area background 
                  item_ = themeItem;
                  break;
               default:
                  break;
               }
            }
         }
         case 1:
         {
            break;
         }
         case 2:
         {
            break;
         }
         default:
         {
            break;
         }
         }
      }

      int r2, g2, b2;
      _appWidget->GetRgb(item_.value, r2, g2, b2);
      QColor color_(r2, g2, b2);

      //if (parent != nullptr && (QWidget*)parent->parent() != nullptr ) {
      //   ((QWidget*)parent->parent())->setStyleSheet(QString("%1 " 
      //      "QWidget { " 
      //      "background-color: rgb(%1, %2, %3); " 
      //      "} " 
      //      "" 
      //   ).arg(((QWidget*)parent->parent())->styleSheet()).arg(color_.red()).arg(color_.green()).arg(color_.blue())
      //   );
      //   ((QWidget*)parent)->setStyleSheet(QString("%1 "
      //      "QWidget { "
      //      "background-color: rgb(%1, %2, %3); "
      //      "} "
      //      ""
      //   ).arg(((QWidget*)parent)->styleSheet()).arg(color_.red()).arg(color_.green()).arg(color_.blue())
      //   );
      //   ((QWidget*)widdgetItem_)->setStyleSheet(QString("%1 "
      //      "QWidget { "
      //      "background-color: rgb(%1, %2, %3); "
      //      "} "
      //      ""
      //   ).arg(((QWidget*)widdgetItem_)->styleSheet()).arg(color_.red()).arg(color_.green()).arg(color_.blue())
      //   );
      //}

      ((QWidget*)widdgetItem_)->setStyleSheet(QString(" "
         "QWidget { "
         "background-color: rgb(%1, %2, %3); "
         "} "
         ""
      ).arg(color_.red()).arg(color_.green()).arg(color_.blue())
      );

      connect(widdgetItem_, SIGNAL(tablePanelIndexChanged(int, int)), this, SLOT(tablePanelIndexChangedExpd(int, int)));

      SetPosition(widdgetItem_, index, x_, y_, width_, height_);
      QRect rect(x_, y_, width_, height_);
      QPoint point(x_, y_);
      widdgetItem_->setGeometry(rect);
      widdgetItem_->move(point);

      //widdgetItem_->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //Qt::WindowStaysOnTopHint

      //widdgetItem_->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //DON'T WORK 
      //widdgetItem_->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      //widdgetItem_->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      widdgetItem_->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint ); //work
      //widdgetItem_->setWindowFlags(Qt::Sheet | Qt::FramelessWindowHint ); //work
      //widdgetItem_->setWindowFlags(Qt::Drawer | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      //widdgetItem_->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      //widdgetItem_->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      //widdgetItem_->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      //widdgetItem_->setWindowFlags(Qt::SplashScreen | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work
      //widdgetItem_->setWindowFlags(Qt::Desktop | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //DON'T WORK 
      //widdgetItem_->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //DON'T WORK 
      //widdgetItem_->setWindowFlags(Qt::ForeignWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //DON'T WORK 
      //widdgetItem_->setWindowFlags(Qt::CoverWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //work

      //widdgetItem_->setWindowModality(Qt::WindowModal); //NonModal, //WindowModal, //ApplicationModal 
      widdgetItem_->setWindowModality(Qt::NonModal); //NonModal, //WindowModal, //ApplicationModal 

      _screenTablePanels[tablePanel] = widdgetItem_;
   }
   else {
      //if (dynamic_cast<ScreenTextItem *>(_screenTablePanels[tablePanel]) == nullptr) {
      //   return;
      //}
      gsa::t::IScreenItem *v = _screenTablePanels[tablePanel];
      v = v;
   }

   widdgetItem_ = dynamic_cast<DialogItemTablePanel *>(_screenTablePanels[tablePanel]);
   widdgetItem_->setGridLayout(gridLayout);

   QObject *objparent1 = widdgetItem_->parent();
   widdgetItem_->setVParent(parent);
   QObject *objparent2 = widdgetItem_->parent();

   //int count = tablePanel->Columns * tablePanel->Rows;
   //for (int i = 0; i < count; i++) {
   //   tablePanel->Cells[i];
   //}

   //widdgetItem_->setLocation(screenPad->items[index].guiLocation);
   SetPosition(widdgetItem_, index, x_, y_, width_, height_);

   //int itemIndex(screenPad->items[index].itemIndex);
   //widdgetItem_->setItemIndex(screenPad->items[index].itemIndex);

   if (index == 1) {
      ////widdgetItem_->setText(QString(""));
      //widdgetItem_->setLocation(screenPad->items[index].guiLocation);
      //widdgetItem_->setGsaVisible(SetPosition(widdgetItem_, index, x_, y_));

      widdgetItem_->setTablePanelData(tablePanel, x_, y_, width_, height_, index);

      //QRect rect(x_, y_, width_, height_);
      //QPoint point(x_, y_);
      //widdgetItem_->setGeometry(rect);
      //widdgetItem_->move(point);

      widdgetItem_->setGsaVisible(true);
      if (widdgetItem_->gsaVisible())
      {
         //   QString name_ = QString::fromWCharArray(screenPad->items[index].name);
         //   QString unit_ = QString::fromWCharArray(screenPad->items[index].unit);

         //   screenPad->items[index].units[0];
         //   screenPad->items[index].length;
         //   QStringList names_;
         //   for (int i = 0; i < screenPad->items[index].length; i++) {
         //      names_.push_back(QString::fromWCharArray(screenPad->items[index].units[i]));
         //   }

         //   widdgetItem_->setName(name_);
         //   widdgetItem_->setNames(names_);
         //   //widdgetItem_->setUnit(unit_);
         //   //widdgetItem_->setValue(screenPad->items[index].value);
         //   widdgetItem_->setIndex(screenPad->items[index].itemIndex);
         //   //widdgetItem_->setPos(qreal(x_), qreal(y_));
         //   widdgetItem_->setPosition(QPoint(x_, y_));

         //   QString strValue;
         //   gsa::controller->Double2String(strValue, screenPad->items[index].value);
         //   //widdgetItem_->setText(QString("%1 %2 %3 ").arg(name_).arg(strValue).arg(unit_));
         //   //widdgetItem_->setBrush(QColor(128, 128, 128));
         //   widdgetItem_->setFont(QFont("lucida", 14, QFont::Bold));

      }
      else {
         //widdgetItem_->setText(QString(""));
      }
   }
   else {
      widdgetItem_->setGsaVisible(false);
   }

   return widdgetItem_;
}

void MainScreen::createScreenPage(gsa::t::GuiScreenPad *screenPad)
{
   //qreal x_;
   //qreal y_;
   //QRectF plotArea_(_chart->plotArea());

   if (_screenBottoms.find(screenPad) == _screenBottoms.end()) {
      for (int i = 0; i < screenPad->length; i++)
      {
         //if (i < _screenBottoms[screenPad].size() && _screenBottoms[screenPad][i] == nullptr)
         //{
         QString type_ = QString::fromWCharArray(screenPad->items[i].type);
         if (type_ == QString("ComboBox")) {
            fillComboBox(screenPad, i);
            //OpenItem(_screenBottoms[screenPad][i]);
         }
         else if (type_ == QString("EditBox")) {
            fillEditBox(screenPad, i);
         }

         //_screenBottoms[screenPad][i] = new ScreenTextItem(_chart);

         //_screenBottoms[screenPad][i]->setText(QString(""));
         //_screenBottoms[screenPad][i]->setLocation(screenPad->items[i].guiLocation);
         //_screenBottoms[screenPad][i]->setGsaVisible(SetPosition(_screenBottoms[screenPad][i], i, _screenBottoms[screenPad][i]->location(), x_, y_) );
         //if (_screenBottoms[screenPad][i]->gsaVisible())
         //{
         //   QString name_ = QString::fromWCharArray(screenPad->items[i].name);
         //   QString unit_ = QString::fromWCharArray(screenPad->items[i].unit);
         //   //const wchar_t *ch = name_.toStdWString().c_str();

         //   _screenBottoms[screenPad][i]->setName(name_);
         //   _screenBottoms[screenPad][i]->setUnit(unit_);
         //   _screenBottoms[screenPad][i]->setValue(screenPad->items[i].value);
         //   _screenBottoms[screenPad][i]->setIndex(screenPad->items[i].itemIndex);
         //   _screenBottoms[screenPad][i]->setPos(qreal(x_), qreal(y_));

         //   QString strValue;
         //   gsa::controller->Double2String(strValue, screenPad->items[i].value);
         //   //_screenBottoms[screenPad][i]->setText(QString("%1 %2 %3 ").arg(_name).arg((long long)screenPad->items[i].value).arg(_unit));
         //   _screenBottoms[screenPad][i]->setText(QString("%1 %2 %3 ").arg(name_).arg(strValue).arg(unit_));
         //   _screenBottoms[screenPad][i]->setBrush(QColor(128, 128, 128));
         //   _screenBottoms[screenPad][i]->setFont(QFont("lucida", 14, QFont::Bold));

         //}
         //else {
         //   //_screenBottoms[screenPad][i]->setText(QString(""));
         //}
         //}
      }
   }
   //std::map<gsa::t::GuiScreenPad *, std::array<DialogItemComboBox *, 16> > _screenComboBoxes;

   _chartView->setScreenBottoms(_screenBottoms);

   //if (_leftBottomText == nullptr) {
   //   //screenPad->length;
   //   //_leftBottomText = new QGraphicsSimpleTextItem(_chart);
   //   _leftBottomText = new ScreenTextItem(_chart);

   //   //_leftBottomText->_location.horizontal = screenPad->items[0].guiLocation.horizontal;
   //   //_leftBottomText->_location.vertical = screenPad->items[0].guiLocation.vertical;
   //   _leftBottomText->setLocation(screenPad->items[0].guiLocation);

   //   //screenPad->items[0].value;
   //   //screenPad->items[0].unit;

   //   //_leftBottomText->setText("Center 1 GHz\nResBW 9.1000 kHz");
   //   _leftBottomText->setText(QString("Center 1 GHz\n%1 %2 %3 ").arg(QString::fromWCharArray(screenPad->items[0].name)).
   //      arg(screenPad->items[0].value).arg(QString::fromWCharArray(screenPad->items[0].unit)) );

   //   //_leftBottomText->setBrush(QColor(54, 54, 209));
   //   _leftBottomText->setBrush(QColor(128, 128, 128));
   //   _leftBottomText->setFont(QFont("lucida", 14, QFont::Bold));

   //   QRectF _leftBottomRect = _leftBottomText->boundingRect();
   //   qreal _xLeftBottom(plotArea_.x());
   //   qreal _yLeftBottom(plotArea_.y() + plotArea_.height() + plotArea_.height() / 32);

   //   qreal x_;
   //   qreal y_;
   //   //SetLocation(_leftBottomText, _leftBottomText->_location, x_, y_);
   //   SetLocation(_leftBottomText, _leftBottomText->location(), x_, y_);
   //   //_leftBottomText->setPos(qreal(_xLeftBottom), qreal(_yLeftBottom));
   //   _leftBottomText->setPos(qreal(x_), qreal(y_));

   //   //_leftBottomText->setPos(qreal(0), qreal(0));

   //   _chartView->setLeftBottomText(_leftBottomText);

   //   //connect(_leftBottomText, SIGNAL(clicked()), this, SLOT(callDialog()) );
   //   //connect(_chartView, SIGNAL(clicked()), this, SLOT(callDialog()));
   //}
   //if (_rightBottomText == nullptr) {
   //   //_rightBottomText = new QGraphicsSimpleTextItem(_chart);
   //   _rightBottomText = new ScreenTextItem(_chart);
   //   //_leftBottomText->_location.horizontal = screenPad->items[0].guiLocation.horizontal;
   //   //_leftBottomText->_location.vertical = screenPad->items[0].guiLocation.vertical;
   //   _rightBottomText->setLocation(screenPad->items[0].guiLocation);

   //   _rightBottomText->setText("Span 1 MHz\nSweep Time 14.6 ms (1001 pts)");
   //   //_rightBottomText->setBrush(QColor(54, 54, 209));
   //   _rightBottomText->setBrush(QColor(128, 128, 128));
   //   _rightBottomText->setFont(QFont("lucida", 14, QFont::Bold));

   //   QRectF _rightBottomRect = _rightBottomText->boundingRect();
   //   qreal _xRightBottom(plotArea_.x() + plotArea_.width() - _rightBottomRect.width());
   //   qreal _yRightBottom(plotArea_.y() + plotArea_.height() + plotArea_.height() / 32);
   //   _rightBottomText->setPos(qreal(_xRightBottom), qreal(_yRightBottom));

   //   //_rightBottomText->setPos(qreal(0), qreal(0));

   //   _chartView->setRightBottomText(_rightBottomText);

   //   //connect(_rightBottomText, SIGNAL(clicked()), this, SLOT(callDialog()) );
   //   connect(_chartView, SIGNAL(clicked()), this, SLOT(callDialog()));
   //}

}

QAbstractSeries *MainScreen::CreateSeries(const int &index, const MainScreen::SeriesType &type)
{
   QGraphicsSimpleTextItem *freqText(nullptr);
   QGraphicsSimpleTextItem *valueText(nullptr);

#ifdef HTML_TEXT
   QGraphicsTextItem *anyText(nullptr);
   anyText = new QGraphicsTextItem(_chart);
   _anyTextes[index] = anyText;
#else
   QGraphicsSimpleTextItem *markerText(nullptr);
   markerText = new QGraphicsSimpleTextItem(_chart);
   _markerTextes[index] = markerText;
#endif

   freqText = new QGraphicsSimpleTextItem(_chart);
   _freqTextes[index] = freqText;

   valueText = new QGraphicsSimpleTextItem(_chart);
   _valueTextes[index] = valueText;

   switch (type)
   {
   case SeriesType::line:
   {
      QLineSeries *lineSeries_(nullptr);
      lineSeries_ = new QLineSeries;

      return lineSeries_;
   }
   case SeriesType::area:
   {
      //van_2019_01_25
      QLineSeries *series0 = new QLineSeries();
      QLineSeries *series1 = new QLineSeries();

      //QAreaSeries *_areaSeries;
      //QAreaSeries *series = new QAreaSeries(series0, series1);
      QAreaSeries *areaSeries_ = new QAreaSeries(series0, series1);
      //PowerSpanSeries *areaSeries_ = new PowerSpanSeries(series0, series1);
      //_areaSeries->setName("Batman");
      //QPen pen(0x059605);
      QPen pen(QColor(0, 0, 255, 64));
      pen.setWidth(1);
      areaSeries_->setPen(pen);

      QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
      //gradient.setColorAt(0.0, 0x3cc63c);
      //gradient.setColorAt(1.0, 0x26f626);
      gradient.setColorAt(0.0, QColor(0, 0, 255, 128));
      gradient.setColorAt(1.0, QColor(0, 255, 0, 128));
      gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
      areaSeries_->setBrush(gradient);
      //_areaSeries->setBrush(QColor(0, 0, 255, 64));

      //QChart *chart = new QChart();
      //chart->addSeries(_areaSeries);
      //chart->setTitle("Simple areachart example");
      //chart->createDefaultAxes();
      //chart->axes(Qt::Horizontal).first()->setRange(0, 20);
      //chart->axes(Qt::Vertical).first()->setRange(0, 10);

      return areaSeries_;
   }
   case SeriesType::power:
   {
      PowerSpanSeries *energySeries_(nullptr);
      energySeries_ = new PowerSpanSeries();

      QLineSeries *series0 = new QLineSeries();
      QLineSeries *series1 = new QLineSeries();
      QAreaSeries *areaSeries_ = new QAreaSeries(series0, series1);

      QPen pen(QColor(0, 0, 255, 64));
      pen.setWidth(1);
      areaSeries_->setPen(pen);

      QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
      gradient.setColorAt(0.0, QColor(0, 0, 255, 128));
      gradient.setColorAt(1.0, QColor(0, 255, 0, 128));
      gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
      areaSeries_->setBrush(gradient);

      energySeries_->setAreaSeries(areaSeries_);

      return energySeries_;
   }
   }

   return nullptr;
}

void MainScreen::initArrayNew(const gsa::t::ThemeFont &font_)
{
   const uint32_t __index__(21);
   QLineSeries *m_series(nullptr);
   //QVector <QPointF> *m_Vector(nullptr);
   QGraphicsSimpleTextItem *_anyText(nullptr);
   QGraphicsSimpleTextItem *_freqText(nullptr);
   QGraphicsSimpleTextItem *_valueText(nullptr);

   _font = font_;

   if (_chart == nullptr) return;

   int index(0);
   for (index = 0; index < Main::_numberTrace; ++index)
   {
//#ifdef TEMP1

      if (index == __index__) {
         PowerSpanSeries *energySeries_ = dynamic_cast<PowerSpanSeries *>(CreateSeries(index, SeriesType::power));
         _chart->addSeries(energySeries_);
         _chart->addSeries(energySeries_->areaSeries());
         _arrayseries[index] = energySeries_;
         _updated[_arrayseries[index]] = true;
      }
      //else if (index == 20) {
      ////if (index == Main::_numberTrace - 1) {
      //   QAreaSeries *areaSeries_ = dynamic_cast<QAreaSeries *>(CreateSeries(index, SeriesType::area));
      //   _chart->addSeries(areaSeries_);
      //   _arrayseries[index] = areaSeries_;
      //   _updated[_arrayseries[index]] = true;
      //}
      else {

//#endif // TEMP1

         if (index < _arrayseries.size() ) {
            ;
         }
         QLineSeries *lineSeries_ = dynamic_cast<QLineSeries *>(CreateSeries(index, SeriesType::line));
         _chart->addSeries(lineSeries_);
         _arrayseries[index] = lineSeries_;
         //_vectors[index] = (m_Vector);

         //m_Vector = new QVector<QPointF>(gsa::t::maxPoint);
         //for (int l_N = 0; l_N < gsa::t::maxPoint; l_N++)
         //{
         //   (*m_Vector)[l_N].setX(DBL_MAX);
         //   (*m_Vector)[l_N].setY(0);
         //}

         //_anyText = new QGraphicsSimpleTextItem(_chart);
         //_anyTextes[index] = _anyText;

         //_freqText = new QGraphicsSimpleTextItem(_chart);
         //_freqTextes[index] = _freqText;

         //_valueText = new QGraphicsSimpleTextItem(_chart);
         //_valueTextes[index] = _valueText;

         _updated[_arrayseries[index]] = true;

//#ifdef TEMP1

      }

//#endif // TEMP1

   }

   //if (_leftBottomText == nullptr) {
   //   //_leftBottomText = new QGraphicsSimpleTextItem(_chart);
   //   _leftBottomText = new ScreenTextItem(_chart);

   //   _leftBottomText->setText("Center 1 GHz\nResBW 9.1000 kHz");
   //   //_leftBottomText->setBrush(QColor(54, 54, 209));
   //   _leftBottomText->setBrush(QColor(128, 128, 128));
   //   _leftBottomText->setFont(QFont("lucida", 14, QFont::Bold));
   //   _leftBottomText->setPos(qreal(0), qreal(0));
   //}
   //if (_rightBottomText == nullptr) {
   //   //_rightBottomText = new QGraphicsSimpleTextItem(_chart);
   //   _rightBottomText = new ScreenTextItem(_chart);

   //   _rightBottomText->setText("Span 1 MHz\nSweep Time 14.6 ms (1001 pts)");
   //   //_rightBottomText->setBrush(QColor(54, 54, 209));
   //   _rightBottomText->setBrush(QColor(128, 128, 128));
   //   _rightBottomText->setFont(QFont("lucida", 14, QFont::Bold));
   //   _rightBottomText->setPos(qreal(0), qreal(0));

   //   //connect(_rightBottomText, SIGNAL(clicked()), this, SLOT(callDialog()) );
   //   connect(_chartView, SIGNAL(clicked()), this, SLOT(callDialog()) );
   //}

   //_chartView->setLeftBottomText(_leftBottomText);
   //_chartView->setRightBottomText(_rightBottomText);



   //if (_carrigeSeries == nullptr) {
   //   _carrigeSeries = new QLineSeries;
   //   _chart->addSeries(_carrigeSeries);

   //   _updated[_carrigeSeries] = true;
   //}

   ////if (_markerSeries == nullptr) {
   ////   _markerSeries = new QLineSeries;
   ////   _chart->addSeries(_markerSeries);

   ////   _updated[_markerSeries] = true;
   ////}

   //for (int index = 0; index < _numberMarker; ++index)
   //{
   //   m_series = new QLineSeries;
   //   _chart->addSeries(m_series);
   //   m_Vector = new QVector<QPointF>(gsa::t::maxPoint);
   //   for (int l_N = 0; l_N < gsa::t::maxPoint; l_N++)
   //   {
   //      (*m_Vector)[l_N].setX(DBL_MAX);
   //      (*m_Vector)[l_N].setY(0);
   //   }

   //   _markerseries[index] = (m_series);
   //   _markervectors[index] = (m_Vector);

   //   _updated[_markerseries[index]] = true;
   //}

   initAxisNew(font_);

}

//int MainScreen::init(QChart **chart, QChartView **chartView)
int MainScreen::init(VChart **chart, QChartView **chartView, int index, const gsa::t::ThemeFont &font_, const gsa::t::ThemeFont &fontAxis_)
{
   int counter;
   QSurfaceFormat surfaceFormat;
   QList<QGraphicsView*> l_ViewList;
   QList<QOpenGLWidget*> l_GLList;
   int l_N;

   //if (_chartView != nullptr) delete _chartView;
   //if (_chart != nullptr) delete _chart;

   //_chart = new QChart;
   if (_chart == nullptr) _chart = new VChart;

   //if (_chartView == nullptr) _chartView = new QChartView(_chart);
   if (_chartView == nullptr) _chartView = new VChartView(_chart, _parentWindow);
   //_chartView->scene()->addItem(_chart);

   (*chart) = _chart;
   //_chart->size();
   //_chart->setMinimumSize(2048, 1024);
   _chart->setAcceptHoverEvents(true);

   //(*chartView) = new QChartView(_chart);
   (*chartView) = _chartView;

   //(*chartView)->setMinimumSize(800, 600);
   (*chartView)->setAttribute(Qt::WA_AcceptTouchEvents);

   _chart->legend()->hide();
   _chart->setTitle("Spectrum analyzer");

   int r, g, b;
   _appWidget->GetRgb(font_.color, r, g, b);

   //_chart->setTitleFont(QFont("lucida", 14, QFont::Bold));
   int weight;
   if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal;
   else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold;
   QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);
   _chart->setTitleFont(qfont_);
   //_chart->setTitleBrush(QColor(54, 54, 209));
   _chart->setTitleBrush(QColor(r, g, b));

   //if (_appWidget->colorindexes().size() > 18) {
   //   int  iiiii = 90;
   //}

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());
   //_fontindexes = _appWidget->fontindexes();
   //_colorindexes = _appWidget->colorindexes();
   //_sizeindexes = _appWidget->sizeindexes();
   //_indentindexes = _appWidget->indentindexes();

   gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

   for (auto &themeItem : _theme->themeItems) {
      switch (themeItem.type)
      {
      case 0:
      {
         if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) {
            switch (_colorindexes[std::wstring(themeItem.description)])
            {
            case gsa::t::ColorIndex::DisplayArea: //Display area background 
               item_ = themeItem;
               break;
            default:
               break;
            }
         }
      }
      case 1:
      {
         break;
      }
      case 2:
      {
         break;
      }
      default:
      {
         break;
      }
      }
   }

   int r2, g2, b2;
   _appWidget->GetRgb(item_.value, r2, g2, b2);
   QColor color_(r2, g2, b2);

   //_chart->setBackgroundBrush(QColor(0, 0, 0));
   //_chart->setBackgroundBrush(QColor(0, 0, 128));
   _chart->setBackgroundBrush(color_);
   //_chartView->setBackgroundBrush(color_);

   //_chart->setFont(QFont("lucida", 14, QFont::Bold));
   //_chartView->setFont(QFont("lucida", 14, QFont::Bold));

   //initArray(&m_series, &m_Vector, index);
   initArrayNew(fontAxis_);

   //if (_appWidget->colorindexes().size() > 18) {
   //   int  iiiii = 90;
   //}

   //QObject::connect(m_series, SIGNAL(pointsReplaced()), SLOT(Updated()));
   for (int index = 0; index < Main::_numberTrace; ++index) 
   {
      if (dynamic_cast<QLineSeries *>(_arrayseries[index]) != nullptr) 
      {
         QObject::connect(_arrayseries[index], SIGNAL(pointsReplaced()), SLOT(Updated()));
      }
      _arrayseries[index]->setUseOpenGL(true);

      if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) != nullptr)
         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries() != nullptr)
            dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries()->setUseOpenGL(true);

#ifdef HTML_TEXT
      _anyTextes[index]->setPlainText(""); //("marker");
      _anyTextes[index]->setDefaultTextColor(QColor(0, 255, 0));
      //_anyTextes[index]->setFont(QFont("lucida", 14)); //, QFont::Bold));
      _anyTextes[index]->setFont(QFont("lucida", 54)); //, QFont::Bold));
#else
      _markerTextes[index]->setText(""); //("marker");
      _markerTextes[index]->setBrush(QColor(0, 255, 0));
      _markerTextes[index]->setFont(QFont("lucida", 54)); //, QFont::Bold));
#endif

      _freqTextes[index]->setText(""); //("freq: 400.34 MGz");
      _freqTextes[index]->setBrush(QColor(0, 0, 255));

      _valueTextes[index]->setText(""); //("val: 0.7 mW");
      _valueTextes[index]->setBrush(QColor(0, 0, 255));
   }
   //QObject::connect(_carrigeSeries, SIGNAL(pointsReplaced()), SLOT(Updated()));
   ////QObject::connect(_markerSeries, SIGNAL(pointsReplaced()), SLOT(Updated()));
   //for (int index = 0; index < _numberMarker; ++index) {
   //   QObject::connect(_markerseries[index], SIGNAL(pointsReplaced()), SLOT(Updated()));
   //   _markerseries[index]->setUseOpenGL(true);
   //}

   //_areaSeries->setUseOpenGL(true);

   //если включить OpenGL, то почему-то перестают нормально работать некоторые органы управления, например QComboBox
   //m_series->setUseOpenGL(true);
   //_arrayseries[index]->setUseOpenGL(true);
   //_carrigeSeries->setUseOpenGL(true);
   //_markerSeries->setUseOpenGL(true);

   //connect(m_series, &QLineSeries::clicked, _chartView, &VChartView::keepCallout);
   //connect(m_series, &QLineSeries::hovered, _chartView, &VChartView::tooltip);
   connect(dynamic_cast<QLineSeries *>(_arrayseries[0]), &QLineSeries::clicked, _chartView, &VChartView::keepCallout);
   connect(dynamic_cast<QLineSeries *>(_arrayseries[0]), &QLineSeries::hovered, _chartView, &VChartView::tooltip);

   //connect(_carrigeSeries, &QLineSeries::clicked, this, &View::keepCallout);
   //connect(_carrigeSeries, &QLineSeries::hovered, this, &View::tooltip);

   QGraphicsSimpleTextItem *m_coordX(nullptr);
   QGraphicsSimpleTextItem *m_coordY(nullptr);

   int height = _chart->size().height();

   //_freqText = new QGraphicsSimpleTextItem(_chart);
   //_freqText->setPos(100, 900);
   //_freqText->setText("freq: 400.34 MGz");
   //_freqText->setBrush(QColor(0, 0, 255));

   //_valueText = new QGraphicsSimpleTextItem(_chart);
   //_valueText->setPos(200, 900);
   //_valueText->setText("val: 0.7 mW");
   //_valueText->setBrush(QColor(0, 0, 255));

   //m_coordX = new QGraphicsSimpleTextItem(_chart);
   ////m_coordX->setPos(_chart->size().width() / 2 -   0, _chart->size().height());
   //m_coordX->setPos(100, 900);
   //m_coordX->setText("freq: 400.34 MGz");
   //m_coordX->setBrush(QColor(255, 0, 0));

   //m_coordY = new QGraphicsSimpleTextItem(_chart);
   ////m_coordY->setPos(_chart->size().width() / 2 + 100, _chart->size().height());
   //m_coordY->setPos(200, 900);
   //m_coordY->setText("val: 0.7 mW");
   //m_coordY->setBrush(QColor(255, 0, 0));

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

   ////ui->comboBox->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
   ////ui->comboBox->setFocusProxy((QWidget *)chartView);
   //ui->comboBox->setMaxVisibleItems(10);
   ////ui->comboBox->setMinimumHeight(100);

   //_chartView->scene()->addItem(_chart);

   l_ViewList = _chart->scene()->views();
   //scene()->addItem(_chart);
   const char *_classScene = ((QObject*)_chart->scene())->metaObject()->className();
   const char *_className = ((QObject*)l_ViewList[0])->metaObject()->className();
   const char *_superClass = ((QObject*)l_ViewList[0])->metaObject()->superClass()->className();

   l_GLList = l_ViewList[0]->findChildren<QOpenGLWidget *>();
   if (l_GLList.length() > 0) {
      m_GLWidget = l_GLList[0];
      QObject::connect(m_GLWidget, SIGNAL(frameSwapped()), SLOT(Swaped()));
      QObject::connect(m_GLWidget, SIGNAL(resized()), SLOT(Sized()));
   }

   //////openGLWidget = (QOpenGLWidget *)chartView;
   //////surfaceFormat = openGLWidget->format();
   ////surfaceFormat = ll[0]->format();

   ////int si = surfaceFormat.swapInterval();

   //ui->horizontalLayout->addWidget(chartView);
   //ui->frameRight->raise();

   QSize _size2 = (*chartView)->size();

   //changeAxises(&m_series);
   changeAxises(nullptr);

   //_chartView->setGeometry(100, 100, 100, 100);
   //_chart->setGeometry(100, 100, 100, 100);

   return 0;
}

//void MainScreen::initAxis(QLineSeries **series)
//{
//   if (_chart == nullptr || _carrigeSeries == nullptr || _carrigeSeries == nullptr)
//      return;
//
//   _xmin = 0;
//   _xmax = gsa::t::maxPoint;
//
//   _ymin = -50;
//   _ymax = 50;
//
//   //_chart->removeAxis(_axisX);
//   //_axisX->setRange(min, max);
//
//   //QLogValueAxis *axisY = new QLogValueAxis();
//   //axisY->setTitleText("Values");
//   //axisY->setLabelFormat("%g");
//   //axisY->setBase(8.0);
//   //axisY->setMinorTickCount(-1);
//   //chart->addAxis(axisY, Qt::AlignLeft);
//   //series->attachAxis(axisY);
//
//   //if (_axisX != nullptr) delete _axisX;
//   //if (_axisY != nullptr) delete _axisY;
//
//   if (_axisX == nullptr) {
//      _axisX = new QValueAxis;
//
//      //_axisX->setRange(0, gsa::t::maxPoint);
//      _axisX->setRange(_xmin, _xmax);
//      ((QValueAxis*)_axisX)->setLabelFormat("%g");
//      _axisX->setTitleText("Frequency");
//   }
//   if (_axisY == nullptr) {
//      _axisY = new QValueAxis;
//
//      //_axisY->setRange(-50, 50);
//      _axisY->setRange(_ymin, _ymax);
//      ((QValueAxis*)_axisY)->setLabelFormat("%g");
//      _axisY->setTitleText("Level");
//   }
//
//   if (_axisLogX == nullptr) {
//      _axisLogX = new QLogValueAxis;
//   }
//   if (_axisLogY == nullptr) {
//      _axisLogY = new QLogValueAxis;
//
//      ((QLogValueAxis*)_axisLogY)->setTitleText("Level");
//      ((QLogValueAxis*)_axisLogY)->setLabelFormat("%g");
//      ((QLogValueAxis*)_axisLogY)->setBase(8.0);//(2.72); //
//      ((QLogValueAxis*)_axisLogY)->setMinorTickCount(-1);
//   }
//
//   _axisActiveX = _axisX;
//   _axisActiveY = _axisY;
//
//   _axisLog = true;
//
//   if (_chart->axes().length() == 0 ) {
//      _chart->setAxisX(_axisX, (*series));
//      _chart->setAxisY(_axisY, (*series));
//      _chart->setAxisX(_axisX, _carrigeSeries);
//      _chart->setAxisY(_axisY, _carrigeSeries);
//      _chart->setAxisX(_axisX, _markerSeries);
//      _chart->setAxisY(_axisY, _markerSeries);
//   }
//
//   QList<QAbstractSeries *> series_ = _chart->series();
//   QList<QAbstractAxis*> axes_ = _chart->axes();
//   int i(0);
//}

void MainScreen::initAxisNew(const gsa::t::ThemeFont &font_)
{
   //if (_chart == nullptr || _carrigeSeries == nullptr || _carrigeSeries == nullptr)
   //   return;

   if (_chartView == nullptr || _chart == nullptr) return;

   _xmin = 0;
   _xmax = gsa::t::maxPoint;

   _ymin = -50;
   _ymax = 50;

   int r, g, b;
   _appWidget->GetRgb(font_.color, r, g, b);

   int weight;
   if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal;
   else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold;
   QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);

   if (_axisX == nullptr) {
      _axisX = new QValueAxis;

      //_axisX->setRange(0, gsa::t::maxPoint);
      _axisX->setRange(_xmin, _xmax);
      ((QValueAxis*)_axisX)->setLabelFormat("%g");
      _axisX->setTitleText("Frequency");
      _axisX->setLabelsFont(QFont("lucida", 14, QFont::Bold));
      _axisX->setTitleFont(QFont("lucida", 14, QFont::Bold));
      //_axisX->setLabelsFont(qfont_);
      //_axisX->setTitleFont(qfont_);

      _axisX->setGridLineColor(QColor(128,128,128));
      _axisX->setLabelsColor(QColor(128, 128, 128));
      _axisX->setTitleBrush(QColor(128, 128, 128));
      ((QValueAxis*)_axisX)->setTickCount(11);
   }
   if (_axisY == nullptr) {
      _axisY = new QValueAxis;

      //_axisY->setRange(-50, 50);
      _axisY->setRange(_ymin, _ymax);
      ((QValueAxis*)_axisY)->setLabelFormat("%g");
      _axisY->setTitleText("Level");
      _axisY->setLabelsFont(QFont("lucida", 14, QFont::Bold));
      _axisY->setTitleFont(QFont("lucida", 14, QFont::Bold));
      //_axisY->setLabelsFont(qfont_);
      //_axisY->setTitleFont(qfont_);

      _axisY->setGridLineColor(QColor(128, 128, 128));
      _axisY->setLabelsColor(QColor(128, 128, 128));
      _axisY->setTitleBrush(QColor(128, 128, 128));
      ((QValueAxis*)_axisY)->setTickCount(11);
   }

   if (_axisLogX == nullptr) {
      _axisLogX = new QLogValueAxis;

      ((QLogValueAxis*)_axisLogX)->setLabelsFont(QFont("lucida", 14, QFont::Bold));
      ((QLogValueAxis*)_axisLogX)->setTitleFont(QFont("lucida", 14, QFont::Bold));
      //((QLogValueAxis*)_axisLogX)->setLabelsFont(qfont_);
      //((QLogValueAxis*)_axisLogX)->setTitleFont(qfont_);
   }
   if (_axisLogY == nullptr) {
      _axisLogY = new QLogValueAxis;

      ((QLogValueAxis*)_axisLogY)->setTitleText("Level");
      ((QLogValueAxis*)_axisLogY)->setLabelsFont(QFont("lucida", 14, QFont::Bold));
      ((QLogValueAxis*)_axisLogY)->setTitleFont(QFont("lucida", 14, QFont::Bold));
      //((QLogValueAxis*)_axisLogY)->setLabelsFont(qfont_);
      //((QLogValueAxis*)_axisLogY)->setTitleFont(qfont_);
      ((QLogValueAxis*)_axisLogY)->setLabelFormat("%g");
      ((QLogValueAxis*)_axisLogY)->setBase(10.0);//(2.72); //
      ((QLogValueAxis*)_axisLogY)->setMinorTickCount(-1);
   }

   _axisActiveX = _axisX;
   _axisActiveY = _axisY;

   _axisLog = false;

   if (_chart->axes().length() == 0) {
      for (int index = 0; index < Main::_numberTrace; ++index) {
         _chart->setAxisX(_axisActiveX, _arrayseries[index]);
         _chart->setAxisY(_axisActiveY, _arrayseries[index]);

         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) != nullptr) {
            if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries() != nullptr)
            {
               _chart->setAxisX(_axisActiveX, dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries());
               _chart->setAxisY(_axisActiveY, dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries());
            }
         }
      }
      //_chart->setAxisX(_axisActiveX, _carrigeSeries);
      //_chart->setAxisY(_axisActiveY, _carrigeSeries);
      ////_chart->setAxisX(_axisActiveX, _markerSeries);
      ////_chart->setAxisY(_axisActiveY, _markerSeries);
      //for (int index = 0; index < _numberMarker; ++index) {
      //   _chart->setAxisX(_axisActiveX, _markerseries[index]);
      //   _chart->setAxisY(_axisActiveY, _markerseries[index]);
      //}
   }

   //_chart->setAxisX(_axisActiveX, _areaSeries);
   //_chart->setAxisY(_axisActiveY, _areaSeries);

   //_axisActiveX->setLinePenColor(QColor(256, 256, 0));
   //_axisActiveY->setLinePenColor(QColor(256, 256, 0));

   //// Customize axis colors
   ////QPen axisPen(QRgb(0xf1f912));
   //QPen axisPen(QColor(255, 255, 0));
   //axisPen.setWidth(2);
   //_axisActiveX->setLinePen(axisPen);
   //_axisActiveY->setLinePen(axisPen);

   QList<QAbstractSeries *> series_ = _chart->series();
   QList<QAbstractAxis*> axes_ = _chart->axes();

   //for (auto &item: series_) {
   //   item->attachAxis(_axisActiveX);
   //   item->attachAxis(_axisActiveY);
   //}

   int i(0);

}

void MainScreen::changeAxises(QLineSeries **series)
{
   //if (_chart == nullptr || _carrigeSeries == nullptr || _carrigeSeries == nullptr)
   //   return;

   if (_chartView == nullptr || _chart == nullptr) return;

   //_chart->removeAxis(_axisX);
   //_chart->removeAxis(_axisY);
   _chart->removeAxis(_axisActiveX);
   _chart->removeAxis(_axisActiveY);

   QList<QAbstractSeries *> series_ = _chart->series();
   QList<QAbstractAxis*> axes_ = _chart->axes();
   int i(0);

   //_xmin *= 0.97;
   //_xmax *= 1.03;
   //_ymin *= 0.97;
   //_ymax *= 1.03;
   //_axisX->setRange(_xmin, _xmax);
   //_axisY->setRange(_ymin, _ymax);

   //_chart->setAxisX(_axisX, (*series));
   //_chart->setAxisY(_axisY, (*series));
   //_chart->setAxisX(_axisX, _carrigeSeries);
   //_chart->setAxisY(_axisY, _carrigeSeries);
   //_chart->setAxisX(_axisX, _markerSeries);
   //_chart->setAxisY(_axisY, _markerSeries);

}

void MainScreen::vrangeChangedXEmit(qreal min, qreal max, bool setrange)
{
   emit signalVrangeChangedX(min, max, setrange);
}

void MainScreen::vrangeChangedYEmit(qreal min, qreal max, bool setrange)
{
   emit signalVrangeChangedY(min, max, setrange);
}

void MainScreen::vrangeChangedX(qreal min, qreal max, bool setrange)
{
   _xmin = min;
   _xmax = max;

   DWORD id = GetCurrentThreadId();

   if (_chartView == nullptr || _chart == nullptr) return;

   QSize size3 = size();
   QSize size4 = _chartView->size();
   QSizeF size5 = _chart->size();
   QSizeF size6 = _chart->plotArea().size();

   //QString str(QString("INFO007 %1[%2]%3 this=%4 setrange=%5 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this).arg(setrange ? "true" : "false"));
   //qInfo(str.toStdString().c_str());

   if (setrange) {
      //((QValueAxis*)(_chart->axisX()))->setRange(min, max);
      //_axisX->setRange(min, max);

      //int count = _chart->axes().size();
      //QAbstractAxis *px = _chart->axisX();
      //QAbstractAxis *py = _chart->axisY();
      if(_chart->axisX() != nullptr)
         _chart->removeAxis(_axisActiveX);

      _axisActiveX->setRange(_xmin, _xmax);

      QList<QAbstractSeries *> series1_ = _chart->series();
      QList<QAbstractAxis*> axes1_ = _chart->axes();
      int j(0);

      //_axisX->setRange(min, max);
      //((QValueAxis*)_axisX)->setLabelFormat("%g");
      //_axisX->setTitleText("Frequency");

      //_chart->setAxisX(_axisX, m_series);
      for (int index = 0; index < Main::_numberTrace; ++index) {
         _chart->setAxisX(_axisActiveX, _arrayseries[index]);

         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) != nullptr) {
            if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries() != nullptr)
            {
               _chart->setAxisX(_axisActiveX, dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries());
            }
         }
      }
      //_chart->setAxisX(_axisActiveX, _carrigeSeries);
      ////_chart->setAxisX(_axisActiveX, _markerSeries);
      //for (int index = 0; index < _numberMarker; ++index) {
      //   _chart->setAxisX(_axisActiveX, _markerseries[index]);
      //}
      //_chart->setAxisX(_axisActiveX, _areaSeries);

      setActiveFont();

      QList<QAbstractSeries *> series_ = _chart->series();
      QList<QAbstractAxis*> axes_ = _chart->axes();
      int i(0);

      //_chart->update();

      //_chart->removeAxis(_axisY);

      ////_axisY->setRange(min, max);
      ////((QValueAxis*)_axisY)->setLabelFormat("%g");
      ////_axisY->setTitleText("Level");

      //_chart->setAxisY(_axisY, m_series);
      //_chart->setAxisY(_axisY, _carrigeSeries);
      //_chart->setAxisY(_axisY, _markerSeries);

      //_axisY->setRange(_ymin, _ymax);

   }
}

void MainScreen::vrangeChangedY(qreal min, qreal max, bool setrange)
{
   _ymin = min;
   _ymax = max;

   DWORD id = GetCurrentThreadId();

   if (_chartView == nullptr || _chart == nullptr) return;

   QSize size3 = size();
   QSize size4 = _chartView->size();
   QSizeF size5 = _chart->size();
   QSizeF size6 = _chart->plotArea().size();

   //QString str(QString("INFO007 %1[%2]%3 this=%4 setrange=%5 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this).arg(setrange ? "true" : "false"));
   //qInfo(str.toStdString().c_str());

   if (setrange)
   {
      //((QValueAxis*)(_chart->axisY()))->setRange(min, max);
      //_axisY->setRange(min, max);

      //_chart->removeAxis(_axisY);
      if (_chart->axisY() != nullptr)
         _chart->removeAxis(_axisActiveY);

      //_axisLog = !_axisLog;

      if (_axisLog) {
         _axisActiveY = _axisLogY;

         //_yminLinear = _ymin;
         //_ymaxLinear1 = _ymax;

         //_ymin = 1.0;
         //_ymax = 1000.0; //4096.0; //10e10; //1000000.0;
         _axisActiveY->setRange(_ymin, _ymax);
         ((QLogValueAxis*)_axisActiveY)->setBase(10.0);
         ((QLogValueAxis*)_axisActiveY)->setMinorTickCount(-1);

         _axisActiveY->setLabelsFont(QFont("lucida", 14, QFont::Bold));
         _axisActiveY->setTitleFont(QFont("lucida", 14, QFont::Bold));
      }
      else {
         _axisActiveY = _axisY;

         /*if (_yminLinear != _ymaxLinear1) {
            _ymin = _yminLinear;
            _ymax = _ymaxLinear1;
         }*/

         _axisActiveY->setRange(_ymin, _ymax);

         _axisActiveY->setLabelsFont(QFont("lucida", 14, QFont::Bold));
         _axisActiveY->setTitleFont(QFont("lucida", 14, QFont::Bold));
      }

      //_axisY->setRange(_ymin, _ymax);

      QList<QAbstractSeries *> series_ = _chart->series();
      QList<QAbstractAxis*> axes_ = _chart->axes();
      int i(0);

      //_axisY->setRange(min, max);
      //((QValueAxis*)_axisY)->setLabelFormat("%g");
      //_axisY->setTitleText("Level");

      //_chart->setAxisY(_axisY, m_series);
      //_chart->setAxisY(_axisY, _carrigeSeries);
      //_chart->setAxisY(_axisY, _markerSeries);

      //_chart->setAxisY(_axisActiveY, m_series);
      for (int index = 0; index < Main::_numberTrace; ++index) {
         _chart->setAxisY(_axisActiveY, _arrayseries[index]);

         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) != nullptr) {
            if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries() != nullptr)
            {
               _chart->setAxisY(_axisActiveY, dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries());
            }
         }
      }
      //_chart->setAxisY(_axisActiveY, _carrigeSeries);
      ////_chart->setAxisY(_axisActiveY, _markerSeries);
      //for (int index = 0; index < _numberMarker; ++index) {
      //   _chart->setAxisY(_axisActiveY, _markerseries[index]);
      //}
      //_chart->setAxisY(_axisActiveY, _areaSeries);

      //_axisY->setRange(_ymin, _ymax);

      QList<QAbstractSeries *> series2_ = _chart->series();
      QList<QAbstractAxis*> axes2_ = _chart->axes();
      int j(0);

      //_chart->update();

      //_chart->removeAxis(_axisX);

      ////_axisX->setRange(min, max);
      ////((QValueAxis*)_axisX)->setLabelFormat("%g");
      ////_axisX->setTitleText("Frequency");

      //_chart->setAxisX(_axisX, m_series);
      //_chart->setAxisX(_axisX, _carrigeSeries);
      //_chart->setAxisX(_axisX, _markerSeries);

      //_axisX->setRange(_xmin, _xmax);

   }

   _chartViewHeight = _chartView->size().height();

   //qreal yvald_((_ymin));
   ////qreal yvalu_((_ymin + _ymin*0.05));
   ////qreal yvalu_((_ymin + (_ymax - _ymin)*((_ymax - _ymin) / 200.0)));
   //qreal yvalu_(_ymin + (_ymax - _ymin) / 200.0);
   //qreal yvalm_((_ymax));

   //_freqText->setPos(100, height - height / 20);
   //_valueText->setPos(400, height - height / 20);
   //_freqTextes[0]->setPos(128, _chartViewHeight - _chartViewHeight / 20);
   //_valueTextes[0]->setPos(256, _chartViewHeight - _chartViewHeight / 20);

   setActiveFont();

   int i(0);
   //_offsetIndexMarker
   for (i = 0; i < 4; i++) {
      _freqTextes[_offsetIndexMarker + i]->setPos(64 + i * 384, _chartViewHeight - _chartViewHeight / 28);
      _valueTextes[_offsetIndexMarker + i]->setPos(256 + i * 384, _chartViewHeight - _chartViewHeight / 28);
   }
   for (i = 4; i < 8; i++) {
      _freqTextes[_offsetIndexMarker + i]->setPos(64 + (i - 4) * 384, _chartViewHeight - _chartViewHeight / 42);
      _valueTextes[_offsetIndexMarker + i]->setPos(256 + (i - 4) * 384, _chartViewHeight - _chartViewHeight / 42);
   }
}

void MainScreen::setRestyle(int _index, GraphPanelStyle _style)
{
   delete[] m_CurrentStyle.XAxisName;
   delete[] m_CurrentStyle.XAxisUnit;
   delete[] m_CurrentStyle.YAxisName;
   delete[] m_CurrentStyle.YAxisUnit;

   m_CurrentStyle.XAxisName = new wchar_t[1024];
   m_CurrentStyle.XAxisUnit = new wchar_t[1024];
   m_CurrentStyle.YAxisName = new wchar_t[1024];
   m_CurrentStyle.YAxisUnit = new wchar_t[1024];
   //m_CurrentStyle.XAxisName = new wchar_t[wcslen(_style.XAxisName)];
   //m_CurrentStyle.XAxisUnit = new wchar_t[wcslen(_style.XAxisUnit)];
   //m_CurrentStyle.YAxisName = new wchar_t[wcslen(_style.YAxisName)];
   //m_CurrentStyle.YAxisUnit = new wchar_t[wcslen(_style.YAxisUnit)];

   wcscpy(m_CurrentStyle.XAxisName, _style.XAxisName);
   wcscpy(m_CurrentStyle.XAxisUnit, _style.XAxisUnit);
   wcscpy(m_CurrentStyle.YAxisName, _style.YAxisName);
   wcscpy(m_CurrentStyle.YAxisUnit, _style.YAxisUnit);

   m_CurrentStyle._axisColour = _style._axisColour;
   m_CurrentStyle._xscaling = _style._xscaling;
   m_CurrentStyle._yscaling = _style._yscaling;

   emit signalRestyle(_index);
}

void MainScreen::slotRestyle(int _index)
{
   //mainWindow->_mainScreen->setRestyle(_index, _style);

   if (_chartView == nullptr || _chart == nullptr) return;

   QSize size3 = size();
   QSize size4 = _chartView->size();
   QSizeF size5 = _chart->size();
   QSizeF size6 = _chart->plotArea().size();

   QString l_Teg;

   if (_chart->axisY() != nullptr)
      _chart->removeAxis(_axisActiveY);

   switch (_index)
   {
   case 0: //StyleEventTypeEnum.AxisScaling:
      //AxisStyle pX = _Panel.Style.XScaling;
      //AxisStyle pY = _Panel.Style.YScaling;
      m_CurrentStyle._xscaling;
      m_CurrentStyle._yscaling;
      if (m_CurrentStyle._yscaling == AxisStyle::Linear) {
         _axisLog = false;
      }
      else {
         _axisLog = true;
      }
      break;
   case 1: //StyleEventTypeEnum.AxisUnit:
      //Enum yAxisUnit = _Panel.Style.YAxisUnit;
      //_style._xaxisUnit;
      //_style._yaxisUnit;
      break;
   case 2: //StyleEventTypeEnum.AxisColor:
      //ColourStruct axisColour = _Panel.Style.AxisColour;
      m_CurrentStyle._axisColour.Red;
      break;
   case 3: //StyleEventTypeEnum.FullReset:
      //QtGuiLib.setRestyle(_Args.EventType, _Panel.Style);
      break;
   }

   //_axisLog = !_axisLog;

   l_Teg.clear();
   l_Teg.append(QString::fromWCharArray(m_CurrentStyle.XAxisName).append(QString::fromWCharArray(L" (")).
      append(QString::fromWCharArray(m_CurrentStyle.XAxisUnit)).append(QString::fromWCharArray(L")")));
   _axisActiveX->setTitleText(l_Teg);
   //((QValueAxis *)_axisActiveX)->setLabelFormat("%8e");

   l_Teg.clear();
   l_Teg.append(QString::fromWCharArray(m_CurrentStyle.YAxisName).append(QString::fromWCharArray(L" (")).
      append(QString::fromWCharArray(m_CurrentStyle.YAxisUnit)).append(QString::fromWCharArray(L")")));
   _axisActiveY->setTitleText(l_Teg);

   if (_axisLog) {
      _axisActiveY = _axisLogY;

      //_yminLinear = _ymin;
      //_ymaxLinear1 = _ymax;

      //_ymin = 1.0;
      //_ymax = 1000.0; //4096.0; //10e10; //1000000.0;
      _axisActiveY->setRange(_ymin, _ymax);
      ((QLogValueAxis*)_axisActiveY)->setBase(10.0);
      ((QLogValueAxis*)_axisActiveY)->setMinorTickCount(-1);
   }
   else {
      _axisActiveY = _axisY;

      //_ymin = _yminLinear;
      //_ymax = _ymaxLinear1;

      _axisActiveY->setRange(_ymin, _ymax);
   }

   QList<QAbstractSeries *> series_ = _chart->series();
   QList<QAbstractAxis*> axes_ = _chart->axes();
   int i(0);

   //_chart->setAxisY(_axisActiveY, m_series);
   for (int index = 0; index < Main::_numberTrace; ++index) {
      _chart->setAxisY(_axisActiveY, _arrayseries[index]);

      if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) != nullptr) {
         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries() != nullptr)
         {
            _chart->setAxisY(_axisActiveY, dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries());
         }
      }
   }
   //_chart->setAxisY(_axisActiveY, _carrigeSeries);
   ////_chart->setAxisY(_axisActiveY, _markerSeries);
   //for (int index = 0; index < _numberMarker; ++index) {
   //   _chart->setAxisY(_axisActiveY, _markerseries[index]);
   //}
   //_chart->setAxisY(_axisActiveY, _areaSeries);

   setActiveFont();

   QList<QAbstractSeries *> series2_ = _chart->series();
   QList<QAbstractAxis*> axes2_ = _chart->axes();
   int j(0);

}

void MainScreen::messageBox(wchar_t* _caption, wchar_t* _text)
{
   //mainWindow->_mainScreen->messageBox(_caption, _text);
   //return 0;

   DWORD id = GetCurrentThreadId();

   emit signalMessageBox(_caption, _text);

   //DialogMessage *test = new DialogMessage(this);
   //test->show();
}

void MainScreen::setActiveFont(void)
{
   int r, g, b;
   _appWidget->GetRgb(_font.color, r, g, b);

   int weight;
   if (QString::fromWCharArray(_font.style) == QString("normal")) weight = QFont::Normal;
   else if (QString::fromWCharArray(_font.style) == QString("bold")) weight = QFont::Bold;
   QFont qfont_(QString::fromWCharArray(_font.family), _font.size, weight);

   _axisActiveX->setLabelsFont(QFont("lucida", 14, QFont::Bold));
   //_axisActiveX->setTitleFont(QFont("lucida", 14, QFont::Bold));
   _axisActiveY->setLabelsFont(QFont("lucida", 14, QFont::Bold));
   //_axisActiveY->setTitleFont(QFont("lucida", 14, QFont::Bold));

   //_axisActiveX->setLabelsFont(qfont_);
   _axisActiveX->setTitleFont(qfont_);
   //_axisActiveY->setLabelsFont(qfont_);
   _axisActiveY->setTitleFont(qfont_);

   _axisActiveX->setTitleBrush(QColor(r, g, b));
   _axisActiveY->setTitleBrush(QColor(r, g, b));

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());
   //_fontindexes = _appWidget->fontindexes();
   //_colorindexes = _appWidget->colorindexes();
   //_sizeindexes = _appWidget->sizeindexes();
   //_indentindexes = _appWidget->indentindexes();

   gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

   for (auto &item : _theme->themeItems) {
      if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
         switch (_colorindexes[std::wstring(item.description)])
         {
         case gsa::t::ColorIndex::GraphicPanelScale: //Graphic panel scale 
         {
            item_ = item;
            break;
         }
         default:
            break;
         }
      }
   }

   int r2, g2, b2;
   _appWidget->GetRgb(item_.value, r2, g2, b2);

   //_axisActiveX->setLinePenColor(QColor(256, 256, 0));
   //_axisActiveY->setLinePenColor(QColor(256, 256, 0));

   // Customize axis colors
   //QPen axisPen(QRgb(0xf1f912));
   QPen axisPen(QColor(r2, g2, b2));
   axisPen.setWidth(2);
   _axisActiveX->setLinePen(axisPen);
   _axisActiveY->setLinePen(axisPen);

   QList<QAbstractSeries *> series_ = _chart->series();
   QList<QAbstractAxis*> axes_ = _chart->axes();

   int i(0);

}

void MainScreen::on_rangeChangedX(qreal min, qreal max)
{
   //return;

   wchar_t _Param1[1024] = L"Spectrogram";
   GraphPanelRange _Param2;
   _Param2.Min = min;
   _Param2.Max = max;

   if (RerangeXCallback != nullptr) {
      int i(g_Parameter._currentMenu->indexMode);
      int j(g_Parameter._currentMenu->indexMeas);
      int k(g_Parameter._currentMenu->indexView);

      //__van__ 2019.08.08 
      if (g_Parameter._modeMeasView.get() != nullptr) {
        wchar_t *name = g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[0].name;
        if (name != nullptr)
          RerangeXCallback(name, _Param2);
        else
          RerangeXCallback(_Param1, _Param2);
        //_chart->axisX()->setRange(min, max);
      }
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
   //   min = avg - 0.05;
   //   max = avg + 0.05;
   //   range_fixed = true;
   //}

   //if (min < 0.0) { min = 0.0; range_fixed = true; }

   //if (max > 4.0) { max = 4.0; range_fixed = true; }

   //if (range_fixed) {
   //   x->setRange(min, max);    // will re-signal with the fixed range
   //   return;
   //}

   //qreal    vis_width = c->plotArea().width();
   //qreal    all_width = vis_width * (4.0 - 0.0) / (max - min);

   ////    cerr << "range " << min << " ... " << max << " in " << vis_width << " pixels" << endl;
   ////    cerr << "full width requires " << all_width << " pixels" << endl;;

   //if (max - min < 4.0) {
   //   //        cerr << "set scroll parameters" << endl;
   //   scrolling = true;
   //   ui->chartScroll->setMaximum(all_width - vis_width);
   //   sv = min / (4.0 - 0.0) * all_width;
   //   ui->chartScroll->setValue(sv);
   //   scrolling = false;
   //}
   //else {
   //   //        cerr << "disable scroll bar" << endl;
   //   scrolling = true;
   //   ui->chartScroll->setMaximum(0);
   //   ui->chartScroll->setValue(sv);
   //   scrolling = false;
   //}
}

void MainScreen::on_rangeChangedY(qreal min, qreal max)
{
   //return;

   wchar_t _Param1[1024] = L"Spectrogram";
   GraphPanelRange _Param2;
   _Param2.Min = min;
   _Param2.Max = max;

   if (RerangeYCallback != nullptr) {
      int i(g_Parameter._currentMenu->indexMode);
      int j(g_Parameter._currentMenu->indexMeas);
      int k(g_Parameter._currentMenu->indexView);

      //__van__ 2019.08.08 
      if (g_Parameter._modeMeasView.get() != nullptr) {
        wchar_t *name = g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[0].name;
        if (name != nullptr)
          RerangeYCallback(name, _Param2);
        else
          RerangeYCallback(_Param1, _Param2);
        //_chart->axisY()->setRange(min, max);
      }
   }
}

void MainScreen::Updated(void)
{
   QObject* obj = sender();

   if (obj == (QObject*)___series___) {
      int i(0);
   }

   if (_updated.find(obj) != _updated.end()) {
      _updated[obj] = true;
   }
   else {
      int i(0);
   }
}

void MainScreen::Swaped(void)
{
  //__van__ 2019.08.08 
  if (VSyncCallback != nullptr)
    VSyncCallback();
}

void MainScreen::setCentralRect(const QRect &rect)
{
   _centralRect.setRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void MainScreen::myResizeCallback(wchar_t *name, QRect *rect, bool bForce)
{
   //return;

   QSize size3 = size();
   QSize size4 = _chartView->size();
   QSizeF size5 = _chart->size();
   QSizeF size6 = _chart->plotArea().size();

   _centralRect.setRect(rect->x(), rect->y(), rect->width(), rect->height());

   int _chartWidth222 = _chart->plotArea().width();
   //if (_chartWidth != _chart->plotArea().width()) 
   if (bForce || (_chartWidth != _chartView->size().width()))
      //if (abs(_chartWidth - _chartView->size().width()) > 4) 
   {
     //__van__ 2019.08.08 
     if (ResizeCallback != nullptr)
       ResizeCallback(name, _chart->plotArea().width());

      _chartWidth = _chartView->size().width();

      //QSize size4 = _chartView->size();
      //QSizeF size5 = _chart->size();
      //QSizeF size6 = _chart->plotArea().size();
      //_leftBottomText->setPos(qreal(0), qreal(_chartView->size().height() - 100));
   }
}

void MainScreen::Sized(void) 
{ 
   //return;

   //int weight;
   //if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal;
   //else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold;
   //QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);
   //_chart->setTitleFont(qfont_);
   ////_chart->setTitleBrush(QColor(54, 54, 209));
   //_chart->setTitleBrush(QColor(r, g, b));

   //if (_appWidget->colorindexes().size() > 18) {
   //   int  iiiii = 90;
   //}

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

   gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

   item_.description = nullptr;

   for (auto &themeItem : _theme->themeItems) {
      switch (themeItem.type)
      {
      case 0:
      {
         if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) {
            switch (_colorindexes[std::wstring(themeItem.description)])
            {
            case gsa::t::ColorIndex::DisplayArea: //Display area background 
            {
               item_ = themeItem;
               break;
            }
            default:
               break;
            }
         }
      }
      case 1:
      {
         break;
      }
      case 2:
      {
         break;
      }
      default:
      {
         break;
      }
      }
   }

   int r2, g2, b2;
   _appWidget->GetRgb(item_.value, r2, g2, b2);
   QColor color_(r2, g2, b2);

   QSize size3 = size();
   QSize size4 = _chartView->size(); 
   QSizeF size5 = _chart->size(); 
   QSizeF size6 = _chart->plotArea().size();
   //int _chartWidth = _chart->plotArea().width(); 
   QRectF rectPlot = _chart->plotArea();

   //_chartView->setGeometry(128, 128, 1024, 768); //!!!
   //_chart->setGeometry(128, 128, 640, 480);
   //_chart->setGeometry(rectPlot.x(), rectPlot.y(), rectPlot.width(), rectPlot.height());

   //QRectF rect;
   //QBrush brush(QColor(255, 0, 0));
   //_chartView->setBackgroundBrush(QColor(120, 120, 120));
   //_chartView->setBackgroundBrush(QColor(0, 0, 0));

   _chartView->setBackgroundBrush(color_);

   //_chart->setPlotArea(rect);
   _chart->setPlotAreaBackgroundVisible();
   //_chart->setPlotAreaBackgroundBrush(QColor(8, 8, 8));
   if(item_.description != nullptr)
      _chart->setPlotAreaBackgroundBrush(color_);

   if (_chartWidth != _chartView->size().width())
   //if (abs(_chartWidth - _chartView->size().width()) > 4)
   { 
      //qreal width = _chart->plotArea().width(); 
      //qreal height = _chart->plotArea().height(); 
      QSizeF size7 = _chart->plotArea().size(); 

      int i(g_Parameter._currentMenu->indexMode); 
      int j(g_Parameter._currentMenu->indexMeas); 
      int k(g_Parameter._currentMenu->indexView); 

      //__van__ 2019.08.08 
      if (g_Parameter._modeMeasView.get() != nullptr)
      {
        wchar_t *name = g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[0].name;

        //__van__ 2019.08.08 
        if (name != nullptr)
          ResizeCallback(name, _chart->plotArea().width());
        else
          ResizeCallback(L"Spectrogram", _chart->plotArea().width());
      }

      _chartWidth = _chartView->size().width(); 
   }

   //endless cycle 
   if (_plotWidth != _chart->plotArea().width() ) { 
      _plotWidth = _chart->plotArea().width(); 
      //ResizeCallback(L"Spectrogram", _chart->plotArea().width()); 
   } 

   //QSize size14 = _chartView->size();
   //QSizeF size15 = _chart->size();
   //QSizeF size16 = _chart->plotArea().size();
   //qreal x_ = _chart->plotArea().x();
   //qreal y_ = _chart->plotArea().y();
   //QPointF _pos1 = _chart->pos();
   //QPointF _pos2 = _chartView->pos();
   //QPointF _pos3 = _leftBottomText->pos();
   //QRectF _rect2 = _leftBottomText->boundingRect();
   ////QRectF _rect3 = _leftBottomText->boundingRegion();
   //QPolygonF _poly1 = _leftBottomText->mapFromScene(_rect2);
   //QPolygonF _poly2 = _leftBottomText->mapToScene(_rect2);

   qreal x_; 
   qreal y_;
   qreal width_;
   qreal height_;
   for (auto item : _screenBottoms) {
      for (int i = 0; i < item.second.size(); i++) {
         if (item.second[i] != nullptr) {
            if (dynamic_cast<ScreenTextItem *>(item.second[i]) != nullptr) 
            {
               ScreenTextItem *textItem_(dynamic_cast<ScreenTextItem *>(item.second[i]));
               textItem_->setGsaVisible(SetPosition(textItem_, i, x_, y_, width_, height_));
#ifdef HTML_TEXT
               if (textItem_->gsaVisible()) 
               {
                  gsa::t::Theme *_theme(g_Parameter._theme);
                  std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
                  std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
                  std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
                  std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

                  gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
                  gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

                  for (auto &font : _theme->themeFonts) {
                     if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
                        switch (_fontindexes[std::wstring(font.description)])
                        {
                        case gsa::t::FontIndex::PanelControl: font_ = font; break;
                        default: break;
                        }
                     }
                  }
                  for (auto &item : _theme->themeItems) {
                     if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                        switch (_colorindexes[std::wstring(item.description)])
                        {
                        case gsa::t::ColorIndex::PanelControl: item_ = item; break;
                        default: break;
                        }
                     }
                  }

                  int r, g, b;
                  _appWidget->GetRgb(item_.value, r, g, b);
                  QColor cbackground(r, g, b);
                  _appWidget->GetRgb(font_.color, r, g, b);
                  QColor cfont(r, g, b);

                  textItem_->setDefaultTextColor(cfont);

                  textItem_->setPlainText(QString(""));
                  QString name_(textItem_->name());
                  QString unit_(textItem_->unit());
                  QString value_(QString(""));
                  gsa::controller->Double2String(value_, textItem_->value());
                  textItem_->setPos(qreal(x_), qreal(y_));

                  //textItem_->setPlainText(QString("%1 %2 %3 ").arg(name_).arg(value_).arg(unit_));

                  //QString textNew(QString(
                  //   "<div style='background-color: #ffff00;'>"
                  //   "%1 "
                  //   "</div>"
                  //).arg(name_)
                  //);
                  QString textNew(QString(
                     "<!DOCTYPE html>"
                     "<html>"
                     "<body>"
                     //"<p1 style=\"font-size:%1px; background-color: #ff0000; \">%2 %3 %4 </p1>"
                     //"<p1 style=\"font-size:%1px\">%2 %3 %4 </p1>"
                     //"<p1 style=\"font-size:%1px; background-color: RGB(%2, %3, %4); \">%5 %6 %7 </p1>"
                     //"<p1 style=\"font-size:%1px; background-color: #%2%3%4; \">%5 %6 %7 </p1>"
                     "<p1 style=\"height:170px; font-size:%1px; background-color: #%2%3%4; \">%5 %6 %7 </p1>"
                     "</body>"
                     "</html>"
                  ).arg((int32_t)font_.size).arg(cbackground.red(), 2, 16, QChar('0')).arg(cbackground.green(), 2, 16, QChar('0')).arg(cbackground.blue(), 2, 16, QChar('0')).
                     arg(name_).arg(value_).arg(unit_));
                  textItem_->setHtml(textNew);
               }
               else {
                  textItem_->setPlainText(QString(""));
               }
#else
               if (textItem_->gsaVisible()) {
                  textItem_->setText(QString(""));
                  QString name_(textItem_->name());
                  QString unit_(textItem_->unit());
                  QString value_(QString(""));
                  gsa::controller->Double2String(value_, textItem_->value());
                  textItem_->setText(QString("%1 %2 %3 ").arg(name_).arg(value_).arg(unit_));
                  textItem_->setPos(qreal(x_), qreal(y_));
               }
               else {
                  textItem_->setText(QString(""));
               }
#endif
            }
            else if (dynamic_cast<DialogItemComboBox *>(item.second[i]) != nullptr) {
               DialogItemComboBox *screenItem_(dynamic_cast<DialogItemComboBox *>(item.second[i]));
               screenItem_->setGsaVisible(SetPosition(screenItem_, i, x_, y_, width_, height_));
               if (screenItem_->gsaVisible()) {
                  //screenItem_->setText(QString("")); 
                  QString name_(screenItem_->name()); 
                  //QString unit_(screenItem_->unit()); 
                  //QString value_(QString("")); 
                  //gsa::controller->Double2String(value_, screenItem_->value()); 
                  //screenItem_->setText(QString("%1 %2 %3 ").arg(name_).arg(value_).arg(unit_)); 

                  //screenItem_->setPosition( QPoint(x_, y_+ rectPlot.y()) ); 
                  screenItem_->setPosition( QPoint(x_, y_) ); 

                  gsa::t::Theme *_theme(g_Parameter._theme);
                  std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
                  std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
                  std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
                  std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

                  gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
                  gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

                  for (auto &font : _theme->themeFonts) {
                     if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
                        switch (_fontindexes[std::wstring(font.description)])
                        {
                        case gsa::t::FontIndex::ControlDropDownPanel: font_ = font; break;
                        default: break;
                        }
                     }
                  }
                  for (auto &item : _theme->themeItems) {
                     if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                        switch (_colorindexes[std::wstring(item.description)])
                        {
                        case gsa::t::ColorIndex::ControlDropDownPanel: item_ = item; break;
                        default: break;
                        }
                     }
                  }

                  int r, g, b;
                  _appWidget->GetRgb(item_.value, r, g, b);
                  QColor cbackground(r, g, b);
                  _appWidget->GetRgb(font_.color, r, g, b);
                  QColor cfont(r, g, b);

                  screenItem_->setStyleSheet(QString("%1 "
                     "QWidget { " //"QComboBox { " 
                     "background-color: rgb(%2, %3, %4); "
                     "color: rgb(%5, %6, %7); "
                     "} "
                  //).arg(screenItem_->styleSheet()).arg(127).arg(127).arg(0)
                  ).arg(screenItem_->styleSheet()).arg(cbackground.red()).arg(cbackground.green()).arg(cbackground.blue()).
                     arg(cfont.red()).arg(cfont.green()).arg(cfont.blue())
                  );
               }
               else { 
                  //screenItem_->setText(QString("")); 
               }
            }
         }
      }
   }

   //for (int i = 0; i < _screenBottoms.size(); i++) {
   //   if (_screenBottoms[i] != nullptr) {
   //      SetLocation(_screenBottoms[i], i, _screenBottoms[i]->location(), x_, y_);
   //      _screenBottoms[i]->setPos(qreal(x_), qreal(y_));
   //   }
   //}

   //QRectF plotArea_(_chart->plotArea());

   //if (_leftBottomText != nullptr) {
   //   QRectF _leftBottomRect = _leftBottomText->boundingRect();
   //   qreal _xLeftBottom(plotArea_.x());
   //   qreal _yLeftBottom(plotArea_.y() + plotArea_.height() + plotArea_.height() / 32);
   //   _leftBottomText->setPos(qreal(_xLeftBottom), qreal(_yLeftBottom));
   //}

   //if (_rightBottomText != nullptr) {
   //   QRectF _rightBottomRect = _rightBottomText->boundingRect();
   //   qreal _xRightBottom(plotArea_.x() + plotArea_.width() - _rightBottomRect.width());
   //   qreal _yRightBottom(plotArea_.y() + plotArea_.height() + plotArea_.height() / 32);
   //   _rightBottomText->setPos(qreal(_xRightBottom), qreal(_yRightBottom));
   //}

   //QPolygonF _poly3 = _leftBottomText->mapFromScene(_rect2);
   //QPolygonF _poly4 = _leftBottomText->mapToScene(_rect2);

   /*
   QRect l_Rect;
   QSize l_Size;
   QSizeF l_Sizef;
   l_Rect = m_GLWidget->geometry();
   l_Size = m_GLWidget->size();
   l_Size = m_GLWidget->maximumSize();
   l_Size = m_GLWidget->minimumSize();
   l_Sizef = _chart->preferredSize();
   l_Sizef = _chart->size();
   l_Sizef = _chart->maximumSize();
   l_Sizef = _chart->minimumSize();
   */
}

void MainScreen::resizeEvent(QResizeEvent * event)
{
   Q_UNUSED(event)

   if (_chartView == nullptr || _chart == nullptr) return;

   QSize size1_ = event->size();
   QSize size2_ = size();

   QDesktopWidget *mydesk = QApplication::desktop();
   QSize size2 = mydesk->size();

   QSize size3 = size();
   QSize size4 = _chartView->size();
   QSizeF size5 = _chart->size();
   QSizeF size6 = _chart->plotArea().size();

   //QSize size3 = _chartView->size();
   //QSize size4 = _mainScreen->size();
}

void MainScreen::moveEvent(QMoveEvent * event) 
{ 
   Q_UNUSED(event)

   if (_chartView == nullptr || _chart == nullptr) return;

   //QSize size1_ = event->size(); 
   QSize size2_ = size(); 

   QDesktopWidget *mydesk = QApplication::desktop();
   QSize size2 = mydesk->size(); 

   QSize size3 = size();
   QSize size4 = _chartView->size();
   QSizeF size5 = _chart->size();
   QSizeF size6 = _chart->plotArea().size();

   //QSize size3 = _chartView->size(); 
   //QSize size4 = _mainScreen->size(); 
} 

void MainScreen::changeData(int item, double value)
{
   //_mainScreen->changeData(item, value);
   int i(0);
}

void MainScreen::slotPutCurrentData(int m_Period, int index, int length)
{
   //QMutexLocker locker(&mutex);

   DWORD id = GetCurrentThreadId();

   int counter(0);
   //int indexMarker(index-7);
   //QVector <QPointF> *m_Vector(_vectors[0]);
   QLineSeries *m_series(nullptr);
   //QAbstractSeries *m_series(nullptr);
   QVector <QPointF> vector2_[2];

   if (_chartView->stop()) {
      _semaphore.release();
      return;
   }

   if (!(index < Main::_numberTrace)) {
      _semaphore.release();
      return;
   }

   if (index == 0) {
      for (int i = 0; i < Main::_numberTrace; i++) {
         vector_[i].clear();
      }
   }

   //if (m_values == nullptr) {
   //   m_values = new gsa::t::XYValue[gsa::t::maxPoint];
   //}
   //else
   //{

   if (_arrayseries.size() == 0 ) { // || _vectors.size() == 0) {
      _semaphore.release();
      return;
   }
   //else {
      //if (index == 1) {
      //   int i(0);
      //}

      //QMap<int, QLineSeries *>::iterator it = _arrayseries.find(index);
      //if (it == _arrayseries.end())
      //{
      //   switch (_data->Type)
      //   {
      //   case gsa::t::Carret:
      //   {
      //      int i(0);
      //      break;
      //   }
      //   case gsa::t::Polyline:
      //   {   //
      //      //initArray(&m_series, &m_Vector, index);
      //      //QObject::connect(m_series, SIGNAL(pointsReplaced()), SLOT(Updated()));
      //      //___series___ = m_series;
      //      ////m_series->setUseOpenGL(true);

      //      ////l_ViewList = _chart->scene()->views();
      //      ////l_GLList = l_ViewList[0]->findChildren<QOpenGLWidget *>();
      //      ////m_GLWidget = l_GLList[0];
      //      ////QObject::connect(m_GLWidget, SIGNAL(frameSwapped()), SLOT(Swaped()));
      //      ////QObject::connect(m_GLWidget, SIGNAL(resized()), SLOT(Sized()));
      //      break;
      //   }
      //   case gsa::t::Lines:
      //   {
      //      int i(0);
      //      break;
      //   }
      //   case gsa::t::Marker:
      //   {
      //      int i(0);
      //      break;
      //   }
      //   }
      //}
      //else {
      //   m_series = _arrayseries[index];
      //   m_Vector = _vectors[index];
      //}
   //}

   m_series = dynamic_cast<QLineSeries *>(_arrayseries[index]);
   //m_Vector = _vectors[index];

   //switch (_data->Type)
   //{
   //case gsa::t::Polyline:
   //{
   //   int i(0);
   //   break;
   //}
   //case gsa::t::Lines:
   //{
   //   int i(0);
   //   break;
   //}
   //case gsa::t::Carret:
   //{
   //   m_series = _carrigeSeries;
   //   break;
   //}
   //case gsa::t::Marker:
   //{
   //   //m_series = _markerSeries;

   //   QMap<int, QLineSeries *>::iterator it = _markerseries.find(indexMarker);
   //   if (it == _markerseries.end())
   //   {
   //      m_series = nullptr;
   //      m_Vector = nullptr;
   //   }
   //   else {
   //      m_series = _markerseries[indexMarker];
   //      m_Vector = _markervectors[indexMarker];
   //   }

   //   break;
   //}
   //}

   //if (m_Vector == nullptr || m_series == nullptr) {
   //if (m_series == nullptr) {
   if (_arrayseries[index] == nullptr) {
      _semaphore.release();
      return;
   }

   m_Blinker = (m_Blinker + 1) % (1000000 / m_Period);

   //if ((*m_Vector).size() == gsa::t::maxPoint) {
   //   for (counter = 0; counter < gsa::t::maxPoint; counter++)
   //      //for (counter = 0; counter < _data->Length; counter++) 
   //   {
   //      if (counter < _data->Length) {
   //         (*m_Vector)[counter].setX(_data->Values[counter].XValue);
   //      }
   //      else {
   //         //(*m_Vector)[counter].setX(std::numeric_limits<double>::max()); 
   //         //(*m_Vector)[counter].setX(DBL_MAX); 
   //         (*m_Vector)[counter].setX(_xmax);
   //      }

   //      //if (_data->Values[counter].YValue == std::numeric_limits<double>::infinity()) {
   //      //   int i(0);
   //      //}
   //      //if (std::isnan(_data->Values[counter].YValue)) {
   //      //   break;
   //      //   (*m_Vector)[counter].setY(_ymin);
   //      //   int i(0);
   //      //}
   //      //else {
   //      //   (*m_Vector)[counter].setY(_data->Values[counter].YValue);
   //      //}
   //      (*m_Vector)[counter].setY(_data->Values[counter].YValue);
   //   }
   //}

   //QString str(QString("INFO0077 %1[%2]%3 this = %4 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this, 0, 16));
   //qInfo(str.toStdString().c_str());

   switch (_data->Type)
   {
   case gsa::t::Disabled:
   {
      //break;

      if (index == length - 1) {
         int i(0);
      }

      if (index == 0) {
         int i(0);
      }
      if (_updated.find(m_series) != _updated.end()) {
         if (_updated[m_series]) {
            _updated[m_series] = false;

            //if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) == nullptr) {

#ifdef HTML_TEXT
            _anyTextes[index]->setPlainText("");
#else
            _markerTextes[index]->setText("");
#endif

            _freqTextes[index]->setText("");
            _valueTextes[index]->setText("");

            //}

            //QVector<QPointF> vector_;
            //vector_[index].clear();
            //m_series->replace(vector_);
            if (index - _offsetIndexMarker >= 0 && index - _offsetIndexMarker < 6) {
               QString text = QString("");
               QColor color = QColor(0, 0, 0);
               emit signalSetMarker(index - _offsetIndexMarker, text, color);
            }
         }
      }
      int i(0);
      break;
   }
   case gsa::t::Polyline:
   {
      //break;

      if (_axisLog) {
         int i(0);
      }

      if (index == 0) {
         int i(0);
         //break;
      }

      if (_updated.find(m_series) != _updated.end()) {
         if (_updated[m_series]) {
            m_Skiped = 0;
            m_Position = (m_Position + 1) % gsa::t::maxPoint;

            //QVector<QPointF> vector_;
            qreal xmin(_xmin);
            qreal xmax(_xmax);
            qreal ymin(_ymin);
            qreal ymax(_ymax);
            bool stop(false);
            bool axisLog(_axisLog);

            int j(0);

            //if (_data->Values[0].XValue == std::numeric_limits<double>::infinity())

            //QString str(QString("INFO007 %1[%2]%3 this=%4 y=%5 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this).arg(_data->Values[0].YValue, 0, 'f'));
            //qInfo(str.toStdString().c_str());

            QPointF point;
            for (counter = 0; counter < _data->Length; counter++)
               //for (counter = 0; counter < gsa::t::maxPoint; counter++)
            {
               //if (counter < _data->Length) {

               if (_data->Values[counter].XValue < xmin)
                  _data->Values[counter].XValue = xmin;
               if (_data->Values[counter].XValue > xmax)
                  _data->Values[counter].XValue = xmax;
               if (_data->Values[counter].YValue < ymin)
                  _data->Values[counter].YValue = ymin;
               if (_data->Values[counter].YValue > ymax)
                  _data->Values[counter].YValue = ymax;

               if (axisLog) {
                  _data->Values[counter].YValue <= 0.0 ? _data->Values[counter].YValue = 10e-300 : _data->Values[counter].YValue;
               }

               point.setX(_data->Values[counter].XValue);
               point.setY(_data->Values[counter].YValue);
               vector_[index].push_back(point);

               //}
            }

            //for_each_if((*m_Vector).begin(), (*m_Vector).end(),
            //   [&stop](QPointF &point)
            //   {
            //      if (stop || std::isnan(point.y()) || point.y() == std::numeric_limits<double>::infinity()) {
            //         stop = true;
            //         return false;
            //      }
            //      else {
            //         return true;
            //      }
            //   },
            //   [&vector_, xmin, xmax, ymin, ymax, axisLog](QPointF &point)
            //   {
            //      //if (point.y() < ymin || point.y() > ymax) {
            //      //   int i(0);
            //      //}
            //      //double p1 = std::numeric_limits<double>::infinity();
            //      //double p2 = std::numeric_limits<double>::max();

            //      if (point.x() < xmin)
            //         point.setX(xmin - 1.0);
            //      if (point.x() > xmax)
            //         point.setX(xmax + 1.0);
            //      if (point.y() < ymin)
            //         point.setY(ymin);
            //      if (point.y() > ymax)
            //         point.setY(ymax);

            //      point.x() < xmin ? point.setX(xmin) : point;
            //      point.x() > xmax ? point.setX(xmax) : point;
            //      point.y() < ymin ? point.setY(ymin) : point;
            //      point.y() > ymax ? point.setY(ymax) : point;

            //      if (axisLog) {
            //         point.y() <= 0.0 ? point.setY(10e-300) : point;
            //      }

            //      vector_.push_back(point);
            //   }
            //);

            //std::for_each((*m_Vector).begin(), (*m_Vector).end(), [&vector_, xmin, xmax, ymin, ymax, counter](QPointF &point)
            //{
            //   if (point.y() < ymin || point.y() > ymax) {
            //      int i(0);
            //   }
            //   if (point.x() < xmin) 
            //      point.setX(xmin - 1.0) ;
            //   if (point.x() > xmax) 
            //      point.setX(xmax + 1.0) ;
            //   if (point.y() < ymin) 
            //      point.setY(ymin) ;
            //   if (point.y() > ymax) 
            //      point.setY(ymax) ;

            //   point.x() < xmin ? point.setX(xmin) : point;
            //   point.x() > xmax ? point.setX(xmax) : point;
            //   point.y() < ymin ? point.setY(ymin) : point;
            //   point.y() > ymax ? point.setY(ymax) : point;

            //   vector_.push_back(point);
            //   if (vector_.length() == counter) 
            //      return;
            //});

            _updated[m_series] = false;

            if (index == 1) {
               int i(0);
            }

            //if (_data->Values[0].Colour.Red == 0 && _data->Values[0].Colour.Green == 0 && _data->Values[0].Colour.Blue == 0) {
            //   int i(0);
            //}
            m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //m_series->replace(vector_[index]);

            //if (m_bSkUpdated)
            //{
            //   m_SkipedSeries->replace(*m_SkipedVector);
            //   m_bSkUpdated = false;
            //}
            //if (m_bPeriodUpdated)
            //{
            //   m_PeriodSeries->replace(*m_PeriodVector);
            //   m_bPeriodUpdated = false;
            //}
         }
         else
         {
            counter = 0;
            m_Skiped++;
         }
      }
      break;
   }
   case gsa::t::Lines:
   {
      //break;

      int i(0);
      break;
   }
   case gsa::t::Carret:
   {
      //break;

      if (_data->Values[0].XValue == std::numeric_limits<double>::infinity())
         break;

      //if (_updated.find(_carrigeSeries) != _updated.end()) {
      //   if (_updated[_carrigeSeries]) {

      if (_updated.find(m_series) != _updated.end()) {
         if (_updated[m_series]) {
            //QVector <QPointF> vector_;
            QPointF point_;
            //qreal xval((*m_Vector)[0].x());
            qreal xval(_data->Values[0].XValue);
            qreal yvald_(_ymin);
            //qreal yvalu_((_ymin + _ymin*0.05));
            //qreal yvalu_((_ymin + _ymin*((_ymax-_ymin)/200.0)));
            qreal yvalu_(_ymin + (_ymax - _ymin) / 100.0);
            qreal yvalm_(_ymax);
            qreal step_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));

            if (_axisLog)
               yvalu_ = _ymin + (_ymax - _ymin) / 10000.0;

            QVector <qreal> xvals = { xval - step_, xval, xval, xval, xval + step_ };
            QVector <qreal> yvals = { yvald_, yvalu_, yvalm_, yvalu_, yvald_ };
            for (int i = 0; i < xvals.size(); i++) {
               point_.setX(xvals[i]);
               point_.setY(yvals[i]);
               vector_[index].push_back(point_);
            }
            _updated[m_series] = false;
            m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //m_series->replace(vector_[index]);
         }
      }

      break;
   }
   case gsa::t::VerticalLine:
   {
      //break;

      if (_data->Values[0].XValue == std::numeric_limits<double>::infinity()) {
         int i(0);
         break;
      }
      else {
         int i(0);
         if (_updated.find(m_series) != _updated.end()) {
            if (_updated[m_series]) {
               //QVector <QPointF> vector_;
               QPointF point_;
               //qreal xval((*m_Vector)[0].x());
               qreal xval(_data->Values[0].XValue);
               qreal yvald_(_ymin);
               qreal yvalu_(_ymax);
               //qreal step_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));

               if (_axisLog)
                  yvalu_ = _ymin + (_ymax - _ymin) / 10000.0;

               QVector <qreal> xvals = { xval, xval };
               QVector <qreal> yvals = { yvald_, yvalu_ };
               for (int i = 0; i < xvals.size(); i++) {
                  point_.setX(xvals[i]);
                  point_.setY(yvals[i]);
                  vector_[index].push_back(point_);
               }
               _updated[m_series] = false;
               m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
               //m_series->replace(vector_[index]);
            }
         }

         break;
      }

      break;
   }
   case gsa::t::HorisontalLine:
   {
      //break;

      if (_data->Values[0].YValue == std::numeric_limits<double>::infinity()) {
         int i(0);
         break;
      }
      else {
         int i(0);
         if (_updated.find(m_series) != _updated.end()) {
            if (_updated[m_series]) {
               //QVector <QPointF> vector_;
               QPointF point_;
               //qreal yval((*m_Vector)[0].y());
               qreal yval(_data->Values[0].YValue);
               qreal xvall_(_xmin);
               qreal xvalr_(_xmax);
               //qreal step_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));

               QVector <qreal> xvals = { xvall_, xvalr_ };
               QVector <qreal> yvals = { yval, yval };
               for (int i = 0; i < xvals.size(); i++) {
                  point_.setX(xvals[i]);
                  point_.setY(yvals[i]);
                  vector_[index].push_back(point_);
               }
               _updated[m_series] = false;
               m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
               //m_series->replace(vector_[index]);
            }
         }

         break;
      }

      break;
   }

   case gsa::t::Marker:
   {
      //__TestHtmlText(index);
      //break;

      if (index == 1) {
         int i(0);
      }
      if (_data->Values[0].XValue == std::numeric_limits<double>::infinity()) {
         int i(0);
         break;
      }

      //if (_updated.find(_markerSeries) != _updated.end()) {
      //   if (_updated[_markerSeries]) {

      //if (_updated.find(_markerseries[indexMarker]) != _updated.end()) {
      //   if (_updated[_markerseries[indexMarker]]) {

      gsa::t::Theme *_theme(g_Parameter._theme);
      std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
      std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
      std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
      std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeFont fontInactive_(themeFont); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::ActiveMarker: //Tabs of the selected menu(name of the subcomposition)
            {
               font_ = font;
               break;
            }
            case gsa::t::FontIndex::InactiveMarker: //Tabs of the selected menu(name of the subcomposition)
            {
               fontInactive_ = font;
               break;
            }
            default:
               break;
            }
         }
      }

      int r, g, b;
      _appWidget->GetRgb(font_.color, r, g, b);
      QColor cfont_(r, g, b);

      int weight;
      if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal;
      else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold;
      QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);

      qfont_.setPixelSize(52);
      qfont_.setPointSize(52);
      uint32_t _pixelsize = qfont_.pixelSize();
      uint32_t _pointsize = qfont_.pointSize();

      //__TestHtmlText(index);
      //break;

      if (_updated.find(m_series) != _updated.end()) {
         if (_updated[m_series]) {
            if (_data->Values[0].YValue == std::numeric_limits<double>::infinity()) {
               _data->Values[0].YValue = _ymax;
            }
            if (isnan(_data->Values[0].YValue)) {
               _data->Values[0].YValue = _ymax;
            }

            if (_data->Values[0].XValue == std::numeric_limits<double>::infinity()) {
               _data->Values[0].XValue = _xmax;
            }
            if (isnan(_data->Values[0].XValue)) {
               _data->Values[0].XValue = _xmax;
            }

            //QVector <QPointF> vector_;
            QPointF point_;

            qreal xval(_data->Values[0].XValue);
            qreal yval(_data->Values[0].YValue);
            //qreal xval((_xmax - _xmin) / 2);
            //qreal yval((_ymax - _ymin)/2);

            xval < _xmin ? xval = _xmin : xval;
            xval > _xmax ? xval = _xmax : xval;
            yval < _ymin ? yval = _ymin : yval;
            yval > _ymax ? yval = _ymax : yval;

            qreal xstep_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));
            qreal ystep_((_ymax - _ymin) / (100.0));

            if (_axisLog)
               ystep_ = (_ymax - _ymin) / (3000.0);

            xval - xstep_ <= _xmin ? xval = xstep_ + _xmin : xval;
            //yval - ystep_ <= _ymin ? yval = ystep_ + 10e-300 : yval;
            yval - ystep_ <= _ymin ? yval = ystep_ + _ymin : yval;
            QVector <qreal> xvals = { xval - xstep_, xval, xval + xstep_, xval, xval - xstep_ };
            QVector <qreal> yvals = { yval, yval + ystep_, yval, yval - ystep_, yval };
            //QVector <qreal> xvals = { 400000.0, 500000.0, 600000.0, 500000.0, 400000.0 };
            //QVector <qreal> yvals = { 4, 6, 4, 2, 4 };
            //QVector <qreal> xvals = { _xmin*2, _xmin*3, _xmin*4, _xmin*5, _xmin*6 };
            //QVector <qreal> yvals = { _ymin*2, _ymin*3, _ymin*4, _ymin*5, _ymin*6 };
            for (int i = 0; i < xvals.size(); i++) {
               point_.setX(xvals[i]);
               point_.setY(yvals[i]);
               vector_[index].push_back(point_);
            }

            //if ((*m_Vector)[1].y() != std::numeric_limits<double>::infinity()) {
            if (_data->Values[1].YValue != std::numeric_limits<double>::infinity()) {
               //qreal xval((*m_Vector)[1].x());
               //qreal yval((*m_Vector)[1].y());
               qreal xval(_data->Values[1].XValue);
               qreal yval(_data->Values[1].YValue);

               xval < _xmin ? xval = _xmin : xval;
               xval > _xmax ? xval = _xmax : xval;
               yval < _ymin ? yval = _ymin : yval;
               yval > _ymax ? yval = _ymax : yval;

               qreal xstep_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));
               qreal ystep_((_ymax - _ymin) / (100.0));

               if (_axisLog)
                  ystep_ = (_ymax - _ymin) / (3000.0);

               xval - xstep_ <= 0 ? xval = xstep_ : xval;
               yval - ystep_ <= 0 ? yval = ystep_ + 10e-300 : yval;
               QVector <qreal> xvals = { xval - xstep_, xval, xval + xstep_, xval, xval - xstep_ };
               QVector <qreal> yvals = { yval, yval + ystep_, yval, yval - ystep_, yval };
               for (int i = 0; i < xvals.size(); i++) {
                  point_.setX(xvals[i]);
                  point_.setY(yvals[i]);
                  vector_[index].push_back(point_);
               }
            }

            //qreal ymax(0.0), ymin(0.0);
            //qreal xmax(0.0), xmin(0.0);

            //QVector <QPointF>::iterator it_max = std::max_element(vector_.begin(), vector_.end(), [](QPointF point1, QPointF point2) {return point1.y() < point2.y(); });
            //QVector <QPointF>::iterator it_min = std::min_element(vector_.begin(), vector_.end(), [](QPointF point1, QPointF point2) {return point1.y() < point2.y(); });
            //if (it_max != vector_.end() && it_min != vector_.end()) {
            //   ymax = it_max->y();
            //   ymin = it_min->y();
            //}

            //QVector <QPointF>::iterator it_xmax = std::max_element(vector_.begin(), vector_.end(), [](QPointF point1, QPointF point2) {return point1.x() < point2.x(); });
            //QVector <QPointF>::iterator it_xmin = std::min_element(vector_.begin(), vector_.end(), [](QPointF point1, QPointF point2) {return point1.x() < point2.x(); });
            //if (it_max != vector_.end() && it_min != vector_.end()) {
            //   xmax = it_max->x();
            //   xmin = it_min->x();
            //}

            _updated[m_series] = false; 
            //m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            m_series->setColor(cfont_);

            //m_series->replace(vector_[index]); 

            //__TestHtmlText(index);
            //break;

#ifdef HTML_TEXT
            if (_anyTextes[index] != nullptr)
#else
            if (_markerTextes[index] != nullptr)
#endif
            { 
               //_anyTextes[index]->setText(QString("%1 %2 ").arg(xval, 0, 'f').arg(" Hz"));
               //QString dimension = QString("%1(%2)").arg(QString::fromWCharArray(m_CurrentStyle.XAxisName)).arg(QString::fromWCharArray(m_CurrentStyle.XAxisUnit));
               //QString dimension = QString("%1 %2").arg(xval, 0, 'f').arg(QString::fromWCharArray(m_CurrentStyle.XAxisUnit));

               //index - _offsetIndexMarker
               //QString dimension = QString("%1 %2").arg((long)xval).arg(QString::fromWCharArray(m_CurrentStyle.XAxisUnit));
               //_anyTextes[index]->setBrush(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));

               QString dimension = QString("%1").arg((long)index - _offsetIndexMarker);

#ifdef HTML_TEXT
               _anyTextes[index]->setDefaultTextColor(cfont_);

               QString textNew(QString(
                  "<!DOCTYPE html>"
                  "<html>"
                  "<body>"
                  "<p1 style=\"font-size:%1px\">%2</p1>"
                  "</body>"
                  "</html>"
               ).arg((int32_t)font_.size).arg(dimension));
               _anyTextes[index]->setHtml(textNew);
               //_anyTextes[index]->setPlainText(dimension);
#else
               _markerTextes[index]->setFont(qfont_);
               //uint32_t _size1 = _anyTextes[index]->font().pixelSize();
               //uint32_t _size2 = _anyTextes[index]->font().pointSize();
               //uint32_t _size3 = qfont_.pixelSize();
               _markerTextes[index]->setBrush(cfont_);
               _markerTextes[index]->setText(dimension);
#endif

               qreal xoffset(0.0);
               if ((xval - _xmin) / (_xmax - _xmin) > 0.8) {
                  xoffset = -160.0;
               }
               else {
                  xoffset = 70.0;
               }

               qreal width = (qreal)_chartView->size().width() - 70.0;
               qreal height = (qreal)_chartView->size().height() - 80.0;
               qreal iwidth = (width * ((xval - _xmin) / (_xmax - _xmin))) + xoffset;
               qreal iheight = (height - height * ((yval - _ymin) / (_ymax - _ymin))); //+80.0);

#ifdef HTML_TEXT
               _anyTextes[index]->setPos(iwidth, iheight);
#else
               //_markerTextes[index]->setZValue(100.0);
               //qreal zvalue = _markerTextes[index]->zValue();

               _markerTextes[index]->setPos(iwidth, iheight);
               //_markerTextes[index]->setFont(qfont_);
#endif

               //_chartView->keepCallout();
            }
            else {
               int i(0);
            }

            //if (_freqTextes[index] != nullptr) {
            //   //_freqText->setFont(QFont("lucida", 14)); //, QFont::Bold));
            //   _freqTextes[index]->setText(QString("freq: %1 %2 ").arg(xval, 10, 'f').arg(" Hz"));
            //   _freqTextes[index]->setBrush(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //}
            //if (_valueTextes[index] != nullptr) {
            //   //_valueText->setFont(QFont("lucida", 14)); //, QFont::Bold));
            //   _valueTextes[index]->setText(QString("val: %1 %2 ").arg(yval, 10, 'f').arg(" mV"));
            //   _valueTextes[index]->setBrush(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //}

            //QString text = QString("freq: %1 %2  :  val: %3 %4 ").arg(xval, 10, 'f').arg(" Hz").arg(yval, 10, 'f').arg(" mV");
            QString text = QString("[%1] %6: %2 %3  :  %7: %4 %5 ").arg((long)(index - _offsetIndexMarker)).
               arg(xval, 10, 'f').arg(QString::fromStdWString(m_CurrentStyle.XAxisUnit)).
               arg(yval, 10, 'f').arg(QString::fromStdWString(m_CurrentStyle.YAxisUnit)).arg(QString::fromStdWString(m_CurrentStyle.XAxisName)).arg(QString::fromStdWString(m_CurrentStyle.YAxisName));

            QColor color = QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue);

            emit signalSetMarker(index - _offsetIndexMarker, text, color);
         }
      }
      break;
   }
   case gsa::t::SpanPower:
   {
      //break;

      index;
      length;
      _updated[m_series];

      if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index]) != nullptr)
      {
         //int i(0);

         m_series = dynamic_cast<QLineSeries *>(_arrayseries[index]);

         qreal xval11(_data->Values[0].XValue);
         qreal xval12(_data->Values[1].XValue);
         qreal yval11(_data->Values[0].YValue);
         qreal yval12(_data->Values[1].YValue);

         QPointF point_;
         //qreal xval1(16500.0 - 300.0);
         //qreal xval2(16500.0 + 300.0);
         qreal xval1(_data->Values[0].XValue);
         qreal xval2(_data->Values[1].XValue);

         const qreal xstep_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));
         const qreal ystep_((_ymax - _ymin) / (50.0));
         qreal yvald_(_ymin);
         qreal yvalu_(_ymin + (_ymax - _ymin) / 50.0);
         qreal yvalm_(_ymax - ystep_);

         if (_axisLog)
            yvalu_ = _ymin + (_ymax - _ymin) / 10000.0;

         //                        1      2      3      4      5               6      7               8 
         QVector <qreal> xvals = { xval1, xval1, xval1, xval1, xval1 + xstep_, xval1, xval1 + xstep_, xval1,
            //                        9      10     11     12              13     14              15     16 
                                      xval2, xval2, xval2, xval2 - xstep_, xval2, xval2 - xstep_, xval2, xval2 };
         QVector <qreal> yvals = { yvald_, yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ - ystep_, yvalm_,
                                   yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ - ystep_, yvalm_, yvald_ };

         vector_[index].clear();

         for (int j = 0; j < xvals.size(); j++) {
            point_.setX(xvals[j]);
            point_.setY(yvals[j]);
            vector_[index].push_back(point_);
         }
         _updated[m_series] = false;
         //m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
         //m_series->setColor(QColor(0, 0, 255));
         m_series->setColor(QColor(255, 255, 255, 64));

         QPen pen(QColor(255, 255, 255, 64));
         //pen.setWidth(1);
         m_series->setPen(pen);

         qreal xoffset(0.0);
         qreal yoffset(0.0);
         if ((xval1 - _xmin) / (_xmax - _xmin) > 0.8) {
            xoffset = -160.0;
         }
         else {
            xoffset = 70.0;
         }
         xoffset = 150.0;
         yoffset = 75.0;

         qreal width = (qreal)_chartView->size().width();
         qreal height = (qreal)_chartView->size().height();
         QPoint point2_ = _chartView->pos();
         QRect rect_ = _chartView->geometry();

         xoffset = width / 100;
         yoffset = 0; // height / 10; 
         //qreal iwidth = (width * ((xval1 - _xmin) / (_xmax - _xmin))) + xoffset; 
         //qreal iwidth = (width * ((xval2 - xval1) / (_xmax - _xmin))) - xoffset; 
         qreal iwidth = width / 2 - xoffset;
         //qreal iheight = (height - (height * ((yvalm_ - _ymin) / (_ymax - _ymin)) - yoffset)); 
         //qreal iheight = (height - (height * ((yvalm_ - _ymin) / (_ymax - _ymin)))) + yoffset; 
         qreal iheight = (height - (height * ((_data->Values[0].YValue - _ymin) / (_ymax - _ymin)))) - yoffset;

#ifdef HTML_TEXT
         if (_anyTextes[index] != nullptr)
         {
            //_data->Values[0].YValue;
            //QString dimension = QString("-48.13 dBm").arg(_data->Values[0].YValue, 5, 'f', 2, '0');
            QString dimension = QString("%1 %2").arg(_data->Values[0].YValue, 5, 'f', 2, '0').arg(QString::fromWCharArray(m_CurrentStyle.YAxisUnit));
            //_markerTextes[index]->setText(dimension);
            _anyTextes[index]->setPlainText(dimension);

            //_anyTextes[index]->setBrush(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //_anyTextes[index]->setBrush(QColor(0, 0, 255));
            QColor color_(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue);
            //_markerTextes[index]->setBrush(color_);
            _anyTextes[index]->setDefaultTextColor(color_);

            //_markerTextes[index]->setPos(iwidth, iheight);
            _anyTextes[index]->setPos(iwidth, iheight);
         }
#else
         if (_markerTextes[index] != nullptr)
         {
            //_data->Values[0].YValue;
            //QString dimension = QString("-48.13 dBm").arg(_data->Values[0].YValue, 5, 'f', 2, '0');
            QString dimension = QString("%1 %2").arg(_data->Values[0].YValue, 5, 'f', 2, '0').arg(QString::fromWCharArray(m_CurrentStyle.YAxisUnit));
            _markerTextes[index]->setText(dimension);

            //_anyTextes[index]->setBrush(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //_anyTextes[index]->setBrush(QColor(0, 0, 255));
            QColor color_(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue);
            _markerTextes[index]->setBrush(color_);

            _markerTextes[index]->setPos(iwidth, iheight);
         }
#endif

         else {
            int i(0);
         }

         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries() != nullptr) {
            QVector <qreal> xvals1 = { xval1, xval2 };
            QVector <qreal> yvals1 = { yvald_, yvald_ };
            //QVector <qreal> yvals2 = { yvalm_ / 2, yvalm_ / 2 };
            QVector <qreal> yvals2 = { _data->Values[0].YValue, _data->Values[0].YValue };

            //areaSeries_->setBrush(gradient);
            QColor color_(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue, 64);
            dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries()->setBrush(color_);

            //QVector <QPointF> vector2_[2];
            for (int j = 0; j < xvals1.size(); j++) {
               point_.setX(xvals1[j]);
               point_.setY(yvals1[j]);
               vector2_[0].push_back(point_);

               point_.setY(yvals2[j]);
               vector2_[1].push_back(point_);
            }
            ////dynamic_cast<QAreaSeries *>(_arrayseries[index])->lowerSeries()->replace(vector2_[0]);
            ////dynamic_cast<QAreaSeries *>(_arrayseries[index])->upperSeries()->replace(vector2_[1]);
            ////dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries()->lowerSeries();
            //dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries()->lowerSeries()->replace(vector2_[0]);
            //dynamic_cast<PowerSpanSeries *>(_arrayseries[index])->areaSeries()->upperSeries()->replace(vector2_[1]);
         }
      }

      break;
   }
   }
   //}

   if (index == length - 1)
   {
#ifdef HTML_TEXT
      if (_anyTextes.size() > length) {
         for (int i = length; i < _anyTextes.size(); i++) {
            _anyTextes[i]->setPlainText("");
            _freqTextes[i]->setText("");
            _valueTextes[i]->setText("");
         }
      }
#else
      if (_markerTextes.size() > length) {
         for (int i = length; i < _markerTextes.size(); i++) {
            _markerTextes[i]->setText("");
            _freqTextes[i]->setText("");
            _valueTextes[i]->setText("");
      }
   }
#endif

      int j(0);
      for (int i = 0; i < length; i++) 
      {
         if (dynamic_cast<PowerSpanSeries *>(_arrayseries[i]) != nullptr) 
         {
            //m_series = dynamic_cast<QLineSeries *>(_arrayseries[i]);

            //QPointF point_;
            //qreal xval1(16500.0 - 300.0);
            //qreal xval2(16500.0 + 300.0);

            //const qreal xstep_((_xmax - _xmin) / (gsa::t::maxPoint / 10.0));
            //const qreal ystep_((_ymax - _ymin) / (100.0));
            //qreal yvald_(_ymin);
            //qreal yvalu_(_ymin + (_ymax - _ymin) / 100.0);
            //qreal yvalm_(_ymax - ystep_);

            //if (_axisLog)
            //   yvalu_ = _ymin + (_ymax - _ymin) / 10000.0;

            ////                        1      2      3      4      5               6      7               8 
            //QVector <qreal> xvals = { xval1, xval1, xval1, xval1, xval1 + xstep_, xval1, xval1 + xstep_, xval1,
            //   //                        9      10     11     12              13     14              15     16 
            //                             xval2, xval2, xval2, xval2 - xstep_, xval2, xval2 - xstep_, xval2, xval2 };
            //QVector <qreal> yvals = { yvald_, yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ - ystep_, yvalm_,
            //                          yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ + ystep_, yvalm_, yvalm_ - ystep_, yvalm_, yvald_ };

            //vector_[i].clear();

            //for (int j = 0; j < xvals.size(); j++) {
            //   point_.setX(xvals[j]);
            //   point_.setY(yvals[j]);
            //   vector_[i].push_back(point_);
            //}
            //_updated[m_series] = false;
            ////m_series->setColor(QColor(_data->Values[0].Colour.Red, _data->Values[0].Colour.Green, _data->Values[0].Colour.Blue));
            //m_series->setColor(QColor(0, 0, 255));

            dynamic_cast<QLineSeries *>(_arrayseries[i])->replace(vector_[i]);

            if (dynamic_cast<PowerSpanSeries *>(_arrayseries[i])->areaSeries() != nullptr) {
               //QVector <qreal> xvals1 = { xval1, xval2 };
               //QVector <qreal> yvals1 = { yvald_, yvald_ };
               //QVector <qreal> yvals2 = { yvalm_ / 2, yvalm_ / 2 };

               //QVector <QPointF> vector2_[2];
               //for (int j = 0; j < xvals1.size(); j++) {
               //   point_.setX(xvals1[j]);
               //   point_.setY(yvals1[j]);
               //   vector2_[0].push_back(point_);

               //   point_.setY(yvals2[j]);
               //   vector2_[1].push_back(point_);
               //}
               ////dynamic_cast<QAreaSeries *>(_arrayseries[i])->lowerSeries()->replace(vector2_[0]);
               ////dynamic_cast<QAreaSeries *>(_arrayseries[i])->upperSeries()->replace(vector2_[1]);
               ////dynamic_cast<PowerSpanSeries *>(_arrayseries[i])->areaSeries()->lowerSeries();
               dynamic_cast<PowerSpanSeries *>(_arrayseries[i])->areaSeries()->lowerSeries()->replace(vector2_[0]);
               dynamic_cast<PowerSpanSeries *>(_arrayseries[i])->areaSeries()->upperSeries()->replace(vector2_[1]);
            }
         }
         else if (dynamic_cast<QLineSeries *>(_arrayseries[i]) != nullptr) {
            dynamic_cast<QLineSeries *>(_arrayseries[i])->replace(vector_[i]);
         }
         //else if (dynamic_cast<QAreaSeries *>(_arrayseries[i]) != nullptr) {
         //   QVector <qreal> xvals1 = { xval1, xval2 };
         //   QVector <qreal> yvals1 = { yvald_, yvald_ };
         //   QVector <qreal> yvals2 = { yvalm_ / 2, yvalm_ / 2 };

         //   QVector <QPointF> vector2_[2];
         //   for (int j = 0; j < xvals1.size(); j++) {
         //      point_.setX(xvals1[j]);
         //      point_.setY(yvals1[j]);
         //      vector2_[0].push_back(point_);

         //      point_.setY(yvals2[j]);
         //      vector2_[1].push_back(point_);
         //   }
         //   dynamic_cast<QAreaSeries *>(_arrayseries[i])->lowerSeries()->replace(vector2_[0]);
         //   dynamic_cast<QAreaSeries *>(_arrayseries[i])->upperSeries()->replace(vector2_[1]);
         //}
         else if (dynamic_cast<PowerSpanSeries *>(_arrayseries[i]) != nullptr) {
            if (dynamic_cast<PowerSpanSeries *>(_arrayseries[i])->areaSeries() != nullptr) {
            }
         }
      }
   }

   _semaphore.release();
}

void MainScreen::__TestHtmlText(int32_t index)
{
#ifdef HTML_TEXT
   QString dimension = QString("%1").arg("Font54"); 
   //_anyTextes[index]->setText(dimension);
   //_anyTextes[index]->setBrush(QColor(255, 0, 0));

   QString textNew(QString(
      "<!DOCTYPE html>"
      "<html>"
      "<body>"
      "<p1 style=\"font-size:%1px\">%2</p1><br>"
      "<p1 style=\"font-size:%3px\">%4</p1>"
      "</body>"
      "</html>"
   ).arg((int32_t)54).arg(dimension).arg((int32_t)32).arg("Font32"));
   _anyTextes[index]->setHtml(textNew);
   //_anyTextes[index]->setPlainText(textNew);

   //_anyTextes[index]->setPlainText(dimension);
   _anyTextes[index]->setDefaultTextColor(QColor(0, 0, 255));
   QFont qfont2_(QString::fromWCharArray(L"Courier"), 2, QFont::Bold, true);
   _anyTextes[index]->setPos(100, 100);
   //_anyTextes[index]->setFont(qfont2_);

   //break;
#else
#endif

}

void MainScreen::putCurrentData(gsa::t::CurrentData *data, int m_Period, int index, int length)
{
   int counter(0);

   _data = data;

   DWORD id = GetCurrentThreadId();

   //QString str(QString("INFO0077 %1[%2]%3 this = %4 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this, 0, 16));
   //QString str(QString("INFO0077 %1 [%2] this = %3 ").arg(__FUNCTION__).arg(__LINE__).arg((int)this, 0, 16));
   //qInfo(str.toStdString().c_str());

   //QMutexLocker locker(&mutex);
   emit signalPutCurrentData(m_Period, index, length);

   //QString str(QString("INFO007 %1[%2]%3 this = %4 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this, 0, 16) );
   //qInfo(str.toStdString().c_str());

   //QWaitCondition waitCondition;
   //waitCondition.wait(locker.mutex());
   //bufferNotEmpty.wait(&mutex);

   while ( _semaphore.tryAcquire() == false && _exit == false ) 
   {
      QThread::sleep(0);
      //int i(0);
   }

   return;
}

void MainScreen::putTableData(gsa::t::TablePanelData *tablePanelData, int index, int length)
{
   //_mainScreen->putTableData(_Data, index, length);

   //gsa::t::TablePanelData *tablePanelData_(g_Parameter._tablePanel);
   //if (g_Parameter._tablePanel == nullptr)
   //   tablePanelData_ = g_Parameter._tablePanel;

   //DialogItemTablePanel *widdgetItem2_ = dialogItemTablePanel(g_Parameter._tablePanel);
   DialogItemTablePanel *widget_ = dialogItemTablePanel(g_Parameter._tablePanel);

   //QString str(QString("INFO0077 <<<<<<>>>>>> %1 [%2] widget_= %3 ").arg(__FUNCTION__).arg(__LINE__).arg((long)widget_));
   //qInfo(str.toStdString().c_str());

   if (widget_ != nullptr) {
      //QString str(QString("INFO007 %1 OK _tablePanel = %2").arg(__FUNCTION__).arg((long long)g_Parameter._tablePanel, 0, 16));
      //qInfo(str.toStdString().c_str());
      widget_->setTableData(tablePanelData, g_Parameter._tablePanel);
   } 
   else {
      //QString str(QString("INFO007 %1 ERROR _tablePanel = %2").arg(__FUNCTION__).arg((long long)g_Parameter._tablePanel, 0, 16));
      //qInfo(str.toStdString().c_str());
      int i = 0;
   }

   VSyncCallback();
}

void MainScreen::putTablePanel(gsa::t::Table *tablePanel, int index)
{
   //fillTablePanel(g_Parameter._tablePanel, 0);
   fillTablePanel(_parentWindow, tablePanel, index, nullptr);

   DialogItemTablePanel *widget_ = dialogItemTablePanel(tablePanel);
   if (widget_ != nullptr) 
      widget_->setNames(_names);

   //QString str(QString("INFO007 %1 _tablePanel = %2").arg(__FUNCTION__).arg((long long)tablePanel, 0, 16));
   //qInfo(str.toStdString().c_str());

   //_mainScreen->putTablePanel(_Data, index, length);

   //VSyncCallback();
}

void VChart::showEvent(QShowEvent * event)
{
   QSizeF size1_ = this->size();
}

void VChartView::keepCallout()
{
   //_callouts.append(_callout);

   if (_callout == 0) {
      //_callout = new Callout(_chart);
   }

   QPointF point(10.0, 10.0);

   //_callout->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
   //_callout->setAnchor(point);
   //_callout->setZValue(11);
   //_callout->updateGeometry();
   //_callout->show();

   //setStop();
}

void VChartView::tooltip(QPointF point, bool state)
{
   if (_callout == 0)
      _callout = new Callout(_chart);

   //if (state) {
   _callout->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
   _callout->setAnchor(point);
   _callout->setZValue(11);
   _callout->updateGeometry();
   _callout->show();
   //}
   //else {
   //   m_tooltip->hide();
   //}
}

