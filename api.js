/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

const os   = require('os');
const path = require('path');

try
{
  console.log(getResourcePath());

  module.exports = require(getBindingsPath());

  module.exports.getBindingsPath  = getBindingsPath;
  module.exports.getResourcePath  = getResourcePath;
  module.exports.getPlatform      = getPlatform;
}
catch(err)
{
  console.log(err);
}

function getBindingsPath()
{
  return path.resolve(path.join(__dirname, './bin/' + getPlatform() + '/ts3client.node'));
}

function getResourcePath()
{
  return path.resolve(path.join(__dirname, './bin/' + getPlatform())) + '/';
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
