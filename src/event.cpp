/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "event.h"

void Event::onConnectStatusChangeEvent(uint64 scHandlerID, int status, unsigned int error)
{
    eventQueue.add(new Callback(__FUNCTION__, "6iI", scHandlerID, status, error));
}

void Event::onServerProtocolVersionEvent(uint64 scHandlerID, int protocolVersion)
{
    eventQueue.add(new Callback(__FUNCTION__, "6i", scHandlerID, protocolVersion));
}

void Event::onNewChannelEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID)
{
    eventQueue.add(new Callback(__FUNCTION__, "666", scHandlerID, channelID, channelPID));
}

void Event::onNewChannelCreatedEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    eventQueue.add(new Callback(__FUNCTION__, "666Iss", scHandlerID, channelID, channelPID, invokerID, invokerName, invokerUID));
}

void Event::onDelChannelEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66Iss", scHandlerID, channelID, invokerID, invokerName, invokerUID));
}

void Event::onChannelMoveEvent(uint64 scHandlerID, uint64 channelID, uint64 newChannelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    eventQueue.add(new Callback(__FUNCTION__, "666Iss", scHandlerID, channelID, newChannelPID, invokerID, invokerName, invokerUID));
}

void Event::onUpdateChannelEvent(uint64 scHandlerID, uint64 channelID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onUpdateChannelEditedEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66Iss", scHandlerID, channelID, invokerID, invokerName, invokerUID));
}

void Event::onUpdateClientEvent(uint64 scHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6IIss", scHandlerID, clientID, invokerID, invokerName, invokerUID));
}

void Event::onClientMoveEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I66is", scHandlerID, clientID, oldChannelID, newChannelID, visibility, message));
}

void Event::onClientMoveSubscriptionEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I66i", scHandlerID, clientID, oldChannelID, newChannelID, visibility));
}

void Event::onClientMoveTimeoutEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I66is", scHandlerID, clientID, oldChannelID, newChannelID, visibility, message));
}

void Event::onClientMoveMovedEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

void Event::onClientKickFromChannelEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

void Event::onClientKickFromServerEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

void Event::onClientIDsEvent(uint64 scHandlerID, const char* clientUID, anyID clientID, const char* clientName)
{
    eventQueue.add(new Callback(__FUNCTION__, "6sIs", scHandlerID, clientUID, clientID, clientName));
}

void Event::onClientIDsFinishedEvent(uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6", scHandlerID));
}

void Event::onServerEditedEvent(uint64 scHandlerID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6Iss", scHandlerID, invokerID, invokerName, invokerUID));
}

void Event::onServerUpdatedEvent(uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6", scHandlerID));
}

void Event::onServerErrorEvent(uint64 scHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage)
{
    eventQueue.add(new Callback(__FUNCTION__, "6sIss", scHandlerID, errorMessage, error, returnCode, extraMessage));
}

void Event::onServerStopEvent(uint64 scHandlerID, const char* shutdownMessage)
{
    eventQueue.add(new Callback(__FUNCTION__, "6s", scHandlerID, shutdownMessage));
}

void Event::onTextMessageEvent(uint64 scHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUID, const char* message)
{
    eventQueue.add(new Callback(__FUNCTION__, "6IIIsss", scHandlerID, targetMode, toID, fromID, fromName, fromUID, message));
}

void Event::onTalkStatusChangeEvent(uint64 scHandlerID, int status, int isWhisper, anyID clientID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6iiI", scHandlerID, status, isWhisper, clientID));
}

void Event::onIgnoredWhisperEvent(uint64 scHandlerID, anyID clientID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I", scHandlerID, clientID));
}

void Event::onConnectionInfoEvent(uint64 scHandlerID, anyID clientID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6I", scHandlerID, clientID));
}

void Event::onServerConnectionInfoEvent(uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6", scHandlerID));
}

void Event::onChannelSubscribeEvent(uint64 scHandlerID, uint64 channelID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onChannelSubscribeFinishedEvent(uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6", scHandlerID));
}

void Event::onChannelUnsubscribeEvent(uint64 scHandlerID, uint64 channelID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onChannelUnsubscribeFinishedEvent(uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6", scHandlerID));
}

void Event::onChannelDescriptionUpdateEvent(uint64 scHandlerID, uint64 channelID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onChannelPasswordChangedEvent(uint64 scHandlerID, uint64 channelID)
{
    eventQueue.add(new Callback(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onPlaybackShutdownCompleteEvent(uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "6", scHandlerID));
}

void Event::onSoundDeviceListChangedEvent(const char* modeID, int type)
{
    eventQueue.add(new Callback(__FUNCTION__, "si", modeID, type));
}

void Event::onEditPlaybackVoiceDataEvent(uint64 scHandlerID, anyID clientID, short* samples, int sampleCount, int channels)
{
    // not implemented
}

void Event::onEditPostProcessVoiceDataEvent(uint64 scHandlerID, anyID clientID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask)
{
    // not implemented
}

void Event::onEditMixedPlaybackVoiceDataEvent(uint64 scHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask)
{
    // not implemented
}

void Event::onEditCapturedVoiceDataEvent(uint64 scHandlerID, short* samples, int sampleCount, int channels, int* edited)
{
    // not implemented
}

void Event::onCustom3dRolloffCalculationClientEvent(uint64 scHandlerID, anyID clientID, float distance, float* volume)
{
    // not implemented
}

void Event::onCustom3dRolloffCalculationWaveEvent(uint64 scHandlerID, uint64 waveHandle, float distance, float* volume)
{
    // not implemented
}

void Event::onUserLoggingMessageEvent(const char* message, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* formattedString)
{
    eventQueue.add(new Callback(__FUNCTION__, "sis6ss", message, logLevel, logChannel, logID, logTime, formattedString));
}

void Event::onCustomPacketEncryptEvent(char** data, unsigned int* size)
{
    // not implemented
}

void Event::onCustomPacketDecryptEvent(char** data, unsigned int* size)
{
    // not implemented
}

void Event::onProvisioningSlotRequestResultEvent(unsigned int error, uint64 requestHandle, const char* connectionKey)
{
    eventQueue.add(new Callback(__FUNCTION__, "I6s", error, requestHandle, connectionKey));
}

void Event::onCheckServerUniqueIdentifierEvent(uint64 scHandlerID, const char* serverUID, int* cancelConnect)
{
    // not implemented
}

void Event::onClientPasswordEncrypt(uint64 scHandlerID, const char* plain, char* encrypted, int size)
{
    eventQueue.add(new Callback(__FUNCTION__, "6ssi", scHandlerID, plain, encrypted, size));
}

void Event::onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remoteSize, uint64 scHandlerID)
{
    eventQueue.add(new Callback(__FUNCTION__, "IIs66", (unsigned int) transferID, status, statusMessage, remoteSize, scHandlerID));
}

void Event::onFileListEvent(uint64 scHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompleteSize, const char* returnCode)
{
    eventQueue.add(new Callback(__FUNCTION__, "66ss66i6s", scHandlerID, channelID, path, name, size, datetime, type, incompleteSize, returnCode));
}

void Event::onFileListFinishedEvent(uint64 scHandlerID, uint64 channelID, const char* path)
{
    eventQueue.add(new Callback(__FUNCTION__, "66s", scHandlerID, channelID, path));
}

void Event::onFileInfoEvent(uint64 scHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime)
{
    eventQueue.add(new Callback(__FUNCTION__, "66s66", scHandlerID, channelID, name, size, datetime));
}
