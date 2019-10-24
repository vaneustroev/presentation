#ifndef CONTROLLERPRESETS_H
#define CONTROLLERPRESETS_H

#include <QString>
#include <QSettings>
#include <QDateTime>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include "measuresettings.h"
#include "controllerpresets_const.h"
#include <ui_edituserpresets.h>

//using namespace CTRL_UserPreset;

namespace Table {

class ControllerPresets : public QObject
{
    Q_OBJECT
private:
    Ui_EditUserPresetDialog ui;

    MeasureSettings *measSettings;

    QString filenameSession;
    QString filenameUserList;
    QList<MeasureSettings> settingsList;
    int ShowInputStrDialog( const QString & title, QString & value );
    void ReadSettings( QSettings *fileIni, QString sectionName, MeasureSettings *measSet );
    void WriteSettings( QSettings *fileIni, QString sectionName, MeasureSettings *measSet );

    void WriteLastSession();                        //Записать параметры текущей сессии
    void ReadLastSession();                         //Прочитать параметры и установить в текущую сессию

    void WriteUserList();                           //Записать пользовательский список
    void ReadUserList();                            //Читать пользовательский список

    void UpdateButtonsEnabled();

public:
    ControllerPresets(QString filePath, MeasureSettings &measSet );
    void SaveAllData();
    QStringList GetUserPresetsList();               //Вернуть список пользовательских настроек
    int GetUserPresetsListCount();                  //Вернуть количество элементов списка пользовательских настроек
    bool ApplyUserPreset( int UserPresetIndex );    //Установить пользовательские настройки по указанному индексу
    void ShowEditWindow();                          //Отобразить окно редактирования

signals:
    void presetsChange();
    void presetsReset();

private slots:
    void AddSettingsItem();
    void Apply();                                   //Установить выбранные параметры настройки в прибор
    void Replace();                                 //Заменить выбранные параметры настройки текущими (из прибора)
    void DeleteItem();                              //Удалить элемент списка настроек
    void ClearList();                               //Очистить список настроек
    void Rename();                                  //Переименовать элемент
    void Reset();                                   //Сброс к заводским настройкам
    void SelectItem();
    void ShowEditForm();                            //Показать форму для редактирования
};

} //namespace Table

#endif // CONTROLLERPRESETS_H

