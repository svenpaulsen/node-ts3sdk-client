/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "connection.h"
#include "error.h"

/**
 * Wrapper for ts3client_spawnNewServerConnectionHandler().
 */
NAN_METHOD(Connection::Init)
{
    unsigned int error;
    unsigned int port;
    uint64       scHandlerID;
    
    if((error = Argument::num(info, 0, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &port, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_spawnNewServerConnectionHandler(port, &scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(scHandlerID));
}

/**
 * Wrapper for ts3client_destroyServerConnectionHandler().
 */
NAN_METHOD(Connection::Destroy)
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
    
    if((error = ts3client_destroyServerConnectionHandler(scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_startConnection().
 */
NAN_METHOD(Connection::Start)
{
    unsigned int  error;
    uint64        scHandlerID;
    char*         identity;
    char*         host;
    unsigned int  port;
    char*         nickname;
    vector<char*> channelArr;
    char*         channelPwd;
    char*         serverPwd;
    
    if((error = Argument::num(info, 2, 8)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &identity, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &host, "localhost")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &port, 9987)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &nickname, "TeamSpeak User")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 5, channelArr, nullptr)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 6, &channelPwd, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 7, &serverPwd, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }

    if((error = ts3client_startConnection(scHandlerID, identity, host, port, nickname, channelArr.empty() ? nullptr : (const char**) channelArr.data(), channelPwd, serverPwd)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    for(int i = 0; i < (int) channelArr.size(); ++i)
    {
        free(channelArr[i]);
    }
    
    channelArr.clear();
}

/**
 * Wrapper for ts3client_stopConnection().
 */
NAN_METHOD(Connection::Stop)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        quitMessage;
    
    if((error = Argument::num(info, 1, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &quitMessage, "leaving")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_stopConnection(scHandlerID, quitMessage)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}
