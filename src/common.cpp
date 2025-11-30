#include "common.hpp"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>

std::map<std::string, std::string> parseArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> arguments;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        // Check for the last argument (log file)
        if (i == argc-1) {
            if (arg[0] != '-') {
                std::string value = arg;
                arguments["log"] = value;
            }
        }
        // Check for 2nd to last argument being a flag without value
        else if (i == argc-2) {
            if (arg[0] == '-') {
                std::string key = arg;
                std::string value = "true"; // Flag without value
                arguments[key] = value;
                continue;
            }
        }

        // Process flags and their values
        if (arg[0] == '-') {
            std::string key = arg;
            std::string value;
            if ((i + 1) < argc && argv[i + 1][0] != '-') {
                value = argv[++i];
            } else {
                value = "true"; // Flag without value
            }
            arguments[key] = value;
        }
    }

    return arguments;
}

// see hpp
std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string piece;

    while (std::getline(ss, piece, delimiter)) {
        result.push_back(piece);
    }

    return result;
}

void printArgs(std::map<std::string, std::string> args) {
    for (auto i = args.begin(); i != args.end(); i++) {
        std::cout << i->first << " " << i->second << std::endl;
    }
}

std::string sha256(const std::string s) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(s.c_str()),
           s.size(),
           hash);

    std::ostringstream oss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(hash[i]);
    }

    return oss.str();
}


void deriveKey(const std::string& token, unsigned char* key, const unsigned char* salt)
{
    PKCS5_PBKDF2_HMAC(
        token.c_str(), token.length(),
        salt, 16,
        10000,
        EVP_sha256(),
        32,
        key
    );
}

std::string encryptData(const std::string& plaintext, const unsigned char* key)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(!ctx)return "";

    unsigned char iv[12];
    RAND_bytes(iv, sizeof(iv));

    std::vector<unsigned char> ciphertext(plaintext.size() + EVP_CIPHER_block_size(EVP_aes_256_gcm()));

    int len = 0;
    int ciphertext_len = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, iv);
    

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, (const unsigned char*)plaintext.c_str(), plaintext.size());
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    unsigned char tag[16];
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag);

    EVP_CIPHER_CTX_free(ctx);

    std::string result;
    result.append((char*)iv, 12);
    result.append((char*)ciphertext.data(), ciphertext_len);
    result.append((char*)tag, 16);
    return result;
}


std::string decryptData(const std::string& encrypted, const unsigned char* key)
{
    if(encrypted.size() < 28) return "";

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(!ctx) return "";

    unsigned char iv[12];
    memcpy(iv, encrypted.data(), 12);

    unsigned char tag[16];
    memcpy(tag, encrypted.data() + encrypted.size() - 16, 16);

    int ciphertext_len = encrypted.size() - 28;
    const unsigned char* ciphertext = (const unsigned char*)encrypted.data() + 12;

    std::vector<unsigned char> plaintext(ciphertext_len + EVP_CIPHER_block_size(EVP_aes_256_gcm()));
    int len = 0;
    int plaintext_len = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext, ciphertext_len);
    plaintext_len = len;

    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag);

    int ret = EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);

    EVP_CIPHER_CTX_free(ctx);

    if(ret <= 0) {
        return "";
    }
    plaintext_len += len;

    return std::string((char*)plaintext.data(), plaintext_len);
}
