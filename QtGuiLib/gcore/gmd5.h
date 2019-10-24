// Copyright (C) 2016 GAMMA All Rights Reserved.
// Author: vaneustroev
//
// @file
// Created: 22.08.2016
//

#ifndef GMD5_H
#define GMD5_H

#include "gutilities/MD5.h"

namespace Util {

class gmd5
{
public:
    gmd5();
    ~gmd5();

    int md5string(char *str, unsigned char Hash1[16]);

};

} // namespace Util

#endif // GMD5_H

