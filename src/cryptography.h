#pragma once

#include <array>
#include <memory>
#include "openssl/evp.h"

#include "globals.h"

using EVP_CIPHER_CTX_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)>;

using Key = std::array<byte, 32>;
using Salt = std::array<byte, PKCS5_SALT_LEN>;
using IV = std::array<byte, EVP_MAX_IV_LENGTH>;

class Cryptography
{
public:
    Cryptography();
    Cryptography(Salt salt, IV iv);
    ~Cryptography();
    
    Salt get_salt();
    IV get_IV();

    int generate_parameters();
    int generate_key(const std::string& password);
    
    byte_string encrypt(const byte_string& plaintext);
    byte_string decrypt(const byte_string& ciphertext);
private:
    Salt m_salt;
    IV m_iv; 
    Key m_key;
};