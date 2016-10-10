/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "event.h"
#include "error.h"

std::map<std::string, Nan::Callback*> Event::m_pool;

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

void Event::exec(uv_async_t* handle, int status)
{
    Payload* p = (Payload*) handle->data;
    
    auto func = m_pool.find(p->getName());
    
    if(func != m_pool.end())
    {
        Nan::HandleScope scope;
        Nan::TryCatch    trycatch;
        
        v8::Handle<v8::Value>* args = (v8::Handle<v8::Value>*) malloc(sizeof(v8::Handle<v8::Value>)*p->getLength());
        
        for(unsigned int i = 0; i < p->getLength(); ++i)
        {
            switch(p->getFormat()[i])
            {
                case '6':
                    args[i] = Nan::New<v8::Number>(p->getArgument<uint64>(i));
                    break;
                    
                case 'I':
                    args[i] = Nan::New<v8::Number>(p->getArgument<unsigned int>(i));
                    break;
                    
                case 'i':
                    args[i] = Nan::New<v8::Number>(p->getArgument<int>(i));
                    break;
                    
                case 'f':
                    args[i] = Nan::New<v8::Number>(p->getArgument<double>(i));
                    break;
                    
                case 's':
                    if(!p->getArgument<char*>(i))
                    {
                        args[i] = Nan::Undefined();
                    }
                    else
                    {
                        args[i] = Nan::New(p->getArgument<char*>(i)).ToLocalChecked();
                    }
                    break;
                    
                default:
                    args[i] = Nan::Undefined();
                    break;
            }
        }
        
        func->second->Call(p->getLength(), args);
        
        if(trycatch.HasCaught())
        {
            Nan::FatalException(trycatch);
        }
        
        free(args);
    }

    uv_close((uv_handle_t*) handle, done);
}

void Event::done(uv_handle_t* handle)
{
    Payload* p = (Payload*) handle->data;
    
    delete p;
    delete (uv_async_t*) handle;
}

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

void Event::onConnectStatusChangeEvent(uint64 scHandlerID, int status, unsigned int error)
{
    emit(new Payload(__FUNCTION__, "6iI", scHandlerID, status, error));
}

void Event::onServerProtocolVersionEvent(uint64 scHandlerID, int protocolVersion)
{
    emit(new Payload(__FUNCTION__, "6i", scHandlerID, protocolVersion));
}

void Event::onNewChannelEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID)
{
    emit(new Payload(__FUNCTION__, "666", scHandlerID, channelID, channelPID));
}

void Event::onNewChannelCreatedEvent(uint64 scHandlerID, uint64 channelID, uint64 channelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__FUNCTION__, "666Iss", scHandlerID, channelID, channelPID, invokerID, invokerName, invokerUID));
}

void Event::onDelChannelEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__FUNCTION__, "66Iss", scHandlerID, channelID, invokerID, invokerName, invokerUID));
}

void Event::onChannelMoveEvent(uint64 scHandlerID, uint64 channelID, uint64 newChannelPID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__FUNCTION__, "666Iss", scHandlerID, channelID, newChannelPID, invokerID, invokerName, invokerUID));
}

void Event::onUpdateChannelEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onUpdateChannelEditedEvent(uint64 scHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__FUNCTION__, "66Iss", scHandlerID, channelID, invokerID, invokerName, invokerUID));
}

void Event::onUpdateClientEvent(uint64 scHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__FUNCTION__, "6IIss", scHandlerID, clientID, invokerID, invokerName, invokerUID));
}

void Event::onClientMoveEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{
    emit(new Payload(__FUNCTION__, "6I66is", scHandlerID, clientID, oldChannelID, newChannelID, visibility, message));
}

void Event::onClientMoveSubscriptionEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility)
{
    emit(new Payload(__FUNCTION__, "6I66i", scHandlerID, clientID, oldChannelID, newChannelID, visibility));
}

void Event::onClientMoveTimeoutEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* message)
{
    emit(new Payload(__FUNCTION__, "6I66is", scHandlerID, clientID, oldChannelID, newChannelID, visibility, message));
}

void Event::onClientMoveMovedEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    emit(new Payload(__FUNCTION__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

void Event::onClientKickFromChannelEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    emit(new Payload(__FUNCTION__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

void Event::onClientKickFromServerEvent(uint64 scHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID invokerID, const char* invokerName, const char* invokerUID, const char* message)
{
    emit(new Payload(__FUNCTION__, "6I66iIsss", scHandlerID, clientID, oldChannelID, newChannelID, visibility, invokerID, invokerName, invokerUID, message));
}

void Event::onClientIDsEvent(uint64 scHandlerID, const char* clientUID, anyID clientID, const char* clientName)
{
    emit(new Payload(__FUNCTION__, "6sIs", scHandlerID, clientUID, clientID, clientName));
}

void Event::onClientIDsFinishedEvent(uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "6", scHandlerID));
}

void Event::onServerEditedEvent(uint64 scHandlerID, anyID invokerID, const char* invokerName, const char* invokerUID)
{
    emit(new Payload(__FUNCTION__, "6Iss", scHandlerID, invokerID, invokerName, invokerUID));
}

void Event::onServerUpdatedEvent(uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "6", scHandlerID));
}

void Event::onServerErrorEvent(uint64 scHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage)
{
    emit(new Payload(__FUNCTION__, "6sIss", scHandlerID, errorMessage, error, returnCode, extraMessage));
}

void Event::onServerStopEvent(uint64 scHandlerID, const char* shutdownMessage)
{
    emit(new Payload(__FUNCTION__, "6s", scHandlerID, shutdownMessage));
}

void Event::onTextMessageEvent(uint64 scHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUID, const char* message)
{
    emit(new Payload(__FUNCTION__, "6IIIsss", scHandlerID, targetMode, toID, fromID, fromName, fromUID, message));
}

void Event::onTalkStatusChangeEvent(uint64 scHandlerID, int status, int isWhisper, anyID clientID)
{
    emit(new Payload(__FUNCTION__, "6iiI", scHandlerID, status, isWhisper, clientID));
}

void Event::onIgnoredWhisperEvent(uint64 scHandlerID, anyID clientID)
{
    emit(new Payload(__FUNCTION__, "6I", scHandlerID, clientID));
}

void Event::onConnectionInfoEvent(uint64 scHandlerID, anyID clientID)
{
    emit(new Payload(__FUNCTION__, "6I", scHandlerID, clientID));
}

void Event::onServerConnectionInfoEvent(uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "6", scHandlerID));
}

void Event::onChannelSubscribeEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onChannelSubscribeFinishedEvent(uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "6", scHandlerID));
}

void Event::onChannelUnsubscribeEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onChannelUnsubscribeFinishedEvent(uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "6", scHandlerID));
}

void Event::onChannelDescriptionUpdateEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onChannelPasswordChangedEvent(uint64 scHandlerID, uint64 channelID)
{
    emit(new Payload(__FUNCTION__, "66", scHandlerID, channelID));
}

void Event::onPlaybackShutdownCompleteEvent(uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "6", scHandlerID));
}

void Event::onSoundDeviceListChangedEvent(const char* modeID, int type)
{
    emit(new Payload(__FUNCTION__, "si", modeID, type));
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
    emit(new Payload(__FUNCTION__, "sis6ss", message, logLevel, logChannel, logID, logTime, formattedString));
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
    emit(new Payload(__FUNCTION__, "I6s", error, requestHandle, connectionKey));
}

void Event::onCheckServerUniqueIdentifierEvent(uint64 scHandlerID, const char* serverUID, int* cancelConnect)
{
    // not implemented
}

void Event::onClientPasswordEncrypt(uint64 scHandlerID, const char* plain, char* encrypted, int size)
{
    emit(new Payload(__FUNCTION__, "6ssi", scHandlerID, plain, encrypted, size));
}

void Event::onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remoteSize, uint64 scHandlerID)
{
    emit(new Payload(__FUNCTION__, "IIs66", (unsigned int) transferID, status, statusMessage, remoteSize, scHandlerID));
}

void Event::onFileListEvent(uint64 scHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompleteSize, const char* returnCode)
{
    emit(new Payload(__FUNCTION__, "66ss66i6s", scHandlerID, channelID, path, name, size, datetime, type, incompleteSize, returnCode));
}

void Event::onFileListFinishedEvent(uint64 scHandlerID, uint64 channelID, const char* path)
{
    emit(new Payload(__FUNCTION__, "66s", scHandlerID, channelID, path));
}

void Event::onFileInfoEvent(uint64 scHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime)
{
    emit(new Payload(__FUNCTION__, "66s66", scHandlerID, channelID, name, size, datetime));
}
