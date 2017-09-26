# TeamSpeak 3 SDK Client Addon for Node.js

[![Build Status](https://travis-ci.org/svenpaulsen/node-ts3sdk-client.svg?branch=master)](https://travis-ci.org/svenpaulsen/node-ts3sdk-client)

This native Node.js addon is a wrapper for the TeamSpeak 3 SDK and allows JavaScript implementations of third-party clients using the TeamSpeak 3 ClientLib.

## Prerequisites

The following prerequisites are necessary prior to using the addon:

- [TeamSpeak 3 SDK](https://www.teamspeak.com)
- [Node.js](https://www.nodejs.org)
- [Native Addon Build Tool for Node.js](https://www.npmjs.com/package/node-gyp)
- [Visual C++ Build Tools](https://www.npmjs.com/package/windows-build-tools) (Windows only)

## Installing

All dependencies can be installed via `npm`:

```sh
npm install
```

This will also build build the module for your current platform. If you want to build the addon manually, issue the following commands in the root directory after cloning the repository:

```sh
$ node-gyp configure
$ node-gyp build
```

## Testing

Included is a minimal console client to connect to a local TeamSpeak 3 SDK Server.

```sh
$ cd node-ts3sdk-client
$ node examples/client_minimal.js
```

## Usage

Please refer to the official TeamSpeak 3 SDK [documentation](https://github.com/svenpaulsen/node-ts3sdk-client/blob/master/doc/client.pdf) for a list of functions and events available.

### Basics

After loading the addon, most TeamSpeak 3 ClientLib features are available in JavaScript. For the sake of convenience the `ts3client_` prefix has been removed from function names and some arguments are optional.

```javascript
var ts3client = require('ts3client.node');

ts3client.initClientLib(logLevel, logPath, soundBackendPath);

var schID = ts3client.spawnNewServerConnectionHandler();
var ident = ts3client.createIdentity();

ts3client.startConnection(schID, ident, '127.0.0.1', 9987, 'JohnDoe');
```

### Callbacks

To register a callback to an event triggered by the TeamSpeak 3 CliebtLib, use the `on` method:

```javascript
ts3client.on('onClientMoveEvent', function(schID, clientID, oldChannelID, newChannelID, visibility, moveMessage)
{
  // your code
});
```

### Error Handling

When an error occurs, the addon will throw exceptions:

```javascript
try
{
  // your code
}
catch(err)
{
  console.log(err.message);
}
```

## Known Issues

I am aware that some features of the SDK are not implemented and I am working to update these. Please visit the project on [GitHub](https://github.com/svenpaulsen/node-ts3sdk-client) to view outstanding issues.
