/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "shared.h"

#ifndef ADDON_CAPTURE_H
#define ADDON_CAPTURE_H

class Capture : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(OpenDevice);
    static NAN_METHOD(CloseDevice);
    static NAN_METHOD(ActivateDevice);
    static NAN_METHOD(SetLocalTestMode);
    static NAN_METHOD(ListDevices);
    static NAN_METHOD(ListModes);
};

#endif // ADDON_CAPTURE_H
