/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "argument.h"

/**
 * Validates the number of arguments and returns an appropriate error code.
 */
unsigned int Argument::num(const Nan::FunctionCallbackInfo<v8::Value> &info, int min, int max)
{
    if(max < min) max = min;
    
    if(info.Length() > max)
    {
        return ERROR_parameter_invalid_count;
    }
    else if(info.Length() < min)
    {
        return ERROR_parameter_missing;
    }
    else
    {
        return ERROR_ok;
    }
}

/**
 * Fetches a specified argument as anyID.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, anyID* res, anyID def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsInt32())
    {
        return ERROR_parameter_invalid;
    }
    else if(res == nullptr)
    {
        return ERROR_undefined;
    }
    
    *res = info[arg]->IsUndefined() ? def : (anyID) info[arg]->Int32Value();
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as uint64.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, uint64* res, uint64 def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsNumber())
    {
        return ERROR_parameter_invalid;
    }
    else if(res == nullptr)
    {
        return ERROR_undefined;
    }
    
    *res = static_cast<uint64>(info[arg]->IsUndefined() ? def : info[arg]->NumberValue());
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as unsigned int.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, unsigned int* res, unsigned int def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsUint32())
    {
        return ERROR_parameter_invalid;
    }
    else if(res == nullptr)
    {
        return ERROR_undefined;
    }
    
    *res = info[arg]->IsUndefined() ? def : info[arg]->Uint32Value();
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as int.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, int* res, int def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsInt32())
    {
        return ERROR_parameter_invalid;
    }
    else if(res == nullptr)
    {
        return ERROR_undefined;
    }
    
    *res = info[arg]->IsUndefined() ? def : info[arg]->Int32Value();
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as float.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, float* res, float def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsNumber())
    {
        return ERROR_parameter_invalid;
    }
    else if(res == nullptr)
    {
        return ERROR_undefined;
    }
    
    *res = info[arg]->IsUndefined() ? def : (float) info[arg]->NumberValue();
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as char*.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, char** res, const char* def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsString())
    {
        return ERROR_parameter_invalid;
    }
    else if(res == nullptr)
    {
        return ERROR_undefined;
    }
    
    if(info[arg]->IsUndefined())
    {
        if(def != nullptr)
        {
            *res = (char*) malloc(strlen(def)+1);
            strcpy(*res, def);
        }
        else
        {
            *res = nullptr;
        }
    }
    else
    {
        *res = (char*) malloc(Nan::Utf8String(info[arg]).length()+1);
        strcpy(*res, *Nan::Utf8String(info[arg]));
    }
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as anyID list.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, std::vector<anyID> &res, anyID def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsArray())
    {
        return ERROR_parameter_invalid;
    }
    
    v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(info[arg]);
    
    for(unsigned int i = 0; i < arr->Length(); i++)
    {
        res.push_back(static_cast<anyID>(info[arg]->Uint32Value()));
    }
    
    if(res.empty() && def != 0)
    {
        res.push_back(def);
    }
    
    if(!res.empty())
    {
        res.push_back(0);
    }
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as uint64 list.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, std::vector<uint64> &res, uint64 def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsArray())
    {
        return ERROR_parameter_invalid;
    }
    
    v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(info[arg]);
    
    for(unsigned int i = 0; i < arr->Length(); i++)
    {
        res.push_back(static_cast<uint64>(info[arg]->NumberValue()));
    }
    
    if(res.empty() && def != 0)
    {
        res.push_back(def);
    }
    
    if(!res.empty())
    {
        res.push_back(0);
    }
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as unsigned int list.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, std::vector<unsigned int> &res, unsigned int def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsArray())
    {
        return ERROR_parameter_invalid;
    }
    
    v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(info[arg]);
    
    for(unsigned int i = 0; i < arr->Length(); i++)
    {
        res.push_back(static_cast<unsigned int>(info[arg]->Uint32Value()));
    }
    
    if(res.empty() && def != 0)
    {
        res.push_back(def);
    }
    
    if(!res.empty())
    {
        res.push_back(0);
    }
    
    return ERROR_ok;
}

/**
 * Fetches a specified argument as char* array.
 */
unsigned int Argument::get(const Nan::FunctionCallbackInfo<v8::Value> &info, int arg, std::vector<char*> &res, const char* def)
{
    if(!info[arg]->IsUndefined() && !info[arg]->IsArray())
    {
        return ERROR_parameter_invalid;
    }
    
    v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(info[arg]);
    
    for(unsigned int i = 0; i < arr->Length(); i++)
    {
        char* str = (char*) malloc(Nan::Utf8String(info[arg]).length()+1);
        strcpy(str, *Nan::Utf8String(arr->Get(i)));
        res.push_back(str);
    }
    
    if(res.empty() && def != nullptr)
    {
        res.push_back((char*) def);
    }
    
    if(!res.empty())
    {
        char* str = (char*) malloc(sizeof(char));
        str[0] = '\0';
        res.push_back(str);
    }
    
    return ERROR_ok;
}


