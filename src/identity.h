/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_IDENTITY_H
#define ADDON_IDENTITY_H

#include "shared.h"

class Identity : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(Create);
    static NAN_METHOD(GetUID);
};

#endif // ADDON_IDENTITY_H
