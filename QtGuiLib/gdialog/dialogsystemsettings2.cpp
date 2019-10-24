// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: van
//
// @file   dialogsystemsettings2.cpp
// Created: 12.04.2017
//

#include "dialogsystemsettings2.h"
#include "ui_dialogsystemsettings2.h"

DialogSystemSettings2::DialogSystemSettings2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemSettings2)
{
    ui->setupUi(this);

    connect(ui->buttonSystem, SIGNAL(clicked()), this, SLOT(clickedSystem()));
    connect(ui->buttonConfig, SIGNAL(clicked()), this, SLOT(clickedConfig()));
    connect(ui->buttonUserInterface, SIGNAL(clicked()), this, SLOT(clickedUserInterface()));
    connect(ui->buttonPowerOn, SIGNAL(clicked()), this, SLOT(clickedPowerOn()));
    connect(ui->buttonRestoreDefault, SIGNAL(clicked()), this, SLOT(clickedRestoreDefault()));
    connect(ui->buttonAlignments, SIGNAL(clicked()), this, SLOT(clickedAlignments()));
    connect(ui->buttonLicensing, SIGNAL(clicked()), this, SLOT(clickedLicensing()));
    connect(ui->buttonSecurity, SIGNAL(clicked()), this, SLOT(clickedSecurity()));
    connect(ui->buttonDiagnostics, SIGNAL(clicked()), this, SLOT(clickedDiagnostics()));
    connect(ui->buttonService, SIGNAL(clicked()), this, SLOT(clickedService()));
    connect(ui->buttonHelp, SIGNAL(clicked()), this, SLOT(clickedHelp()));
    connect(ui->buttonExit, SIGNAL(clicked()), this, SLOT(clickedExit()));

    //QPushButton *button1 = new QPushButton(this);
    //QPushButton *button2 = new QPushButton(this);
    //ui->stackedSystem->addWidget(button1);
    //ui->stackedSystem->addWidget(button2);
    //ui->stackedSystem->setCurrentIndex(2);
}

DialogSystemSettings2::~DialogSystemSettings2()
{
    delete ui;
}

void DialogSystemSettings2::clickedSystem(void)
{
    ui->stackedSystem->setCurrentIndex(0);
}

void DialogSystemSettings2::clickedConfig(void)
{
    ui->stackedSystem->setCurrentIndex(1);
}

void DialogSystemSettings2::clickedUserInterface(void)
{
    ui->stackedSystem->setCurrentIndex(2);
}

void DialogSystemSettings2::clickedPowerOn(void)
{
    ui->stackedSystem->setCurrentIndex(3);
}

void DialogSystemSettings2::clickedRestoreDefault(void)
{
    ui->stackedSystem->setCurrentIndex(4);
}

void DialogSystemSettings2::clickedAlignments(void)
{
    ui->stackedSystem->setCurrentIndex(5);
}

void DialogSystemSettings2::clickedLicensing(void)
{
    ui->stackedSystem->setCurrentIndex(6);
}

void DialogSystemSettings2::clickedSecurity(void)
{
    ui->stackedSystem->setCurrentIndex(7);
}

void DialogSystemSettings2::clickedDiagnostics(void)
{
    ui->stackedSystem->setCurrentIndex(8);
}

void DialogSystemSettings2::clickedService(void)
{
    ui->stackedSystem->setCurrentIndex(9);
}

void DialogSystemSettings2::clickedHelp(void)
{
    ;
}

void DialogSystemSettings2::clickedExit(void)
{
    this->close();
}

