/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "error.h"

unsigned int Error::m_lastCode    = ERROR_ok;
std::string  Error::m_lastMessage = Error::translateCode(ERROR_ok);

/**
 * Translates a specified error code into an error message.
 */
std::string Error::translateCode(unsigned int code)
{
    char* result;
    
    ts3client_getErrorMessage(code, &result);
    
    std::string message(result);
    
    ts3client_freeMemory(result);
    
    return message;
}

/**
 * Throws an exception object with a translated error message in the current V8 context.
 */
void Error::throwException(unsigned int code)
{
    m_lastCode    = code;
    m_lastMessage = translateCode(code);
    
    Nan::ThrowError(m_lastMessage.data());
}

/**
 * Returns the error code from the last thrown exception.
 */
NAN_METHOD(Error::GetLastCode)
{
    info.GetReturnValue().Set(Nan::New<v8::Number>(m_lastCode));
}

/**
 * Returns the error message from the last thrown exception.
 */
NAN_METHOD(Error::GetLastMessage)
{
    info.GetReturnValue().Set(Nan::New(m_lastMessage.data()).ToLocalChecked());
}

/**
 * Wrapper for ts3client_getErrorMessage()
 */
NAN_METHOD(Error::GetMessage)
{
    unsigned int error;
    unsigned int code;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return throwException(error);
    }
    
    if((error = Argument::get(info, 0, &code, ERROR_undefined)) != ERROR_ok)
    {
        return throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(translateCode(code).data()).ToLocalChecked());
}
