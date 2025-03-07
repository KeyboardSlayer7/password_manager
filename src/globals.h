#pragma once

#include <string>

typedef unsigned char byte;
typedef std::basic_string<byte> byte_string;

int ctoi(char c);
std::string input(const char* message);
std::string to_hex(const unsigned char* ciphertext, size_t length);
size_t un_hex(std::string hex_string, unsigned char* plaintext, size_t length);

// I have no idea why this function exists
void print_array(unsigned char* array, size_t length);

// Copy text to clipboard
void copy(const byte_string& text);

void disable_echo();
void enable_echo();