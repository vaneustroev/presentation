// Copyright (C) 2015 GAMMA All Rights Reserved.
// Author: Vladimir Neustroev
//
// @file
// Created: 07.09.2015
//

#ifndef KEYPADNEW_H
#define KEYPADNEW_H

#include <QWidget>

namespace Ui {
class KeyPadNew;
}

namespace Pad {

class KeyPadNew : public QWidget
{
    Q_OBJECT

public:
    explicit KeyPadNew(QWidget *parent = 0);
    ~KeyPadNew();

private:
    Ui::KeyPadNew *ui;
};

} // namespace Pad

#endif // KEYPADNEW_H

