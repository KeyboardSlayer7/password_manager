# Password Manager

A simple terminal user interface password management application that uses C++ with OpenSSL and nlohmann/json.

## Why

Password Manager was created as a side project to help me understand how a password manager works, as well as some other concepts including hashing and encryption.

## Project Status

:white_check_mark: What Works

- Creating log in details
- Adding passwords
- Retrieving passwords
- Copy to clipboard (Windows only)
- Deleting passwords

:construction: In Progress

- Updating a password

:bug: Known Issues

- Problems with colored text in certain terminals

:bulb: Future Plans

- Copy to clipboard in Linux
- Ability to generate strong passwords

## Building

Requirements

- A C++ compiler
- CMake

Clone repo

```
git clone https://github.com/KeyboardSlayer7/password_manager.git
```

Download OpenSSL

Visit either [OpenSSL](https://openssl-library.org/source/) or their [GitHub Repository](https://github.com/openssl/openssl/releases/tag/openssl-3.4.1) and download and extract the library.

CMake

```
cmake -B build -DOPENSSL_ROOT_DIR=<path_to_openssl_directory> -A Win32
```

```
cmake --build build --config Release
```

## How 

The password manager uses a master password based approach to encrypting password. A key is generated from the users master password, using a password based key derivation function, which is used to encrypt passwords for storing and decrypt passwords when retrieving them. The program uses the AES-256 encryption algorithm to handle encryption and decryption, and uses the SHA256 algorithm to store the users master password so that it can be checked every time the user tries to log in.

## Feedback

I've only been working with C/C++ for a few years and am still fairly new to CMake, so I'd love to hear your thoughts! If you find any bugs or have any suggestions, feel free to email me at keyboardslayer7@protonmail.com. Any feedback, big or small, is greatly appreciated!
