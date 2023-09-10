Visual Studio Code
==================

Settings
--------

Recommended `.vscode/settings.json`:

```jsonc
{
  "[c]": {
    "files.encoding": "utf8",
    "editor.defaultFormatter": "xaver.clang-format"
  },
  "[cpp]": {
    "files.encoding": "utf8",
    "editor.defaultFormatter": "xaver.clang-format"
  },
  "[python]": {
    "editor.defaultFormatter": "ms-python.black-formatter"
  },
  "files.insertFinalNewline": true,
  "files.trimFinalNewlines": true,
  "search.useIgnoreFiles": false,
  "search.exclude": {
    "build/*/config.json": true,
    "build/**/*.MAP": true,
    "build.ninja": true,
    ".ninja_*": true,
    "objdiff.json": true,
  }
}
```

C/C++ configuration
-------------------

Recommended `.vscode/c_cpp_properties.json`:

```jsonc
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/include/**"
            ],
            "cStandard": "c99",
            "cppStandard": "c++98",
            "intelliSenseMode": "linux-clang-x86",
            "compilerPath": "",
            "configurationProvider": "ms-vscode.makefile-tools",
            "browse": {
                "path": [
                    "${workspaceFolder}/include"
                ],
                "limitSymbolsToIncludedHeaders": true
            }
        }
    ],
    "version": 4
}
```
