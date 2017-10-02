/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "server.h"
#include "error.h"
#include "helper.h"

/**
 * Wrapper for ts3client_requestServerConnectionInfo().
 */
NAN_METHOD(Server::GetConectionInfo)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 1, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestServerConnectionInfo(scHandlerID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_getServerConnectionVariableAsUInt64().
 */
NAN_METHOD(Server::GetConectionVarAsUInt64)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int flag;
    uint64       variable;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerConnectionVariableAsUInt64(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getServerConnectionVariableAsFloat().
 */
NAN_METHOD(Server::GetConectionVarAsFloat)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int flag;
    float        variable;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerConnectionVariableAsFloat(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_requestServerVariables().
 */
NAN_METHOD(Server::GetVars)
{
    unsigned int error;
    uint64       scHandlerID;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestServerVariables(scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getServerVariableAsInt().
 */
NAN_METHOD(Server::GetVarAsInt)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int flag;
    int          variable;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerVariableAsInt(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getServerVariableAsUInt64().
 */
NAN_METHOD(Server::GetVarAsUInt64)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int flag;
    uint64       variable;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerVariableAsUInt64(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getServerVariableAsString().
 */
NAN_METHOD(Server::GetVarAsString)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int flag;
    char*        variable;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerVariableAsString(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(variable).ToLocalChecked());
    
    ts3client_freeMemory(variable);
}

/**
 * Wrapper for ts3client_requestSendServerTextMsg().
 */
NAN_METHOD(Server::SendMessage)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        message;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &message, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestSendServerTextMsg(scHandlerID, message, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}
