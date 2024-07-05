#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <Windows.h>

#include "globals.h"

int ctoi(char c)
{
    if (isdigit(c))
    {
        return (int)c - '0';
    }
    else
    {
        return (int)c - 87;
    }
}

std::string input(const char* message)
{
    std::cout << message; 

    std::string buffer;
    std::getline(std::cin, buffer);

    return buffer;
}

std::string to_hex(const unsigned char* text, size_t length)
{
    std::stringstream ss;

    for (size_t i = 0; i < length; i++)
    {
        ss << std::setfill('0') << std::setw(sizeof(char) * 2) << std::hex << static_cast<int>(text[i]);
    } 

    return ss.str();
}

size_t un_hex(std::string hex_string, unsigned char* plaintext, size_t length)
{
    int index = 0;
    for (size_t i = 0; i < hex_string.size(); i += 2)
    {
        // std::cout << ctoi(hex_string[i]) << "* 16 + " << ctoi(hex_string[i + 1]) << "\n";
        unsigned char val = ctoi(hex_string[i]) * 16 + ctoi(hex_string[i + 1]);
        plaintext[index] = val;
        index++; 
    }

    return hex_string.size() / 2;
}

void print_array(unsigned char* array, size_t length)
{
    std::cout << "[";
    for (size_t i = 0; i < length; ++i)
    {
        if (i != length - 1)
        {
            std::cout << (int)array[i] << ", ";
        }
        else
        {
            std::cout << (int)array[i] << "]\n";
        }

    }
}

void copy(const byte_string& text)
{   
    if (!OpenClipboard(NULL))
    {
        std::string message = "\n\033[91m[ERROR] " + std::to_string(GetLastError()) + "\033[m"; 
        throw std::runtime_error(message);
    }

    EmptyClipboard();

    HGLOBAL handle = GlobalAlloc(GMEM_MOVEABLE, (text.length() + 1) * sizeof(byte));

    if (handle == NULL)
    {
        std::string message = "\n\033[91m[ERROR] " + std::to_string(GetLastError()) + "\033[m";
        throw std::runtime_error(message);
    }

    LPTSTR lptstr = (LPTSTR)GlobalLock(handle);
    
    if (lptstr == NULL)
    {
        std::string message = "\n\033[91m[ERROR] " + std::to_string(GetLastError()) + "\033[m";
        throw std::runtime_error(message);
    }

    memcpy(lptstr, text.data(), text.length() * sizeof(byte));
    lptstr[text.length()] = '\0'; 

    if (!GlobalUnlock(handle) && GetLastError() > 0)
    {
        std::string message = "\n\033[91m[ERROR] " + std::to_string(GetLastError()) + "\033[m";
        // throw std::runtime_error(message);
        std::cout << message << "\n";
    }
    
    if (SetClipboardData(CF_TEXT, handle) == NULL)
    {
        std::string message = "\n\033[91m[ERROR] " + std::to_string(GetLastError()) + "\033[m";
        throw std::runtime_error(message);
    }

    CloseClipboard();
}

void disable_echo()
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    
    GetConsoleMode(handle, &mode);
    SetConsoleMode(handle, mode & (~ENABLE_ECHO_INPUT));
}

void enable_echo()
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    
    GetConsoleMode(handle, &mode);
    SetConsoleMode(handle, mode | ENABLE_ECHO_INPUT);
}