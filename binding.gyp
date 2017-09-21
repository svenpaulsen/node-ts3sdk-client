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
            "<(module_root_dir)/bin/ts3client_win64.lib",
          ]
        }],
        ["OS==\"win\" and target_arch!=\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/ts3client_win32.lib",
          ],
        }],
        ["OS==\"linux\" and target_arch==\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/libts3client_linux_amd64.so",
          ]
        }],
        ["OS==\"linux\" and target_arch!=\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/libts3client_linux_x86.so",
          ]
        }],
        ["OS==\"mac\"", {
          "libraries": [
            "<(module_root_dir)/bin/libts3client_mac.dylib",
          ],
          "postbuilds": [{
            "postbuild_name": "Adjust link path to TeamSpeak SDK ClientLib",
            "action": [
              "install_name_tool",
              "-change",
              "/usr/local/lib/libts3client.dylib",
              "@loader_path/libts3client_mac.dylib",
              "<@(PRODUCT_DIR)/ts3client.node"
            ]
          }]
        }]
      ]
    },
    {
      "target_name": "ts3client_deploy",
      "type": "none",
      "dependencies": [
        "ts3client"
      ],
      "copies": [{
        "destination": "<(module_root_dir)/bin/",
        "files": [
          "<(module_root_dir)/build/Release/ts3client.node"
        ]
      }]
    }
  ]
}
