/**
 * TeamSpeak 3 SDK Client Addon for Node.js (Minimal Example)
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

process.stdin.resume();
process.stdin.setEncoding('utf8');

/**
 * Load the required Node.js addons.
 */
var ts3client = require('../api.js');

// ============================================================
// ======================== CALLBACKS =========================
// ============================================================

/**
 * Register callback function for 'onConnectStatusChangeEvent'. This will write debug messages to the
 * client log upon connection status updates and kill the process when the connection attempt fails.
 */
ts3client.on('onConnectStatusChangeEvent', function(schID, status, errno)
{
  ts3client.logMessage('Connect status changed; new status is: ' + status, ts3client.LogLevel.DEBUG);

  if(errno)
  {
    var error = ts3client.getErrorMessage(errno);

    ts3client.logMessage('Failed to connect: ' + error, ts3client.LogLevel.ERROR);

    process.exit();
  }
});

/**
 * Register callback function for 'onNewChannelEvent'. This will write an informational message to the
 * client log for channels announced by the server while connecting.
 */
ts3client.on('onNewChannelEvent', function(schID, channelID, channelPID)
{
  try
  {
    var channelName = ts3client.getChannelVariableAsString(schID, channelID, ts3client.ChannelProperties.NAME);

    ts3client.logMessage('Server announced channel "' + channelName + '" (id:' + channelID + ')');
  }
  catch(err)
  {
    var error = ts3client.getErrorMessage(errno);

    ts3client.logMessage('Failed to determine channel name: ' + error, ts3client.LogLevel.WARNING);
  }
});

/**
 * Register callback function for 'onNewChannelCreatedEvent'. This will write an informational message to the client log
 * whenever a new channel gets created.
 */
ts3client.on('onNewChannelCreatedEvent', function(schID, channelID, channelPID, invokerID, invokerName, invokerUID)
{
  try
  {
    var channelName = ts3client.getChannelVariableAsString(schID, channelID, ts3client.ChannelProperties.NAME);

    ts3client.logMessage('Client "' + invokerName + '" (id:' + invokerID + ') created channel "' + channelName + '" (id:' + channelID + ')');
  }
  catch(err)
  {
    var error = ts3client.getErrorMessage(errno);

    ts3client.logMessage('Failed to determine channel name: ' + error, ts3client.LogLevel.WARNING);
  }
});

/**
 * Register callback function for 'onDelChannelEvent'. This will write an informational message to the client log whenever
 * a channel gets deleted. Note, that we cannot determine the name for channels that are already deleted.
 */
ts3client.on('onDelChannelEvent', function(schID, channelID, invokerID, invokerName, invokerUID)
{
  ts3client.logMessage('Client "' + invokerName + '" deleted channel (id:' + channelID + ')');
});

/**
 * Register a callback function for 'onClientMoveEvent'. This will write an informational message to the client log whenever
 * a client gets moved, connects or disconnects.
 */
ts3client.on('onClientMoveEvent', function(schID, clientID, oldChannelID, newChannelID, visibility, moveMessage)
{
  if(!oldChannelID)
  {
    ts3client.logMessage('Client (id:' + clientID + ') connected');
  }
  else if(!newChannelID)
  {
    ts3client.logMessage('Client (id:' + clientID + ') disconnected' + (moveMessage ? ' (' + moveMessage + ')' : ''));
  }
  else
  {
    ts3client.logMessage('Client (id:' + clientID + ') switched channels; new channel is ' + newChannelID);
  }
});

/**
 * Register a callback function for 'onClientMoveTimeoutEvent'. This will write an informational message to the client
 * log for clients announced by the server.
 */
ts3client.on('onClientMoveTimeoutEvent', function(schID, clientID, oldChannelID, newChannelID, visibility, timeoutMessage)
{
  ts3client.logMessage('Client (id:' + clientID + ') timed out (' + timeoutMessage + ')');
});

/**
 * Register a callback function for 'onClientMoveSubscriptionEvent'. This will write an informational message to the client
 * log for clients announced by the server.
 */
ts3client.on('onClientMoveSubscriptionEvent', function(schID, clientID, oldChannelID, newChannelID, visibility)
{
  try
  {
    var clientName  = ts3client.getClientVariableAsString(schID, clientID, ts3client.ClientProperties.NICKNAME);

    ts3client.logMessage('Server announced client "' + clientName + '" (id:' + clientID + ')');
  }
  catch(err)
  {
    var error = ts3client.getErrorMessage(errno);

    ts3client.logMessage('Failed to determine client name: ' + error, ts3client.LogLevel.WARNING);
  }
});

/**
 * Register a callback function for 'onTalkStatusChangeEvent'. This will write a debug message to the client log whenever
 * a client starts/stops talking.
 */
ts3client.on('onTalkStatusChangeEvent', function(schID, status, isWhisper, clientID)
{
  ts3client.logMessage('Client (id:' + clientID + ') ' + (status ? 'started' : 'stopped') + ' talking', ts3client.LogLevel.INFO);
});

/**
 * Register a callback function for 'onServerErrorEvent'. This will write an error message to the client log for errors
 * reported by the server.
 */
ts3client.on('onServerErrorEvent', function(schID, error, errno, returnCode, extraMessage)
{
  if(errno)
  {
    ts3client.logMessage('Server returned error: ' + error, ts3client.LogLevel.ERROR);
  }
});

// ============================================================
// ================= MINIMAL CLIENT EXAMPLE ===================
// ============================================================

try
{
  /**
   * Initialize the ClientLib and point the resource path to the platform specific SDK\bin directory to
   * locate the sound backend libraries.
   */
  ts3client.initClientLib(ts3client.LogTypes.CONSOLE, undefined, ts3client.getResourcePath());

  /**
   * Spawn a new server connection handler and store its ID. Since we did not specify any port, the OS
   * will determine a free port for outgoing connections automatically.
   */
  var schID = ts3client.spawnNewServerConnectionHandler();

  /**
   * Open the capture/playback devices. Since we did not specify any devices, the ClientLib will use the
   * default audio devices.
   */
  ts3client.openCaptureDevice(schID);
  ts3client.openPlaybackDevice(schID);

  /**
   * Create a new client identity. In a production environment, you should do this only once and store
   * the identity locally for later use.
   */
  var ident = ts3client.createIdentity();

  /**
   * Connect to server on localhost:9987. In this example, we use the nickname 'Node.js' and join the
   * default channel 'My Channel' without a channel password. The server password is set to 'secret'.
   */
  ts3client.startConnection(schID, ident, 'localhost', 9987, 'Node.js', ['My Channel'], '', 'secret');

  /**
   * Intercept SIGINT signals, disconnect from the server and destroy the ClientLib.
   */
  process.on('SIGINT', function()
  {
    ts3client.stopConnection(schID);

    setTimeout(function()
    {
      ts3client.destroyServerConnectionHandler(schID);
      ts3client.destroyClientLib();
    }, 200);

    process.exit();
  });
}
catch(err)
{
  /**
   * Print the last known error code and the error message from the exception.
   */
  console.log('ERROR ' + ts3client.getLastError() + ': ' + err.message);

  process.exit(1);
}
