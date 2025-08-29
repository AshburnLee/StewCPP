
确保你的编译器版本

CC=/usr/bin/gcc-11 CXX=/usr/bin/g++-11 cmake .. -DSTEWCPP_COMPILER=/usr/bin/g++-11 -DSTEWC_COMPILER=/usr/bin/gcc-11

## PrepareCPP

知识点理解: 
“标准库中，这个点是如何应用的？”
“编译器遇到这个点时的行为是什么？”


## Debug Config

参考以下模板

```json
{
    "configurations": [
    {
        "name": "(gdb) Launch",
        "type": "cppdbg",
        "request": "launch",
        "program": "PATH/a.out",
        "args": ["arg1", "arg2", "arg3"],
        "stopAtEntry": true,
        "cwd": "${fileDirname}",
        "environment": [{"name": "NUM_THREADS", "value": "1"}],
        "externalConsole": false,
        "MIMode": "gdb",
        "setupCommands": [
            {
                "description": "Enable pretty-printing for gdb",
                "text": "-enable-pretty-printing",
                "ignoreFailures": true
            },
            {
                "description":  "Set Disassembly Flavor to Intel",
                "text": "-gdb-set disassembly-flavor intel",
                "ignoreFailures": true
            }
        ]
    }
    ]
}
```
