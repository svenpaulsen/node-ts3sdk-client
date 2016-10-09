/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "callback.h"

/**
 * The Callback object constructor.
 */
Callback::Callback(const char* name, const char* frmt, ...)
{
    string m_name(name);
    string m_frmt(frmt);
    
    uint64       arg_6;
    unsigned int arg_I;
    int          arg_i;
    double       arg_f;
    string       arg_s;
    
    if(m_name.length())
    {
        va_list vl;
        va_start(vl, frmt);
        
        for(unsigned int i = 0; i < m_name.length(); ++i)
        {
            arg* item = (arg*) malloc(sizeof(arg));
            
            item->type = m_frmt[i];
            item->size = getTypeSize(m_frmt[i]);
            item->data = (void*) malloc(item->size);
            
            switch(m_frmt[i])
            {
                case '6':
                    arg_6 = va_arg(vl, uint64);
                    memcpy(item->data, &arg_6, item->size);
                    break;
                    
                case 'I':
                    arg_I = va_arg(vl, unsigned int);
                    memcpy(item->data, &arg_I, item->size);
                    break;
                    
                case 'i':
                    arg_i = va_arg(vl, int);
                    memcpy(item->data, &arg_i, item->size);
                    break;
                    
                case 'f':
                    arg_f = va_arg(vl, double);
                    memcpy(item->data, &arg_f, item->size);
                    break;
                    
                case 's':
                    arg_s = string(va_arg(vl, char*));
                    memcpy(item->data, &arg_s, item->size);
                    break;
                    
                default:
                    item->data = nullptr;
                    break;
            }
            
            m_args.push_back(item);
        }
    }
}

/**
 * The Callback object destructor.
 */
Callback::~Callback()
{
    for(int i = 0; i < (int) m_args.size(); ++i)
    {
        free(m_args[i]->data);
        free(m_args[i]);
    }
}

/**
 * Returns the underlying event name.
 */
string Callback::getName()
{
    return m_name;
}

/**
 * Returns the underlying event format.
 */
string Callback::getFormat()
{
    return m_frmt;
}

/**
 * Returns the number of arguments attached.
 */
size_t Callback::getLength()
{
    return m_frmt.length();
}

/**
 * Returns the size for a specified datatype identifier.
 */
unsigned int Callback::getTypeSize(char type)
{
    switch(type)
    {
        case '6':
            return sizeof(uint64);
            break;
            
        case 'I':
            return sizeof(unsigned int);
            break;
            
        case 'i':
            return sizeof(int);
            break;
            
        case 'f':
            return sizeof(double);
            break;
            
        case 's':
            return sizeof(string);
            break;
            
        default:
            return 0;
    }
}
