#include <iostream>
#include <vector>

#include "options.h"
#include "globals.h"

#include "cryptography.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

void new_entry(json& data, std::string& password)
{
    Cryptography generator;
    generator.generate_parameters();
    generator.generate_key(password.c_str());

    std::string website = input("Website: ");
    std::string website_password = input("Website Password: ");

    byte_string ciphertext = generator.encrypt((unsigned char*)website_password.c_str());

    website_password = to_hex(ciphertext.data(), ciphertext.length());

    Salt salt = generator.get_salt();
    IV iv = generator.get_IV();

    data[website] = {to_hex(salt.data(), PKCS5_SALT_LEN), to_hex(iv.data(), EVP_MAX_IV_LENGTH), website_password};
}

void get_entry(json& data, std::string& password)
{
    std::string website = input("Website: ");

    std::vector<std::string> website_password = data[website];

    Salt salt;
    un_hex(website_password[0], salt.data(), PKCS5_SALT_LEN);

    std::cout << website_password[0] << "\n";
    print_array(salt.data(), PKCS5_SALT_LEN); 

    IV iv;
    un_hex(website_password[1], iv.data(), EVP_MAX_IV_LENGTH);

    std::array<byte, 128> ciphertext;
    size_t ciphertext_length = un_hex(website_password[2], ciphertext.data(), website_password[2].length());

    Cryptography generator(salt, iv);
    generator.generate_key(password);

    byte_string plaintext = generator.decrypt(byte_string(ciphertext.begin(), ciphertext.begin() + ciphertext_length));

    std::cout << website << "'s password: " << plaintext.c_str() << "\n";
}

// might not need this, could just use new_entry?
// void update_entry(json& data)
// {
    
// }

void delete_entry(json& data)
{
    std::string website = input("Website: ");

    std::string prompt = "Delete password for " + website + " (Yes/No): "; 
    std::string option = input(prompt.c_str());

    if (option == "Yes")
    {
        data[website].clear();
        data.erase(website);
    }
    else if (option == "No")
    {
        return;
    }
    else
    {
        std::cout << "Invalid Option \n";
        delete_entry(data);
    }
}