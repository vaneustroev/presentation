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
//#include <boost/container/vector.hpp>
//#include <boost/chrono.hpp>

//#include "gcore/controller.h"
//#include "gcore/core.h"

#include "guiUnman.h"
#include "gmenu/gmenupage.h"
#include "gmenu/gmenuitem.h"
#include "gmain/mainwindow.h"
#include "gcolor/color_selector.hpp"

MenuPage::MenuPage(QWidget *parent, const gsa::t::GuiPad &guiPad, bool multi, gsa::core::Controller *controller)
   : QWidget(parent)
   , _controller(controller)
   //, _guiPad((gsa::t::GuiPad *)&guiPad)
   , _tabWidget(nullptr)
   , _verticalLayout(nullptr)
   , _verticalLayout2(nullptr)
   , _groupBoxTest(nullptr)
   , _verticalLayout_2(nullptr)
   , currentMenuItem(nullptr)
   , _itemIndex(0)
{
   //if (multi)
   //{
   //   QTabWidget *tabWidget(nullptr);
   //   QWidget *tab(nullptr);
   //   QWidget *tab_2(nullptr);
   //   QWidget *tab_3(nullptr);

   //   _verticalLayout = new QVBoxLayout(this);
   //   _verticalLayout->setSpacing(2);
   //   _verticalLayout->setContentsMargins(11, 11, 11, 11);
   //   _verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
   //   tabWidget = new QTabWidget(this);
   //   tabWidget->setObjectName(QStringLiteral("tabWidget"));
   //   tabWidget->setTabPosition(QTabWidget::East);
   //   tabWidget->setTabShape(QTabWidget::Rounded);
   //   tabWidget->setElideMode(Qt::ElideNone);
   //   tab = new QWidget();
   //   tab->setObjectName(QStringLiteral("tab"));
   //   tabWidget->addTab(tab, QString());
   //   tab_2 = new QWidget();
   //   tab_2->setObjectName(QStringLiteral("tab_2"));
   //   tabWidget->addTab(tab_2, QString());
   //   tab_3 = new QWidget();
   //   tab_3->setObjectName(QStringLiteral("tab_3"));
   //   tabWidget->addTab(tab_3, QString());

   //   tabWidget->setCurrentIndex(0);

   //   tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
   //   tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
   //   tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Page", Q_NULLPTR));

   //   _verticalLayout->addWidget(tabWidget);
   //}
   //else {
   //   //QWidget *tab(nullptr);

   //   std::string name = QString::fromWCharArray(_guiPad->name).toStdString();
   //   
   //   if (_tabwidgets.find(name) == _tabwidgets.end()) 
   //   {
   //QTabWidget *tabWidget(nullptr);

   _mainWindow = (Main::MainWindow *)parent;

   _verticalLayout = new QVBoxLayout(this);
   _verticalLayout->setSpacing(0); //(2);
   //_verticalLayout->setContentsMargins(11, 11, 11, 11);
   _verticalLayout->setContentsMargins(0, 0, 0, 0);
   _verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

   _tabWidget = new QTabWidget(this);
   _tabWidget->setObjectName(QStringLiteral("_tabWidget"));
   _tabWidget->setTabPosition(QTabWidget::East);
   //_tabWidget->setTabShape(QTabWidget::Rounded);
   //_tabWidget->setElideMode(Qt::ElideNone);
   //_tabWidget->setFocusPolicy(Qt::ClickFocus);

   //scrollview so all items fit in window
   QScrollArea* techScroll = new QScrollArea(_tabWidget);
   techScroll->setBackgroundRole(QPalette::Window);
   techScroll->setFrameShadow(QFrame::Plain);
   techScroll->setFrameShape(QFrame::NoFrame);
   techScroll->setWidgetResizable(true);

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_mainWindow->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_mainWindow->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_mainWindow->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_mainWindow->indentindexes());

   gsa::t::ThemeItem item_;

   item_.description = nullptr;

   for (auto &item : _theme->themeItems) {
      if (_indentindexes.find(std::wstring(item.description)) != _indentindexes.end()) {
         switch (_indentindexes[std::wstring(item.description)])
         {
         case gsa::t::IndentIndex::MenuArea: //Unifying frame of the menu area from the size of the control 
         {
            item_ = item;
            break;
         }
         default:
            break;
         }
      }
   }

   double value(0.0);
   if(item_.description != nullptr)
      _mainWindow->GetValue(item_.value, value);

   QWidget *tab(nullptr);

   tab = new QWidget(_tabWidget);
   tab->setObjectName(QString::fromWCharArray(guiPad.tab));
   tab->setFocusPolicy(Qt::ClickFocus);
   techScroll->setWidget(tab);
   _tabWidget->addTab(techScroll, QString::fromWCharArray(guiPad.tab));
   //_tabWidget->addTab(tab, QString::fromWCharArray(guiPad.tab));

   _verticalLayout2 = new QVBoxLayout(tab);
   _verticalLayout2->setSpacing(0); //(2);
   //_verticalLayout2->setContentsMargins(11, 11, 11, 11);
   //_verticalLayout2->setContentsMargins(0, 0, 0, 0);
   _verticalLayout2->setContentsMargins((int)value, (int)value, (int)value, (int)value);
   _verticalLayout2->setObjectName(QStringLiteral("verticalLayout"));

   _tabWidget->setCurrentIndex(0);

   _tabWidget->setTabText(_tabWidget->indexOf(tab), QApplication::translate("MainWindow", QString::fromWCharArray(guiPad.tab).toStdString().c_str(), Q_NULLPTR));

   _verticalLayout->addWidget(_tabWidget);

   lineEdits.clear();
   pushButtons.clear();
   radioButtons.clear();
   comboBoxes.clear();

   _caption = QString::fromWCharArray(guiPad.name);

   //gsa::t::Theme *_theme(g_Parameter._theme);
   //std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_mainWindow->fontindexes());
   //std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_mainWindow->colorindexes());
   //std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_mainWindow->sizeindexes());
   //std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_mainWindow->indentindexes());
   
   gsa::t::ThemeFont font_;

   for (auto &font : _theme->themeFonts) {
      if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
         switch (_fontindexes[std::wstring(font.description)])
         {
         case gsa::t::FontIndex::SelectedMenu: //Tabs of the selected menu(name of the subcomposition)
         {
            font_ = font;
            break;
         }
         default:
            break;
         }
      }
   }

   int r, g, b;
   _mainWindow->GetRgb(font_.color, r, g, b);
   QColor cfont_(r, g, b);

   QFont font;
   font.setFamily(QString::fromWCharArray(font_.family));
   font.setPixelSize(font_.size);
   QFontMetrics fm(font);

#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
   uint32_t fontWidth = static_cast<int>(fm.horizontalAdvance(QString("012345678901234")));
#else
   uint32_t fontWidth = static_cast<int>(fm.width(QString("012345678901234567890123456789"))); //__van__
#endif
   uint32_t fontHeight = fm.height();

   _tabWidget->setStyleSheet(QString("%1 "
      "QTabBar::tab { " //"QWidget { " //"QComboBox { " 
      "font-family: %2; "
      "font-size: %3pt; " //"font-size: %3px; " 
      "font-weight: %4; "
      "color: rgb(%5, %6, %7); "
      "width: %8px; "
      "height: %9px; "
      //"height: auto; "
      //"background-color: rgb(%8, %9, %10); "
      "} "
      //"QTabBar::tab:selected{ "
      //"background: rgb(255, 0, 0); "
      //"color: black; "
      //"} "
   ).arg(_tabWidget->styleSheet()).arg(QString::fromWCharArray(font_.family)).arg(font_.size).arg(QString::fromWCharArray(font_.style)).
      arg(cfont_.red()).arg(cfont_.green()).arg(cfont_.blue()).arg(fontHeight).arg(fontWidth)
   );





   //techScroll->setWidgetResizable(true);

   //for (auto &themeItem : _theme->themeItems) {
   //   switch (themeItem.type)
   //   {
   //   case 0:
   //   {
   //      switch (_colorindexes[std::wstring(themeItem.description)])
   //      {
   //      case gsa::t::ColorIndex::DisplayArea:
   //      case gsa::t::ColorIndex::GraphicPanelScale: //Graphic panel scale 
   //      case gsa::t::ColorIndex::TableBorders: //Borders of the table display 
   //      case gsa::t::ColorIndex::CurrentMeasurement: //Current measurement selection area 
   //      case gsa::t::ColorIndex::TabSelectionArea: //Tab in the general dimension selection area 
   //      case gsa::t::ColorIndex::QuickAccess: //Tabs in the quick access area 
   //      case gsa::t::ColorIndex::DropDownMenu: //Drop down menu 
   //         break;
   //      case gsa::t::ColorIndex::UnifyingFrame: //Unifying frame in the menu area
   //      {
   //         //widgetItems_[ui->comboBox] = item;
   //         for (auto &item : lineEdits) {
   //            widgetItems_[(QWidget*)item].region = themeItem;
   //         }
   //         for (auto &item : pushButtons) {
   //            widgetItems_[(QWidget*)item].region = themeItem;
   //         }
   //         for (auto &item : radioButtons) {
   //            widgetItems_[(QWidget*)item].region = themeItem;
   //         }
   //         for (auto &item : comboBoxes) {
   //            widgetItems_[(QWidget*)item].region = themeItem;
   //         }
   //         for (auto &item : colorSelectores) {
   //            widgetItems_[(QWidget*)item].region = themeItem;
   //         }
   //         break;
   //      }
   //      case gsa::t::ColorIndex::UnifyingFrameBorder: //Border of the unifying frame in the menu area
   //      {
   //         //widgetItems_[ui->comboBox] = item;
   //         for (auto &item : lineEdits) {
   //            widgetItems_[(QWidget*)item].border = themeItem;
   //         }
   //         for (auto &item : pushButtons) {
   //            widgetItems_[(QWidget*)item].border = themeItem;
   //         }
   //         for (auto &item : radioButtons) {
   //            widgetItems_[(QWidget*)item].border = themeItem;
   //         }
   //         for (auto &item : comboBoxes) {
   //            widgetItems_[(QWidget*)item].border = themeItem;
   //         }
   //         for (auto &item : colorSelectores) {
   //            widgetItems_[(QWidget*)item].border = themeItem;
   //         }
   //         break;
   //      }
   //      case gsa::t::ColorIndex::ControlDropDownMenu: //Control drop - down list in the menu area
   //      case gsa::t::ColorIndex::ControlDropDownPanel: //Control drop - down list in the panel(additional data area)
   //      case gsa::t::ColorIndex::PanelControl: //Control in the panel(additional data area)
   //      case gsa::t::ColorIndex::SelectedLine: //Selected line in the expanded control drop - down list
   //      case gsa::t::ColorIndex::UnselectedString: //Unselected string in expanded control drop - down list
   //      case gsa::t::ColorIndex::ElementsBorders: //Borders of the elements of the drop - down menu
   //      case gsa::t::ColorIndex::CompositionMenu: //Menu area(composition)
   //      case gsa::t::ColorIndex::ControlMenu: //Control in the menu area(composition)
   //      case gsa::t::ColorIndex::Default: //Default
   //      default:
   //         break;
   //      }
   //      break;
   //   }
   //   case 1:
   //   {
   //      break;
   //   }
   //   case 2:
   //   {
   //      break;
   //   }
   //   default:
   //   {
   //      break;
   //   }
   //   }
   //}




   //   }
   //   else {
   //      QTabWidget *tabWidget(_tabwidgets[name]);
   //      QWidget *tab(nullptr);

   //      tab = new QWidget();
   //      tab->setObjectName(QString::fromWCharArray(_guiPad->tab));
   //      tab->setFocusPolicy(Qt::ClickFocus);
   //      tabWidget->addTab(tab, QString());

   //      _verticalLayout2 = new QVBoxLayout(tab);
   //      _verticalLayout2->setSpacing(2); //(2);
   //      _verticalLayout2->setContentsMargins(11, 11, 11, 11);
   //      _verticalLayout2->setObjectName(QStringLiteral("verticalLayout"));

   //      tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", QString::fromWCharArray(_guiPad->tab).toStdString().c_str(), Q_NULLPTR));
   //   }
   //}
}

MenuPage::MenuPage(QWidget *parent)
{
}

MenuPage::~MenuPage()
{
   int size1 = lineEdits.size();
   int size2 = pushButtons.size();
   int size3 = radioButtons.size();
   int size4 = comboBoxes.size();
   int i(0);
}

void MenuPage::addPage(const gsa::t::GuiPad &guiPad)
{
   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_mainWindow->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_mainWindow->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_mainWindow->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_mainWindow->indentindexes());

   gsa::t::ThemeItem item_;

   for (auto &item : _theme->themeItems) {
      if (_indentindexes.find(std::wstring(item.description)) != _indentindexes.end()) {
         switch (_indentindexes[std::wstring(item.description)])
         {
         case gsa::t::IndentIndex::MenuArea: //Unifying frame of the menu area from the size of the control 
         {
            item_ = item;
            break;
         }
         default:
            break;
         }
      }
   }

   double value(0.0);
   _mainWindow->GetValue(item_.value, value);

   //QWidget *tab(new QWidget());
   QWidget *tab(new QWidget(_tabWidget));

   tab->setObjectName(QString::fromWCharArray(guiPad.tab));
   tab->setFocusPolicy(Qt::ClickFocus);
   if (_tabWidget != nullptr) {

      //_tabWidget->addTab(tab, QString::fromWCharArray(guiPad.tab));

      //scrollview so all items fit in window
      QScrollArea* techScroll = new QScrollArea(_tabWidget);
      techScroll->setBackgroundRole(QPalette::Window);
      techScroll->setFrameShadow(QFrame::Plain);
      techScroll->setFrameShape(QFrame::NoFrame);
      techScroll->setWidgetResizable(true);

      techScroll->setWidget(tab);
      _tabWidget->addTab(techScroll, QString::fromWCharArray(guiPad.tab));
   }
   else {
      int i(0);
   }

   _verticalLayout2 = new QVBoxLayout(tab);
   _verticalLayout2->setSpacing(0); //(2);
   //_verticalLayout2->setContentsMargins(11, 11, 11, 11);
   //_verticalLayout2->setContentsMargins(0, 0, 0, 0);
   _verticalLayout2->setContentsMargins((int)value, (int)value, (int)value, (int)value);
   _verticalLayout2->setObjectName(QStringLiteral("verticalLayout"));

   _tabWidget->setTabText(_tabWidget->indexOf(tab), QApplication::translate("MainWindow", QString::fromWCharArray(guiPad.tab).toStdString().c_str(), Q_NULLPTR));
}

void MenuPage::fillButtonNames(wchar_t *units[32], int length)
{
   _keyPadParam._buttonNames.clear();

   for (int i = 0; i < length; i++) {
      _keyPadParam._buttonNames << QString::fromWCharArray(units[i]);
   }
}

int MenuPage::KeyPad(TG::KeyPadParam &keyPadParam, QString &unit, int &index)
{
   TG::UnitTypes type(TG::unitUndef);
   double value(0.0);

   index = 0;
   int unitindex = keyPadParam._buttonNames.indexOf(unit);
   int ret = _controller->KeyPad(keyPadParam, unitindex);
   if (ret == QDialog::Accepted)
   {
      _controller->getSelection(type, index, value);
      if (index > 0) {
         unit = keyPadParam._buttonNames[index-1];
      } else {
         unit = keyPadParam._buttonNames[0];
      }
      keyPadParam._value = value;

      if (keyPadParam._fieldType == TG::typeFreqCenter) {
         //_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
         //_controller->setFreqCenter(value);
         //ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
         //ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
         //ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
         //ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
      }
      else if (keyPadParam._fieldType == TG::typeFreqSpan) {
         //_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
         //_controller->setFreqSpan(value);
         //ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
         //ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
         //ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
         //ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
      }
      else if (keyPadParam._fieldType == TG::typeFreqStart) {
         //_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
         //_controller->setFreqStart(value);
         //ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
         //ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
         //ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
         //ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
      }
      else if (keyPadParam._fieldType == TG::typeFreqStop) {
         //_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
         //_controller->setFreqStop(value);
         //ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
         //ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
         //ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
         //ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
      }
      else if (keyPadParam._fieldType == TG::typeFreqStep) {
         //_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
         //_controller->setFreqStep(value);
         //ui->EditStep->setText(QString("%1 %2").arg(value).arg(_controller->freqUnitText()));
      }
      else if (keyPadParam._fieldType == TG::typeFreqOffset) {
         //_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
         //_controller->setFreqOffset(value);
         //ui->EditOffset->setText(QString("%1 %2").arg(value).arg(_controller->freqUnitText()));
      }

      //_controller->screenWidget()->redraw();
   }

   return ret;
}

MenuItem* MenuPage::getItemRbw(void)
{
   //realPageIndex
   //lineEdits.push_back(lineEdit);
   float tt1 = 1;
   char tt2 = tt1;

   MenuItem *menuItem(nullptr);
   for (auto item : lineEdits) {
      QString Name;
      QString Name2;
      wchar_t *_wchar = (dynamic_cast<MenuItem*>(item)->name());
      //Name.fromWCharArray((dynamic_cast<MenuItem*>(item)->name()));
      //Name.fromWCharArray(_wchar);
      Name = QString::fromWCharArray(_wchar);
      std::wstring wstr(_wchar);

      const char *ch(Name.toStdString().c_str());
      const char *ch2(Name2.toStdString().c_str());
      if (Name == QString("Res BW")) {
         int i(0);
         menuItem = dynamic_cast<MenuItem*>(item);
      }
      else {
         int i(0);
      }
   }

   //QObject* object(currentMenuItem);

   //auto itObj = std::find_if(
   //   lineEdits.begin(), lineEdits.end(),
   //   [object](QObject* p) { return p == object; }
   //);
   //if (itObj != lineEdits.end()) {
   //   _itemIndex = dynamic_cast<MenuItem*>(*itObj)->itemIndex();
   //}

   return menuItem;
}

MenuItem* MenuPage::getItemByName(const QString &name)
{
   MenuItem *menuItem(nullptr);

   //Костыль, надо синхронизовать имена 
   std::map<QString, QString> converter;
   converter[QString("RBW")] = QString("Res BW");
   converter[QString("Center")] = QString("Center Frequency");
   converter[QString("Span")] = QString("Span");

   for (auto item : lineEdits) {
      QString Name = QString::fromWCharArray((dynamic_cast<MenuItem*>(item)->name()));
      if (Name == converter[name]) {
         menuItem = dynamic_cast<MenuItem*>(item);
      }
   }

   //QObject* object(currentMenuItem);
   //auto itObj = std::find_if(
   //   lineEdits.begin(), lineEdits.end(),
   //   [object](QObject* p) { return p == object; }
   //);
   //if (itObj != lineEdits.end()) {
   //   _itemIndex = dynamic_cast<MenuItem*>(*itObj)->itemIndex();
   //}

   return menuItem;
}

int MenuPage::itemIndex(void)
{ 
   QObject* object(currentMenuItem);

   auto itObj = std::find_if(
      lineEdits.begin(), lineEdits.end(),
      [object](QObject* p) { return p == object; }
   );
   if (itObj != lineEdits.end()) {
      if (dynamic_cast<MenuItem*>(*itObj) != nullptr) {
         _itemIndex = dynamic_cast<MenuItem*>(*itObj)->itemIndex();
      }
   }

   //QString str(QString("[%1]").arg(_itemIndex));
   //qInfo(str.toStdString().c_str());

   return _itemIndex;
}

bool MenuPage::eventFilter(QObject* object, QEvent* event)
{
   Q_UNUSED(object);
   Q_UNUSED(event);

   //if (_controller == nullptr) return true;

   _keyPadParam._unitType = TG::unitFreq;

   //TouchBegin //194,
   //TouchUpdate //195,
   //TouchEnd //196,
   //TouchCancel //209,

   //keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqSpan;
   //keyPadParamList[TG::unitFreq]._value = dynamic_cast<QLineEdit*>(*itObj)->text().toDouble();
   //KeyPad(keyPadParamList[TG::unitFreq]);

   //dynamic_cast<QLineEdit*>(*itObj)->setText(QString("%1").arg((int)keyPadParamList[TG::unitFreq]._value));
   //QString text2(dynamic_cast<QLineEdit*>(*itObj)->text());
   //QString text3(dynamic_cast<MenuItem*>(*itObj)->text());
   ////g_Parameter._SetValue(dynamic_cast<MenuItem*>(*itObj)->itemIndex(), dynamic_cast<QLineEdit*>(*itObj)->text().toDouble());
   //g_Parameter._SetValue(dynamic_cast<MenuItem*>(*itObj)->itemIndex(), keyPadParamList[TG::unitFreq]._value);

   if (event && event->type() == QEvent::MouseButtonPress) 
   {
      auto itObj = std::find_if(
         lineEdits.begin(), lineEdits.end(),
         [object](QObject* p) { return p == object; }
      );
      if (itObj != lineEdits.end()) {
         QRegExp rx("[ ]");
         QString value = dynamic_cast<QLineEdit*>(*itObj)->text();
         QStringList valueParams = value.split(rx, QString::SkipEmptyParts);
         if (valueParams.size() == 2) 
         {
            //bool enabled = dynamic_cast<MenuItem*>(currentMenuItem)->isEnabled();
            //if (enabled == false) return false;

            _keyPadParam._fieldType = TG::typeFreqSpan;
            _keyPadParam._value = valueParams[0].toDouble();
            QString unit(valueParams[1]);
            //int currentIndex = dynamic_cast<MenuItem*>(*itObj)->currentIndex();
            int index(dynamic_cast<MenuItem*>(*itObj)->currentIndex());

            currentMenuItemPrev = currentMenuItem;
            if (dynamic_cast<MenuItem*>(currentMenuItemPrev) != nullptr) 
            {
               dynamic_cast<MenuItem*>(currentMenuItemPrev)->setProcessFocus(true);
               g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItemPrev)->itemIndex(), 0);

               currentMenuItem = dynamic_cast<QObject*>(*itObj);

               bool enabled = dynamic_cast<MenuItem*>(currentMenuItem)->isEnabled();
               if (enabled == false) return false;

               //dynamic_cast<MenuItem*>(currentMenuItemPrev)->buttonNames();
               TG::KeyPadParam _keyPadParam2(dynamic_cast<MenuItem*>(currentMenuItem)->keyPadParam());
               _keyPadParam2._value = valueParams[0].toDouble();
               //_keyPadParam2._buttonNames.indexOf(QRegExp("^" + QRegExp::escape(textToFind) + ".+"));
               //int unitindex = _keyPadParam2._buttonNames.indexOf(unit);

               if (KeyPad(_keyPadParam2, unit, index) == 0) {
                  //dynamic_cast<MenuItem*>(currentMenuItemPrev)->setFocus();
                  dynamic_cast<MenuItem*>(currentMenuItemPrev)->setProcessFocus(true);
                  g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItemPrev)->itemIndex(), 1);
                  return false; //true;
               }
               else {
                  g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex(), 1);
               }

               //index = index - 1;
               if (index < 0) index = 0;

               int itemIndex = dynamic_cast<MenuItem*>(*itObj)->itemIndex();
               wcscpy(_unit, (wchar_t*)_keyPadParam2._buttonNames[index].toStdWString().c_str());
               //_keyPadParam2._buttonNames[index].toStdWString().c_str();

               QString strValue;
               //Double2String(strValue, _keyPadParam2._value);
               gsa::controller->Double2String(strValue, _keyPadParam2._value);

               //dynamic_cast<QLineEdit*>(*itObj)->setText(QString("%1 %2").arg((int)_keyPadParam2._value).arg(_keyPadParam2._buttonNames[index]) );
               dynamic_cast<QLineEdit*>(*itObj)->setText(QString("%1 %2").arg(strValue).arg(_keyPadParam2._buttonNames[index]));

               //unit = dynamic_cast<QLineEdit*>(*itObj)->text();
               //QString text2(dynamic_cast<QLineEdit*>(*itObj)->text());
               //QString text3(dynamic_cast<MenuItem*>(*itObj)->text());
               //wcscpy(_unit, (wchar_t*)unit.toStdWString().c_str());
               g_Parameter._SetValue(dynamic_cast<MenuItem*>(*itObj)->itemIndex(), _keyPadParam2._value, _unit, index);
            }
            else {
               currentMenuItem = dynamic_cast<MenuItem*>(*itObj);
               int i = 0;
            }

            return false;
         }

         return false;

      } else {
         int i(0);
      }
      return true; // lets the event continue to the edit
   }
   //else if (event && event->type() == QEvent::KeyPress) {
   //   QKeyEvent * keyEvent = dynamic_cast<QKeyEvent*>(event);
   //   if (keyEvent && keyEvent->key() == Qt::Key_Tab)
   //      return true;
   //}
   else if (event && event->type() == QEvent::KeyRelease) {
      QKeyEvent* key = static_cast<QKeyEvent*>(event);
      //if ((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return)) {
      if ( (key->key() == Qt::Key_Escape) ) {
         //Enter or return was pressed
         return QObject::eventFilter(object, event);
      }
      //else {
      //   return QObject::eventFilter(object, event);
      //}

      auto itObj = std::find_if(
         lineEdits.begin(), lineEdits.end(),
         [object](QObject* p) { return p == object; }
      );
      if (itObj != lineEdits.end()) {
         QRegExp rx("[ ]");
         QString value = dynamic_cast<QLineEdit*>(*itObj)->text();
         QStringList valueParams = value.split(rx, QString::SkipEmptyParts);
         if (valueParams.size() == 2)
         {
            g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex(), 0);
            currentMenuItem = dynamic_cast<QObject*>(*itObj);
            g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex(), 1);
            return false;
         }
      }
      return false;
   } 
   else if (event && event->type() == QEvent::FocusOut) {
      auto itObj = std::find_if(
         lineEdits.begin(), lineEdits.end(),
         [object](QObject* p) { return p == object; }
      );
      if (itObj != lineEdits.end()) {
         QRegExp rx("[ ]");
         QString value = dynamic_cast<QLineEdit*>(*itObj)->text();
         QStringList valueParams = value.split(rx, QString::SkipEmptyParts);
         if (valueParams.size() == 2)
         {
            if (dynamic_cast<MenuItem*>(currentMenuItem) != nullptr) {
               if (dynamic_cast<MenuItem*>(currentMenuItem)->processFocus() == false) {
                  int itemIndex = dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex();
                  g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex(), 0);
               }
               else {
                  dynamic_cast<MenuItem*>(currentMenuItem)->setProcessFocus(false);
               }
            }
            return false;
         }
         return false;
      }
      else {
         int i(0);
      }
      return false; 
   }
   else if (event && event->type() == QEvent::FocusIn) {
      auto itObj = std::find_if(
         lineEdits.begin(), lineEdits.end(),
         [object](QObject* p) { return p == object; }
      );
      if (itObj != lineEdits.end()) {
         QRegExp rx("[ ]");
         QString value = dynamic_cast<QLineEdit*>(*itObj)->text();
         QStringList valueParams = value.split(rx, QString::SkipEmptyParts);
         if (valueParams.size() == 2 && currentMenuItem != nullptr)
         {
            if (dynamic_cast<MenuItem*>(currentMenuItem) != nullptr) {
               if (dynamic_cast<MenuItem*>(currentMenuItem)->processFocus() == false) {
                  int itemIndex = dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex();
                  //g_Parameter._GSetFocus(dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex(), 0);
               }
               else {
                  int itemIndex = dynamic_cast<MenuItem*>(currentMenuItem)->itemIndex();
                  //dynamic_cast<MenuItem*>(currentMenuItem)->setProcessFocus(false);
               }
            }
            return false;
         }
         return false;
      }
      else {
         int i(0);
      }
      return false;
   }

   return false;
}

void MenuPage::addSpacer(void)
{
   if (lineEdits.size() > 0) {
      QFocusEvent* eventFocus = new QFocusEvent(QEvent::FocusIn);
      qApp->postEvent(dynamic_cast<QLineEdit*>(*lineEdits.begin()), (QEvent *)eventFocus, Qt::LowEventPriority);
      if (dynamic_cast<QLineEdit*>(*lineEdits.begin()) != nullptr) {
         dynamic_cast<QLineEdit*>(*lineEdits.begin())->setFocusPolicy(Qt::StrongFocus);
         dynamic_cast<QLineEdit*>(*lineEdits.begin())->setFocus();
      }

      currentMenuItem = dynamic_cast<QObject*>(*lineEdits.begin());
   }

   QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
   _verticalLayout2->addItem(verticalSpacer);
}

void MenuPage::doWheelEvent(int delta)
{
   if (currentMenuItem != nullptr && dynamic_cast<MenuItem*>(currentMenuItem)) {
      if (dynamic_cast<MenuItem*>(currentMenuItem) != nullptr) {
         dynamic_cast<MenuItem*>(currentMenuItem)->doWheelEvent(delta);
      }
   }
}

void MenuPage::slotButton(void)
{
   QObject *senderObj = sender(); // This will give Sender object
   QString senderObjName = senderObj->objectName();

   auto itObj = std::find_if(
      pushButtons.begin(), pushButtons.end(),
      [senderObj](QObject* p) { return p == senderObj; }
   );
   if (itObj != pushButtons.end()) {
      double value(1.0);
      wcscpy(_text, L"TRUE");
      int index(0);
      g_Parameter._SetValue(dynamic_cast<MenuPushButton*>(*itObj)->itemIndex(), value, _text, index);
   }
   else {
      int i(0);
   }
}

void MenuPage::slotColorSelector(void)
{
   QObject *senderObj = sender(); // This will give Sender object
   QString senderObjName = senderObj->objectName();

   auto itObj = std::find_if(
      colorSelectores.begin(), colorSelectores.end(),
      [senderObj](QObject* p) { return p == senderObj; }
   );
   if (itObj != colorSelectores.end()) {
      double value(1.0);
      wcscpy(_text, L"TRUE");
      int index(0);
      //g_Parameter._SetValue(dynamic_cast<MenuPushButton*>(*itObj)->itemIndex(), value, _text, index);
   }
   else {
      int i(0);
   }
}

void MenuPage::slotColorSelected(QColor _color)
{
   QObject *senderObj = sender(); // This will give Sender object
   QString senderObjName = senderObj->objectName();

   auto itObj = std::find_if(
      colorSelectores.begin(), colorSelectores.end(),
      [senderObj](QObject* p) { return p == senderObj; }
   );
   if (itObj != colorSelectores.end()) 
   {
      //int r;
      //int g;
      //int b;
      //_color.getRgb(&r, &g, &b);

      //QColor _color;
      //_color.setRgb((unsigned int)guiItem.value);

      int r;
      int g;
      int b;
      _color.getRgb(&r, &g, &b);
      //_color.setAlpha(0);
      //unsigned int temp = _color.rgb();

      double value(_color.rgb());
      wcscpy(_text, L"TRUE");
      int index(0);

      _color.setRgb((unsigned int)value);
      //_color.setAlpha(0);
      _color.getRgb(&r, &g, &b);
      int _itemIndex = dynamic_cast<MenuColorSelector*>(*itObj)->itemIndex();
      //value = _color.rgb();

      g_Parameter._SetValue(dynamic_cast<MenuColorSelector*>(*itObj)->itemIndex(), value, _text, index);
   }
   else {
      int i(0);
   }
}

void MenuPage::slotRadioButton(bool checked)
{
   QObject *senderObj = sender(); // This will give Sender object
   QString senderObjName = senderObj->objectName();

   auto itObj = std::find_if(
      radioButtons.begin(), radioButtons.end(),
      [senderObj](QObject* p) { return p == senderObj; }
   );
   if (itObj != radioButtons.end()) {
      double value(dynamic_cast<MenuRadioButton*>(*itObj)->index());
      wcscpy(_text, L"TRUE");
      int index(0);
      g_Parameter._SetValue(dynamic_cast<MenuRadioButton*>(*itObj)->itemIndex(), value, _text, index);
   }
   else {
      int i(0);
   }
}

void MenuPage::doReturnPressed(void)
{
   QObject *senderObj = sender(); // This will give Sender object
   QString senderObjName = senderObj->objectName();

   auto itObj = std::find_if(
      lineEdits.begin(), lineEdits.end(),
      [senderObj](QObject* p) { return p == senderObj; }
   );
   if (itObj != lineEdits.end()) {
      QRegExp rx("[ ]");
      QString value = dynamic_cast<QLineEdit*>(*itObj)->text();
      QStringList valueParams = value.split(rx, QString::SkipEmptyParts);
      if (valueParams.size() == 2) {
         //QString str = valueParams[0];

         _keyPadParam._fieldType = TG::typeFreqSpan;
         _keyPadParam._value = valueParams[0].toDouble();
         QString unit(valueParams[1]);
         int index(dynamic_cast<MenuItem*>(*itObj)->currentIndex());

         TG::KeyPadParam _keyPadParam2(dynamic_cast<MenuItem*>(currentMenuItem)->keyPadParam());
         _keyPadParam2._value = valueParams[0].toDouble();

         //if (KeyPad(_keyPadParam, unit, index) == 0) return true;
         //index = index - 1;

         int itemIndex = dynamic_cast<MenuItem*>(*itObj)->itemIndex();
         wcscpy(_unit, (wchar_t*)_keyPadParam2._buttonNames[index].toStdWString().c_str());
         //_keyPadParam2._buttonNames[index].toStdWString().c_str();

         QString strValue;
         //Double2String(strValue, _keyPadParam2._value);
         gsa::controller->Double2String(strValue, _keyPadParam2._value);

         //dynamic_cast<QLineEdit*>(*itObj)->setText(QString("%1 %2").arg((int)_keyPadParam2._value).arg(_keyPadParam2._buttonNames[index]));
         dynamic_cast<QLineEdit*>(*itObj)->setText(QString("%1 %2").arg(strValue).arg(_keyPadParam2._buttonNames[index]));

         //unit = dynamic_cast<QLineEdit*>(*itObj)->text();
         //QString text2(dynamic_cast<QLineEdit*>(*itObj)->text());
         //QString text3(dynamic_cast<MenuItem*>(*itObj)->text());
         //wcscpy(_unit, (wchar_t*)unit.toStdWString().c_str());
         g_Parameter._SetValue(dynamic_cast<MenuItem*>(*itObj)->itemIndex(), _keyPadParam2._value, _unit, index);
      }

      //QString unit("");
      //int index(0);
      //unit = dynamic_cast<QLineEdit*>(*itObj)->text();
      ////QString text2(dynamic_cast<QLineEdit*>(*itObj)->text());
      ////QString text3(dynamic_cast<MenuItem*>(*itObj)->text());
      //wcscpy(_text, (wchar_t*)unit.toStdWString().c_str());
      //index = 0; //index - 1;
      //g_Parameter._SetValue(dynamic_cast<MenuItem*>(*itObj)->itemIndex(), _keyPadParam._value, _text, index);
   }
   else {
      int i(0);
   }
}

void MenuPage::keyProcess(gsa::t::ItemInfo &itemInfo)
{
   if (itemInfo.type == QString("Switch") || itemInfo.type == QString("CheckList") ) {
      QList<QObject*>::iterator itrb(radioButtons.begin());
      while (itrb != radioButtons.end()) {
         if (((MenuRadioButton*)(*itrb))->itemIndex() == itemInfo.item) {
            if (((MenuRadioButton*)(*itrb))->isChecked() == false) {
               emit((MenuRadioButton*)(*itrb))->click();
               return;
            }
         }
         ++itrb;
      }
   }
   else if (itemInfo.type == QString("Button")) {
      QList<QObject*>::iterator itpb(pushButtons.begin());
      while (itpb != pushButtons.end()) {
         if (((MenuPushButton*)(*itpb))->itemIndex() == itemInfo.item) {
            if (((MenuPushButton*)(*itpb))->isEnabled() == true) {
               emit((MenuPushButton*)(*itpb))->click();
               return;
            }
         }
         ++itpb;
      }
   }
   else if (itemInfo.type == QString("EditBox")) {
      QList<QObject*>::iterator itle(lineEdits.begin());
      while (itle != lineEdits.end()) {
         if (((MenuItem*)(*itle))->itemIndex() == itemInfo.item) {
            if (((MenuItem*)(*itle))->isEnabled() == true) {
               QEvent _event(QEvent::MouseButtonPress);
               //eventFilter((QObject*)(*itle), &_event);
               QCoreApplication::sendEvent((QObject*)(*itle), &_event);
               return;
            }
         }
         ++itle;
      }
   }
   else if (itemInfo.type == QString("ComboBox")) {
      QList<QObject*>::iterator itcb(comboBoxes.begin());
      while (itcb != comboBoxes.end()) {
         if (((MenuComboBox*)(*itcb))->itemIndex() == itemInfo.item) {
            if (((MenuComboBox*)(*itcb))->isEnabled() == true) {
               int index( ((MenuComboBox*)(*itcb))->currentIndex() );
               int count( ((MenuComboBox*)(*itcb))->count() );
               emit((MenuComboBox*)(*itcb))->currentIndexChanged((++index) % count);
               return;
            }
         }
         ++itcb;
      }
   }
   else if (itemInfo.type == QString("ColorSelector")) {
      QList<QObject*>::iterator itcs(colorSelectores.begin());
      while (itcs != colorSelectores.end()) {
         //if (((MenuComboBox*)(*itcs))->itemIndex() == itemInfo.item) {
         //   if (((MenuComboBox*)(*itcs))->isEnabled() == true) {
         //      int index(((MenuComboBox*)(*itcs))->currentIndex());
         //      int count(((MenuComboBox*)(*itcs))->count());
         //      emit((MenuComboBox*)(*itcs))->currentIndexChanged((++index) % count);
         //      return;
         //   }
         //}
         ++itcs;
      }
   }
   else if (itemInfo.type == QString("CheckBox")) {
      QList<QObject*>::iterator itcs(colorSelectores.begin());
      while (itcs != colorSelectores.end()) {
         //if (((MenuComboBox*)(*itcs))->itemIndex() == itemInfo.item) {
         //   if (((MenuComboBox*)(*itcs))->isEnabled() == true) {
         //      int index(((MenuComboBox*)(*itcs))->currentIndex());
         //      int count(((MenuComboBox*)(*itcs))->count());
         //      emit((MenuComboBox*)(*itcs))->currentIndexChanged((++index) % count);
         //      return;
         //   }
         //}
         ++itcs;
      }
   }
   //CheckBox, CheckList
}

void MenuPage::uiPropertyChanged(int item, int type, int value)
{
   //QList<QObject*>::iterator it(lineEdits.begin());
   //while (it != lineEdits.end())
   //{
   //   if (((MenuItem*)(*it))->itemIndex() == item)
   //   {
   //      int index((dynamic_cast<MenuItem*>(*it))->currentIndex());
   //      //_keyPadParam._buttonNames[(dynamic_cast<MenuItem*>(*it))->currentIndex()];

   //      //QString strValue;
   //      //Double2String(strValue, value);
   //      //QString strUnit(QString::fromWCharArray(unit));

   //      ////QString str(QString("==item [%1] value=%2 unit=%3").arg(item).arg(value).arg(QString::fromWCharArray(unit)));
   //      ////qInfo(str.toStdString().c_str());

   //      //(dynamic_cast<QLineEdit*>(*it))->setText(QString("%1 %2").arg(strValue).arg(strUnit));
   //      break;
   //   }
   //   else {
   //      //QString str(QString("!=item [%1] value=%2 unit=%3").arg(item).arg(value).arg(QString::fromWCharArray(unit)));
   //      //qInfo(str.toStdString().c_str());
   //   }
   //   ++it;
   //}

   //int index((int)value);
   //QList<QObject*>::iterator itr(radioButtons.begin());
   //while (itr != radioButtons.end()) {
   //   if (((MenuRadioButton*)(*itr))->index() == index) {
   //      ((MenuRadioButton*)(*itr))->setChecked(true);
   //   }
   //   ++itr;
   //}

   //int index((int)value);
   QList<QObject*>::iterator itpb(pushButtons.begin());
   while (itpb != pushButtons.end()) {
      if (((MenuPushButton*)(*itpb))->itemIndex() == item) {
         if (type == 0) {
            if (value == 1)
               ((MenuPushButton*)(*itpb))->groupBox()->setVisible(true);
            else
               ((MenuPushButton*)(*itpb))->groupBox()->setVisible(false);
         }
         else if (type == 1) {
            if (value == 1)
               ((MenuPushButton*)(*itpb))->setEnabled(true);
            else
               ((MenuPushButton*)(*itpb))->setEnabled(false);
         }
      }
      ++itpb;
   }

   QList<QObject*>::iterator itle(lineEdits.begin());
   while (itle != lineEdits.end()) {
      if (((MenuItem*)(*itle))->itemIndex() == item) {
         if (type == 0) {
            if (value == 1) 
               ((MenuItem*)(*itle))->groupBox()->setVisible(true);
            else 
               ((MenuItem*)(*itle))->groupBox()->setVisible(false);
         }
         else if (type == 1) {
            if (value == 1)
               ((MenuItem*)(*itle))->setEnabled(true);
            else
               ((MenuItem*)(*itle))->setEnabled(false);
         }
      }
      ++itle;
   }

   QList<QObject*>::iterator itrb(radioButtons.begin());
   while (itrb != radioButtons.end()) {
      if (((MenuRadioButton*)(*itrb))->itemIndex() == item) {
         if (type == 0) {
            if (value == 1)
               ((MenuRadioButton*)(*itrb))->groupBox()->setVisible(true);
            else
               ((MenuRadioButton*)(*itrb))->groupBox()->setVisible(false);
         }
         else if (type == 1) {
            if (value == 1)
               ((MenuRadioButton*)(*itrb))->setEnabled(true);
            else
               ((MenuRadioButton*)(*itrb))->setEnabled(false);
         }
      }
      ++itrb;
   }

   QList<QObject*>::iterator itcb(comboBoxes.begin());
   while (itcb != comboBoxes.end()) {
      if (((MenuComboBox*)(*itcb))->itemIndex() == item) {
         if (type == 0) {
            if (value == 1)
               ((MenuComboBox*)(*itcb))->groupBox()->setVisible(true);
            else
               ((MenuComboBox*)(*itcb))->groupBox()->setVisible(false);
         }
         else if (type == 1) {
            if (value == 1)
               ((MenuComboBox*)(*itcb))->setEnabled(true);
            else
               ((MenuComboBox*)(*itcb))->setEnabled(false);
         }
      }
      ++itcb;
   }

   //int index2((int)value);
   //QList<QObject*>::iterator itr2(comboBoxes.begin());
   //while (itr2 != comboBoxes.end()) {
   //   if (((MenuComboBox*)(*itr2))->itemIndex() == item) {
   //      ((MenuComboBox*)(*itr2))->setCurrentIndex(index2);
   //   }
   //   ++itr2;
   //}

}

void MenuPage::changeData(int item, double value, wchar_t* unit)
{
   QList<QObject*>::iterator it( lineEdits.begin() );
   while (it != lineEdits.end() ) 
   {
      if (((MenuItem*)(*it)) != nullptr && ((MenuItem*)(*it))->itemIndex() == item )
      {
         int index((dynamic_cast<MenuItem*>(*it))->currentIndex());
         //_keyPadParam._buttonNames[(dynamic_cast<MenuItem*>(*it))->currentIndex()];

         QString strValue;
         //Double2String(strValue, value);
         gsa::controller->Double2String(strValue, value);

         QString strUnit(QString::fromWCharArray(unit));

         //QString str(QString("==item [%1] value=%2 unit=%3").arg(item).arg(value).arg(QString::fromWCharArray(unit)));
         //qInfo(str.toStdString().c_str());

         (dynamic_cast<QLineEdit*>(*it))->setText(QString("%1 %2").arg(strValue).arg(strUnit));
         break;
      }
      else {
         //QString str(QString("!=item [%1] value=%2 unit=%3").arg(item).arg(value).arg(QString::fromWCharArray(unit)));
         //qInfo(str.toStdString().c_str());
      }
      ++it;
   }

   //int index( (int)value );
   //QList<QObject*>::iterator itr(radioButtons.begin());
   //while (itr != radioButtons.end()) {
   //   if (((MenuRadioButton*)(*itr))->index() == index) {
   //      ((MenuRadioButton*)(*itr))->setChecked(true);
   //   }
   //   ++itr;
   //}

   int index((int)value);
   QList<QObject*>::iterator itr(radioButtons.begin());
   while (itr != radioButtons.end()) {
      if (((MenuRadioButton*)(*itr))->itemIndex() == item && ((MenuRadioButton*)(*itr))->index() == index ) {
         ((MenuRadioButton*)(*itr))->setChecked(true);
      }
      ++itr;
   }

   int index2((int)value);
   QList<QObject*>::iterator itr2(comboBoxes.begin());
   while (itr2 != comboBoxes.end()) {
      if (((MenuComboBox*)(*itr2))->itemIndex() == item) {
         ((MenuComboBox*)(*itr2))->setCurrentIndex(index2);
      }
      ++itr2;
   }

   //if (itObj != lineEdits.end()) {
   //   ((QLineEdit*)(*itObj))->setText(QString("%1").arg((int)value));
   //}

   int index3((int)value);
   QList<QObject*>::iterator itr3(colorSelectores.begin());
   while (itr3 != colorSelectores.end()) {
      if (((MenuColorSelector*)(*itr3))->itemIndex() == item) {
         QColor _color;
         _color.setRgb((unsigned int)value);
         ((MenuColorSelector*)(*itr3))->AbstractionColorChanged(_color);
      }
      ++itr3;
   }

}

//void MenuPage::addItemsOld(const gsa::t::GuiPad &guiPad, const int& pageIndex, std::map<gsa::t::KeyInfo, int> &keys)
//{
//   int length(guiPad.length);
//
//   //if (QString::fromWCharArray(guiItem.type) == QString("Separator")) {
//
//   for (int j = 0; j < guiPad.length; j++) {
//      //QString name = QString::fromWCharArray(guiPad.items[j].name);
//      QString type = QString::fromWCharArray(guiPad.items[j].type);
//      if (type == QString("Switch") || type == QString("CheckList")) {
//         implAddItems(this, _verticalLayout2, guiPad.items[j]);
//      }
//      else {
//         implAddItem(this, _verticalLayout2, guiPad.items[j]);
//      }
//
//      gsa::t::KeyInfo keyInfo;
//      keyInfo.keyCode = guiPad.items[j].keyCode;
//      keyInfo.nativeModifiers = guiPad.items[j].nativeModifiers;
//      keys.insert(std::pair<gsa::t::KeyInfo, int>(keyInfo, pageIndex));
//      //guiPad.items[j].keyCode;
//      //guiPad.items[j].nativeModifiers;
//   }
//}

void MenuPage::addItems(const gsa::t::GuiPad &guiPad, const int& pageIndex, std::map<gsa::t::KeyInfo, gsa::t::ItemInfo> &keys)
{
   int length(guiPad.length);

   //if (QString::fromWCharArray(guiItem.type) == QString("Separator")) {

   bool beginGroup(false);
   for (int j = 0; j < guiPad.length; j++) {
      QString type = QString::fromWCharArray(guiPad.items[j].type);
      if (type == QString("Separator")) {
         if (beginGroup == true) {
            beginGroup = false;
            implGroupEnd();
         }
         else {
            beginGroup = true;
            implGroupBegin(this, _verticalLayout2, guiPad.items[j]);
         }
      }
      else {
         if (beginGroup == false) {
            beginGroup = true;
            implGroupBegin(this, _verticalLayout2, guiPad.items[j]);
         }
         implAddItemNew(this, _verticalLayout2, guiPad.items[j]);
      }

      //if (type == QString("Switch") || type == QString("CheckList")) {
      //   implAddItems(this, _verticalLayout2, guiPad.items[j]);
      //}
      //else {
      //   implAddItem(this, _verticalLayout2, guiPad.items[j]);
      //}

      gsa::t::KeyInfo keyInfo;
      keyInfo.keyCode = guiPad.items[j].keyCode;
      keyInfo.nativeModifiers = guiPad.items[j].nativeModifiers;

      gsa::t::ItemInfo itemInfo;
      itemInfo.item = guiPad.items[j].itemIndex;
      itemInfo.pageIndex = pageIndex;
      itemInfo.type = QString::fromWCharArray(guiPad.items[j].type);
      itemInfo.itemtype = guiPad.items[j].itemtype;

      //keys.insert(std::pair<gsa::t::KeyInfo, int>(keyInfo, pageIndex));
      keys.insert(std::pair<gsa::t::KeyInfo, gsa::t::ItemInfo>(keyInfo, itemInfo));

      int i(0);
      //guiPad.items[j].keyCode;
      //guiPad.items[j].nativeModifiers;
   }
   if (beginGroup == true) {
      beginGroup = false;
      implGroupEnd();
   }
}

int MenuPage::implGroupBegin(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem)
{
   //QGroupBox *groupBoxTest(nullptr);

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_mainWindow->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_mainWindow->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_mainWindow->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_mainWindow->indentindexes());

   gsa::t::ThemeItem item_;
   gsa::t::ThemeItem itemMenu_;

   for (auto &item : _theme->themeItems) {
      if (_indentindexes.find(std::wstring(item.description)) != _indentindexes.end()) {
         switch (_indentindexes[std::wstring(item.description)])
         {
         case gsa::t::IndentIndex::UnifyingFrame: //Unifying frame of the menu area from the size of the control 
         {
            item_ = item;
            break;
         }
         default:
            break;
         }
      }
   }

   for (auto &item : _theme->themeItems) {
      if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
         switch (_colorindexes[std::wstring(item.description)])
         {
         case gsa::t::ColorIndex::ControlMenu: //Control in the menu area(composition) 
         {
            itemMenu_ = item;
            break;
         }
         default:
            break;
         }
      }
   }

   double value(0.0);
   _mainWindow->GetValue(item_.value, value);
   int r, g, b;
   _mainWindow->GetRgb(itemMenu_.value, r, g, b);

   _groupBoxTest = new QGroupBox(page);
   _groupBoxTest->setObjectName(QStringLiteral("groupBoxTest"));
   _verticalLayout_2 = new QVBoxLayout(_groupBoxTest);
   _verticalLayout_2->setSpacing(0); //(6);
   //_verticalLayout_2->setContentsMargins(11, 11, 11, 11);
   //_verticalLayout_2->setContentsMargins(0, 0, 0, 0);
   _verticalLayout_2->setContentsMargins((int)value, (int)value, (int)value, (int)value);
   _verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

   //_groupBoxTest->setStyleSheet(QString("%1 "
   //   //"QWidget { " //"QComboBox { " 
   //   //"background-color: rgb(%2, %3, %4); "
   //   //"} "
   //   "QGroupBox{"
   //   "background-color: red; "
   //   "margin-top:1em; "
   //   "} "
   //).arg(_groupBoxTest->styleSheet()) //.arg(r).arg(g).arg(b)
   //);

   if (guiItem.IsVisible == 0)
      _groupBoxTest->setVisible(false);
   else if(guiItem.IsVisible == 1)
      _groupBoxTest->setVisible(true);

   return 1;
}

void MenuPage::implGroupEnd(void)
{
   _verticalLayout2->addWidget(_groupBoxTest);
}

void MenuPage::implAddItemNew(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem)
{
   //ComboBox, Separator, Button, List, EditBox, Switch, CheckBox, CheckList 
   //CheckBox -> CheckBox 
   //CheckList -> RadioButton 
   //Main::MainWindow *_mainWindow;

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_mainWindow->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_mainWindow->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_mainWindow->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_mainWindow->indentindexes());

   gsa::t::ThemeItem item_;
   gsa::t::ThemeItem itemMenuItem_;
   gsa::t::ThemeItem itemButton_;
   gsa::t::ThemeItem itemRadioButton_; //???
   gsa::t::ThemeItem itemCheckbox_;
   gsa::t::ThemeItem itemDropDownList_;
   gsa::t::ThemeItem itemDropDownListBackground_;
   gsa::t::ThemeItem itemDropDownListItem_;
   gsa::t::ThemeItem itemDropDownListSelected_;
   gsa::t::ThemeItem itemSwitch_;
   gsa::t::ThemeItem itemNumericValue_;
   gsa::t::ThemeItem itemColorSelector_;

   itemDropDownListBackground_.description = nullptr;
   itemDropDownListItem_.description = nullptr;
   itemDropDownListSelected_.description = nullptr;

   for (auto &item : _theme->themeItems) { 
      if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) { 
         switch (_colorindexes[std::wstring(item.description)]) 
         { 
         case gsa::t::ColorIndex::ControlDropDownMenu: itemDropDownListBackground_ = item;  break; 
         case gsa::t::ColorIndex::SelectedLine: itemDropDownListSelected_ = item;  break;
         case gsa::t::ColorIndex::UnselectedString: itemDropDownListItem_ = item;  break;
         default:
            break;
         }
      }
   }

   for (auto &item : _theme->themeItems) {
      if (_sizeindexes.find(std::wstring(item.description)) != _sizeindexes.end()) {
         switch (_sizeindexes[std::wstring(item.description)])
         {
         case gsa::t::SizeIndex::MenuItem: //Menu item in the drop-down menu
         {
            itemMenuItem_ = item;
            break;
         }
         case gsa::t::SizeIndex::Button: //Control button in the menu area
         {
            itemButton_ = item;
            break;
         }
         case gsa::t::SizeIndex::RadioButton: //Control radio button in the menu area
         {
            itemRadioButton_ = item;
            break;
         }
         case gsa::t::SizeIndex::Checkbox: //Control checkbox in the menu area
         {
            itemCheckbox_ = item;
            break;
         }
         case gsa::t::SizeIndex::DropDownList: //Control drop - down list in the menu area
         {
            itemDropDownList_ = item;
            break;
         }
         case gsa::t::SizeIndex::Switch: //Control item is a switch in the menu area
         {
            itemSwitch_ = item;
            break;
         }
         case gsa::t::SizeIndex::NumericValue: //Control is a numeric value in the menu area
         {
            itemNumericValue_ = item;
            break;
         }
         default:
            break;
         }
      }
   }
   double value(0.0);
   //_mainWindow->GetValue(item_.value, value);

   if (QString::fromWCharArray(guiItem.type) == QString("Separator")) {
      QFrame *lineHoriz = new QFrame(_groupBoxTest);
      lineHoriz->setObjectName(QStringLiteral("lineHoriz"));
      lineHoriz->setFrameShape(QFrame::HLine);
      lineHoriz->setFrameShadow(QFrame::Sunken);
      lineHoriz->setFocusPolicy(Qt::NoFocus);

      if (guiItem.IsEnabled == 0) {
         lineHoriz->setEnabled(false);
      }
      if (guiItem.IsVisible == 0) {
         lineHoriz->setVisible(false);
      }

      _verticalLayout_2->addWidget(lineHoriz);
   }
   else if (QString::fromWCharArray(guiItem.type) == QString("Switch") || QString::fromWCharArray(guiItem.type) == QString("CheckList")) {
      //QString itemName = QString::fromWCharArray(guiItem.name);
      if (QString::fromWCharArray(guiItem.name).length() > 0) {
         //int i(0);
         QLabel* label = new QLabel(_groupBoxTest);
         label->setObjectName(QStringLiteral("label"));
         label->setMaximumSize(QSize(16777215, 20));
         label->setFocusPolicy(Qt::NoFocus);
         label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));

         //if (guiItem.IsEnabled == 0) {
         //   label->setEnabled(false);
         //}
         //if (guiItem.IsVisible == 0) {
         //   label->setVisible(false);
         //}

         _verticalLayout_2->addWidget(label);

         radioButtons.push_back(label);
      }

      QStringList names;
      for (int k = 0; k < guiItem.guilist.length; k++) {
         names << QString::fromWCharArray(guiItem.guilist.names[k]);
      }

      int i(0);
      for (auto name : names) {
         MenuRadioButton *radioButton = new MenuRadioButton(_groupBoxTest, guiItem.itemIndex, i, _groupBoxTest);
         radioButton->setObjectName(name);
         radioButton->setText(name);
         radioButton->setContentsMargins(0, 0, 0, 0);
         radioButton->setFocusPolicy(Qt::ClickFocus);

         if (guiItem.IsEnabled == 0) {
            radioButton->setEnabled(false);
         }
         //if (guiItem.IsVisible == 0) {
         //   radioButton->setVisible(false);
         //}

         QSize size_ = radioButton->size();
         //size_.setHeight(size_.height() * 2);
         //size_.setWidth(size_.width() * 2);
         _mainWindow->GetValue(itemCheckbox_.value, value);
         _mainWindow->GetValue(itemSwitch_.value, value);
         double coef = (double)size_.width() / size_.height();
         size_.setHeight((int)value);
         size_.setWidth((int)(value*coef));
         //radioButton->setMinimumSize(size_);
         //radioButton->setMaximumSize(size_);
         radioButton->setMinimumHeight(size_.height());
         radioButton->setMaximumHeight(size_.height());

         _verticalLayout_2->addWidget(radioButton);

         radioButtons.push_back(radioButton);

         //if (i++ == index) radioButton->setChecked(true);
         if (i++ == guiItem.guilist.index) radioButton->setChecked(true);

         connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(slotRadioButton(bool)));
      }
   }
   else if (QString::fromWCharArray(guiItem.type) == QString("Button")) {
      //QString itemName = QString::fromWCharArray(guiItem.name);
      if (QString::fromWCharArray(guiItem.name).length() > 0) {
         //int i(0);
         QLabel* label = new QLabel(_groupBoxTest);
         label->setObjectName(QStringLiteral("label"));
         label->setMaximumSize(QSize(16777215, 20));
         label->setFocusPolicy(Qt::NoFocus);
         label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));

         //if (guiItem.IsEnabled == 0) {
         //   label->setEnabled(false);
         //}
         //if (guiItem.IsVisible == 0) {
         //   label->setVisible(false);
         //}

         _verticalLayout_2->addWidget(label);

         pushButtons.push_back(label);
      }

      MenuPushButton *pushButton;

      pushButton = new MenuPushButton(_groupBoxTest, guiItem.itemIndex, _groupBoxTest);
      pushButton->setObjectName(QStringLiteral("pushButton"));

      //pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
      pushButton->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));
      pushButton->setFocusPolicy(Qt::ClickFocus);

      if (guiItem.IsEnabled == 0) {
         pushButton->setEnabled(false);
      }
      //if (guiItem.IsVisible == 0) {
      //   pushButton->setVisible(false);
      //}

      QSize size_ = pushButton->size();
      //size_.setHeight(size_.height() * 2);
      //size_.setWidth(size_.width() * 2);
      _mainWindow->GetValue(itemButton_.value, value);
      double coef = (double)size_.width() / size_.height();
      size_.setHeight((int)value);
      size_.setWidth((int)(value*coef));
      //pushButton->setMinimumSize(size_);
      //pushButton->setMaximumSize(size_);
      pushButton->setMinimumHeight(size_.height());
      pushButton->setMaximumHeight(size_.height());

      _verticalLayout_2->addWidget(pushButton);

      pushButtons.push_back(pushButton);

      connect(pushButton, SIGNAL(clicked()), this, SLOT(slotButton()));
   }
   else if (QString::fromWCharArray(guiItem.type) == QString("EditBox")) 
   {
      //if (guiItem.IsVisible == 0) 
      //QGroupBox* GroupFreq = new QGroupBox(_groupBoxTest);
      //GroupFreq->setObjectName(QStringLiteral("GroupFreq"));
      //GroupFreq->setMaximumSize(QSize(16777215, 60));
      //GroupFreq->setFlat(false);
      //GroupFreq->setCheckable(false);
      //QVBoxLayout* verticalLayout_2 = new QVBoxLayout(GroupFreq);
      //verticalLayout_2->setSpacing(4);
      //verticalLayout_2->setContentsMargins(11, 11, 11, 11);
      //verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
      //verticalLayout_2->setContentsMargins(4, 4, 4, 4);

      //QLabel* label = new QLabel(_groupBoxTest);
      //label->setObjectName(QStringLiteral("label"));
      //label->setMaximumSize(QSize(16777215, 20));
      //label->setFocusPolicy(Qt::NoFocus);
      //label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));

      //_verticalLayout_2->addWidget(label);

      if (QString::fromWCharArray(guiItem.name).length() > 0) {
         //int i(0);
         QLabel* label = new QLabel(_groupBoxTest);
         label->setObjectName(QStringLiteral("label"));
         label->setMaximumSize(QSize(16777215, 20));
         label->setFocusPolicy(Qt::NoFocus);
         label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));

         //if (guiItem.IsEnabled == 0) {
         //   label->setEnabled(false);
         //}
         //if (guiItem.IsVisible == 0) {
         //   label->setVisible(false);
         //}

         _verticalLayout_2->addWidget(label);

         lineEdits.push_back(label);
      }

      MenuItem* lineEdit = new MenuItem(_groupBoxTest, guiItem.itemIndex, guiItem.currentIndex, this, _groupBoxTest);
      lineEdit->setObjectName(QStringLiteral("lineEdit"));
      lineEdit->setMaximumSize(QSize(16777215, 32));
      lineEdit->setReadOnly(true);
      lineEdit->setFocusPolicy(Qt::StrongFocus); //(Qt::WheelFocus); //(Qt::TabFocus);

      //lineEdit->setInputMask("000.000.000.000");
      //lineEdit->setInputMask("000 000 000 000");

      //lineEdit->setStyleSheet("QLineEdit[readOnly = \"true\"]{ color: gray }");
      QString styleSheet = 
         //"QLineEdit { border: 1px solid; border-color:#dcdcdc; border-radius: 4px;} "
         "QLineEdit:focus { "
         "border:2px solid gray; "
         "background-color: rgb(119,119,119); "
         "}";
      lineEdit->setStyleSheet(styleSheet);

      if (guiItem.IsEnabled == 0) {
         lineEdit->setEnabled(false);
      }
      //if (guiItem.IsVisible == 0) {
      //   lineEdit->setVisible(false);
      //}

      _verticalLayout_2->addWidget(lineEdit);

      //QTextEdit *textEdit = new QTextEdit(GroupFreq);
      //textEdit->setObjectName(QStringLiteral("textEdit"));
      //_verticalLayout_2->addWidget(textEdit);

      fillButtonNames((wchar_t **)guiItem.units, guiItem.length);
      lineEdit->setButtonNames(_keyPadParam._buttonNames);

      QString strValue;
      //Double2String(strValue, guiItem.value);
      gsa::controller->Double2String(strValue, guiItem.value);

      QString unit = _keyPadParam._buttonNames[guiItem.currentIndex];
      lineEdit->setText(QString("%1 %2").arg(strValue).arg(_keyPadParam._buttonNames[guiItem.currentIndex]));

      lineEdit->setName(guiItem.name);

      QSize size_ = lineEdit->size();
      //size_.setHeight(size_.height() * 2);
      //size_.setWidth(size_.width() * 2);
      _mainWindow->GetValue(itemNumericValue_.value, value);
      double coef = (double)size_.width() / size_.height();
      size_.setHeight((int)value);
      size_.setWidth((int)(value*coef));
      //lineEdit->setMinimumSize(size_);
      //lineEdit->setMaximumSize(size_);
      lineEdit->setMinimumHeight(size_.height());
      lineEdit->setMaximumHeight(size_.height());

      lineEdits.push_back(lineEdit);

      lineEdit->installEventFilter(this);

      _groupBoxTest->setTitle(QString());
      //label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));

      //QString str(QString("[%1] name=%2").arg(guiItem.itemIndex).arg(QString::fromWCharArray(guiItem.name).toStdString().c_str()) );
      //qInfo(str.toStdString().c_str());

      connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(doReturnPressed()));
   } 
   else if (QString::fromWCharArray(guiItem.type) == QString("ComboBox")) { 

      //QString itemName = QString::fromWCharArray(guiItem.name); 
      if (QString::fromWCharArray(guiItem.name).length() > 0) { 
         //int i(0); 
         QLabel* label = new QLabel(_groupBoxTest); 
         label->setObjectName(QStringLiteral("label")); 
         label->setMaximumSize(QSize(16777215, 20)); 
         label->setFocusPolicy(Qt::NoFocus); 
         label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR)); 

         //if (guiItem.IsEnabled == 0) {
         //   label->setEnabled(false);
         //}
         //if (guiItem.IsVisible == 0) {
         //   label->setVisible(false);
         //}

         _verticalLayout_2->addWidget(label);

         comboBoxes.push_back(label);
      }

      guiItem.units[0];

      QStringList names;
      for (int k = 0; k < guiItem.guilist.length; k++) {
         names << QString::fromWCharArray(guiItem.guilist.names[k]);
      }

      MenuComboBox *combo = new MenuComboBox(_groupBoxTest, guiItem.itemIndex, _groupBoxTest);

      //QtColorPicker;

      combo->setStyleSheet(
         "QComboBox{"
         "   border: 1px solid gray;"
         "   border-radius: 3px;"
         "   padding: 1px 18px 1px 3px;"
         "   min-width: 6em;"
         //"   min-height: 12em;"
         "   background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, "
         "   stop : 0 #E1E1E1, stop: 0.4 #DDDDDD,"
         "   stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
         "}"
         " \
         "
      );
      //QComboBox::drop-down { \
      //   width: 0px; \
      //   height:0px; \
      //   border - radius: 0px; \
      //} \
      //   QComboBox::drop - down:hover \
      //{ \
      //   border: solid; \
      //   border - radius: 5px; \
      //   background - color: rgb(0, 170, 255); \
      //} \
      //   QComboBox QAbstractItemView{ \
      //       border: 2px solid darkgray; \
      //       alternate - background - color: red; \
      //       selection - background - color: lightgray; \
      //} \
      //border: none; \

      if (itemDropDownListBackground_.description != nullptr)
      {
         //gsa::t::ThemeItem background(itemDropDownListBackground_);

         int r, g, b;
         _mainWindow->GetRgb(itemDropDownListBackground_.value, r, g, b);

         combo->setStyleSheet(QString("%1 " 
            "QWidget { " //"QComboBox { " 
            "background-color: rgb(%2, %3, %4); " 
            "} " 
         ).arg(combo->styleSheet()).arg(r).arg(g).arg(b)
         );

      }

      if (itemDropDownListItem_.description != nullptr && itemDropDownListSelected_.description != nullptr )
      {
         int r, g, b;
         _mainWindow->GetRgb(itemDropDownListItem_.value, r, g, b);
         int r2, g2, b2;
         _mainWindow->GetRgb(itemDropDownListSelected_.value, r2, g2, b2);

         QListView *view = new QListView(combo);
         view->setStyleSheet(QString("%1 "
            "QListView::item { "
            "background-color: rgb(%2, %3, %4); "
            "} "
            "QListView::item:selected { "
            "background-color: rgb(%5, %6, %7); "
            "} "
         ).arg(view->styleSheet()).arg(r).arg(g).arg(b).arg(r2).arg(g2).arg(b2)
         );
         combo->setView(view);
      }

      for (auto name : names) {
         combo->addItem(name);
      }

      //((QTableView*)combo->view())->setRowHeight(0, 45);

      //combo->setFocusPolicy(Qt::NoFocus);
      //combo->setFocusPolicy(Qt::ClickFocus);
      combo->setFocusPolicy(Qt::StrongFocus);

      QSize size_ = combo->size();
      //size_.setHeight(size_.height() * 2);
      //size_.setWidth(size_.width() * 2);
      _mainWindow->GetValue(itemDropDownList_.value, value);
      double coef = (double)size_.width() / size_.height();
      size_.setHeight((int)value);
      size_.setWidth((int)(value*coef));
      //combo->setMinimumSize(size_);
      //combo->setMaximumSize(size_);
      combo->setMinimumHeight(size_.height());
      combo->setMaximumHeight(size_.height());

      comboBoxes.push_back(combo);

      //combo->installEventFilter(this);

      connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
      connect(combo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(indexChanged(const QString&)));

      if (guiItem.IsEnabled == 0) {
         combo->setEnabled(false);
      }
      //if (guiItem.IsVisible == 0) {
      //   combo->setVisible(false);
      //}

      _verticalLayout_2->addWidget(combo);
   }
   else if (QString::fromWCharArray(guiItem.type) == QString("ColourSelector")) 
   {
      //QString itemName = QString::fromWCharArray(guiItem.name);
      if (QString::fromWCharArray(guiItem.name).length() > 0) {
         //int i(0);
         QLabel* label = new QLabel(_groupBoxTest);
         label->setObjectName(QStringLiteral("label"));
         label->setMaximumSize(QSize(16777215, 20));
         label->setFocusPolicy(Qt::NoFocus);

         int _colorInt = guiItem.value;
         QColor _color;
         _color.setRgb((unsigned int)guiItem.value);

         int r;
         int g;
         int b;
         _color.getRgb(&r, &g, &b);

         label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));

         //if (guiItem.IsEnabled == 0) {
         //   label->setEnabled(false);
         //}
         //if (guiItem.IsVisible == 0) {
         //   label->setVisible(false);
         //}

         _verticalLayout_2->addWidget(label);

         colorSelectores.push_back(label);

         //MenuComboBox *colorSelector = new MenuComboBox(_groupBoxTest, guiItem.itemIndex); 
         //Color_Selector* colorSelector = new Color_Selector; 
         MenuColorSelector* colorSelector = new MenuColorSelector(_groupBoxTest, guiItem.itemIndex, _groupBoxTest);
         if (colorSelector != nullptr) 
         { 
            colorSelector->setFocusPolicy(Qt::StrongFocus); 

            //QColor _color(255, 0, 0); 
            colorSelector->setDisplayMode(Color_Preview::AllAlpha); 
            colorSelector->setColor(_color); 
            //p->mapper.setMapping(colorSelector, col); 
            //connect(colorSelector, SIGNAL(colorChanged(QColor)), &p->mapper, SLOT(map())); 

            //connect(this, SIGNAL(wheelFlagsChanged(Color_Wheel::Display_Flags)), colorSelector, SLOT(setWheelFlags(Color_Wheel::Display_Flags))); 
            connect(colorSelector, SIGNAL(colorSelected(QColor)), this, SLOT(slotColorSelected(QColor))); 

            //connect(colorSelector, SIGNAL(clicked()), this, SLOT(slotColorSelector())); 
            //appendWidget(cbs); 
            //setRowHeight(count() - 1, 22); 

            colorSelectores.push_back(colorSelector); 

            //connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int))); 
            //connect(combo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(indexChanged(const QString&))); 

            if (guiItem.IsEnabled == 0) { 
               colorSelector->setEnabled(false); 
            } 
            //if (guiItem.IsVisible == 0) { 
            //   colorSelector->setVisible(false); 
            //} 

            QSize size_ = colorSelector->size();
            //size_.setHeight(size_.height() * 2);
            //size_.setWidth(size_.width() * 2);
            _mainWindow->GetValue(itemSwitch_.value, value);
            double coef = (double)size_.width() / size_.height();
            size_.setHeight((int)value);
            size_.setWidth((int)(value*coef));
            //colorSelector->setMinimumSize(size_);
            //colorSelector->setMaximumSize(size_);

            _verticalLayout_2->addWidget(colorSelector);
         }
      }

      int i(0);
   }
   else if (QString::fromWCharArray(guiItem.type) == QString("CheckBox"))
   {
      int i(0);
   }
   else {
      int i(0);
   } //CheckBox, CheckList
}

void MenuPage::setCustomizing(void)
{
   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_mainWindow->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_mainWindow->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_mainWindow->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_mainWindow->indentindexes());

   //if (_mainWindow->colorindexes().size() > 18) {
   //   int  iiiii = 90;
   //}

   typedef struct {
      gsa::t::ThemeItem region;
      gsa::t::ThemeItem border;
   } tagItem;

   std::map<QWidget*, gsa::t::ThemeFont> widgetFonts_;
   //std::map<QWidget*, gsa::t::ThemeItem> widgetItems_;
   std::map<QWidget*, tagItem> widgetItems_;
   gsa::t::ThemeFont font_;
   gsa::t::ThemeItem item_;

   if (_theme != nullptr)
   {
      QString description("Default");
      gsa::t::ThemeFont *themeFont(std::find_if(std::begin(_theme->themeFonts), std::end(_theme->themeFonts),
         [&description](const gsa::t::ThemeFont& font) { return QString::fromWCharArray(font.description) == description; }));
      gsa::t::ThemeItem *themeItem(std::find_if(std::begin(_theme->themeItems), std::end(_theme->themeItems),
         [&description](const gsa::t::ThemeItem& item) { return QString::fromWCharArray(item.description) == description; }));

      //if (std::end(_theme->themeFonts) != std::find_if(std::begin(_theme->themeFonts), std::end(_theme->themeFonts), 
      //   [&description](const gsa::t::ThemeFont& font) { return QString::fromWCharArray(font.description) == description; } ))
      if (themeFont == std::end(_theme->themeFonts)) font_.description = nullptr;
      else font_ = *themeFont;
      if (themeItem == std::end(_theme->themeItems)) item_.description = nullptr;
      else item_ = *themeItem;

      //widgetFonts_[ui->comboBox] = font_;
      //widgetItems_[ui->comboBox] = item_;

      lineEdits;
      pushButtons;
      radioButtons;
      comboBoxes;
      colorSelectores;

      for (auto &item : lineEdits) {
         widgetFonts_[(QWidget*)item] = font_;
         widgetItems_[(QWidget*)item].region = item_;
      }
      for (auto &item : pushButtons) {
         widgetFonts_[(QWidget*)item] = font_;
         widgetItems_[(QWidget*)item].region = item_;
         //widgetBorders_[(QWidget*)item] = item_;
      }
      for (auto &item : radioButtons) {
         widgetFonts_[(QWidget*)item] = font_;
         widgetItems_[(QWidget*)item].region = item_;
      }
      for (auto &item : comboBoxes) {
         widgetFonts_[(QWidget*)item] = font_;
         widgetItems_[(QWidget*)item].region = item_;
      }
      for (auto &item : colorSelectores) {
         widgetFonts_[(QWidget*)item] = font_;
         widgetItems_[(QWidget*)item].region = item_;
      }

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::CurrentMeasurement: //Current measurement selection area
            case gsa::t::FontIndex::MeasurementScale: //Measurement scale
            case gsa::t::FontIndex::PanelHeader: //Panel header
            case gsa::t::FontIndex::QuickAccess: //Quick Access Area Tab
            case gsa::t::FontIndex::DropDownMenu: //Drop - down menu items(list of songs)
            case gsa::t::FontIndex::SelectedMenu: //Tabs of the selected menu(name of the subcomposition)
               break;
            case gsa::t::FontIndex::ControlsSelectedTab: //Controls located in the selected tab
            {
               //widgetFonts_[ui->comboBox] = font;
               for (auto &item : lineEdits) {
                  widgetFonts_[(QWidget*)item] = font;
               }
               for (auto &item : pushButtons) {
                  widgetFonts_[(QWidget*)item] = font;
               }
               for (auto &item : radioButtons) {
                  widgetFonts_[(QWidget*)item] = font;
               }
               for (auto &item : comboBoxes) {
                  widgetFonts_[(QWidget*)item] = font;
               }
               for (auto &item : colorSelectores) {
                  widgetFonts_[(QWidget*)item] = font;
               }
               break;
            }
            case gsa::t::FontIndex::ActiveMarker: //Displaying the active marker in the graphics area
            case gsa::t::FontIndex::InactiveMarker: //Displaying inactive marker in the graphics area
            case gsa::t::FontIndex::ActiveMarkerTable: //Displaying the active marker in the marker table
            case gsa::t::FontIndex::Default: //Default
            default:
               break;
            }
         }
      }

      //if (_mainWindow->colorindexes().size() > 18) {
      //   int  iiiii = 90;
      //}

      for (auto &themeItem : _theme->themeItems) {
         switch (themeItem.type)
         {
         case 0:
         {
            if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) {
               switch (_colorindexes[std::wstring(themeItem.description)])
               {
               case gsa::t::ColorIndex::DisplayArea:
               case gsa::t::ColorIndex::GraphicPanelScale: //Graphic panel scale 
               case gsa::t::ColorIndex::TableBorders: //Borders of the table display 
               case gsa::t::ColorIndex::CurrentMeasurement: //Current measurement selection area 
               case gsa::t::ColorIndex::TabSelectionArea: //Tab in the general dimension selection area 
               case gsa::t::ColorIndex::QuickAccess: //Tabs in the quick access area 
               case gsa::t::ColorIndex::DropDownMenu: //Drop down menu 
                  break;
               case gsa::t::ColorIndex::UnifyingFrame: //Unifying frame in the menu area
               {
                  //widgetItems_[ui->comboBox] = item;
                  for (auto &item : lineEdits) {
                     widgetItems_[(QWidget*)item].region = themeItem;
                  }
                  for (auto &item : pushButtons) {
                     widgetItems_[(QWidget*)item].region = themeItem;
                  }
                  for (auto &item : radioButtons) {
                     widgetItems_[(QWidget*)item].region = themeItem;
                  }
                  for (auto &item : comboBoxes) {
                     widgetItems_[(QWidget*)item].region = themeItem;
                  }
                  for (auto &item : colorSelectores) {
                     widgetItems_[(QWidget*)item].region = themeItem;
                  }
                  break;
               }
               case gsa::t::ColorIndex::UnifyingFrameBorder: //Border of the unifying frame in the menu area
               {
                  //widgetItems_[ui->comboBox] = item;
                  for (auto &item : lineEdits) {
                     widgetItems_[(QWidget*)item].border = themeItem;
                  }
                  for (auto &item : pushButtons) {
                     widgetItems_[(QWidget*)item].border = themeItem;
                  }
                  for (auto &item : radioButtons) {
                     widgetItems_[(QWidget*)item].border = themeItem;
                  }
                  for (auto &item : comboBoxes) {
                     widgetItems_[(QWidget*)item].border = themeItem;
                  }
                  for (auto &item : colorSelectores) {
                     widgetItems_[(QWidget*)item].border = themeItem;
                  }
                  break;
               }
               case gsa::t::ColorIndex::ControlDropDownMenu: //Control drop - down list in the menu area
               case gsa::t::ColorIndex::ControlDropDownPanel: //Control drop - down list in the panel(additional data area)
               case gsa::t::ColorIndex::PanelControl: //Control in the panel(additional data area)
               case gsa::t::ColorIndex::SelectedLine: //Selected line in the expanded control drop - down list
               case gsa::t::ColorIndex::UnselectedString: //Unselected string in expanded control drop - down list
               case gsa::t::ColorIndex::ElementsBorders: //Borders of the elements of the drop - down menu
               case gsa::t::ColorIndex::CompositionMenu: //Menu area(composition)
               case gsa::t::ColorIndex::ControlMenu: //Control in the menu area(composition)
               case gsa::t::ColorIndex::Default: //Default
               default:
                  break;
               }
            }
            break;
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

      //if (widgetFonts_[ui->comboBox].description != nullptr)
      //{
      //   gsa::t::ThemeFont font(widgetFonts_[ui->comboBox]);

      //   int r, g, b;
      //   _mainWindow->GetRgb(font.color, r, g, b);

      //   ui->comboBox->setStyleSheet(QString("%1 "
      //      "QWidget { " //"QComboBox { " 
      //      "font-family: %2; "
      //      "font-size: %3pt; " //"font-size: %3px; " 
      //      "font-weight: %4; "
      //      "color: rgb(%5, %6, %7); "
      //      "}"
      //   ).arg(ui->comboBox->styleSheet()).arg(QString::fromWCharArray(font.family)).arg(font.size).arg(QString::fromWCharArray(font.style)).arg(r).arg(g).arg(b)
      //   );
      //}

      //if (widgetItems_[ui->comboBox].description != nullptr)
      //{
      //   gsa::t::ThemeItem font(widgetItems_[ui->comboBox]);

      //   int r, g, b;
      //   _mainWindow->GetRgb(font.value, r, g, b);

      //   ui->comboBox->setStyleSheet(QString("%1 "
      //      "QWidget { " //"QComboBox { " 
      //      "background-color: rgb(%2, %3, %4); "
      //      "}"
      //   ).arg(ui->comboBox->styleSheet()).arg(r).arg(g).arg(b)
      //   );
      //}

      //if (_mainWindow->colorindexes().size() > 18) {
      //   int  iiiii = 90;
      //}

      for (auto &item : widgetFonts_) {
         if (widgetFonts_[item.first].description != nullptr)
         {
            gsa::t::ThemeFont font(widgetFonts_[item.first]);

            int r, g, b;
            _mainWindow->GetRgb(font.color, r, g, b);

            item.first->setStyleSheet(QString("%1 " 
               "QWidget { " //"QComboBox { " 
               "font-family: %2; " 
               "font-size: %3pt; " //"font-size: %3px; " 
               "font-weight: %4; " 
               "color: rgb(%5, %6, %7); " 
               "}" 
            ).arg(item.first->styleSheet()).arg(QString::fromWCharArray(font.family)).arg(font.size).arg(QString::fromWCharArray(font.style)).arg(r).arg(g).arg(b)
            );
         }
      }
      
      //if (_mainWindow->colorindexes().size() > 18) {
      //   int  iiiii = 90;
      //}

      for (auto &item : widgetItems_) {
         if (widgetItems_[item.first].region.description != nullptr)
         {
            gsa::t::ThemeItem fontRegion(widgetItems_[item.first].region);
            gsa::t::ThemeItem fontBorder(widgetItems_[item.first].border);

            int r, g, b;
            _mainWindow->GetRgb(fontRegion.value, r, g, b);
            int r2, g2, b2;
            _mainWindow->GetRgb(fontBorder.value, r2, g2, b2);

            //item.first->setStyleSheet(QString("%1 "
            //   "QWidget { " //"QComboBox { " 
            //   "background-color: rgb(%2, %3, %4); "
            //   "}"
            //).arg(item.first->styleSheet()).arg(r).arg(g).arg(b)
            //);
            if (item.first->parent() != nullptr) {
               ((QWidget*)item.first->parent())->setStyleSheet(QString("%1 "
                  "QWidget { " //"QComboBox { " 
                  "background-color: rgb(%2, %3, %4); "
                  "border-color: rgb(%5, %6, %7); "
                  "}"
               ).arg(((QWidget*)item.first->parent())->styleSheet()).arg(r).arg(g).arg(b).arg(r2).arg(g2).arg(b2)
               );
            }
         }
      }
      //border-color: beige;
   }
}

void MenuPage::indexChanged(int index)
{
   QObject *senderObj = sender(); // This will give Sender object
   //QString senderObjName = senderObj->objectName();

   auto itObj = std::find_if(
      comboBoxes.begin(), comboBoxes.end(),
      [senderObj](QObject* p) { return p == senderObj; }
   );
   if (itObj != comboBoxes.end()) {
      double value((double)index);
      wcscpy(_text, L"TRUE");
      g_Parameter._SetValue(dynamic_cast<MenuComboBox*>(*itObj)->itemIndex(), value, _text, index);
   }
   else {
      int i(0);
   }

   int i(0);
}

void MenuPage::indexChanged(const QString& text)
{
   int i(0);
}

int MenuPage::setSelect(int index)
{
   return index;
}

bool MenuPage::setNext(void)
{
   return true;
}

bool MenuPage::setCurrentField(void)
{
   return true;
}

//void MenuPage::implAddItem(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem)
//{
//   if (QString::fromWCharArray(guiItem.type) == QString("Separator")) {
//      QFrame *lineHoriz = new QFrame(page);
//      lineHoriz->setObjectName(QStringLiteral("lineHoriz"));
//      lineHoriz->setFrameShape(QFrame::HLine);
//      lineHoriz->setFrameShadow(QFrame::Sunken);
//
//      _verticalLayout2->addWidget(lineHoriz);
//   }
//   else if (QString::fromWCharArray(guiItem.type) == QString("Switch") || QString::fromWCharArray(guiItem.type) == QString("CheckList")) {
//   }
//   else if (QString::fromWCharArray(guiItem.type) == QString("Button")) {
//      MenuPushButton *pushButton;
//
//      pushButton = new MenuPushButton(page, guiItem.itemIndex, nullptr);
//      pushButton->setObjectName(QStringLiteral("pushButton"));
//
//      //pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
//      pushButton->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));
//
//      _verticalLayout2->addWidget(pushButton);
//
//      pushButtons.push_back(pushButton);
//
//      connect(pushButton, SIGNAL(clicked()), this, SLOT(slotButton()));
//   }
//   else if (QString::fromWCharArray(guiItem.type) == QString("EditBox")) {
//      QGroupBox* GroupFreq = new QGroupBox(page);
//      GroupFreq->setObjectName(QStringLiteral("GroupFreq"));
//      GroupFreq->setMaximumSize(QSize(16777215, 60));
//      GroupFreq->setFlat(false);
//      GroupFreq->setCheckable(false);
//      QVBoxLayout* verticalLayout_2 = new QVBoxLayout(GroupFreq);
//      verticalLayout_2->setSpacing(4);
//      verticalLayout_2->setContentsMargins(11, 11, 11, 11);
//      verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
//      verticalLayout_2->setContentsMargins(4, 4, 4, 4);
//      QLabel* label = new QLabel(GroupFreq);
//      label->setObjectName(QStringLiteral("label"));
//      label->setMaximumSize(QSize(16777215, 20));
//
//      verticalLayout_2->addWidget(label);
//
//      //QLineEdit* lineEdit = new QLineEdit(GroupFreq);
//      MenuItem* lineEdit = new MenuItem(GroupFreq, guiItem.itemIndex, guiItem.currentIndex, this, GroupFreq);
//      lineEdit->setObjectName(QStringLiteral("lineEdit"));
//      lineEdit->setMaximumSize(QSize(16777215, 32));
//      verticalLayout_2->addWidget(lineEdit);
//
//      //QTextEdit *textEdit = new QTextEdit(GroupFreq);
//      //textEdit->setObjectName(QStringLiteral("textEdit"));
//      //verticalLayout_2->addWidget(textEdit);
//
//      fillButtonNames((wchar_t **)guiItem.units, guiItem.length);
//      lineEdit->setButtonNames(_keyPadParam._buttonNames);
//
//      _keyPadParam._buttonNames[guiItem.currentIndex];
//      lineEdit->setText(QString("%1 %2").arg(guiItem.value).arg(_keyPadParam._buttonNames[guiItem.currentIndex]));
//
//      lineEdits.push_back(lineEdit);
//
//      lineEdit->installEventFilter(this);
//
//      GroupFreq->setTitle(QString());
//      //label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
//      label->setText(QApplication::translate("MainWindow", QString::fromWCharArray(guiItem.name).toStdString().c_str(), Q_NULLPTR));
//
//      connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(doReturnPressed()));
//
//      _verticalLayout2->addWidget(GroupFreq);
//   }
//   else {
//      int i(0);
//   }
//}

//void MenuPage::implAddItems(QWidget *page, QVBoxLayout *verticalLayout, const gsa::t::GuiItem &guiItem)
//{
//   if (QString::fromWCharArray(guiItem.type) == QString("Separator")) {
//      //QFrame *lineHoriz = new QFrame(page);
//      //lineHoriz->setObjectName(QStringLiteral("lineHoriz"));
//      //lineHoriz->setFrameShape(QFrame::HLine);
//      //lineHoriz->setFrameShadow(QFrame::Sunken);
//
//      //verticalLayout->addWidget(lineHoriz);
//   }
//   else if (QString::fromWCharArray(guiItem.type) == QString("Switch") || QString::fromWCharArray(guiItem.type) == QString("CheckList")) {
//      QGroupBox *groupBoxTest(nullptr);
//
//      groupBoxTest = new QGroupBox(page);
//      groupBoxTest->setObjectName(QStringLiteral("groupBoxTest"));
//      QVBoxLayout* verticalLayout_2 = new QVBoxLayout(groupBoxTest);
//      verticalLayout_2->setSpacing(0); //(6);
//      verticalLayout_2->setContentsMargins(11, 11, 11, 11);
//      //verticalLayout_2->setContentsMargins(0, 0, 0, 0);
//      verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
//
//      QStringList names;
//      for (int k = 0; k < guiItem.guilist.length; k++) {
//         names << QString::fromWCharArray(guiItem.guilist.names[k]);
//      }
//
//      int i(0);
//      for (auto name : names) {
//         MenuRadioButton *radioButton = new MenuRadioButton(groupBoxTest, guiItem.itemIndex, i, groupBoxTest);
//         radioButton->setObjectName(name);
//         radioButton->setText(name);
//         radioButton->setContentsMargins(0, 0, 0, 0);
//
//         verticalLayout_2->addWidget(radioButton);
//
//         radioButtons.push_back(radioButton);
//
//         //if (i++ == index) radioButton->setChecked(true);
//         if (i++ == guiItem.guilist.index) radioButton->setChecked(true);
//
//         connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(slotRadioButton(bool)));
//      }
//
//      _verticalLayout2->addWidget(groupBoxTest);
//   }
//   else {
//      //QGroupBox* GroupFreq = new QGroupBox(page);
//      //GroupFreq->setObjectName(QStringLiteral("GroupFreq"));
//      //GroupFreq->setMaximumSize(QSize(16777215, 60));
//      //GroupFreq->setFlat(false);
//      //GroupFreq->setCheckable(false);
//      //QVBoxLayout* verticalLayout_2 = new QVBoxLayout(GroupFreq);
//      //verticalLayout_2->setSpacing(4);
//      //verticalLayout_2->setContentsMargins(11, 11, 11, 11);
//      //verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
//      //verticalLayout_2->setContentsMargins(4, 4, 4, 4);
//      //QLabel* label = new QLabel(GroupFreq);
//      //label->setObjectName(QStringLiteral("label"));
//      //label->setMaximumSize(QSize(16777215, 20));
//
//      //verticalLayout_2->addWidget(label);
//
//      //QLineEdit* lineEdit = new QLineEdit(GroupFreq);
//      //lineEdit->setObjectName(QStringLiteral("lineEdit"));
//      //lineEdit->setMaximumSize(QSize(16777215, 32));
//      //verticalLayout_2->addWidget(lineEdit);
//
//      ////QTextEdit *textEdit = new QTextEdit(GroupFreq);
//      ////textEdit->setObjectName(QStringLiteral("textEdit"));
//      ////verticalLayout_2->addWidget(textEdit);
//
//      //GroupFreq->setTitle(QString());
//      ////label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
//      //label->setText(QApplication::translate("MainWindow", name.toStdString().c_str(), Q_NULLPTR));
//
//      //verticalLayout->addWidget(GroupFreq);
//   }
//}

//void MenuPage::Double2String(QString &str, double value)
//{
//   QString strValue(QString("%1").arg(value, 0, 'f'));
//   QString strCut(QString("%1").arg(value, 0, 'f'));
//   int index = strValue.indexOf(".");
//   if (strValue.length() > 9)
//      strCut = QString(strValue.toStdString().substr(0, index).c_str());
//
//   //QString strCut(QString("%1").arg((long long)value));
//
//   str = strCut;
//}

////big menu backgrount: rgb(2,45,142) - rgb(4,93,174) 
//big menu item / backgrount: rgb(53,253,254)
//edit item - rgb(137,165,174)
//switch button - rgb(3,138,244) - rgb(11,207,252)

