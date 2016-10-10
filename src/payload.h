/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_PAYLOAD_H
#define ADDON_PAYLOAD_H

#include "shared.h"

class Payload
{
    struct arg {
        unsigned int size;
        char         type;
        void*        data;
    };
    
    std::string       m_name;
    std::string       m_frmt;
    std::vector<arg*> m_args;
    
public:
    Payload(const char* func, const char* frmt, ...);
    ~Payload();
    
    std::string getName();
    std::string getFormat();
    size_t      getLength();
    
private:
    unsigned int getTypeSize(char type);
};

#endif // ADDON_PAYLOAD_H
