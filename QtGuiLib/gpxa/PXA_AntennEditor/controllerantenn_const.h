#ifndef CONTROLLERANTENN_CONST
#define CONTROLLERANTENN_CONST

#include <QString>

namespace CTRL_Antenn {

//Названия файлов для хранения настроек
const QString ANTENN_FILE_NAME = "antenn.cof";
const QString ACTIVE_ANTENN_FILE_NAME = "input.cof";
//Названия секция для файла
const QString Sec_ActiveAnt = "Ant";
const QString Key_ActiveAnt_Name = "Name";
const QString Key_ActiveAnt_SN = "SN";
const QString Key_ActiveAnt_IDN = "N";

//Константы ошибок, заголовков сообщение и т.д.
const QString MSG_TITLE_ATTENTION = "Внимание";

const QString MSG_WAR_DELETE_ROW = "Вы собираетесь удалить оконечное устройство [%1]. Продолжить?";
const QString MSG_WAR_DELETE_ROW_KOEF = "Вы собираетесь удалить коэффициент на частоте [%1] оконечного устройства [%2]. Продолжить?";
const QString MSG_WAR_CLEAR_LIST = "Вы собираетесь очистить всю таблицу оконечных устройств. Продолжить?";
const QString MSG_WAR_CLEAR_LIST_KOEF = "Вы собираетесь очистить всю таблицу коэффициентов оконечного устройства [%1]. Продолжить?";

const QString MSG_ERR_KOEF_DOUBLE = "[%1]. Частота коэффициента калибровки [%2] обнаружена повторно";
const QString MSG_ERR_KOEF_EMPTY = "[%1]. Таблица коэффициентов калибровки пуста";
const QString MSG_ERR_KOEF_2COUNT = "[%1]. Таблица коэффициентов калибровки должна содержать как минимум две частоты";
const QString MSG_ERR_ANT_ERROR = "Оконечное устройство [%1] содержит ошибки и не может быть выбрано активным.";
const QString MSG_WAR_ACT_ANT_NOT_VALID = "Оконечное устройство [%1] содержит ошибки.\n"
                                          "Повтор - для изменения активного оконечного устройства.\n"
                                          "Игнорировать - для отказа от использования оконечного устройства";
}

#endif // CONTROLLERANTENN_CONST

