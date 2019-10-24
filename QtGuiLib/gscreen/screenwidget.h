// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

// screenwidget.h

#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#define INDEX_ARRAY

#define GM_GL

#define USEQOPENGLWIDGET

#ifdef GM_GL
#else
#endif

#ifdef USEQOPENGLWIDGET
#else //USEQOPENGLWIDGET
#endif //USEQOPENGLWIDGET

#include <vector>

#ifdef GM_GL

#ifdef USEQOPENGLWIDGET
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLBuffer>
#else //USEQOPENGLWIDGET
#include <QGLWidget>
#endif //USEQOPENGLWIDGET

#include <QtGui/QMatrix4x4>
#include <QPainter>

#else

#include <QWidget>
//#include <QOpenGLWidget>

#endif

#include <QString>
#include <QStack>
#include <QPoint>
#include <QVector>
#include <QMap>
#include <QSharedPointer>
#include <QWeakPointer>

#include "gcore/core.h"
#include "gemulator/iemulatordigital.h"
//#include "gemulator/emulatordigital.h"
//#include "gemulator/emulatordigital2.h"
//#include "gcore/controller.h"

namespace Core {
class Controller;
class EmulatorDigital;
class EmulatorDigital2;
class EmulatorDigital3;
class GData;
} // namespace Core

//QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
//QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

namespace Screen {

class ScreenItem
{
public:
    ScreenItem(QString name=QString(""), QString newline=QString(""), QString text=QString(""), QPoint point=QPoint(0, 0)) {
        _name = name; _newline = newline; _text = text; _point = point;
    }
    ~ScreenItem() {;}

public:
    ScreenItem& operator=(const ScreenItem& screenItem);

    void setName(const QString &name) {_name = name;}
    const QString &name(void) {return _name;}

    void setNewLine(const QString &newline) {_newline = newline;}
    const QString &newLine(void) {return _newline;}

    void setText(const QString &text) {_text = text;}
    const QString &text(void) {return _text;}

    void setPoint(const QPoint &point) {_point = point;}
    const QPoint &point(void) {return _point;}

    void setValuePointer(float *pvalue) {_pvalue = pvalue;}
    float value(void) {if(_pvalue!=0) return *_pvalue; else return 0;}

private:
    QString _name;
    QString _newline;
    QString _text;
    QPoint _point;

    float *_pvalue;

};

} // namespace Screen

#ifdef GM_GL
#ifdef USEQOPENGLWIDGET
class ScreenWidget : public QOpenGLWidget, protected QOpenGLFunctions
#else //USEQOPENGLWIDGET
class ScreenWidget : public QGLWidget
#endif //USEQOPENGLWIDGET
#else //GM_GL
class ScreenWidget : public QWidget
//class ScreenWidget : public QOpenGLWidget
#endif //GM_GL
{
    Q_OBJECT

public:
    explicit ScreenWidget(QWidget *parent = 0);
    ~ScreenWidget();

public:
    void setController(Core::Controller *controller);
    Core::Controller *controller(void);

    void setScreenNames(const TG::Button &button, const TG::Button &parentbutton);
    //void setMin(const float &min) {_min = min;}
    //void setMax(const float &max) {_max = max;}
    void setUnitUp(const double &value); //{_unitMax = value;}
    void setUnitDown(const double &value); //{_unitMin = value;}
    void setUnitRange(const double &value); //{_unitRange = value;}
    double unitUp(void) {return _unitMax;}
    double unitDown(void) {return _unitMin;}
    double unitRange(void) {return _unitRange;}
    void setDataLog(bool dataLog = true) {
        _dataLog = dataLog;
    }
    void setDisplayLog(bool displayLog = true) {
        _displayLog = displayLog;
    }
    void setAmptYAxis(const TG::AmptYAxis &yAxis);
    QString yAxisUnitText(double &exponent);
    void fractionAndExponent(double &fraction, double &exponent);

    void redraw();
    void updateScreen(Core::IEmulatorDigital *iemulatorDigital);
    void stop();

    void redrawText();
    void renderText(QPainter &painter, const int &x, const int &y, const QString &text, const QFont &font_, const QColor &color_);
    bool checkOverlay(int current);

    //QMap<TG::ScreenItemType, ScreenItem> &screenItems() {return _screenItems;}

    void setActiveTrace(const int &activeTrace);
    void setTypeTrace(const TG::TypeTrace &typeTrace);
    const TG::TypeTrace &typeTrace(void);
    void fillTypeTraces(const std::vector<TG::TypeTrace> &typeTraces);
    void setInputAntenna(const bool &antenna);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void dataChanged(void);

public slots:
    void changeData();
    void slotScreenStateChanged(TG::ScreenStates screenStates);
    void slotAmptChanged(TG::AmptParam &amptParam);

    //// slots for xyz-rotation slider
    //void setXRotation(int angle);
    //void setYRotation(int angle);
    //void setZRotation(int angle);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    //void resizeEvent( QResizeEvent * event );
    void moveEvent( QMoveEvent * event );
    bool event(QEvent *event);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

    double unit2Screen(double value);
    double getValue(const int &i);

private:
    void drawFirst(QPainter &painter);
    void drawFirstAxis();
    void drawFirstAxisUnits(QPainter &painter);
    void drawFirstText(QPainter &painter);

    void drawFirstPieces(QPainter &painter);
    void drawFirstPieceOld(const int &i);
    void drawFirstPiece(const int &i);
    void drawSecondPieces(QPainter &painter);
    void drawSecondPieceOld(const int &i);
    void drawSecondPiece(const int &i);

    inline void drawFirstPieceTrace(const int &i, const TG::ItemColor &colortrace, const std::vector<double> *dataTrace, const std::vector<double> *dataTracePrev,
                                    double &x, double &y, double &yPrev);

    void drawSecondMarkers();
    void drawSecondDisplayLines();

    void drawInputText(QPainter &painter);
    void clearInputText(QPainter &painter);

    //inline void drawLine(const int &i);
    //inline void drawLinePrev(const int &i);

private:
    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
    QPoint _markerPos;

    Core::Controller *_controller;
    Core::EmulatorDigital *_emulatorDigital;
    Core::EmulatorDigital2 *_emulatorDigital2;
    Core::EmulatorDigital3 *_emulatorDigital3;
    //TG::Unit2Unit *_unit2Unit;
    int _internalEmulator;
    QString _firstMarkerValue;
    QString _secondMarkerValue;
    QMap<double, QString> _unitTexts;

    //Core::GData *_data;

    //boost::container::vector<float> *_dataArray2;
    //boost::container::vector<float> *_dataArrayPrev2;
    //boost::container::vector<int> *_pindexArray2;

    //std::vector<double> *_dataArray2;
    //std::vector<double> *_dataArrayPrev2;
    std::vector<double> *_dataArray1;
    std::vector<double> *_dataArrayPrev1;
    std::vector<double> *_dataTrace1;
    std::vector<double> *_dataTracePrev1;
    std::vector<double> *_dataTrace2;
    std::vector<double> *_dataTracePrev2;
    std::vector<double> *_dataTrace3;
    std::vector<double> *_dataTracePrev3;
    std::vector<double> *_dataTrace4;
    std::vector<double> *_dataTracePrev4;
    std::vector<double> *_dataTrace5;
    std::vector<double> *_dataTracePrev5;
    std::vector<double> *_dataTrace6;
    std::vector<double> *_dataTracePrev6;
    std::vector<int> *_pindexArray;
    std::vector<std::vector<double>*> _dataTraces;
    std::vector<std::vector<double>*> _dataTracesPrev;
    std::vector<TG::TypeTrace> _typeTraces;
    std::vector<TG::ItemColor> _colorTraces;
    std::vector<double> _yBegTraces;
    std::vector<double> _yBegPrevTraces;
    int _maxTraces;
    int _activeTrace;

    QWeakPointer<TG::Unit2Unit> _unit2Unit;
    //boost::container::map<TG::Ref2LevlUnit, boost::container::map<TG::Ref2LevlUnit, QSharedPointer<TG::Unit2Unit> > > _convertList;
    QMap<TG::Ref2LevlUnit, QMap<TG::Ref2LevlUnit, QSharedPointer<TG::Unit2Unit> > > _convertList;

    QStack<int> _bufferStack;
    QMutex mutex;
    //QVector<ScreenItem> _screenItems;
    QMap<TG::ScreenItemType, Screen::ScreenItem> _screenItems;
    //boost::container::map<int, TG::MarkerItem> *_pmarkerArray;
    TG::ItemColor _linecolor;
    TG::ItemColor _colortrace1;
    TG::ItemColor _colortrace2;
    TG::ItemColor _colortrace3;
    TG::ItemColor _colortrace4;
    TG::ItemColor _colortrace5;
    TG::ItemColor _colortrace6;
    TG::AmptYAxis _yAxis;

    int _xoffset;
    int _xstep;
    int _ystep;
    int _xxAxisOffset;
    int _yxAxisOffset;
    int _xAxisStep;
    int _yAxisStep;

    float _offset;
    float _min;
    float _max;
    double _unitMin;
    double _unitMax;
    double _unitRange;
    bool _dataLog;
    bool _displayLog;
    float _yLevelOffset;
    int _number;
    bool _antenna;
    int _width;
    int _height;
    int _side;
    bool _drawFull;
    bool _drawPart;
    bool _drawText;
    bool _drawMarkers;
    int _begin;
    int _end;
    int _current;
    int _total;
    int _currentMarker;
    double _xBeg;
    double _yBeg;
    double _yBegPrev;
    double _yBegTrace1;
    double _yBegPrevTrace1;
    double _yBegTrace2;
    double _yBegPrevTrace2;
    double _yBegTrace3;
    double _yBegPrevTrace3;
    float _prevData;
    //float _time;

    static int counter;

};

#endif // SCREENWIDGET_H

