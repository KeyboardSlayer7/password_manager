#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "options.h"
#include "globals.h"

#include "cryptography.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

void sign_up()
{
    std::cout << "\nSign up\n";
    std::string username = input("\nUsername: "); 

    disable_echo();    
    std::string password = input("Password: ");
    enable_echo();

    std::fstream file("C:/etc/users.json", std::ios_base::in | std::ios_base::out);

    json file_json = json::parse(file);

    file_json[username] = sha256(password);

    file.seekg(0, file.beg);
    file << std::setw(4) << file_json << std::endl;

    file.close();
}

bool login(std::string& password_out)
{
    std::cout << "\nLog in\n";
    std::string username = input("\nUsername: "); 

    disable_echo();    
    std::string password = input("Password: ");
    enable_echo();

    std::fstream file("C:/etc/users.json", std::ios_base::in | std::ios_base::out);

    json file_json = json::parse(file);

    try
    {
        if (file_json.at(username) == sha256(password))
        {
            password_out = password; 
            return true;
        } 
        else
        {
            return false;
        }
    }
    catch(const json::out_of_range& e)
    {
        // std::cout << "\n\033[91m[ERROR] No such user \n\033[m";
        return false;
    }

    file.close();   
}

void new_entry(json& data, std::string& password)
{
    Cryptography generator;
    generator.generate_parameters();
    generator.generate_key(password.c_str());

    std::cout << "\n";
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
    std::cout << "\n";
    std::string website = input("Website: ");

    std::vector<std::string> website_password; 

    try { 
        website_password = data.at(website);
    }
    catch (const json::out_of_range& e)
    {
        std::cout << "\n\033[91m[ERROR] No such website \n\033[m";
        return;
    }

    Salt salt;
    un_hex(website_password[0], salt.data(), PKCS5_SALT_LEN);

    // std::cout << website_password[0] << "\n";
    // print_array(salt.data(), PKCS5_SALT_LEN); 

    IV iv;
    un_hex(website_password[1], iv.data(), EVP_MAX_IV_LENGTH);

    std::array<byte, 128> ciphertext;
    size_t ciphertext_length = un_hex(website_password[2], ciphertext.data(), website_password[2].length());

    Cryptography generator(salt, iv);
    generator.generate_key(password);

    byte_string plaintext = generator.decrypt(byte_string(ciphertext.begin(), ciphertext.begin() + ciphertext_length));

    copy(plaintext);
    std::cout << website << "'s password: " << plaintext.c_str() << "\n";
}

// might not need this, could just use new_entry?
// void update_entry(json& data)
// {
    
// }

void delete_entry(json& data)
{
    std::cout << "\n";
    std::string website = input("Website: ");

    std::string prompt = "\n\033[91mDelete password for " + website + "? (y/N): \033[m"; 
    std::string option = input(prompt.c_str());

    if (option[0] == 'y') 
    {
        data[website].clear();
        data.erase(website);
    }
    else if (option[0] == 'N')
    {
        return;
    }
    else
    {
        std::cout << "Invalid Option \n";
        delete_entry(data);
    }
}