/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_CONNECTION_H
#define ADDON_CONNECTION_H

#include "shared.h"

class Connection : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(Init);
    static NAN_METHOD(Destroy);
    static NAN_METHOD(Start);
    static NAN_METHOD(StartWithChannelID);
    static NAN_METHOD(Stop);
    static NAN_METHOD(GetList);
    static NAN_METHOD(GetStatus);
    static NAN_METHOD(GetInfoVarAsUInt64);
    static NAN_METHOD(GetInfoVarAsDouble);
    static NAN_METHOD(GetInfoVarAsString);
    static NAN_METHOD(CleanupInfo);
};

#endif // ADDON_CONNECTION_H
