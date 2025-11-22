#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void sha256_example() {
    std::string input = "hello world";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    std::cout << "SHA256: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    std::cout << std::dec << "\n";
}

void aes_encrypt_example() {
    const unsigned char plaintext[] = "secret message";
    const int plaintext_len = sizeof(plaintext) - 1;

    unsigned char key[32];
    unsigned char iv[16];

    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    unsigned char ciphertext[128];
    int len, ciphertext_len;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    std::cout << "AES-256-CBC ciphertext (" << ciphertext_len << " bytes): ";
    for (int i = 0; i < ciphertext_len; i++)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)ciphertext[i];
    std::cout << std::dec << "\n";
}

int main() {
    sha256_example();
    aes_encrypt_example();
    return 0;
}
