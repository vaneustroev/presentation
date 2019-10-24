// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: van
//
// @file   dialogsystemsettings2.h
// Created: 12.04.2017
//

#ifndef DIALOGSYSTEMSETTINGS2_H
#define DIALOGSYSTEMSETTINGS2_H

#include <QtWidgets\QDialog>

namespace Ui {
class DialogSystemSettings2;
}

class DialogSystemSettings2 : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSystemSettings2(QWidget *parent = 0);
    ~DialogSystemSettings2();

public slots:
    void clickedSystem(void);
    void clickedConfig(void);
    void clickedUserInterface(void);
    void clickedPowerOn(void);
    void clickedRestoreDefault(void);
    void clickedAlignments(void);
    void clickedLicensing(void);
    void clickedSecurity(void);
    void clickedDiagnostics(void);
    void clickedService(void);
    void clickedHelp(void);
    void clickedExit(void);

private:
    Ui::DialogSystemSettings2 *ui;
};

#endif // DIALOGSYSTEMSETTINGS2_H
