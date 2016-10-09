/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "shared.h"

#ifndef ADDON_CALLBACK_H
#define ADDON_CALLBACK_H

class Callback
{
    struct arg {
        unsigned int size;
        char         type;
        void*        data;
    };
    
    string       m_name;
    string       m_frmt;
    vector<arg*> m_args;
    
public:
    Callback(const char* func, const char* frmt, ...);
    
    string getName();
    string getFormat();
    size_t getLength();
    
private:
    unsigned int getTypeSize(char type);
};

#endif // ADDON_CALLBACK_H
