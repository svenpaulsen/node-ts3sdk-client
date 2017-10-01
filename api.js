/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

const fs   = require('fs');
const os   = require('os');
const path = require('path');

try
{
  module.exports = require('./bin/' + getPlatform() + '/ts3client.node');

  module.exports.getBindingsPath  = getBindingsPath;
  module.exports.getResourcePath  = getResourcePath;
  module.exports.getPlatform      = getPlatform;

  module.exports.LogTypes = {
    NONE:          0x00,
    FILE:          0x01,
    CONSOLE:       0x02,
    USERLOGGING:   0x04,
    NO_NETLOGGING: 0x08,
    DATABASE:      0x0010,
    SYSLOG:        0x0020
  }

  module.exports.LogLevel = {
    CRITICAL: 0x00,
    ERROR:    0x01,
    WARNING:  0x02,
    DEBUG:    0x03,
    INFO:     0x04,
    DEVEL:    0x05
  };

  module.exports.Visibility = {
    ENTER:  0x00,
    RETAIN: 0x01,
    LEAVE:  0x02
  }

  module.exports.ConnectStatus = {
    DISCONNECTED: 0x00,
    CONNECTING:   0x01,
    CONNECTED:    0x02,
    ESTABLISHING: 0x03,
    ESTABLISHED:  0x04
  }

  module.exports.TalkStatus = {
    NOT_TALKING:            0x00,
    TALKING:                0x01,
    TALKING_WHILE_DISABLED: 0x02
  }

  module.exports.CodecType = {
    SPEEX_NARROWBAND:    0x01,
    SPEEX_WIDEBAND:      0x02,
    SPEEX_ULTRAWIDEBAND: 0x03,
    CELT_MONO:           0x04,
    OPUS_VOICE:          0x05,
    OPUS_MUSIC:          0x06
  }

  module.exports.CodecEncryptionMode = {
    PER_CHANNEL: 0x00,
    FORCED_OFF:  0x01,
    FORCED_ON:   0x02
  }

  module.exports.TextMessageTargetMode = {
    CLIENT:  0x01,
    CHANNEL: 0x02,
    SERVER:  0x03
  }

  module.exports.MuteInputStatus = {
    NONE:  0x00,
    MUTED: 0x01
  }

  module.exports.MuteOutputStatus = {
    NONE:  0x00,
    MUTED: 0x01
  }

  module.exports.HardwareInputStatus = {
    DISABLED: 0x00,
    ENABLED:  0x01
  }

  module.exports.HardwareOutputStatus = {
    DISABLED: 0x00,
    ENABLED:  0x01
  }

  module.exports.InputDeactivationStatus = {
    ACTIVE:      0x00,
    DEACTIVATED: 0x01,
  }

  module.exports.ReasonIdentifier = {
    NONE:                             0x00,
    MOVED:                            0x01,
    SUBSCRIPTION:                     0x02,
    LOST_CONNECTION:                  0x03,
    KICK_CHANNEL:                     0x04,
    KICK_SERVER:                      0x05,
    KICK_SERVER_BAN:                  0x06,
    SERVERSTOP:                       0x07,
    CLIENTDISCONNECT:                 0x08,
    CHANNELUPDATE:                    0x09,
    CHANNELEDIT:                      0x0A,
    CLIENTDISCONNECT_SERVER_SHUTDOWN: 0x0B
  }

  module.exports.ChannelProperties = {
    NAME:                 0x00,
    TOPIC:                0x01,
    DESCRIPTION:          0x02,
    PASSWORD:             0x03,
    CODEC:                0x04,
    CODEC_QUALITY:        0x05,
    MAXCLIENTS:           0x06,
    MAXFAMILYCLIENTS:     0x07,
    ORDER:                0x08,
    FLAG_PERMANENT:       0x09,
    FLAG_SEMI_PERMANENT:  0x0A,
    FLAG_DEFAULT:         0x0B,
    FLAG_PASSWORD:        0x0C,
    CODEC_LATENCY_FACTOR: 0x0D,
    CODEC_IS_UNENCRYPTED: 0x0E,
    SECURITY_SALT:        0x0F,
    DELETE_DELAY:         0x10
  }

  module.exports.ClientProperties = {
    UNIQUE_IDENTIFIER:        0x00,
    NICKNAME:                 0x01,
    VERSION:                  0x02,
    PLATFORM:                 0x03,
    FLAG_TALKING:             0x04,
    INPUT_MUTED:              0x05,
    OUTPUT_MUTED:             0x06,
    OUTPUTONLY_MUTED:         0x07,
    INPUT_HARDWARE:           0x08,
    OUTPUT_HARDWARE:          0x09,
    INPUT_DEACTIVATED:        0x0A,
    IDLE_TIME:                0x0B,
    DEFAULT_CHANNEL:          0x0C,
    DEFAULT_CHANNEL_PASSWORD: 0x0D,
    SERVER_PASSWORD:          0x0E,
    META_DATA:                0x0F,
    IS_MUTED:                 0x10,
    IS_RECORDING:             0x11,
    VOLUME_MODIFICATOR:       0x12,
    VERSION_SIGN:             0x13,
    SECURITY_HASH:            0x14
  }

  module.exports.VirtualServerProperties = {
    UNIQUE_IDENTIFIER:     0x00,
    NAME:                  0x01,
    WELCOMEMESSAGE:        0x02,
    PLATFORM:              0x03,
    VERSION:               0x04,
    MAXCLIENTS:            0x05,
    PASSWORD:              0x06,
    CLIENTS_ONLINE:        0x07,
    CHANNELS_ONLINE:       0x08,
    CREATED:               0x09,
    UPTIME:                0x0A,
    CODEC_ENCRYPTION_MODE: 0x0B
  }
}
catch(err)
{
  console.log(err);
}

function getBindingsPath()
{
  return getResourcePath() + 'ts3client.node';
}

function getResourcePath()
{
  var relPath = './bin/' + getPlatform();
  var absPath = path.resolve(path.join(__dirname, 'node_modules/node-ts3sdk-client', relPath));

  try
  {
    if(fs.statSync(absPath).isDirectory())
    {
      return path.normalize(absPath) + path.sep;
    }
  }
  catch(err)
  {
    absPath = path.resolve(path.join(__dirname, relPath));
  }

  try
  {
    if(fs.statSync(absPath).isDirectory())
    {
      return path.normalize(absPath) + path.sep;
    }
  }
  catch(err)
  {}

  return relPath + path.sep;
}

function getPlatform()
{
  switch(os.type())
  {
    case 'Windows_NT':
      return (os.arch() == 'x64' ? 'win64' : 'win32');
    case 'Linux':
      return (os.arch() == 'x64' ? 'linux_amd64' : 'linux_x86');
    case 'Darwin':
      return 'mac';
    default:
      return 'unknown';
  }
}
