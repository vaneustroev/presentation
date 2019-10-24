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
#include <algorithm>
//#include <boost/container/vector.hpp>
//#include <boost/chrono.hpp>

//#include "gcore/controller.h"
#include "gcore/core.h"

//#ifdef Q_OS_LINUX
//#include <unistd.h>
//#include <sys/syscall.h>
//#include <sys/types.h>
//#endif

#include "xyseriesiodevice.h"

class Controller;

#include "guiUnman.h"
#include "gcore/controller.h"
#include "gmain/mainwindow.h"
#include "gmenu/menufreq.h"
//#include "gmenu/gmenupage.h"
#include "gscreen/gmainscreen.h"
#include "gdialog/dialogsystemsettings2.h"
#include "gdialog/dialogmodemeasview.h"
#include "gdialog/dialogmessage.h"
#include "gkeypad/keypadnew2.h"

#include <QtNetwork\QLocalSocket>
#include <QtRemoteObjects\QtRemoteObjects>

//#include <QTest>

//-------------------------------------------------------------------------------------------------//

QT_CHARTS_USE_NAMESPACE

constexpr long long addition(long long num)
{
   long long sum(0);
   for (int i = 0; i <= num; i++)
   {
      sum += i;
   }

   return sum;
}

namespace Main 
{
   MainWindow::MainWindow(QWidget *parent)
      : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , m_audioInput(nullptr)
      , m_device(nullptr)
      , m_series(nullptr)
      //, m_SkipedSeries(nullptr)
      //, _mainScreen(new MainScreen(parent))
      //, _mainScreen(new MainScreen(this)) //rm#1129
      , _draw(true)
      , _chart(nullptr)
      , _chartView(nullptr)
      //, m_values(nullptr)
      //, m_Vector(nullptr)
      //, m_SkipedVector(nullptr)
      //, m_bUpdated(true)
      //, m_bSkUpdated(true)
      //, m_Skiped(0)
      //, m_Position(0)
      //, _msgBox(nullptr)
      //, _mainMenu(nullptr)
      //, _menuTop(nullptr)
      //, _keypad(nullptr)
      //, _keypadanalog(nullptr)
      , _keyMode(new QShortcut(this))
      , _keySystem(new QShortcut(this))
      , _keyExit(new QShortcut(this))
      , _type(gsa::t::ViewConfiguration::Solo)
      , _menuFreq(nullptr)
      , _controller(nullptr)
      //, _currentPos(0)
      //, _number(501) //(401)
      //, _time(1000.0)
      , _stop(false)
      , _splitterScreenWidget(nullptr)
      , _splitterHorizontal(nullptr)
      , _splitterVertical(nullptr)
      , _table(nullptr)
      , _plusButton(nullptr)
      , _frameSplitterScreenWidget(nullptr)
      , _currentMode(-1)
      , _currentMeas(-1)
      , _currentView(-1)
      , _currentMenuPage(-1)
   {
      ui->setupUi(this);

      //freeScreenWidget(_type);
      ////_type = gsa::t::ViewConfiguration::TLeftVertical;
      ////_type = gsa::t::ViewConfiguration::TRightVertical;
      ////_type = gsa::t::ViewConfiguration::TTopHorizontal;
      ////_type = gsa::t::ViewConfiguration::TBottomHorizontal;
      //_type = gsa::t::ViewConfiguration::Quadro;
      //gsa::t::GuiPanel guiPanels[gsa::t::maxPanel];
      //guiPanels[0].type = (int)gsa::t::PanelType::Graph;
      //guiPanels[0].position = (int)gsa::t::PanelPosition::LeftTop;
      //guiPanels[1].type = (int)gsa::t::PanelType::Table;
      //guiPanels[1].position = (int)gsa::t::PanelPosition::RightTop;
      //guiPanels[2].type = (int)gsa::t::PanelType::Disabled;
      //guiPanels[2].position = (int)gsa::t::PanelPosition::LeftBottom;
      //guiPanels[3].type = (int)gsa::t::PanelType::Disabled;
      //guiPanels[3].position = (int)gsa::t::PanelPosition::RightBottom;
      ////initScreenWidget(_type, nullptr, 0);
      //initScreenWidget(_type, guiPanels, 0);

#ifdef TEMP1

      initScreenWidget(MainWindow::ViewConfiguration::Solo);
      //initScreenWidget(MainWindow::ViewConfiguration::DVertical);
      //initScreenWidget(MainWindow::ViewConfiguration::DHorizontal);
      //initScreenWidget(MainWindow::ViewConfiguration::TLeftVertical);
      //initScreenWidget(MainWindow::ViewConfiguration::TRightVertical);
      //initScreenWidget(MainWindow::ViewConfiguration::TTopHorizontal);
      //initScreenWidget(MainWindow::ViewConfiguration::TBottomHorizontal);
      //initScreenWidget(MainWindow::ViewConfiguration::Quadro);
      MainWindow::PanelPosition::Bottom;

#endif // TEMP1

      //rm#1129
      //_mainScreen = new MainScreen(this);
      //_mainScreen = new MainScreen(ui->frame2Central);
      _mainScreen = new MainScreen(ui->screenWidget, this);

      _mainScreen->OpenItem(nullptr);

      //ui->comboBox->setFont(QFont("lucida", 64, QFont::Bold));
      //int rowIndex(0);
      //ui->comboBox->setItemData(rowIndex, QVariant(QFont("lucida", 64, QFont::Bold)), Qt::FontRole);

      //qInfo("\nStep 001 "); 
      //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint); //задаём позицию окна под всеми окнами
      this->setWindowFlags( Qt::FramelessWindowHint ); 
      this->setAttribute( Qt::WA_AcceptTouchEvents );

      int _number(0);
      float _min(0.0);
      float _max(0.0);
      float _step(0.0);

      for (int i = 0; i < gsa::t::maxPad; i++) {
         _menuPages[i] = nullptr;
      }

      //QTabBar::tab{
      //   /*background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);*/
      //   background: rgb(92,92,92);
      //   border: 2px solid #C4C4C3;
      //   border - bottom - color: #C2C7CB; /* same as the pane color */
      //   border - top - left - radius: 4px;
      //   border - top - right - radius: 4px;
      //   min - width: 8ex;
      //   padding: 2px;
      //   color: white;
      //}

      //QTabBar::tab{
      //height: 60px;
      //width: 200px;
      //}

      //MyTabBar* bar;
      //bar = new MyTabBar(this);
      //ui->tabScreenWidgets->setTabBar(bar);

      _controller = new gsa::core::Controller(this, _number, _min, _max, _step);

      connect(this, SIGNAL(signalKeyPadPress(int, quint32, int)), this, SLOT(keyPadPressed(int, quint32, int)));

      connect(this, SIGNAL(signalChangeData(int, double, wchar_t*)), this, SLOT(changeData(int, double, wchar_t*)), Qt::QueuedConnection);
      connect(this, SIGNAL(signalUiPropertyChanged(int, int, int)), this, SLOT(uiPropertyChanged(int, int, int)), Qt::QueuedConnection);
      connect(this, SIGNAL(signalPutCurrentMenu()), this, SLOT(slotPutCurrentMenu()), Qt::QueuedConnection);
      connect(this, SIGNAL(signalPutTablePanel(int )), this, SLOT(slotPutTablePanel(int )), Qt::QueuedConnection);
      connect(this, SIGNAL(signalPutTableDat(int, int)), this, SLOT(slotPutTableDat(int, int)), Qt::QueuedConnection);

      //_keyMode = new QShortcut(this);
      //_keySystem = new QShortcut(this);
      //_keyExit = new QShortcut(this);
      _keyMode->setKey(Qt::CTRL + Qt::Key_M); //Qt::Key_F11; //Qt::Key_Shift / Qt::Key_P / Qt::CTRL; / Qt::SHIFT
      _keySystem->setKey(Qt::CTRL + Qt::Key_S);
      _keyExit->setKey(Qt::CTRL + Qt::Key_X);

      connect(_keyMode, SIGNAL(activated()), this, SLOT(clickedModeMeasView()));
      connect(_keySystem, SIGNAL(activated()), this, SLOT(clickedSystemParams()));
      connect(_keyExit, SIGNAL(activated()), this, SLOT(clickExit()));

      connect(ui->buttonModeMeasView, SIGNAL(clicked()), this, SLOT(clickedModeMeasView()));
      connect(ui->buttonSystemMenu, SIGNAL(clicked()), this, SLOT(clickedSystemParams()));
      connect(ui->buttonExit, SIGNAL(clicked()), this, SLOT(clickExit()));

      connect(ui->tabScreenWidgets, SIGNAL(currentChanged(int)), this, SLOT(tabSelected(int)));

      connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotIndexChanged(int)));

      _labels[0] = ui->label01;
      _labels[1] = ui->label02;
      _labels[2] = ui->label03;
      _labels[3] = ui->label04;
      _labels[4] = ui->label05;
      _labels[5] = ui->label06;

      _visibles[0] = 0;
      _visibles[1] = 0;
      _visibles[2] = 0;
      _visibles[3] = 0;
      _visibles[4] = 0;
      _visibles[5] = 0;

      _labelHeight = ui->label01->height();
      int _minimumHeight = ui->frame3Bottom1->minimumHeight();
      int _maximumHeight = ui->frame3Bottom1->maximumHeight();

      ui->frame3Bottom1->setMinimumHeight(0);
      ui->frame3Bottom1->setMaximumHeight(0);

      QPoint centralRect = ui->frame2Central->pos();
      QPoint bottom = ui->frame3Bottom2->pos();

      setGsaIcon(ui->buttonExit, QString(":/images/exit.png"));
      setGsaIcon(ui->buttonModeMeasView, QString(":/images/properties.png"));
      setGsaIcon(ui->buttonSystemMenu, QString(":/images/busy.png"));

      //QPixmap exitPixmap(":/images/exit.png");
      //QIcon exitIcon(exitPixmap);
      //ui->buttonExit->setIcon(exitIcon);
      //ui->buttonExit->setIconSize(exitPixmap.rect().size());
      //ui->buttonExit->setText(QString(""));
      //ui->buttonExit->setFixedSize(exitPixmap.rect().size());

      for (int index = 0; index < 6; index++) {
         _labels[index]->setText(QString(""));
      }
      //bool b(true);
      //if (b ? true : false) {;}

      //setFocusPolicy(Qt::StrongFocus);
      //QObject::connect(ui-> this, SIGNAL(keyPressEvent), this, SLOT(keyPressed(QKeyEvent *_pEvent)));
      //m_series = nullptr;
      //m_SkipedSeries = nullptr;
      //m_values = nullptr;
      //m_Vector = nullptr;
      //m_SkipedVector = nullptr;
      //m_PeriodSeries = nullptr;
      //m_bUpdated = true;
      //m_bSkUpdated = true;
      //m_bPeriodUpdated = true;
      //m_Skiped = m_Position = 0;
      //m_Blinker = 0;
      m_Period = 16666;

      m_keyPressEater = new KeyPressEater(this, _controller);
      qApp->installEventFilter(m_keyPressEater);

#ifdef Q_OS_WIN
      winId();
      QWindowsWindowFunctions::setHasBorderInFullScreen(windowHandle(), true);
#endif // Q_OS_WIN

      //DialogMessage *test = new DialogMessage(this);
      //test->show();

      //rm#1129


      //QPushButton *pushButton_ = new QPushButton(ui->frame2Central);
      //pushButton_->setObjectName(QStringLiteral("setObjectName - 1234567890"));
      ////frame2Central->setText(QString("setText - lsdflkjlksdflkjlsdf"));
      //pushButton_->setText(QApplication::translate("context - MainWindow", "key - PushButton", nullptr));
      //ui->horizontalLayout->addWidget(pushButton_);

      //int count1 = ui->horizontalLayout->count();

      //QFrame *frame2Central = new QFrame(ui->frameLeft);
      //frame2Central->setObjectName(QStringLiteral("frame2Central"));
      //frame2Central->setFrameShape(QFrame::StyledPanel);
      //frame2Central->setFrameShadow(QFrame::Raised);
      //QHBoxLayout *horizontalLayout = new QHBoxLayout(frame2Central);
      //horizontalLayout->setSpacing(0);
      //horizontalLayout->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
      //horizontalLayout->setContentsMargins(0, 0, 0, 0);

      //ui->horizontalLayout->removeWidget(ui->screenWidget);
      //ui->horizontalLayout->removeWidget(ui->screenWidget);
      //ui->horizontalLayout->removeWidget(ui->screenWidget);
      //QLayoutItem *child1 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child2 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child3 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child4 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child5 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child6 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child7 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child8 = ui->horizontalLayout->takeAt(0);
      //QLayoutItem *child9 = ui->horizontalLayout->takeAt(0);
      //QWidget *cwidget1_ = child1->widget();
      //QWidget *cwidget2_ = child2->widget();
      //QWidget *cwidget3_ = child3->widget();
      //ui->screenWidget;

      //QLayoutItem *child2 = ui->horizontalLayout->takeAt( ui->horizontalLayout->indexOf(ui->screenWidget));
      //QWidget *cwidget2_ = child2->widget();
      //if (cwidget2_ == ui->screenWidget) {
      //   int jjj = 0;
      //}

      //QList<QWidget*> screenWidgets2 = ui->frame2Central->findChildren<QWidget*>(QStringLiteral("screenWidget"));
      //int count2 = ui->horizontalLayout->count();
      //ui->horizontalLayout->activate();
      //ui->horizontalLayout->update();

      //QList<QObject*> objects = ui->frame2Central->findChildren<QObject*>();
      //QList<QWidget*> widgets = ui->frame2Central->findChildren<QWidget*>();
      //QList<QPushButton*> buttons = ui->frame2Central->findChildren<QPushButton*>();
      //QList<QWidget*> screenWidgets = ui->frame2Central->findChildren<QWidget*>(QStringLiteral("screenWidget"));
      //QString objectName_ = ui->screenWidget->parentWidget()->objectName();

      //int size_ = widgets.size();
      //for (int i=0; i < size_; ++i) {
      //   QLayoutItem *child = ui->horizontalLayout->takeAt(i);
      //   if (child != nullptr) {
      //      QWidget *widget_ = child->widget();
      //      if (widget_ == ui->screenWidget) {
      //         int jjj = 0;
      //      }
      //   }
      //}
      //QList<QWidget*> widgets2 = ui->frame2Central->findChildren<QWidget*>();
      //int size2_ = widgets2.size();

      //frame2Central->insertChild();
      //frame2Central->removeChild();
      //frame2Central->setParent();
      //frame2Central->findChildren();

      //ui->horizontalLayout->setStretch(0, 5);
      //ui->horizontalLayout->setStretch(1, 10);
      //ui->horizontalLayout->setStretch(0, 1);
      //ui->horizontalLayout->setStretch(1, 10);

      //int count = ui->horizontalLayout->count();
      //int count2 = ui->frame2Central->count();

      //int iiii = 0;


      //QSplitter *_splitterScreenWidget;

      //_splitterScreenWidget = new QSplitter(ui->frame2Central);
      //_splitterScreenWidget->setObjectName(QStringLiteral("_splitterScreenWidget"));
      //_splitterScreenWidget->setOrientation(Qt::Horizontal);

      //QPushButton *pushButton = new QPushButton(_splitterScreenWidget);
      //pushButton->setObjectName(QStringLiteral("pushButton"));
      //_splitterScreenWidget->addWidget(pushButton);

      ////screenWidget = new QWidget(_splitterScreenWidget);
      ////screenWidget->setObjectName(QStringLiteral("screenWidget"));
      ////ui->horizontalLayout_6 = new QHBoxLayout(screenWidget);
      ////ui->horizontalLayout_6->setSpacing(0);
      ////ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
      ////ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
      ////ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
      ////_splitterScreenWidget->addWidget(screenWidget);

      //ui->horizontalLayout->addWidget(_splitterScreenWidget);



      ////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

      //QWidget *tab_5_Van_ = new QWidget();
      //tab_5_Van_->setObjectName(QStringLiteral("tab_5_Van_"));
      //QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(tab_5_Van_);
      //horizontalLayout_7->setSpacing(6);
      //horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
      //QFrame *frame_2_Van_ = new QFrame(tab_5_Van_);
      //frame_2_Van_->setObjectName(QStringLiteral("frame_2_Van_"));
      //frame_2_Van_->setFrameShape(QFrame::StyledPanel);
      //frame_2_Van_->setFrameShadow(QFrame::Raised);
      //QHBoxLayout *horizontalLayout_9 = new QHBoxLayout(frame_2_Van_);
      //horizontalLayout_9->setSpacing(6);
      //horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
      //QSplitter *splitter_Van_ = new QSplitter(frame_2_Van_);
      //splitter_Van_->setObjectName(QStringLiteral("splitter_Van_"));
      //splitter_Van_->setOrientation(Qt::Vertical);
      //QPushButton *pushButton_Van_ = new QPushButton(splitter_Van_);
      //pushButton_Van_->setObjectName(QStringLiteral("pushButton_Van_"));
      //splitter_Van_->addWidget(pushButton_Van_);
      //QPushButton *pushButton_2_Van_ = new QPushButton(splitter_Van_);
      //pushButton_2_Van_->setObjectName(QStringLiteral("pushButton_2_Van_"));
      //splitter_Van_->addWidget(pushButton_2_Van_);

      //horizontalLayout_9->addWidget(splitter_Van_);

      //horizontalLayout_7->addWidget(frame_2_Van_);

      //ui->tabScreenWidgets->addTab(tab_5_Van_, QString());

      //pushButton_Van_->setText(QApplication::translate("MainWindow", "PushButton 007", nullptr));
      //pushButton_2_Van_->setText(QApplication::translate("MainWindow", "PushButton 007", nullptr));
      //ui->tabScreenWidgets->setTabText(ui->tabScreenWidgets->indexOf(tab_5_Van_), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));

      ////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

      ui->tabScreenWidgets->removeTab(ui->tabScreenWidgets->indexOf(ui->tab_5_Van_));
      ui->labelModeMeasView->setMinimumHeight(0);
      ui->labelModeMeasView->setMaximumHeight(0);

      FillIndexes();

      gsa::t::Theme *_theme(g_Parameter._theme);

      putTheme(g_Parameter._theme);

      //__van__ 2019.08.08 
      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 
      gsa::t::ThemeFont fontTab_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem itemTab_(themeItem); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) { 
            switch (_fontindexes[std::wstring(font.description)]) 
            { 
            case gsa::t::FontIndex::Default: font_ = font; break; 
            case gsa::t::FontIndex::CurrentMeasurement: //Current measurement selection area 
               fontTab_ = font;
               break;
            default: break;
            } 
         } 
      } 

      for (auto &themeItem : _theme->themeItems) {
         switch (themeItem.type) 
         { 
         case 0: 
         { 
            if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) { 
               switch (_colorindexes[std::wstring(themeItem.description)]) 
               { 
               case gsa::t::ColorIndex::Default: item_ = themeItem; break; 
               case gsa::t::ColorIndex::TabSelectionArea: //Tab in the general dimension selection area 
                  itemTab_ = themeItem;
                  break;
               default: break;
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

      int r, g, b;
      GetRgb(font_.color, r, g, b);
      QColor color_(r, g, b);
      int r2, g2, b2;
      GetRgb(item_.value, r2, g2, b2);
      QColor color2_(r2, g2, b2);

      this->setStyleSheet(QString("%1 "
         "QWidget { "
         "font-family: %2; "
         "font-size: %3pt; " //"font-size: %3px; " 
         "font-weight: %4; "
         "color: rgb(%5, %6, %7); "
         "background-color: rgb(%8, %9, %10); "
         "} "
         ""
      ).arg(this->styleSheet()).arg(QString::fromWCharArray(font_.family)).arg(font_.size).arg(QString::fromWCharArray(font_.style)).
         arg(color_.red()).arg(color_.green()).arg(color_.blue()).arg(color2_.red()).arg(color2_.green()).arg(color2_.blue())
      );

      GetRgb(fontTab_.color, r, g, b);
      QColor colorTab_(r, g, b);
      GetRgb(itemTab_.value, r2, g2, b2);
      QColor color2Tab_(r2, g2, b2);

      _plusButton = new QPushButton();
      _plusButton->setText("+");
      ui->tabScreenWidgets->setCornerWidget(_plusButton);
      _plusButton->setStyleSheet(QString("%1 "
         "QPushButton { "
         "font: bold 40px; "
         "height: 50px; width: 50px; "
         //"color: white; "
         //"background: rgb(92, 92, 92); "
         "color: rgb(%2, %3, %4); "
         "background-color: rgb(%5, %6, %7); "
         //"border-radius: 8px;"
         "}"
      ).arg(_plusButton->styleSheet()).
         arg(colorTab_.red()).arg(colorTab_.green()).arg(colorTab_.blue()).arg(color2Tab_.red()).arg(color2Tab_.green()).arg(color2Tab_.blue())
      );

      connect(_plusButton, SIGNAL(clicked()), this, SLOT(clickedPlusButton()));

   }

   MainWindow::~MainWindow()
   {
   }

   void MainWindow::FillIndexes(void)
   {
      _fontindexes[L"Current measurement selection area"] = gsa::t::FontIndex::CurrentMeasurement;
      _fontindexes[L"Measurement scale"] = gsa::t::FontIndex::MeasurementScale;
      _fontindexes[L"Panel header"] = gsa::t::FontIndex::PanelHeader;
      _fontindexes[L"Quick Access Area Tab"] = gsa::t::FontIndex::QuickAccess;
      _fontindexes[L"Drop-down menu items (list of composition)"] = gsa::t::FontIndex::DropDownMenu;
      _fontindexes[L"Tabs of the selected menu (name of the subcomposition)"] = gsa::t::FontIndex::SelectedMenu;
      _fontindexes[L"Controls located in the selected tab"] = gsa::t::FontIndex::ControlsSelectedTab;
      _fontindexes[L"Displaying the active marker in the graphics area"] = gsa::t::FontIndex::ActiveMarker;
      _fontindexes[L"Displaying inactive marker in the graphics area"] = gsa::t::FontIndex::InactiveMarker;
      _fontindexes[L"Displaying the active marker in the marker table"] = gsa::t::FontIndex::ActiveMarkerTable;
      _fontindexes[L"Displaying the inactive marker in the marker table"] = gsa::t::FontIndex::InactiveMarkerTable;
      _fontindexes[L"Control drop-down list in the panel (additional data area)"] = gsa::t::FontIndex::ControlDropDownPanel;
      _fontindexes[L"Control located in the panel (additional data area)"] = gsa::t::FontIndex::PanelControl;
      _fontindexes[L"Default"] = gsa::t::FontIndex::Default;

      _colorindexes[L"Display area background"] = gsa::t::ColorIndex::DisplayArea; 
      _colorindexes[L"Graphic panel scale"] = gsa::t::ColorIndex::GraphicPanelScale; 
      _colorindexes[L"Borders of the table display"] = gsa::t::ColorIndex::TableBorders; 
      _colorindexes[L"Current measurement selection area"] = gsa::t::ColorIndex::CurrentMeasurement; 
      _colorindexes[L"Tab in the general dimension selection area"] = gsa::t::ColorIndex::TabSelectionArea; 
      _colorindexes[L"Tabs in the quick access area"] = gsa::t::ColorIndex::QuickAccess; 
      _colorindexes[L"Drop down menu"] = gsa::t::ColorIndex::DropDownMenu; 
      _colorindexes[L"Unifying frame in the menu area"] = gsa::t::ColorIndex::UnifyingFrame; 
      _colorindexes[L"Border of the unifying frame in the menu area"] = gsa::t::ColorIndex::UnifyingFrameBorder; 
      _colorindexes[L"Control drop-down list in the menu area (color)"] = gsa::t::ColorIndex::ControlDropDownMenu; 
      _colorindexes[L"Control drop-down list in the panel (additional data area)"] = gsa::t::ColorIndex::ControlDropDownPanel; 
      _colorindexes[L"Control in the panel (additional data area)"] = gsa::t::ColorIndex::PanelControl; 
      _colorindexes[L"Selected line in the expanded control drop-down list"] = gsa::t::ColorIndex::SelectedLine; 
      _colorindexes[L"Unselected string in expanded control drop-down list"] = gsa::t::ColorIndex::UnselectedString; 
      _colorindexes[L"Borders of the elements of the drop-down menu"] = gsa::t::ColorIndex::ElementsBorders; 
      _colorindexes[L"Menu area (composition)"] = gsa::t::ColorIndex::CompositionMenu; 
      _colorindexes[L"Control in the menu area (composition)"] = gsa::t::ColorIndex::ControlMenu; 
      _colorindexes[L"Default"] = gsa::t::ColorIndex::Default; 

      _sizeindexes[L"Menu item in the drop-down menu"] = gsa::t::SizeIndex::MenuItem;
      _sizeindexes[L"Control button in the menu area"] = gsa::t::SizeIndex::Button;
      _sizeindexes[L"Control radio button in the menu area"] = gsa::t::SizeIndex::RadioButton;
      _sizeindexes[L"Control checkbox in the menu area"] = gsa::t::SizeIndex::Checkbox;
      _sizeindexes[L"Control drop-down list in the menu area (size)"] = gsa::t::SizeIndex::DropDownList;
      _sizeindexes[L"Control item is a switch in the menu area"] = gsa::t::SizeIndex::Switch;
      _sizeindexes[L"Control is a numeric value in the menu area"] = gsa::t::SizeIndex::NumericValue;
      _sizeindexes[L"Control located in the panel(additional data area)"] = gsa::t::SizeIndex::Panel;

      _indentindexes[L"Unifying frame of the menu area from the size of the control"] = gsa::t::IndentIndex::UnifyingFrame;
      _indentindexes[L"The menu area, from the size of the unifying frame located in it"] = gsa::t::IndentIndex::MenuArea;
      _indentindexes[L"Borders of the table display from the text"] = gsa::t::IndentIndex::TableBorders;

   }

   void MainWindow::freeScreenWidget(const gsa::t::ViewConfiguration &viewConfiguration)
   {
      _tabs;

      switch (viewConfiguration)
      {
      case gsa::t::ViewConfiguration::Solo:
      {
         //ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
         //ui->screenWidget->setParent(nullptr);

         //int currentIndex = ui->tabScreenWidgets->currentIndex();
         //QWidget *parent(nullptr);
         //if (currentIndex >= 0) {
         //   parent = ui->tabScreenWidgets->widget(currentIndex);
         //   QLayout *layout = parent->layout();
         //   if (layout != nullptr) {
         //      //layout->addWidget(ui->frameScreenWidget);
         //      //ui->frameScreenWidget->setParent(parent);
         //      layout->removeWidget(ui->frameScreenWidget);
         //      ui->frameScreenWidget->setParent(nullptr);
         //   }
         //}

         if (_frameSplitterScreenWidget != nullptr && _frameSplitterScreenWidget->layout() != nullptr) {
            int count6 = _frameSplitterScreenWidget->layout()->count();
            int iii = 0;
         }

         int count1;
         int count2;
         if (ui->frameScreenWidget != nullptr && ui->frameScreenWidget->layout() != nullptr ) {
            count1 = ui->frameScreenWidget->layout()->count();
         }

         //if (ui->frameScreenWidget != nullptr && ui->frameScreenWidget->layout() != nullptr) {
         //   int count = ui->frameScreenWidget->layout()->count();
         //   for (int i = 0; i < count; i++) {
         //      ui->frameScreenWidget->layout()->removeItem(ui->frameScreenWidget->layout()->itemAt(0));
         //   }
         //}

         setCurrentTab(viewConfiguration, nullptr, 0, false);

         if (ui->frameScreenWidget != nullptr && ui->frameScreenWidget->layout() != nullptr) {
            count2 = ui->frameScreenWidget->layout()->count();
         }
         int iii = 0;

         ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
         ui->screenWidget->setParent(nullptr);

         //ui->horizontalLayout_8->removeWidget(ui->frameScreenWidget);
         //ui->frameScreenWidget->setParent(nullptr);

         break;
      }
      case gsa::t::ViewConfiguration::DVertical:
      {
         if (_splitterScreenWidget == nullptr) {
            return;
         }

         int count6 = _frameSplitterScreenWidget->layout()->count();
         int iii = 0;

         if (_splitterScreenWidget != nullptr)
         {
            if (_frameSplitterScreenWidget->layout() != nullptr) {
               int count = _frameSplitterScreenWidget->layout()->count();
               for (int i = 0; i < count; i++) {
                  //_frameSplitterScreenWidget->layout()->itemAt(0)->widget();
                  _frameSplitterScreenWidget->layout()->removeItem(_frameSplitterScreenWidget->layout()->itemAt(0));
               }
               int count2 = _frameSplitterScreenWidget->layout()->count();
               int i = 0;
               //_frameSplitterScreenWidget->layout()->removeWidget(_table);
            }

            //if (_splitterScreenWidget->layout() != nullptr) {
            //   int count = _splitterScreenWidget->layout()->count();
            //   _splitterScreenWidget->layout()->removeWidget(_frameSplitterScreenWidget);
            //   _splitterScreenWidget->layout()->removeWidget(ui->screenWidget);
            //}
            //else {
            //   int i = 0;
            //}

            ui->screenWidget->setParent(nullptr);
            _frameSplitterScreenWidget->setParent(nullptr);

            int count = _splitterScreenWidget->count();
            int index = _splitterScreenWidget->indexOf(ui->screenWidget);
            index = index;

            for (int i = 0; i < count; i++)
            {
               QWidget *widget_ = _splitterScreenWidget->widget(i);
               int iii = 0;
            }

            if (ui->frameScreenWidgetHorizontalLayout != nullptr) {
               int count = ui->frameScreenWidgetHorizontalLayout->count();
               QWidget * w1 = ui->frameScreenWidgetHorizontalLayout->itemAt(0)->widget();
               QWidget * w2 = _splitterScreenWidget;
               if (w1 == w2) {
                  int i = 0;
               }
               else {
                  int i = 0;
               }
               //ui->frameScreenWidgetHorizontalLayout->removeItem(ui->frameScreenWidgetHorizontalLayout->itemAt(0));
               //int count2 = ui->frameScreenWidgetHorizontalLayout->count();
               //int i = 0;

               ////ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterScreenWidget);
            }

            setCurrentTab(viewConfiguration, nullptr, 0, false);

            //QObjectList list = _splitterScreenWidget->children();
            //for (auto item : list) {
            //   if (item->isWidgetType()) {
            //      //_splitterScreenWidget->addWidget();
            //      int i(0);
            //   }
            //}
            //ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            //ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            //ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterScreenWidget);
            //ui->screenWidget->setParent(nullptr);
            ////delete _table;
            ////delete _splitterScreenWidget;
         }
         break;
      }
      case gsa::t::ViewConfiguration::DHorizontal:
      {
         if (_splitterScreenWidget != nullptr)
         {
            setCurrentTab(viewConfiguration, nullptr, 0, false);

            //ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            //ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            //ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterScreenWidget);
            //ui->screenWidget->setParent(nullptr);
            ////delete _table;
            ////delete _splitterScreenWidget;
         }
         break;
      }
      case gsa::t::ViewConfiguration::TLeftVertical:
      {
         setCurrentTab(viewConfiguration, nullptr, 0, false);

         //if (_splitterHorizontal != nullptr) {
         //   ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
         //   ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
         //   ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal);
         //   ui->screenWidget->setParent(nullptr);
         //   //delete _table;
         //   //delete _splitterScreenWidget;
         //}
         //if (_splitterVertical != nullptr) {
         //   ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
         //   ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
         //   ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterVertical);
         //   ui->screenWidget->setParent(nullptr);
         //   //delete _table;
         //   //delete _splitterScreenWidget;
         //}
         break;
      }
      case gsa::t::ViewConfiguration::TRightVertical:
      {
         if (_splitterHorizontal != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         if (_splitterVertical != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterVertical);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         break;
      }
      case gsa::t::ViewConfiguration::TTopHorizontal:
      {
         if (_splitterHorizontal != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         if (_splitterVertical != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterVertical);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         break;
      }
      case gsa::t::ViewConfiguration::TBottomHorizontal:
      {
         if (_splitterHorizontal != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         if (_splitterVertical != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterVertical);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         break;
      }
      case gsa::t::ViewConfiguration::Quadro:
      {
         if (_splitterHorizontal != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         if (_splitterHorizontal2 != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal2);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         if (_splitterVertical != nullptr) {
            ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
            ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterVertical);
            ui->screenWidget->setParent(nullptr);
            //delete _table;
            //delete _splitterScreenWidget;
         }
         break;
      }
      }
   }

   //void MainWindow::clearCurrentTab(void)
   //{
   //   int currentIndex = ui->tabScreenWidgets->currentIndex();
   //   if (currentIndex >= 0) {
   //      QWidget *parent = ui->tabScreenWidgets->widget(currentIndex);
   //      if (parent != nullptr) {
   //         QLayout *layout = parent->layout();
   //         if (layout != nullptr) {
   //            layout->removeWidget(ui->frameScreenWidget);
   //            ui->frameScreenWidget->setParent(nullptr);
   //         }
   //      }
   //   }
   //}

   void MainWindow::setCurrentTab(const gsa::t::ViewConfiguration &viewConfiguration, const gsa::t::GuiPanel guiPanels[], const int &length, bool add)
   {
      int currentIndex = ui->tabScreenWidgets->currentIndex();
      if (currentIndex >= 0) {
         QWidget *parent = ui->tabScreenWidgets->widget(currentIndex);
         if (parent != nullptr) {
            QLayout *layout = parent->layout();
            if (layout != nullptr) {
               _tabs;

               if (add) {
                  //QLayout *layout2 = ui->frameScreenWidget->layout();
                  //int count = layout2->count();

                  layout->addWidget(ui->frameScreenWidget);
                  ui->frameScreenWidget->setParent(parent);

                  if (_tabs.find(currentIndex) == _tabs.end()) {
                     _tabParams._type = viewConfiguration;
                     _tabParams._guiPanels = const_cast<gsa::t::GuiPanel *>(guiPanels);
                     _tabParams._length = length;
                     int _currentMode = _currentMenu->indexMode;
                     int _currentMeas = _currentMenu->indexMeas;
                     int _currentView = _currentMenu->indexView;
                     _tabParams._currentMode = _currentMode;
                     _tabParams._currentMeas = _currentMeas;
                     _tabParams._currentView = _currentView;
                     _tabParams._currentMenuPage = 0; // _currentMenuPage;
                     _tabs[currentIndex] = _tabParams;
                  }
                  else {
                     _tabs[currentIndex]._type = viewConfiguration;
                     _tabs[currentIndex]._guiPanels = const_cast<gsa::t::GuiPanel *>(guiPanels);
                     _tabs[currentIndex]._length = length;
                     int _currentMode = _currentMenu->indexMode;
                     int _currentMeas = _currentMenu->indexMeas;
                     int _currentView = _currentMenu->indexView;
                     _tabs[currentIndex]._currentMode = _currentMode;
                     _tabs[currentIndex]._currentMeas = _currentMeas;
                     _tabs[currentIndex]._currentView = _currentView;
                     _tabs[currentIndex];
                  }
               }
               else {
                  //int count1 = layout->count();
                  //QWidget *parent2 = (QWidget *)ui->frameScreenWidget->parent();
                  //int index1 = layout->indexOf(ui->frameScreenWidget);

                  if (_tabs.find(currentIndex) != _tabs.end()) {
                     //_tabs[currentIndex]._currentMenuPage = _currentMenuPage;
                     int currentMenuPage = _tabs[currentIndex]._currentMenuPage;
                     currentMenuPage = currentMenuPage;
                  }

                  layout->removeWidget(ui->frameScreenWidget);
                  ui->frameScreenWidget->setParent(nullptr);

                  //int count2 = layout->count();

                  //int index2 = layout->indexOf(_splitterScreenWidget);
                  //index2 = index2;

                  ////ui->frameScreenWidgetHorizontalLayout->removeWidget(ui->screenWidget);
                  ////ui->frameScreenWidgetHorizontalLayout->removeWidget(_table);
                  ////ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterHorizontal);
                  ////ui->frameScreenWidgetHorizontalLayout->removeWidget(_splitterScreenWidget);
               }
            }
         }
      }
   }

   void MainWindow::initScreenWidget(const gsa::t::ViewConfiguration &viewConfiguration, const gsa::t::GuiPanel guiPanels[], const int &length)
   {
      _tabs;

      gsa::t::Theme *_theme(g_Parameter._theme);

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
      GetRgb(item_.value, r2, g2, b2);
      QColor color_(r2, g2, b2);

      //rm#1129
      switch (viewConfiguration)
      {
      case gsa::t::ViewConfiguration::Solo:
      {
         std::map<int, int> indexes;

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Solo);

         if (_frameSplitterScreenWidget != nullptr && _frameSplitterScreenWidget->layout() != nullptr) {
            int count6 = _frameSplitterScreenWidget->layout()->count();
            int iii = 0;
         }

         setCurrentTab(viewConfiguration, guiPanels, length);

         ui->frameScreenWidgetHorizontalLayout->setParent(ui->frameScreenWidget);
         ui->screenWidget->setParent(ui->frameScreenWidget);
         ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));

         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         ui->horizontalLayout_6->setParent(ui->screenWidget);
         ui->horizontalLayout_6->setSpacing(0);
         ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

         //ui->screenWidget->setSizePolicy(policy_);

         ui->frameScreenWidgetHorizontalLayout->addWidget(ui->screenWidget);
         //_splitterScreenWidget->addWidget(ui->screenWidget);

         ////int count = ui->tabScreenWidgets->count(); 
         //int currentIndex = ui->tabScreenWidgets->currentIndex(); 
         ////QWidget *parent(nullptr); 
         //if (currentIndex >= 0) { 
         //   QWidget *parent = ui->tabScreenWidgets->widget(currentIndex); 
         //   QLayout *layout = parent->layout(); 
         //   //int i = 0; 
         //   //ui->horizontalLayout_8->removeWidget(ui->frameScreenWidget); 
         //   //ui->horizontalLayout_8->addWidget(ui->frameScreenWidget); 
         //   if (layout != nullptr) { 
         //      layout->addWidget(ui->frameScreenWidget); 
         //      ui->frameScreenWidget->setParent(parent); 
         //   } 

         //   //   parent = ui->frameScreenWidget;
         //   //   ui->screenWidget->setParent(parent);
         //   //   ui->frameScreenWidgetHorizontalLayout->addWidget(ui->screenWidget);

         //   //   //QRect Rect2 = ui->tabScreenWidgets->frameGeometry(); // geometry();
         //   //   //QRect centralRect = parent->frameGeometry(); // geometry();
         //   //   //QPoint point1xy(Rect2.x(), Rect2.y());
         //   //   //QPoint point2xy(centralRect.x(), centralRect.y());
         //   //   //QPoint pointxy(0, 0);
         //   //   //point1xy = ui->tabScreenWidgets->mapToGlobal(pointxy);
         //   //   //point2xy = parent->mapToGlobal(pointxy);
         //   //   //QRect newRect;
         //   //   //newRect.setX(point2xy.x());
         //   //   //newRect.setY(point2xy.y());
         //   //   //newRect.setWidth(centralRect.width());
         //   //   //newRect.setHeight(centralRect.height());
         //   //   //_mainScreen->setCentralRect(newRect);

         //}

         ////else {
         ////   parent = ui->frame2Central;
         ////   ui->screenWidget->setParent(ui->frame2Central);
         ////   ui->horizontalLayout->addWidget(ui->screenWidget);

         //ui->screenWidget->setParent(ui->frameScreenWidget);
         //ui->frameScreenWidgetHorizontalLayout->addWidget(ui->screenWidget);

         ////}

         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         break;
      }
      case gsa::t::ViewConfiguration::DVertical:
      {
         //DVertical - две панели, разделённые горизонтальной чертой - одна под другой (Panels - всегда состоит из двух элементов со значениями Top (верхний), Bottom (нижний), Disabled (Выключен));

         ////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

         //QWidget *tab_5_Van_ = new QWidget();
         //tab_5_Van_->setObjectName(QStringLiteral("tab_5_Van_"));
         //QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(tab_5_Van_);
         //horizontalLayout_7->setSpacing(6);
         //horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
         //horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
         //QFrame *frame_2_Van_ = new QFrame(tab_5_Van_);
         //frame_2_Van_->setObjectName(QStringLiteral("frame_2_Van_"));
         //frame_2_Van_->setFrameShape(QFrame::StyledPanel);
         //frame_2_Van_->setFrameShadow(QFrame::Raised);
         //QHBoxLayout *horizontalLayout_9 = new QHBoxLayout(frame_2_Van_);
         //horizontalLayout_9->setSpacing(6);
         //horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
         //horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
         //QSplitter *splitter_Van_ = new QSplitter(frame_2_Van_);
         //splitter_Van_->setObjectName(QStringLiteral("splitter_Van_"));
         //splitter_Van_->setOrientation(Qt::Vertical);
         //QPushButton *pushButton_Van_ = new QPushButton(splitter_Van_);
         //pushButton_Van_->setObjectName(QStringLiteral("pushButton_Van_"));
         //splitter_Van_->addWidget(pushButton_Van_);
         //QPushButton *pushButton_2_Van_ = new QPushButton(splitter_Van_);
         //pushButton_2_Van_->setObjectName(QStringLiteral("pushButton_2_Van_"));
         //splitter_Van_->addWidget(pushButton_2_Van_);

         //horizontalLayout_9->addWidget(splitter_Van_);

         //horizontalLayout_7->addWidget(frame_2_Van_);

         //ui->tabScreenWidgets->addTab(tab_5_Van_, QString());

         //break;

         ////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

         std::map<int, int> indexes;

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Top);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Bottom);

         setCurrentTab(viewConfiguration, guiPanels, length);

         //int currentIndex = ui->tabScreenWidgets->currentIndex();
         //if (currentIndex >= 0) {
         //   QWidget *parent = ui->tabScreenWidgets->widget(currentIndex);
         //   if (parent != nullptr) {
         //      QLayout *layout = parent->layout();
         //      if (layout != nullptr) {
         //         layout->addWidget(ui->frameScreenWidget);
         //         ui->frameScreenWidget->setParent(parent);
         //      }
         //   }
         //}

         //QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);
         //QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
         QSizePolicy policy_(QSizePolicy::Expanding, QSizePolicy::Expanding);

         int count01 = ui->frameScreenWidget->layout()->count();
         //_splitterScreenWidget = new QSplitter(ui->frame2Central);
         _splitterScreenWidget = new QSplitter(ui->frameScreenWidget);
         _splitterScreenWidget->setObjectName(QStringLiteral("_splitterScreenWidget"));
         _splitterScreenWidget->setOrientation(Qt::Vertical);

         int count02 = ui->frameScreenWidget->layout()->count();

         int jjj = 0;

         //QVBoxLayout *verticalLayout; 
         //verticalLayout = new QVBoxLayout(_splitterScreenWidget); 
         //verticalLayout->setSpacing(0); 
         //verticalLayout->setContentsMargins(11, 11, 11, 11); 
         //verticalLayout->setObjectName(QStringLiteral("verticalLayout")); 
         //verticalLayout->setContentsMargins(0, 0, 0, 0); 
         ////_splitterScreenWidget->layout(); 

         for (int i = 0; i < length; i++) 
         { 
            if (guiPanels[i].type == (int)gsa::t::PanelType::Graph) 
            { 
               QWidget *parent = (QWidget *)ui->screenWidget->parent();

               //ui->screenWidget = new QWidget(_splitterScreenWidget);
               ui->screenWidget->setParent(_splitterScreenWidget);
               ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));

               //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
               ui->horizontalLayout_6->setParent(ui->screenWidget);
               ui->horizontalLayout_6->setSpacing(0);
               ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
               ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
               ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

               ui->screenWidget->setSizePolicy(policy_);

               _splitterScreenWidget->addWidget(ui->screenWidget);

               ui->screenWidget->setMinimumHeight((double)this->size().height() / 2.5);
               ui->screenWidget->setMinimumWidth((double)this->size().width() / 2.5);

            }
            else if (guiPanels[i].type == (int)gsa::t::PanelType::Table) 
            {
               int index(1);

               //QFrame *frame_2 = new QFrame(_splitterScreenWidget); 
               _frameSplitterScreenWidget = new QFrame(_splitterScreenWidget);

               //int count1 = _frameSplitterScreenWidget->layout()->count();

               _frameSplitterScreenWidget->setObjectName(QStringLiteral("_frameSplitterScreenWidget"));
               _frameSplitterScreenWidget->setFrameShape(QFrame::StyledPanel);
               _frameSplitterScreenWidget->setFrameShadow(QFrame::Raised);

               //_frameSplitterScreenWidget->setStyleSheet(QLatin1String(
               //   "QFrame {\n"
               //   "background-color: rgb(8,8,8); \n"
               //   "}\n"
               //   "\n"
               //""));

               //_frameSplitterScreenWidget->setStyleSheet(QString("%1 "
               //   "QFrame { "
               //   "background-color: rgb(%1, %2, %3); "
               //   "} "
               //   ""
               //).arg(_frameSplitterScreenWidget->styleSheet()).arg(color_.red()).arg(color_.green()).arg(color_.blue())
               //);

               const char *ch = _frameSplitterScreenWidget->styleSheet().toStdString().c_str();
               _frameSplitterScreenWidget->setStyleSheet(QString(""
                  "QFrame { "
                  "background-color: rgb(%1, %2, %3); "
                  "} "
                  ""
               ).arg(color_.red()).arg(color_.green()).arg(color_.blue())
               );

               if (false)
               {
                  QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(_frameSplitterScreenWidget);
                  horizontalLayout_7->setSpacing(0);
                  horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
                  horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));

                  QSpacerItem *horizontalSpacer_2 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
                  //std::unique_ptr<QSpacerItem> horizontalSpacer_2(std::make_unique<QSpacerItem>(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
                  horizontalLayout_7->addItem(horizontalSpacer_2);

                  _table = _mainScreen->fillTablePanel(_frameSplitterScreenWidget, g_Parameter._tablePanel, index, nullptr);
                  if (_table != nullptr)
                     horizontalLayout_7->addWidget(_table);

                  QSpacerItem *horizontalSpacer_3 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
                  //std::unique_ptr<QSpacerItem> horizontalSpacer_3(std::make_unique<QSpacerItem>(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
                  horizontalLayout_7->addItem(horizontalSpacer_3);

                  horizontalLayout_7->setStretch(0, 1);
                  horizontalLayout_7->setStretch(1, 50);
                  horizontalLayout_7->setStretch(2, 1);
               }
               else {
                  QGridLayout *gridLayout = new QGridLayout(_frameSplitterScreenWidget);
                  //std::unique_ptr<QGridLayout> gridLayout(std::make_unique<QGridLayout>(_frameSplitterScreenWidget.get()));

                  int count1 = _frameSplitterScreenWidget->layout()->count();

                  QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                  QSpacerItem *horizontalSpacer_1 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
                  //std::unique_ptr<QSpacerItem> horizontalSpacer_1(std::make_unique<QSpacerItem>(1, 1, policy.horizontalPolicy(), policy.verticalPolicy()));
                  gridLayout->addItem(horizontalSpacer_1, 0, 1);

                  int count2 = _frameSplitterScreenWidget->layout()->count();

                  QSpacerItem *horizontalSpacer_2 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
                  //std::unique_ptr<QSpacerItem> horizontalSpacer_2(std::make_unique<QSpacerItem>(1, 1, policy.horizontalPolicy(), policy.verticalPolicy()));
                  gridLayout->addItem(horizontalSpacer_2, 1, 0);

                  int count3 = _frameSplitterScreenWidget->layout()->count();

                  _table = _mainScreen->fillTablePanel(_frameSplitterScreenWidget, g_Parameter._tablePanel, index, gridLayout);
                  if (_table != nullptr)
                     gridLayout->addWidget(_table, 1, 1);
                  _table->setSizePolicy(policy);

                  int count4 = _frameSplitterScreenWidget->layout()->count();

                  QSpacerItem *horizontalSpacer_3 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
                  //std::unique_ptr<QSpacerItem> horizontalSpacer_3(std::make_unique<QSpacerItem>(1, 1, policy.horizontalPolicy(), policy.verticalPolicy()));
                  gridLayout->addItem(horizontalSpacer_3, 1, 2);

                  int count5 = _frameSplitterScreenWidget->layout()->count();

                  QSpacerItem *horizontalSpacer_4 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
                  //std::unique_ptr<QSpacerItem> horizontalSpacer_4(std::make_unique<QSpacerItem>(1, 1, policy.horizontalPolicy(), policy.verticalPolicy()));
                  gridLayout->addItem(horizontalSpacer_4, 2, 1);

                  int count6 = _frameSplitterScreenWidget->layout()->count();

                  //for (int i = 0; i < count6; i++) {
                  //   _frameSplitterScreenWidget->layout()->takeAt(i);
                  //}

                  gridLayout->setRowStretch(0, 1);
                  gridLayout->setRowStretch(1, 50);
                  gridLayout->setRowStretch(2, 1);
                  gridLayout->setColumnStretch(0, 1); //4);
                  gridLayout->setColumnStretch(1, 1); //8);
                  gridLayout->setColumnStretch(2, 1); //4);

               }

               _frameSplitterScreenWidget->setSizePolicy(policy_);

               _splitterScreenWidget->addWidget(_frameSplitterScreenWidget);

            }
            else if (guiPanels[i].type == (int)gsa::t::PanelType::Disabled) {
               QPushButton *pushButton = new QPushButton(_splitterScreenWidget);
               //std::unique_ptr<QPushButton> pushButton(std::make_unique<QPushButton>(_splitterScreenWidget));
               pushButton->setText(QStringLiteral(""));
               pushButton->setObjectName(QStringLiteral(""));
               _splitterScreenWidget->addWidget(pushButton);
            }
         }

         ////ui->screenWidget = new QWidget(_splitterScreenWidget);
         //ui->screenWidget->setParent(_splitterScreenWidget);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         ////ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setParent(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //_splitterScreenWidget->addWidget(ui->screenWidget);

         //QPushButton *pushButton = new QPushButton(_splitterScreenWidget);
         //pushButton->setText(QStringLiteral("pushButton\nWwwwww"));
         //pushButton->setObjectName(QStringLiteral("pushButton\nWwwwww"));
         //_splitterScreenWidget->addWidget(pushButton);

         _splitterScreenWidget->setStretchFactor(0, 2);
         _splitterScreenWidget->setStretchFactor(1, 3);

         //int index = _splitterScreenWidget->indexOf(widget);
         _splitterScreenWidget->setCollapsible(0, false);
         _splitterScreenWidget->setCollapsible(1, false);

         //ui->horizontalLayout->addWidget(_splitterScreenWidget);
         ui->frameScreenWidgetHorizontalLayout->addWidget(_splitterScreenWidget);

         //if (_frameSplitterScreenWidget->layout() != nullptr) {
         //   int count = _frameSplitterScreenWidget->layout()->count();
         //   for (int i = 0; i < count; i++) {
         //      _frameSplitterScreenWidget->layout()->removeItem(_frameSplitterScreenWidget->layout()->itemAt(0));
         //   }
         //}

         int count6 = _frameSplitterScreenWidget->layout()->count();
         int iii = 0;

         break;
      }
      case gsa::t::ViewConfiguration::DHorizontal:
      {
         //DHorizontal - две панели,разделённые вертикальной чертой (Panels - всегда состоит из двух элементов со значениями Left (левый), Right (правый), Disabled (Выключен));

         std::map<int, int> indexes;

         //rm1129
         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Left);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Right);

         setCurrentTab(viewConfiguration, guiPanels, length);

         //QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);
         //QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
         QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         ////ui->horizontalLayout->removeWidget(ui->screenWidget);
         ////delete ui->horizontalLayout_6;
         ////delete ui->screenWidget;

         ////QSplitter *splitter(nullptr);

         //_splitterScreenWidget = new QSplitter(ui->frame2Central);
         //_splitterScreenWidget->setObjectName(QStringLiteral("_splitterScreenWidget"));
         //_splitterScreenWidget->setOrientation(Qt::Horizontal);

         //QPushButton *pushButton = new QPushButton(_splitterScreenWidget);
         //pushButton->setText(QStringLiteral("pushButton"));
         //pushButton->setObjectName(QStringLiteral("pushButton"));
         //_splitterScreenWidget->addWidget(pushButton);

         //ui->screenWidget = new QWidget(_splitterScreenWidget);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //_splitterScreenWidget->addWidget(ui->screenWidget);

         //_splitterScreenWidget->setStretchFactor(0, 4);
         //_splitterScreenWidget->setStretchFactor(1, 20);

         //ui->horizontalLayout->addWidget(_splitterScreenWidget);

         ////ui->screenWidget = new QWidget(ui->frame2Central);
         ////ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         ////ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         ////ui->horizontalLayout_6->setSpacing(0);
         ////ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         ////ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         ////ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

         ////ui->horizontalLayout->addWidget(ui->screenWidget);

         //_splitterScreenWidget = new QSplitter(ui->frame2Central);
         _splitterScreenWidget = new QSplitter(ui->frameScreenWidget);
         _splitterScreenWidget->setObjectName(QStringLiteral("_splitterScreenWidget"));
         _splitterScreenWidget->setOrientation(Qt::Horizontal);
         //connect(_splitterScreenWidget, SIGNAL(splitterMoved(int, int)), this, SLOT(slotSplitterMoved(int, int)));

         for (int i = 0; i < length; i++) {
            if (guiPanels[i].type == (int)gsa::t::PanelType::Graph) {
               //ui->screenWidget = new QWidget(_splitterScreenWidget);
               ui->screenWidget->setParent(_splitterScreenWidget);
               ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
               //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
               ui->horizontalLayout_6->setParent(ui->screenWidget);
               ui->horizontalLayout_6->setSpacing(0);
               ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
               ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
               ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

               ui->screenWidget->setSizePolicy(policy);

               _splitterScreenWidget->addWidget(ui->screenWidget);

               int width = ui->screenWidget->width();
               //ui->screenWidget->setMinimumWidth(width / 2);
               //ui->screenWidget->setMaximumWidth(width / 2);
               //ui->screenWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               ui->screenWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               //ui->screenWidget-Hint>sizeHint()

               ui->screenWidget->setMinimumHeight((double)this->size().height() / 2.5);
               ui->screenWidget->setMinimumWidth((double)this->size().width() / 2.5);

            }
            else if (guiPanels[i].type == (int)gsa::t::PanelType::Table)
            {
               int index(1);

               QFrame *frame_2 = new QFrame(_splitterScreenWidget);
               frame_2->setObjectName(QStringLiteral("frame_2"));
               frame_2->setFrameShape(QFrame::StyledPanel);
               frame_2->setFrameShadow(QFrame::Raised);

               //frame_2->setStyleSheet(QLatin1String(
               //   "QFrame {\n"
               //   "background-color: rgb(8,8,8); \n"
               //   "}\n"
               //   "\n"
               //   ""));

               _frameSplitterScreenWidget->setStyleSheet(QString(""
                  "QFrame { "
                  "background-color: rgb(%1, %2, %3); "
                  "} "
                  ""
               ).arg(color_.red()).arg(color_.green()).arg(color_.blue())
               );

               //QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(frame_2);
               ////horizontalLayout_7->setSpacing(6);
               ////horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
               //horizontalLayout_7->setSpacing(0);
               //horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
               //horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));

               QGridLayout *horizontalLayout_7 = new QGridLayout(frame_2);

               //QSpacerItem *horizontalSpacer_2 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
               //horizontalLayout_7->addItem(horizontalSpacer_2);

               ////QSpacerItem *horizontalSpacer_3 = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
               //QSpacerItem *horizontalSpacer_3 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
               //horizontalLayout_7->addItem(horizontalSpacer_3);

               //QSpacerItem *horizontalSpacer_1 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
               QSpacerItem *horizontalSpacer_1 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
               horizontalLayout_7->addItem(horizontalSpacer_1, 0, 1);

               //QLabel *pLabel = new QLabel(frame_2);
               //pLabel->setText("first line\nsecond line\nthird line\n");
               //pLabel->setWordWrap(true);
               //pLabel->setStyleSheet(QLatin1String(
               //   "QLabel {\n"
               //   "background-color: rgb(8,8,8); \n"
               //   "color: rgb(128,128,128); \n"
               //   "}\n"
               //   "\n"
               //   ""));
               //horizontalLayout_7->addWidget(pLabel, 0, 1);

               //QSpacerItem *horizontalSpacer_2 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
               QSpacerItem *horizontalSpacer_2 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
               horizontalLayout_7->addItem(horizontalSpacer_2, 1, 0);

               //tableWidget = new QTableWidget(frame_2);
               //tableWidget->setObjectName(QStringLiteral("tableWidget"));
               //horizontalLayout_7->addWidget(tableWidget);
               _table = _mainScreen->fillTablePanel(frame_2, g_Parameter._tablePanel, index, nullptr);
               if (_table != nullptr) { 
                  horizontalLayout_7->addWidget(_table, 1, 1); 
                  //_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum); 
                  _table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum); 
               } 

               //QSpacerItem *horizontalSpacer_3 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
               QSpacerItem *horizontalSpacer_3 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
               horizontalLayout_7->addItem(horizontalSpacer_3, 1, 2);

               //QSpacerItem *horizontalSpacer_4 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);
               QSpacerItem *horizontalSpacer_4 = new QSpacerItem(1, 1, policy.horizontalPolicy(), policy.verticalPolicy());
               horizontalLayout_7->addItem(horizontalSpacer_4, 2, 1);

               //horizontalLayout_7->setStretch(0, 1);
               //horizontalLayout_7->setStretch(1, 50);
               //horizontalLayout_7->setStretch(2, 1);

               horizontalLayout_7->setRowStretch(0, 1);
               horizontalLayout_7->setRowStretch(1, 1);
               horizontalLayout_7->setRowStretch(2, 1);
               horizontalLayout_7->setColumnStretch(0, 1);
               horizontalLayout_7->setColumnStretch(1, 50);
               horizontalLayout_7->setColumnStretch(2, 1);

               frame_2->setSizePolicy(policy);

               _splitterScreenWidget->addWidget(frame_2);

               int width = frame_2->width();
               //frame_2->setMinimumWidth(width / 2);
               //frame_2->setMaximumWidth(width / 2);
               //frame_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
               //frame_2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
               QSize size_ = frame_2->sizeHint();
               size_;
               int i = 0;
            }
            else if (guiPanels[i].type == (int)gsa::t::PanelType::Disabled) {
               QPushButton *pushButton = new QPushButton(_splitterScreenWidget);
               pushButton->setText(QStringLiteral(""));
               pushButton->setObjectName(QStringLiteral(""));
               _splitterScreenWidget->addWidget(pushButton);
            }
         }

         //QList<int> sizes = { 500, 0 };
         //_splitterScreenWidget->setSizes(sizes);

         //QSizePolicy::Minimum on the "fixed" widget
         //QSizePolicy::Expanding on the other widget(s)

         //QSplitterHandle *handle_ = _splitterScreenWidget->handle(0);
         //QSize size_ = _splitterScreenWidget->minimumSizeHint();
         //_splitterScreenWidget->setSizePolicy();

         //int index = _splitterScreenWidget->indexOf(widget);
         _splitterScreenWidget->setCollapsible(0, false);
         _splitterScreenWidget->setCollapsible(1, false);

         //ui->horizontalLayout->addWidget(_splitterScreenWidget);
         ui->frameScreenWidgetHorizontalLayout->addWidget(_splitterScreenWidget);

         break;
      }
      case gsa::t::ViewConfiguration::TLeftVertical:
      {
         //TLeftVertical - три панели, при этом экран разделён вертикальной чертой, а левая из полученный панелей разделена горизонтальной 
         //(Panels - всегда состоит из трёх элементов со значениями Right (правый), LeftTop (левый верхний), LeftBottom (левый нижний), Disabled (Выключен));

         //QSplitter *splitterTemp(nullptr);

         std::map<int, int> indexes;
         //std::map<int, int> type_m;
         //public enum ViewConfiguration { Solo, DVertical, DHorizontal, TLeftVertical, TRightVertical, TTopHorizontal, TBottomHorizontal, Quadro };
         //public enum PanelPosition { Solo, Left, Right, Top, Bottom, LeftTop, LeftBottom, RightTop, RightBottom, Disabled };
         //Right, LeftTop, LeftBottom, Disabled 

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::LeftTop);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::LeftBottom);
         indexes[2] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Right);

         setCurrentTab(viewConfiguration, guiPanels, length);

         //addPanelWidget(guiPanels, indexes[2], splitterTemp);

         //int index = findIndex(guiPanels, (int)gsa::t::PanelPosition::Right);
         //if (index < 0) {
         //   position_m[0] = (int)gsa::t::PanelPosition::Right;
         //   type_m[0] = (int)gsa::t::PanelType::Disabled;
         //}
         //else {
         //   position_m[0] = (int)gsa::t::PanelPosition::Right;
         //   type_m[0] = (int)gsa::t::PanelType::Disabled;
         //}

         //int type;
         //type = (int)gsa::t::PanelPosition::Right;
         ////const gsa::t::GuiPanel *panel_ = std::find_if(guiPanels, guiPanels + gsa::t::maxPanel, [&type](gsa::t::GuiPanel *item) {return item->type == type; });
         //const gsa::t::GuiPanel *panel_ = std::find_if(&guiPanels[0], &guiPanels[gsa::t::maxPanel], [&type](gsa::t::GuiPanel *item) {return item->type == type; });

         //QSplitter *splitterTemp(nullptr);

         //_splitterHorizontal = new QSplitter(ui->frame2Central);
         //_splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
         //_splitterHorizontal->setOrientation(Qt::Horizontal);

         //QWidget *containerWidget = new QWidget(_splitterHorizontal);
         //containerWidget->setObjectName(QStringLiteral("containerWidget"));
         //_splitterHorizontal->addWidget(containerWidget);

         //_splitterVertical = new QSplitter(containerWidget);
         //_splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
         //_splitterVertical->setOrientation(Qt::Vertical);

         //QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget);
         //verticalLayout->setSpacing(0);
         //verticalLayout->setContentsMargins(11, 11, 11, 11);
         //verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
         //verticalLayout->setContentsMargins(0, 0, 0, 0);

         //for (int i = 0; i < length; i++) {
         //   //guiPanels[i].position;
         //   if (guiPanels[i].type == (int)gsa::t::PanelType::Graph) {
         //      if (guiPanels[i].position == (int)gsa::t::PanelPosition::Right) {
         //         splitterTemp = _splitterHorizontal;
         //      }
         //      else {
         //         splitterTemp = _splitterVertical;
         //      }
         //      ui->screenWidget->setParent(splitterTemp);
         //      ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //      //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //      ui->horizontalLayout_6->setParent(ui->screenWidget);
         //      ui->horizontalLayout_6->setSpacing(0);
         //      ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //      ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //      ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

         //      //if (guiPanels[i].position == (int)gsa::t::PanelPosition::Right) {
         //      //   //splitterTemp->addWidget(ui->screenWidget);
         //      //   splitterTemp->insertWidget(1, ui->screenWidget);
         //      //}
         //      //else {
         //      //   if (guiPanels[i].position == (int)gsa::t::PanelPosition::LeftTop) {
         //      //      splitterTemp->insertWidget(0, ui->screenWidget);
         //      //   }
         //      //   else {
         //      //      splitterTemp->insertWidget(1, ui->screenWidget);
         //      //   }
         //      //}
         //      splitterTemp->addWidget(ui->screenWidget);
         //      //splitterTemp->insertWidget(0, ui->screenWidget);
         //   }
         //   else if (guiPanels[i].type == (int)gsa::t::PanelType::Table)
         //   {
         //      if (guiPanels[i].position == (int)gsa::t::PanelPosition::Right) {
         //         splitterTemp = _splitterHorizontal;
         //      }
         //      else {
         //         splitterTemp = _splitterVertical;
         //      }
         //      //splitterTemp->insertWidget(0, ui->screenWidget);
         //   }
         //   else if (guiPanels[i].type == (int)gsa::t::PanelType::Disabled) {
         //      QPushButton *pushButton = new QPushButton(_splitterHorizontal);
         //      pushButton->setText(QStringLiteral(""));
         //      pushButton->setObjectName(QStringLiteral(""));
         //      _splitterHorizontal->addWidget(pushButton);
         //   }
         //}

         //verticalLayout->addWidget(_splitterVertical);

         //break;

         //_splitterHorizontal = new QSplitter(ui->frame2Central);
         _splitterHorizontal = new QSplitter(ui->frameScreenWidget);
         _splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
         _splitterHorizontal->setOrientation(Qt::Horizontal);

         //first left item 
         QWidget *containerWidget = new QWidget(_splitterHorizontal);
         containerWidget->setObjectName(QStringLiteral("containerWidget"));
         _splitterHorizontal->addWidget(containerWidget);

         {
            _splitterVertical = new QSplitter(containerWidget);
            _splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
            _splitterVertical->setOrientation(Qt::Vertical);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            //first top item 
            //QPushButton *pushButton1 = new QPushButton(_splitterVertical);
            //pushButton1->setText(QStringLiteral("pushButton1"));
            //pushButton1->setObjectName(QStringLiteral("pushButton1"));
            //_splitterVertical->addWidget(pushButton1);
            addPanelWidget(guiPanels, indexes[0], _splitterVertical);

            //first bottom item 
            //QPushButton *pushButton2 = new QPushButton(_splitterVertical);
            //pushButton2->setText(QStringLiteral("pushButton2"));
            //pushButton2->setObjectName(QStringLiteral("pushButton2"));
            //_splitterVertical->addWidget(pushButton2);
            addPanelWidget(guiPanels, indexes[1], _splitterVertical);

            verticalLayout->addWidget(_splitterVertical);
         }

         ////second right item 
         ////ui->screenWidget = new QWidget(_splitterHorizontal);
         //ui->screenWidget->setParent(_splitterHorizontal);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         ////ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setParent(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         ////ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         ////ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         ////ui->horizontalLayout_6->setSpacing(0);
         ////ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         ////ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         ////ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //_splitterHorizontal->addWidget(ui->screenWidget);
         addPanelWidget(guiPanels, indexes[2], _splitterHorizontal);

         _splitterHorizontal->setStretchFactor(0, 2);
         _splitterHorizontal->setStretchFactor(1, 20);

         //int index = _splitterScreenWidget->indexOf(widget);
         _splitterScreenWidget->setCollapsible(0, false);
         _splitterScreenWidget->setCollapsible(1, false);

         ui->horizontalLayout->addWidget(_splitterHorizontal);

         break;

         //ui->horizontalLayout->removeWidget(ui->screenWidget);
         //delete ui->horizontalLayout_6;
         //delete ui->screenWidget;

         //QSplitter *splitterHorizontal(nullptr);
         //QSplitter *splitterVertical(nullptr);

         //_splitterHorizontal = new QSplitter(ui->frame2Central);
         _splitterHorizontal = new QSplitter(ui->frameScreenWidget);
         _splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
         _splitterHorizontal->setOrientation(Qt::Horizontal);

         //first left item 
         containerWidget = new QWidget(_splitterHorizontal);
         containerWidget->setObjectName(QStringLiteral("containerWidget"));
         _splitterHorizontal->addWidget(containerWidget);

         {
            _splitterVertical = new QSplitter(containerWidget);
            _splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
            _splitterVertical->setOrientation(Qt::Vertical);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            //first top item 
            QPushButton *pushButton1 = new QPushButton(_splitterVertical);
            pushButton1->setText(QStringLiteral("pushButton1"));
            pushButton1->setObjectName(QStringLiteral("pushButton1"));
            _splitterVertical->addWidget(pushButton1);

            //first bottom item 
            QPushButton *pushButton2 = new QPushButton(_splitterVertical);
            pushButton2->setText(QStringLiteral("pushButton2"));
            pushButton2->setObjectName(QStringLiteral("pushButton2"));
            _splitterVertical->addWidget(pushButton2);

            verticalLayout->addWidget(_splitterVertical);
         }


         //second right item 
         //ui->screenWidget = new QWidget(_splitterHorizontal);
         ui->screenWidget->setParent(_splitterHorizontal);
         ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         ui->horizontalLayout_6->setParent(ui->screenWidget);
         ui->horizontalLayout_6->setSpacing(0);
         ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

         _splitterHorizontal->addWidget(ui->screenWidget);

         _splitterHorizontal->setStretchFactor(0, 2);
         _splitterHorizontal->setStretchFactor(1, 20);

         ui->horizontalLayout->addWidget(_splitterHorizontal);
         break;
      }
      case gsa::t::ViewConfiguration::TRightVertical:
      {
         //TRightVertical - три панели, при этом экран разделён вертикальной чертой, а правая из полученный панелей разделена горизонтальной 
         //(Panels - всегда состоит из трёх элементов со значениями Left(левый), RightTop (правый верхний), RightBottom (правый нижний), Disabled (Выключен));

         std::map<int, int> indexes;

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Left);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::RightTop);
         indexes[2] = findIndex(guiPanels, (int)gsa::t::PanelPosition::RightBottom);

         setCurrentTab(viewConfiguration, guiPanels, length);

         //ui->horizontalLayout->removeWidget(ui->screenWidget);
         //delete ui->horizontalLayout_6;
         //delete ui->screenWidget;

         //QSplitter *splitterHorizontal(nullptr);
         //QSplitter *splitterVertical(nullptr);

         //_splitterHorizontal = new QSplitter(ui->frame2Central);
         _splitterHorizontal = new QSplitter(ui->frameScreenWidget);
         _splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
         _splitterHorizontal->setOrientation(Qt::Horizontal);

         ////first item 
         //ui->screenWidget = new QWidget(_splitterHorizontal);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //_splitterHorizontal->addWidget(ui->screenWidget);
         addPanelWidget(guiPanels, indexes[0], _splitterHorizontal);

         //second item 
         QWidget *containerWidget = new QWidget(_splitterHorizontal);
         containerWidget->setObjectName(QStringLiteral("containerWidget"));
         _splitterHorizontal->addWidget(containerWidget);

         {
            _splitterVertical = new QSplitter(containerWidget);
            _splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
            _splitterVertical->setOrientation(Qt::Vertical);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            //second top item 
            //QPushButton *pushButton1 = new QPushButton(_splitterVertical);
            //pushButton1->setText(QStringLiteral("pushButton1"));
            //pushButton1->setObjectName(QStringLiteral("pushButton1"));
            //_splitterVertical->addWidget(pushButton1);
            addPanelWidget(guiPanels, indexes[1], _splitterVertical);

            //second bottom item 
            //QPushButton *pushButton2 = new QPushButton(_splitterVertical);
            //pushButton2->setText(QStringLiteral("pushButton2"));
            //pushButton2->setObjectName(QStringLiteral("pushButton2"));
            //_splitterVertical->addWidget(pushButton2);
            addPanelWidget(guiPanels, indexes[2], _splitterVertical);

            verticalLayout->addWidget(_splitterVertical);
         }

         _splitterHorizontal->setStretchFactor(0, 20);
         _splitterHorizontal->setStretchFactor(1, 2);

         ui->horizontalLayout->addWidget(_splitterHorizontal);
         break;
      }
      case gsa::t::ViewConfiguration::TTopHorizontal:
      {
         //TTopHorizontal - три панели, при этом экран разделён горизонтальной чертой, а верхняя из полученный панелей разделена вертикальной 
         //(Panels - всегда состоит из трёх элементов со значениями Bottom(нижний), LeftTop(левый верхний), RightTop (правый верхний), Disabled (Выключен));

         std::map<int, int> indexes;

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::RightTop);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::LeftTop);
         indexes[2] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Bottom);

         setCurrentTab(viewConfiguration, guiPanels, length);

         //ui->horizontalLayout->removeWidget(ui->screenWidget);
         //delete ui->horizontalLayout_6;
         //delete ui->screenWidget;

         //QSplitter *splitterHorizontal(nullptr);
         //QSplitter *splitterVertical(nullptr);

         //_splitterVertical = new QSplitter(ui->frame2Central);
         _splitterVertical = new QSplitter(ui->frameScreenWidget);
         _splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
         _splitterVertical->setOrientation(Qt::Vertical);

         //first item 
         QWidget *containerWidget = new QWidget(_splitterVertical);
         containerWidget->setObjectName(QStringLiteral("containerWidget"));
         _splitterVertical->addWidget(containerWidget);

         {
            _splitterHorizontal = new QSplitter(containerWidget);
            _splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
            _splitterHorizontal->setOrientation(Qt::Horizontal);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            //QPushButton *pushButton1 = new QPushButton(_splitterHorizontal);
            //pushButton1->setText(QStringLiteral("pushButton1"));
            //pushButton1->setObjectName(QStringLiteral("pushButton1"));
            //_splitterHorizontal->addWidget(pushButton1);
            addPanelWidget(guiPanels, indexes[0], _splitterHorizontal);

            //QPushButton *pushButton2 = new QPushButton(_splitterHorizontal);
            //pushButton2->setText(QStringLiteral("pushButton2"));
            //pushButton2->setObjectName(QStringLiteral("pushButton2"));
            //_splitterHorizontal->addWidget(pushButton2);
            addPanelWidget(guiPanels, indexes[1], _splitterHorizontal);

            verticalLayout->addWidget(_splitterHorizontal);
         }

         //second item 
         //ui->screenWidget = new QWidget(_splitterVertical);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //_splitterVertical->addWidget(ui->screenWidget);
         addPanelWidget(guiPanels, indexes[2], _splitterVertical);

         _splitterVertical->setStretchFactor(0, 5);
         _splitterVertical->setStretchFactor(1, 20);

         ui->horizontalLayout->addWidget(_splitterVertical);
         break;
      }
      case gsa::t::ViewConfiguration::TBottomHorizontal:
      {
         //TBottomHorizontal - три панели, при этом экран разделён горизонтальной чертой, а нижняя из полученный панелей разделена вертикальной 
         //(Panels - всегда состоит из трёх элементов со значениями Top (верхний), LeftBottom (левый нижний), RightBottom(правый нижний), Disabled (Выключен));

         std::map<int, int> indexes;

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::Top);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::RightBottom);
         indexes[2] = findIndex(guiPanels, (int)gsa::t::PanelPosition::LeftBottom);

         setCurrentTab(viewConfiguration, guiPanels, length);

         //ui->horizontalLayout->removeWidget(ui->screenWidget);
         //delete ui->horizontalLayout_6;
         //delete ui->screenWidget;

         //QSplitter *splitterHorizontal(nullptr);
         //QSplitter *splitterVertical(nullptr);

         //_splitterVertical = new QSplitter(ui->frame2Central);
         _splitterVertical = new QSplitter(ui->frameScreenWidget);
         _splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
         _splitterVertical->setOrientation(Qt::Vertical);

         //first item 
         //ui->screenWidget = new QWidget(_splitterVertical);
         //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
         //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
         //ui->horizontalLayout_6->setSpacing(0);
         //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
         //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
         //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
         //_splitterVertical->addWidget(ui->screenWidget);
         addPanelWidget(guiPanels, indexes[0], _splitterVertical);

         //second item 
         QWidget *containerWidget = new QWidget(_splitterVertical);
         containerWidget->setObjectName(QStringLiteral("containerWidget"));
         _splitterVertical->addWidget(containerWidget);

         {
            _splitterHorizontal = new QSplitter(containerWidget);
            _splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
            _splitterHorizontal->setOrientation(Qt::Horizontal);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            //QPushButton *pushButton1 = new QPushButton(_splitterHorizontal);
            //pushButton1->setText(QStringLiteral("pushButton1"));
            //pushButton1->setObjectName(QStringLiteral("pushButton1"));
            //_splitterHorizontal->addWidget(pushButton1);
            addPanelWidget(guiPanels, indexes[1], _splitterHorizontal);

            //QPushButton *pushButton2 = new QPushButton(_splitterHorizontal);
            //pushButton2->setText(QStringLiteral("pushButton2"));
            //pushButton2->setObjectName(QStringLiteral("pushButton2"));
            //_splitterHorizontal->addWidget(pushButton2);
            addPanelWidget(guiPanels, indexes[2], _splitterHorizontal);

            verticalLayout->addWidget(_splitterHorizontal);
         }

         _splitterVertical->setStretchFactor(0, 20);
         _splitterVertical->setStretchFactor(1, 5);

         ui->horizontalLayout->addWidget(_splitterVertical);
         break;
      }
      case gsa::t::ViewConfiguration::Quadro:
      {
         //Quadro - четыре панели. Экран одновременно разделён вертикальной и горизонтальной полосой 
         //(Panels - всегда состоит из четырёх элементов со значениями LeftTop(левый верхний), RightTop (правый верхний), LeftBottom (левый нижний), RightBottom(правый нижний), Disabled (Выключен)).

         std::map<int, int> indexes;

         indexes[0] = findIndex(guiPanels, (int)gsa::t::PanelPosition::LeftTop);
         indexes[1] = findIndex(guiPanels, (int)gsa::t::PanelPosition::RightTop);
         indexes[2] = findIndex(guiPanels, (int)gsa::t::PanelPosition::LeftBottom);
         indexes[3] = findIndex(guiPanels, (int)gsa::t::PanelPosition::RightBottom);

         //ui->horizontalLayout->removeWidget(ui->screenWidget);
         //delete ui->horizontalLayout_6;
         //delete ui->screenWidget;

         //QSplitter *splitterHorizontal(nullptr);
         //QSplitter *splitterVertical(nullptr);

         //_splitterVertical = new QSplitter(ui->frame2Central);
         _splitterVertical = new QSplitter(ui->frameScreenWidget);
         _splitterVertical->setObjectName(QStringLiteral("_splitterVertical"));
         _splitterVertical->setOrientation(Qt::Vertical);

         //first item 
         QWidget *containerWidget1 = new QWidget(_splitterVertical);
         containerWidget1->setObjectName(QStringLiteral("containerWidget1"));
         _splitterVertical->addWidget(containerWidget1);
         {
            //QSplitter *splitterHorizontal(nullptr);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget1);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            _splitterHorizontal = new QSplitter(containerWidget1);
            _splitterHorizontal->setObjectName(QStringLiteral("_splitterHorizontal"));
            _splitterHorizontal->setOrientation(Qt::Horizontal);

            //QPushButton *pushButton1 = new QPushButton(_splitterHorizontal);
            //pushButton1->setText(QStringLiteral("pushButton1"));
            //pushButton1->setObjectName(QStringLiteral("pushButton1"));
            //_splitterHorizontal->addWidget(pushButton1);
            addPanelWidget(guiPanels, indexes[0], _splitterHorizontal);

            //ui->screenWidget = new QWidget(_splitterHorizontal);
            //ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
            //ui->horizontalLayout_6 = new QHBoxLayout(ui->screenWidget);
            //ui->horizontalLayout_6->setSpacing(0);
            //ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
            //ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
            //ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
            //_splitterHorizontal->addWidget(ui->screenWidget);
            addPanelWidget(guiPanels, indexes[1], _splitterHorizontal);

            _splitterHorizontal->setStretchFactor(0, 20);
            _splitterHorizontal->setStretchFactor(1, 5);

            verticalLayout->addWidget(_splitterHorizontal);
         }

         //second item 
         QWidget *containerWidget2 = new QWidget(_splitterVertical);
         containerWidget2->setObjectName(QStringLiteral("containerWidget2"));
         _splitterVertical->addWidget(containerWidget2);
         {
            //QSplitter *splitterHorizontal(nullptr);

            QVBoxLayout *verticalLayout = new QVBoxLayout(containerWidget2);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(11, 11, 11, 11);
            verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);

            _splitterHorizontal2 = new QSplitter(containerWidget2);
            _splitterHorizontal2->setObjectName(QStringLiteral("_splitterHorizontal2"));
            _splitterHorizontal2->setOrientation(Qt::Horizontal);

            //QPushButton *pushButton3 = new QPushButton(_splitterHorizontal2);
            //pushButton3->setText(QStringLiteral("pushButton3"));
            //pushButton3->setObjectName(QStringLiteral("pushButton4"));
            //_splitterHorizontal2->addWidget(pushButton3);
            addPanelWidget(guiPanels, indexes[2], _splitterHorizontal2);

            //QPushButton *pushButton4 = new QPushButton(_splitterHorizontal2);
            //pushButton4->setText(QStringLiteral("pushButton4"));
            //pushButton4->setObjectName(QStringLiteral("pushButton4"));
            //_splitterHorizontal2->addWidget(pushButton4);
            addPanelWidget(guiPanels, indexes[3], _splitterHorizontal2);

            _splitterHorizontal2->setStretchFactor(0, 20);
            _splitterHorizontal2->setStretchFactor(1, 5);

            verticalLayout->addWidget(_splitterHorizontal2);
         }

         _splitterVertical->setStretchFactor(0, 2);
         _splitterVertical->setStretchFactor(1, 2);

         ui->horizontalLayout->addWidget(_splitterVertical);
         break;
      }
      default:
      {
      break;
      }
      }

      //// example 1 
      //horizontalLayout = new QHBoxLayout(frame2Central);
      //horizontalLayout->setSpacing(6);
      //horizontalLayout->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
      //splitter = new QSplitter(frame2Central);
      //splitter->setObjectName(QStringLiteral("splitter"));
      //splitter->setOrientation(Qt::Vertical);
      //pushButton = new QPushButton(splitter);
      //pushButton->setObjectName(QStringLiteral("pushButton"));
      //splitter->addWidget(pushButton);
      //screenWidget = new QWidget(splitter);
      //screenWidget->setObjectName(QStringLiteral("screenWidget"));
      //horizontalLayout_6 = new QHBoxLayout(screenWidget);
      //horizontalLayout_6->setSpacing(0);
      //horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
      //horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
      //splitter->addWidget(screenWidget);

      //horizontalLayout->addWidget(splitter);



      //// example 2 
      //horizontalLayout = new QHBoxLayout(frame2Central);
      //horizontalLayout->setSpacing(12);
      //horizontalLayout->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
      //horizontalLayout->setContentsMargins(15, 15, 15, 15);
      //splitter = new QSplitter(frame2Central);
      //splitter->setObjectName(QStringLiteral("splitter"));
      //splitter->setOrientation(Qt::Vertical);
      //frame_2 = new QFrame(splitter);
      //frame_2->setObjectName(QStringLiteral("frame_2"));
      //frame_2->setFrameShape(QFrame::StyledPanel);
      //frame_2->setFrameShadow(QFrame::Raised);
      //horizontalLayout_7 = new QHBoxLayout(frame_2);
      //horizontalLayout_7->setSpacing(6);
      //horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
      //horizontalSpacer_2 = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      //horizontalLayout_7->addItem(horizontalSpacer_2);

      //tableWidget = new QTableWidget(frame_2);
      //tableWidget->setObjectName(QStringLiteral("tableWidget"));

      //horizontalLayout_7->addWidget(tableWidget);

      //horizontalSpacer_3 = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      //horizontalLayout_7->addItem(horizontalSpacer_3);

      //splitter->addWidget(frame_2);
      //screenWidget = new QWidget(splitter);
      //screenWidget->setObjectName(QStringLiteral("screenWidget"));
      //horizontalLayout_6 = new QHBoxLayout(screenWidget);
      //horizontalLayout_6->setSpacing(0);
      //horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
      //horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
      //splitter->addWidget(screenWidget);

      //horizontalLayout->addWidget(splitter);

   }

   int MainWindow::findIndex(const gsa::t::GuiPanel guiPanels[], int position)
   {
      if (guiPanels != nullptr) {
         for (int i = 0; i < gsa::t::maxPanel; i++) {
            if (guiPanels[i].position == position) {
               return i;
            }
         }
      }
      return -1;
   }

   void MainWindow::addPanelWidget(const gsa::t::GuiPanel guiPanels[], int index, QSplitter *splitterTemp)
   {
      gsa::t::Theme *_theme(g_Parameter._theme);

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
      GetRgb(item_.value, r2, g2, b2);
      QColor color_(r2, g2, b2);

      if (index < 0) {
         QPushButton *pushButton1 = new QPushButton(splitterTemp);
         pushButton1->setText(QStringLiteral(""));
         pushButton1->setObjectName(QStringLiteral(""));
         splitterTemp->addWidget(pushButton1);
      }
      else {
         if (guiPanels[index].type == (int)gsa::t::PanelType::Graph) {
            ui->screenWidget->setParent(splitterTemp);
            ui->screenWidget->setObjectName(QStringLiteral("screenWidget"));
            ui->horizontalLayout_6->setParent(ui->screenWidget);
            ui->horizontalLayout_6->setSpacing(0);
            ui->horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
            ui->horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
            ui->horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

            splitterTemp->addWidget(ui->screenWidget);
         }
         else if (guiPanels[index].type == (int)gsa::t::PanelType::Table)
         {
            int index(1);
            QFrame *frame_2 = new QFrame(splitterTemp);
            frame_2->setObjectName(QStringLiteral("frame_2"));
            frame_2->setFrameShape(QFrame::StyledPanel);
            frame_2->setFrameShadow(QFrame::Raised);

            //frame_2->setStyleSheet(QLatin1String( 
            //   "QFrame {\n"
            //   "background-color: rgb(8,8,8); \n"
            //   "}\n"
            //   "\n"
            //   ""));

            _frameSplitterScreenWidget->setStyleSheet(QString(""
               "QFrame { "
               "background-color: rgb(%1, %2, %3); "
               "} "
               ""
            ).arg(color_.red()).arg(color_.green()).arg(color_.blue())
            );

            QHBoxLayout *horizontalLayout_7 = new QHBoxLayout(frame_2);
            //horizontalLayout_7->setSpacing(6);
            //horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
            horizontalLayout_7->setSpacing(0);
            horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
            horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
            //QSpacerItem *horizontalSpacer_2 = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QSpacerItem *horizontalSpacer_2 = new QSpacerItem(110, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

            horizontalLayout_7->addItem(horizontalSpacer_2);

            _table = _mainScreen->fillTablePanel(frame_2, g_Parameter._tablePanel, index, nullptr);
            if (_table != nullptr) {
               horizontalLayout_7->addWidget(_table);
               //_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
               _table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            }

            //QSpacerItem *horizontalSpacer_3 = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QSpacerItem *horizontalSpacer_3 = new QSpacerItem(110, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

            horizontalLayout_7->addItem(horizontalSpacer_3);

            horizontalLayout_7->setStretch(0, 1);
            horizontalLayout_7->setStretch(1, 50);
            horizontalLayout_7->setStretch(2, 1);

            splitterTemp->addWidget(frame_2);
         }
         else if (guiPanels[index].type == (int)gsa::t::PanelType::Disabled)
         {
            QPushButton *pushButton1 = new QPushButton(splitterTemp);
            pushButton1->setText(QStringLiteral(""));
            pushButton1->setObjectName(QStringLiteral(""));
            splitterTemp->addWidget(pushButton1);
         }
         else //gsa::t::PanelType::Disabled 
         {
            QPushButton *pushButton1 = new QPushButton(splitterTemp);
            pushButton1->setText(QStringLiteral(""));
            pushButton1->setObjectName(QStringLiteral(""));
            splitterTemp->addWidget(pushButton1);
         }
      }
   }

   void MainWindow::setGsaIcon(QPushButton *button, const QString &path)
   {
      QPixmap exitPixmap(path);
      QIcon exitIcon(exitPixmap);
      button->setIcon(exitIcon);
      button->setIconSize(exitPixmap.rect().size());
      button->setText(QString(""));
      button->setFixedSize(exitPixmap.rect().size());
   }

   void MainWindow::setModeName(QString text)
   {
      ui->labelModeMeasView->setText(text);

      gsa::t::Theme *_theme(g_Parameter._theme);
      //std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(fontindexes());
      //std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(colorindexes());
      //_fontindexes;
      //_colorindexes;
      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 
      gsa::t::ThemeItem itemTab_(themeItem); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end() ) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::CurrentMeasurement: //Current measurement selection area
               font_ = font;
               break;
            default:
               break;
            }
         }
      }

      for (auto &themeItem : _theme->themeItems) {
         switch (themeItem.type)
         {
         case 0:
         {
            if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) {
               switch (_colorindexes[std::wstring(themeItem.description)])
               {
               case gsa::t::ColorIndex::CurrentMeasurement: //Current measurement selection area 
                  item_ = themeItem;
                  break;
               case gsa::t::ColorIndex::TabSelectionArea: //Tab in the general dimension selection area 
                  itemTab_ = themeItem;
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

      int currentIndex = ui->tabScreenWidgets->currentIndex();
      if (currentIndex >= 0) {
         QWidget *currentWidget = ui->tabScreenWidgets->widget(currentIndex);
         if (currentWidget != nullptr) {
            QRegExp rx("[/]");
            QStringList valueParams = text.split(rx, QString::SkipEmptyParts);
            if (valueParams.size() > 1)
            {
               QString textNew(QString("%1\n%2").arg(valueParams[0]).arg(valueParams[1]));
               //QString textNew(QString("<font color = 'red'>%1\n%2</font>").arg(valueParams[0]).arg(valueParams[1]));
               //ui->tabScreenWidgets->setMyText(ui->tabScreenWidgets->indexOf(currentWidget), QApplication::translate("MainWindow", textNew.toStdString().c_str(), nullptr));
               //ui->tabScreenWidgets->setTabText(ui->tabScreenWidgets->indexOf(currentWidget), QApplication::translate("MainWindow", textNew.toStdString().c_str(), nullptr));
               int r, g, b;
               GetRgb(font_.color, r, g, b);
               int r2, g2, b2;
               GetRgb(item_.value, r2, g2, b2);
               int r3, g3, b3;
               GetRgb(itemTab_.value, r3, g3, b3);
               ui->tabScreenWidgets->setTabTextNew(ui->tabScreenWidgets->indexOf(currentWidget),
                  QApplication::translate("MainWindow", text.toStdString().c_str(), nullptr), font_, QColor(r, g, b), QColor(r2, g2, b2), QColor(r3, g3, b3));

               //// append
               //ui->textEdit->setFontWeight(QFont::DemiBold);
               //ui->textEdit->setTextColor(QColor("red"));
               //ui->textEdit->append(entry);
            }
            else {
               //ui->tabScreenWidgets->setTabText(ui->tabScreenWidgets->indexOf(currentWidget), QApplication::translate("MainWindow", text.toStdString().c_str(), nullptr));
            }
         }
      }
   }

   void MainWindow::keyPressed(QKeyEvent *_pEvent)
   {
      int l_n = 0;
   }

   MenuItem* MainWindow::getItemRbw(void)
   {
      for (int i = 0; i < realPageIndex; i++) {
         MenuItem *menuItem = _menuPages[i]->getItemRbw();
         if (menuItem != nullptr) {
            //QEvent _event(QEvent::MouseButtonPress);
            //_menuPages[i]->eventFilter(dynamic_cast<QObject*>(menuItem), &_event);
            return menuItem;
         }
      }
      return nullptr;
   }

   MenuItem* MainWindow::getItemByName(const QString &name)
   {
      for (int i = 0; i < realPageIndex; i++) {
         MenuItem *menuItem = _menuPages[i]->getItemByName(name);
         if (menuItem != nullptr) {
            //QEvent _event(QEvent::MouseButtonPress);
            //_menuPages[i]->eventFilter(dynamic_cast<QObject*>(menuItem), &_event);
            return menuItem;
         }
      }
      return nullptr;
   }

   //void MainWindow::init()
   //{
   //   //1
   //   QLineSeries *series = new QLineSeries();
   //   *series << QPointF(0, 6) << QPointF(9, 4) << QPointF(15, 20) << QPointF(25, 12) << QPointF(29, 26);
   //   QChart *chart = new QChart();
   //   chart->legend()->hide();
   //   chart->addSeries(series);

   //   //2
   //   // Customize series
   //   QPen pen(QRgb(0xfdb157));
   //   pen.setWidth(5);
   //   series->setPen(pen);

   //   // Customize chart title
   //   QFont font;
   //   font.setPixelSize(18);
   //   chart->setTitleFont(font);
   //   chart->setTitleBrush(QBrush(Qt::white));
   //   chart->setTitle("Gamma spectrum analyzer (gsa)");

   //   // Customize chart background
   //   QLinearGradient backgroundGradient;
   //   backgroundGradient.setStart(QPointF(0, 0));
   //   backgroundGradient.setFinalStop(QPointF(0, 1));
   //   backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
   //   backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
   //   backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
   //   chart->setBackgroundBrush(backgroundGradient);

   //   //// Customize plot area background
   //   //QLinearGradient plotAreaGradient;
   //   //plotAreaGradient.setStart(QPointF(0, 1));
   //   //plotAreaGradient.setFinalStop(QPointF(1, 0));
   //   //plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
   //   //plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
   //   //plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
   //   //chart->setPlotAreaBackgroundBrush(plotAreaGradient);
   //   chart->setPlotAreaBackgroundVisible(true);

   //   //3
   //   QCategoryAxis *axisX = new QCategoryAxis();
   //   QCategoryAxis *axisY = new QCategoryAxis();

   //   // Customize axis label font
   //   QFont labelsFont;
   //   labelsFont.setPixelSize(12);
   //   axisX->setLabelsFont(labelsFont);
   //   axisY->setLabelsFont(labelsFont);

   //   //// Customize axis colors
   //   //QPen axisPen(QRgb(0xd18952));
   //   //axisPen.setWidth(2);
   //   //axisX->setLinePen(axisPen);
   //   //axisY->setLinePen(axisPen);

   //   // Customize axis label colors
   //   QBrush axisBrush(Qt::white);
   //   axisX->setLabelsBrush(axisBrush);
   //   axisY->setLabelsBrush(axisBrush);

   //   // Customize grid lines and shades
   //   axisX->setGridLineVisible(false);
   //   axisY->setGridLineVisible(false);
   //   axisY->setShadesPen(Qt::NoPen);
   //   axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
   //   axisY->setShadesVisible(true);

   //   //4
   //   axisX->append("1000", 10);
   //   axisX->append("2000", 20);
   //   axisX->append("3000", 30);
   //   axisX->setRange(0, 30);

   //   axisY->append("10", 10);
   //   axisY->append("100", 20);
   //   axisY->append("1000", 30);
   //   axisY->setRange(0, 30);

   //   chart->setAxisX(axisX, series);
   //   chart->setAxisY(axisY, series);

   //   //5
   //   QChartView *chartView = new QChartView(chart);
   //   chartView->setRenderHint(QPainter::Antialiasing);

   //   //6
   //   //this->setCentralWidget(chartView);

   //   //pushButtonCentral = new QPushButton(ui->frame2Central);
   //   //pushButtonCentral->setObjectName(QStringLiteral("pushButtonCentral"));

   //   ui->horizontalLayout->addWidget(chartView);
   //}

   //void MainWindow::free(void)
   //{
   //}

   //void MainWindow::init2()
   //{
   //   int l_N;

   //   QChart *m_chart = new QChart;
   //   QChartView *chartView = new QChartView(m_chart);
   //   chartView->setMinimumSize(800, 600);

   //   //QLineSeries *m_series = new QLineSeries;
   //   m_series = new QLineSeries;
   //   m_chart->addSeries(m_series);

   //   QValueAxis *axisX = new QValueAxis;
   //   axisX->setRange(0, gsa::t::maxPoint);
   //   axisX->setLabelFormat("%g");
   //   axisX->setTitleText("Samples");

   //   QValueAxis *axisY = new QValueAxis;
   //   axisY->setRange(-1, 1);
   //   axisY->setTitleText("Audio level");
   //   m_chart->setAxisX(axisX, m_series);
   //   m_chart->setAxisY(axisY, m_series);
   //   m_chart->legend()->hide();
   //   m_chart->setTitle("Data from the microphone");

   //   //QVBoxLayout *mainLayout = new QVBoxLayout;
   //   //mainLayout->addWidget(chartView);
   //   //setLayout(mainLayout);

   //   m_series->clear();
   //   for (l_N = 0; l_N < gsa::t::maxPoint; l_N++)
   //   {
   //      m_series->insert(l_N, QPoint(l_N, 0));
   //      //   //   m_series->append(2, -0.5);
   //      //   //m_series->append(200, 0.5);
   //      //   //m_series->append(300, -0.8);
   //      //   //m_series->append(2200, 0.9);
   //   }

   //   ui->horizontalLayout->addWidget(chartView);

   //   //QAudioFormat formatAudio;
   //   //formatAudio.setSampleRate(8000);
   //   //formatAudio.setChannelCount(1);
   //   //formatAudio.setSampleSize(8);
   //   //formatAudio.setCodec("audio/pcm");
   //   //formatAudio.setByteOrder(QAudioFormat::LittleEndian);
   //   //formatAudio.setSampleType(QAudioFormat::UnSignedInt);

   //   //QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
   //   //m_audioInput = new QAudioInput(inputDevices, formatAudio, this);
   //   //m_device = new XYSeriesIODevice(m_series, this);

   //   //m_device->open(QIODevice::WriteOnly);
   //   //m_audioInput->start(m_device);
   //}

   //void MainWindow::free2(void)
   //{
   //   if (m_audioInput != nullptr) m_audioInput->stop();
   //   if (m_device != nullptr) m_device->close();
   //}

   void MainWindow::serverConnected(void)
   {
     int i = 0;
   }

   void MainWindow::serverDisconnected(void)
   {
     int i = 0;
   }

   void MainWindow::PipeClient()
   {
     QLocalSocket *socket = new QLocalSocket(nullptr);

     if (socket != nullptr) 
     {
       connect(socket, SIGNAL(connected()), this, SLOT(serverConnected()));
       connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));

       socket->connectToServer("BD.Pipe");

       socket->write("Hello from QtGuiLib");
       socket->flush();

       socket->disconnectFromServer();
     }

     return;
   }

   void MainWindow::init3(void)
   {
      //return;

      //PipeClient();

      gsa::t::Theme *_theme(g_Parameter._theme);
      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeFont fontAxis_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::PanelHeader: font_ = font; break;
            case gsa::t::FontIndex::MeasurementScale: fontAxis_ = font; break;
            default:
               break;
            }
         }
      }

      if (_colorindexes.size() > 18) {
         int  iiiii = 90;
      }
      for (auto &themeItem : _theme->themeItems) {
         switch (themeItem.type)
         {
         case 0:
         {
            if (_colorindexes.find(std::wstring(themeItem.description)) != _colorindexes.end()) {
               switch (_colorindexes[std::wstring(themeItem.description)])
               {
               case gsa::t::ColorIndex::CurrentMeasurement: //Current measurement selection area
                  //item_ = themeItem;
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

      int index(0);
      _mainScreen->init(&_chart, &_chartView, index, font_, fontAxis_);

      QSize size(_chartView->size());
      int i(0);

      //ui->comboBox->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
      //ui->comboBox->setFocusProxy((QWidget *)chartView);
      ui->comboBox->setMaxVisibleItems(10);
      //ui->comboBox->setMinimumHeight(100);
      //ui->comboBox->setStyleSheet("QListView::item{height: 100px}");

      //QList<QGraphicsView*> Lis = m_chart->scene()->views();
      //QList<QOpenGLWidget*> ll = Lis[0]->findChildren<QOpenGLWidget *>();

      ////l_Gl = (QOpenGLWidget *)chartView;
      ////l_F = l_Gl->format();
      //l_F = ll[0]->format();

      //int si = l_F.swapInterval();

      //ui->horizontalLayout->addWidget(_chartView);
      ui->horizontalLayout_6->addWidget(_chartView);
      ui->frameRight->raise();

      _mainScreen->setRestyle(0, g_Parameter._currentStyle);

      //_draw = true;
   }

   void MainWindow::free3(void)
   {
   }

   void MainWindow::tabSelected(int index)
   {
      ui->tabScreenWidgets;
      //_type(gsa::t::ViewConfiguration::Solo)
      //_tabParams._type = _type;
      //_tabs[index] = _tabParams;

      if (_tabs.find(index) == _tabs.end()) return;

      gsa::t::ViewConfiguration type = _tabs[index]._type;

      //van_003
      ui->frameScreenWidget->setHidden(true);
      ui->frameScreenWidget->hide();
      //ui->screenWidget->setHidden(true);
      //ui->screenWidget->hide();

      freeScreenWidget(_type);

      _type = _tabs[index]._type;
      _currentMode = _tabs[index]._currentMode;
      _currentMeas = _tabs[index]._currentMeas;
      _currentView = _tabs[index]._currentView;

      int currentMode = _tabs[index]._currentMode;
      int currentMeas = _tabs[index]._currentMeas;
      int currentView = _tabs[index]._currentView;

      _currentMenu->indexMode = _tabs[index]._currentMode;
      _currentMenu->indexMeas = _tabs[index]._currentMeas;
      _currentMenu->indexView = _tabs[index]._currentView;

      //initScreenWidget(_type, guiPanels, length);
      initScreenWidget(_type, _tabs[index]._guiPanels, _tabs[index]._length);

      if (index >= 0 && _tabs[index]._currentMode >= 0) {
         g_Parameter._CallActivator(_tabs[index]._currentMode, _tabs[index]._currentMeas, _tabs[index]._currentView);

         _currentMenuPage = _tabs[index]._currentMenuPage;

         ui->stackedWidget->setCurrentIndex(_currentMenuPage);
         ui->comboBox->setCurrentIndex(_currentMenuPage);
      }

      //van_003
      //ui->frameScreenWidget->setVisible(true);
      //ui->frameScreenWidget->show();
      //ui->screenWidget->setVisible(true);
      //ui->screenWidget->show();

      index = index;
   }

   void MainWindow::clickExit(void)
   {
      _stop = true;
      _mainScreen->setExit();
      qApp->quit();
   }

   void MainWindow::stop(void)
   {
      _stop = true;
      //_mainScreen->setExit();
      //mainWindow->isStop();
      qApp->quit();
   }

   void MainWindow::wheelEvent(QWheelEvent * event)
   {
      //event->delta() can be negative or positive
      //this->setText("Delta Value: " + QString::number(event->delta()));

      QPoint numPixels = event->pixelDelta();
      QPoint numDegrees = event->angleDelta() / 8;
      QString delta = QString::number(event->delta());
      //QPoint numS;
      //QPoint numSteps;

      QWidget *widget = ui->stackedWidget->currentWidget();
      MenuPage *menuPage = (MenuPage *)widget;
      if (menuPage != nullptr) {
         menuPage->doWheelEvent(event->delta());
      }

      //if (!numPixels.isNull()) {
      //   //numS = numPixels / 15;
      //   //scrollWithPixels(numPixels);
      //}
      //else if (!numDegrees.isNull()) {
      //   //numSteps = numDegrees / 15;
      //   //scrollWithDegrees(numSteps);
      //}

      event->accept();
   };

   void MainWindow::putCurrentIndexes(int PreviousPosition, int CurrentPosition)
   {
   }

   //void MainWindow::putData(double *_XData, double *_YData)
   //{
   //   if (m_series != nullptr) {
   //      for (int index = 0; index < gsa::t::maxPoint && index < m_series->points().count(); index++) {
   //         //m_series->replace(index, _Data.Values[index].XValue, _Data.Values[index].XValue);
   //      }
   //   }
   //}

   void MainWindow::slotPutTablePanel(int index)
   {
      //mutex.lock();
      //if (mutex.tryLock(2000) == false) return;
      QMutexLocker locker(&mutex);

      //QString str(QString("INFO0077 --------- %1 [%2] ").arg(__FUNCTION__).arg(__LINE__) );
      //qInfo(str.toStdString().c_str());

      //Sleep(16); 

      if (_tablePanel != nullptr && _tablePanel->Columns > 0 && _tablePanel->Rows > 0) 
      { 
         int count = ui->tabScreenWidgets->count(); 
         int currentIndex = ui->tabScreenWidgets->currentIndex(); 
         QWidget *parent(nullptr); 
         if (currentIndex >= 0) { 
            parent = ui->tabScreenWidgets->widget(currentIndex); 
            QRect centralRect = parent->frameGeometry(); // geometry(); 
            QPoint pointzero(0, 0); 
            QPoint pointxy = parent->mapToGlobal(pointzero); 
            QRect newRect; 
            newRect.setX(pointxy.x()); 
            newRect.setY(pointxy.y()); 
            newRect.setWidth(centralRect.width()); 
            newRect.setHeight(centralRect.height()); 

            _mainScreen->setCentralRect(newRect); 
         } 

         _mainScreen->putTablePanel(_tablePanel, index); 
      } 

      //mutex.unlock();

      //QString str2(QString("INFO007 --------- %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
      //qInfo(str2.toStdString().c_str());

   }

   void MainWindow::slotPutTableDat(int index, int length)
   {
      //mutex.lock();
      //if (mutex.tryLock() == false) return;
      QMutexLocker locker(&mutex);

      //QString str(QString("INFO0077 <<<>>> %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
      //qInfo(str.toStdString().c_str());

      //QString str(QString("INFO007 !!!!!!!!! %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
      //qInfo(str.toStdString().c_str());

      //Sleep(16);

      //QString str(QString("INFO007 <<<>>> %1 index = %2 length=%d ").arg(__FUNCTION__).arg(index).arg(length) );
      //qInfo(str.toStdString().c_str());

      _mainScreen->putTableData(_tablePanelData, index, length);

      //mutex.lock();
      //++numUsedBytes;
      //bufferNotEmpty.wakeAll();

      //mutex.unlock();

      //QString str2(QString("INFO007 !!!!!!!!! %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
      //qInfo(str2.toStdString().c_str());

   }

   void MainWindow::slotPutCurrentMenu(void)
   {
      ui->comboBox->clear();

      g_Parameter._currentMenu->indexMode;
      _currentMenu->nameMode;
      _currentMenu->nameMeas;
      _currentMenu->nameView;

      int indexMode = _currentMenu->indexMode;
      int indexMeas = _currentMenu->indexMeas;
      int indexView = _currentMenu->indexView;

      QString text(QString("%1 / %2 / %3").arg(
         QString::fromWCharArray(_currentMenu->nameMode)).arg(
         QString::fromWCharArray(_currentMenu->nameMeas)).arg(
         QString::fromWCharArray(_currentMenu->nameView)) );

      _currentMode = _currentMenu->indexMode;
      _currentMeas = _currentMenu->indexMeas;
      _currentView = _currentMenu->indexView;
      _currentMenuPage = 0;

      setModeName(text);

      int currentIndex(ui->tabScreenWidgets->currentIndex());
      int currentMenuPage(0);
      if (currentIndex >= 0) {
         if (_tabs.find(currentIndex) != _tabs.end()) {
            currentMenuPage = _tabs[currentIndex]._currentMenuPage;
         }
      }

      if (_currentMenu->length == 0) {
        //__van__ 2019.08.08 
        //MessageBox(NULL, L"_currentMenu->length == 0", L"Error", MB_OK);
      }
      else {
         //std::wstringstream ss;
         //ss << L"<<<>>> MainWindows() _currentMenu->length == " << _currentMenu->length << "  capacity == " << _currentMenu->capacity;
         //MessageBox(NULL, ss.str().c_str(), L"Error", MB_OK);

         int count = ui->stackedWidget->count();
         for (int i = 0; i < count; i++) {
            ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
         }

         for (int i = 0; i < gsa::t::maxPad; i++) {
            if (_menuPages[i] != nullptr) {
               delete _menuPages[i];
               _menuPages[i] = nullptr;
            }
         }

         _keys.clear();
         _stringMenuPages.clear();

         int pageIndex(0);
         //int realPageIndex(0);
         int index(-1);
         realPageIndex = 0;

         _length = _currentMenu->lengthScreen; 
         for (pageIndex = 0; pageIndex < _currentMenu->lengthScreen; pageIndex++) 
         { 
            std::string name(QString::fromWCharArray(_currentMenu->screenPads[pageIndex].name).toStdString()); 

            _mainScreen->createScreenPage(&(_currentMenu->screenPads[pageIndex]));

            //if (_stringMenuPages.find(name) == _stringMenuPages.end()) 
            //{ 
            //} 
         } 

         _length = _currentMenu->length;
         for (pageIndex = 0; pageIndex < _currentMenu->length; pageIndex++)
         {
            if (pageIndex == 5) {
               int i(0);
            }

            _currentMenu->pads[pageIndex].name;
            _currentMenu->pads[pageIndex].tab;

            //g_Parameter._theme->themeFonts[0];

            gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
            gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

            font_.description = nullptr;
            item_.description = nullptr;
            for (auto &font : g_Parameter._theme->themeFonts) {
               if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
                  switch (_fontindexes[std::wstring(font.description)])
                  {
                  case gsa::t::FontIndex::Default:
                     if (font_.description == nullptr)
                        font_ = font;
                     break;
                     //case gsa::t::FontIndex::CurrentMeasurement:
                     //case gsa::t::FontIndex::MeasurementScale:
                     //case gsa::t::FontIndex::PanelHeader:
                     //case gsa::t::FontIndex::QuickAccess:
                     //   break;
                  case gsa::t::FontIndex::DropDownMenu:
                     font_ = font;
                     break;
                     //case gsa::t::FontIndex::SelectedMenu:
                     //case gsa::t::FontIndex::ControlsSelectedTab:
                     //case gsa::t::FontIndex::ActiveMarker:
                     //case gsa::t::FontIndex::InactiveMarker:
                     //case gsa::t::FontIndex::ActiveMarkerTable:
                  default:
                     break;
                  }
               }
            }

            if (_colorindexes.size() > 18) {
               int  iiiii = 90;
            }
            
            for (auto &item : g_Parameter._theme->themeItems) {
               switch (item.type)
               {
               case 0:
               {
                  if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                     switch (_colorindexes[std::wstring(item.description)])
                     {
                     case gsa::t::ColorIndex::Default:
                        if (item_.description == nullptr) item_ = item;
                        break;
                     case gsa::t::ColorIndex::DropDownMenu:
                        item_ = item;
                        break;
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

            _colorindexes;

            std::string name(QString::fromWCharArray(_currentMenu->pads[pageIndex].name).toStdString());
            if (_stringMenuPages.find(name) == _stringMenuPages.end())
            {
               ui->comboBox->addItem(QString::fromWCharArray(_currentMenu->pads[pageIndex].name));

               //ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QFont("lucida", 40, QFont::Bold)), Qt::FontRole);
               if (font_.description == nullptr) {
                  ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QFont("Courier", 40, QFont::Bold)), Qt::FontRole);
                  //ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QColor(r, g, b)), Qt::TextColorRole);
                  //ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QColor(r, g, b)), Qt::BackgroundColorRole);
               } 
               else { 
                  //Font Style - normal | italic | oblique
                  //Font Weight - normal | bold
                  int weight;
                  if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal; 
                  else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold; 
                  QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);
                  if (QString::fromWCharArray(font_.style) == QString("oblique")) qfont_.setStyle(QFont::Style::StyleOblique);
                  else if (QString::fromWCharArray(font_.style) == QString("italic")) qfont_.setStyle(QFont::Style::StyleItalic);
                  else if (QString::fromWCharArray(font_.style) == QString("normal")) qfont_.setStyle(QFont::Style::StyleNormal);

                  ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(qfont_), Qt::FontRole);

                  int r, g, b; 
                  GetRgb(font_.color, r, g, b); 
                  ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QColor(r, g, b)), Qt::TextColorRole); 
                  //GetRgb(item_.value, r, g, b); 
                  //ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QColor(r, g, b)), Qt::BackgroundColorRole); 
               } 

               if (item_.description == nullptr) {
                  ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QColor(255, 255, 255)), Qt::BackgroundColorRole);
               }
               else {
                  int r, g, b;
                  GetRgb(item_.value, r, g, b);
                  ui->comboBox->setItemData(ui->comboBox->count() - 1, QVariant(QColor(r, g, b)), Qt::BackgroundColorRole);
               }

               _menuPages[realPageIndex] = new MenuPage(this, _currentMenu->pads[pageIndex], false, _controller);
               //_menuPages[pageIndex]->addItems(_currentMenu->pads[pageIndex], pageIndex, _keys);
               _menuPages[realPageIndex]->addItems(_currentMenu->pads[pageIndex], realPageIndex, _keys);
               _menuPages[realPageIndex]->addSpacer();

               ui->stackedWidget->addWidget(_menuPages[realPageIndex]);

               _stringMenuPages[name] = _menuPages[realPageIndex];

               _colorindexes;

               ++realPageIndex;
            }
            else {
               _stringMenuPages[name]->addPage(_currentMenu->pads[pageIndex]);
               //_stringMenuPages[name]->addItems(_currentMenu->pads[pageIndex], pageIndex, _keys);
               _stringMenuPages[name]->addItems(_currentMenu->pads[pageIndex], realPageIndex, _keys);
               _stringMenuPages[name]->addSpacer();

               _colorindexes;

            }

            _colorindexes;

            if (_colorindexes.size() > 18) {
               int  iiiii = 90;
            }
            //ui->comboBox->addItem(QString::fromWCharArray(_currentMenu->pads[pageIndex].name));

            //_currentMenu->pads[pageIndex].name;
            //_currentMenu->pads[pageIndex].tab;
            ////std::find_if(&_currentMenu->pads[0], &_currentMenu->pads[pageIndex], );
            //for (int i = 0; i < pageIndex; i++) {
            //   _menuPages[i]->caption();
            //   QString caption(QString::fromWCharArray(_menuPages[i]->caption()));
            //   QString name(QString::fromWCharArray(_currentMenu->pads[i].name));
            //   if (caption == name) {
            //      index = i;
            //   }
            //}

            //if (index >= 0) {
            //   int i(0);
            //}
            //else {
            //   int i(0);
            //}

            //_menuPages[pageIndex] = new MenuPage(this, _currentMenu->pads[pageIndex], false, _controller);
            //_menuPages[pageIndex]->addItems(_currentMenu->pads[pageIndex], pageIndex, _keys);
            //_menuPages[pageIndex]->addSpacer();

            //ui->stackedWidget->addWidget(_menuPages[pageIndex]);





            //_menuPages[pageIndex] = new QWidget();
            //_menuPages[pageIndex]->setObjectName(QStringLiteral("menuPages"));

            //QVBoxLayout *verticalLayout_2 = new QVBoxLayout(_menuPages[pageIndex]);
            //verticalLayout_2->setSpacing(2);
            //verticalLayout_2->setContentsMargins(11, 11, 11, 11);
            //verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
            //verticalLayout_2->setContentsMargins(2, 2, 2, 2);

            //int length = _currentMenu->pads[pageIndex].length;
            //for (int j = 0; j < _currentMenu->pads[pageIndex].length; j++) {
            //   //QString name = QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].name);
            //   QString type = QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].type);
            //   if (type == QString("Switch")) {
            //      QStringList strlist;
            //      for (int k = 0; k < _currentMenu->pads[pageIndex].items[j].guilist.length; k++) {
            //         strlist << QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].guilist.names[k]);
            //      }
            //      addItems(_menuPages[pageIndex], verticalLayout_2, QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].type), strlist, _currentMenu->pads[pageIndex].items[j].guilist.index);
            //   }
            //   else {
            //      addItem(_menuPages[pageIndex], verticalLayout_2, QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].type), QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].name) );
            //   }
            //}

            //QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
            //verticalLayout_2->addItem(verticalSpacer);
         }

         for (pageIndex = 0; pageIndex < _currentMenu->length; pageIndex++)
         {
            //if (_colorindexes.size() > 18) {
            //   int  iiiii = 90;
            //}
            if(_menuPages[pageIndex] != nullptr) 
               _menuPages[pageIndex]->setCustomizing();
         }

         //_mainScreen->setMenuPages(_menuPages);

         //ui->comboBox->addItem(QString::fromWCharArray(L"multi_pages"));

         //_menuPages[pageIndex] = new MenuPage(this, _currentMenu->pads[0], true, _controller);
         ////_menuPages[pageIndex]->addSpacer();

         //ui->stackedWidget->addWidget(_menuPages[pageIndex]);
      }

      if (currentIndex >= 0) {
         if (_tabs.find(currentIndex) != _tabs.end()) {
            _tabs[currentIndex]._currentMenuPage = currentMenuPage;
         }
      }

      ui->comboBox->setCurrentIndex(currentMenuPage);
      ui->comboBox->setFocusPolicy(Qt::ClickFocus);

      //ui->comboBox->setFont(QFont("lucida", 24, QFont::Bold));
      QLineEdit *lineEdit = ui->comboBox->lineEdit();
      if (lineEdit != nullptr) {
         lineEdit->setFont(QFont("lucida", 24, QFont::Bold));
      }

      //connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotIndexChanged(int)));

      //__van__ 2019.08.08 
      if (g_Parameter._modeMeasView.get() != nullptr)
      {
        wchar_t *name1 = g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].name;
        wchar_t *name2 = g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].guiMeases[_currentMenu->indexMeas].name;
        wchar_t *name3 = g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].guiMeases[_currentMenu->indexMeas].guiViewes[_currentMenu->indexView].name;
        g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].guiMeases[_currentMenu->indexMeas].guiViewes[_currentMenu->indexView].guiPanels[0].name;
        gsa::t::GuiPanel *guiPanels = g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].guiMeases[_currentMenu->indexMeas].guiViewes[_currentMenu->indexView].guiPanels;
        int length = g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].guiMeases[_currentMenu->indexMeas].guiViewes[_currentMenu->indexView].length;

        freeScreenWidget(_type);
        _type = static_cast<gsa::t::ViewConfiguration>(g_Parameter._modeMeasView->guiModes[_currentMenu->indexMode].guiMeases[_currentMenu->indexMeas].guiViewes[_currentMenu->indexView].type);
        //if(_type == gsa::t::ViewConfiguration::DVertical)
        //   _type = gsa::t::ViewConfiguration::DHorizontal;
        initScreenWidget(_type, guiPanels, length);

        //van_003
        ui->frameScreenWidget->setVisible(true);
        ui->frameScreenWidget->show();
      }
   }

   void MainWindow::GetRgb(const std::wstring &color, int &r, int &g, int &b)
   {
      std::wstring R = color.substr(0, 2);
      std::wstring G = color.substr(2, 2);
      std::wstring B = color.substr(4, 2);
      r = std::stoi(R, 0, 16);
      g = std::stoi(G, 0, 16);
      b = std::stoi(B, 0, 16);
   }

   void MainWindow::GetValue(const std::wstring &param, double &value)
   {
      value = std::stof(param);
   }

   void MainWindow::putTheme(gsa::t::Theme *_theme)
   {
      //g_Parameter._theme;
      //_mainScreen->putTheme(_theme);

      typedef struct {
         gsa::t::ThemeItem background;
         gsa::t::ThemeItem border;
         gsa::t::ThemeItem size;
      } tagItem;

      std::map<QWidget*, gsa::t::ThemeFont> widgetFonts_;
      //std::map<QWidget*, gsa::t::ThemeItem> widgetItems_;
      std::map<QWidget*, tagItem> widgetItems_;
      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

      if (_theme != nullptr) 
      {
         //gsa::t::ThemeFont *begin = _theme->themeFonts;
         //gsa::t::ThemeFont *end = begin + N;
         QString description("Default");
         gsa::t::ThemeFont *themeFont(std::find_if(std::begin(_theme->themeFonts), std::end(_theme->themeFonts),
            [&description](const gsa::t::ThemeFont& font) { return QString::fromWCharArray(font.description) == description; }) );
         gsa::t::ThemeItem *themeItem(std::find_if(std::begin(_theme->themeItems), std::end(_theme->themeItems),
            [&description](const gsa::t::ThemeItem& item) { return QString::fromWCharArray(item.description) == description; }));

         //if (std::end(_theme->themeFonts) != std::find_if(std::begin(_theme->themeFonts), std::end(_theme->themeFonts), 
         //   [&description](const gsa::t::ThemeFont& font) { return QString::fromWCharArray(font.description) == description; } ))
         if (themeFont == std::end(_theme->themeFonts)) font_.description = nullptr;
         else font_ = *themeFont;
         if (themeItem == std::end(_theme->themeItems)) item_.description = nullptr;
         else item_ = *themeItem;

         //list<S>::iterator it = find_if(l.begin(), l.end(), [](const S& s) { return s.S1 == 0; });
         //gsa::t::ThemeFont* it = find_if(l.begin(), l.end(), [](const S& s) { return s.S1 == 0; });

         //if (_fontindexes.find(L"Default") == _fontindexes.end()) {
         //   font_.description = nullptr;
         //}
         //else {
         //   font_ = _theme->themeFonts[(int)_fontindexes[L"Default"]];
         //}

         widgetFonts_[ui->comboBox] = font_;
         widgetItems_[ui->comboBox].background = item_;
         widgetItems_[ui->comboBox].size = item_;

         for (auto &font: _theme->themeFonts) {
            if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
               switch (_fontindexes[std::wstring(font.description)])
               {
               case gsa::t::FontIndex::CurrentMeasurement: //Current measurement selection area 
               case gsa::t::FontIndex::MeasurementScale: //Measurement scale 
               case gsa::t::FontIndex::PanelHeader: //Panel header 
               case gsa::t::FontIndex::QuickAccess: //Quick Access Area Tab 
                  break;
               case gsa::t::FontIndex::DropDownMenu: //Drop - down menu items(list of songs) 
               {
                  widgetFonts_[ui->comboBox] = font;
                  break;
               }
               case gsa::t::FontIndex::SelectedMenu: //Tabs of the selected menu(name of the subcomposition) 
               case gsa::t::FontIndex::ControlsSelectedTab: //Controls located in the selected tab 
               case gsa::t::FontIndex::ActiveMarker: //Displaying the active marker in the graphics area 
               case gsa::t::FontIndex::InactiveMarker: //Displaying inactive marker in the graphics area 
               case gsa::t::FontIndex::ActiveMarkerTable: //Displaying the active marker in the marker table 
               case gsa::t::FontIndex::Default: //Default 
               default:
                  break;
               }
            }
         } 

         //if (_colorindexes.size() > 18) {
         //   int  iiiii = 90;
         //}
         for (auto &item : _theme->themeItems) {
            switch (item.type)
            {
            case 0:
            {
               if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                  switch (_colorindexes[std::wstring(item.description)])
                  {
                  case gsa::t::ColorIndex::DisplayArea:
                  case gsa::t::ColorIndex::GraphicPanelScale: //Graphic panel scale
                  case gsa::t::ColorIndex::TableBorders: //Borders of the table display
                  case gsa::t::ColorIndex::CurrentMeasurement: //Current measurement selection area
                  case gsa::t::ColorIndex::TabSelectionArea: //Tab in the general dimension selection area
                  case gsa::t::ColorIndex::QuickAccess: //Tabs in the quick access area
                     break;
                  case gsa::t::ColorIndex::DropDownMenu: //Drop down menu
                  {
                     widgetItems_[ui->comboBox].background = item;
                     break;
                  }
                  case gsa::t::ColorIndex::UnifyingFrame: //Unifying frame in the menu area
                  case gsa::t::ColorIndex::UnifyingFrameBorder: //Border of the unifying frame in the menu area
                  case gsa::t::ColorIndex::ControlDropDownMenu: //Control drop - down list in the menu area
                  case gsa::t::ColorIndex::ControlDropDownPanel: //Control drop - down list in the panel(additional data area)
                  case gsa::t::ColorIndex::PanelControl: //Control in the panel(additional data area)
                  case gsa::t::ColorIndex::SelectedLine: //Selected line in the expanded control drop - down list
                  case gsa::t::ColorIndex::UnselectedString: //Unselected string in expanded control drop - down list
                  case gsa::t::ColorIndex::ElementsBorders: //Borders of the elements of the drop-down menu
                  {
                     widgetItems_[ui->comboBox].border = item;
                     break;
                  }
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
               if (_sizeindexes.find(std::wstring(item.description)) != _sizeindexes.end()) {
                  switch (_sizeindexes[std::wstring(item.description)])
                  {
                  case gsa::t::SizeIndex::MenuItem: //Menu item in the drop-down menu 
                     widgetItems_[ui->comboBox].size = item;
                     break;
                  }
               }
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

         if (widgetFonts_[ui->comboBox].description != nullptr)
         { 
            ////wchar_t *family; 
            ////int size; 
            ////wchar_t *style; 
            ////wchar_t *color; 

            ////font-family:"Trebuchet MS", sans - serif; 
            ////font-size:1.0em; 
            ////color:#fff; 
            ////border: 1px solid #000; 
            ////"font: bold 60px; " 
            ////"font: bold; " 
            ////"background: rgb(92, 92, 92); " 
            ////"height: 50px; width: 50px; " 
            ////"font-style: bold; " 

            gsa::t::ThemeFont font(widgetFonts_[ui->comboBox]); 

            int r, g, b; 
            GetRgb(font.color, r, g, b); 

            ui->comboBox->setStyleSheet(QString("%1 " 
               "QWidget { " //"QComboBox { " 
               "font-family: %2; " 
               "font-size: %3pt; " //"font-size: %3px; " 
               "font-weight: %4; " 
               "color: rgb(%5, %6, %7); " 
               "}" 
               //"QListView::item{height: 200px}" 
            ).arg(ui->comboBox->styleSheet()).arg(QString::fromWCharArray(font.family)).arg(font.size).arg(QString::fromWCharArray(font.style)).arg(r).arg(g).arg(b) 
            ); 
         } 

         if (widgetItems_[ui->comboBox].background.description != nullptr) 
         { 
            gsa::t::ThemeItem background(widgetItems_[ui->comboBox].background);

            int r, g, b; 
            GetRgb(background.value, r, g, b);

            ui->comboBox->setStyleSheet(QString("%1 " 
               "QWidget { " //"QComboBox { " 
               "background-color: rgb(%2, %3, %4); " 
               "}" 
            ).arg(ui->comboBox->styleSheet()).arg(r).arg(g).arg(b) 
            ); 
         }
         if (widgetItems_[ui->comboBox].size.description != nullptr) 
         { 
            gsa::t::ThemeItem size(widgetItems_[ui->comboBox].size); 
            gsa::t::ThemeItem border(widgetItems_[ui->comboBox].border);

            double value; 
            GetValue(size.value, value); 

            int r, g, b;
            GetRgb(border.value, r, g, b);

            QListView *view = new QListView(ui->comboBox);
            view->setStyleSheet(QString("%1 " 
               "QListView::item { " 
               "height: %2px; " 
               //"border: 5px solid green; "
               "border: 2px solid rgb(%3, %4, %5); "
               "} "
            ).arg(view->styleSheet()).arg( (int)value).arg(r).arg(g).arg(b) 
            ); 
            ui->comboBox->setView(view); 

            //QComboBox QAbstractItemView::item{ 
            //margin - top: 2px; 
            //} 
         } 
      } 
   } 

   void MainWindow::putCurrentMenu(gsa::t::CurrentMenu *currentMenu)
   {
      //_draw = false;

      _currentMenu = currentMenu;

      emit signalPutCurrentMenu();

      return;

      ui->comboBox->clear();

      if (_currentMenu->length == 0) {
         MessageBox(NULL, L"_currentMenu->length == 0", L"Error", MB_OK);
      }
      else {
         //std::wstringstream ss;
         //ss << L"<<<>>> MainWindows() _currentMenu->length == " << _currentMenu->length << "  capacity == " << _currentMenu->capacity;
         //MessageBox(NULL, ss.str().c_str(), L"Error", MB_OK);

         int count = ui->stackedWidget->count();
         for (int i = 0; i < count; i++) {
            ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
         }

         for (int i = 0; i < gsa::t::maxPad; i++) {
            if(_menuPages[i] != nullptr) delete _menuPages[i];
            _menuPages[i] = nullptr;
         }

         _keys.clear();
         _stringMenuPages.clear();

         int pageIndex(0);
         int index(-1);
         _length = _currentMenu->length;
         for (pageIndex = 0; pageIndex < _currentMenu->length; pageIndex++)
         {
            _currentMenu->pads[pageIndex].name;
            _currentMenu->pads[pageIndex].tab;

            std::string name(QString::fromWCharArray(_currentMenu->pads[pageIndex].name).toStdString());
            if (_stringMenuPages.find(name) == _stringMenuPages.end() ) 
            {
               ui->comboBox->addItem(QString::fromWCharArray(_currentMenu->pads[pageIndex].name));

               _menuPages[pageIndex] = new MenuPage(this, _currentMenu->pads[pageIndex], false, _controller);
               _menuPages[pageIndex]->addItems(_currentMenu->pads[pageIndex], pageIndex, _keys);
               _menuPages[pageIndex]->addSpacer();

               ui->stackedWidget->addWidget(_menuPages[pageIndex]);

               _stringMenuPages[name] = _menuPages[pageIndex];
            }
            else {
               _stringMenuPages[name]->addPage(_currentMenu->pads[pageIndex]);
               _stringMenuPages[name]->addItems(_currentMenu->pads[pageIndex], pageIndex, _keys);
               _stringMenuPages[name]->addSpacer();
            }

            //ui->comboBox->addItem(QString::fromWCharArray(_currentMenu->pads[pageIndex].name));

            //_currentMenu->pads[pageIndex].name;
            //_currentMenu->pads[pageIndex].tab;
            ////std::find_if(&_currentMenu->pads[0], &_currentMenu->pads[pageIndex], );
            //for (int i = 0; i < pageIndex; i++) {
            //   _menuPages[i]->caption();
            //   QString caption(QString::fromWCharArray(_menuPages[i]->caption()));
            //   QString name(QString::fromWCharArray(_currentMenu->pads[i].name));
            //   if (caption == name) {
            //      index = i;
            //   }
            //}

            //if (index >= 0) {
            //   int i(0);
            //}
            //else {
            //   int i(0);
            //}

            //_menuPages[pageIndex] = new MenuPage(this, _currentMenu->pads[pageIndex], false, _controller);
            //_menuPages[pageIndex]->addItems(_currentMenu->pads[pageIndex], pageIndex, _keys);
            //_menuPages[pageIndex]->addSpacer();

            //ui->stackedWidget->addWidget(_menuPages[pageIndex]);





            //_menuPages[pageIndex] = new QWidget();
            //_menuPages[pageIndex]->setObjectName(QStringLiteral("menuPages"));

            //QVBoxLayout *verticalLayout_2 = new QVBoxLayout(_menuPages[pageIndex]);
            //verticalLayout_2->setSpacing(2);
            //verticalLayout_2->setContentsMargins(11, 11, 11, 11);
            //verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
            //verticalLayout_2->setContentsMargins(2, 2, 2, 2);

            //int length = _currentMenu->pads[pageIndex].length;
            //for (int j = 0; j < _currentMenu->pads[pageIndex].length; j++) {
            //   //QString name = QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].name);
            //   QString type = QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].type);
            //   if (type == QString("Switch")) {
            //      QStringList strlist;
            //      for (int k = 0; k < _currentMenu->pads[pageIndex].items[j].guilist.length; k++) {
            //         strlist << QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].guilist.names[k]);
            //      }
            //      addItems(_menuPages[pageIndex], verticalLayout_2, QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].type), strlist, _currentMenu->pads[pageIndex].items[j].guilist.index);
            //   }
            //   else {
            //      addItem(_menuPages[pageIndex], verticalLayout_2, QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].type), QString::fromWCharArray(_currentMenu->pads[pageIndex].items[j].name) );
            //   }
            //}

            //QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
            //verticalLayout_2->addItem(verticalSpacer);
         }

         for (pageIndex = 0; pageIndex < _currentMenu->length; pageIndex++)
         {
            _menuPages[pageIndex]->setCustomizing();
         }

         //ui->comboBox->addItem(QString::fromWCharArray(L"multi_pages"));

         //_menuPages[pageIndex] = new MenuPage(this, _currentMenu->pads[0], true, _controller);
         ////_menuPages[pageIndex]->addSpacer();

         //ui->stackedWidget->addWidget(_menuPages[pageIndex]);
      }

      ui->comboBox->setCurrentIndex(0);
      ui->comboBox->setFocusPolicy(Qt::ClickFocus);

      connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotIndexChanged(int)));

      //if (_menuFreq != nullptr) delete _menuFreq;
      //_menuFreq = new Menu::MenuFreq(this, _controller);

      //ui->stackedWidget->addWidget(_menuFreq);

      //addItem(ui->menuPages, "Start");
      //addItem(ui->menuPages, "Stop");
   }

   void MainWindow::slotIndexChanged(int index)
   {
      _currentMenuPage = index;

      int currentIndex = ui->tabScreenWidgets->currentIndex();
      if (currentIndex >= 0) {
         if (_tabs.find(currentIndex) != _tabs.end()) {
            if ( _currentMenuPage >= 0 ) {
               _tabs[currentIndex]._currentMenuPage = _currentMenuPage;
            }
         }
      }

      ui->stackedWidget->setCurrentIndex(index);

      //ui->stackedWidget->setCurrentIndex(static_cast<int>(indexes[static_cast<TG::IndexMenu>(index)]));

      //_indexMenu = static_cast<TG::IndexMenu>(index);

      //if (static_cast<TG::IndexMenu>(index) == TG::indexPeakSearch) {
      //   _menuMarker->setAcivePeakSearch();
      //}
   }

   void MainWindow::keyProcess(gsa::t::ItemInfo &itemInfo) 
   { 
      _menuPages[itemInfo.pageIndex]->keyProcess(itemInfo);
   } 

   bool MainWindow::keyCheck(int keyCode, quint32 nativeModifiers, int key)
   {
      bool ret(false);
      gsa::t::KeyInfo keyInfo;
      keyInfo.keyCode = keyCode;
      keyInfo.nativeModifiers = (int)nativeModifiers;
      std::map<gsa::t::KeyInfo, gsa::t::ItemInfo>::iterator it(_keys.find(keyInfo));
      if (it != _keys.end()) {
         if (it->second.pageIndex >= 0 && it->second.pageIndex < gsa::t::maxPad) {
            ret = true;
         }
      }
      return ret;
   }

   void MainWindow::keyPadPressed(int keyCode, quint32 nativeModifiers, int key)
   {
      bool hardKeyCode(true);
      TG::IndexMenu indexMenu(TG::indexUserMenu);

      gsa::t::KeyInfo keyInfo;
      keyInfo.keyCode = keyCode;
      keyInfo.nativeModifiers = (int)nativeModifiers;
      //gsa::t::ItemInfo itemInfo;
      //std::map<gsa::t::KeyInfo, int>::iterator it(_keys.find(keyInfo));
      std::map<gsa::t::KeyInfo, gsa::t::ItemInfo>::iterator it(_keys.find(keyInfo));
      if (it != _keys.end()) {
         if (it->second.pageIndex >= 0 && it->second.pageIndex < gsa::t::maxPad ) {
            hardKeyCode = false;
            ui->stackedWidget->setCurrentWidget(_menuPages[it->second.pageIndex]);
            ui->comboBox->setCurrentIndex(it->second.pageIndex);

            if (it->second.itemtype > 0) {
               keyProcess(it->second);
            }
         }
      }

      if (hardKeyCode) {
         if (keyCode == Qt::Key_F) { //
            indexMenu = TG::indexFreq;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_K) { //
            indexMenu = TG::indexMarker;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_H) { //
            indexMenu = TG::indexPeakSearch;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_P) { //
            indexMenu = TG::indexUserMenu;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_A) { //
            indexMenu = TG::indexAmpt;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_B) { //
            indexMenu = TG::indexBw;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_C) { //
            indexMenu = TG::indexTrace;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_U) { //
            indexMenu = TG::indexUserMenu;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_W) { //
            indexMenu = TG::indexSweep;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_T) { //_T("t");
            indexMenu = TG::indexTrigger;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_I) { //_T("i");
            indexMenu = TG::indexInput;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_L) { //_T("l");
         }
         else if (keyCode == Qt::Key_S) { //_T("s");
            indexMenu = TG::indexMeasSetup;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_D) { //_T("d");
            indexMenu = TG::indexDisplay;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_U) { //_T("u");
            indexMenu = TG::indexUserMenu;
            emit menuChanged(indexMenu);
         }
         else if (keyCode == Qt::Key_F2) { //_T("F2"); //Save
         }
         else if (keyCode == Qt::Key_M) { //_T("m"); //MODE/Meas
         }
         else if (keyCode == Qt::Key_F3) { //_T("F3"); //Single
            indexMenu = TG::indexSweep;
            emit menuChanged(indexMenu);
            emit menuSingleCont();
         }
         else if (keyCode == Qt::Key_R) { //_T("r"); //Restart
            indexMenu = TG::indexSweep;
            emit menuChanged(indexMenu);
            emit menuSingleRestart();
         }
         else if (keyCode == Qt::Key_Q) { //_T("q"); //Quick Save
         }
         else if (keyCode == Qt::Key_Left) { //_T("Left");
            currentDown();
         }
         else if (keyCode == Qt::Key_Up) { //_T("Up");
            currentUp();
         }
         else if (keyCode == Qt::Key_Down) { //_T("Down");
            currentDown();
         }
         else if (keyCode == Qt::Key_Right) { //_T("Right");
            currentUp();
            //} else if(keyCode == Qt::Key_Enter) { //_T("Enter");
         }
         else if (keyCode == Qt::Key_Return) { //_T("Enter");
            emit menuItemEdit(QString("Enter"));
         }
         else if (keyCode == Qt::Key_PageDown) { //_T("Page Down");
            currentUp();
         }
         else if (keyCode == Qt::Key_PageUp) { //_T("Page Up");
            currentDown();
         }
         else if (keyCode == Qt::Key_Escape) { //_T("Esc");
            emit menuItemEdit(QString("Esc"));
         }
         else if (keyCode == Qt::Key_F1) { //_T("F1"); //Help
         }
         else if (keyCode == Qt::Key_F4) { //_T("F4"); //System
         }
         else if (keyCode == Qt::Key_7) { //_T("7");
            emit menuItemEdit(QString("7"));
         }
         else if (keyCode == Qt::Key_8) { //_T("8");
            emit menuItemEdit(QString("8"));
         }
         else if (keyCode == Qt::Key_9) { //_T("9");
            emit menuItemEdit(QString("9"));
         }
         else if (keyCode == Qt::Key_Backspace) { //_T("Backspace");
            emit menuItemEdit(QString("Backspace"));
         }
         else if (keyCode == Qt::Key_4) { //_T("4");
            emit menuItemEdit(QString("4"));
         }
         else if (keyCode == Qt::Key_5) { //_T("5");
            emit menuItemEdit(QString("5"));
         }
         else if (keyCode == Qt::Key_6) { //_T("6");
            emit menuItemEdit(QString("6"));
         }
         else if (keyCode == Qt::Key_Delete) { //_T("Del");
            emit menuItemEdit(QString("Delete"));
         }
         else if (keyCode == Qt::Key_1) { //_T("1");
            emit menuItemEdit(QString("1"));
         }
         else if (keyCode == Qt::Key_2) { //_T("2");
            emit menuItemEdit(QString("2"));
         }
         else if (keyCode == Qt::Key_3) { //_T("3");
            emit menuItemEdit(QString("3"));
         }
         else if (keyCode == Qt::Key_Control) { //_T("Ctrl");
         }
         else if (keyCode == Qt::Key_0) { //_T("0");
            emit menuItemEdit(QString("0"));
         }
         else if (keyCode == Qt::Key_B) { //_T(".");
            emit menuItemEdit(QString("."));
         }
         else if (keyCode == Qt::Key_C) { //_T("-");
         }
         else if (keyCode == Qt::Key_Alt) { //_T("Left Alt");
         }
         else if (keyCode == Qt::Key_ScrollLock) { //_T("Scroll lock");
         }
         else if (keyCode == Qt::Key_NumLock) { //_T("Num lock");
         }
         else if (keyCode == Qt::Key_Tab) { //_T("Tab");
         }
         else if (keyCode == Qt::Key_X) { //_T("ctrl-x");
            if (nativeModifiers == 0x14) {
               StopThreads();
            }
         }
      }
   }

   void MainWindow::currentDown(bool bWheel)
   {
   }

   void MainWindow::currentUp(bool bWheel)
   {
   }

   void MainWindow::StopThreads(void)
   {
      //QCoreApplication::exit(0);
      qApp->quit();
   }

   bool MainWindow::nativeEvent(const QByteArray &_EventType, void *_Message, long *_Result)
   {
      int i;

      switch (((MSG *)_Message)->message)
      {
      case WM_PAINT:
         i = 0;
         break;
      default:
         break;
      }
      return QWidget::nativeEvent(_EventType, _Message, _Result);
   }

   //void MainWindow::uiPropertyChanged(int item, int value)
   //{
   //   emit signalUiPropertyChanged(item, value);

   //   //DWORD id = GetCurrentThreadId();

   //   //for (int i = 0; i < _length; i++) {
   //   //   _menuPages[i]->changeData(item, value, unit);
   //   //}
   //}

   void MainWindow::changeDataEmit(int item, double value, wchar_t* unit)
   {
      emit signalChangeData(item, value, unit);

      //DWORD id = GetCurrentThreadId();

      //for (int i = 0; i < _length; i++) {
      //   _menuPages[i]->changeData(item, value, unit);
      //}
   }

   void MainWindow::uiPropertyChangedEmit(int item, int type, int value)
   {
      emit signalUiPropertyChanged(item, type, value);

      //DWORD id = GetCurrentThreadId();

      //for (int i = 0; i < _length; i++) {
      //   _menuPages[i]->changeData(item, value, unit);
      //}
   }

   void MainWindow::uiPropertyChanged(int item, int type, int value)
   {
      DWORD id = GetCurrentThreadId();

      for (int i = 0; i < _length; i++) {
         if (_menuPages[i] != nullptr) {
            _menuPages[i]->uiPropertyChanged(item, type, value);
         }
      }
   }

   void MainWindow::changeData(int item, double value, wchar_t* unit)
   {
      DWORD id = GetCurrentThreadId();

      for (int i = 0; i < _length; i++) {
         if (_menuPages[i] != nullptr) {
            _menuPages[i]->changeData(item, value, unit);
         }
      }

      _mainScreen->changeData(item, value, unit);
   }

   void MainWindow::putCarriage(gsa::t::CurrentData *_Data, int index)
   {
      //_mainScreen->putCarriage(_Data, m_Period, index);
   }

   void MainWindow::putCurrentData(gsa::t::CurrentData *_Data, int index, int length)
   {
      //if (_draw == true) {
      _mainScreen->putCurrentData(_Data, m_Period, index, length);
      //}

      //int l_N;
      //QVector<QPoint> l_Vector;

      //if (m_values == nullptr) {
      //   m_values = new gsa::t::XYValue[gsa::t::maxPoint];
      //}
      //else
      //{
      //   if (m_Vector == nullptr || m_series == nullptr)
      //      return;

      //   m_Blinker = (m_Blinker + 1) % (1000000 / m_Period);

      //   for (l_N = 0; l_N < gsa::t::maxPoint; l_N++)
      //   {
      //      //if (m_Blinker == 0)
      //      if (false)
      //      {
      //         //(*m_Vector)[l_N].setX((*m_Vector)[(l_N + 1023) % gsa::t::maxPoint].x());
      //         //(*m_Vector)[l_N].setY((*m_Vector)[(l_N + 1023) % gsa::t::maxPoint].y());
      //         (*m_Vector)[l_N].setX(0);
      //         (*m_Vector)[l_N].setY(0);
      //      }
      //      else
      //      {
      //         (*m_Vector)[l_N].setX(_Data->Values[l_N].XValue);
      //         if (abs(l_N - m_Position) > 30)
      //            (*m_Vector)[l_N].setY(_Data->Values[l_N].YValue);
      //         else if (abs(l_N - m_Position) > 17)
      //            (*m_Vector)[l_N].setY(0.0);
      //         else
      //            (*m_Vector)[l_N].setY(4.0);

      //      }
      //      //l_Vector.append()
      //   }

      //   if (m_bUpdated)
      //   {
      //      //(*m_SkipedVector)[m_Position].setX(m_Position);
      //      (*m_SkipedVector)[m_Position].setY(m_Skiped * 10);
      //      (*m_PeriodVector)[m_Position].setY(((qreal)m_Period) / 10000.0);
      //      m_Skiped = 0;
      //      m_Position = (m_Position + 1) % gsa::t::maxPoint;

      //      ui->labelPeriod->setText(QString::number(m_Period));

      //      m_series->replace(*m_Vector);
      //      if (m_bSkUpdated)
      //      {
      //         m_SkipedSeries->replace(*m_SkipedVector);
      //         m_bSkUpdated = false;
      //      }

      //      if (m_bPeriodUpdated)
      //      {
      //         m_PeriodSeries->replace(*m_PeriodVector);
      //         m_bPeriodUpdated = false;
      //      }
      //      m_bUpdated = false;
      //   }
      //   else
      //   {
      //      l_N = 0;
      //      m_Skiped++;
      //   }
      //}
   }

   void MainWindow::putTableData(gsa::t::TablePanelData *tablePanelData, int index, int length)
   {
      //mutex.lock();
      //if (mutex.tryLock() == false) return;
      {
         QMutexLocker locker(&mutex);

         //if (numUsedBytes == 0)
         //bool ret = bufferNotEmpty.wait(&mutex, 0);
         //bufferNotEmpty.wait(&mutex);
         //mutex.unlock();
         //if (ret == false) return;

         //QString str(QString("INFO0077 %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
         //qInfo(str.toStdString().c_str());

         //QString str(QString("INFO0077 %1[%2]%3 this = %4 ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__).arg((int)this, 0, 16));
         //qInfo(str.toStdString().c_str());

         //Sleep(16);

         if (tablePanelData->Length < 0) {
            return;
         }

         _tablePanelData = tablePanelData;

         //mutex.unlock();
         //Sleep(16);

      //}

         //QString str(QString("INFO0077 %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
         //qInfo(str.toStdString().c_str());

         //emit signalPutCurrentMenu();
         emit signalPutTableDat(index, length);
         //_mainScreen->putTableData(tablePanelData, index, length);

         //QString str2(QString("INFO007 <<<<<<<<<>>>>>>>>> %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
         //qInfo(str2.toStdString().c_str());

      }

   }

   void MainWindow::putTablePanel(gsa::t::Table *tablePanel, int index)
   {
      //if (mutex.tryLock() == false) return;

      {
         QMutexLocker locker(&mutex);

         //QString str(QString("INFO007 ||||||||| %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
         //qInfo(str.toStdString().c_str());

         _tablePanel = tablePanel;
         Sleep(16);

         //mutex.unlock();
      //}

         //emit signalPutCurrentMenu();
         emit signalPutTablePanel(index);
         //_mainScreen->putTablePanel(tablePanel);

         //QString str2(QString("INFO007 ||||||||| %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
         //qInfo(str2.toStdString().c_str());
      }
   }

   void MainWindow::keyPadPress(const int &keyCode, quint32 nativeModifiers, const int &key)
   {
      emit signalKeyPadPress(keyCode, nativeModifiers, key);
   }

   bool MainWindow::keypres(QKeyEvent *keyevent)
   {
      if (keyevent->key() == Qt::Key_W) {
         //_T() << "hi";
      }
      return true;
   }

   void MainWindow::resizeEvent(QResizeEvent * event)
   {
      Q_UNUSED(event)

      QDesktopWidget *mydesk = QApplication::desktop();
      QSize size2 = mydesk->size();

      QSize size1_ = event->size();
      QSize size11_ = event->oldSize();
      QSize size2_ = size();

      //if (size1_.height() > size2.height() ) {
      //   setMinimumHeight(size2.height());
      //   setMaximumHeight(size2.height());
      //   //return;
      //}

      //_chartView->setFixedSize(size1_);
      //_chartView->setMinimumSize(size1_);
      //_mainScreen->setMinimumSize(size1_);

      //_chart->setMinimumSize(400, 300);
      //_chart->setMaximumSize(400, 300);

      if (size().height() == 1136) {
         int i(0);
      }

      if (size().height() == 1078) {
         int i(0);
      }

      //QSize size3 = _mainScreen->size();
      QSize size3 = size();
      QSize size4 = _chartView->size();
      QSizeF size5 = _chart->size();
      QSizeF size6 = _chart->plotArea().size();

      //if (size3.height() > size2.height()) {
      //   setMinimumHeight(size2.height());
      //   setMaximumHeight(size2.height());
      //}

      QSize size3_ = size();

      //QPoint centralRect = ui->frame2Central->pos();
      QRect centralRect = ui->frame2Central->geometry();
      //QPoint bottom = ui->frame3Bottom2->pos();
      //QRect rect(centralRect.x(), centralRect.y(), );

      int i(g_Parameter._currentMenu->indexMode);
      int j(g_Parameter._currentMenu->indexMeas);
      int k(g_Parameter._currentMenu->indexView);

      //__van__ 2019.08.08 
      wchar_t *name(nullptr);
      if (g_Parameter._modeMeasView.get() != nullptr)
        name = g_Parameter._modeMeasView->guiModes[i].guiMeases[j].guiViewes[k].guiPanels[0].name;

      if(name != nullptr)
         _mainScreen->myResizeCallback(name, &centralRect); //(L"Normal");
      else
         _mainScreen->myResizeCallback(L"Spectrogram", &centralRect); //(L"Normal");
      //ResizeCallback(L"Normal", (_chart->findChildren<QOpenGLWidget *>())[0]->size().width());

      int count = ui->tabScreenWidgets->count();
      int currentIndex = ui->tabScreenWidgets->currentIndex();
      QWidget *parent(nullptr);
      if (currentIndex >= 0) {
         parent = ui->tabScreenWidgets->widget(currentIndex);
         QRect Rect2 = ui->tabScreenWidgets->frameGeometry(); // geometry();
         QRect centralRect = parent->frameGeometry(); // geometry();
         int i = 0;
      }
   }

   void MainWindow::show(void)
   {
      int i(0);
      return;
   }
   void MainWindow::showMaximized()
   {
      int i(0);
      return;
   }
   void MainWindow::showFullScreen()
   {
      int i(0);
      return;
   }
   void MainWindow::showNormal()
   {
      int i(0);
      return;
   }

   void MainWindow::moveEvent(QMoveEvent * event)
   {
      Q_UNUSED(event)

      if (_chartView == nullptr || _mainScreen == nullptr) return;

      //QSize size1_ = event->size();
QSize size2_ = size();

QDesktopWidget *mydesk = QApplication::desktop();
QSize size2 = mydesk->size();

QSize size3 = _chartView->size();
QSize size4 = _mainScreen->size();
   }

   void MainWindow::closeEvent(QCloseEvent *event)
   {
      if (true) {
         //ui->screenWidget->stop();
         //QTest::qSleep(300);
         event->accept();
      }
      else {
         event->ignore();
      }
   }

   void MainWindow::buttonESC()
   {
   }

   void MainWindow::slotMessageBox(wchar_t* _caption, wchar_t* _text)
   {
      DWORD id = GetCurrentThreadId();
      int i(0);

      DialogMessage *test = new DialogMessage(this, _caption, _text);
      test->show();
   }

   void MainWindow::slotSetMarker(int index, QString text, QColor color)
   {
      gsa::t::Theme *_theme(g_Parameter._theme);
      //std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
      //std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
      //std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
      //std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeFont fontInactive_(themeFont); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::ActiveMarkerTable: //Tabs of the selected menu(name of the subcomposition)
            {
               font_ = font;
               break;
            }
            case gsa::t::FontIndex::InactiveMarkerTable: //Tabs of the selected menu(name of the subcomposition)
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
      GetRgb(font_.color, r, g, b);
      QColor cfont_(r, g, b);

      int weight;
      if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal;
      else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold;
      QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);
      //qfont_.setPixelSize(font_.size);

      //QFont font;
      //font.setFamily(QString::fromWCharArray(font_.family));
      //font.setPixelSize(font_.size);
      QFontMetrics fm(qfont_);
      
      //fm.boundingRect(QRect(0, 0, width, 100), 0, QString("012345678901234"));
      QRect rect = fm.boundingRect(QString("012345678901234"));

#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
      uint32_t fontWidth = static_cast<int>(fm.horizontalAdvance(QString("012345678901234")));
#else
      uint32_t fontWidth = static_cast<int>(fm.width(QString("012345678901234567890123456789"))); //__van__
#endif
      uint32_t fontHeight = fm.height();
      uint32_t xHeight = fm.xHeight();

      int maxindex(0);
      bool _show(false);
      if (text.length() == 0)
         _visibles[index] = 0;
      else
         _visibles[index] = 1;

      int i(0);
      for (auto p : _visibles) {
         if (p.second == 1) {
            _show = true;
            maxindex = i; // index;
            //break; 
         }
         else {
            _labels[i]->setText(QString(""));
         }
         ++i;
      }

      //int i(0);
      //for (auto p : _visibles) {
      //   if (p.second == 0)
      //      _labels[index]->setText(QString(""));
      //   ++i;
      //}

      if (index == 3) {
         int jjj(0);
      }
      if (_show == false) {
         ui->frame3Bottom1->setMinimumHeight(0);
         ui->frame3Bottom1->setMaximumHeight(0);
      }
      else {
         if (_visibles[index] == 1)
         {
            _labelHeight = fontHeight;
            _labelHeight = font_.size;

            //int height = (index / 3 + 1) * _labels[0]->height() * 1.1;
            //int height = (index / 3 + 1) * _labelHeight * 1.3; 
            //int height = (maxindex / 3 + 1) * _labelHeight * 1.3;
            int height = (maxindex / 3 + 1) * _labelHeight * 2.1;
            if (height != 78) {
               int jjj(0);
            }

            int left, top, right, bottom;
            ui->gridLayout->getContentsMargins(&left, &top, &right, &bottom);

            ui->frame3Bottom1->setMinimumHeight(height);
            ui->frame3Bottom1->setMaximumHeight(height);

            ////_labels[index]->setFont(QFont("lucida", 12, QFont::Bold));
            //_labels[index]->setFont(QFont("lucida", 2));
            ////_labels[index]->setFont(qfont_);
            //_labels[index]->setText(text);

            QString textNew(QString(
               "<!DOCTYPE html>"
               "<html>"
               "<body>"
               "<p1 style=\"font-size:%1px\">%2</p1>"
               "</body>"
               "</html>"
            ).arg(font_.size).arg(text));
            _labels[index]->setText(textNew);

            //QPalette palette = _labels[index]->palette();
            ////palette.setColor(_labels[index]->backgroundRole(), Qt::red);
            ////palette.setColor(_labels[index]->foregroundRole(), Qt::yellow);
            ////palette.setColor(_labels[index]->foregroundRole(), color);
            //palette.setColor(_labels[index]->foregroundRole(), cfont_);
            //palette.setColor(_labels[index]->backgroundRole(), Qt::red);
            //_labels[index]->setPalette(palette);
            _labels[index]->setStyleSheet(QString(" "
               "QLabel { "
               //"background-color : red; "
               "color : rgb(%1, %2, %3); "
               "} "
            ).arg(cfont_.red()).arg(cfont_.green()).arg(cfont_.blue())
            );
         }
      }
   }

   void MainWindow::clickedPlusButton(void)
   {
      QWidget *tab_4 = new QWidget();
      tab_4->setObjectName(QStringLiteral("tab_4"));

      QHBoxLayout *horizontalLayout_007 = new QHBoxLayout(tab_4);
      horizontalLayout_007->setSpacing(0);
      horizontalLayout_007->setContentsMargins(11, 11, 11, 11);
      horizontalLayout_007->setObjectName(QStringLiteral("horizontalLayout_007"));
      horizontalLayout_007->setContentsMargins(0, 0, 0, 0);
      //QPushButton *pushButtonTmp = new QPushButton(tab_4);
      //pushButtonTmp->setObjectName(QStringLiteral("pushButtonTmp"));
      //pushButtonTmp->setText("START PROCESS !");
      //QHBoxLayout *horizontalLayout_6 = new QHBoxLayout(pushButtonTmp);
      //horizontalLayout_6->setSpacing(0);
      //horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
      //horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
      //horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

      //horizontalLayout_7->addWidget(pushButtonTmp);

      _currentMode = -1;
      _currentMeas = -1;
      _currentView = -1;
      _currentMenuPage = -1;

      ui->tabScreenWidgets->addTab(tab_4, QString());
      ui->tabScreenWidgets->setTabText(ui->tabScreenWidgets->indexOf(tab_4), QApplication::translate("MainWindow", "Any New Tab", nullptr));
      ui->tabScreenWidgets->setCurrentWidget(tab_4);

      //_tabs[0] = _tabParams;
      //int currentMode = _tabs[index]._currentMode;
      //int currentMeas = _tabs[index]._currentMeas;
      //int currentView = _tabs[index]._currentView;

      showModeMeasView();
   }

   void MainWindow::clickedModeMeasView(void)
   {
      //DialogModeMeasView *dialogModeMeasView = new DialogModeMeasView(this);
      //dialogModeMeasView->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
      //dialogModeMeasView->show();

      showModeMeasView();
   }

   bool MainWindow::showModeMeasView(void)
   {
      DialogModeMeasView *dialogModeMeasView = new DialogModeMeasView(this);
      dialogModeMeasView->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
      //dialogModeMeasView->setModal(true);
      //dialogModeMeasView->show();
      dialogModeMeasView->exec();

      _currentMode = dialogModeMeasView->currentMode();
      _currentMeas = dialogModeMeasView->currentMeas();
      _currentView = dialogModeMeasView->currentView();

      //g_Parameter._CallActivator(_currentMode, _currentMeas, _currentView);

      return true;
   }

   void MainWindow::clickedSystemParams(void)
   {
      //dialogSystemSettings *_dialogSystemSettings = new dialogSystemSettings(this);
      //_dialogSystemSettings->show();

      DialogSystemSettings2 *dialogSystemSettings2 = new DialogSystemSettings2(this);
      //dialogSystemSettings2->resize(100, 100);
      //dialogSystemSettings2->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
      dialogSystemSettings2->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
      dialogSystemSettings2->show();
      //dialogSystemSettings2->pos();
      //dialogSystemSettings2->size();

   }

   bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
   {
      //Qt::NoModifier;
      //Qt::ShiftModifier;
      //Qt::ControlModifier;
      //Qt::AltModifier;
      //Qt::MetaModifier;
      //Qt::KeypadModifier;
      //Qt::GroupSwitchModifier;

      //obj;

      //auto itObj = std::find_if(
      //   comboBoxes.begin(), comboBoxes.end(),
      //   [senderObj](QObject* p) { return p == senderObj; }
      //);
      //if (itObj != comboBoxes.end()) {
      //   double value((double)index);
      //   wcscpy(_text, L"TRUE");
      //   g_Parameter._SetValue(dynamic_cast<MenuComboBox*>(*itObj)->itemIndex(), value, _text, index);
      //}
      //else {
      //   int i(0);
      //}

      //need to use QShortcut(QKeySequence("Ctrl+Space"), this);
      //https://evileg.com/ru/post/75/
      //https://www.qtcentre.org/threads/31755-Qt-shortcut-to-hide-QWidget
      //https://stackoverflow.com/questions/17631601/how-to-program-custom-keyboard-shortcuts
      if (event->type() == QEvent::KeyPress) 
      {
         QString objName = obj->objectName();
         //if (objName != QString("MainWindowWindow")) return;

         QObject *senderObj = sender(); // This will give Sender object
         if (senderObj != nullptr) {
            QString senderObjName = senderObj->objectName();
            int i(0);
         }
         else {
            int i(0);
         }

         QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
         Qt::KeyboardModifiers keyboardModifiers = keyEvent->modifiers();

         quint32 nativeScanCode = keyEvent->nativeScanCode();
         quint32 nativeVirtualKey = keyEvent->nativeVirtualKey();
         quint32 nativeModifiers = keyEvent->nativeModifiers();
         int key = keyEvent->key();
         int key2 = Qt::Key_F1;

         //if (key == Qt::Key_Left && keyboardModifiers == Qt::AltModifier) {
         //   // do any 
         //   if (senderObj == anySender) {
         //      ;
         //   }
         //}

         //if (key == Qt::Key_Left || key == Qt::Key_Hyper_L || key == Qt::Key_Super_L ) {
         //   int t1 = nativeModifiers & Qt::Key_Alt;
         //   int t2 = key & Qt::Key_Left;
         //   int t3 = key & Qt::Key_Hyper_L;
         //   int t4 = key & Qt::Key_Super_L;

         //   if (keyboardModifiers == Qt::AltModifier) {
         //      ;
         //   }

         //   QString str = QString("%1").arg(nativeModifiers, 1, 16);
         //   int i(0);
         //}

         //_mainWindow->keyPadPress(keyEvent->key(), nativeModifiers);
         _mainWindow->keyPadPress(keyEvent->nativeVirtualKey(), nativeModifiers, key);
         if (_mainWindow->keyCheck(keyEvent->nativeVirtualKey(), nativeModifiers, key)) {
            return true;
         }

         switch (nativeScanCode)
         {
         case 328:
            if (nativeModifiers & 0x0001 != 0)
               _mainWindow->m_Period++;
            else
               _mainWindow->m_Period += 1000;

            if (_mainWindow->m_Period > 500000)
               _mainWindow->m_Period = 500000;
            g_Parameter._Deleagate(_mainWindow->m_Period);
            break;
         case 329:
            if (nativeModifiers & 0x0001 != 0)
               _mainWindow->m_Period += 10;
            else
               _mainWindow->m_Period += 10000;

            if (_mainWindow->m_Period > 500000)
               _mainWindow->m_Period = 500000;
            g_Parameter._Deleagate(_mainWindow->m_Period);
            break;
         case 336:
            if (nativeModifiers & 0x0001 != 0)
               _mainWindow->m_Period--;
            else
               _mainWindow->m_Period -= 1000;

            if (_mainWindow->m_Period < 10)
               _mainWindow->m_Period = 10;
            g_Parameter._Deleagate(_mainWindow->m_Period);
            break;
         case 337:
            if (nativeModifiers & 0x0001 != 0)
               _mainWindow->m_Period -= 10;
            else
               _mainWindow->m_Period -= 10000;

            if (_mainWindow->m_Period < 10)
               _mainWindow->m_Period = 10;
            g_Parameter._Deleagate(_mainWindow->m_Period);
            break;

         default:
            // !!!!!!!! 
            //если событие не обработно, передай дальше /van/2017.09.20
            return QObject::eventFilter(obj, event);
            //break;
            //return true;
         }
         return true;
      }
      else if (event->type() == QEvent::TouchBegin) {
         //_mainWindow->m_Period = 20000;
         //g_Parameter._Deleagate(_mainWindow->m_Period);
         return QObject::eventFilter(obj, event);
      }
      else if (event->type() == QEvent::TouchUpdate) {
         //_mainWindow->m_Period = 30000;
         //g_Parameter._Deleagate(_mainWindow->m_Period);
         return QObject::eventFilter(obj, event);
      }
      else if (event->type() == QEvent::TouchEnd) {
         //_mainWindow->m_Period = 40000;
         //g_Parameter._Deleagate(_mainWindow->m_Period);
         return QObject::eventFilter(obj, event);
      }
      else if (event->type() == QEvent::TouchCancel) {
         //_mainWindow->m_Period = 50000;
         //g_Parameter._Deleagate(_mainWindow->m_Period);
         return QObject::eventFilter(obj, event);
      }
      else if (event->type() == QEvent::MouseButtonPress) {
         //_mainWindow->m_Period = 50000;
         //g_Parameter._Deleagate(_mainWindow->m_Period);
         //Pad::KeyPadNew2 *keyPad = _controller->keyPadNew2();
         //if (obj != (QObject *)keyPad) {
         //   keyPad->doCancel();
         //   int i = 0;
         //}
         return QObject::eventFilter(obj, event);
      }
      else {
         // standard event processing

         //if (event->type() == QEvent::MouseButtonPress)
         //{
         //   if (mainWindow->ui->comboBox.)
         //}

         //if (event->type() == QEvent::Show)
         //{
         //   QObjectList ql = mainWindow->ui->comboBox->children();
         //   //::RedrawWindow((HWND)mainWindow->winId(), NULL, NULL, RDW_INTERNALPAINT);
         //}
         //{
         //   int i = 0;
         //   if (obj->isWidgetType())
         //      ((QWidget *)obj)->raise();
         //}
         return QObject::eventFilter(obj, event);
      }
   }

} // namespace Main

