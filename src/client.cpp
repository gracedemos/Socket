#include <iostream>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int conn(const char* addr, int port, int* sock) {
    struct sockaddr_in serv_addr;
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &serv_addr.sin_addr);
    if(connect(*sock, (const sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        return -1;
    }
    return 0;
}

void messageHandler(int sock) {
    char buffer[1024];
    while(true) {
        read(sock, buffer, 1024);
        std::cout << buffer << std::endl;
    }
}

int main(int argc, const char* argv[]) {
    if(argc != 3) {
        std::cout << "[Incorrect number of arguments]\n";
        return -1;
    }
    int sock = 0, valread;
    if(conn(argv[1], std::stoi(argv[2]), &sock) < 0) {
        std::cout << "[Connection Failed]\n";
        return -1;
    }
    std::cout << "[Connected to " + (std::string)argv[1] + " on port " + (std::string)argv[2] + "]\n";
    const char* msg = "Yessir!";
    send(sock, msg, strlen(msg), 0);
    std::thread msg_handler(messageHandler, sock);
    msg_handler.join();
    return 0;
}