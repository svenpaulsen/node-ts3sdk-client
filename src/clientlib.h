/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_CLIENTLIB_H
#define ADDON_CLIENTLIB_H

#include "shared.h"

class ClientLib : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(Init);
    static NAN_METHOD(Destroy);
    static NAN_METHOD(GetVersion);
    static NAN_METHOD(GetVersionNumber);
};

#endif // ADDON_CLIENTLIB_H
