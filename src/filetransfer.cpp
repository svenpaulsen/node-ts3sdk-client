/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "error.h"
#include "filetransfer.h"
#include "helper.h"

/**
 * Wrapper for ts3client_sendFile().
 */
NAN_METHOD(FileTransfer::InitUpload)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    char*        channelPW;
    char*        file;
    unsigned int overwrite;
    unsigned int resume;
    char*        srcDir;
    anyID        result;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 7, 8)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &channelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &file, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &overwrite, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 5, &resume, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 6, &srcDir, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 7, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_sendFile(scHandlerID, channelID, channelPW, file, overwrite, resume, srcDir, &result, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(2);
    
    Nan::Set(ret, 0, Nan::New<v8::Number>(result));
    Nan::Set(ret, 1, Nan::New(returnCode).ToLocalChecked());
    
    info.GetReturnValue().Set(ret);
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestFile().
 */
NAN_METHOD(FileTransfer::InitDownload)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    char*        channelPW;
    char*        file;
    unsigned int overwrite;
    unsigned int resume;
    char*        dstDir;
    anyID        result;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 7, 8)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &channelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &file, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &overwrite, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 5, &resume, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 6, &dstDir, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 7, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestFile(scHandlerID, channelID, channelPW, file, overwrite, resume, dstDir, &result, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(2);
    
    Nan::Set(ret, 0, Nan::New<v8::Number>(result));
    Nan::Set(ret, 1, Nan::New(returnCode).ToLocalChecked());
    
    info.GetReturnValue().Set(ret);
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_haltTransfer().
 */
NAN_METHOD(FileTransfer::Stop)
{
    unsigned int error;
    uint64       scHandlerID;
    unsigned int transferID;
    unsigned int deleteFile;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 3, 4)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &deleteFile, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_haltTransfer(scHandlerID, transferID, deleteFile, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestFileList().
 */
NAN_METHOD(FileTransfer::GetFileList)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    char*        channelPW;
    char*        path;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 4, 5)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &channelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &path, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestFileList(scHandlerID, channelID, channelPW, path, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestFileInfo().
 */
NAN_METHOD(FileTransfer::GetFileInfo)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    char*        channelPW;
    char*        file;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 4, 5)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &channelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &file, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestFileInfo(scHandlerID, channelID, channelPW, file, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestDeleteFile().
 */
NAN_METHOD(FileTransfer::DeleteFile)
{
    unsigned int       error;
    uint64             scHandlerID;
    uint64             channelID;
    char*              channelPW;
    std::vector<char*> files;
    char*              returnCode;
    char*              defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 4, 5)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &channelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, files, nullptr)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestDeleteFile(scHandlerID, channelID, channelPW, (const char**) files.data(), returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestRenameFile().
 */
NAN_METHOD(FileTransfer::RenameFile)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       frChannelID;
    char*        frChannelPW;
    uint64       toChannelID;
    char*        toChannelPW;
    char*        frFile;
    char*        toFile;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 7, 8)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &frChannelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &frChannelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &toChannelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &toChannelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 5, &frFile, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 6, &toFile, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 7, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestRenameFile(scHandlerID, frChannelID, frChannelPW, toChannelID, toChannelPW, frFile, toFile, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_requestCreateDirectory().
 */
NAN_METHOD(FileTransfer::CreateDirectory)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       channelID;
    char*        channelPW;
    char*        path;
    char*        returnCode;
    char*        defretCode = Helper::createReturnCode();
    
    if((error = Argument::num(info, 4, 5)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &channelID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 2, &channelPW, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 3, &path, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 4, &returnCode, defretCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_requestCreateDirectory(scHandlerID, channelID, channelPW, path, returnCode)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(returnCode).ToLocalChecked());
    
    free(returnCode);
    free(defretCode);
}

/**
 * Wrapper for ts3client_setInstanceSpeedLimitUp().
 */
NAN_METHOD(FileTransfer::SetInstanceSpeedLimitUpload)
{
    unsigned int error;
    uint64       limit;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &limit, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setInstanceSpeedLimitUp(limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setInstanceSpeedLimitDown().
 */
NAN_METHOD(FileTransfer::SetInstanceSpeedLimitDownload)
{
    unsigned int error;
    uint64       limit;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &limit, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setInstanceSpeedLimitDown(limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setServerConnectionHandlerSpeedLimitUp().
 */
NAN_METHOD(FileTransfer::SetServerSpeedLimitUpload)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       limit;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &limit, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setServerConnectionHandlerSpeedLimitUp(scHandlerID, limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setServerConnectionHandlerSpeedLimitDown().
 */
NAN_METHOD(FileTransfer::SetServerSpeedLimitDownload)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       limit;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &limit, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setServerConnectionHandlerSpeedLimitDown(scHandlerID, limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_setTransferSpeedLimit().
 */
NAN_METHOD(FileTransfer::SetTransferSpeedLimit)
{
    unsigned int error;
    unsigned int transferID;
    uint64       limit;
    
    if((error = Argument::num(info, 2)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 1, &limit, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_setTransferSpeedLimit(transferID, limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
}

/**
 * Wrapper for ts3client_getInstanceSpeedLimitUp().
 */
NAN_METHOD(FileTransfer::GetInstanceSpeedLimitUpload)
{
    unsigned int error;
    uint64       limit;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getInstanceSpeedLimitUp(&limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(limit));
}

/**
 * Wrapper for ts3client_getInstanceSpeedLimitDown().
 */
NAN_METHOD(FileTransfer::GetInstanceSpeedLimitDownload)
{
    unsigned int error;
    uint64       limit;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getInstanceSpeedLimitDown(&limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(limit));
}

/**
 * Wrapper for ts3client_getServerConnectionHandlerSpeedLimitUp().
 */
NAN_METHOD(FileTransfer::GetServerSpeedLimitUpload)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       limit;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerConnectionHandlerSpeedLimitUp(scHandlerID, &limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(limit));
}

/**
 * Wrapper for ts3client_getServerConnectionHandlerSpeedLimitDown().
 */
NAN_METHOD(FileTransfer::GetServerSpeedLimitDownload)
{
    unsigned int error;
    uint64       scHandlerID;
    uint64       limit;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &scHandlerID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getServerConnectionHandlerSpeedLimitDown(scHandlerID, &limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(limit));
}

/**
 * Wrapper for ts3client_getTransferSpeedLimit().
 */
NAN_METHOD(FileTransfer::GetTransferSpeedLimit)
{
    unsigned int error;
    unsigned int transferID;
    uint64       limit;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferSpeedLimit(transferID, &limit)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(limit));
}

/**
 * Wrapper for ts3client_getTransferFileName().
 */
NAN_METHOD(FileTransfer::GetTransferFileName)
{
    unsigned int error;
    unsigned int transferID;
    char*        name;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferFileName(transferID, &name)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
    
    ts3client_freeMemory(name);
}

/**
 * Wrapper for ts3client_getTransferFilePath().
 */
NAN_METHOD(FileTransfer::GetTransferFilePath)
{
    unsigned int error;
    unsigned int transferID;
    char*        path;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferFilePath(transferID, &path)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(path).ToLocalChecked());
    
    ts3client_freeMemory(path);
}

/**
 * Wrapper for ts3client_getTransferFileRemotePath().
 */
NAN_METHOD(FileTransfer::GetTransferFilePathRemote)
{
    unsigned int error;
    unsigned int transferID;
    char*        path;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferFileRemotePath(transferID, &path)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(path).ToLocalChecked());
    
    ts3client_freeMemory(path);
}

/**
 * Wrapper for ts3client_getTransferFileSize().
 */
NAN_METHOD(FileTransfer::GetTransferFileSize)
{
    unsigned int error;
    unsigned int transferID;
    uint64       size;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferFileSize(transferID, &size)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(size));
}

/**
 * Wrapper for ts3client_getTransferFileSizeDone().
 */
NAN_METHOD(FileTransfer::GetTransferFileSizeDone)
{
    unsigned int error;
    unsigned int transferID;
    uint64       size;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferFileSizeDone(transferID, &size)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(size));
}

/**
 * Wrapper for ts3client_getTransferStatus().
 */
NAN_METHOD(FileTransfer::GetTransferStatus)
{
    unsigned int error;
    unsigned int transferID;
    int          status;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferStatus(transferID, &status)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(status));
}

/**
 * Wrapper for ts3client_getTransferRunTime().
 */
NAN_METHOD(FileTransfer::GetTransferRuntime)
{
    unsigned int error;
    unsigned int transferID;
    uint64       time;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getTransferRunTime(transferID, &time)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(time));
}

/**
 * Wrapper for ts3client_getCurrentTransferSpeed().
 */
NAN_METHOD(FileTransfer::GetTransferSpeed)
{
    unsigned int error;
    unsigned int transferID;
    float        speed;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getCurrentTransferSpeed(transferID, &speed)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(speed));
}

/**
 * Wrapper for ts3client_getAverageTransferSpeed().
 */
NAN_METHOD(FileTransfer::GetTransferSpeedAverage)
{
    unsigned int error;
    unsigned int transferID;
    float        speed;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_getAverageTransferSpeed(transferID, &speed)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(speed));
}

/**
 * Wrapper for ts3client_isTransferSender().
 */
NAN_METHOD(FileTransfer::IsTransferSender)
{
    unsigned int error;
    unsigned int transferID;
    int          status;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &transferID, 0)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_isTransferSender(transferID, &status)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New<v8::Number>(status));
}
