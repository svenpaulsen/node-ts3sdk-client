/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "shared.h"

struct ClientUIFunctions clientSDK;

void freeMemory(void* ptr)
{
    if (ptr != nullptr)
        free(ptr);
}
