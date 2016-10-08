/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_LOG_H
#define ADDON_LOG_H

#include "shared.h"

class Log : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(AddMessage);
    static NAN_METHOD(SetVerbosity);
};

#endif // ADDON_LOG_H
