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
    return Error::throwException(ERROR_not_implemented);
}

/**
 * Wrapper for ts3client_getServerConnectionVariableAsUInt64().
 */
NAN_METHOD(Server::GetConectionVarAsUInt64)
{
    return Error::throwException(ERROR_not_implemented);
}


/**
 * Wrapper for ts3client_getServerConnectionVariableAsFloat().
 */
NAN_METHOD(Server::GetConectionVarAsFloat)
{
    return Error::throwException(ERROR_not_implemented);
}


/**
 * Wrapper for ts3client_requestServerVariables().
 */
NAN_METHOD(Server::GetVars)
{
    return Error::throwException(ERROR_not_implemented);
}


/**
 * Wrapper for ts3client_getServerVariableAsInt().
 */
NAN_METHOD(Server::GetVarAsInt)
{
    return Error::throwException(ERROR_not_implemented);
}


/**
 * Wrapper for ts3client_getServerVariableAsUInt64().
 */
NAN_METHOD(Server::GetVarAsUInt64)
{
    return Error::throwException(ERROR_not_implemented);
}


/**
 * Wrapper for ts3client_getServerVariableAsString().
 */
NAN_METHOD(Server::GetVarAsString)
{
    return Error::throwException(ERROR_not_implemented);
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
