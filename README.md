# Redis-CLI (Custom C++ Redis Client)

A lightweight, fully custom Redis command-line client built from scratch in modern C++.  
This project implements raw socket communication, full RESP2 serialization, command formatting, response parsing, and an interactive REPL — without using hiredis or any external Redis libraries.

---

## 🚀 Features

### ✔ Full TCP Redis Client (No External Libraries)
- Connects to Redis using Berkeley sockets  
- Supports IPv4 / IPv6 via `getaddrinfo`  
- Clean, modular networking layer with error handling

### ✔ Full RESP2 Protocol Support
Implements parsing for all major Redis response types:

- `+` Simple Strings  
- `-` Simple Errors  
- `:` Integers  
- `$` Bulk Strings  
- `*` Arrays  

### ✔ Command Formatting
Automatically converts user input into RESP:

*3\r\n
$3\r\nSET\r\n
$3\r\nkey\r\n
$5\r\nvalue\r\n

### ✔ Interactive REPL
- Type Redis commands as if using the official Redis CLI  
- Commands: `help`, `quit`  
- Clean and simple prompt interface

### ✔ One-Shot Command Mode
Run commands directly from the command line:

./redis-cli -h 127.0.0.1 -p 6379 GET mykey

---

## 📁 Project Structure
src/
│── main.cpp
│── CLI.h / CLI.cpp
│── RedisClient.h / RedisClient.cpp
│── CommandHandler.h / CommandHandler.cpp
│── ResponseParser.h / ResponseParser.cpp


---

## 🔧 Build Instructions

### Requirements
- C++17 or later  
- Linux/macOS (Windows needs Winsock modifications)  
- Running Redis server  

### Build with g++
```bash
make
make clean
```
---

📚 Technical Highlights
Networking

Raw TCP sockets

Blocking send/recv

Graceful error handling

IPv4/IPv6 support

Protocol Handling

Full RESP2 parser

Handles bulk strings, arrays, integers, errors, etc.

Strict length-based parsing for bulk and array types

OOP Architecture

Clear class separation

Easy to extend

Highly modular for future features

🧪 Future Improvements

Non-blocking / async I/O

Command history + autocomplete

RESP3 support

Unit tests for parser + networking

Config file for startup defaults

