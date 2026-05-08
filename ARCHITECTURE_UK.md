# 🏗️ ARCHITECTURE_UK.md - Архітектура та дизайн

## 📋 Зміст

- [Огляд архітектури](#огляд-архітектури)
- [Системний дизайн](#системний-дизайн)
- [Компоненти](#компоненти)
- [Потоки даних](#потоки-даних)
- [Design Patterns](#design-patterns)
- [Оптимізація](#оптимізація)

---

## 🏗️ Огляд архітектури

### Загальна структура

```
University Learning Project
│
├─ Logger System (ООП)
│  ├─ Абстрактна база Logger
│  ├─ FileLogger реалізація
│  └─ EncryptLogger реалізація
│
├─ Network Attack Simulator (Мережа)
│  ├─ UDP сокети
│  ├─ Потокова система
│  └─ Управління портами
│
└─ Packet Sniffer (Мережеві Утиліти)
   ├─ RAW сокети
   ├─ Парсинг заголовків
   └─ DNS обробка
```

---

## 🎯 Системний дизайн

### 1. Polymorphism Logger System

```
┌─────────────────────────┐
│   Logger (Abstract)      │
│  + log(message)         │
│  + ~Logger()            │
└──────────┬──────────────┘
           │
     ┌─────┴──────┐
     │            │
┌────▼────┐  ┌───▼────┐
│ FileLog │  │EncryptLog│
└─────────┘  └─────────┘
```

#### Як це працює

1. **Базовий клас** - Дефінує інтерфейс
2. **Похідні класи** - Реалізують інтерфейс
3. **Поліморфізм** - Один вызов, різні реалізації
4. **Контейнер** - Vector для управління

#### Переваги цього дизайну

✅ Легко додавати нові типи логерів  
✅ Код залишається незмінним (Open/Closed Principle)  
✅ Динамічний вивір реалізації  
✅ Тестування через мок-об'єкти  

---

### 2. Internet Crash Architecture

```
┌───────────────┐
│   main()      │
├───────────────┤
│ WSAStartup()  │
│ 16 threads───┐
└───────────────┘
     │
     │ fork
     ▼
┌───────────────┐
│  flood()      │
├───────────────┤
│ socket()      │
│ loop while... │
│ - port rand   │
│ - sendto()    │
└───────────────┘
```

#### Компоненти

1. **WinSock2 Ініціалізація**
   - Запуск API
   - Налаштування

2. **Thread Management**
   - 16 паралельних потоків
   - std::atomic для синхронізації
   - Контрольований завершення

3. **UDP Flood**
   - Випадкові порти
   - Великі буфери
   - Безперервна відправка

#### Безпека потоків

```cpp
std::atomic<bool> stop_flag;  // Потокобезпечна змінна
// Всі потоки можуть читати/писати
// Без явного блокування (atomic операції)
```

---

### 3. Network Sniffer Architecture

```
┌──────────────────────┐
│  NetworkMonitor      │
├──────────────────────┤
│  _socket             │
│  _is_running         │
├──────────────────────┤
│  initialize()        │ ◄─ RAW socket
│  run()               │ ◄─ Recv loop
│  process_dns_query() │ ◄─ Parse DNS
└──────────────────────┘
```

#### Послідовність роботи

1. **Ініціалізація**
   ```
   WSAStartup() → socket(SOCK_RAW) → bind() → SIO_RCVALL
   ```

2. **Обробка пакетів**
   ```
   recv() → parse IP → filter UDP → parse DNS → log
   ```

3. **Завершення**
   ```
   closesocket() → WSACleanup()
   ```

---

## 🔧 Компоненти

### Logger Component

#### Клас Logger

```cpp
class Logger {
public:
    virtual void log(string message) {
        // Базова реалізація
    }
    virtual ~Logger() {}  // Важливо!
};
```

**Назва:** Base Logger  
**Відповідальність:** Дефінує інтерфейс  
**Залежності:** iostream  

#### Клас FileLogger

```cpp
class FileLogger : public Logger {
public:
    void log(string message) override {
        // Запис у "файл" (на практиці - консоль)
    }
};
```

**Назва:** File Logger  
**Відповідальність:** Логування у файли  
**Залежності:** Logger базовий клас  

#### Клас EncryptLogger

```cpp
class EncryptLogger : public Logger {
public:
    void log(string message) override {
        // "Шифрування" логу (демонстрація)
    }
};
```

**Назва:** Encrypt Logger  
**Відповідальність:** Логування з шифруванням  
**Залежності:** Logger базовий клас  

---

### Internet Crash Component

#### Основні функції

| Функція | Параметри | Повертає | Назначення |
|---------|-----------|---------|----------|
| `main()` | - | int | Точка входу, управління потоками |
| `flood()` | - | void | UDP flood функція (виконується у потоці) |

#### Глобальні змінні

| Змінна | Тип | Значення | Назначення |
|--------|-----|---------|----------|
| `stop_flag` | atomic<bool> | false | Прапор для зупинки потоків |
| `TARGET_IP` | const char* | "..." | IP адреса цілі |
| `THREAD_COUNT` | const int | 16 | Кількість потоків |

---

### Sniffer Component

#### Клас NetworkMonitor

```cpp
class NetworkMonitor {
private:
    SOCKET _socket;           // Дескриптор сокету
    bool _is_running;         // Флаг роботи
    
    string get_timestamp();   // Отримання часу
    void process_dns_query(); // Обробка DNS
    
public:
    bool initialize(...);     // Ініціалізація
    void run();              // Основний цикл
    ~NetworkMonitor();       // Очистка ресурсів
};
```

**Назва:** Network Monitor  
**Відповідальність:** Перехвачення та обробка пакетів  
**Залежності:** WinSock2  

#### Структури даних

```cpp
struct IPHeader {
    // 20 байт базового IP заголовку
    uint8_t  v_hl;          // 1 байт
    uint8_t  tos;           // 1 байт
    uint16_t total_len;     // 2 байти
    // ... інші поля
};

struct UDPHeader {
    // 8 байт UDP заголовку
    uint16_t src_port;      // 2 байти
    uint16_t dst_port;      // 2 байти
    uint16_t length;        // 2 байти
    uint16_t checksum;      // 2 байти
};
```

---

## 📊 Потоки даних

### Logger Flow

```
User Input
    │
    ▼
main() {
    create: vector<Logger*> loggers
    │
    ├─► new Logger()
    ├─► new FileLogger()
    └─► new EncryptLogger()
}
    │
    ▼
for each Logger {
    loggerPtr->log("Message")
}
    │
    ├─► BaseLogger::log()     → cout
    ├─► FileLogger::log()     → cout
    └─► EncryptLogger::log()  → cout
    │
    ▼
Output to Console
    │
    ├─ "Base log: Text message"
    ├─ "File: Text message"
    └─ "Encrypted log: Text message???..."
```

---

### Internet Crash Flow

```
main() START
    │
    ▼
WSAStartup()
    │
    ▼
for i = 0 to 15 {
    create thread(flood)
}
    │
    ├─► Thread 1: flood()
    ├─► Thread 2: flood()
    ├─► ...
    └─► Thread 16: flood()
    │
    ├─► All threads loop:
    │   - Generate random port
    │   - Create UDP packet
    │   - Send to TARGET_IP
    │
    ▼
Wait for user input (Enter)
    │
    ▼
stop_flag = true
    │
    ▼
All threads exit loop
    │
    ▼
join() all threads
    │
    ▼
WSACleanup()
    │
    ▼
DONE
```

---

### Sniffer Flow

```
main() START
    │
    ▼
NetworkMonitor::initialize(IP)
    │
    ├─► WSAStartup()
    ├─► socket(SOCK_RAW)
    ├─► bind()
    └─► ioctlsocket(SIO_RCVALL)
    │
    ▼
NetworkMonitor::run()
    │
    ├─ LOOP (while _is_running)
    │   │
    │   ├─► recv() packet
    │   │
    │   ├─► parse IP header
    │   │   - Check protocol == 17 (UDP)
    │   │
    │   ├─► parse UDP header
    │   │   - Check dst_port == 53 (DNS)
    │   │
    │   └─► process_dns_query()
    │       - Extract domain name
    │       - Print with timestamp
    │
    ▼
User presses Ctrl+C (SIGINT)
    │
    ▼
Destructor: closesocket(), WSACleanup()
    │
    ▼
DONE
```

---

## 🎨 Design Patterns

### 1. Strategy Pattern (Logger)

```cpp
// Strategy інтерфейс
class Logger {
public:
    virtual void log(...) = 0;
};

// Конкретні стратегії
class FileLogger : public Logger { };
class EncryptLogger : public Logger { };

// Використання
vector<Logger*> strategies;
for (auto s : strategies) {
    s->log(...);  // Поліморфна
}
```

**Переваги:**
- ✅ Легко додавати нові логери
- ✅ Алгоритм відокремлений від деталей
- ✅ Runtime вибір реалізації

---

### 2. Singleton Pattern (WinSock2)

```cpp
// На практиці WinSock2 ініціалізується один раз
WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData);  // Один раз!

// На кінець програми
WSACleanup();  // Один раз!
```

**Переваги:**
- ✅ Один екземпляр ресурсу
- ✅ Глобальний доступ
- ✅ Контрольована ініціалізація

---

### 3. Observer Pattern (Atomic Flag)

```cpp
// Спостерігаємо за флагом
std::atomic<bool> stop_flag;

// Всі потоки спостерігають
while (!stop_flag) {  // Читають флаг
    // Робимо роботу
}

// Main потік повідомлює
stop_flag = true;  // Пишемо флаг
```

**Переваги:**
- ✅ Слабка развязка (loose coupling)
- ✅ Потокобезпечна комунікація
- ✅ Зручне управління життєвим циклом

---

### 4. Template Method Pattern (Sniffer)

```cpp
class NetworkMonitor {
public:
    bool initialize(...) {
        // Шаблон методу
        WSAStartup(...);
        socket(...);
        bind(...);
        ioctlsocket(...);
    }
    
    void run() {
        // Шаблон для обробки
        while (_is_running) {
            recv();
            parseHeaders();  // Делегований метод
            processDNS();    // Делегований метод
        }
    }
};
```

**Переваги:**
- ✅ Контроль послідовності операцій
- ✅ Переопис підкроків у похідних класах
- ✅ Уникнення дублювання коду

---

## ⚡ Оптимізація

### 1. Logger Оптимізація

#### Проблема
```cpp
// ❌ Неефективно - копіювання string для кожного логера
for (Logger* l : loggers) {
    l->log(message);  // message копіюється
}
```

#### Рішення
```cpp
// ✅ Ефективно - передача за посиланням
for (Logger* l : loggers) {
    l->log(const string& message);
}
```

---

### 2. Internet Crash Оптимізація

#### Проблема
```cpp
// ❌ Неефективно - новий socket для кожного пакету
while (!stop_flag) {
    SOCKET sock = socket(...);  // Дорогий виклик
    sendto(...);
    closesocket(sock);
}
```

#### Рішення
```cpp
// ✅ Ефективно - один socket для багатьох пакетів
SOCKET sock = socket(...);
while (!stop_flag) {
    sendto(...);  // Бързак вывік
}
closesocket(sock);
```

---

### 3. Sniffer Оптимізація

#### Проблема
```cpp
// ❌ Неефективно - новий буфер для кожного пакету
while (_is_running) {
    std::vector<uint8_t> buffer(65535);  // Алокація
    recv(buffer);
}
```

#### Рішення
```cpp
// ✅ Ефективно - один буфер для всіх пакетів
std::vector<uint8_t> buffer(65535);  // Одна алокація
while (_is_running) {
    recv(buffer);  // Переиспользование
}
```

---

## 📈 Масштабування

### Logger масштабування

```cpp
// Можна додавати будь-яку кількість логерів
vector<Logger*> loggers;
loggers.push_back(new ConsoleLogger());
loggers.push_back(new FileLogger());
loggers.push_back(new DatabaseLogger());
loggers.push_back(new NetworkLogger());
loggers.push_back(new CloudLogger());

// Код залишається незмінним!
for (auto l : loggers) {
    l->log(message);
}
```

---

### Internet Crash масштабування

```cpp
// Можна змінити кількість потоків
const int THREAD_COUNT = 32;  // Замість 16
const int PACKET_SIZE = 4096;  // Замість 1450
int sndbuf = 8 * 1024 * 1024;  // Замість 4MB
```

---

### Sniffer масштабування

```cpp
// Можна фільтрувати більше портів
vector<int> dns_ports = {53, 5353, 8053};
if (std::find(dns_ports.begin(), dns_ports.end(), 
              ntohs(udph->dst_port)) != dns_ports.end()) {
    process_dns_query(...);
}

// Можна логувати у БД замість консолі
```

---

## 🎯 SOLID Принципи

### S - Single Responsibility Principle ✅

```cpp
class Logger {
    // Відповідає за логування
};

class NetworkMonitor {
    // Відповідає за перехоплення пакетів
};
```

### O - Open/Closed Principle ✅

```cpp
// Открито для розширення
class CustomLogger : public Logger { };

// Закрито для модифікації
class Logger { /* невід'ємна */ };
```

### L - Liskov Substitution Principle ✅

```cpp
Logger* logger = new FileLogger();
// Можна використовувати як Logger
logger->log(...);  // Працює!
```

### I - Interface Segregation Principle ✅

```cpp
// Мінімальний інтерфейс
class Logger {
    virtual void log(string) = 0;
};

// Не перевантажено методами
```

### D - Dependency Inversion Principle ✅

```cpp
// Залежить від абстракції
void useLogger(Logger* logger) {
    logger->log(...);
}

// А не від конкретної реалізації
void useFileLogger(FileLogger* logger) { }
```

---

**Версія:** 1.0  
**Оновлено:** 2026-05-08  
**Автор:** mrdbv

*Архітектура добра, коли її розумієш!* 🎯
