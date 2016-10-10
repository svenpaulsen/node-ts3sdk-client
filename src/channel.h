/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_CHANNEL_H
#define ADDON_CHANNEL_H

#include "shared.h"

class Channel : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(GetList);
    static NAN_METHOD(GetClients);
    static NAN_METHOD(GetID);
    static NAN_METHOD(GetPID);
    static NAN_METHOD(GetSecondsEmpty);
    static NAN_METHOD(GetDescription);
    static NAN_METHOD(GetVarAsInt);
    static NAN_METHOD(GetVarAsUInt64);
    static NAN_METHOD(GetVarAsString);
    static NAN_METHOD(SetVarAsInt);
    static NAN_METHOD(SetVarAsUInt64);
    static NAN_METHOD(SetVarAsString);
    static NAN_METHOD(FlushCreation);
    static NAN_METHOD(FlushUpdates);
    static NAN_METHOD(Move);
    static NAN_METHOD(Delete);
    static NAN_METHOD(Subscribe);
    static NAN_METHOD(Unsubscribe);
    static NAN_METHOD(SubscribeAll);
    static NAN_METHOD(UnsubscribeAll);
    static NAN_METHOD(SendMessage);
};

#endif // ADDON_CHANNEL_H
