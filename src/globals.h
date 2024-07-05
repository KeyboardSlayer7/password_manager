#pragma once

#include <string>

typedef unsigned char byte;
typedef std::basic_string<byte> byte_string;

int ctoi(char c);
std::string input(const char* message);
std::string to_hex(const unsigned char* ciphertext, size_t length);
size_t un_hex(std::string hex_string, unsigned char* plaintext, size_t length);

void print_array(unsigned char* array, size_t length);
void copy(const byte_string& text);

void disable_echo();
void enable_echo();