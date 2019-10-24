// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef CORE
#define CORE

#include <QtCore\QMap>
#include <QtCore\QSharedPointer>
#include <QtCore\QStringList>
#include <QtWidgets\QWidget>

//namespace Core {
//class Controller;
//} // namespace Core

#define NUMBEROFDEVICES 4

namespace gsa {

namespace core {

   class Controller;

} 

namespace t {

const int maxPoint(2048);
const int maxPad(32);
const int maxItem(64);
//const int maxTableValue(2); // (128); van 2019.01.11 
const int maxTableValue(256); // (128); van 2019.02.20 
//const int maxCell(6); // (32); van 2019.01.11 
//const int maxCell(4); // (32); van 2019.02.12 
const int maxCell(256); // (32); van 2019.02.20 

const int maxPanel(32);
const int maxView(32);
const int maxMeas(32);
const int maxMode(32);
const int maxThemeFont(16);
const int maxThemeItem(64);

enum DataType { Points = 0, Lines = 1, Polyline = 2, Marker = 3, Carret = 4, Disabled = 5, VerticalLine = 6, HorisontalLine = 7, SpanPower = 8 };
enum VectorType { MainVector = 0, SkipedVector = 1, PeriodVector = 2 };
enum class VerticalType { top = 0, bottom = 1, undef = 3 };
enum class HorizontalType { left = 0, middle = 1, right = 2, undef = 3};
enum class FontIndex {
   CurrentMeasurement = 0, //Current measurement selection area
   MeasurementScale, //Measurement scale
   PanelHeader, //Panel header
   QuickAccess, //Quick Access Area Tab
   DropDownMenu, //Drop - down menu items(list of songs)
   SelectedMenu, //Tabs of the selected menu(name of the subcomposition)
   ControlsSelectedTab, //Controls located in the selected tab
   ActiveMarker, //Displaying the active marker in the graphics area
   InactiveMarker, //Displaying inactive marker in the graphics area
   ActiveMarkerTable, //Displaying the active marker in the marker table
   InactiveMarkerTable, //Displaying the active marker in the marker table
   ControlDropDownPanel, //Control drop-down list in the panel(additional data area)
   PanelControl, //Control located in the panel (additional data area)
   Default //Default
};

enum class ColorIndex {
   DisplayArea = 0, //Display area background 
   GraphicPanelScale, //Graphic panel scale 
   TableBorders, //Borders of the table display 
   CurrentMeasurement, //Current measurement selection area 
   TabSelectionArea, //Tab in the general dimension selection area 
   QuickAccess, //Tabs in the quick access area 
   DropDownMenu, //Drop down menu 
   UnifyingFrame, //Unifying frame in the menu area 
   UnifyingFrameBorder, //Border of the unifying frame in the menu area 
   ControlDropDownMenu, //Control drop-down list in the menu area 
   ControlDropDownPanel, //Control drop-down list in the panel(additional data area) 
   PanelControl, //Control in the panel(additional data area) 
   SelectedLine, //Selected line in the expanded control drop-down list 
   UnselectedString, //Unselected string in expanded control drop-down list 
   ElementsBorders, //Borders of the elements of the drop-down menu 
   CompositionMenu, //Menu area(composition) 
   ControlMenu, //Control in the menu area(composition) 
   Default //Default 
};

enum class SizeIndex {
   MenuItem, //Menu item in the drop-down menu 
   Button, //Control button in the menu area 
   RadioButton, //Control radio button in the menu area 
   Checkbox, //Control checkbox in the menu area 
   DropDownList, //Control drop-down list in the menu area 
   Switch, //Control item is a switch in the menu area 
   NumericValue, //Control is a numeric value in the menu area 
   Panel //Control located in the panel(additional data area) 
};

enum class IndentIndex {
   UnifyingFrame, //Unifying frame of the menu area from the size of the control 
   MenuArea, //Area of ​​the menu, from the size of the unifying frame located in it 
   TableBorders //Borders of the table display from the text 
};

enum class ViewConfiguration { Solo, DVertical, DHorizontal, TLeftVertical, TRightVertical, TTopHorizontal, TBottomHorizontal, Quadro };
enum class PanelPosition { Solo, Left, Right, Top, Bottom, LeftTop, LeftBottom, RightTop, RightBottom, Disabled };
enum class PanelType { Graph, Table, Disabled };

struct ColourStruct
{
   unsigned char Red, Green, Blue;
};

struct KeyInfo
{
   int keyCode;
   int nativeModifiers;

   bool operator<(KeyInfo const& right) const
   {
      //return (strcmp(m_or, right.m_or) < 0);
      return keyCode < right.keyCode;
   }
};

struct ItemInfo
{
   QString type;
   int item;
   int pageIndex; 
   int itemtype;

   //int keyCode;
   //int nativeModifiers;

   //bool operator<(KeyInfo const& right) const
   //{
   //   //return (strcmp(m_or, right.m_or) < 0);
   //   return keyCode < right.keyCode;
   //}
};

struct TableValue
{
   int TableID;
   int CellID;
   wchar_t *Value;
   ColourStruct Background;
   ColourStruct Foreground;
};

struct TableCell
{
   int Row;
   int Column;
   int RowSpan;
   int ColumnSpan;
   TableValue Default;
};

struct Table
{
   int ID;
   int Rows;
   int Columns;
   TableCell Cells[maxCell];
};

struct TablePanelData
{
   TableValue Values[maxTableValue];
   int Length;
};

struct XYValue
{
   double XValue;
   double YValue;
   ColourStruct Colour;
};

struct CurrentData
{
   DataType Type;
   int Length;
   XYValue Values[maxPoint];
   int* _hMutex;
};

struct ThemeFont
{
   int type;
   wchar_t *description;
   wchar_t *family;
   int size;
   wchar_t *style;
   wchar_t *color;

};

struct ThemeItem
{
   int type;
   wchar_t *description;
   wchar_t *value;
};

struct Theme
{
   ThemeFont themeFonts[maxThemeFont];
   ThemeItem themeItems[maxThemeItem];
};

struct GuiList
{
   double value;
   wchar_t *name;
   int index;
   int length;
   int capacity;
   wchar_t *names[32];
};

struct GuiLocation
{
   int x;
   int y;
   VerticalType vertical;
   HorizontalType horizontal;
   //int vertical; //0 - top, 1 - bottom 
   //int horizontal; //0 - left, 1 - middle, 2 - right 
};

struct GuiItem
{
   double value;
   int itemIndex;
   int currentIndex;
   int IsEnabled;
   int IsVisible;
   int keyCode;
   int nativeModifiers;
   int itemtype;
   int length;
   int capacity;
   wchar_t *unit;
   wchar_t *units[32];
   wchar_t *name;
   wchar_t *type;
   GuiList guilist;
   GuiLocation guiLocation;
};

struct GuiPad
{
   int keyCode;
   int nativeModifiers;
   int length;
   int capacity;
   wchar_t *name;
   wchar_t *tab;
   GuiItem items[maxItem];
};

struct GuiScreenPad
{
   int keyCode;
   int nativeModifiers;
   int length;
   int capacity;
   wchar_t *name;
   wchar_t *tab;
   GuiItem items[maxItem];
};

struct CurrentMenu
{
   int length;
   int lengthScreen;
   int capacity;
   int indexMode;
   int indexMeas;
   int indexView;
   wchar_t *nameMode;
   wchar_t *nameMeas;
   wchar_t *nameView;
   GuiPad pads[maxPad];
   GuiScreenPad screenPads[maxPad];
};

struct GuiPanel
{
   int position;
   int type;
   wchar_t *name;
};

struct GuiView
{
   int length;
   int capacity;
   int type;
   wchar_t *name;
   GuiPanel guiPanels[maxPanel];
};

struct GuiMeas
{
   int length;
   int capacity;
   wchar_t *name;
   GuiView guiViewes[maxView];
   void *measObject;
};

struct GuiMode
{
   int length;
   int capacity;
   wchar_t *name;
   //std::unique_ptr<wchar_t[]> name;
   GuiMeas guiMeases[maxMeas];
};

struct ModeMeasView
{
   int length;
   int capacity;
   wchar_t *name;
   //std::unique_ptr<wchar_t[]> name;
   GuiMode guiModes[maxMode];
};

class IScreenItem
{
public:
   IScreenItem() = default;
   virtual ~IScreenItem() = 0 { ; };

   virtual void setType(QString type) = 0;
   virtual QString &type(void) = 0;

   virtual void setIndex(int index) = 0;
   virtual int index(void) = 0;

   virtual void setPosition(const QPoint &point) = 0;
   virtual QPoint &position(void) = 0;

   virtual void setLocation(gsa::t::GuiLocation location) = 0;
   virtual gsa::t::GuiLocation &location(void) = 0;

   //setVisible already exist in Qt 
   virtual void setGsaVisible(bool visible) = 0;
   virtual bool gsaVisible(void) = 0;

   virtual void setName(QString name) = 0;
   virtual QString &name(void) = 0;

   virtual void setNames(QStringList names) = 0;
   virtual QStringList &names(void) = 0;

};

} // namespace gsa::t

} // namespace gsa

namespace TG
{

class Unit2Unit
{
public:
   Unit2Unit(void){;}
   virtual ~Unit2Unit(void){;}

   virtual double convert(const double &, const bool &, const double &, const double &) = 0;
   virtual void setStart(const double &start) = 0;
   virtual void setStop(const double &stop) = 0;

protected:
    //Unit2Unit(void){;}

};

class dBm2dB : public TG::Unit2Unit
{
public:
    dBm2dB(gsa::core::Controller *controller = 0)
        : _controller(controller)
        , _start(0.0)
        , _stop(0.0)
    {
        int i(0);
        Q_UNUSED(i)
    }
    ~dBm2dB(void){;}

    double convert(const double &value, const bool &antenna, const double &index, const double &number);
    void setStart(const double &start) {_start = start;}
    void setStop(const double &stop) {_stop = stop;}

private:
    gsa::core::Controller *_controller;
    double _start;
    double _stop;
};

enum DeviceType : unsigned int {
    devtypeGamma,
    devtypeFsl3,
    devtypeFsh4,
    devtypeCxa,
};

enum MenuType : unsigned int {
    menuOld,
    menuNew,
};

enum MenuActive : unsigned int {
    menuMarker,
    menuUndef,
};

enum Button : unsigned int {
    buttonUndef,
    buttonFreq,
    buttonSpan,
    buttonAmpt,
    buttonBW,
    buttonSweep,
    buttonTrace,
    buttonMarker,
    buttonMarkerMain,
    buttonMarkerPeak,
    buttonSave,
    buttonPrint,
    buttonMeas,
    buttonRestart,
    //buttonKeyPad,
    button00,
    button01,
    button02,
    button03,
    button04,
    button05,
    button06,
    button07,
};

enum IndexMenu : unsigned int {
    indexAmpt,
    indexBw,
    indexDisplay,
    indexFreq,
    indexInput,
    indexOutput,
    indexMarker,
    indexMeasSetup,
    indexPeakSearch,
    indexSweep,
    indexTrace,
    indexTrigger,
    indexUserMenu,
};

enum PeakSearchType : unsigned int {
    peakSearchUndef,
    peakSearchNext,
    peakSearchNextRight,
    peakSearchNextLeft,
    peakSearchMin,
    peakSearchPeakPeak,
    peakSearchNextDelta,
    peakSearchNextMarker,
    peakSearchNextRefLevel,
};

enum MarkerToFreqType : unsigned int {
    markerToCenter,
    markerToStep,
    markerToStart,
    markerToStop,
    markerToRefLvl,
    markerToSpan,
};

enum ScreenStates : unsigned int {
    stateUndef,
    stateFreqCenter,
    stateFreqStart,
};

enum SweepStates : unsigned int {
    sweepContinuous,
    sweepSingle,
};

//enum AmptModes : unsigned int {
//    amptModeLog,
//    amptModeLin,
//};

enum TypeTrace : unsigned int {
    traceClear,
    traceAver,
    traceMax,
    traceMin,
    traceView,
    traceBlank,
	traceDouble,
};

enum TypeDetector : unsigned int {
    detectorApeak,
    detectorNegative,
    detectorPositive,
    detectorSample,
    detectorRms,
    //detectorAuto,
    //detectorMan,
    //detectorAutoAll,
};

enum TypeDetectorSelect : unsigned int {
    detectorAuto,
    detectorMan,
    //detectorAutoAll,
};

enum AmptSourceModes : unsigned int {
    amptSourcedB,
    amptSourceVolt,
};

enum AmptYAxis : unsigned int {
    yAxisdBm,
    yAxisdBmV,
    yAxisWatt,
    yAxisVolt,
    yAxisUndef,
};

enum FreqUnits : unsigned int {
    fr_Undef,
    fr_GHz,
    fr_MHz,
    fr_kHz,
    fr_Hz,
};

enum Units : unsigned int {
    unitHz,
    unitSec,
};

enum Exps : unsigned int {
    exp_G,
    exp_M,
    exp_k,
    exp_,
    exp_m,
    exp_mk,
    exp_n,
    exp_p,
    exp_f,
    exp_a,
    exp_z,
    exp_y,
};

enum SelectFreq : unsigned int {
    unselFreq,
    selFreqCenter,
    selFreqSpan,
    selFreqStart,
    selFreqStop,
    selFreqStep,
};

enum SelectBw : unsigned int {
    unselBw,
    selResBw,
    selVideoBw,
};

enum AmptUnits : unsigned int {
    ampt_Undef,
    ampt_dB,
};

enum RelativeUnits : unsigned int {
    relativeWatt,
    relativeVolt,
};

enum RefLevlUnit : unsigned int {
    ref_Undef,
    ref_dBm,
    ref_dBmV,
    ref_Watt,
    ref_Volt,
    //ref_ndBm,
    //ref_m,
    //ref_mk,
    //ref_n,
};

enum SweepUnits : unsigned int {
    sw_Undef,
    sw_ks,
    sw_s,
    sw_ms,
    sw_mks,
    sw_ns,
};

enum Ref2LevlUnit : unsigned int {
    ref2_Undef,
    ref2_dB,
    ref2_dBm,
    ref2_dBmV,
    ref2_dBmkV,
    ref2_dBmkA,
    ref2_Watts,
    ref2_Volts,
    ref2_Amps,
};

enum Types : unsigned int {
    typeUndef,
    typeUnit,
    typeSweep,
    typeFreqCenter,
    typeFreqSpan,
    typeFreqStep,
    typeFreqStart,
    typeFreqStop,
    typeFreqOffset,
    typeResBw,
    typeVideoBw,
    typeVbw3dbRbw,
    typeSpan3dbRbw,
    typeRbwFilterBw,
    typeRefLevl,
    typeRefLevlOffset,
    typeDisplayLine,
    typeInputPreamp,
    typeIpAddress,
    typeScaleDef,
    typeMarker,
    typeMarkerPeak,
    typeToMarker,
    typeReturn,
};

enum Types2 : unsigned int {
    type2Undef,
    type2Sweep,
    type2Freq,
    type2BW,
    type2Ref,
    type2Marker,
    type2Ampt,
};

enum UnitTypes : unsigned int {
    unitUndef,
    unitFreq,
    unitTime,
    unitAmpt,
    unitBw,
    unitLine,
    unitInput,
    unitIpAddress,
};

enum Moving : unsigned int {
    lvlUp,
    lvlCurrent,
    lvlDown,
};

enum ButtonType : unsigned int {
    btnUnselect,
    btnGrouped,
    btnSelected,
};

enum MarkerType : unsigned int {
    mrkStandart,
    mrkDelta,
    mrkBand,
    mrkSpan,
    mrkFixed,
    mrkOff,
};

enum Data : unsigned int {
    data_ref,
    data_atten,
    data_log,
    data_start,
    data_stop,
    data_center,
    data_span,
    data_res,
    data_wbm,
    data_sweep,
};

enum ScreenItemType : unsigned int {
    screen_Top0Left,
    screen_Top0Center,
    //screen_LeftTop0,
    //screen_LeftCenter,
    screen_Bottom0Left,
    screen_Bottom0Right,
    screen_Bottom1Left,
    screen_Bottom1Center,
    screen_Bottom1Right,

};

struct MarkerItem
{
    TG::MarkerType type2;
    bool changed;
    bool drawn1;
    bool drawn2;
    double v1;
    double v2;
    double x1;
    double x2;
    double x1prev;
    double x2prev;
    double r;
    double g;
    double b;

};

struct ItemColor
{
    float r;
    float g;
    float b;
};

struct DisplayLine
{
    bool changed;
    bool drawn1;
    double _unit;
    //double y1;
    double _unitPrev;
    //double y1prev;
    double r;
    double g;
    double b;
};

class FreqParam : public QObject
{
public:
    FreqParam(void){;}
    ~FreqParam(void){;}

    void setCenter(double center) {_center = center;}
    double center(void) {return _center;}
    void setSpan(double span) {_span = span;}
    double span(void) {return _span;}
    void setStart(double start) {_start = start;}
    double start(void) {return _start;}
    void setStop(double stop) {_stop = stop;}
    double stop(void) {return _stop;}
    void setStep(double step) {_step = step;}
    double step(void) {return _step;}
    void setOffset(double offset) {_offset = offset;}
    double offset(void) {return _offset;}
    void setFullSpan(double fullSpan) {_fullSpan = fullSpan;}
    double fullSpan(void) {return _fullSpan;}
    void setZeroSpan(double zeroSpan) {_zeroSpan = zeroSpan;}
    double zeroSpan(void) {return _zeroSpan;}

    void setUnitFreq(TG::Units unitFreq) {_unitFreq = unitFreq;}
    TG::Units unitFreq(void) {return _unitFreq;}
    void setExpFreq(TG::Exps expFreq) {_expFreq = expFreq;}
    TG::Exps expFreq(void) {return _expFreq;}
    void setSelectFreq(TG::SelectFreq selectFreq) {_selectFreq = selectFreq;}
    TG::SelectFreq selectFreq(void) {return _selectFreq;}
    void setUnitText(QString unitText) {_unitText = unitText;}
    QString unitText(void) {return _unitText;}

    enum {
        _ECENTER = 0x01,
        _EFULLSPAN = 0x02,
        _ESPAN = 0x02,
        _ESTART = 0x04,
        _ESTOP = 0x08,
        _ESTEP = 0x10,
        _EOFFSET = 0x20,
    };
    unsigned int _flags;

    double _center;
    double _span;
    double _start;
    double _stop;
    double _step;
    double _offset;
    bool _fullSpan;
    bool _zeroSpan;

    TG::Units _unitFreq;
    TG::Exps _expFreq;
    TG::SelectFreq _selectFreq;
    QString _unitText;

};

class AmptParam : public QObject
{
public:
    AmptParam(void){;}
    ~AmptParam(void){;}

    enum {
        _ELOG = 0x01,
        _EYAXIS = 0x02,
        _ELEVEL = 0x04,
    };
    unsigned int _flags;

    //float relativeValueHard;
    //TG::RelativeUnits relativeUnitHard;
    //bool dataLog;
    TG::AmptYAxis yAxis;
    bool displayLog;
    double relativeValue;
    TG::RelativeUnits relativeUnit;
    double scaleDev;
    QString scaleDevUnitText;
    double refLevl;
    double refLevlOffset;
    TG::RefLevlUnit refLevlUnit;
    QString unitText;

};

class BwParam : public QObject
{
public:
    BwParam(void){;}
    ~BwParam(void){;}

    enum {
        _ERESBW = 0x01,
        _EVIDEOBW = 0x02,
        _EVBW3DBRBW = 0x04,
        _ESPAN3DBRBW = 0x08,
        _ERBWFILTERBW = 0x10,
        _EAUTORBW = 0x20,
        _EAUTOVBW = 0x40,
    };
    unsigned int _flags;

    double resBw;
    double videoBw;
    double vbw3dbRbw;
    double span3dbRbw;
    double rbwFilterBw;
    bool _autoRbw;
    bool _autoVbw;
    TG::FreqUnits unit;
    TG::AmptUnits unitAmpt;
    TG::SelectBw selectBw;
    QString unitText;
    QString unitAmptText;

};

class DetectorParam : public QObject
{
public:
    DetectorParam(void){;}
    ~DetectorParam(void){;}

    unsigned int _flags;

    int _activeTrace;
    std::vector<TG::TypeDetector> _typeDetectors;
    std::vector<bool> _autoDetectors;
};

class SweepParam : public QObject
{
public:
    SweepParam(void){;}
    ~SweepParam(void){;}

    enum {
        _ETIME = 0x01,
        _EAUTO = 0x02,
        _EPOINTS = 0x04,
    };
    unsigned int _flags;

    double _time;
    int _points;
    bool _auto;
    TG::SweepUnits _unit;
    QString _unitText;

};

class InputParam : public QObject
{
public:
    InputParam(void){;}
    ~InputParam(void){;}

    enum {
        _EEXTERNALPREAMP = 0x01,
    };
    unsigned int _flags;

    double externalPreamp;
    //double refLevl;
    //double refLevlOffset;
    //TG::RefLevlUnit refLevlUnit;
    //QString unit;

};

class OutputParam : public QObject
{
public:
    OutputParam(void){;}
    ~OutputParam(void){;}

    unsigned int _flags;

    double refLevl;
    double refLevlOffset;
    TG::RefLevlUnit refLevlUnit;
    QString unit;

};

//class DisplayParam : public QObject
//{
//public:
//    DisplayParam(void){;}
//    ~DisplayParam(void){;}

//    bool _on;
//    double _line;
//    //TG::RefLevlUnit refLevlUnit;
//    //QString unit;

//};

class MarkerParam : public QObject
{
public:
    MarkerParam(void){;}
    ~MarkerParam(void){;}

    unsigned int _flags;

    std::vector<bool> _states;
    std::vector<double> _markers;
    //double refLevl;
    //double refLevlOffset;
    //TG::RefLevlUnit refLevlUnit;
    //QString unit;

};

class TraceParam : public QObject
{
public:
    TraceParam(void){;}
    ~TraceParam(void){;}

    enum {
        _EAPE = 0x01,
        _ENEG = 0x02,
        _EPOS = 0x04,
        _ESAM = 0x08,
        _ERMS = 0x10,
    };
    unsigned int _flags;

};

class MeasSetupParam : public QObject
{
public:
    MeasSetupParam(void){;}
    ~MeasSetupParam(void){;}

    unsigned int _flags;

    double refLevl;
    double refLevlOffset;
    TG::RefLevlUnit refLevlUnit;
    QString unit;

};

class PeakSearchParam : public QObject
{
public:
    PeakSearchParam(void){;}
    ~PeakSearchParam(void){;}

    unsigned int _flags;

    double refLevl;
    double refLevlOffset;
    TG::RefLevlUnit refLevlUnit;
    QString unit;

};

class TriggerParam : public QObject
{
public:
    TriggerParam(void){;}
    ~TriggerParam(void){;}

    unsigned int _flags;

    double refLevl;
    double refLevlOffset;
    TG::RefLevlUnit refLevlUnit;
    QString unit;

};

class UserMenuParam : public QObject
{
public:
    UserMenuParam(void){;}
    ~UserMenuParam(void){;}

    unsigned int _flags;

    double refLevl;
    double refLevlOffset;
    TG::RefLevlUnit refLevlUnit;
    QString unit;

};

class KeyPadParam : public QObject
{
public:
    KeyPadParam(QObject *parent=nullptr, QString name=QString(""), TG::UnitTypes=TG::unitUndef, int value=0);
    KeyPadParam(const TG::KeyPadParam&);
    //KeyPadParam(KeyPadParam);
    ~KeyPadParam(void){;}

    TG::KeyPadParam& operator=(const TG::KeyPadParam&);

//private:
public:
    QString _name;
    TG::UnitTypes _unitType;
    double _value;
    QString _text;
    TG::Types _fieldType;
    QStringList _buttonNames;

};

} // namespace TG

namespace Core {

class SAItem
{
public:
    SAItem(QSharedPointer<SAItem> parent=QSharedPointer<SAItem>(0), TG::Button button=TG::buttonUndef, std::string name="", TG::Types type=TG::typeUndef)
        : _parent(parent)
        //, _pThis(this)
        , _button(button)
        , _activeButton(TG::buttonUndef)
        , _type(type)
        , _name(name)
    {
        //_pThis = QSharedPointer<SAItem>(this);
        //_pThis = QWeakPointer<SAItem>::assign(this);
    }
    ~SAItem() {
        int i = 0;
        i = 1;
        Q_UNUSED(i)

        //_pThis.clear();
        //_pThis.reset(this);
    }

    //QSharedPointer<SAItem> &setParent(QSharedPointer<SAItem> parent) {_parent = parent; return _pThis;}
    void setParent(QSharedPointer<SAItem> parent) {_parent = parent; }
    QSharedPointer<SAItem> &parent() {return _parent;}

    //QSharedPointer<SAItem> &setButton(TG::Button &button) {_button = button; return _pThis;}
    void setButton(TG::Button &button) {_button = button; }
    TG::Button &button(void) {return _button;}

    //QSharedPointer<SAItem> &setActiveButton(TG::Button activebutton) {_activeButton = activebutton; return _pThis;}
    void setActiveButton(TG::Button activebutton) {_activeButton = activebutton; }
    TG::Button &activeButton(void) {return _activeButton;}

    //QSharedPointer<SAItem> &setType(TG::Types &type) {_type=type; return _pThis;}
    void setType(TG::Types &type) {_type=type; }
    TG::Types &type(void) {return _type;}

    //QSharedPointer<SAItem> &setName(const std::string &name) {_name=name; return _pThis;}
    void setName(const std::string &name) {_name=name; }
    const std::string &name(void) {return _name;}

    //QSharedPointer<SAItem> &setText(const std::string &text) {_text=text; return _pThis;}
    void setText(const std::string &text) {_text=text; }
    const std::string &text(void) {return _text;}

    QSharedPointer<SAItem> &addChild(QSharedPointer<SAItem> child) {_children[child->button()] = child; return _children[child->button()];}
    QSharedPointer<SAItem> &child(TG::Button button) {return _children[button];}
    //void setChildren(boost::container::map<TG::Button, QSharedPointer<SAItem> > childern) {_children = childern;}
    //boost::container::map<TG::Button, QSharedPointer<SAItem> > &children() {return _children;}
    QMap<TG::Button, QSharedPointer<SAItem> > &children(void) {return _children;}
    void createChildren(QSharedPointer<SAItem> &parent, QMap<TG::Button, QSharedPointer<SAItem> > &childern);

private:
    QSharedPointer<SAItem> _parent;
    //QSharedPointer<SAItem> _pThis;
    QWeakPointer<SAItem> _pThis;
    TG::Button _button;
    TG::Button _activeButton;
    TG::Types _type;
    std::string _name;
    std::string _text;
    //boost::container::map<TG::Button, QSharedPointer<SAItem> > _children;
    QMap<TG::Button, QSharedPointer<SAItem> > _children;
};

} // namespace Core

#include <QtCore\QScopedPointer>
#include <QtCore\QMutex>
#include <QtCore\QMutexLocker>

//namespace Gm {
namespace Core {

namespace {
/// Функтор создания экземляра по умолчанию
template<typename T>
struct DefaultCreator
{
    T* operator()();
};
} // namespace

/**
 * Шаблон проектирования Singleton
 */
template <typename T, typename Creator=DefaultCreator<T> >
class Singleton
{
public:
    /**
     * @brief Возвращает экземпляр класса одиночки
     *
     * При первом вызове осуществляет создание объекта
     */
    static T& instance();
private:
    static T* createNew() { return new T(); }
    static QScopedPointer<T> _d;
    static QMutex _mutex;

    friend struct DefaultCreator<T>;
};

template<typename T>
T* DefaultCreator<T>::operator()()
{
    return Singleton<T, DefaultCreator<T> >::createNew();
}

template <typename T, typename Creator>
T& Singleton<T, Creator>::instance()
{
    if (_d.isNull()) {
        QMutexLocker locker(&_mutex);
        if (_d.isNull()) {
            Creator f;
            _d.reset(f());
        }
    }
    return *_d;
}

template <typename T, typename Creator>
QMutex Singleton<T, Creator>::_mutex;

template <typename T, typename Creator>
QScopedPointer<T> Singleton<T, Creator>::_d;

} // namespace Core
//} // namespace Gm

//namespace T
//{

//class Unit2Unit
//{
//public:
//    virtual ~Unit2Unit(void){;}

//    virtual double convert(const double &, const bool &, const double &, const double &) = 0;
//    virtual void setStart(const double &start) = 0;
//    virtual void setStop(const double &stop) = 0;

//protected:
//    Unit2Unit(void){;}

//};

//class dBm2dB : public Unit2Unit
//{
//public:
//    dBm2dB(Core::Controller *controller = 0)
//        : _controller(controller)
//        , _start(0.0)
//        , _stop(0.0)
//    {
//        int i(0);
//        Q_UNUSED(i)
//    }
//    ~dBm2dB(void){;}

//    double convert(const double &value, const bool &antenna, const double &index, const double &number);
//    void setStart(const double &start) {_start = start;}
//    void setStop(const double &stop) {_stop = stop;}

//private:
//    Core::Controller *_controller;
//    double _start;
//    double _stop;
//};

//} // namespace T

#endif // CORE

