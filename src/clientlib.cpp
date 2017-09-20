/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "clientlib.h"
#include "error.h"
#include "event.h"

/**
 * Wrapper for ts3client_initClientLib().
 */
NAN_METHOD(ClientLib::Init)
{
    unsigned int error;
    unsigned int logType;
    char*        logPath;
    char*        resPath;
    
    if((error = Argument::num(info, 0, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &logType, LogType_NONE)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &logPath, nullptr)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &resPath, nullptr)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    memset(&clientSDK, 0, sizeof(struct ClientUIFunctions));
    
    clientSDK.onConnectStatusChangeEvent           = Event::onConnectStatusChangeEvent;
    clientSDK.onServerProtocolVersionEvent         = Event::onServerProtocolVersionEvent;
    clientSDK.onNewChannelEvent                    = Event::onNewChannelEvent;
    clientSDK.onNewChannelCreatedEvent             = Event::onNewChannelCreatedEvent;
    clientSDK.onDelChannelEvent                    = Event::onDelChannelEvent;
    clientSDK.onChannelMoveEvent                   = Event::onChannelMoveEvent;
    clientSDK.onUpdateChannelEvent                 = Event::onUpdateChannelEvent;
    clientSDK.onUpdateChannelEditedEvent           = Event::onUpdateChannelEditedEvent;
    clientSDK.onUpdateClientEvent                  = Event::onUpdateClientEvent;
    clientSDK.onClientMoveEvent                    = Event::onClientMoveEvent;
    clientSDK.onClientMoveSubscriptionEvent        = Event::onClientMoveSubscriptionEvent;
    clientSDK.onClientMoveTimeoutEvent             = Event::onClientMoveTimeoutEvent;
    clientSDK.onClientMoveMovedEvent               = Event::onClientMoveMovedEvent;
    clientSDK.onClientKickFromChannelEvent         = Event::onClientKickFromChannelEvent;
    clientSDK.onClientKickFromServerEvent          = Event::onClientKickFromServerEvent;
    clientSDK.onClientIDsEvent                     = Event::onClientIDsEvent;
    clientSDK.onClientIDsFinishedEvent             = Event::onClientIDsFinishedEvent;
    clientSDK.onServerEditedEvent                  = Event::onServerEditedEvent;
    clientSDK.onServerUpdatedEvent                 = Event::onServerUpdatedEvent;
    clientSDK.onServerErrorEvent                   = Event::onServerErrorEvent;
    clientSDK.onServerStopEvent                    = Event::onServerStopEvent;
    clientSDK.onTextMessageEvent                   = Event::onTextMessageEvent;
    clientSDK.onTalkStatusChangeEvent              = Event::onTalkStatusChangeEvent;
    clientSDK.onIgnoredWhisperEvent                = Event::onIgnoredWhisperEvent;
    clientSDK.onConnectionInfoEvent                = Event::onConnectionInfoEvent;
    clientSDK.onServerConnectionInfoEvent          = Event::onServerConnectionInfoEvent;
    clientSDK.onChannelSubscribeEvent              = Event::onChannelSubscribeEvent;
    clientSDK.onChannelSubscribeFinishedEvent      = Event::onChannelSubscribeFinishedEvent;
    clientSDK.onChannelUnsubscribeEvent            = Event::onChannelUnsubscribeEvent;
    clientSDK.onChannelUnsubscribeFinishedEvent    = Event::onChannelUnsubscribeFinishedEvent;
    clientSDK.onChannelDescriptionUpdateEvent      = Event::onChannelDescriptionUpdateEvent;
    clientSDK.onChannelPasswordChangedEvent        = Event::onChannelPasswordChangedEvent;
    clientSDK.onPlaybackShutdownCompleteEvent      = Event::onPlaybackShutdownCompleteEvent;
    clientSDK.onSoundDeviceListChangedEvent        = Event::onSoundDeviceListChangedEvent;
    clientSDK.onUserLoggingMessageEvent            = Event::onUserLoggingMessageEvent;
    clientSDK.onFileTransferStatusEvent            = Event::onFileTransferStatusEvent;
    clientSDK.onFileListEvent                      = Event::onFileListEvent;
    clientSDK.onFileListFinishedEvent              = Event::onFileListFinishedEvent;
    clientSDK.onFileInfoEvent                      = Event::onFileInfoEvent;
    
    if((error = ts3client_initClientLib(&clientSDK, nullptr, logType, logPath, resPath)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_destroyClientLib().
 */
NAN_METHOD(ClientLib::Destroy)
{
    unsigned int error;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_destroyClientLib()) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getClientLibVersion().
 */
NAN_METHOD(ClientLib::GetVersion)
{
    unsigned int error;
    char*        version;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getClientLibVersion(&version)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(version).ToLocalChecked());
    
    ts3client_freeMemory(version);
}

/**
 * Wrapper for ts3client_getClientLibVersionNumber().
 */
NAN_METHOD(ClientLib::GetVersionNumber)
{
    unsigned int error;
    uint64       version;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getClientLibVersionNumber(&version)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(version));
}
