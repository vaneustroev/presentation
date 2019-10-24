// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#include <QResizeEvent>

#include "gkeypad/keypadnew2.h"

#include "ui_keypadnew2.h"

namespace Pad {

KeyPadNew2::KeyPadNew2(QWidget *parent, TG::KeyPadParam keyPadParam )
   : QDialog(parent)
   , ui(new Ui::KeyPadNew2)
   , _keyPadParam(keyPadParam)
   , _unitindex(0)
   , _selectedText(false)
   , currentWidget(nullptr)
   , unitFreq(nullptr)
   , unitTime(nullptr)
   , index(0)
{
   ui->setupUi(this);

   setParams(keyPadParam, _unitindex);

   //ui->labelName->setText(keyPadParam.name);
   //ui->lineEdit->setText(QString("%1").arg(keyPadParam.value));

   //keyPadNew2->setText("The document has been modified.");
   //keyPadNew2->setInformativeText("Do you want to save your changes?");
   //keyPadNew2->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
   //keyPadNew2->setDefaultButton(QMessageBox::Save);

   //unitFreq = new UnitFreq(this);
   //unitTime = new UnitTime(this);

   //ui->stackedUnit->addWidget(unitFreq);
   //ui->stackedUnit->addWidget(unitTime);

   //ui->stackedUnit->setCurrentIndex(index);

   //if(keyPadParam.unitType == TG::unitFreq) {
   //    ui->ButtonUnit1->setText("GHz");
   //    ui->ButtonUnit2->setText("MHz");
   //    ui->ButtonUnit3->setText("kHz");
   //    ui->ButtonUnit4->setText("Hz");
   //    ui->ButtonUnit5->setText("");
   //    ui->ButtonUnit5->setVisible(false);
   //} else if(keyPadParam.unitType == TG::unitTime) {
   //    ui->ButtonUnit1->setText("ks");
   //    ui->ButtonUnit2->setText("s");
   //    ui->ButtonUnit3->setText("ms");
   //    ui->ButtonUnit4->setText("mks");
   //    ui->ButtonUnit5->setText("ns");
   //} else if(keyPadParam.unitType == TG::unitAmpt) {
   //    ui->ButtonUnit1->setText("dBmV");
   //    ui->ButtonUnit2->setText("dBmkV");
   //    ui->ButtonUnit3->setText("Volt");
   //    ui->ButtonUnit4->setText("Watt");
   //    ui->ButtonUnit5->setText("");
   //    ui->ButtonUnit5->setVisible(false);
   //} else if(keyPadParam.unitType == TG::unitBw) {
   //    ui->ButtonUnit1->setText("dB");
   //    ui->ButtonUnit2->setVisible(false);
   //    ui->ButtonUnit3->setVisible(false);
   //    ui->ButtonUnit4->setVisible(false);
   //    ui->ButtonUnit5->setVisible(false);
   //} else {
   //    ui->ButtonUnit1->setText("");
   //    ui->ButtonUnit2->setText("");
   //    ui->ButtonUnit3->setText("");
   //    ui->ButtonUnit4->setText("");
   //    ui->ButtonUnit5->setText("");
   //    //ui->ButtonUnit5->setVisible(false);
   //}

   connect(ui->Button0, SIGNAL(clicked()), this, SLOT(slotButton0()));
   connect(ui->Button1, SIGNAL(clicked()), this, SLOT(slotButton1()));
   connect(ui->Button2, SIGNAL(clicked()), this, SLOT(slotButton2()));
   connect(ui->Button3, SIGNAL(clicked()), this, SLOT(slotButton3()));
   connect(ui->Button4, SIGNAL(clicked()), this, SLOT(slotButton4()));
   connect(ui->Button5, SIGNAL(clicked()), this, SLOT(slotButton5()));
   connect(ui->Button6, SIGNAL(clicked()), this, SLOT(slotButton6()));
   connect(ui->Button7, SIGNAL(clicked()), this, SLOT(slotButton7()));
   connect(ui->Button8, SIGNAL(clicked()), this, SLOT(slotButton8()));
   connect(ui->Button9, SIGNAL(clicked()), this, SLOT(slotButton9()));
   connect(ui->ButtonUp, SIGNAL(clicked()), this, SLOT(slotButtonUp()));
   connect(ui->ButtonDown, SIGNAL(clicked()), this, SLOT(slotButtonDown()));
   connect(ui->ButtonDot, SIGNAL(clicked()), this, SLOT(slotButtonDot()));
   connect(ui->ButtonMinus, SIGNAL(clicked()), this, SLOT(slotButtonMinus()));
   connect(ui->ButtonDelete, SIGNAL(clicked()), this, SLOT(slotButtonDelete()));

   connect(ui->ButtonUnit1, SIGNAL(clicked()), this, SLOT(slotButtonUnit1()));
   connect(ui->ButtonUnit2, SIGNAL(clicked()), this, SLOT(slotButtonUnit2()));
   connect(ui->ButtonUnit3, SIGNAL(clicked()), this, SLOT(slotButtonUnit3()));
   connect(ui->ButtonUnit4, SIGNAL(clicked()), this, SLOT(slotButtonUnit4()));
   connect(ui->ButtonUnit5, SIGNAL(clicked()), this, SLOT(slotButtonUnit5()));

   connect(ui->ButtonReject, SIGNAL(clicked()), this, SLOT(slotReject()));

   //connect(unitFreq, SIGNAL(clickedUnit(TG::UnitTypes, int)), this, SLOT(slotClickedUnit(TG::UnitTypes, int))); 
   connect(ui->lineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(doTextEdited(const QString &)));
   connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(doReturnPressed()));

   _buttonUnits.push_back(ui->ButtonUnit1);
   _buttonUnits.push_back(ui->ButtonUnit2);
   _buttonUnits.push_back(ui->ButtonUnit3);
   _buttonUnits.push_back(ui->ButtonUnit4);
   _buttonUnits.push_back(ui->ButtonUnit5);

   ui->lineEdit->installEventFilter(this);
   //ui->Button0->installEventFilter(this);
   //ui->Button1->installEventFilter(this);
   //ui->Button2->installEventFilter(this);
   //ui->Button3->installEventFilter(this);
   //ui->Button4->installEventFilter(this);
   //ui->Button5->installEventFilter(this);
   //ui->Button6->installEventFilter(this);
   //ui->Button7->installEventFilter(this);
   //ui->Button8->installEventFilter(this);
   //ui->Button9->installEventFilter(this);
}

KeyPadNew2::~KeyPadNew2()
{
    delete ui;
}

void KeyPadNew2::doTextEdited(const QString &text)
{
   if (checkSimbol(ui->lineEdit->text())) {
      _textBefore = ui->lineEdit->text();
   }
   else {
      ui->lineEdit->setText(_textBefore);
   }
}

bool KeyPadNew2::checkSimbol(QString &newText)
{
   //const double maxValue(65'000'000'000.0);
   const double maxValue(40'000'000'000.0);

   double newValue = newText.toDouble();

   ui->ButtonUnit5->setDisabled(true);
   if (newValue * 1'000'000'000.0 > maxValue) {
      ui->ButtonUnit4->setEnabled(false);
      //ui->ButtonUnit5->setDisabled(true);
   }
   else {
      ui->ButtonUnit4->setEnabled(true);
   }
   if (newValue * 1'000'000.0 > maxValue) {
      ui->ButtonUnit3->setEnabled(false);
      //ui->ButtonUnit4->setDisabled(true);
      //ui->ButtonUnit5->setDisabled(true);
   }
   else {
      ui->ButtonUnit3->setEnabled(true);
   }
   if (newValue * 1'000.0 > maxValue) {
      ui->ButtonUnit2->setEnabled(false);
      //ui->ButtonUnit3->setDisabled(true);
      //ui->ButtonUnit4->setDisabled(true);
      //ui->ButtonUnit5->setDisabled(true);
   }
   else {
      ui->ButtonUnit2->setEnabled(true);
   }
   if (newValue * 1.0 > maxValue) {
      //ui->ButtonUnit1->setEnabled(false);
      //ui->ButtonUnit2->setEnabled(false);
      //ui->ButtonUnit3->setEnabled(false);
      //ui->ButtonUnit4->setEnabled(false);
      //ui->ButtonUnit5->setEnabled(false);
      return false;
   }
   else {
      ui->ButtonUnit1->setEnabled(true);
   }
   //else {
   //   ui->ButtonUnit1->setEnabled(true);
   //   ui->ButtonUnit2->setEnabled(true);
   //   ui->ButtonUnit3->setEnabled(true);
   //   ui->ButtonUnit4->setEnabled(true);
   //   ui->ButtonUnit5->setEnabled(true);
   //}

   return true;
}

bool KeyPadNew2::checkSimbol(QObject* object, QEvent* event)
{
   //const double maxValue(60'000'000'000.0);

   QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
   QString simbol = keyEvent->text();
   QString text = ui->lineEdit->text();
   QString newText(QString("%1%2").arg(text).arg(simbol));
   double newValue = newText.toDouble();

   //if (simbol.length() == 0) return false;
   //else return checkSimbol(newText);
   return false;
}

bool KeyPadNew2::eventFilter(QObject* object, QEvent* event)
{
   Q_UNUSED(object);
   Q_UNUSED(event);

   //if (_controller == nullptr) return true;

   //_keyPadParam._unitType = TG::unitFreq;

   //TouchBegin //194,
   //TouchUpdate //195,
   //TouchEnd //196,
   //TouchCancel //209,

   if (object == (QObject*)ui->lineEdit) {
      if (event->type() == QEvent::FocusOut) {
         int i(0);
         if (ui->lineEdit->hasSelectedText()) {
            _selectedText = true;
            //QString value = ui->lineEdit->selectedText();
            //ui->lineEdit->del();
            //int i(0);
         }
      }
      //if (event->type() == QEvent::Enter) {
      //	int i(0);
      //}
      //if (event->type() == QEvent::Leave) {
      //	int i(0);
      //}
   }
   else {
      if (event->type() == QEvent::MouseButtonPress) {
         int i = 0;
         //if (ui->lineEdit->hasSelectedText()) {
         //	QString value = ui->lineEdit->selectedText();
         //	ui->lineEdit->del();
         //	int i(0);
         //}
         //else {
         //	int i(0);
         //}
      }
      //if (event->type() == QEvent::Enter) {
      //	int i(0);
      //}
      //if (event->type() == QEvent::Leave) {
      //	int i(0);
      //}
   }

   //if (object == target && event->type() == QEvent::KeyPress)
   if (event->type() == QEvent::KeyPress)
   {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

      return checkSimbol(object, event);
      //QString simbol = keyEvent->text();
      //QString text = ui->lineEdit->text();
      //QString newText(QString("%1%2").arg(text).arg(simbol));
      //double newValue = newText.toDouble();

      //if (keyEvent->key() == Qt::Key_Tab) {
      //   //return true; // Special tab handling
      //   return false; // lets the event continue to process
      //}
      //else
      //   return false; // lets the event continue to process
   }
   else if (event->type() == QEvent::MouseButtonPress) {
      int i(0);
      //return true; // Special handling
      return false; // lets the event continue to process
      //}
      //else if (event->type() == QEvent::KeyPress) {
      //	int i(0);
      //	return true; // lets the event continue to the edit
   }

   //return QWidget::event(event);
   return false; // lets the event continue to the edit
}

void KeyPadNew2::getSelection(TG::UnitTypes &type, int &index, double &value)
{
    type = this->type;
    index = this->index;
    value = ui->lineEdit->text().toDouble();
}

void KeyPadNew2::getSelection(TG::UnitTypes &type, int &index, QString &text)
{
    type = this->type;
    index = this->index;
    text = ui->lineEdit->text();
}

TG::KeyPadParam& KeyPadNew2::params(void)
{
    return _keyPadParam;
}

void KeyPadNew2::setParams(const TG::KeyPadParam& keyPadParam, int unitindex)
{
    _keyPadParam = keyPadParam;
    _unitindex = unitindex;

    ui->labelName->setText(_keyPadParam._name);

    if(_keyPadParam._unitType == TG::unitIpAddress) {
        ui->lineEdit->setText(QString("%1").arg(_keyPadParam._text));
    } else {
      //QString strValue(QString("%1").arg(_keyPadParam._value, 0, 'f'));
      //QString strCut(QString("%1").arg(_keyPadParam._value, 0, 'f'));
      //if (strValue.length() > 10)
      //	strCut = QString(strValue.toStdString().substr(0, 11).c_str());

      QString strValue;
      //Double2String(strValue, _keyPadParam._value);
      gsa::controller->Double2String(strValue, _keyPadParam._value);

      //ui->lineEdit->setText(QString("%1").arg(_keyPadParam._value));
      ui->lineEdit->setText(QString("%1").arg(strValue));
   }

   QFocusEvent* eventFocus = new QFocusEvent(QEvent::FocusIn);
   qApp->postEvent(ui->lineEdit, (QEvent *)eventFocus, Qt::LowEventPriority);
   ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
   ui->lineEdit->setFocus();
   ui->lineEdit->selectAll();

   _selectedText = true;

   this->type = _keyPadParam._unitType;

   int length(std::min(_buttonUnits.length(), keyPadParam._buttonNames.length()));

   _textBefore = ui->lineEdit->text();
   checkSimbol(ui->lineEdit->text());

   for(int i=0; i<_buttonUnits.length(); i++) {
      _buttonUnits[i]->setText("");
      _buttonUnits[i]->setVisible(false);
   }
   for(int i=0; i<length; i++) {
      _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
      _buttonUnits[i]->setVisible(true);
   }
   //if(_keyPadParam.unitType == TG::unitFreq) {
   //    for(int i=0; i<length; i++) {
   //        _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
   //        _buttonUnits[i]->setVisible(true);
   //    }
   //} else if(_keyPadParam.unitType == TG::unitTime) {
   //    for(int i=0; i<length; i++) {
   //        _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
   //        _buttonUnits[i]->setVisible(true);
   //    }
   //} else if(_keyPadParam.unitType == TG::unitAmpt) {
   //    for(int i=0; i<length; i++) {
   //        _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
   //        _buttonUnits[i]->setVisible(true);
   //    }
   //} else if(_keyPadParam.unitType == TG::unitBw) {
   //    for(int i=0; i<length; i++) {
   //        _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
   //        _buttonUnits[i]->setVisible(true);
   //    }
   //} else if(_keyPadParam.unitType == TG::unitLine) {
   //    for(int i=0; i<length; i++) {
   //        _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
   //        _buttonUnits[i]->setVisible(true);
   //    }
   //} else {
   //    for(int i=0; i<length; i++) {
   //        _buttonUnits[i]->setText(keyPadParam._buttonNames[i]);
   //        _buttonUnits[i]->setVisible(true);
   //    }
   //}
}

void KeyPadNew2::pressButton(QString &button)
{
    if(button == QString("1")) {
        QTimer::singleShot(0, ui->Button1, SLOT(click()));
    } else if(button == QString("2")) {
        QTimer::singleShot(0, ui->Button2, SLOT(click()));
    } else if(button == QString("3")) {
        QTimer::singleShot(0, ui->Button3, SLOT(click()));
    } else if(button == QString("4")) {
        QTimer::singleShot(0, ui->Button4, SLOT(click()));
    } else if(button == QString("5")) {
        QTimer::singleShot(0, ui->Button5, SLOT(click()));
    } else if(button == QString("6")) {
        QTimer::singleShot(0, ui->Button6, SLOT(click()));
    } else if(button == QString("7")) {
        QTimer::singleShot(0, ui->Button7, SLOT(click()));
    } else if(button == QString("8")) {
        QTimer::singleShot(0, ui->Button8, SLOT(click()));
    } else if(button == QString("9")) {
        QTimer::singleShot(0, ui->Button9, SLOT(click()));
    } else if(button == QString("0")) {
        QTimer::singleShot(0, ui->Button0, SLOT(click()));
    } else if(button == QString(".")) {
        QTimer::singleShot(0, ui->ButtonDot, SLOT(click()));
    } else if(button == QString("Backspace")) {
        QTimer::singleShot(0, ui->ButtonDelete, SLOT(click()));
    } else if(button == QString("Delete")) {
        QTimer::singleShot(0, ui->ButtonDelete, SLOT(click()));
    } else if(button == QString("Enter")) {
        QTimer::singleShot(0, ui->ButtonUnit1, SLOT(click()));
    } else if(button == QString("Esc")) {
        QTimer::singleShot(0, ui->ButtonReject, SLOT(click()));
    }
}

void KeyPadNew2::slotClickedUnit(TG::UnitTypes type, int index)
{
    this->type = type;
    this->index = index;

    //switch(type)
    //{
    //case TG::unitUndef:
    //{
    //    break;
    //}
    //case TG::unitFreq:
    //{
    //    this->type = type;
    //    this->index = index;
    //    break;
    //}
    //case TG::unitTime:
    //{
    //    break;
    //}
    //case TG::unitAmpt:
    //{
    //    break;
    //}
    //default:
    //{
    //    break;
    //}
    //}

    QDialog::accept();
}

void KeyPadNew2::setText(QString &text)
{
   if (_selectedText == true) {
      ui->lineEdit->selectAll();
      ui->lineEdit->del();
      _selectedText = false;
   }
   ui->lineEdit->setText(ui->lineEdit->text().append(text));
}

void KeyPadNew2::doCancel(void)
{
   reject();
}

void KeyPadNew2::slotButton0(void)
{
   //if (ui->lineEdit->hasSelectedText()) {
   //	QString value = ui->lineEdit->selectedText();
   //	ui->lineEdit->del();
   //	int i(0);
   //}
   //else {
   //	int i(0);
   //}
   //bool selectedText = ui->lineEdit->hasSelectedText();
   //QString value = ui->lineEdit->selectedText();
   //ui->lineEdit->del();

   //QString strValue = ui->lineEdit->text();
   //ui->lineEdit->setText(QString("%1").arg(strValue));
   //double value = 0;
   //double value = ui->lineEdit->text().toDouble();
   //int value2 = ui->lineEdit->text().toInt();
   //QString strValue = ui->lineEdit->text();
   //QString str = ui->lineEdit->text();
   //int temp = str.toInt();
   //ui->lineEdit->setText(QString("%1").arg(value2));

   //int value = ui->lineEdit->text().toInt();
   //++value;
   //ui->lineEdit->setText(QString("%1").arg(value));

   //if (_selectedText == true) {
   //	ui->lineEdit->selectAll();
   //	ui->lineEdit->del();
   //	_selectedText = false;
   //}
   //ui->lineEdit->setText(ui->lineEdit->text().append(QString("0")));
   setText(QString("0"));
}

void KeyPadNew2::slotButton1(void)
{
   //if (_selectedText == true) {
   //	ui->lineEdit->selectAll();
   //	ui->lineEdit->del();
   //	_selectedText = false;
   //}
   //ui->lineEdit->setText(ui->lineEdit->text().append(QString("1")));
   setText(QString("1"));
}

void KeyPadNew2::slotButton2(void)
{
   //if (_selectedText == true) {
   //	ui->lineEdit->selectAll();
   //	ui->lineEdit->del();
   //	_selectedText = false;
   //}
   //ui->lineEdit->setText(ui->lineEdit->text().append(QString("2")));
   setText(QString("2"));
}

void KeyPadNew2::slotButton3(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("3")));
   setText(QString("3"));
}

void KeyPadNew2::slotButton4(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("4")));
   setText(QString("4"));
}

void KeyPadNew2::slotButton5(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("5")));
   setText(QString("5"));
}

void KeyPadNew2::slotButton6(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("6")));
   setText(QString("6"));
}

void KeyPadNew2::slotButton7(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("7")));
   setText(QString("7"));
}

void KeyPadNew2::slotButton8(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("8")));
   setText(QString("8"));
}

void KeyPadNew2::slotButton9(void)
{
    //ui->lineEdit->setText(ui->lineEdit->text().append(QString("9")));
   setText(QString("9"));
}

void KeyPadNew2::slotButtonUp(void)
{
   if (_selectedText == true) {
      ui->lineEdit->selectAll();
      ui->lineEdit->del();
      _selectedText = false;
   }
   double value = ui->lineEdit->text().toDouble();
      value = value + 1.0;
   QString strValue;
   //Double2String(strValue, value);
   gsa::controller->Double2String(strValue, value);
   
   ui->lineEdit->setText(QString("%1").arg(strValue));
}

void KeyPadNew2::slotButtonDown(void)
{
	if (_selectedText == true) {
		ui->lineEdit->selectAll();
		ui->lineEdit->del();
		_selectedText = false;
	}
	double value = ui->lineEdit->text().toDouble();
	value = value - 1.0;
	QString strValue;
	//Double2String(strValue, value);
   gsa::controller->Double2String(strValue, value);
   ui->lineEdit->setText(QString("%1").arg(strValue));
}

void KeyPadNew2::slotButtonDot(void)
{
    QString text = ui->lineEdit->text();
    if(text.indexOf(".") == -1) {
        ui->lineEdit->setText(text.append(QString(".")));
    }
}

void KeyPadNew2::slotButtonMinus(void)
{
    QString text = ui->lineEdit->text();
    if(text.length() > 0) {
        QString sign = text.left(1);
        if(sign == QString("-")) {
            ui->lineEdit->setText(text.remove(0, 1));
        } else {
            ui->lineEdit->setText(text.insert(0, QString("-")));
        }
    }
}

void KeyPadNew2::slotButtonDelete(void)
{
    QString text = ui->lineEdit->text();
    if(text.length() > 0) {
        text.chop(1);
        ui->lineEdit->setText(text);
    }
}

void KeyPadNew2::slotButtonUnit1(void)
{
   this->index = 0;

   //if(this->type == TG::unitFreq) {
   //     this->index = TG::fr_GHz;
   // } else if(this->type == TG::unitTime) {
   //     this->index = TG::sw_ks;
   // } else if(this->type == TG::unitAmpt) {
   //     this->index = 1;
   // } else if(this->type == TG::unitBw) {
   //     this->index = TG::fr_kHz;
   // }
   // //this->type = TG::unitFreq;
   // //this->index = TG::fr_GHz;

    QDialog::accept();
}

void KeyPadNew2::slotButtonUnit2(void)
{
   this->index = 1;

   //if(this->type == TG::unitFreq) {
   //     this->index = TG::fr_MHz;
   // } else if(this->type == TG::unitTime) {
   //     this->index = TG::sw_s;
   // } else if(this->type == TG::unitAmpt) {
   //     this->index = 1;
   // } else if(this->type == TG::unitBw) {
   //     this->index = TG::fr_kHz;
   // }
   // //this->type = TG::unitFreq;
   // //this->index = TG::fr_MHz;

    QDialog::accept();
}

void KeyPadNew2::slotButtonUnit3(void)
{
   this->index = 2;

   //if(this->type == TG::unitFreq) {
   //     this->index = TG::fr_kHz;
   // } else if(this->type == TG::unitTime) {
   //     this->index = TG::sw_ms;
   // } else if(this->type == TG::unitAmpt) {
   //     this->index = 1;
   // } else if(this->type == TG::unitBw) {
   //     this->index = TG::fr_kHz;
   // }
   // //this->type = TG::unitFreq;
   // //this->index = TG::fr_kHz;

    QDialog::accept();
}

void KeyPadNew2::slotButtonUnit4(void)
{
   this->index = 3;

   //if(this->type == TG::unitFreq) {
   //     this->index = TG::fr_Hz;
   // } else if(this->type == TG::unitTime) {
   //     this->index = TG::sw_mks;
   // } else if(this->type == TG::unitAmpt) {
   //     this->index = 1;
   // } else if(this->type == TG::unitBw) {
   //     this->index = TG::fr_kHz;
   // }
   // //this->type = TG::unitFreq;
   // //this->index = TG::fr_Hz;

    QDialog::accept();
}

void KeyPadNew2::slotButtonUnit5(void)
{
   this->index = 4;

   //if(this->type == TG::unitFreq) {
   //     this->index = 1;
   // } else if(this->type == TG::unitTime) {
   //     this->index = TG::sw_ns;
   // } else if(this->type == TG::unitAmpt) {
   //     this->index = 1;
   // } else if(this->type == TG::unitBw) {
   //     this->index = TG::fr_kHz;
   // }
   // //this->type = TG::unitFreq;
   // //this->index = TG::fr_Hz;

    QDialog::accept();
}

void KeyPadNew2::slotReject(void)
{
    QDialog::reject();
}

void KeyPadNew2::resizeEvent ( QResizeEvent * event )
{
    Q_UNUSED(event)

    QSize size = event->size();
    int i(0);
    Q_UNUSED(size)
    Q_UNUSED(i)

    //QDesktopWidget *mydesk = QApplication::desktop();
    //QSize size2 = mydesk->size();

}

void KeyPadNew2::doReturnPressed(void)
{
   QObject *senderObj = sender(); // This will give Sender object
   QString senderObjName = senderObj->objectName();

   //if (this->type == TG::unitFreq) {
   //	this->index = TG::fr_GHz;
   //}
   //else if (this->type == TG::unitTime) {
   //	this->index = TG::sw_ks;
   //}
   //else if (this->type == TG::unitAmpt) {
   //	this->index = 1;
   //}
   //else if (this->type == TG::unitBw) {
   //	this->index = TG::fr_kHz;
   //}

   //this->type = TG::unitFreq;
   //this->index = 1; //TG::fr_Hz;

   this->index = _unitindex; 

   QDialog::accept();

   //auto itObj = std::find_if(
   //	lineEdits.begin(), lineEdits.end(),
   //	[senderObj](QObject* p) { return p == senderObj; }
   //);
   //if (itObj != lineEdits.end()) {
   //	QString unit("");
   //	int index(0);
   //	unit = dynamic_cast<QLineEdit*>(*itObj)->text();
   //	//QString text2(dynamic_cast<QLineEdit*>(*itObj)->text());
   //	//QString text3(dynamic_cast<MenuItem*>(*itObj)->text());
   //	wcscpy(wtext, (wchar_t*)unit.toStdWString().c_str());
   //	index = 0; //index - 1;
   //	g_Parameter._SetValue(dynamic_cast<MenuItem*>(*itObj)->itemIndex(), _keyPadParam._value, wtext, index);
   //}
   //else {
   //	int i(0);
   //}
}

void KeyPadNew2::wheelEvent(QWheelEvent * event)
{
	//event->delta() can be negative or positive
	//this->setText("Delta Value: " + QString::number(event->delta()));

	QPoint numPixels = event->pixelDelta();
	QPoint numDegrees = event->angleDelta() / 8;
	QString delta = QString::number(event->delta());
	//QPoint numS;
	//QPoint numSteps;

	//QWidget *widget = ui->stackedWidget->currentWidget();
	//MenuPage *menuPage = (MenuPage *)widget;
	//if (menuPage != nullptr) {
	//	menuPage->doWheelEvent(event->delta());
	//}

	//if (!numPixels.isNull()) {
	//	//numS = numPixels / 15;
	//	//scrollWithPixels(numPixels);
	//}
	//else if (!numDegrees.isNull()) {
	//	//numSteps = numDegrees / 15;
	//	//scrollWithDegrees(numSteps);
	//}

	event->accept();

	QDialog::reject();
};

//void KeyPadNew2::Double2String(QString &str, double value)
//{
//   QString strValue(QString("%1").arg(value, 0, 'f'));
//   QString strCut(QString("%1").arg(value, 0, 'f'));
//   int index = strValue.indexOf(".");
//   if (strValue.length() > 9)
//      strCut = QString(strValue.toStdString().substr(0, index).c_str());
//
//   //QString strCut(QString("%1").arg((long long)value));
//
//   str = strCut;
//}

} // namespace Pad

