{
  "targets": [
    {
      "target_name": "jsecrypt",
      "sources": [
        "addon.cpp",
        "errors.cpp",
        "secure_message.cpp",
        "secure_keygen.cpp",
        "secure_session.cpp",
        "secure_cell_seal.cpp",
        "secure_cell_context_imprint.cpp",
        "secure_cell_token_protect.cpp",
        "secure_comparator.cpp",
      ],
      "include_dirs": [
         "<!(node -e \"require('nan')\")",
      ],
      "conditions": [
        [ "OS=='linux' or OS=='mac'", {
          "libraries": [
            "-L/usr/local/lib",
            "-L/usr/lib",
            "-lecconnect",
            "-lecrypt",
          ],
        }],
        [ "OS=='win'", {
          "libraries": [
            "libecconnect.dll.a",
            "libecrypt.dll.a",
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "AdditionalIncludeDirectories": [
                "<!(echo %ProgramFiles%)\\Ecrypt\\include",
              ],
            },
            "VCLinkerTool": {
              "AdditionalLibraryDirectories": [
                "<!(echo %ProgramFiles%)\\Ecrypt\\lib",
              ],
            },
          },
        }],
      ],
    }
  ]
}
