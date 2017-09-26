/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "capture.h"
#include "error.h"

/**
 * Wrapper for ts3client_openCaptureDevice().
 */
NAN_METHOD(Capture::OpenDevice)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        mode;
    char*        modeDefault;
    char*        device;
    char**       deviceDefault;
    
    if((error = Argument::num(info, 1, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getDefaultCaptureMode(&modeDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getDefaultCaptureDevice(modeDefault, &deviceDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &mode, modeDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &device, deviceDefault[1])) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_openCaptureDevice(scHandlerID, mode, device)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    ts3client_freeMemory(modeDefault);
    ts3client_freeMemory(deviceDefault);
}

/**
 * Wrapper for ts3client_closeCaptureDevice().
 */
NAN_METHOD(Capture::CloseDevice)
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
    
    if((error = ts3client_closeCaptureDevice(scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_activateCaptureDevice().
 */
NAN_METHOD(Capture::ActivateDevice)
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
    
    if((error = ts3client_activateCaptureDevice(scHandlerID)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setLocalTestMode().
 */
NAN_METHOD(Capture::SetLocalTestMode)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int status;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &status, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setLocalTestMode(scHandlerID, status)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getCaptureDeviceList().
 */
NAN_METHOD(Capture::ListDevices)
{
    unsigned int error;
    char*        mode;
    char*        modeDefault;
    char**       deviceDefault;
    char***      devices;
    
    if((error = Argument::num(info, 0, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getDefaultCaptureMode(&modeDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &mode, modeDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getDefaultCaptureDevice(modeDefault, &deviceDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getCaptureDeviceList(mode, &devices)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    int n = 0;
    for(; devices[n] != NULL; ++n)
    {}
    
    v8::Local<v8::Array> arr = Nan::New<v8::Array>(n+1);
    v8::Local<v8::Array> def = Nan::New<v8::Array>(2);
    
    Nan::Set(def, 0, Nan::New(deviceDefault[0]).ToLocalChecked());
    Nan::Set(def, 1, Nan::New(deviceDefault[1]).ToLocalChecked());
    Nan::Set(arr, 0, def);
    
    for(int i = 0; devices[i] != NULL; ++i)
    {
        v8::Local<v8::Array> itm = Nan::New<v8::Array>(2);
        
        Nan::Set(itm, 0, Nan::New(devices[i][0]).ToLocalChecked());
        Nan::Set(itm, 1, Nan::New(devices[i][1]).ToLocalChecked());
        Nan::Set(arr, i+1, itm);
        
        ts3client_freeMemory(devices[i][0]);
        ts3client_freeMemory(devices[i][1]);
        ts3client_freeMemory(devices[i]);
    }
    
    info.GetReturnValue().Set(arr);
    
    ts3client_freeMemory(modeDefault);
    ts3client_freeMemory(deviceDefault);
    ts3client_freeMemory(devices);
}

/**
 * Wrapper for ts3client_getCurrentCaptureDeviceName().
 */
NAN_METHOD(Capture::GetCurrentDevice)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        device;
    int          isDefault;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getCurrentCaptureDeviceName(scHandlerID, &device, &isDefault)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(device).ToLocalChecked());
    
    ts3client_freeMemory(device);
}

/**
 * Wrapper for ts3client_getCurrentCaptureMode().
 */
NAN_METHOD(Capture::GetCurrentMode)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        mode;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getCurrentCaptureMode(scHandlerID, &mode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(mode).ToLocalChecked());
    
    ts3client_freeMemory(mode);
}

/**
 * Wrapper for ts3client_getCaptureModeList().
 */
NAN_METHOD(Capture::ListModes)
{
    unsigned int error;
    char**       modes;
    
    if((error = Argument::num(info, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getCaptureModeList(&modes)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    int n = 0;
    for(; modes[n] != NULL; ++n)
    {}
    
    v8::Local<v8::Array> arr = Nan::New<v8::Array>(n);
    
    for(int i = 0; modes[i] != NULL; ++i)
    {
        Nan::Set(arr, i, Nan::New(modes[i]).ToLocalChecked());
        
        ts3client_freeMemory(modes[i]);
    }
    
    info.GetReturnValue().Set(arr);
    
    ts3client_freeMemory(modes);
}

/**
 * Wrapper for ts3client_getPreProcessorInfoValueFloat().
 */
NAN_METHOD(Capture::GetInfoValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    float        val;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getPreProcessorInfoValueFloat(scHandlerID, key, &val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(val));
}

/**
 * Wrapper for ts3client_getPreProcessorConfigValue().
 */
NAN_METHOD(Capture::GetConfigValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    char*        val;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getPreProcessorConfigValue(scHandlerID, key, &val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(val).ToLocalChecked());
    
    ts3client_freeMemory(val);
}

/**
 * Wrapper for ts3client_setPreProcessorConfigValue().
 */
NAN_METHOD(Capture::SetConfigValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    char*        val;
    
    if((error = Argument::num(info, 3)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &val, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setPreProcessorConfigValue(scHandlerID, key, val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getEncodeConfigValue().
 */
NAN_METHOD(Capture::GetEncoderValue)
{
    unsigned int error;
    uint64       scHandlerID;
    char*        key;
    char*        val;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &key, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getEncodeConfigValue(scHandlerID, key, &val)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(val).ToLocalChecked());
    
    ts3client_freeMemory(val);
}
