/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "log.h"
#include "error.h"

/**
 * Wrapper for ts3client_logMessage().
 */
NAN_METHOD(Log::AddMessage)
{
    unsigned int error;
    char*        logMessage;
    unsigned int logLevel;
    char*        logChannel;
    uint64       scHandlerID;
    
    if((error = Argument::num(info, 1, 4)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &logMessage, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &logLevel, LogLevel_INFO)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &logChannel, "Node.js")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_logMessage(logMessage, (enum LogLevel) logLevel, logChannel, scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setLogVerbosity().
 */
NAN_METHOD(Log::SetVerbosity)
{
    unsigned int error;
    unsigned int logLevel;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &logLevel, LogLevel_INFO)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setLogVerbosity((enum LogLevel) logLevel)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}
