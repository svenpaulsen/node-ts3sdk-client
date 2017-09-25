/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_PREPROCESSOR_H
#define ADDON_PREPROCESSOR_H

#include "shared.h"

class Preprocessor : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(GetInfoValue);
    static NAN_METHOD(GetConfigValue);
    static NAN_METHOD(SetConfigValue);
    static NAN_METHOD(GetEncoderValue);
};

#endif // ADDON_PREPROCESSOR_H
