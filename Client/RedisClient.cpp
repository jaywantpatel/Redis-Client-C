/*
Establishing a TCP Connection to Redis (RedisClient)
    Uses Berkely sockets to open a TCP connection to the Redis server
    Supports IPv4 and IPv6 resolution using getaddrinfo.

    Implements:
        connectToServer() -> Establishes the connection
        sendCommand() -> Sends a command over the socket
        disconnect() -> Closes the socket when finished
*/

#include "RedisClient.h"

RedisClient::RedisClient(const std::string &host, int port) 
    : host(host), port(port), sockfd(-1) {}

RedisClient::~RedisClient() {
    disconnect();
}

bool RedisClient::connectToServer() {
    struct addrinfo hints, *res= nullptr;
    std::memset(&hints, 0, sizeof(hints)); // Clear the hints structure
    hints.ai_family = AF_UNSPEC; //IPv4 IPv6
    hints.ai_socktype = SOCK_STREAM; //Use TCP

    std::string portStr = std::to_string(port); //Connect port number to string
    int err = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &res); //Resolve address
    if(err != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(err) << "\n"; 
        return false;
    }

    //Iterate through resolved addresses
    for(auto p = res; p!= nullptr; p = p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol); //Create socket
        if(sockfd == -1) continue; //Skip if token creation failed
        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) { //Attempt to connect
            break; //On success
        }
        close(sockfd); //close socket if connection failed
        sockfd = -1; //Reset the socket file descriptor
    } 
    freeaddrinfo(res); //Free address information

    if(sockfd == -1){
        std::cerr << "Could not connect to "<< host << ":" << port << "\n";
        return false;
    }
    return true;
}

void RedisClient::disconnect(){
    if(sockfd != -1){
        close(sockfd);
        sockfd = -1;
    }
}

int RedisClient::getSocketFD() const {
    return sockfd;
}

bool RedisClient::sendCommand(const std::string &command){
    if(sockfd == -1) return false;
    ssize_t sent = send(sockfd, command.c_str(), command.size(), 0);
    return (sent == (ssize_t)command.size());
}