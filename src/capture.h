/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_CAPTURE_H
#define ADDON_CAPTURE_H

#include "shared.h"

class Capture : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(OpenDevice);
    static NAN_METHOD(CloseDevice);
    static NAN_METHOD(ActivateDevice);
    static NAN_METHOD(SetLocalTestMode);
    static NAN_METHOD(ListDevices);
    static NAN_METHOD(GetCurrentDevice);
    static NAN_METHOD(GetCurrentMode);
    static NAN_METHOD(ListModes);
    static NAN_METHOD(GetInfoValue);
    static NAN_METHOD(GetConfigValue);
    static NAN_METHOD(SetConfigValue);
    static NAN_METHOD(GetEncoderValue);
};

#endif // ADDON_CAPTURE_H
