/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"
#include "identity.h"
#include "error.h"

/**
 * Wrapper for ts3client_createIdentity().
 */
NAN_METHOD(Identity::Create)
{
    unsigned int error;
    char*        identity;
    
    if((error = Argument::num(info)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_createIdentity(&identity)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(identity).ToLocalChecked());
    
    ts3client_freeMemory(identity);
}

/**
 * Wrapper for ts3client_identityStringToUniqueIdentifier().
 */
NAN_METHOD(Identity::GetUID)
{
    unsigned int error;
    char*        identity;
    char*        uid;
    
    if((error = Argument::num(info, 1)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = Argument::get(info, 0, &identity, "")) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    if((error = ts3client_identityStringToUniqueIdentifier(identity, &uid)) != ERROR_ok)
    {
        return Error::throwException(error);
    }
    
    info.GetReturnValue().Set(Nan::New(uid).ToLocalChecked());
    
    ts3client_freeMemory(uid);
}
