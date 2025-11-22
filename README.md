# Secure Programming Final Project

### Group 2: Zach Arnett, Lennice Bolton, Joao Donaton

- Specification [logappend](https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logappend.html)
- Specification [logread](https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logread.html)

### Setup
-


### Documentation
- The format for the log file is the following:
```
[TIMESTAMP] room "ROOMID": (guest | employee) "NAME" (departed | arrived)
```
- Where: uppercase words are the parameters and every entry ends in a `\n` (newline)

### MSYS2 
- Install MSYS2 (https://www.msys2.org/)
- Open MSYS2 MINGW shell (it's a program called "MSYS2 MINGW64"), HAS TO BE THIS SHELL NOT THE DEFAULT MSYS2 ONE
- run `pacman -S mingw-w64-x86_64-openssl` to install openssl dependency
- Now we need to add the MSYS2 mingw shell to vscode
- Open Vscode, press ctrl+shift+p go to "Preferences: open user settings (JSON)"
- Add this inside the top level object:
```
"terminal.integrated.profiles.windows": {
        "MSYS2 MINGW64": {
            "path": "C:\\msys64\\usr\\bin\\bash.exe",
            "args": ["-li"],
            "env": { "MSYSTEM": "MINGW64" },
            "icon": "terminal-bash"
        }
    },
```
- Now you can open the shell inside vscode by doing ctrl+shift+p and "create new terminal (with profile)" and selecting MSYS2
- Then go to this project's path by doing `cd PATH_TO_ROOT_OF_PROJECT` 

- Also, VSCode will show errors in the `#include <>` for openssl stuff, because you need to add the headers to the include path
    - Do this by: ctrl+shift+p, then int "c/c++: edit configurations"
    - In here, find include path, in a new line, add the path to the include folder for your msys mingw64 installation, example of what it should look like:
```
${workspaceFolder}/**
${workspaceFolder}/libsodium/include
C:\msys64\mingw64\include
```

- Example compile command:
    - `g++ openssl_test.cpp -I/mingw64/include -L/mingw64/lib -lssl -lcrypto -o openssl_test.exe`