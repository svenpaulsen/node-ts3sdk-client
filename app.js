process.stdin.resume();

const ts3client = require('./build/Release/ts3client.node');

ts3client.initClientLib(2);

var schID = ts3client.spawnNewServerConnectionHandler();
var ident = ts3client.createIdentity();

ts3client.startConnection(schID, ident, "127.0.0.1", 9987, undefined, undefined, undefined, "secret");
