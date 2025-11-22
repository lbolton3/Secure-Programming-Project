# Secure Programming Final Project

### Group 2: Zach Arnett, Lennice Bolton, Joao Donaton

- Specification for [logappend](https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logappend.html)
- Specification for [logread](https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logread.html)

### Build and Run 
- Compiling and running running requires:
    - Windows OS
    - `g++` installed
    - some form of the `cmake` command
- Building and running `logappend.exe` and `logread.exe`
    - run `make logappend` and `make logread`
    - These commands will generate executable files for each program and place them in the project's root `/`
- Running tests
    - run `make testlogappend` and `make testlogread`
    - These will automatically build and run the unit tests


### Security Details
- This project uses the [openssl](https://github.com/openssl/openssl) library to calculate hashes and perform encryption for the log
    - No additional setup is required for this
    - A precompiled version of openssl is already included in the repo and linked via the `Makefile`
- Input validation is done via Regex to match patterns that correspond to specific kinds of attacks or invalid inputs 
    - These are documented and verified in the test files under `tests/`

### Example usage
- <b>IMPORTANT NOTE:</b> in the current version, the token `-K` is just the string `123`
```
# LOGREAD EXAMPLES
./logread 
TODO...

# LOGAPPEND EXAMPLES

# appends that the employee MahaAllouzi arrived at room 7 at timestep 1, to log.txt logfile
./logappend.exe -T 1 -K 123 -E MahaAllouzi -A -R 7 log.txt

# appends that the guest MikhailNesterenko departed from room 2 at timestep 4, to log.txt logfile
./logappend.exe -T 4 -K 123 -E MikhailNesterenko -L -R 2 log.txt

# reads batchfile.txt line by line
./logappend.exe -K 123 -B batchfile.txt
```

### Further documentation
- The format for the log file is the following:
```
[TIMESTAMP] room "ROOMID": (guest | employee) "NAME" (departed | arrived)
```
- Where: uppercase words are the parameters and every entry ends in a `\n` (newline)
