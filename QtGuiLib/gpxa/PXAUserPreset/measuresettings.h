//Класс параметров работы прибора
#ifndef MEASURESETTINGS_H
#define MEASURESETTINGS_H

#include <QString>

namespace Table {

enum ModeMeas { //типы режимов работы прибора
    spectrum //анализатор спектра
};

} //namespace Table

namespace Table {

class MeasureSettings
{
public:
    MeasureSettings();
    void Preset();//Сбросить все параметры на заводские

    void FillParamFromSource( MeasureSettings & source );
    //Название настроек
    QString GetSettingsName();
    void SetSettingsName( QString value );

    //Режим работы прибора
    ModeMeas GetMeasMode();//Получить режим работы прибора
    QString GetMeasModeString();//Получить строковое обозначение режима работы прибора
    void SetMeasMode( ModeMeas value );//Установить режим работы прибора

    //Центральная частота
    double GetCentralFreqMHz();
    void SetCentralFreqMHz( double valueMHz );

    //Начальная частота
    double GetStartFreqMHz();
    void SetStartFreqMHz( double valueMHz );

    //Конечная частота
    double GetStopFreqMHz();
    void SetStopFreqMHz( double valueMHz );

    //span
    double GetSpanFreqMHz();
    void SetSpanFreqMHz( double valueMHz );

    //Шаг частоты
    double GetStepFreqMHz();
    void SetStepFreqMHz( double valueMHz );

    //van

    double GetAmptRelativeValue();
    void SetAmptRelativeValue(double value);
    double GetSweepTime();
    void SetSweepTime(double value);
    double GetResBw();
    void SetResBw(double value);
    double GetVideoBw();
    void SetVideoBw(double value);
    double GetDisplayLineVolt();
    void SetDisplayLineVolt(double value);

private:
    QString settingsName; //Название настроек
    ModeMeas measMode; //режим работы прибора

    double centralFreqMHz; //Центральная частота, МГц
    double startFreqMHz; //Начальная частота, МГц
    double stopFreqMHz; //Конечная частота, МГц
    double spanFreqMHz; //span, МГц
    double stepFreqMHz; //Шаг частоты, МГц

    double amptRelativeValue;
    double sweepTime;
    double resBw;
    double videoBw;
    double displayLine;

};

} //namespace Table

#endif // MEASURESETTINGS_H

