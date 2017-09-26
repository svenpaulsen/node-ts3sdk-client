/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "capture.h"
#include "channel.h"
#include "client.h"
#include "clientlib.h"
#include "connection.h"
#include "error.h"
#include "event.h"
#include "filetransfer.h"
#include "identity.h"
#include "log.h"
#include "playback.h"
#include "server.h"

/**
 * Initializes the Node.js addon.
 */
void Init(v8::Local<v8::Object> exports)
{
    // clientlib
    Nan::SetMethod(exports, "initClientLib",             ClientLib::Init);
    Nan::SetMethod(exports, "destroyClientLib",          ClientLib::Destroy);
    Nan::SetMethod(exports, "getClientLibVersion",       ClientLib::GetVersion);
    Nan::SetMethod(exports, "getClientLibVersionNumber", ClientLib::GetVersionNumber);
    
    // connection
    Nan::SetMethod(exports, "spawnNewServerConnectionHandler", Connection::Init);
    Nan::SetMethod(exports, "destroyServerConnectionHandler",  Connection::Destroy);
    Nan::SetMethod(exports, "startConnection",                 Connection::Start);
    Nan::SetMethod(exports, "startConnectionWithChannelID",    Connection::StartWithChannelID);
    Nan::SetMethod(exports, "stopConnection",                  Connection::Stop);
    Nan::SetMethod(exports, "getConnectionStatus",             Connection::GetStatus);
    Nan::SetMethod(exports, "getServerConnectionHandlerList",  Connection::GetList);
    Nan::SetMethod(exports, "getConnectionVariableAsUInt64",   Connection::GetInfoVarAsUInt64);
    Nan::SetMethod(exports, "getConnectionVariableAsDouble",   Connection::GetInfoVarAsDouble);
    Nan::SetMethod(exports, "getConnectionVariableAsString",   Connection::GetInfoVarAsString);
    Nan::SetMethod(exports, "cleanUpConnectionInfo",           Connection::CleanupInfo);
    
    // identity
    Nan::SetMethod(exports, "createIdentity",                   Identity::Create);
    Nan::SetMethod(exports, "identityStringToUniqueIdentifier", Identity::GetUID);
    
    // capture
    Nan::SetMethod(exports, "openCaptureDevice",             Capture::OpenDevice);
    Nan::SetMethod(exports, "closeCaptureDevice",            Capture::CloseDevice);
    Nan::SetMethod(exports, "activateCaptureDevice",         Capture::ActivateDevice);
    Nan::SetMethod(exports, "setLocalTestMode",              Capture::SetLocalTestMode);
    Nan::SetMethod(exports, "getCaptureDeviceList",          Capture::ListDevices);
    Nan::SetMethod(exports, "getCurrentCaptureDeviceName",   Capture::GetCurrentDevice);
    Nan::SetMethod(exports, "getCurrentCaptureMode",         Capture::GetCurrentMode);
    Nan::SetMethod(exports, "getCaptureModeList",            Capture::ListModes);
    Nan::SetMethod(exports, "getPreProcessorInfoValueFloat", Capture::GetInfoValue);
    Nan::SetMethod(exports, "getPreProcessorConfigValue",    Capture::GetConfigValue);
    Nan::SetMethod(exports, "setPreProcessorConfigValue",    Capture::SetConfigValue);
    Nan::SetMethod(exports, "getEncodeConfigValue",          Capture::GetEncoderValue);
    
    // playback
    Nan::SetMethod(exports, "openPlaybackDevice",               Playback::OpenDevice);
    Nan::SetMethod(exports, "closePlaybackDevice",              Playback::CloseDevice);
    Nan::SetMethod(exports, "initiateGracefulPlaybackShutdown", Playback::ShutdownDevice);
    Nan::SetMethod(exports, "playWaveFile",                     Playback::PlayWaveFile);
    Nan::SetMethod(exports, "getPlaybackDeviceList",            Playback::ListDevices);
    Nan::SetMethod(exports, "getCurrentPlaybackDeviceName",     Playback::GetCurrentDevice);
    Nan::SetMethod(exports, "getCurrentPlaybackMode",           Playback::GetCurrentMode);
    Nan::SetMethod(exports, "getPlaybackModeList",              Playback::ListModes);
    Nan::SetMethod(exports, "getPlaybackConfigValueAsFloat",    Playback::GetConfigValue);
    Nan::SetMethod(exports, "setPlaybackConfigValue",           Playback::SetConfigValue);
    
    // client
    Nan::SetMethod(exports, "getClientID",                   Client::GetOwnID);
    Nan::SetMethod(exports, "getClientSelfVariableAsInt",    Client::GetOwnVarAsInt);
    Nan::SetMethod(exports, "getClientSelfVariableAsString", Client::GetOwnVarAsString);
    Nan::SetMethod(exports, "setClientSelfVariableAsInt",    Client::SetOwnVarAsInt);
    Nan::SetMethod(exports, "setClientSelfVariableAsString", Client::SetOwnVarAsString);
    Nan::SetMethod(exports, "getClientList",                 Client::GetList);
    Nan::SetMethod(exports, "requestClientIDs",              Client::GetClones);
    Nan::SetMethod(exports, "getChannelOfClient",            Client::GetChannelID);
    Nan::SetMethod(exports, "requestConnectionInfo",         Client::GetConectionInfo);
    Nan::SetMethod(exports, "requestClientVariables",        Client::GetVars);
    Nan::SetMethod(exports, "getClientVariableAsInt",        Client::GetVarAsInt);
    Nan::SetMethod(exports, "getClientVariableAsUInt64",     Client::GetVarAsUInt64);
    Nan::SetMethod(exports, "getClientVariableAsString",     Client::GetVarAsString);
    Nan::SetMethod(exports, "flushClientSelfUpdates",        Client::FlushUpdates);
    Nan::SetMethod(exports, "requestMuteClients",            Client::Mute);
    Nan::SetMethod(exports, "requestUnmuteClients",          Client::Unmute);
    Nan::SetMethod(exports, "requestClientMove",             Client::Move);
    Nan::SetMethod(exports, "requestClientKickFromChannel",  Client::KickFromChannel);
    Nan::SetMethod(exports, "requestClientKickFromServer",   Client::KickFromServer);
    Nan::SetMethod(exports, "requestSendPrivateTextMsg",     Client::SendMessage);
    Nan::SetMethod(exports, "startVoiceRecording",           Client::SetRecordingStatus);
    Nan::SetMethod(exports, "stopVoiceRecording",            Client::UnsetRecordingStatus);
    Nan::SetMethod(exports, "requestClientSetWhisperList",   Client::SetWhisperList);
    Nan::SetMethod(exports, "allowWhispersFrom",             Client::AllowWhispersFrom);
    Nan::SetMethod(exports, "removeFromAllowedWhispersFrom", Client::PreventWhispersFrom);
    Nan::SetMethod(exports, "setClientVolumeModifier",       Client::SetVolumeModifier);

    // channel
    Nan::SetMethod(exports, "getChannelList",               Channel::GetList);
    Nan::SetMethod(exports, "getChannelClientList",         Channel::GetClients);
    Nan::SetMethod(exports, "getChannelIDFromChannelNames", Channel::GetID);
    Nan::SetMethod(exports, "getParentChannelOfChannel",    Channel::GetPID);
    Nan::SetMethod(exports, "getChannelEmptySecs",          Channel::GetSecondsEmpty);
    Nan::SetMethod(exports, "requestChannelDescription",    Channel::GetDescription);
    Nan::SetMethod(exports, "getChannelVariableAsInt",      Channel::GetVarAsInt);
    Nan::SetMethod(exports, "getChannelVariableAsUInt64",   Channel::GetVarAsUInt64);
    Nan::SetMethod(exports, "getChannelVariableAsString",   Channel::GetVarAsString);
    Nan::SetMethod(exports, "setChannelVariableAsInt",      Channel::SetVarAsInt);
    Nan::SetMethod(exports, "setChannelVariableAsUInt64",   Channel::SetVarAsUInt64);
    Nan::SetMethod(exports, "setChannelVariableAsString",   Channel::SetVarAsString);
    Nan::SetMethod(exports, "flushChannelCreation",         Channel::FlushCreation);
    Nan::SetMethod(exports, "flushChannelUpdates",          Channel::FlushUpdates);
    Nan::SetMethod(exports, "requestChannelMove",           Channel::Move);
    Nan::SetMethod(exports, "requestChannelDelete",         Channel::Delete);
    Nan::SetMethod(exports, "requestChannelSubscribe",      Channel::Subscribe);
    Nan::SetMethod(exports, "requestChannelUnsubscribe",    Channel::Unsubscribe);
    Nan::SetMethod(exports, "requestChannelSubscribeAll",   Channel::SubscribeAll);
    Nan::SetMethod(exports, "requestChannelUnsubscribeAll", Channel::UnsubscribeAll);
    Nan::SetMethod(exports, "requestSendChannelTextMsg",    Channel::SendMessage);
    
    // server
    Nan::SetMethod(exports, "requestServerConnectionInfo",         Server::GetConectionInfo);
    Nan::SetMethod(exports, "getServerConnectionVariableAsUInt64", Server::GetConectionVarAsUInt64);
    Nan::SetMethod(exports, "getServerConnectionVariableAsFloat",  Server::GetConectionVarAsFloat);
    Nan::SetMethod(exports, "requestServerVariables",              Server::GetVars);
    Nan::SetMethod(exports, "getServerVariableAsInt",              Server::GetVarAsInt);
    Nan::SetMethod(exports, "getServerVariableAsUInt64",           Server::GetVarAsUInt64);
    Nan::SetMethod(exports, "getServerVariableAsString",           Server::GetVarAsString);
    Nan::SetMethod(exports, "requestSendServerTextMsg",            Server::SendMessage);
    
    // filetransfer
    Nan::SetMethod(exports, "sendFile",                                 FileTransfer::InitUpload);
    Nan::SetMethod(exports, "requestFile",                              FileTransfer::InitDownload);
    Nan::SetMethod(exports, "haltTransfer",                             FileTransfer::Stop);
    Nan::SetMethod(exports, "requestFileList",                          FileTransfer::GetFileList);
    Nan::SetMethod(exports, "requestFileInfo",                          FileTransfer::GetFileInfo);
    Nan::SetMethod(exports, "requestDeleteFile",                        FileTransfer::DeleteFile);
    Nan::SetMethod(exports, "requestRenameFile",                        FileTransfer::RenameFile);
    Nan::SetMethod(exports, "requestCreateDirectory",                   FileTransfer::CreateDirectory);
    Nan::SetMethod(exports, "setInstanceSpeedLimitUp",                  FileTransfer::SetInstanceSpeedLimitUpload);
    Nan::SetMethod(exports, "setInstanceSpeedLimitDown",                FileTransfer::SetInstanceSpeedLimitDownload);
    Nan::SetMethod(exports, "setServerConnectionHandlerSpeedLimitUp",   FileTransfer::SetServerSpeedLimitUpload);
    Nan::SetMethod(exports, "setServerConnectionHandlerSpeedLimitDown", FileTransfer::SetServerSpeedLimitDownload);
    Nan::SetMethod(exports, "setTransferSpeedLimit",                    FileTransfer::SetTransferSpeedLimit);
    Nan::SetMethod(exports, "getInstanceSpeedLimitUp",                  FileTransfer::GetInstanceSpeedLimitUpload);
    Nan::SetMethod(exports, "getInstanceSpeedLimitDown",                FileTransfer::GetInstanceSpeedLimitDownload);
    Nan::SetMethod(exports, "getServerConnectionHandlerSpeedLimitUp",   FileTransfer::GetServerSpeedLimitUpload);
    Nan::SetMethod(exports, "getServerConnectionHandlerSpeedLimitDown", FileTransfer::GetServerSpeedLimitDownload);
    Nan::SetMethod(exports, "setTransferSpeedLimit",                    FileTransfer::GetTransferSpeedLimit);
    Nan::SetMethod(exports, "getTransferFileName",                      FileTransfer::GetTransferFileName);
    Nan::SetMethod(exports, "getTransferFilePath",                      FileTransfer::GetTransferFilePath);
    Nan::SetMethod(exports, "getTransferFileRemotePath",                FileTransfer::GetTransferFilePathRemote);
    Nan::SetMethod(exports, "getTransferFileSize",                      FileTransfer::GetTransferFileSize);
    Nan::SetMethod(exports, "getTransferFileSizeDone",                  FileTransfer::GetTransferFileSizeDone);
    Nan::SetMethod(exports, "getTransferStatus",                        FileTransfer::GetTransferStatus);
    Nan::SetMethod(exports, "getTransferRunTime",                       FileTransfer::GetTransferRuntime);
    Nan::SetMethod(exports, "getCurrentTransferSpeed",                  FileTransfer::GetTransferSpeed);
    Nan::SetMethod(exports, "getAverageTransferSpeed",                  FileTransfer::GetTransferSpeedAverage);
    Nan::SetMethod(exports, "isTransferSender",                         FileTransfer::IsTransferSender);
    
    // log
    Nan::SetMethod(exports, "logMessage",      Log::AddMessage);
    Nan::SetMethod(exports, "setLogVerbosity", Log::SetVerbosity);
    
    // error
    Nan::SetMethod(exports, "getLastError",        Error::GetLastCode);
    Nan::SetMethod(exports, "getLastErrorMessage", Error::GetLastMessage);
    Nan::SetMethod(exports, "getErrorMessage",     Error::GetMessage);
    
    // callback
    Nan::SetMethod(exports, "on", Event::On);
}

NODE_MODULE(ts3client, Init);
