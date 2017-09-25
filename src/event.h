/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_EVENT_H
#define ADDON_EVENT_H

#include "shared.h"
#include "payload.h"

class Event
{
    static std::map<std::string, Nan::Callback*> m_pool;
    
    static void emit(Payload* p);
    static void exec(uv_async_t* handle, int status);
    static void done(uv_handle_t* handle);
    
public:
    static NAN_METHOD(On);
    
    static void onConnectStatusChangeEvent(uint64 scHandlerID, int status, unsigned int error);
    static void onServerProtocolVersionEvent(uint64 scHandlerID, int protocolVersion);
    static void onNewChannelEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID);
    static void onNewChannelCreatedEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID, anyID invokerID, const char* invokerName, const char* invokerUID);
    static void onDelChannelEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID);
    static void onChannelMoveEvent(uint64 scHandlerID, uint64 channelID, uint64 newChannelPID, anyID invokerID, const char* invokerName, const char* invokerUID);
    static void onUpdateChannelEvent(uint64 scHandlerID, uint64 channelID);
    static void onUpdateChannelEditedEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID);
    static void onUpdateClientEvent(uint64 scHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUID);
    static void onClientMoveEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message);
    static void onClientMoveSubscriptionEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility);
    static void onClientMoveTimeoutEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message);
    static void onClientMoveMovedEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message);
    static void onClientKickFromChannelEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message);
    static void onClientKickFromServerEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message);
    static void onClientIDsEvent(uint64 scHandlerID, const char* clientUID, anyID clientID, const char* clientName);
    static void onClientIDsFinishedEvent(uint64 scHandlerID);
    static void onServerEditedEvent(uint64 scHandlerID, anyID invokerID, const char* invokerName, const char* invokerUID);
    static void onServerUpdatedEvent(uint64 scHandlerID);
    static void onServerErrorEvent(uint64 scHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
    static void onServerStopEvent(uint64 scHandlerID, const char* shutdownMessage);
    static void onTextMessageEvent(uint64 scHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUID, const char* message);
    static void onTalkStatusChangeEvent(uint64 scHandlerID, int status, int isWhisper, anyID clientID);
    static void onIgnoredWhisperEvent(uint64 scHandlerID, anyID clientID);
    static void onConnectionInfoEvent(uint64 scHandlerID, anyID clientID);
    static void onServerConnectionInfoEvent(uint64 scHandlerID);
    static void onChannelSubscribeEvent(uint64 scHandlerID, uint64 channelID);
    static void onChannelSubscribeFinishedEvent(uint64 scHandlerID);
    static void onChannelUnsubscribeEvent(uint64 scHandlerID, uint64 channelID);
    static void onChannelUnsubscribeFinishedEvent(uint64 scHandlerID);
    static void onChannelDescriptionUpdateEvent(uint64 scHandlerID, uint64 channelID);
    static void onChannelPasswordChangedEvent(uint64 scHandlerID, uint64 channelID);
    static void onPlaybackShutdownCompleteEvent(uint64 scHandlerID);
    static void onSoundDeviceListChangedEvent(const char* modeID, int type);
    static void onUserLoggingMessageEvent(const char* message, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* formattedString);
    static void onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remoteSize, uint64 scHandlerID);
    static void onFileListEvent(uint64 scHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompleteSize, const char* returnCode);
    static void onFileListFinishedEvent(uint64 scHandlerID, uint64 channelID, const char* path);
    static void onFileInfoEvent(uint64 scHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime);
};

#endif // ADDON_EVENT_H
