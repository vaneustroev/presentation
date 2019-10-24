// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#include "gmenu/menufreq.h"
#include "gcore/controller.h"
//#include "gscreen/screenwidget.h"
#include "ui_MenuFreq.h"

namespace Menu
{

	MenuFreq::MenuFreq(QWidget *parent, gsa::core::Controller *controller)
		: IMenu(parent)
		, ui(new Ui::MenuFreq)
		, _controller(controller)
	{
		ui->setupUi(this);
	}

	MenuFreq::~MenuFreq()
	{
		delete ui;
	}

	void MenuFreq::menuItemEdit(QString text)
	{
	}

	void MenuFreq::KeyPad(const TG::KeyPadParam &keyPadParam)
	{
		//fillButtonNames();

		//int ret = _controller->KeyPad(keyPadParam);
		//if (ret == QDialog::Accepted)
		//{
		//	_controller->getSelection(type, index, value);

		//	if (keyPadParam._fieldType == TG::typeFreqCenter) {
		//		_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
		//		_controller->setFreqCenter(value);
		//		//ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
		//		//ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
		//		//ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
		//		//ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
		//	}
		//	else if (keyPadParam._fieldType == TG::typeFreqSpan) {
		//		_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
		//		_controller->setFreqSpan(value);
		//		//ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
		//		//ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
		//		//ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
		//		//ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
		//	}
		//	else if (keyPadParam._fieldType == TG::typeFreqStart) {
		//		_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
		//		_controller->setFreqStart(value);
		//		//ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
		//		//ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
		//		//ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
		//		//ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
		//	}
		//	else if (keyPadParam._fieldType == TG::typeFreqStop) {
		//		_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
		//		_controller->setFreqStop(value);
		//		//ui->EditCenter->setText(QString("%1 %2").arg(_controller->freqCenter()).arg(_controller->freqUnitText()));
		//		//ui->EditSpan->setText(QString("%1 %2").arg(_controller->freqSpan()).arg(_controller->freqUnitText()));
		//		//ui->EditStart->setText(QString("%1 %2").arg(_controller->freqStart()).arg(_controller->freqUnitText()));
		//		//ui->EditStop->setText(QString("%1 %2").arg(_controller->freqStop()).arg(_controller->freqUnitText()));
		//	}
		//	else if (keyPadParam._fieldType == TG::typeFreqStep) {
		//		_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
		//		_controller->setFreqStep(value);
		//		//ui->EditStep->setText(QString("%1 %2").arg(value).arg(_controller->freqUnitText()));
		//	}
		//	else if (keyPadParam._fieldType == TG::typeFreqOffset) {
		//		_controller->setFreqUnit(static_cast<TG::FreqUnits>(index));
		//		_controller->setFreqOffset(value);
		//		//ui->EditOffset->setText(QString("%1 %2").arg(value).arg(_controller->freqUnitText()));
		//	}

		//	//_controller->screenWidget()->redraw();
		//}

		////    position = keyPadNew2->pos();

		////    delete keyPadNew2;
	}

	bool MenuFreq::eventFilter(QObject* object, QEvent* event)
	{
		Q_UNUSED(object);
		Q_UNUSED(event);

		//if(object == edit && event->type() == QEvent::MouseClick) {
		//    // bring up your custom edit
		//    return false; // lets the event continue to the edit
		//}
		//boost::container::map<TG::Types, TG::KeyPadParam> keyPadParamList;

		if (_controller == nullptr) return true;

		keyPadParamList[TG::unitFreq]._unitType = TG::unitFreq;

		if (event->type() == QEvent::MouseButtonPress) {
			//if (object == ui->EditCenter) {
			//	//KeyPad(TG::unitFreq, "Center Freq");
			//	keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqCenter;
			//	keyPadParamList[TG::unitFreq]._name = QString("Center Freq");
			//	keyPadParamList[TG::unitFreq]._value = _controller->freqCenter();
			//	KeyPad(keyPadParamList[TG::unitFreq]);
			//}
			//else if (object == ui->EditSpan) {
			//	//KeyPad(TG::unitFreq, "Span Freq");
			//	keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqSpan;
			//	keyPadParamList[TG::unitFreq]._name = QString("Span Freq");
			//	keyPadParamList[TG::unitFreq]._value = _controller->freqSpan();
			//	KeyPad(keyPadParamList[TG::unitFreq]);
			//}
			//else if (object == ui->EditStart) {
			//	//KeyPad(TG::unitFreq, "Start Freq");
			//	keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqStart;
			//	keyPadParamList[TG::unitFreq]._name = QString("Start Freq");
			//	keyPadParamList[TG::unitFreq]._value = _controller->freqStart();
			//	KeyPad(keyPadParamList[TG::unitFreq]);
			//}
			//else if (object == ui->EditStop) {
			//	//KeyPad(TG::unitFreq, "Stop Freq");
			//	keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqStop;
			//	keyPadParamList[TG::unitFreq]._name = QString("Stop Freq");
			//	keyPadParamList[TG::unitFreq]._value = _controller->freqStop();
			//	KeyPad(keyPadParamList[TG::unitFreq]);
			//}
			//else if (object == ui->EditStep) {
			//	//KeyPad(TG::unitFreq, "Step Freq");
			//	keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqStep;
			//	keyPadParamList[TG::unitFreq]._name = QString("Step Freq");
			//	keyPadParamList[TG::unitFreq]._value = _controller->freqStep();
			//	KeyPad(keyPadParamList[TG::unitFreq]);
			//}
			//else if (object == ui->EditOffset) {
			//	//KeyPad(TG::unitFreq, "Offset Freq");
			//	keyPadParamList[TG::unitFreq]._fieldType = TG::typeFreqOffset;
			//	keyPadParamList[TG::unitFreq]._name = QString("Offset Freq");
			//	keyPadParamList[TG::unitFreq]._value = _controller->freqOffset();
			//	KeyPad(keyPadParamList[TG::unitFreq]);
			//}
			//else if (object == ui->FullSpan) {
			//	_controller->setFullSpan();
			//	ui->SweptSpan->setChecked(true);
			//	_controller->setFreq();
			//}
			//return false; // lets the event continue to the edit
			return true; // lets the event continue to the edit
		}

		return false;
	}

	void MenuFreq::clickSweptSpan(void)
	{
	}

	void MenuFreq::clickFullSpan(void)
	{
	}

	void MenuFreq::clickZeroSpan(void)
	{
	}

	void MenuFreq::fillButtonNames(void)
	{
	}

	void MenuFreq::setParam(TG::FreqParam &freqParam)
	{
	}

} // namespace Menu

