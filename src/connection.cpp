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
    unsigned int       error;
    uint64             scHandlerID;
    char*              identity;
    char*              host;
    unsigned int       port;
    char*              nickname;
    std::vector<char*> channelArr;
    char*              channelPwd;
    char*              serverPwd;
    
    if((error = Argument::num(info, 3, 8)) != ERROR_ok)
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
    
    if((error = Argument::get(info, 2, &host, "")) != ERROR_ok)
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
 * Wrapper for ts3client_startConnectionWithChannelID().
 */
NAN_METHOD(Connection::StartWithChannelID)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        identity;
    char*        host;
    unsigned int port;
    char*        nickname;
    uint64       channelID;
    char*        channelPwd;
    char*        serverPwd;
    
    if((error = Argument::num(info, 3, 8)) != ERROR_ok)
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
    
    if((error = Argument::get(info, 2, &host, "")) != ERROR_ok)
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
    
    if((error = Argument::get(info, 5, &channelID, 0)) != ERROR_ok)
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
    
    if((error = ts3client_startConnectionWithChannelID(scHandlerID, identity, host, port, nickname, channelID, channelPwd, serverPwd)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
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
    
    if((error = Argument::get(info, 1, &quitMessage, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_stopConnection(scHandlerID, quitMessage)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getServerConnectionHandlerList().
 */
NAN_METHOD(Connection::GetList)
{
    unsigned int error;
    uint64*      scHandlerIDs;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerConnectionHandlerList(&scHandlerIDs)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    int n = 0;
    for(; scHandlerIDs[n]; ++n)
    {}
    
    v8::Local<v8::Array> arr = Nan::New<v8::Array>(n);
    
    for(int i = 0; scHandlerIDs[i]; i++)
    {
        Nan::Set(arr, i, Nan::New<v8::Number>(scHandlerIDs[i]));
    }
    
    info.GetReturnValue().Set(arr);
    
    ts3client_freeMemory(scHandlerIDs);
}

/**
 * Wrapper for ts3client_getConnectionStatus().
 */
NAN_METHOD(Connection::GetStatus)
{
    unsigned int error;
    uint64       scHandlerID;
    int          status;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getConnectionStatus(scHandlerID, &status)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(status));
}

/**
 * Wrapper for ts3client_getConnectionVariableAsUInt64().
 */
NAN_METHOD(Connection::GetInfoVarAsUInt64)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int clientID;
    unsigned int flag;
    uint64       variable;
    
    if((error = Argument::num(info, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getConnectionVariableAsUInt64(scHandlerID, clientID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getConnectionVariableAsDouble().
 */
NAN_METHOD(Connection::GetInfoVarAsDouble)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    unsigned int flag;
    double       variable;
    
    if((error = Argument::num(info, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getConnectionVariableAsDouble(scHandlerID, clientID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getConnectionVariableAsString().
 */
NAN_METHOD(Connection::GetInfoVarAsString)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    unsigned int flag;
    char*        variable;
    
    if((error = Argument::num(info, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getConnectionVariableAsString(scHandlerID, clientID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(variable).ToLocalChecked());
    
    ts3client_freeMemory(variable);
}

/**
 * Wrapper for ts3client_cleanUpConnectionInfo().
 */
NAN_METHOD(Connection::CleanupInfo)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_cleanUpConnectionInfo(scHandlerID, clientID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}
