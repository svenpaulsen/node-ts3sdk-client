/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "shared.h"

#ifndef ADDON_ERROR_H
#define ADDON_ERROR_H

class Error : public Nan::ObjectWrap
{
    static unsigned int m_lastCode;
    static string       m_lastMessage;
    
public:
    static string translateCode(unsigned int code);
    static void   throwException(unsigned int code);
    
    static NAN_METHOD(GetLastCode);
    static NAN_METHOD(GetLastMessage);
    static NAN_METHOD(GetMessage);
};

#endif // ADDON_ERROR_H
