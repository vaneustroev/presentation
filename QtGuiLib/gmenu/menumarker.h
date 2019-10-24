// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef MENUMARKER_H
#define MENUMARKER_H

//#include <boost/container/map.hpp>
//#include <boost/container/vector.hpp>
#include <map>
#include <vector>

#include <QWidget>
#include <QStringListModel>
#include <QListView>

#include "gcore/core.h"
#include "gmenu/menu.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class MenuMarker;
}

namespace Menu
{

class MenuMarker : public IMenu
{
    Q_OBJECT

public:
    explicit MenuMarker(QWidget *parent = 0, Core::Controller *controller = 0);
    ~MenuMarker();

    void KeyPad(const TG::KeyPadParam &keyPadParam);

    void menuItemEdit(QString text);
    bool eventFilter(QObject* object, QEvent* event);
    void setParam(TG::MarkerParam &markerParam);
    void setAciveMarker(int index);
    void setAcivePeakSearch(void);
    void setMarkerFrequency(void);

    int current(void) {return _current;}

private slots:
    void onActivated(int index);
    void clickAllMarkersOff(void);
    void onClickedPeakSearch( bool checked = false );
    void onClickedPeakNext( bool checked = false );
    void onClickedPeakNextRight( bool checked = false );
    void onClickedPeakNextLeft( bool checked = false );
    void onClickedPeakMin( bool checked = false );
    void onClickedPeakPeak( bool checked = false );
    void onClickedPeakDelta( bool checked = false );
    void onClickedPeakMarker( bool checked = false );
    void onClickedPeakRefLevel( bool checked = false );

    void onClickedMarkerToCf( bool checked = false );
    void onClickedMarkerToCfStep( bool checked = false );
    void onClickedMarkerToStart( bool checked = false );
    void onClickedToStop( bool checked = false );
    void onClickedMarkerToRefLvl( bool checked = false );
    void onClickedMarkerDeltaToCf( bool checked = false );
    void onClickedMarkerDeltaToSpan( bool checked = false );

    void viewClicked( const QModelIndex & index );
    void viewActivated( const QModelIndex & index );

private:
    Ui::MenuMarker *ui;

    Core::Controller *_controller;

    TG::UnitTypes type;
    int index;
    double value;

    QPoint position;
    //boost::container::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;
    std::map<TG::UnitTypes, TG::KeyPadParam> keyPadParamList;

    int _current;
};

} // namespace Menu

#endif // MENUMARKER_H
