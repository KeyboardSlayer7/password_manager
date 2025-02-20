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

CMake

```
cmake -B build
```

```
cmake --build build
```

## How 


