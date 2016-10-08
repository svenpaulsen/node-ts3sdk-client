/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "event.h"

void Event::onConnectStatusChangeEvent(uint64 scHandlerID, int status, unsigned int error)
{}

void Event::onServerProtocolVersionEvent(uint64 scHandlerID, int protocolVersion)
{}

void Event::onNewChannelEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID)
{}

void Event::onNewChannelCreatedEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{}

void Event::onDelChannelEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{}

void Event::onChannelMoveEvent(uint64 scHandlerID, uint64 channelID, uint64 newChannelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{}

void Event::onUpdateChannelEvent(uint64 scHandlerID, uint64 channelID)
{}

void Event::onUpdateChannelEditedEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{}

void Event::onUpdateClientEvent(uint64 scHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUID)
{}

void Event::onClientMoveEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{}

void Event::onClientMoveSubscriptionEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility)
{}

void Event::onClientMoveTimeoutEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{}

void Event::onClientMoveMovedEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{}

void Event::onClientKickFromChannelEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{}

void Event::onClientKickFromServerEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{}

void Event::onClientIDsEvent(uint64 scHandlerID, const char* clientUID, anyID clientID, const char* clientName)
{}

void Event::onClientIDsFinishedEvent(uint64 scHandlerID)
{}

void Event::onServerEditedEvent(uint64 scHandlerID, anyID invokerID, const char* invokerName, const char* invokerUID)
{}

void Event::onServerUpdatedEvent(uint64 scHandlerID)
{}

void Event::onServerErrorEvent(uint64 scHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage)
{}

void Event::onServerStopEvent(uint64 scHandlerID, const char* shutdownMessage)
{}

void Event::onTextMessageEvent(uint64 scHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUID, const char* message)
{}

void Event::onTalkStatusChangeEvent(uint64 scHandlerID, int status, int isWhisper, anyID clientID)
{}

void Event::onIgnoredWhisperEvent(uint64 scHandlerID, anyID clientID)
{}

void Event::onConnectionInfoEvent(uint64 scHandlerID, anyID clientID)
{}

void Event::onServerConnectionInfoEvent(uint64 scHandlerID)
{}

void Event::onChannelSubscribeEvent(uint64 scHandlerID, uint64 channelID)
{}

void Event::onChannelSubscribeFinishedEvent(uint64 scHandlerID)
{}

void Event::onChannelUnsubscribeEvent(uint64 scHandlerID, uint64 channelID)
{}

void Event::onChannelUnsubscribeFinishedEvent(uint64 scHandlerID)
{}

void Event::onChannelDescriptionUpdateEvent(uint64 scHandlerID, uint64 channelID)
{}

void Event::onChannelPasswordChangedEvent(uint64 scHandlerID, uint64 channelID)
{}

void Event::onPlaybackShutdownCompleteEvent(uint64 scHandlerID)
{}

void Event::onSoundDeviceListChangedEvent(const char* modeID, int type)
{}

void Event::onEditPlaybackVoiceDataEvent(uint64 scHandlerID, anyID clientID, short* samples, int sampleCount, int channels)
{}

void Event::onEditPostProcessVoiceDataEvent(uint64 scHandlerID, anyID clientID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask)
{}

void Event::onEditMixedPlaybackVoiceDataEvent(uint64 scHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask)
{}

void Event::onEditCapturedVoiceDataEvent(uint64 scHandlerID, short* samples, int sampleCount, int channels, int* edited)
{}

void Event::onCustom3dRolloffCalculationClientEvent(uint64 scHandlerID, anyID clientID, float distance, float* volume)
{}

void Event::onCustom3dRolloffCalculationWaveEvent(uint64 scHandlerID, uint64 waveHandle, float distance, float* volume)
{}

void Event::onUserLoggingMessageEvent(const char* message, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* formattedString)
{}

void Event::onCustomPacketEncryptEvent(char** data, unsigned int* size)
{}

void Event::onCustomPacketDecryptEvent(char** data, unsigned int* size)
{}

void Event::onProvisioningSlotRequestResultEvent(unsigned int error, uint64 requestHandle, const char* connectionKey)
{}

void Event::onCheckServerUniqueIdentifierEvent(uint64 scHandlerID, const char* serverUID, int* cancelConnect)
{}

void Event::onClientPasswordEncrypt(uint64 scHandlerID, const char* plain, char* encrypted, int size)
{}

void Event::onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remoteSize, uint64 scHandlerID)
{}

void Event::onFileListEvent(uint64 scHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompleteSize, const char* returnCode)
{}

void Event::onFileListFinishedEvent(uint64 scHandlerID, uint64 channelID, const char* path)
{}

void Event::onFileInfoEvent(uint64 scHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime)
{}
