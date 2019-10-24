#pragma once

#include <QtWidgets\QTabWidget>
#include <QtWidgets\QTabBar>
#include <QtWidgets\QLabel>

#include "ui_GTabWidget.h"

#include "gcore/core.h"

class GTabBar : public QTabBar
{
public:
   GTabBar(QWidget* parent);

   void setTabText(int index, const QString &text, const gsa::t::ThemeFont &font_, const QColor &cfont_, const QColor &cground_);
   //void setMyText(int index, const QString &text);

};

class GTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    GTabWidget(QWidget *parent = Q_NULLPTR);
    ~GTabWidget();

    void setTabTextNew(int index, const QString &text, const gsa::t::ThemeFont &font_, const QColor &cfont_, const QColor &cground_, const QColor &ctab_);
    //void setMyText(int index, const QString &text);

private:
    Ui::GTabWidget ui;

    GTabBar* _gTabBar;
};

