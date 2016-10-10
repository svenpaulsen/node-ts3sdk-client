{
  "targets": [
    {
      "target_name": "ts3client",
      "sources": [
        "src/addon.cpp",
        "src/argument.cpp",
        "src/argument.h",
        "src/callback.cpp",
        "src/callback.h",
        "src/capture.cpp",
        "src/capture.h",
        "src/clientlib.cpp",
        "src/clientlib.h",
        "src/connection.cpp",
        "src/connection.h",
        "src/error.cpp",
        "src/error.h",
        "src/event.cpp",
        "src/event.h",
        "src/identity.cpp",
        "src/identity.h",
        "src/log.cpp",
        "src/log.h",
        "src/playback.cpp",
        "src/playback.h",
        "src/queue.h",
        "src/shared.cpp",
        "src/shared.h",
        "src/singleton.h",
      ],
      "include_dirs": [
        "includes",
        "<!(node -e \"require('nan')\")",
      ],
      "conditions": [
        ["OS==\"win\" and target_arch==\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/ts3client_win64.dll",
          ],
        }],
        ["OS==\"win\" and target_arch!=\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/ts3client_win32.dll",
          ],
        }],
        ["OS==\"linux\" and target_arch==\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/libts3client_linux_amd64.so",
          ],
        }],
        ["OS==\"linux\" and target_arch!=\"x64\"", {
          "libraries": [
            "<(module_root_dir)/bin/libts3client_linux_x86.so",
          ],
        }],
        ["OS==\"mac\"", {
          "libraries": [
            "<(module_root_dir)/bin/libts3client_mac.dylib",
          ],
        }],
      ]
    }
  ]
}
