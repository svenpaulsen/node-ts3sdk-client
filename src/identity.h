/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "shared.h"

#ifndef ADDON_IDENTITY_H
#define ADDON_IDENTITY_H

class Identity : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(Create);
    static NAN_METHOD(GetUID);
};

#endif // ADDON_IDENTITY_H
