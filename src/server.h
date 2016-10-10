/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_SERVER_H
#define ADDON_SERVER_H

#include "shared.h"

class Server : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(GetConectionInfo);
    static NAN_METHOD(GetConectionVarAsUInt64);
    static NAN_METHOD(GetConectionVarAsFloat);
    static NAN_METHOD(GetVars);
    static NAN_METHOD(GetVarAsInt);
    static NAN_METHOD(GetVarAsUInt64);
    static NAN_METHOD(GetVarAsString);
    static NAN_METHOD(SendMessage);
};

#endif // ADDON_SERVER_H
