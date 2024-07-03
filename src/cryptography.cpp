#include <iostream>

#include "cryptography.h"
#include "globals.h"

#include "openssl/evp.h"
#include "openssl/rand.h"
#include "openssl/err.h"

Cryptography::Cryptography()
{

}

Cryptography::Cryptography(Salt salt, IV iv)
{
    m_salt = salt;
    m_iv = iv;
}

Salt Cryptography::get_salt()
{
    return m_salt;
}

IV Cryptography::get_IV()
{
    return m_iv;
}

int Cryptography::generate_parameters()
{
    int output = 1;

    if (!RAND_bytes(m_salt.data(), PKCS5_SALT_LEN))
        output = 0;

    print_array(m_salt.data(), PKCS5_SALT_LEN); 

    if (!RAND_bytes(m_iv.data(), EVP_MAX_IV_LENGTH))
        output = 0;

    return output;
}

int Cryptography::generate_key(const std::string& password)
{
    int output = 1;

    output = PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), m_salt.data(), PKCS5_SALT_LEN, PKCS5_DEFAULT_ITER, EVP_sha256(), m_key.size(), m_key.data());

    if (!output)
        throw std::runtime_error("PKCS5_PBKDF2_HMAC() Failed\n");

    return output;
}

byte_string Cryptography::encrypt(const byte_string& plaintext)
{
    EVP_CIPHER_CTX_ptr cipher_ctx(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);

    if (!EVP_EncryptInit_ex(cipher_ctx.get(), EVP_aes_256_cbc(), NULL, m_key.data(), m_iv.data()))
        std::exit(EXIT_FAILURE);

    std::array<byte, 128> ciphertext;
    
    size_t length; 
    size_t ciphertext_length;
    
    if (!EVP_EncryptUpdate(cipher_ctx.get(), ciphertext.data(), (int*)&length, plaintext.data(), plaintext.length()))
        std::exit(EXIT_FAILURE);

    ciphertext_length = length;

    if (!EVP_EncryptFinal_ex(cipher_ctx.get(), ciphertext.data() + length, (int*)&length))
        std::exit(EXIT_FAILURE);

    ciphertext_length += length;

    return byte_string(ciphertext.begin(), ciphertext.begin() + ciphertext_length); 
}

byte_string Cryptography::decrypt(const byte_string& ciphertext)
{
    EVP_CIPHER_CTX_ptr cipher_ctx(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);

    if (!EVP_DecryptInit_ex(cipher_ctx.get(), EVP_aes_256_cbc(), NULL, m_key.data(), m_iv.data()))
        std::exit(EXIT_FAILURE);

    std::array<byte, 128> plaintext;

    size_t length;
    size_t plaintext_length;

    if (!EVP_DecryptUpdate(cipher_ctx.get(), plaintext.data(), (int*)&length, ciphertext.data(), ciphertext.length()))
        std::exit(EXIT_FAILURE);

    plaintext_length = length;

    if (!EVP_DecryptFinal_ex(cipher_ctx.get(), plaintext.data() + length, (int*)&length))
    {
        unsigned long error = ERR_peek_last_error();

        std::cout << "[ERROR] " << error << "\n";
        std::cout << "\t" << ERR_error_string(error, NULL) << "\n";
        std::cout << "\t" << ERR_lib_error_string(error) << "\n"; 
        std::cout << "\t" << ERR_reason_error_string(error) << "\n";

        std::exit(EXIT_FAILURE);  
    }
    
    plaintext_length += length;

    return byte_string(plaintext.begin(), plaintext.begin() + plaintext_length);
}

Cryptography::~Cryptography()
{

}