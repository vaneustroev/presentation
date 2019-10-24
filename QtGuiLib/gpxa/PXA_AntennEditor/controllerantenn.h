#ifndef CONTROLLERANTENN_H
#define CONTROLLERANTENN_H

#include <QString>
#include <QMenu>
#include <ui_editantenn.h>

#include "controllerantenn_const.h"
#include "Table/tabledataantenn.h"
#include "Table/menuheader.h"
#include "Table/antennitemdelegate.h"
#include "../Utilites/Math/utilites_math.h"
#include "../Utilites/Files/systemfolders.h"
#include "../Patterns/singleton.h"

//using namespace CTRL_Antenn;
//using namespace Utilites_Math;

namespace Table {

class ControllerAntennMain : public QObject
{
    Q_OBJECT
private:
  friend class Table::Singleton<SystemFolders>;
    Ui_EditAntennDialog ui;
    QString filenameAntenn;
    QString filename_activeAntenn;
    TableDataAntenn *tableAntenn;
    AntennItem *activeAntenn;
    AntennItem activeAntennTemp;
    int activeAntenn_num;
    QString activeAntenn_name;
    QString activeAntenn_sn;
    QDialog *dialog;
    void UpdateActiveAntennName();
    void UpdateMainButtonsEnabled();
    void UpdateKoefButtonsEnabled();
    void SaveActiveAntenn();
    void LoadActiveAntenn();
public:
    ControllerAntennMain( );
    bool eventFilter( QObject* object, QEvent* event );
    QString GetActiveAntennName( bool *antennValid );       //получить название активного оконечного устройства
    double GetActiveAntennKoef_dB( double Freq_MHz );       //получить коэффициент на требуемой частоте активного оконечного устройства
    void ShowEditWindow();                                  //показать форму редактирования
private slots:
    void ActivateAnt();
    void ItemSelect( const QModelIndex &index );
    void ItemKoefSelect( const QModelIndex &index );
    void SortTable();
    void AddAntenn();
    void RemoveAntenn();
    void InsertAntenn();
    void ClearList();
    void Check();
    void AddKoef();
    void RemoveKoef();
    void InsertKoef();
    void ClearKoef();
    void SortKoef();
    void CancelChange();
    void ApplyChange();
};

} //namespace Table

// *** Контроллер системных папок ***
//#define ControllerAntenn /*ControllerAntennMain;//*/Singleton<ControllerAntennMain>::instance()
#define ControllerAntenn Table::Singleton<Table::ControllerAntennMain>::instance()

#endif // CONTROLLERANTENN_H
