# USE: mingw32-make


# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# --------------------------------------------------------
# PATHS
# --------------------------------------------------------
SRC_DIR = src
SSL_DIR = libs/openssl

# Where to look for .h files (Both your src folder and OpenSSL)
INCLUDES = -I$(SRC_DIR) -I$(SSL_DIR)/include

# --------------------------------------------------------
# LIBRARIES
# --------------------------------------------------------
# Point specifically to the "MD" folder inside VC/x64
SSL_PATH = libs/openssl/lib/VC/x64/MD

# Link the libraries found in that folder
SSL_LIBS = $(SSL_PATH)/libssl.lib $(SSL_PATH)/libcrypto.lib

# Windows System libraries
SYS_LIBS = -lws2_32 -lgdi32 -lcrypt32

# Combine them for the linker
LDFLAGS = $(SSL_LIBS) $(SYS_LIBS)

# --------------------------------------------------------
# SOURCE FILES
# --------------------------------------------------------
# Common logic used by both programs
COMMON_SRC = $(SRC_DIR)/common.cpp

# --------------------------------------------------------
# BUILD RULES
# --------------------------------------------------------

# 'all' is the default target. It builds both programs.
all: logappend logread

# Rule to build logappend.exe
# Depends on: logappend.cpp AND common.cpp
logappend: $(SRC_DIR)/logappend.cpp $(COMMON_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC_DIR)/logappend.cpp $(COMMON_SRC) -o logappend.exe $(LDFLAGS)

# Rule to build logread.exe
# Depends on: logread.cpp AND common.cpp
logread: $(SRC_DIR)/logread.cpp $(COMMON_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC_DIR)/logread.cpp $(COMMON_SRC) -o logread.exe $(LDFLAGS)

openssltest: openssl_test.cpp $(COMMON_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) openssl_test.cpp $(COMMON_SRC) -o test.exe $(LDFLAGS)

# Clean up command (Windows 'del')
clean:
	del logappend.exe logread.exe