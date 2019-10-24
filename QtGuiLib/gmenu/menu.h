// Copyright (C) 2017 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 14.09.2017
//

#ifndef MENU
#define MENU

#include <QtWidgets\QWidget>

namespace Menu
{

class IMenu : public QWidget
{
    Q_OBJECT

public:
    explicit IMenu(QWidget *parent = 0);
    virtual ~IMenu();

    virtual void menuItemEdit(QString text) = 0;
};

} // namespace Menu

#endif // MENU

