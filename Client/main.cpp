/*
1. Command-Line argument parsing
    -h <host> default: 127.0.0.1 -p <port> default: 6379
    If no args, launch interactive REPL mode

2. Object-Oriented Programming
    RedisClient, CommandHandler, ResponseParser, CLI

3. Establish TCP Connection to Redis (RedisClient)
    Berkeley sockets to open TCP connection
    IPv4 and IPv6 `getaddrinfo`

4. Parsing and Command Formatting (CommandHandler)
    Split user input 
    Convert commands into RESP format:
    ```
    *3\r\n
    $3\r\nSET\r\n
    $3\r\nkey\r\n
    $5\r\nvalue\r\n
    ```
5. Handle Redis Responses (ResponseParser)
    Read server responses and parses RESP types
    +OK, -Error, :100, $5\r\nhello -> Bulk string, *2\r\n$3\r\nfoo\r\n$3\r\nbar -> Array response

6. Implement Interactive REPL (CLI)
    Run loop: User Input, valid redis commands, send commands to server, display parsed response
    Support: help, quit

7. main.cpp: parse command-line arguments, instantiate cli and launch in REPL mode.

Socket Programming
Protocol Handeling
OOP principles 
CLI development

*/

#include "CLI.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string host = "127.0.0.1";
    int port = 6379;
    int i = 1;
    std::vector<std::string> commandArgs;

    //Parse command-line args for -h and -p
    while(i < argc){
        std::string arg = argv[i];
        if (arg == "-h" && i+1 < argc){ // -h 127.0.0.1
            host = argv[++i];
        } else if (arg == "-p" && i+1 < argc){
            port = std::stoi(argv[++i]);
        } else {
            // Remaining arguments
            while (i < argc)
            {
                commandArgs.push_back(argv[i]);
                i++;
            }
            break;
        }
        ++i;
    }

    //Handle REPL and one-shot command modes
    CLI cli(host, port);
    cli.run(commandArgs); //launch REPL mode
    

    return 0;
}
