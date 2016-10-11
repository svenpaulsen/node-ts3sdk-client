/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_FILETRANSFER_H
#define ADDON_FILETRANSFER_H

#include "shared.h"

class FileTransfer : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(InitUpload);
    static NAN_METHOD(InitDownload);
    static NAN_METHOD(Stop);
    static NAN_METHOD(GetFileList);
    static NAN_METHOD(GetFileInfo);
    static NAN_METHOD(DeleteFile);
    static NAN_METHOD(RenameFile);
    static NAN_METHOD(CreateDirectory);
    static NAN_METHOD(SetInstanceSpeedLimitUpload);
    static NAN_METHOD(SetInstanceSpeedLimitDownload);
    static NAN_METHOD(SetServerSpeedLimitUpload);
    static NAN_METHOD(SetServerSpeedLimitDownload);
    static NAN_METHOD(SetTransferSpeedLimit);
    static NAN_METHOD(GetInstanceSpeedLimitUpload);
    static NAN_METHOD(GetInstanceSpeedLimitDownload);
    static NAN_METHOD(GetServerSpeedLimitUpload);
    static NAN_METHOD(GetServerSpeedLimitDownload);
    static NAN_METHOD(GetTransferSpeedLimit);
    static NAN_METHOD(GetTransferFileName);
    static NAN_METHOD(GetTransferFilePath);
    static NAN_METHOD(GetTransferFilePathRemote);
    static NAN_METHOD(GetTransferFileSize);
    static NAN_METHOD(GetTransferFileSizeDone);
    static NAN_METHOD(GetTransferStatus);
    static NAN_METHOD(GetTransferRuntime);
    static NAN_METHOD(GetTransferSpeed);
    static NAN_METHOD(GetTransferSpeedAverage);
    static NAN_METHOD(IsTransferSender);
};

#endif // ADDON_FILETRANSFER_H
