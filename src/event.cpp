/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "event.h"
#include "error.h"

std::map<std::string, Nan::Callback*> Event::m_pool;

/**
 * Wakes up the event loop and calls the async handle callback.
 */
void Event::emit(Payload* p)
{
    auto func = m_pool.find(p->getName());
    
    if(func != m_pool.end())
    {
        auto handle = new uv_async_t();
        
        handle->data = (void*) p;
        
        uv_async_init(uv_default_loop(), handle, (uv_async_cb) exec);
        uv_async_send(handle);
    }
}

/**
 * Calls the JavaScript callback for TeamSpeak 3 ClientLib events.
 */
void Event::exec(uv_async_t* handle, int status)
{
    Payload* p = (Payload*) handle->data;
    
    auto func = m_pool.find(p->getName());
    
    if(func != m_pool.end())
    {
        Nan::HandleScope scope;
        Nan::TryCatch    trycatch;
        
        std::vector<v8::Handle<v8::Value>> args;
        
        for(unsigned int i = 0; i < p->getLength(); ++i)
        {
            switch(p->getFormat()[i])
            {
                case '6':
                    args.push_back(Nan::New<v8::Number>(p->getArgument<uint64>(i)));
                    break;
                    
                case 'I':
                    args.push_back(Nan::New<v8::Number>(p->getArgument<unsigned int>(i)));
                    break;
                    
                case 'i':
                    args.push_back(Nan::New<v8::Number>(p->getArgument<int>(i)));
                    break;
                    
                case 'f':
                    args.push_back(Nan::New<v8::Number>(p->getArgument<double>(i)));
                    break;
                    
                case 's':
                    if(!p->getArgument<char*>(i))
                    {
                        args.push_back(Nan::Undefined());
                    }
                    else
                    {
                        args.push_back(Nan::New(p->getArgument<char*>(i)).ToLocalChecked());
                    }
                    break;
                    
                default:
                    args.push_back(Nan::Undefined());
                    break;
            }
        }
        
        func->second->Call(p->getLength(), args.data());
        
        if(trycatch.HasCaught())
        {
            Nan::FatalException(trycatch);
        }
    }

    uv_close((uv_handle_t*) handle, done);
}

/**
 * Close callback to be called after handling events.
 */
void Event::done(uv_handle_t* handle)
{
    Payload* p = (Payload*) handle->data;
    
    delete p;
    delete (uv_async_t*) handle;
}

/**
 * Registers JavaScript callbacks for TeamSpeak 3 ClientLib events.
 */
NAN_METHOD(Event::On)
{
    unsigned int error;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if(!info[0]->IsString() || !info[1]->IsFunction())
    {
        return Error::throwException(ERROR_parameter_invalid);
    }
    
    Nan::Callback* callback = new Nan::Callback(v8::Local<v8::Function>::Cast(info[1]));
    
    m_pool[std::string(*Nan::Utf8String(info[0]->ToString()))] = callback;
}

/**
 * TeamSpeak 3 ClientLib event triggered on connection status updates.
 */
void Event::onConnectStatusChangeEvent(uint64 scHandlerID, int status, unsigned int error)
{
    emit(new Payload(__func__, "6iI", scHandlerID, status, error));
}

/**
 * TeamSpeak 3 ClientLib event triggered when receiving the server protocol version.
 */
void Event::onServerProtocolVersionEvent(uint64 scHandlerID, int protocolVersion)
{
    emit(new Payload(__func__, "6i", scHandlerID, protocolVersion));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server announces a channel.
 */
void Event::onNewChannelEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID)
{
    emit(new Payload(__func__, "666", scHandlerID, channelID, channelPID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a new channel is created.
 */
void Event::onNewChannelCreatedEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__func__, "666Iss", scHandlerID, channelID, channelPID, invokerID, invokerName, invokerUID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel is deleted.
 */
void Event::onDelChannelEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__func__, "66Iss", scHandlerID, channelID, invokerID, invokerName, invokerUID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel is moved.
 */
void Event::onChannelMoveEvent(uint64 scHandlerID, uint64 channelID, uint64 newChannelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__func__, "666Iss", scHandlerID, channelID, newChannelPID, invokerID, invokerName, invokerUID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channels flags are updated.
 */
void Event::onUpdateChannelEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__func__, "66", scHandlerID, channelID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channels properties are updated.
 */
void Event::onUpdateChannelEditedEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__func__, "66Iss", scHandlerID, channelID, invokerID, invokerName, invokerUID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a clients properties are updated.
 */
void Event::onUpdateClientEvent(uint64 scHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__func__, "6IIss", scHandlerID, clientID, invokerID, invokerName, invokerUID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a client switches the channel, connects or disconnects.
 */
void Event::onClientMoveEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{
    emit(new Payload(__func__, "6I66is", scHandlerID, clientID, oldChannelID, newChannelID, visibility, message));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server announces a client.
 */
void Event::onClientMoveSubscriptionEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility)
{
    emit(new Payload(__func__, "6I66i", scHandlerID, clientID, oldChannelID, newChannelID, visibility));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a client times out.
 */
void Event::onClientMoveTimeoutEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{
    emit(new Payload(__func__, "6I66is", scHandlerID, clientID, oldChannelID, newChannelID, visibility, message));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a client is moved.
 */
void Event::onClientMoveMovedEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    emit(new Payload(__func__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a client is kicked from a channel.
 */
void Event::onClientKickFromChannelEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    emit(new Payload(__func__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a client is kicked from the server.
 */
void Event::onClientKickFromServerEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    emit(new Payload(__func__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server is announcing client IDs.
 */
void Event::onClientIDsEvent(uint64 scHandlerID, const char* clientUID, anyID clientID, const char* clientName)
{
    emit(new Payload(__func__, "6sIs", scHandlerID, clientUID, clientID, clientName));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server finished announcing client IDs.
 */
void Event::onClientIDsFinishedEvent(uint64 scHandlerID)
{
    emit(new Payload(__func__, "6", scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the servers properties are updated.
 */
void Event::onServerEditedEvent(uint64 scHandlerID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__func__, "6Iss", scHandlerID, invokerID, invokerName, invokerUID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the servers flags are updated.
 */
void Event::onServerUpdatedEvent(uint64 scHandlerID)
{
    emit(new Payload(__func__, "6", scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server reports an error.
 */
void Event::onServerErrorEvent(uint64 scHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage)
{
    emit(new Payload(__func__, "6sIss", scHandlerID, errorMessage, error, returnCode, extraMessage));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server is shutting down.
 */
void Event::onServerStopEvent(uint64 scHandlerID, const char* shutdownMessage)
{
    emit(new Payload(__func__, "6s", scHandlerID, shutdownMessage));
}

/**
 * TeamSpeak 3 ClientLib event triggered when receiving a text message.
 */
void Event::onTextMessageEvent(uint64 scHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUID, const char* message)
{
    emit(new Payload(__func__, "6IIIsss", scHandlerID, targetMode, toID, fromID, fromName, fromUID, message));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a client starts/stops talking.
 */
void Event::onTalkStatusChangeEvent(uint64 scHandlerID, int status, int isWhisper, anyID clientID)
{
    emit(new Payload(__func__, "6iiI", scHandlerID, status, isWhisper, clientID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when an incoming whisper is ignored.
 */
void Event::onIgnoredWhisperEvent(uint64 scHandlerID, anyID clientID)
{
    emit(new Payload(__func__, "6I", scHandlerID, clientID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when receiving client connection information.
 */
void Event::onConnectionInfoEvent(uint64 scHandlerID, anyID clientID)
{
    emit(new Payload(__func__, "6I", scHandlerID, clientID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when receiving server connection information.
 */
void Event::onServerConnectionInfoEvent(uint64 scHandlerID)
{
    emit(new Payload(__func__, "6", scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel subscription is requested.
 */
void Event::onChannelSubscribeEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__func__, "66", scHandlerID, channelID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel subscription is complete.
 */
void Event::onChannelSubscribeFinishedEvent(uint64 scHandlerID)
{
    emit(new Payload(__func__, "6", scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel subscription removal is requested.
 */
void Event::onChannelUnsubscribeEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__func__, "66", scHandlerID, channelID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel subscription removal is complete.
 */
void Event::onChannelUnsubscribeFinishedEvent(uint64 scHandlerID)
{
    emit(new Payload(__func__, "6", scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel description is updated.
 */
void Event::onChannelDescriptionUpdateEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__func__, "66", scHandlerID, channelID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a channel password is updated.
 */
void Event::onChannelPasswordChangedEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__func__, "66", scHandlerID, channelID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a cplayback device is shut down.
 */
void Event::onPlaybackShutdownCompleteEvent(uint64 scHandlerID)
{
    emit(new Payload(__func__, "6", scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the list of audio devices is changed.
 */
void Event::onSoundDeviceListChangedEvent(const char* modeID, int type)
{
    emit(new Payload(__func__, "si", modeID, type));
}

/**
 * TeamSpeak 3 ClientLib event triggered when a message is logged.
 */
void Event::onUserLoggingMessageEvent(const char* message, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* formattedString)
{
    emit(new Payload(__func__, "sis6ss", message, logLevel, logChannel, logID, logTime, formattedString));
}

/**
 * TeamSpeak 3 ClientLib event triggered when receiving file transfer status updates.
 */
void Event::onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remoteSize, uint64 scHandlerID)
{
    emit(new Payload(__func__, "IIs66", (unsigned int) transferID, status, statusMessage, remoteSize, scHandlerID));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server is announcing available files/directories.
 */
void Event::onFileListEvent(uint64 scHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompleteSize, const char* returnCode)
{
    emit(new Payload(__func__, "66ss66i6s", scHandlerID, channelID, path, name, size, datetime, type, incompleteSize, returnCode));
}

/**
 * TeamSpeak 3 ClientLib event triggered when the server finished announcing available files/directories.
 */
void Event::onFileListFinishedEvent(uint64 scHandlerID, uint64 channelID, const char* path)
{
    emit(new Payload(__func__, "66s", scHandlerID, channelID, path));
}
/**
 * TeamSpeak 3 ClientLib event triggered when receiving file/directoy information.
 */
void Event::onFileInfoEvent(uint64 scHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime)
{
    emit(new Payload(__func__, "66s66", scHandlerID, channelID, name, size, datetime));
}
