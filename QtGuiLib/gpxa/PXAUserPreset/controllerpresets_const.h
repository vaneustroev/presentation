#ifndef CONTROLLERPRESETS_CONST
#define CONTROLLERPRESETS_CONST
#include <QString>
namespace CTRL_UserPreset {

//Названия файлов для хранения настроек
const QString SESSION_FILE_NAME = "session.prst";
const QString USERLIST_FILE_NAME = "userlist.prst";

//Названия групп для записи и чтения файла настроек
const QString idLastSession = "LastSession";
const QString idUserSettings = "UserSettings";
const QString idMeasModeGroup = "MeasMode";

//Названия идентификаторов для записи и чтения файла настроек
const QString idName = "Name";
const QString idMode = "Mode";
const QString idCF_MHz = "CF_MHz";
const QString idStartFreq_MHz = "SAF_MHz";
const QString idStopFreq_MHz = "SBF_MHz";
const QString idSpanFreq_MHz = "SPF_MHz";
const QString idStepFreq_MHz = "STF_MHz";
const QString idAmptRelative = "AMPT_V";
const QString idSweepTime = "TIME_S";
const QString idResBw = "RESBW";
const QString idVideoBw = "VIDEOBW";
const QString idDisplayLine = "LINE";

//Константы ошибок, заголовков сообщение и т.д.
const QString STR_SETTING_DEF_NAME_PREF = "Настройки от ";

const QString MSG_SETTING_NAME = "Название:";
const QString MSG_SETTING_RENAME = "Введите новое название:";
const QString MSG_TITLE_ATTENTION = "Внимание";

const QString MSG_ERR_EMPTY_STR = "Значение названия не может быть пустым";

const QString MSG_WAR_DELETE_ROW = "Вы собираетесь удалить параметры настройки [%1]. Продолжить?";
const QString MSG_WAR_CHANGE_ROW = "Вы собираетесь обновить параметры настройки [%1] текущими. Продолжить?";
const QString MSG_WAR_CLEAR_LIST = "Вы собираетесь очистить весь список настроек. Продолжить?";

}

#endif // CONTROLLERPRESETS_CONST

