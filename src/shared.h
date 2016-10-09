/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_SHARED_H
#define ADDON_SHARED_H

#include <map>
#include <list>
#include <string>
#include <vector>

using namespace std;

#include <nan.h>
#include <stdarg.h>
#include <pthread.h>
#include <teamspeak/clientlib.h>
#include <teamspeak/public_errors.h>

#include "callback.h"
#include "queue.h"
#include "singleton.h"

#define BUFFSIZE_L 512
#define BUFFSIZE_M 256
#define BUFFSIZE_D 128
#define BUFFSIZE_S 64

extern struct ClientUIFunctions clientSDK;
extern Queue<Callback*>         eventQueue;

#endif // ADDON_SHARED_H
