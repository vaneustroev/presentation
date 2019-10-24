#pragma once

// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: van
//
// @file   dialogsystemsettings2.h
// Created: 12.04.2017
//

//#ifndef DIALOGITEMCOMBOBOX_H
//#define DIALOGITEMCOMBOBOX_H

#include <QtCore\QStringListModel>
#include <QtCore\QStringList>
#include <QtSql\QSqlTableModel>
#include <QtWidgets\QDialog>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QListView>
#include <QtWidgets\QListWidget>
#include <QtWidgets\QStyledItemDelegate>

#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include <QTime>
#include <QVariant>

#include "gcore/core.h"

#include <array>

namespace Ui {
   class DialogItemTablePanel;
}

namespace Main {

   class MainWindow;
   extern const int _numberTrace;

}

//class VStyledItemDelegate : public QStyledItemDelegate
//{
//   Q_OBJECT
//
//public:
//   explicit VStyledItemDelegate(QObject *parent = nullptr);
//   ~VStyledItemDelegate();
//
//};

class PanelTableDelegate : public QStyledItemDelegate
{
   Q_OBJECT

public:
   PanelTableDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

   //void paint(QPainter *painter, const QStyleOptionViewItem &option,
   //   const QModelIndex &index) const override;
   //QSize sizeHint(const QStyleOptionViewItem &option,
   //   const QModelIndex &index) const override;
   //QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
   //   const QModelIndex &index) const override;
   //void setEditorData(QWidget *editor, const QModelIndex &index) const override;
   //void setModelData(QWidget *editor, QAbstractItemModel *model,
   //   const QModelIndex &index) const override;

private slots:
   //void commitAndCloseEditor();
};

class DialogItemTablePanel : public QDialog, public gsa::t::IScreenItem
{
   Q_OBJECT

public:
   explicit DialogItemTablePanel(QWidget *parent = nullptr, Main::MainWindow *appWidget = nullptr, QGridLayout *gridLayout = nullptr, gsa::t::Table *tablePanel = nullptr, wchar_t* _caption = nullptr, wchar_t* _text = nullptr);
   ~DialogItemTablePanel();

   //void fillCurrentMode(int current);
   //void fillCurrentMeas(int current);
   //void fillCurrentView(int current);

   void setType(QString type) override { _type = type; };
   QString &type(void) override { return _type; };

   void setIndex(int index) override { _index = index; }
   int index(void) override { return _index; }

   void setPosition(const QPoint &point) override { _point = point; move(point.x(), point.y()); };
   QPoint &position(void) override { return _point; };

   void setLocation(gsa::t::GuiLocation location) override { _location = location; };
   gsa::t::GuiLocation &location(void) override { return _location; };

   //setVisible already exist in Qt 
   void setGsaVisible(bool visible = true) override {
      _visible = visible;
      if (_visible) show();
      else hide();
   }
   bool gsaVisible(void) override { return _visible; }

   void setName(QString name) override { _name = name; };
   QString &name(void) override { return _name; };

   void setNames(QStringList names) override;
   QStringList &names(void) override;

   void setItemIndex(int itemIndex) { _itemIndex = itemIndex; }
   int itemIndex(void) { return _itemIndex; }

   void setTablePanelData(gsa::t::Table *tablePanel, int x_, int y_, int width_, int height_, int internalIndex_);
   gsa::t::Table *tablePanelData(void) { return _tablePanel; }

   void setTableData(gsa::t::TablePanelData *tablePanelData, gsa::t::Table *tablePanel);
   gsa::t::TablePanelData *tableData(void) { return _tablePanelData; }

   void setVParent(QWidget *parent) { _parent = parent; this->setParent(_parent); }
   QWidget *vparent(void) { return _parent; }

   void keyPressEvent(QKeyEvent * event_) override;

   void resizeEvent(QResizeEvent *event) override;
   void resizeEvent_Fixed(QResizeEvent *event);
   void resizeEvent_ResizeToContents(QResizeEvent *event);

   void fillColumnWidthes(const QFontMetrics &fm, std::array<int, gsa::t::maxCell> &columnWidthes, int &tableWidth);

   void setGridLayout(QGridLayout *gridLayout) { _gridLayout = gridLayout; }
   QGridLayout *gridLayout(void) { return _gridLayout; }

   void __test__(void);

signals:
   void tablePanelIndexChanged(int, int);

public slots:
   //void clickedHelp(void);
   //void clickedExit(void);
   //void clickedCancel(void);
   //void clickedOk(void);

   //void rowChangedModes(int currentRow);
   //void rowChangedMeases(int currentRow);
   //void rowChangedViewes(int currentRow);

private slots:
   //void updateTime();
   void IndexChangedExpd(int index);
   void IndexChangedExpd(const QString &);

private:
   //int _currentMode;
   //int _currentMeas;
   //int _currentView;
   //QTimer *_timer; 

   QString _type;
   int _index;
   QPoint _point;
   gsa::t::GuiLocation _location;
   bool _visible;
   QString _name;
   QStringList _names;
   gsa::t::Table *_tablePanel;
   gsa::t::TablePanelData *_tablePanelData;
   //QSqlTableModel *_model;
   QStandardItemModel *_model;
   int _internalIndex;
   bool _process;
   QWidget *_parent;
   QGridLayout *_gridLayout;
   QFont _font;
   Main::MainWindow *_appWidget;

   int _itemIndex;
   wchar_t _text[1024];
   int _rowCount;
   int _columnCount;
   int _emptyRowStretch;
   int _objectRowStretch;
   int _emptyColumnStretch;
   int _objectColumnStretch;

private:
   Ui::DialogItemTablePanel *ui;
};

//#endif // DIALOGITEMCOMBOBOX_H

