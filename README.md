# Secure Programming Final Project

### Group 2: Zach Arnett, Lennice Bolton, Joao Donaton

- Specification for [logappend](https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logappend.html)
- Specification for [logread](https://course.ece.cmu.edu/~ece732/s24/homework/bibifi/logread.html)

- <b>IMPORTANT NOTE:</b> in the current version, the token `-K` is just the string `123`
    - Use this for running `logappend` `logread` as well as the tests, as explained in the Build and Run section

### Build and Run 
- Compiling and running running requires:
    - Windows OS
    - `g++` installed
    - some form of the `cmake` command
- Building and running `logappend.exe` and `logread.exe`
    - run `make logappend` and `make logread`
    - These commands will generate executable files for each program and place them in the project's root `/`
- Running tests
    - run `make testlogappend` to make testlogappend
    - run `make testlogread TOKEN=?` where ? is the authentication token whose hash is in `/token.txt`
        - The token is used for the testlogread because it generates a dummy log full of sample data for tests to be manually run on. Therefore, the token needs to match the real one so we can decrypt it later.
    - These will automatically build and run the unit tests


### Security Details
- This project uses the [openssl](https://github.com/openssl/openssl) library to calculate hashes and perform encryption for the log
    - No additional setup is required for this
    - A precompiled version of openssl is already included in the repo and linked via the `Makefile`
- Input validation is done via Regex to match patterns that correspond to specific kinds of attacks or invalid inputs 
    - These are documented and verified in the test files under `tests/`

#### Encryption
- We use OpenSSL's AES implementation to encrypt and decrypt the logfile. 
- The logfile is stored as an encrypted file on disk and cannot be modified or read without the appropriate token `-K`
- The AES symmetric key is derived from the correct token `-K` after authentication passes
    - Therefore, there is no need to store the AES key anywhere.
- The test `make testlogread` generates an encrypted file called "logfile" that has a bunch of dummy data to test with.

### Example usage
```
# LOGAPPEND EXAMPLES -------------------------------------

# appends that the employee MahaAllouzi arrived at room 7 at timestep 1, to log.txt logfile
./logappend.exe -T 1 -K 123 -E MahaAllouzi -A -R 7 log.txt

# appends that the guest MikhailNesterenko departed from room 2 at timestep 4, to log.txt logfile
./logappend.exe -T 4 -K 123 -E MikhailNesterenko -L -R 2 log.txt

# reads batchfile.txt line by line
./logappend.exe -K 123 -B batchfile.txt

# LOGREAD EXAMPLES ---------------------------------------

# displays the names of all the guests and employees in the log file, followed by what rooms they are currently in
./logread.exe -K 123 -S log.txt

# displays a list of rooms that the specified guest (MikhailNesterenko) entered
./logread.exe -K 123 -R -G MikhailNesterenko log.txt

# displays a list of rooms that the specified employee (MahaAllouzi) entered
./logread.exe -K 123 -R -E MahaAllouzi log.txt
```

### Further documentation
- The format for the log file is the following:
```
[TIMESTAMP] room "ROOMID": (guest | employee) "NAME" (departed | arrived)
```
- Where: uppercase words are the parameters and every entry ends in a `\n` (newline)
