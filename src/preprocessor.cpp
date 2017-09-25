/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "error.h"
#include "helper.h"
#include "preprocessor.h"

/**
 * Wrapper for ts3client_getPreProcessorInfoValueFloat().
 */
NAN_METHOD(Preprocessor::GetInfoValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    float        val;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getPreProcessorInfoValueFloat(scHandlerID, key, &val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(val));
}

/**
 * Wrapper for ts3client_getPreProcessorConfigValue().
 */
NAN_METHOD(Preprocessor::GetConfigValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    char*        val;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getPreProcessorConfigValue(scHandlerID, key, &val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(val).ToLocalChecked());
    
    ts3client_freeMemory(val);
}

/**
 * Wrapper for ts3client_setPreProcessorConfigValue().
 */
NAN_METHOD(Preprocessor::SetConfigValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    char*        val;
    
    if((error = Argument::num(info, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &val, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setPreProcessorConfigValue(scHandlerID, key, val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getEncodeConfigValue().
 */
NAN_METHOD(Preprocessor::GetEncoderValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    char*        val;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getEncodeConfigValue(scHandlerID, key, &val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(val).ToLocalChecked());
    
    ts3client_freeMemory(val);
}
