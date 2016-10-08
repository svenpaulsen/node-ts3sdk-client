{
  "targets": [
    {
      "target_name": "ts3client",
      "sources": [
        "src/addon.cpp",
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
