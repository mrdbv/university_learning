# 🔨 BUILD_UK.md - Посібник компіляції

## 📋 Зміст

- [Швидка компіляція](#швидка-компіляція)
- [Компіляція на Windows](#компіляція-на-windows)
- [Компіляція на Linux](#компіляція-на-linux)
- [Компіляція на macOS](#компіляція-на-macos)
- [Прапори компіляції](#прапори-компіляції)
- [Makefile приклади](#makefile-приклади)
- [Вирішення проблем](#вирішення-проблем)

---

## ⚡ Швидка компіляція

### Компілюємо все за один раз

#### Windows (PowerShell)
```powershell
# MSVC
cl /std:c++17 polymorphism_logger_demo.cpp /link ws2_32.lib
cl /std:c++17 "internet crash.cpp" /link ws2_32.lib
cl /std:c++17 sniffer.cpp /link ws2_32.lib

# GCC/MinGW
g++ -std=c++17 -o polymorphism polymorphism_logger_demo.cpp
g++ -std=c++17 -o internet_crash "internet crash.cpp" -lws2_32
g++ -std=c++17 -o sniffer sniffer.cpp -lws2_32
```

#### Linux (Bash)
```bash
g++ -std=c++17 -o polymorphism polymorphism_logger_demo.cpp
g++ -std=c++17 -o internet_crash "internet crash.cpp"
g++ -std=c++17 -o sniffer sniffer.cpp
```

#### macOS (Bash)
```bash
clang++ -std=c++17 -o polymorphism polymorphism_logger_demo.cpp
clang++ -std=c++17 -o internet_crash "internet crash.cpp"
clang++ -std=c++17 -o sniffer sniffer.cpp
```

---

## 🪟 Компіляція на Windows

### Метод 1: MSVC (Microsoft Visual C++)

#### Відкриття Developer Command Prompt

1. Натисніть Windows key
2. Введіть "Developer Command Prompt"
3. Виберіть правильну версію (2022, 2019 тощо)

#### Компіляція окремих файлів

```powershell
# Перейти до папки проекту
cd C:\path\to\university_learning

# Компіляція Logger
cl /std:c++17 /W4 polymorphism_logger_demo.cpp

# Компіляція Internet Crash
cl /std:c++17 /W4 "internet crash.cpp" /link ws2_32.lib

# Компіляція Sniffer
cl /std:c++17 /W4 sniffer.cpp /link ws2_32.lib
```

#### Запуск

```powershell
# Logger
polymorphism_logger_demo.exe

# Internet Crash
"internet crash.exe"

# Sniffer (вимагає Administrator)
sniffer.exe
```

#### Прапори MSVC

| Прапор | Значення |
|-------|---------|
| `/std:c++17` | Стандарт C++17 |
| `/O2` | Оптимізація для швидкості |
| `/Wall` | Всі попередження |
| `/W4` | Багато попередження |
| `/D_DEBUG` | Дебаг режим |
| `/link ws2_32.lib` | Зв'язування WinSock2 |

---

### Метод 2: GCC (MinGW-w64)

#### Встановлення MSYS2 (якщо необхідно)

```bash
# Скачайте з https://www.msys2.org/
# Встановіть та запустіть MSYS2 MinGW 64-bit

# Оновіть пакетний менеджер
pacman -Syu

# Встановіть GCC
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb
```

#### Компіляція

```bash
# Перейти до папки проекту
cd /c/path/to/university_learning

# Logger
g++ -std=c++17 -o polymorphism polymorphism_logger_demo.cpp

# Internet Crash
g++ -std=c++17 -o internet_crash "internet crash.cpp" -lws2_32

# Sniffer
g++ -std=c++17 -o sniffer sniffer.cpp -lws2_32
```

#### Запуск

```bash
./polymorphism.exe
./internet_crash.exe  # Потребує admin прав
./sniffer.exe
```

---

### Метод 3: Visual Studio (IDE)

#### Створення проекту

1. Файл → Новий → Проект
2. Виберіть "Консольний додаток C++"
3. Назва проекту: `university_learning`
4. Розташування: ваша папка

#### Додавання файлів

1. Right-click на **Source Files** → Додати → Існуючий елемент
2. Виберіть всі `.cpp` файли

#### Компіляція

```
Меню: Build → Build Solution
Комбінація клавіш: Ctrl+Shift+B
```

#### Запуск

```
Меню: Debug → Start Debugging
Комбінація клавіш: F5
```

---

## 🐧 Компіляція на Linux

### Метод 1: GCC

#### Встановлення (якщо потрібно)

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential

# Fedora
sudo dnf install gcc g++ make

# Arch
sudo pacman -S base-devel
```

#### Компіляція

```bash
# Перейти до проекту
cd ~/university_learning

# Logger (тільки STL)
g++ -std=c++17 -O2 -Wall -o polymorphism polymorphism_logger_demo.cpp

# Internet Crash (потребує WinSock2 - не компілюється на Linux)
# Вимагає Windows API

# Sniffer (потребує RAW sockets)
g++ -std=c++17 -O2 -Wall -o sniffer sniffer.cpp
# Або з виправленнями для Linux
```

#### Запуск

```bash
./polymorphism
sudo ./sniffer  # Потребує привілей root
```

---

### Метод 2: Clang

#### Встановлення

```bash
# Ubuntu/Debian
sudo apt-get install clang

# Fedora
sudo dnf install clang

# Arch
sudo pacman -S clang
```

#### Компіляція

```bash
# Logger
clang++ -std=c++17 -O2 -Wall -o polymorphism polymorphism_logger_demo.cpp

# Sniffer
clang++ -std=c++17 -O2 -Wall -o sniffer sniffer.cpp
```

#### Запуск

```bash
./polymorphism
sudo ./sniffer
```

---

### Метод 3: Makefile (Linux/macOS)

Створіть файл `Makefile`:

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -pedantic
LDFLAGS = -lws2_32

TARGETS = polymorphism sniffer

all: $(TARGETS)

polymorphism: polymorphism_logger_demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

sniffer: sniffer.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) *.o

run: all
	./polymorphism
	sudo ./sniffer

.PHONY: all clean run
```

#### Використання

```bash
# Компіляція всіх
make

# Запуск
make run

# Очистка
make clean
```

---

## 🍎 Компіляція на macOS

### Метод 1: Apple Clang

#### Встановлення (якщо потрібно)

```bash
xcode-select --install
```

#### Компіляція

```bash
cd ~/university_learning

# Logger
clang++ -std=c++17 -O2 -Wall -o polymorphism polymorphism_logger_demo.cpp

# Internet Crash (не компілюється - потребує WinSock2)
# Вимагає Windows API

# Sniffer (потребує адаптацій для macOS)
clang++ -std=c++17 -O2 -Wall -o sniffer sniffer.cpp
```

#### Запуск

```bash
./polymorphism
sudo ./sniffer
```

---

### Метод 2: Homebrew GCC

```bash
# Встановлення
brew install gcc

# Компіляція
/usr/local/bin/g++-11 -std=c++17 -O2 -Wall -o polymorphism polymorphism_logger_demo.cpp
/usr/local/bin/g++-11 -std=c++17 -O2 -Wall -o sniffer sniffer.cpp
```

---

## 🎯 Прапори компіляції

### Оптимізація

| Прапор | Ефект | Використання |
|-------|------|-------------|
| `-O0` | Без оптимізації (за замовчуванням) | Дебаг |
| `-O1` | Базова оптимізація | Балans |
| `-O2` | Сильна оптимізація | Рекомендується |
| `-O3` | Максимальна оптимізація | Для критичного коду |
| `-Os` | Оптимізація розміру | Вбудовані системи |

### Попередження

| Прапор | Описання |
|--------|----------|
| `-Wall` | Базові попередження |
| `-Wextra` | Додаткові попередження |
| `-Wpedantic` | Суворі стандарти C++ |
| `-Werror` | Помилки замість попередження |
| `-Wno-unused` | Ігнорувати невикористані змінні |

### Дебаг

| Прапор | Описання |
|--------|----------|
| `-g` | Додати дебаг інформацію |
| `-ggdb` | Дебаг для GDB |
| `-p` | Профілювання |

### Приклади компіляції

```bash
# Дебаг версія
g++ -std=c++17 -g -Wall -o program program.cpp

# Рельїз версія
g++ -std=c++17 -O2 -Wall -o program program.cpp

# З профілюванням
g++ -std=c++17 -O2 -p -o program program.cpp

# Максимум оптимізації та попередження
g++ -std=c++17 -O3 -Wall -Wextra -pedantic -o program program.cpp
```

---

## 🔧 Makefile приклади

### Простий Makefile

```makefile
# Компілятор та прапори
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Цільові файли
SOURCES = polymorphism_logger_demo.cpp sniffer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = university_learning

# Правила
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
```

### Продвинутий Makefile

```makefile
# Налаштування
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
LDFLAGS = -lws2_32

# Папки
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

# Файли
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/university_learning

# Цілі
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "Build successful: $@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned"

run: $(TARGET)
	@echo "Running..."
	@$(TARGET)

help:
	@echo "Targets:"
	@echo "  make       - Build project"
	@echo "  make run   - Build and run"
	@echo "  make clean - Remove build files"

.PHONY: all clean run help
```

---

## 🆘 Вирішення проблем

### Проблема: "error: file not found"

**Причина:** неправильна назва файлу

```bash
# Перевіряємо назву
ls -la

# Правильна компіляція
g++ -std=c++17 -o program "internet crash.cpp"
```

---

### Проблема: "undefined reference to `socket'"

**Причина:** не пов'язана бібліотека WinSock2

```bash
# Windows - додаємо -lws2_32
g++ -std=c++17 -o program program.cpp -lws2_32

# Linux - не потребується для базового сокету
g++ -std=c++17 -o program program.cpp
```

---

### Проблема: "error: 'RCVALL_ON' is not declared"

**Причина:** RCVALL_ON не існує на Linux, тільки на Windows

**Рішення:** Адаптація коду для Linux:

```cpp
#ifdef _WIN32
    unsigned long mode = RCVALL_ON;
    if (ioctlsocket(_socket, SIO_RCVALL, &mode) == SOCKET_ERROR) return false;
#else
    // Linux версія - інші прапори
#endif
```

---

### Проблема: "Permission denied" при запуску

**Причина:** Файл не виконуваний

```bash
chmod +x program  # Додати прав виконання
./program         # Запустити
```

---

### Проблема: "error: 'stoi' is not a member of 'std'"

**Причина:** Старий стандарт C++

```bash
# Вказуємо -std=c++17 або вище
g++ -std=c++17 program.cpp
```

---

### Проблема: "winsock2.h: No such file"

**Причина:** WinSock2 не встановлено (Linux/macOS)

**Рішення:**
- На Windows - встановіть Visual Studio
- На Linux/macOS - змініть код для POSIX сокетів

---

## 📊 Таблиця компіляторів

| Компілятор | Windows | Linux | macOS | C++17 |
|-----------|---------|-------|-------|-------|
| MSVC 2022 | ✅ | ❌ | ❌ | ✅ |
| GCC 11+ | ✅ | ✅ | ✅ | ✅ |
| Clang 10+ | ✅ | ✅ | ✅ | ✅ |
| Apple Clang | ❌ | ❌ | ✅ | ✅ |

---

## 🎓 Оптимальні налаштування

### Для дебага
```bash
g++ -std=c++17 -g -O0 -Wall -Wextra program.cpp
```

### Для розробки
```bash
g++ -std=c++17 -O2 -Wall -Wextra program.cpp
```

### Для рельїзу
```bash
g++ -std=c++17 -O3 -Wall -Wextra program.cpp
```

---

**Версія:** 1.0  
**Оновлено:** 2026-05-08  
**Автор:** mrdbv

*Готові до компіляції? 🔨*
