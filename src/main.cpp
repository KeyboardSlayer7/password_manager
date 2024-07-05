#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <Windows.h>

#include "globals.h"
#include "options.h"
#include "nlohmann/json.hpp"
#include "cryptography.h"

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    std::string user = input("Password Manager\n  (1) Login\n  (2) Sign up\nYour selection?: ");

    if (user[0] == '2')
    {
        sign_up();
    }

    std::string password; 
    
    if (!login(password))
    {
        std::cout << "\n\n\033[91m[ERROR] Incorrect username or password! \n\n\033[m";
        main(argc, argv);
    }

    std::fstream file("C:/etc/manager.json", std::ios_base::in | std::ios_base::out);

    json json_file = json::parse(file);

    bool running = true;
 
    while (running)
    {
        std::string user_input;
        
        user_input = input("\nMain Menu\n  (1) New\n  (2) Get Exisiting\n  (3) Update Exisiting\n  (4) Delete Exisiting\n  (5) Exit\nYour selection?: ");
        char option = user_input[0];

        switch (option)
        {
            case '1':
                new_entry(json_file, password);
                break;
            case '2':
                get_entry(json_file, password);
                break;
            case '3':
                std::cout << "Not Implemented Yet \n";
                break;
            case '4':
                delete_entry(json_file); 
                break;
            case '5':
                std::cout << "\nQuitting\n";
                running = false;
                break;
            default:
                std::cout << "Invalid input \n";
                continue;
        }

        if (file.is_open())
        {
            file.seekg(0, file.beg);
            file << std::setw(4) << json_file << std::endl;
        }
        // else
        // {
        //     std::cout << "File is open: " << std::boolalpha << file.is_open() << "\n";
        // }
    }
    
    file.close();
}
