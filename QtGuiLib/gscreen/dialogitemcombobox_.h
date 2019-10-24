// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: van
//
// @file   dialogsystemsettings2.h
// Created: 12.04.2017
//

#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QtWidgets\QDialog>
#include <QtWidgets\QListView>
#include <QtWidgets\QListWidget>
#include <QtCore\QStringListModel>
#include <QtCore\QStringList>
#include <QTimer>
#include <QTime>

namespace Ui {
   class DialogItemComboBox;
}

class DialogItemComboBox : public QDialog
{
   Q_OBJECT

public:
   explicit DialogItemComboBox(QWidget *parent = 0, wchar_t* _caption = nullptr, wchar_t* _text=nullptr);
   ~DialogItemComboBox();

   //void fillCurrentMode(int current);
   //void fillCurrentMeas(int current);
   //void fillCurrentView(int current);

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

private:
   //int _currentMode;
   //int _currentMeas;
   //int _currentView;
   //QTimer *_timer; 

private:
   Ui::DialogItemComboBox *ui;
};

#endif // DIALOGMESSAGE_H

