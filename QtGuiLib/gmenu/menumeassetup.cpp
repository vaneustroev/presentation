// Copyright (C) 2015-2018 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#include "gmenu/menumeassetup.h"
#include "gcore/controller.h"
#include "gscreen/screenwidget.h"
#include "ui_menumeassetup.h"

namespace Menu
{

MenuMeasSetup::MenuMeasSetup(QWidget *parent, gsa::core::Controller *controller)
    : IMenu(parent)
    , ui(new Ui::MenuMeasSetup)
    , _controller(controller)
{
    ui->setupUi(this);

    //ui->MarkerModeNorma->installEventFilter(this);
}

MenuMeasSetup::~MenuMeasSetup()
{
    delete ui;
}

void MenuMeasSetup::menuItemEdit(QString text)
{
    QWidget * focusWidget1 = QApplication::focusWidget();
    QWidget * focusWidget2 = focusWidget();

    //if(_controller->keyPadFlag() == false) {
    //    QEvent event(QEvent::MouseButtonPress);
    //    eventFilter(focusWidget1, &event);
    //} else {
    //    _controller->pressButton(text);
    //}
}

void MenuMeasSetup::KeyPad(const TG::KeyPadParam &keyPadParam)
{
    //int ret = _controller->KeyPad(keyPadParam);
    //if(ret == QDialog::Accepted)
    //{
    //    _controller->getSelection(type, index, value);

    //    if(keyPadParam._fieldType == TG::typeResBw) {
    //        _controller->setBwUnit(static_cast<TG::FreqUnits>(index));
    //        _controller->setResBw(value, true);
    //        //ui->ResBw->setText(QString("%1 %2").arg(value).arg(_controller->bwUnitText()) );
    //    } else if(keyPadParam._fieldType == TG::typeVideoBw) {
    //        _controller->setBwUnit(static_cast<TG::FreqUnits>(index));
    //        _controller->setVideoBw(value, true);
    //        //ui->VideoBw->setText(QString("%1 %2").arg(value).arg(_controller->bwUnitText()) );
    //    } else if(keyPadParam._fieldType == TG::typeVbw3dbRbw) {
    //        _controller->setBwUnit(static_cast<TG::FreqUnits>(index));
    //        _controller->setVbw3dbRbw(value);
    //        //ui->Vbw3dbRbw->setText(QString("%1 %2").arg(value).arg(_controller->bwUnitText()) );
    //    } else if(keyPadParam._fieldType == TG::typeSpan3dbRbw) {
    //        _controller->setBwUnit(static_cast<TG::FreqUnits>(index));
    //        _controller->setSpan3dbRbw(value);
    //        //ui->Span3dbRbw->setText(QString("%1 %2").arg(value).arg(_controller->bwUnitText()) );
    //    } else if(keyPadParam._fieldType == TG::typeRbwFilterBw) {
    //        _controller->setBwUnit(static_cast<TG::FreqUnits>(index));
    //        _controller->setRbwFilterBw(value);
    //        //ui->RbwFilterBw->setText(QString("%1 %2").arg(value).arg(_controller->bwUnitText()) );
    //    }

    //    _controller->screenWidget()->redraw();
    //}

}

bool MenuMeasSetup::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object);
    Q_UNUSED(event);

    if(_controller == nullptr) return true;

    keyPadParamList[TG::unitAmpt]._unitType = TG::unitAmpt;
    if(event->type() == QEvent::MouseButtonPress) {
        //if(object == ui->MarkerModeNorma) {
        //    keyPadParamList[TG::unitAmpt]._fieldType = TG::typeResBw;
        //    keyPadParamList[TG::unitAmpt].name = QString("Res BW");
        //    keyPadParamList[TG::unitAmpt].value = _controller->freqCenter();
        //    KeyPad(keyPadParamList[TG::unitAmpt]);
        //} else if(object == ui->VideoBw) {
        //    keyPadParamList[TG::unitFreq]._fieldType = TG::typeVideoBw;
        //    keyPadParamList[TG::unitFreq].name = QString("Video BW");
        //    keyPadParamList[TG::unitFreq].value = _controller->freqSpan();
        //    KeyPad(keyPadParamList[TG::unitFreq]);
        //} else if(object == ui->Vbw3dbRbw) {
        //    keyPadParamList[TG::unitFreq]._fieldType = TG::typeVbw3dbRbw;
        //    keyPadParamList[TG::unitFreq].name = QString("VBW RBW");
        //    keyPadParamList[TG::unitFreq].value = _controller->freqStart();
        //    KeyPad(keyPadParamList[TG::unitFreq]);
        //} else if(object == ui->Span3dbRbw) {
        //    keyPadParamList[TG::unitFreq]._fieldType = TG::typeSpan3dbRbw;
        //    keyPadParamList[TG::unitFreq].name = QString("Span RBW");
        //    keyPadParamList[TG::unitFreq].value = _controller->freqStop();
        //    KeyPad(keyPadParamList[TG::unitFreq]);
        //} else if(object == ui->RbwFilterBw) {
        //    keyPadParamList[TG::unitFreq]._fieldType = TG::typeRbwFilterBw;
        //    keyPadParamList[TG::unitFreq].name = QString("RBW FILTER BW");
        //    keyPadParamList[TG::unitFreq].value = _controller->freqStep();
        //    KeyPad(keyPadParamList[TG::unitFreq]);
        //}
        //return false; // lets the event continue to the edit
        return true; // lets the event continue to the edit
    }

    return false;
}

void MenuMeasSetup::setParam(TG::MeasSetupParam &measSetupParam)
{
    Q_UNUSED(measSetupParam);

    //ui->ResBw->setText(QString("%1 %2").arg(bwParam.resBw).arg(bwParam.unit));
    //ui->VideoBw->setText(QString("%1 %2").arg(bwParam.videoBw).arg(bwParam.unit));
    //ui->Vbw3dbRbw->setText(QString("%1 %2").arg(bwParam.vbw3dbRbw).arg(bwParam.unit));
    //ui->Span3dbRbw->setText(QString("%1 %2").arg(bwParam.span3dbRbw).arg(bwParam.unit));
    //ui->RbwFilterBw->setText(QString("%1 %2").arg(bwParam.rbwFilterBw).arg(bwParam.unit));

}

} // namespace Menu

