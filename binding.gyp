{
  "targets": [
    {
      "target_name": "ts3client",
      "sources": [
        "src/addon.cpp",
        "src/argument.cpp",
        "src/argument.h",
        "src/payload.cpp",
        "src/payload.h",
        "src/capture.cpp",
        "src/capture.h",
        "src/channel.cpp",
        "src/channel.h",
        "src/client.cpp",
        "src/client.h",
        "src/clientlib.cpp",
        "src/clientlib.h",
        "src/connection.cpp",
        "src/connection.h",
        "src/error.cpp",
        "src/error.h",
        "src/event.cpp",
        "src/event.h",
        "src/filetransfer.cpp",
        "src/filetransfer.h",
        "src/helper.cpp",
        "src/helper.h",
        "src/identity.cpp",
        "src/identity.h",
        "src/log.cpp",
        "src/log.h",
        "src/playback.cpp",
        "src/playback.h",
        "src/server.cpp",
        "src/server.h",
        "src/shared.cpp",
        "src/shared.h",
      ],
      "include_dirs": [
        "includes",
        "<!(node -e \"require('nan')\")",
      ],
      "conditions": [
        ["OS==\"win\" and target_arch==\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/windows/win64/ts3client.dll",
          ],
        }],
        ["OS==\"win\" and target_arch!=\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/windows/win32/ts3client.dll",
          ],
        }],
        ["OS==\"linux\" and target_arch==\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/linux/amd64/libts3client.so",
          ],
        }],
        ["OS==\"linux\" and target_arch!=\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/linux/x86/libts3client.so",
          ],
        }],
        ["OS==\"mac\"", {
          "libraries": [
            "<(module_root_dir)/bin/darwin/libts3client.dylib",
          ],
        }],
      ]
    }
  ]
}
