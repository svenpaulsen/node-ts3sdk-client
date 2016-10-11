/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "channel.h"
#include "error.h"
#include "helper.h"

/**
 * Wrapper for ts3client_getChannelList().
 */
NAN_METHOD(Channel::GetList)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64*      channels;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelList(scHandlerID, &channels)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    int n = 0;
    for(; channels[n]; ++n)
    {}
    
    v8::Local<v8::Array> arr = Nan::New<v8::Array>(n);
    
    for(int i = 0; channels[i]; i++)
    {
        Nan::Set(arr, i, Nan::New<v8::Number>(channels[i]));
    }
    
    info.GetReturnValue().Set(arr);
    
    ts3client_freeMemory(channels);
}

/**
 * Wrapper for ts3client_getChannelClientList().
 */
NAN_METHOD(Channel::GetClients)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    anyID*       clients;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelClientList(scHandlerID, channelID, &clients)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    int n = 0;
    for(; clients[n]; ++n)
    {}
    
    v8::Local<v8::Array> arr = Nan::New<v8::Array>(n);
    
    for(int i = 0; clients[i]; i++)
    {
        Nan::Set(arr, i, Nan::New<v8::Number>(clients[i]));
    }
    
    info.GetReturnValue().Set(arr);
    
    ts3client_freeMemory(clients);
}

/**
 * Wrapper for ts3client_getChannelIDFromChannelNames().
 */
NAN_METHOD(Channel::GetID)
{
    unsigned int       error;
    uint64             scHandlerID;
    std::vector<char*> channelArr;
    uint64             channelID;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, channelArr, nullptr)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelIDFromChannelNames(scHandlerID, channelArr.data(), &channelID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(channelID));
    
    for(int i = 0; i < (int) channelArr.size(); ++i)
    {
        free(channelArr[i]);
    }
    
    channelArr.clear();
}

/**
 * Wrapper for ts3client_getParentChannelOfChannel().
 */
NAN_METHOD(Channel::GetPID)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    uint64       channelPID;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getParentChannelOfChannel(scHandlerID, channelID, &channelPID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(channelPID));
}

/**
 * Wrapper for ts3client_getChannelEmptySecs().
 */
NAN_METHOD(Channel::GetSecondsEmpty)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    int          seconds;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelEmptySecs(scHandlerID, channelID, &seconds)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(seconds));
}

/**
 * Wrapper for ts3client_requestChannelDescription().
 */
NAN_METHOD(Channel::GetDescription)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
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
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestChannelDescription(scHandlerID, channelID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_getChannelVariableAsInt().
 */
NAN_METHOD(Channel::GetVarAsInt)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    unsigned int flag;
    int          variable;
    
    if((error = Argument::num(info, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelVariableAsInt(scHandlerID, channelID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getChannelVariableAsUInt64().
 */
NAN_METHOD(Channel::GetVarAsUInt64)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
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
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelVariableAsUInt64(scHandlerID, channelID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getChannelVariableAsString().
 */
NAN_METHOD(Channel::GetVarAsString)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
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
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getChannelVariableAsString(scHandlerID, channelID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(variable).ToLocalChecked());
    
    ts3client_freeMemory(variable);
}

/**
 * Wrapper for ts3client_setChannelVariableAsInt().
 */
NAN_METHOD(Channel::SetVarAsInt)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    unsigned int flag;
    int          variable;
    
    if((error = Argument::num(info, 4)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &variable, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setChannelVariableAsUInt64(scHandlerID, channelID, flag, variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setChannelVariableAsUInt64().
 */
NAN_METHOD(Channel::SetVarAsUInt64)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    unsigned int flag;
    uint64       variable;
    
    if((error = Argument::num(info, 4)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &variable, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setChannelVariableAsUInt64(scHandlerID, channelID, flag, variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setChannelVariableAsString().
 */
NAN_METHOD(Channel::SetVarAsString)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    unsigned int flag;
    char*        variable;
    
    if((error = Argument::num(info, 4)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &variable, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setChannelVariableAsString(scHandlerID, channelID, flag, variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    ts3client_freeMemory(variable);
}

/**
 * Wrapper for ts3client_flushChannelCreation().
 */
NAN_METHOD(Channel::FlushCreation)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelPID;
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
    
    if((error = Argument::get(info, 1, &channelPID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_flushChannelCreation(scHandlerID, channelPID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_flushChannelUpdates().
 */
NAN_METHOD(Channel::FlushUpdates)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
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
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_flushChannelUpdates(scHandlerID, channelID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestChannelMove().
 */
NAN_METHOD(Channel::Move)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    uint64       newChannelPID;
    uint64       newChannelOrder;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 5)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &newChannelPID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &newChannelOrder, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestChannelMove(scHandlerID, channelID, newChannelPID, newChannelOrder, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestChannelDelete().
 */
NAN_METHOD(Channel::Delete)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    int          force;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 4)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &force, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestChannelDelete(scHandlerID, channelID, force, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestChannelSubscribe().
 */
NAN_METHOD(Channel::Subscribe)
{
    unsigned int        error;
    uint64              scHandlerID;
    std::vector<uint64> channels;
    char*               returnCode;
    char*               defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, channels, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestChannelSubscribe(scHandlerID, channels.data(), returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestChannelUnsubscribe().
 */
NAN_METHOD(Channel::Unsubscribe)
{
    unsigned int        error;
    uint64              scHandlerID;
    std::vector<uint64> channels;
    char*               returnCode;
    char*               defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, channels, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestChannelSubscribe(scHandlerID, channels.data(), returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestChannelSubscribeAll().
 */
NAN_METHOD(Channel::SubscribeAll)
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
    
    if((error = ts3client_requestChannelSubscribeAll(scHandlerID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestChannelUnsubscribeAll().
 */
NAN_METHOD(Channel::UnsubscribeAll)
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
    
    if((error = ts3client_requestChannelUnsubscribeAll(scHandlerID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestSendChannelTextMsg().
 */
NAN_METHOD(Channel::SendMessage)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        message;
    uint64       channelID;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 3, 4)) != ERROR_ok)
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
    
    if((error = Argument::get(info, 2, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestSendChannelTextMsg(scHandlerID, message, channelID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}
