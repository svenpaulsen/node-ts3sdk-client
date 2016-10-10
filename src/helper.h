/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_HELPER_H
#define ADDON_HELPER_H

#include "shared.h"

class Helper
{
public:
    static char* createReturnCode(int len = 32);
};

#endif // ADDON_HELPER_H
