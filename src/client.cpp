/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "client.h"
#include "error.h"
#include "helper.h"

/**
 * Wrapper for ts3client_getClientID().
 */
NAN_METHOD(Client::GetOwnID)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getClientID(scHandlerID, &clientID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(clientID));
}

/**
 * Wrapper for ts3client_getClientSelfVariableAsInt().
 */
NAN_METHOD(Client::GetOwnVarAsInt)
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
    
    if((error = ts3client_getClientSelfVariableAsInt(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getClientSelfVariableAsString().
 */
NAN_METHOD(Client::GetOwnVarAsString)
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
    
    if((error = ts3client_getClientSelfVariableAsString(scHandlerID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(variable).ToLocalChecked());
    
    ts3client_freeMemory(variable);
}

/**
 * Wrapper for ts3client_setClientSelfVariableAsInt().
 */
NAN_METHOD(Client::SetOwnVarAsInt)
{
    unsigned int error;
    uint64       scHandlerID;
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
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &variable, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setClientSelfVariableAsInt(scHandlerID, flag, variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setClientSelfVariableAsString().
 */
NAN_METHOD(Client::SetOwnVarAsString)
{
    unsigned int error;
    uint64       scHandlerID;
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
    
    if((error = Argument::get(info, 1, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &variable, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setClientSelfVariableAsString(scHandlerID, flag, variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getClientList().
 */
NAN_METHOD(Client::GetList)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID*       clients;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getClientList(scHandlerID, &clients)) != ERROR_ok)
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
 * Wrapper for ts3client_requestClientIDs().
 */
NAN_METHOD(Client::GetClones)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        clientUID;
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
    
    if((error = Argument::get(info, 1, &clientUID, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestClientIDs(scHandlerID, clientUID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_getChannelOfClient().
 */
NAN_METHOD(Client::GetChannelID)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    uint64       channelID;
    
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
    
    if((error = ts3client_getChannelOfClient(scHandlerID, clientID, &channelID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(channelID));
}

/**
 * Wrapper for ts3client_requestConnectionInfo().
 */
NAN_METHOD(Client::GetConectionInfo)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
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
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestConnectionInfo(scHandlerID, clientID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestClientVariables().
 */
NAN_METHOD(Client::GetVars)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
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
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestClientVariables(scHandlerID, clientID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_getClientVariableAsInt().
 */
NAN_METHOD(Client::GetVarAsInt)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
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
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &flag, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getClientVariableAsInt(scHandlerID, clientID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getClientVariableAsUInt64().
 */
NAN_METHOD(Client::GetVarAsUInt64)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
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
    
    if((error = ts3client_getClientVariableAsUInt64(scHandlerID, clientID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(variable));
}

/**
 * Wrapper for ts3client_getClientVariableAsString().
 */
NAN_METHOD(Client::GetVarAsString)
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
    
    if((error = ts3client_getClientVariableAsString(scHandlerID, clientID, flag, &variable)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(variable).ToLocalChecked());
    
    ts3client_freeMemory(variable);
}

/**
 * Wrapper for ts3client_flushClientSelfUpdates().
 */
NAN_METHOD(Client::FlushUpdates)
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
    
    if((error = ts3client_flushClientSelfUpdates(scHandlerID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestMuteClients().
 */
NAN_METHOD(Client::Mute)
{
    unsigned int       error;
    uint64             scHandlerID;
    std::vector<anyID> clients;
    char*              returnCode;
    char*              defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }

    if((error = Argument::get(info, 1, clients, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestMuteClients(scHandlerID, (anyID*) clients.data(), returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestUnmuteClients().
 */
NAN_METHOD(Client::Unmute)
{
    unsigned int       error;
    uint64             scHandlerID;
    std::vector<anyID> clients;
    char*              returnCode;
    char*              defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 2, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }

    if((error = Argument::get(info, 1, clients, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestUnmuteClients(scHandlerID, (anyID*) clients.data(), returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestClientMove().
 */
NAN_METHOD(Client::Move)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    uint64       channelID;
    char*        password;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 3, 5)) != ERROR_ok)
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
    
    if((error = Argument::get(info, 2, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &password, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestClientMove(scHandlerID, clientID, channelID, password, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestClientKickFromChannel().
 */
NAN_METHOD(Client::KickFromChannel)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    char*        reason;
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
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &reason, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestClientKickFromChannel(scHandlerID, clientID, reason, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestClientKickFromServer().
 */
NAN_METHOD(Client::KickFromServer)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    char*        reason;
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
    
    if((error = Argument::get(info, 1, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &reason, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestClientKickFromServer(scHandlerID, clientID, reason, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestSendPrivateTextMsg().
 */
NAN_METHOD(Client::SendMessage)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        message;
    anyID        clientID;
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
    
    if((error = Argument::get(info, 2, &clientID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestSendPrivateTextMsg(scHandlerID, message, clientID, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_startVoiceRecording().
 */
NAN_METHOD(Client::SetRecordingStatus)
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
    
    if((error = ts3client_startVoiceRecording(scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_stopVoiceRecording().
 */
NAN_METHOD(Client::UnsetRecordingStatus)
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
    
    if((error = ts3client_stopVoiceRecording(scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_requestClientSetWhisperList().
 */
NAN_METHOD(Client::SetWhisperList)
{
    unsigned int        error;
    uint64              scHandlerID;
    anyID               clientID;
    std::vector<uint64> channels;
    std::vector<anyID>  clients;
    char*               returnCode;
    char*               defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 1, 5)) != ERROR_ok)
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

    if((error = Argument::get(info, 2, channels, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }

    if((error = Argument::get(info, 3, clients, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestClientSetWhisperList(scHandlerID, clientID, channels.empty() ? nullptr : channels.data(), clients.empty() ? nullptr : clients.data(), returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_allowWhispersFrom().
 */
NAN_METHOD(Client::AllowWhispersFrom)
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
    
    if((error = ts3client_allowWhispersFrom(scHandlerID, clientID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_removeFromAllowedWhispersFrom().
 */
NAN_METHOD(Client::PreventWhispersFrom)
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
    
    if((error = ts3client_removeFromAllowedWhispersFrom(scHandlerID, clientID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setClientVolumeModifier().
 */
NAN_METHOD(Client::SetVolumeModifier)
{
    unsigned int error;
    uint64       scHandlerID;
    anyID        clientID;
    float        val;
    
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

    if((error = Argument::get(info, 2, &val, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setClientVolumeModifier(scHandlerID, clientID, val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}
