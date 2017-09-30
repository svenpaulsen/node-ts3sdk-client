/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

const os = require("os");

try
{
  module.exports = require("./bin/" + getPlatform() + "/ts3client.node");

  module.exports.getPlatform = getPlatform;
}
catch(err)
{
  console.log(err);
}

function getPlatform()
{
  switch(os.type())
  {
    case "Windows_NT":
      return (os.arch() == "x86" ? "win32" : "win64");
    case "Linux":
      return (os.arch() == "x86" ? "linux_x86" : "linux_amd64");
    case "Darwin":
      return "darwin";
    default:
      return "unknown";
  }
}
