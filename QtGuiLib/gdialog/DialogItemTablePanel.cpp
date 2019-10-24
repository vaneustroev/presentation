// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file   dialogsystemsettings2.cpp
// Created: 12.04.2017
//

#include "DialogItemTablePanel.h"
#include "ui_DialogItemTablePanel.h"

#include "guiUnman.h"
#include "gmain/mainwindow.h"

//VStyledItemDelegate::VStyledItemDelegate(QObject *parent)
//   : QStyledItemDelegate(parent)
//{
//   ;
//}

#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
#else
#endif

void DialogItemTablePanel::__test__(void)
{
   //setBackgroundBrush(QColor(0, 0, 0));

   //_model = new QSqlTableModel(_parent);
   _model = new QStandardItemModel(_parent);

   _font = font();
   _font.setFamily("Ubuntu Condensed");
   //"Ubuntu Condensed"
   const QString family = _font.family();

   setFont(_font);
   int pixelSize = _font.pixelSize();
   int pointSize = _font.pointSize();

   //_model->setTable("person");
   //_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
   //_model->select();
   //const int columnCount(2);
   if (_tablePanel != nullptr) {
      _rowCount = _tablePanel->Rows;
      _columnCount = _tablePanel->Columns;
   }
   else {
      _rowCount = 2;
      _columnCount = 2;
   }
   for (int row = 0; row < _rowCount; row++) {
      for (int col = 0; col < _columnCount; col++) {
         _model->setItem(row, col, new QStandardItem(QString("123456789\n987654321")));
      }
   }

   ui->tableView->setModel(_model);

   ui->tableView->verticalHeader()->hide();
   ui->tableView->horizontalHeader()->hide();

   ui->tableView->setWordWrap(true);
   ui->tableView->setTextElideMode(Qt::ElideLeft);

   ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
   ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

   ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 
   ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 

   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();

}

DialogItemTablePanel::DialogItemTablePanel(QWidget *parent, Main::MainWindow *appWidget, QGridLayout *gridLayout, gsa::t::Table *tablePanel, wchar_t* _caption, wchar_t* _text)
   : QDialog(parent)
   , _appWidget(appWidget)
   , ui(new Ui::DialogItemTablePanel)
   , _tablePanel(tablePanel)
   , _process(false)
   , _parent(parent)
   , _gridLayout(gridLayout)
   , _emptyRowStretch(0)
   , _objectRowStretch(0)
   , _emptyColumnStretch(0)
   , _objectColumnStretch(0)
   //, _currentMode(g_Parameter._currentMenu->indexMode)
   //, _currentMeas(g_Parameter._currentMenu->indexMeas)
   //, _currentView(g_Parameter._currentMenu->indexView)
   //, _timer(nullptr)
{
   ui->setupUi(this);

   //__test__(); //__van__ 2019.03.05 

   //* //__van__ 2019.03.05

   //setBackgroundBrush(QColor(0, 0, 0));

   //_model = new QSqlTableModel(_parent);
   _model = new QStandardItemModel(_parent);

   _font = font();
   _font.setFamily("Ubuntu Condensed");
   //"Ubuntu Condensed"
   const QString family = _font.family();

   setFont(_font);
   int pixelSize = _font.pixelSize();
   int pointSize = _font.pointSize();

   //_model->setTable("person");
   //_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
   //_model->select();
   //const int columnCount(2);
   if (_tablePanel != nullptr) {
      _rowCount = _tablePanel->Rows;
      _columnCount = _tablePanel->Columns;
   }
   else {
      _rowCount = 2;
      _columnCount = 2;
   }
   for (int row = 0; row < _rowCount; row++) {
      for (int col = 0; col < _columnCount; col++) {
         if(row == 0) 
            _model->setItem(row, col, new QStandardItem(QString("123456789\n987654321")));
         else
            _model->setItem(row, col, new QStandardItem(QString("123456789")));
      }
   }

   ui->tableView->setModel(_model);

   ui->tableView->verticalHeader()->hide();
   ui->tableView->horizontalHeader()->hide();

   ui->tableView->setWordWrap(true);
   ui->tableView->setTextElideMode(Qt::ElideLeft);

   ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
   ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

   //ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive); // +++ 
   //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive); // +++ 
   //ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 
   ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 

   //ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // !!! 
   //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // !!! 

   //ui->tableView->verticalHeader()->setStretchLastSection(true);
   //ui->tableView->horizontalHeader()->setStretchLastSection(true);

   //ui->tableView->verticalHeader()->sectionSize(0);
   //ui->tableView->horizontalHeader()->sectionSize(0);
   //ui->tableView->verticalHeader()->setMaximumSectionSize(28);
   //ui->tableView->horizontalHeader()->setMaximumSectionSize(16);
   ui->tableView->verticalHeader()->setMinimumSectionSize(1);
   ui->tableView->horizontalHeader()->setMinimumSectionSize(16);

   //ui->tableView->verticalHeader()->resizeSection(0, 200);
   //ui->tableView->horizontalHeader()->resizeSection(0, 200);

   //int size2 = this->size().height() / _rowCount;
   //ui->tableView->verticalHeader()->setDefaultSectionSize(this->size().height() / _rowCount);
   //ui->tableView->setMinimumSize(QSize(0, 0));

   //QFont font("times", 24);
   //_font.setFamily("Ubuntu Condensed");
   //QFont font("lucida", 24, QFont::Bold);
   //QFont font("times", 24);
   //QFontMetrics fm(font);

   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();

   //QSize size = ui->tableView->size();
   //ui->tableView->setColumnWidth(0, 70);

   //ui->tableView->setColumnWidth((ui->tableView->columnCount() - 1), 100);
   //ui->tableView->setItemDelegate(new PanelTableDelegate);

   //*/ //__van__ 2019.03.05 

   QSize sizeTable = ui->tableView->geometry().size();
   QSize sizeParent = _parent->geometry().size();
   QSize sizeThis = this->geometry().size();

   connect(ui->modes, SIGNAL(currentIndexChanged(int)), this, SLOT(IndexChangedExpd(int)));
   connect(ui->modes, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(IndexChangedExpd(const QString &)));

   gsa::t::Theme *_theme(g_Parameter._theme);
   std::map<std::wstring, gsa::t::FontIndex> &_fontindexes(_appWidget->fontindexes());
   std::map<std::wstring, gsa::t::ColorIndex> &_colorindexes(_appWidget->colorindexes());
   std::map<std::wstring, gsa::t::SizeIndex> &_sizeindexes(_appWidget->sizeindexes());
   std::map<std::wstring, gsa::t::IndentIndex> &_indentindexes(_appWidget->indentindexes());

   gsa::t::ThemeItem item_;
   gsa::t::ThemeItem itemTable_;

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
            case gsa::t::ColorIndex::TableBorders: //Borders of the table display 
               itemTable_ = themeItem;
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

   int r, g, b;
   _appWidget->GetRgb(itemTable_.value, r, g, b);
   QColor color_(r, g, b);
   int r2, g2, b2;
   _appWidget->GetRgb(item_.value, r2, g2, b2);
   QColor color2_(r2, g2, b2);

   const char *ch = ui->tableView->styleSheet().toStdString().c_str();
   ui->tableView->setStyleSheet(QString("%1 "
      //"QTableView::item { "
      //"border: 5px solid red; "
      ////"border-left: 1px solid white; "
      ////"border: 1px outset rgb(128,128,128); "
      //"} "
      "QTableView { "
      "border: 1px solid rgb(%2, %3, %4); "
      "background-color: rgb(%5, %6, %7); "
      //"border: 1px outset rgb(128,128,128); "
      //"border-left: 1px solid white; "
      //"background-color: rgb(0, 0, 255); "
      "} "
   //).arg("").arg(color_.red()).arg(color_.green()).arg(color_.blue()).arg(color2_.red()).arg(color2_.green()).arg(color2_.blue()) //.arg(""). //.arg(ui->tableView->styleSheet()).
   ).arg(ui->tableView->styleSheet()).arg(color_.red()).arg(color_.green()).arg(color_.blue()).
      arg(color2_.red()).arg(color2_.green()).arg(color2_.blue()) //.arg(""). //.arg(ui->tableView->styleSheet()).
   );

   //ui->tableView->setContentsMargins(22, 22, 22, 22);
   //QTableWidget::horizontalHeader().setStretchLastSection(true);



   //QString str(QString("INFO007 <<<>>> %1 this=%2 model=%3 thread=%4").arg(__FUNCTION__).arg((long long)this, 0, 16).arg((long long)_model, 0, 16).arg((long long)QThread::currentThread(), 0, 16));
   //qInfo(str.toStdString().c_str());

   //_timer = new QTimer();
   //_timer->setInterval(5000);

   //connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

   //QThread *thread = QThread::currentThread();

   //_timer->start();

}

DialogItemTablePanel::~DialogItemTablePanel()
{
   //delete _timer;
   delete ui;
}

void DialogItemTablePanel::keyPressEvent(QKeyEvent * event_) 
{
   //if (event_->key() == Qt::Key_Enter || event_->key() == Qt::Key_Return)
   if (event_->key() == Qt::Key_Escape)
      return;

   QDialog::keyPressEvent(event_);
}

void DialogItemTablePanel::fillColumnWidthes(const QFontMetrics &fm, std::array<int, gsa::t::maxCell> &columnWidthes, int &tableWidth)
{ 
   for (int c = 0; c < gsa::t::maxCell; c++) {
      columnWidthes[c] = 0;
   }
   for (int c = 0; c < gsa::t::maxCell; c++) {
      if (_tablePanel->Cells[c].Default.Value != nullptr) {
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
         int columnWidth = static_cast<int>(fm.horizontalAdvance(QString::fromWCharArray(_tablePanel->Cells[c].Default.Value)));
#else
         int columnWidth = static_cast<int>(fm.width(QString::fromWCharArray(_tablePanel->Cells[c].Default.Value))); //__van__
#endif
         int Column = _tablePanel->Cells[c].Column;
         if (columnWidthes[_tablePanel->Cells[c].Column] < columnWidth) {
            columnWidthes[_tablePanel->Cells[c].Column] = columnWidth;
         }
      }
   }
   int minColumnWidth = std::numeric_limits<int>::max();
   for (int c = 0; c < _tablePanel->Columns; c++) {
      if (columnWidthes[c] != 0 && minColumnWidth > columnWidthes[c]) {
         minColumnWidth = columnWidthes[c];
      }
   }
   for (int c = 0; c < _tablePanel->Columns; c++) {
      if (columnWidthes[c] == 0) {
         columnWidthes[c] = minColumnWidth;
      }
   }
   tableWidth = 0;
   for (int c = 0; c < _tablePanel->Columns; c++) {
      tableWidth += columnWidthes[c];
   }
}

void DialogItemTablePanel::resizeEvent_Fixed(QResizeEvent *event) 
{ 
   if (event->size().height() < 100) { 
      QSize oldSize(event->oldSize());
      QPoint point(ui->tableView->pos());
      QRect rect(point, oldSize);

      QSize size1 = ui->tableView->geometry().size();
      QSize size2 = event->size();

      int i = 0;
   }
   else {
      int i = 0;
   }

   QSize sizeTable = ui->tableView->geometry().size();
   QPoint pointTable(ui->tableView->pos());
   QRect rectTable(pointTable, sizeTable);

   QSize sizeParent = _parent->geometry().size();
   QSize sizeThis = this->geometry().size();
   QPoint thisPoint(this->pos());
   QRect thisRect(thisPoint, sizeThis);

   int i = 0;

   int hight;
   int hight2;
   int width;
   int width2;

   //QFontMetrics _fm(_font);

   //return; //__van__ 2019.03.05 

   //int cellWidth = sizeTable.width() / _columnCount;
   //double cellWidthCoef = (double)cellWidth / pixelsWide;
   //int cellHeight = sizeTable.height() / _rowCount;
   //double cellHeightCoef = (double)cellHeight / (2.6 * pixelsHigh);
   //double cellCoef = std::min(cellWidthCoef, cellHeightCoef);

   //int pixelSize = _font.pixelSize();
   int pixelSize = _font.pointSize();

   double cellCoef;
   QSize sizeViewport = ui->tableView->viewport()->size();

   int maxRowHeight = 0;
   int rowHeight = 0;
   //int maxColumnWidth = 0;
   //int columnWidth = 0;
   if (sizeParent.width() > sizeParent.height()) {
      //int maxRowHeight = _fm.height() * _rowCount;
      maxRowHeight = 0;
      rowHeight = 0;
      //int maxRowHeight2 = 0;
      rowHeight = sizeTable.height() / _rowCount;
      if (rowHeight < 1.4*pixelSize) rowHeight = 1.4*pixelSize;
      if (rowHeight > 2.2*pixelSize) rowHeight = 2.2*pixelSize;
      for (int r = 0; r < _rowCount; r++) {
         //ui->tableView->setRowHeight(r, sizeTable.height() / _rowCount);
         ui->tableView->setRowHeight(r, rowHeight);
         //ui->tableView->verticalHeader()->setDefaultSectionSize(sizeTable.height() / _rowCount);

         hight = ui->tableView->rowHeight(r);
         maxRowHeight += hight;

         hight2 = rowHeight; // sizeTable.height() / _rowCount;
         if (hight != hight2) {
            int i = 0;
         }
         //maxRowHeight2 += hight2;
      }
      cellCoef = ((double)rowHeight / pixelSize) / 2.2;

      int i = 0;
   }
   else {
      QFont font(_font);
      QFontMetrics fm(font);
      std::array<int, gsa::t::maxCell> columnWidthes;
      int tableWidth;

      fillColumnWidthes(fm, columnWidthes, tableWidth);

      ////int maxRowHeight = _fm.height() * _rowCount;
      int maxColumnWidth = 0;
      //int columnWidth = 0;
      ////int maxRowHeight2 = 0;
      //columnWidth = sizeTable.width() / _columnCount;
      //if (columnWidth < 1.4*pixelSize) columnWidth = 1.4*pixelSize;
      //if (columnWidth > 2.2*pixelSize) columnWidth = 2.2*pixelSize;
      //for (int r = 0; r < _columnCount; r++) {
      //   //ui->tableView->setRowHeight(r, sizeTable.height() / _rowCount);
      //   ui->tableView->setColumnWidth(r, columnWidth);
      //   //ui->tableView->verticalHeader()->setDefaultSectionSize(sizeTable.height() / _rowCount);

      //   width = ui->tableView->columnWidth(r);
      //   maxColumnWidth += width;

      //   width2 = columnWidth; // sizeTable.height() / _rowCount;
      //   if (width != width2) {
      //      int i = 0;
      //   }
      //   //maxRowHeight2 += hight2;
      //}
      double columnCoeff = (double)sizeParent.width() / tableWidth;
      if (columnCoeff < 0.5) columnCoeff = 0.5;
      if (columnCoeff > 1.0) {
         columnCoeff = 1.0;
      }
      //for (int r = 0; r < _columnCount; r++) {
      //   //ui->tableView->setRowHeight(r, sizeTable.height() / _rowCount);
      //   ui->tableView->setColumnWidth(r, columnCoeff*columnWidthes[r]);
      //   //ui->tableView->verticalHeader()->setDefaultSectionSize(sizeTable.height() / _rowCount);

      //   width = ui->tableView->columnWidth(r);
      //   maxColumnWidth += width;

      //   width2 = columnCoeff*columnWidthes[r]; // sizeTable.height() / _rowCount;
      //   if (width != width2) {
      //      int i = 0;
      //   }
      //   //maxRowHeight2 += hight2;
      //}

      cellCoef = columnCoeff;

      int i = 0;
   }

   ////int maxRowHeight = _fm.height() * _rowCount;
   //int maxRowHeight = 0;
   //int rowHeight = 0;
   ////int maxRowHeight2 = 0;
   //rowHeight = sizeTable.height() / _rowCount;
   //if (rowHeight < 1.4*pixelSize) rowHeight = 1.4*pixelSize;
   //if (rowHeight > 2.2*pixelSize) rowHeight = 2.2*pixelSize;
   //for (int r = 0; r < _rowCount; r++) {
   //   //ui->tableView->setRowHeight(r, sizeTable.height() / _rowCount);
   //   ui->tableView->setRowHeight(r, rowHeight);
   //   //ui->tableView->verticalHeader()->setDefaultSectionSize(sizeTable.height() / _rowCount);

   //   hight = ui->tableView->rowHeight(r);
   //   maxRowHeight += hight;

   //   hight2 = rowHeight; // sizeTable.height() / _rowCount;
   //   if (hight != hight2) {
   //      int i = 0;
   //   }
   //   //maxRowHeight2 += hight2;
   //}
   //cellCoef = ((double)rowHeight / pixelSize) / 2.2;

   //return; //__van__ 2019.03.05 

   QFont font(_font);
   //QFontMetrics fm(font);

   //cellCoef = ((double)rowHeight / pixelSize) / 2.2;
   font.setPixelSize(cellCoef * pixelSize);
   int iii = 0;

   //cellCoef = sizeTable.height() / maxRowHeight;
   //if (cellCoef > 1.0) cellCoef = 1.0;
   //else if (cellCoef < 0.5) cellCoef = 0.5;

   //if (_tablePanel != nullptr && _tablePanelData != nullptr) {
   for (int r = 0; r < _rowCount; r++) {
      for (int c = 0; c < _columnCount; c++) {
         //QModelIndex index(_model->index(_tablePanel->Cells[_tablePanelData->Values[i].CellID].Row, _tablePanel->Cells[_tablePanelData->Values[i].CellID].Column));
         QModelIndex index(_model->index(r, c));
         //QFont font("lucida", size.height() / (2 * _rowCount), QFont::Bold);
         //QFont font("lucida", sizeTable.height() / (2 * _rowCount));

         _model->setData(index, font, Qt::FontRole);

         const QVariant fontVariant = _model->data(index, Qt::FontRole);
         QFont newfont = qvariant_cast<QFont>(fontVariant);
         QFont theFont = fontVariant.value<QFont>();
      }
   }
   //}

   //for (int c = 0; c < _columnCount; c++) {
   //   //ui->tableView->setColumnWidth(c, sizeTable.width()/ _columnCount);
   //}

   //QFont font(_font);
   QFontMetrics fm(font); 
   std::array<int, gsa::t::maxCell> columnWidthes;
   int tableWidth;

   fillColumnWidthes(fm, columnWidthes, tableWidth);

   //for (int c = 0; c < gsa::t::maxCell; c++) { 
   //   columnWidthes[c] = 0; 
   //} 
   //int minColumnWidth = std::numeric_limits<int>::max();
   //for (int c = 0; c < _tablePanel->Columns; c++) {
   //   if (columnWidthes[c] != 0 && minColumnWidth > columnWidthes[c] ) {
   //      minColumnWidth = columnWidthes[c];
   //   }
   //}
   //for (int c = 0; c < _tablePanel->Columns; c++) {
   //   if (columnWidthes[c] == 0) {
   //      columnWidthes[c] = minColumnWidth;
   //   }
   //}
   //tableWidth = 0;
   //for (int c = 0; c < _tablePanel->Columns; c++) {
   //   tableWidth += columnWidthes[c];
   //}

   //return; //__van__ 2019.03.05 

   int maxColumnWidth = 0;
   int maxHorizontal = 0;
   for (int c = 0; c < _tablePanel->Columns; c++) {
      ui->tableView->setColumnWidth(c, columnWidthes[c]);
      int horizontal = ui->tableView->columnWidth(c);

      maxColumnWidth += columnWidthes[c];
      maxHorizontal += horizontal;
   }

   //return; //__van__ 2019.03.05 

   sizeParent;
   sizeTable;
   sizeThis;
   sizeViewport;

   //int emptyRowStretch = ((sizeParent.height() - maxRowHeight) / 2) / 100; 
   //int objectRowStretch = (maxRowHeight + 100) / 100; 
   //int emptyRowStretch = ((sizeParent.height() - maxRowHeight) / 2) / 1;
   //int objectRowStretch = (maxRowHeight) / 1;
   //int emptyRowStretch = ((sizeTable.height() - maxRowHeight) / 2) / 10;
   //int objectRowStretch = (maxRowHeight) / 10;

   int objectRowStretch = (100.0 * maxRowHeight) / (sizeParent.height()); 
   int emptyRowStretch = (100.0 * (sizeParent.height() - maxRowHeight)) / (sizeParent.height()); 
   //int objectRowStretch = (100.0 * maxRowHeight2) / (sizeParent.height()); 
   //int emptyRowStretch = (100.0 * (sizeParent.height() - maxRowHeight2)) / (sizeParent.height()); 
   emptyRowStretch = emptyRowStretch / 2; 
   objectRowStretch = powf((double)objectRowStretch, 2.0); 

   //int emptyColumnStretch = ((sizeParent.width() - maxColumnWidth) / 2) / 100; 
   //int objectColumnStretch = (maxColumnWidth + 100) / 100; 
   //int emptyColumnStretch = ((sizeParent.width() - maxColumnWidth) / 2) / 1; 
   //int objectColumnStretch = (maxColumnWidth) / 1; 
   int objectColumnStretch = (100.0 * 1.03 * maxColumnWidth) / (sizeParent.width()); 
   int emptyColumnStretch = (100.0 * (sizeParent.width() - 1.03 * maxColumnWidth)) / (sizeParent.width());
   emptyColumnStretch = emptyColumnStretch / 2; 
   //objectColumnStretch = powf((double)objectColumnStretch, 2.0); 

   //objectRowStretch *= objectRowStretch; 
   if (emptyRowStretch < 0) { 
      emptyRowStretch = 0; 
      //objectRowStretch = 50; 
   } 

   if ( 
      _emptyRowStretch != emptyRowStretch || 
      _objectRowStretch != objectRowStretch || 
      _emptyColumnStretch != emptyColumnStretch || 
      _objectColumnStretch != objectColumnStretch 
      ) 
   { 
      if (_gridLayout != nullptr) { 
         _gridLayout->setRowStretch(0, emptyRowStretch); 
         _gridLayout->setRowStretch(1, objectRowStretch); 
         _gridLayout->setRowStretch(2, emptyRowStretch); 

         _gridLayout->setColumnStretch(0, emptyColumnStretch); 
         _gridLayout->setColumnStretch(1, objectColumnStretch); 
         _gridLayout->setColumnStretch(2, emptyColumnStretch); 
         //if (emptyStretch != 4 || objectStretch != 8) { 
         //   int i = 0; 
         //} 
      } 

      _parent->updateGeometry();

      _emptyRowStretch = emptyRowStretch;
      _objectRowStretch = objectRowStretch;
      _emptyColumnStretch = emptyColumnStretch;
      _objectColumnStretch = objectColumnStretch;

   }

   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();

   //QDialog::resizeEvent(event);
}

void DialogItemTablePanel::resizeEvent_ResizeToContents(QResizeEvent *event)
{
   //QSize oldSize = event->oldSize();
   //QSize size = event->size();

   //ui->tableView->setGeometry();
   //QRect rect = ui->tableView->geometry();
   //QPoint point = ui->tableView->pos();

   if (event->size().height() < 100) {
      QSize oldSize(event->oldSize());
      QPoint point(ui->tableView->pos());
      QRect rect(point, oldSize);

      QSize size1 = ui->tableView->geometry().size();
      QSize size2 = event->size();
      //ui->tableView->setGeometry(rect);

      int i = 0;
   }
   else {
      int i = 0;
   }

   //QRect rect = ui->tableView->geometry();
   //ui->tableView->geometry().size()
   QSize sizeTable = ui->tableView->geometry().size();
   //size.setHeight(size.height() * 3);
   //size.setWidth(size.width() * 3);
   //double coefficient = (double) size.height() / (double)size.width();
   QPoint pointTable(ui->tableView->pos());
   QRect rectTable(pointTable, sizeTable);
   //ui->tableView->setGeometry(rect);

   QSize sizeParent = _parent->geometry().size();
   QSize sizeThis = this->geometry().size();
   //size.setHeight(size.height() * 3);
   //size.setWidth(size.width() * 3);
   //double coefficient = (double) size.height() / (double)size.width();
   QPoint thisPoint(this->pos());
   //point.setX(size.width()/2);
   QRect thisRect(thisPoint, sizeThis);
   //setGeometry(rect);

   int i = 0;

   int hight(std::numeric_limits<int>::max());
   int hight2(std::numeric_limits<int>::max());
   //QSize size = ui->tableView->size();
   //ui->tableView->setColumnWidth(0, 70);

   QFontMetrics _fm(_font);
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
   int pixelsWide = _fm.horizontalAdvance("What's the width of this text?"); 
#else
   int pixelsWide = _fm.width("What's the width of this text?"); //__van__
#endif
   int pixelsHigh = _fm.height();

   QFont font(_font);
   QFontMetrics fm(font);

   //_font.pixelSize();

   //pixelsWide = 0;
   //pixelsHigh = 0;
   //int count(_tablePanel->Columns * _tablePanel->Rows);
   //if (count > gsa::t::maxCell) count = gsa::t::maxCell;
   //for (int i = 0; i < count; i++) {
   pixelsWide = 0;
   for (int i = 0; i < _tablePanel->Columns; i++) {
      if (_tablePanel->Cells[i].Default.Value != nullptr)
      {
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
         if (pixelsWide < _fm.horizontalAdvance(QString::fromWCharArray(_tablePanel->Cells[i].Default.Value)))
            pixelsWide = _fm.horizontalAdvance(QString::fromWCharArray(_tablePanel->Cells[i].Default.Value));
#else
         if (pixelsWide < _fm.width(QString::fromWCharArray(_tablePanel->Cells[i].Default.Value))) //__van__
            pixelsWide = _fm.width(QString::fromWCharArray(_tablePanel->Cells[i].Default.Value)); //__van__
#endif

         //QColor background_(_tablePanel->Cells[i].Default.Background.Red, _tablePanel->Cells[i].Default.Background.Green, _tablePanel->Cells[i].Default.Background.Blue);
         //QColor foreground_(_tablePanel->Cells[i].Default.Foreground.Red, _tablePanel->Cells[i].Default.Foreground.Green, _tablePanel->Cells[i].Default.Foreground.Blue);
      }
   }

   int cellWidth = sizeTable.width() / _columnCount;
   double cellWidthCoef = (double)cellWidth / pixelsWide;
   int cellHeight = sizeTable.height() / _rowCount;
   double cellHeightCoef = (double)cellHeight / (2.6 * pixelsHigh);
   double cellCoef = std::min(cellWidthCoef, cellHeightCoef);

   //font.setPixelSize(cellCoef * font.pixelSize());

   int size2 = this->size().height() / _rowCount;
   //ui->tableView->verticalHeader()->setDefaultSectionSize(this->size().height() / _rowCount);



   int pixelSize = _font.pixelSize();
   //int pointSize = _font.pointSize();

   QSize sizeViewport = ui->tableView->viewport()->size();
   //if (pixelSize * (_rowCount * 3) > sizeTable.height()) {
   //   pixelSize = sizeTable.height() / (_rowCount * 3);
   //   font.setPixelSize(pixelSize);
   //   sizeTable.setHeight(pixelSize * (_rowCount * 3));
   //   int hight = sizeTable.height();
   //   if (hight != pixelSize * (_rowCount * 3)) {
   //      int i = 0;
   //   }
   //}
   if (2.6 * pixelSize > (double)hight) {
      pixelSize = (double)hight / 2.6;
      //font.setPixelSize(pixelSize);
      //sizeTable.setHeight(pixelSize * (_rowCount * 3));
      //int hight = sizeTable.height();
      //if (hight != pixelSize * (_rowCount * 3)) {
      //   int i = 0;
      //}
   }
   //sizeTable.height();

   //pixelSize = font.pixelSize();
   //font.setPixelSize(cellCoef * font.pixelSize());
   //int pixelSizeNew = font.pixelSize();
   //if (pixelSize != pixelSizeNew) {
   //   int iii = 0;
   //}

   ////if (_tablePanel != nullptr && _tablePanelData != nullptr) {
   //for (int r = 0; r < _rowCount; r++) {
   //   for (int c = 0; c < _columnCount; c++) {
   //      //QModelIndex index(_model->index(_tablePanel->Cells[_tablePanelData->Values[i].CellID].Row, _tablePanel->Cells[_tablePanelData->Values[i].CellID].Column));
   //      QModelIndex index(_model->index(r, c));
   //      //QFont font("lucida", size.height() / (2 * _rowCount), QFont::Bold);
   //      //QFont font("lucida", sizeTable.height() / (2 * _rowCount));

   //      //_model->setData(index, font, Qt::FontRole);
   //      const QVariant fontVariant = _model->data(index, Qt::FontRole);
   //      QFont newfont = qvariant_cast<QFont>(fontVariant);
   //      QFont theFont = fontVariant.value<QFont>();
   //   }
   //}
   ////}



   //int maxRowHeight = _fm.height() * _rowCount;
   int maxRowHeight = 0;
   //int maxRowHeight2 = 0;
   for (int r = 0; r < _rowCount; r++) {
      ui->tableView->setRowHeight(r, sizeTable.height() / _rowCount);
      //ui->tableView->verticalHeader()->setDefaultSectionSize(sizeTable.height() / _rowCount);

      hight = ui->tableView->rowHeight(r);
      maxRowHeight += hight;

      hight2 = sizeTable.height() / _rowCount;
      if (hight != sizeTable.height() / _rowCount) {
         int i = 0;
      }
      //maxRowHeight2 += hight2;
   }


   //cellCoef = sizeTable.height() / maxRowHeight;
   //if (cellCoef > 1.0) cellCoef = 1.0;
   //else if (cellCoef < 0.5) cellCoef = 0.5;

   //pixelSize = font.pixelSize();
   //font.setPixelSize(cellCoef * font.pixelSize());
   //int pixelSizeNew = font.pixelSize();
   //if (pixelSize != pixelSizeNew) {
   //   int iii = 0;
   //}

   ////if (_tablePanel != nullptr && _tablePanelData != nullptr) {
   //for (int r = 0; r < _rowCount; r++) {
   //   for (int c = 0; c < _columnCount; c++) {
   //      //QModelIndex index(_model->index(_tablePanel->Cells[_tablePanelData->Values[i].CellID].Row, _tablePanel->Cells[_tablePanelData->Values[i].CellID].Column));
   //      QModelIndex index(_model->index(r, c));
   //      //QFont font("lucida", size.height() / (2 * _rowCount), QFont::Bold);
   //      //QFont font("lucida", sizeTable.height() / (2 * _rowCount));

   //      //_model->setData(index, font, Qt::FontRole);

   //      const QVariant fontVariant = _model->data(index, Qt::FontRole);
   //      QFont newfont = qvariant_cast<QFont>(fontVariant);
   //      QFont theFont = fontVariant.value<QFont>();
   //   }
   //}
   ////}

   //maxRowHeight = 0;
   //for (int r = 0; r < _rowCount; r++) {
   //   ui->tableView->setRowHeight(r, sizeTable.height() / _rowCount);
   //   //ui->tableView->verticalHeader()->setDefaultSectionSize(sizeTable.height() / _rowCount);

   //   hight = ui->tableView->rowHeight(r);
   //   maxRowHeight += hight;

   //   hight2 = sizeTable.height() / _rowCount;
   //   if (hight != sizeTable.height() / _rowCount) {
   //      int i = 0;
   //   }
   //}

   for (int c = 0; c < _columnCount; c++) {
      //ui->tableView->setColumnWidth(c, sizeTable.width()/ _columnCount);
   }

   int maxColumnWidth = 0;
   int maxHorizontal = 0;
   //ui->tableView->horizontalHeader()->size 
   for (int c = 0; c < _tablePanel->Columns; c++) {
      if (_tablePanel->Cells[c].Default.Value != nullptr) {
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
         int columnWidth = static_cast<int>(_fm.horizontalAdvance(QString::fromWCharArray(_tablePanel->Cells[c].Default.Value)));
#else
         int columnWidth = static_cast<int>(_fm.width(QString::fromWCharArray(_tablePanel->Cells[c].Default.Value))); //__van__
#endif

         ui->tableView->setColumnWidth(c, columnWidth);

         int horizontal = ui->tableView->columnWidth(c);
         if (columnWidth != horizontal) {
            int i = 0;
         }
         maxColumnWidth += columnWidth;
         maxHorizontal += horizontal;
      }
      else {
         //ui->tableView->setColumnWidth(c, sizeTable.width()/ (_columnCount*5)); 
      }
   }

   sizeParent;
   sizeTable;
   sizeThis;
   sizeViewport;

   //QSize thisSize = this->size();
   //this->setMaximumWidth(maxSize);

   //int emptyRowStretch = ((sizeParent.height() - maxRowHeight) / 2) / 100; 
   //int objectRowStretch = (maxRowHeight + 100) / 100; 
   //int emptyRowStretch = ((sizeParent.height() - maxRowHeight) / 2) / 1;
   //int objectRowStretch = (maxRowHeight) / 1;
   //int emptyRowStretch = ((sizeTable.height() - maxRowHeight) / 2) / 10;
   //int objectRowStretch = (maxRowHeight) / 10;

   int objectRowStretch = (100.0 * maxRowHeight) / (sizeParent.height());
   int emptyRowStretch = (100.0 * (sizeParent.height() - maxRowHeight)) / (sizeParent.height());
   //int objectRowStretch = (100.0 * maxRowHeight2) / (sizeParent.height());
   //int emptyRowStretch = (100.0 * (sizeParent.height() - maxRowHeight2)) / (sizeParent.height());
   emptyRowStretch = emptyRowStretch / 2;
   //objectRowStretch = objectRowStretch * objectRowStretch;
   objectRowStretch = powf((double)objectRowStretch, 1.8);

   int emptyColumnStretch = ((sizeParent.width() - maxColumnWidth) / 2) / 100;
   int objectColumnStretch = (maxColumnWidth + 100) / 100;
   //int emptyColumnStretch = ((sizeParent.width() - maxColumnWidth) / 2) / 1;
   //int objectColumnStretch = (maxColumnWidth) / 1;

   //objectRowStretch *= objectRowStretch; 
   if (emptyRowStretch < 0) {
      emptyRowStretch = 0;
      //objectRowStretch = 50; 
   }

   if (
      _emptyRowStretch != emptyRowStretch ||
      _objectRowStretch != objectRowStretch ||
      _emptyColumnStretch != emptyColumnStretch ||
      _objectColumnStretch != objectColumnStretch
      )
   {
      if (_gridLayout != nullptr) {
         //_gridLayout->setRowStretch(0, 1);
         //_gridLayout->setRowStretch(1, 1);
         //_gridLayout->setRowStretch(2, 1);
         _gridLayout->setRowStretch(0, emptyRowStretch);
         _gridLayout->setRowStretch(1, objectRowStretch);
         _gridLayout->setRowStretch(2, emptyRowStretch);

         //_gridLayout->setColumnStretch(0, 4);
         //_gridLayout->setColumnStretch(1, 8);
         //_gridLayout->setColumnStretch(2, 4);
         _gridLayout->setColumnStretch(0, emptyColumnStretch);
         _gridLayout->setColumnStretch(1, objectColumnStretch);
         _gridLayout->setColumnStretch(2, emptyColumnStretch);
         //if (emptyStretch != 4 || objectStretch != 8) {
         //   int i = 0;
         //}
      }

      _parent->updateGeometry();

      _emptyRowStretch = emptyRowStretch;
      _objectRowStretch = objectRowStretch;
      _emptyColumnStretch = emptyColumnStretch;
      _objectColumnStretch = objectColumnStretch;

   }

   //QDialog::resizeEvent(event);
}

void DialogItemTablePanel::resizeEvent(QResizeEvent *event)
{
   //return; //__van__ 2019.03.05 

   resizeEvent_Fixed(event);
   //resizeEvent_ResizeToContents(event);
}

//void DialogItemTablePanel::updateTime()
//{
//   //ui->label->setText(QTime::currentTime().toString()); 
//   _timer->stop();
//
//   delete _timer;
//
//   QDialog::accept();
//}

void DialogItemTablePanel::setNames(QStringList names)
{
   _names.clear();
   ui->modes->clear();

   _names = names;

   ui->verticalLayout->removeWidget(ui->frame);

   if ( _names.size() > 0 ) {
      _process = true;
      ui->verticalLayout->insertWidget(0, ui->frame);
      ui->verticalLayout->setStretch(0, 1);
      ui->verticalLayout->setStretch(1, 14);
      //ui->modes->show();

      ui->modes->insertItems(0, _names);
      ui->modes->setCurrentIndex(_internalIndex);
      _process = false;
   }
   else {
      //ui->verticalLayout->insertWidget(0, ui->frame);
      //ui->modes->hide();
   }
};

QStringList &DialogItemTablePanel::names(void)
{
   return _names;
};

void DialogItemTablePanel::IndexChangedExpd(int index) 
{ 
   index = index; 

   //double value((double)index); 
   //wcscpy(_text, L"TRUE"); 
   //g_Parameter._SetValue(_itemIndex, value, _text, index); 

   if (index < _names.size() && _process == false) {
      emit tablePanelIndexChanged(index, 1); 
   } 

   //if (index > 1 || index < 0) {
   //   int i = 0;
   //}
   //emit tablePanelIndexChanged(index);
}

void DialogItemTablePanel::IndexChangedExpd(const QString &name)
{
   int index = _names.indexOf(name);
   index = index;
}

void DialogItemTablePanel::setTablePanelData(gsa::t::Table *tablePanel, int x_, int y_, int width_, int height_, int internalIndex_)
{
   _internalIndex = internalIndex_;

   //return; //__van__ 2019.03.05 

   //QString str(QString("INFO007 <<<>>> %1 this=%2 model=%3 thread=%4").arg(__FUNCTION__).arg((long long)this, 0, 16).arg((long long)_model, 0, 16).arg((long long)QThread::currentThread(), 0, 16));
   //qInfo(str.toStdString().c_str());

   QSize sizeParent = _parent->geometry().size();
   QSize sizeThis = this->geometry().size();
   QSize sizeTable = ui->tableView->geometry().size();

   //sizeParent.setHeight(sizeParent.height() / 8);
   //sizeParent.setWidth(sizeParent.width() / 4);
   //sizeParent.setHeight(sizeParent.height());
   //sizeParent.setWidth(sizeParent.width());
   sizeParent.setWidth(350);
   sizeParent.setHeight(120);

   //ui->tableView->setMinimumSize(QSize(500, 300));
   //this->setMinimumSize(QSize(500, 300));
   this->setMinimumSize(sizeParent);

   QFontMetrics fm(_font);
   //std::array<int, gsa::t::maxCell> columnWidthes;
   //int tableWidth;
   fm.xHeight();

   //for (int r = 0; r < tablePanel->Rows; r++) {
   //   for (int c = 0; c < tablePanel->Columns; c++) {
   //      QModelIndex index(_model->index(r, c));
   //      if (r == tablePanel->Rows - 1) {
   //         QSize size(128, 64);
   //         _model->setData(index, size, Qt::SizeHintRole);
   //      }
   //      else {
   //         QSize size(128, 32);
   //         _model->setData(index, size, Qt::SizeHintRole);
   //      }
   //   }
   //}

   //QStandardItem *item;
   int count( tablePanel->Columns * tablePanel->Rows );
   if (count > gsa::t::maxCell) count = gsa::t::maxCell;
   for (int i = 0; i < count; i++) {
      if (tablePanel->Cells[i].Default.Value != nullptr) 
      {
         QColor background_(tablePanel->Cells[i].Default.Background.Red, tablePanel->Cells[i].Default.Background.Green, tablePanel->Cells[i].Default.Background.Blue);
         QColor foreground_(tablePanel->Cells[i].Default.Foreground.Red, tablePanel->Cells[i].Default.Foreground.Green, tablePanel->Cells[i].Default.Foreground.Blue);

         if (tablePanel->Cells[i].Default.CellID != i) {
            int jjj = 0;
         }

         ////wchar_t *Value = tablePanel->Cells[i].Default.Value;
         ////QString str = QString::fromWCharArray(tablePanel->Cells[i].Default.Value);
         //QStandardItem *item = new QStandardItem(QString::fromWCharArray(tablePanel->Cells[i].Default.Value));
         ////QString str2 = item->text();
         //item->setBackground(background_);
         //item->setForeground(foreground_);

         if (tablePanel->Cells[i].RowSpan > 1 || tablePanel->Cells[i].ColumnSpan > 1) { 
            ui->tableView->setSpan(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column, tablePanel->Cells[i].RowSpan, tablePanel->Cells[i].ColumnSpan); 
         } 

         //_model->setItem(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column, new QStandardItem(QString::fromWCharArray(tablePanel->Cells[i].Default.Value)));
         //_model->setItem(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column, item);
         QModelIndex index(_model->index(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column));
         _model->setData(index, QString::fromWCharArray(tablePanel->Cells[i].Default.Value), Qt::DisplayRole);
         _model->setData(index, background_, Qt::BackgroundColorRole);
         _model->setData(index, foreground_, Qt::TextColorRole);
         _model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);

         QStringList values = QString::fromWCharArray(tablePanel->Cells[i].Default.Value).split("\n");
         if (values.size() > 1) {
            int maxLength(0);
            QString maxValue;
            for (auto item : values) {
               if (maxLength < item.length()) {
                  maxLength = item.length();
                  maxValue = item;
               }
            }
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
            int pixelsWide = fm.horizontalAdvance(maxValue);
#else
            int pixelsWide = fm.width(maxValue); //__van__
#endif
            //int xHeight = fm.xHeight();
            //int height = fm.height();
            int pixelSize = _font.pixelSize();
            //int pointSize = _font.pointSize();
            QSize size(pixelsWide, 0.8*pixelSize*values.size()); // 140);
            //QSize size(pixelsWide, 10); 
            _model->setData(index, size, Qt::SizeHintRole);
            int i = 0;
         }
         else {
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
            int pixelsWide = fm.horizontalAdvance(QString::fromWCharArray(tablePanel->Cells[i].Default.Value));
#else
            int pixelsWide = fm.width(QString::fromWCharArray(tablePanel->Cells[i].Default.Value)); //__van__
#endif
            //QSize size(pixelsWide, 40);
            int pixelSize = _font.pixelSize();
            QSize size(pixelsWide, pixelSize); // 140);
            //QSize size(pixelsWide, 10); 
            _model->setData(index, size, Qt::SizeHintRole);
         }

         //QString str2(QString("INFO007 %1 OK item[%2] = %3 ").arg(__FUNCTION__).arg(i).arg(item->text()));
         //qInfo(str2.toStdString().c_str());

         //if (tablePanel->Cells[i].RowSpan > 1 || tablePanel->Cells[i].ColumnSpan > 1) {
         //   ui->tableView->setSpan(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column, tablePanel->Cells[i].RowSpan, tablePanel->Cells[i].ColumnSpan);
         //}
      }
      else {
         int Row = tablePanel->Cells[i].Row;
         int Column = tablePanel->Cells[i].Column;
         int RowSpan = tablePanel->Cells[i].RowSpan;
         int ColumnSpan = tablePanel->Cells[i].ColumnSpan;
         int iii = 0;
      }
   }

   //x_ = 0;
   //y_ = 0;
   QRect rect(x_, y_, width_, height_);
   QPoint point(x_, y_);
   setGeometry(rect);
   move(point);

   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();
}

void DialogItemTablePanel::setTableData(gsa::t::TablePanelData *tablePanelData, gsa::t::Table *tablePanel)
{
   _tablePanel = tablePanel;
   _tablePanelData = tablePanelData;

   //return;

   //return; //__van__ 2019.03.05 

   //QString str1(QString("INFO007 %1 Length = %2").arg(__FUNCTION__).arg(tablePanelData->Length));
   //qInfo(str1.toStdString().c_str());

   //QString str0(QString("INFO007 <<<>>> %1 this=%2 model=%3 thread=%4").arg(__FUNCTION__).arg((long long)this, 0, 16).arg((long long)_model, 0, 16).arg((long long)QThread::currentThread(), 0, 16));
   //qInfo(str0.toStdString().c_str());

   //QStandardItem *item = new QStandardItem("123");
   //_model->setItem(0, 0, item);
   //QModelIndex index(0, 0);
   //QVariant value("123");
   //_model->setData(_model->index(0, 0), value, Qt::DisplayRole);

   //QString str11(QString("INFO007 %1 EXIT !!!!!!!! Length = %2").arg(__FUNCTION__).arg(tablePanelData->Length));
   //qInfo(str11.toStdString().c_str());

   //return;

   QFontMetrics fm(_font);
   QSize sizeParent = _parent->geometry().size();
   QSize sizeThis = this->geometry().size();
   QSize sizeTable = ui->tableView->geometry().size();

   //QString str(QString("INFO0077 <<<<<<>>>>>> %1 [%2] ").arg(__FUNCTION__).arg(__LINE__));
   //qInfo(str.toStdString().c_str());

   if (tablePanelData->Length <= gsa::t::maxTableValue)
   { 
      for (int i = 0; i < tablePanelData->Length; i++) 
      { 
         //QString str(QString("INFO007 %1 Value[%2] = %3 tablePanel=%4 ").arg(__FUNCTION__).arg(i).arg((long long)tablePanelData->Values[i].Value, 0, 16).arg((long long)tablePanel, 0, 16)); 
         //qInfo(str.toStdString().c_str()); 

         if (tablePanelData->Values[i].Value != nullptr) 
         { 
            //  tablePanelData->Values[i].CellID 
            if (tablePanelData->Values[i].CellID >= 0 && tablePanelData->Values[i].CellID < gsa::t::maxCell) 
            { 
               //QString str2(QString("INFO007 %1 Value = %2 (%3) ").arg(__FUNCTION__).arg((long long)tablePanelData->Values[i].Value, 0, 16).
               //   arg((long long)tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value, 0, 16));
               //qInfo(str2.toStdString().c_str());

               if (tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value == nullptr)
                  tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value = new wchar_t[1024];

               tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Background = tablePanelData->Values[i].Background;
               tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Foreground = tablePanelData->Values[i].Foreground;
               wcscpy(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value, tablePanelData->Values[i].Value);

               //QStandardItem *item = new QStandardItem(QString::fromWCharArray(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value));

               //QString str3(QString("INFO007 %1 Value[%2] = %3 (%4) / row=%5 column=%6 ").arg(__FUNCTION__).arg(i).arg(QString::fromWCharArray(tablePanelData->Values[i].Value)).
               //   arg(QString::fromWCharArray(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value)).
               //   arg(tablePanel->Cells[tablePanelData->Values[i].CellID].Row).arg(tablePanel->Cells[tablePanelData->Values[i].CellID].Column) );
               //qInfo(str3.toStdString().c_str());

               //_model->setItem(tablePanel->Cells[tablePanelData->Values[i].CellID].Row, tablePanel->Cells[tablePanelData->Values[i].CellID].Column, item);

               //QVariant value(QString::fromWCharArray(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value));

               int pixelsWide(0);
               if (tablePanelData->Values[i].CellID >= 0) 
               {
                  QColor background_(
                     tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Background.Red,
                     tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Background.Green,
                     tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Background.Blue);
                  QColor foreground_(
                     tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Foreground.Red,
                     tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Foreground.Green,
                     tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Foreground.Blue);

                  QModelIndex index(_model->index(tablePanel->Cells[tablePanelData->Values[i].CellID].Row, tablePanel->Cells[tablePanelData->Values[i].CellID].Column));
                  _model->setData(index, QString::fromWCharArray(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value), Qt::DisplayRole);
                  _model->setData(index, background_, Qt::BackgroundColorRole);
                  _model->setData(index, foreground_, Qt::TextColorRole);
                  _model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);

#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
                  pixelsWide = fm.horizontalAdvance(QString::fromWCharArray(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value));
#else
                  pixelsWide = fm.width(QString::fromWCharArray(tablePanel->Cells[tablePanelData->Values[i].CellID].Default.Value)); //__van__
#endif
                  int pixelSize = _font.pixelSize();
                  QSize size(pixelsWide, pixelSize); // 400); 
                  _model->setData(index, size, Qt::SizeHintRole); 
                  QSize size2(qvariant_cast<QSize>(_model->data(index, Qt::SizeHintRole))); 
                  int iii = 0; 
               }

               //_model->setData(index, foreground_, Qt::DecorationRole);

               //QColor background_(tablePanel->Cells[i].Default.Background.Red, tablePanel->Cells[i].Default.Background.Green, tablePanel->Cells[i].Default.Background.Blue);
               //QColor foreground_(tablePanel->Cells[i].Default.Foreground.Red, tablePanel->Cells[i].Default.Foreground.Green, tablePanel->Cells[i].Default.Foreground.Blue);
               //item->setBackground(background_);
               //item->setForeground(foreground_);

               ////_model->setItem(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column, new QStandardItem(QString::fromWCharArray(tablePanel->Cells[i].Default.Value)));
               ////_model->setItem(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column, item);
               //QModelIndex index(_model->index(tablePanel->Cells[i].Row, tablePanel->Cells[i].Column));
               //_model->setData(index, QString::fromWCharArray(tablePanel->Cells[i].Default.Value));
               //_model->setData(index, background_, Qt::BackgroundColorRole);

               //QString str(QString("INFO007 %1 OK !!!!! item[%2] = %3 ").arg(__FUNCTION__).arg(i).arg(item->text()));
               //qInfo(str.toStdString().c_str());
            }
         }
         else {
            //QString str(QString("INFO007 %1 ERROR Value = %2 ").arg(__FUNCTION__).arg((long long)tablePanelData->Values[i].Value, 0, 16));
            //qInfo(str.toStdString().c_str());
         }
      }
   }

   //int rowHeight(10);
   //int hight(std::numeric_limits<int>::max());
   //for (int r = 0; r < _rowCount; r++) {
   //   ui->tableView->setRowHeight(r, rowHeight);
   //   hight = ui->tableView->rowHeight(r);
   //   int i = 0;
   //}

   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();
}

