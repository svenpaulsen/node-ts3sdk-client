/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "shared.h"

#ifndef ADDON_PLAYBACK_H
#define ADDON_PLAYBACK_H

class Playback : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(OpenDevice);
    static NAN_METHOD(CloseDevice);
    static NAN_METHOD(ShutdownDevice);
    static NAN_METHOD(PlayWaveFile);
    static NAN_METHOD(ListDevices);
    static NAN_METHOD(GetCurrentDevice);
    static NAN_METHOD(GetCurrentMode);
    static NAN_METHOD(ListModes);
    static NAN_METHOD(SetConfigValue);
    static NAN_METHOD(GetConfigValue);
};

#endif // ADDON_CAPTURE_H
