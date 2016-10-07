# TeamSpeak 3 SDK Client Addon for Node.js

[![Build Status](https://travis-ci.org/svenpaulsen/node-ts3sdk-client.svg?branch=master)](https://travis-ci.org/svenpaulsen/node-ts3sdk-client)

This native Node.js addon is a wrapper for the TeamSpeak 3 SDK and allows JavaScript implementations of third-party clients using the TeamSpeak 3 ClientLib.

## Requirements

- [TeamSpeak 3 SDK](https://www.teamspeak.com)
- [Node.js](https://www.nodejs.org)
- [Native Addon Build Tool for Node.js](https://github.com/nodejs/node-gyp)
- [Native Abstractions for Node.js](https://github.com/nodejs/nan)

## Building from Source

After cloning this repository including submodules, issue the following commands in the root directory:

    node-gyp configure
    node-gyp build
