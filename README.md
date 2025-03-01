# Password Manager

A simple terminal user interface password management application that uses C++ with OpenSSL and nlohmann/json.

> [!Note]
> Colored text may not work in some terminals.

## Why

Password Manager was created as a side project to help me understand how a password manager works, as well as some other concepts including hashing and encryption.

## Project Status

:white_check_mark: What Works

- Creating log in details
- Adding passwords
- Retrieving passwords + Copy to clipboard (Windows only)
- Deleting passwords

:construction: In Progress

- Copy to clipboard (linux)

:bug: Known Issues

- Problems with colored text in certain terminals

:bulb: Future Plans

- 

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

## Feedback
I've only been working with C/C++ for a few years and am still fairly new to CMake, so I'd love to hear your thoughts! If you find any bugs or have any suggestions, feel free to email me at keyboardslayer7@protonmail.com. Any feedback, big or small, is greatly appreciated!
