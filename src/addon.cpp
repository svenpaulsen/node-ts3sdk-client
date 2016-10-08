/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "clientlib.h"
#include "connection.h"
#include "error.h"
#include "identity.h"
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
    
    // error
    Nan::SetMethod(exports, "getErrorMessage", Error::GetMessage);
    
    // identity
    Nan::SetMethod(exports, "createIdentity",                   Identity::Create);
    Nan::SetMethod(exports, "identityStringToUniqueIdentifier", Identity::GetUID);
    
    // log
    Nan::SetMethod(exports, "logMessage",      Log::AddMessage);
    Nan::SetMethod(exports, "setLogVerbosity", Log::SetVerbosity);
}

NODE_MODULE(ts3client, Init);
