/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "capture.h"
#include "clientlib.h"
#include "connection.h"
#include "error.h"
#include "identity.h"
#include "playback.h"
#include "log.h"

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
    Nan::SetMethod(exports, "openCaptureDevice",     Capture::OpenDevice);
    Nan::SetMethod(exports, "closeCaptureDevice",    Capture::CloseDevice);
    Nan::SetMethod(exports, "activateCaptureDevice", Capture::ActivateDevice);
    Nan::SetMethod(exports, "setLocalTestMode",      Capture::SetLocalTestMode);
    Nan::SetMethod(exports, "getCaptureDeviceList",  Capture::ListDevices);
    Nan::SetMethod(exports, "getCaptureModeList",    Capture::ListModes);
    
    // playback
    Nan::SetMethod(exports, "openPlaybackDevice",               Playback::OpenDevice);
    Nan::SetMethod(exports, "closePlaybackDevice",              Playback::CloseDevice);
    Nan::SetMethod(exports, "initiateGracefulPlaybackShutdown", Playback::ShutdownDevice);
    Nan::SetMethod(exports, "playWaveFile",                     Playback::PlayWaveFile);
    Nan::SetMethod(exports, "getPlaybackDeviceList",            Playback::ListDevices);
    Nan::SetMethod(exports, "getPlaybackModeList",              Playback::ListModes);
    
    // log
    Nan::SetMethod(exports, "logMessage",      Log::AddMessage);
    Nan::SetMethod(exports, "setLogVerbosity", Log::SetVerbosity);
    
    // error
    Nan::SetMethod(exports, "getErrorMessage", Error::GetMessage);
}

NODE_MODULE(ts3client, Init);
