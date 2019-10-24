// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: van
//
// @file   dialogsystemsettings2.h
// Created: 12.04.2017
//

#ifndef DIALOGITEMCOMBOBOX_H
#define DIALOGITEMCOMBOBOX_H

#include <QtWidgets\QDialog>
#include <QtWidgets\QListView>
#include <QtWidgets\QListWidget>
#include <QtCore\QStringListModel>
#include <QtCore\QStringList>
#include <QTimer>
#include <QTime>

#include "gcore/core.h"

namespace Ui {
   class DialogItemComboBox;
}

class DialogItemComboBox : public QDialog, public gsa::t::IScreenItem
{
   Q_OBJECT

public:
   explicit DialogItemComboBox(QWidget *parent = 0, wchar_t* _caption = nullptr, wchar_t* _text=nullptr);
   ~DialogItemComboBox();

   //void fillCurrentMode(int current);
   //void fillCurrentMeas(int current);
   //void fillCurrentView(int current);

   void setType(QString type) override { _type = type; };
   QString &type(void) override { return _type; };

   void setIndex(int index) override { _index = index; }
   int index(void) override { return _index; }

   void setPosition(const QPoint &point) override { 
      _point = point; 
      move(point.x(), point.y());  
   };
   QPoint &position(void) override { return _point; };

   void setLocation(gsa::t::GuiLocation location) override { _location = location; };
   gsa::t::GuiLocation &location(void) override { return _location; };

   //setVisible already exist in Qt 
   void setGsaVisible(bool visible = true) override {
      _visible = visible; 
      if(_visible) show();  
      else hide();
   }
   bool gsaVisible(void) override { return _visible; ui; }

   void setName(QString name) override { _name = name; };
   QString &name(void) override { return _name; };

   void setNames(QStringList names) override;
   QStringList &names(void) override;

   void setItemIndex(int itemIndex) { _itemIndex = itemIndex; }
   int itemIndex(void) { return _itemIndex; }

   void keyPressEvent(QKeyEvent * event_) override;

public slots:
   //void clickedHelp(void);
   //void clickedExit(void);
   //void clickedCancel(void);
   //void clickedOk(void);

   //void rowChangedModes(int currentRow);
   //void rowChangedMeases(int currentRow);
   //void rowChangedViewes(int currentRow);

   void tablePanelIndexChangedExpd(int index, int flag);

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

   int _itemIndex;
   wchar_t _text[1024];

private:
   Ui::DialogItemComboBox *ui;
};

#endif // DIALOGITEMCOMBOBOX_H

