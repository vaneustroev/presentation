// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef KEYPADNEW2_H
#define KEYPADNEW2_H

#include <QtWidgets\QDialog>
#include <QtWidgets\QWidget>
#include <QVector>
#include <QTimer>

#include "unitfreq.h"
#include "unittime.h"

#include "gcore/core.h"
#include "gcore/controller.h"

namespace Core {
class Controller;
} // namespace Core

namespace Ui {
class KeyPadNew2;
}

namespace Pad {

class KeyPadNew2 : public QDialog
{
    Q_OBJECT

public:
    //explicit KeyPadNew2(QWidget *parent = 0, TG::KeyPadParam keyPadParam = TG::KeyPadParam() );
    //explicit KeyPadNew2(TG::KeyPadParam keyPadParam, QWidget *parent = 0 );
    //explicit KeyPadNew2(QWidget *parent = 0 );
    explicit KeyPadNew2(QWidget *parent = 0, TG::KeyPadParam keyPadParam = TG::KeyPadParam() );
    ~KeyPadNew2();

   bool eventFilter(QObject* object, QEvent* event);
   bool checkSimbol(QObject* object, QEvent* event);
   bool checkSimbol(QString &newText);

   void getSelection(TG::UnitTypes &type, int &index, double &value);
   void getSelection(TG::UnitTypes &type, int &index, QString &text);
   TG::KeyPadParam& params(void);
   void setParams(const TG::KeyPadParam& keyPadParam, int unitindex);
   void pressButton(QString &);
   void setText(QString &text);

   void doCancel(void);

   void wheelEvent(QWheelEvent * event);
   //void Double2String(QString &str, double value);

public slots:
   void doTextEdited(const QString &text);

   void slotButton0(void);
   void slotButton1(void);
   void slotButton2(void);
   void slotButton3(void);
   void slotButton4(void);
   void slotButton5(void);
   void slotButton6(void);
   void slotButton7(void);
   void slotButton8(void);
   void slotButton9(void);
   void slotButtonUp(void);
   void slotButtonDown(void);
   void slotButtonDot(void);
   void slotButtonMinus(void);
   void slotButtonDelete(void);

   void slotButtonUnit1(void);
   void slotButtonUnit2(void);
   void slotButtonUnit3(void);
   void slotButtonUnit4(void);
   void slotButtonUnit5(void);

   void slotReject(void);

   void slotClickedUnit(TG::UnitTypes type, int index);

   void resizeEvent ( QResizeEvent * event );

   void doReturnPressed(void);

private:
    Ui::KeyPadNew2 *ui;

private:
   TG::KeyPadParam _keyPadParam;
   int _unitindex;
   //TG::UnitTypes unitType;
   //QString name;
   bool _selectedText;
   QWidget *currentWidget;
   UnitFreq *unitFreq;
   UnitTime *unitTime;
   QVector<QPushButton *> _buttonUnits;
   QString _textBefore;

   TG::UnitTypes type;
   int index;

};

} // namespace Pad

#endif // KEYPADNEW2_H

