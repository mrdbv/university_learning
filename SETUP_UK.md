# ⚙️ SETUP_UK.md - Посібник налаштування та встановлення

## 📋 Зміст

- [Швидкий старт](#швидкий-старт)
- [Системні вимоги](#системні-вимоги)
- [Встановлення Git](#встановлення-git)
- [Встановлення компілятора](#встановлення-компілятора)
- [Клонування репозиторію](#клонування-репозиторію)
- [IDE налаштування](#ide-налаштування)
- [Перевірка встановлення](#перевірка-встановлення)

---

## ⚡ Швидкий старт

Якщо у вас уже встановлено Git, мінімум 5 хвилин:

### Windows

```powershell
# 1. Відкрийте PowerShell у папці для проекту

# 2. Клонуємо
git clone https://github.com/mrdbv/university_learning.git
cd university_learning

# 3. Компілюємо (якщо MSVC встановлено)
cl /std:c++17 polymorphism_logger_demo.cpp /link ws2_32.lib

# 4. Запускаємо
polymorphism_logger_demo.exe
```

### Linux/macOS

```bash
# 1. Відкрийте Terminal

# 2. Клонуємо
git clone https://github.com/mrdbv/university_learning.git
cd university_learning

# 3. Компілюємо
g++ -std=c++17 -o polymorphism_logger_demo polymorphism_logger_demo.cpp

# 4. Запускаємо
./polymorphism_logger_demo
```

---

## ⚙️ Системні вимоги

### Мінімальні вимоги

| Компонент | Вимога | Причина |
|-----------|--------|---------|
| **OS** | Windows 7+ / Linux / macOS | Для WinSock2 API |
| **RAM** | 512 МБ | Для компіляції |
| **Місце на диску** | 500 МБ | Для компілятора та проекту |
| **Компілятор** | MSVC / GCC / Clang | Для компіляції C++ |

### Рекомендовані вимоги

| Компонент | Рекомендація |
|-----------|-------------|
| **OS** | Windows 10+ / Ubuntu 20.04+ / macOS 10.15+ |
| **RAM** | 2+ ГБ |
| **Місце на диску** | 2+ ГБ |
| **IDE** | Visual Studio 2019+ / VS Code / Qt Creator |

---

## 🔧 Встановлення Git

### Windows

#### Метод 1: Встановлювач

1. Перейдіть на https://git-scm.com/download/win
2. Завантажте **Git for Windows**
3. Запустіть інсталер
4. Виберіть опції:
   - ✅ Git Bash Here
   - ✅ Git GUI Here
   - ✅ Add to PATH

#### Метод 2: Через Chocolatey

```powershell
# У PowerShell (з адміністратором)
choco install git
```

#### Метод 3: Через Microsoft Store

```powershell
# У PowerShell
winget install Git.Git
```

### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install git
git --version  # Перевірка
```

### Linux (Fedora/RHEL)

```bash
sudo dnf install git
git --version  # Перевірка
```

### macOS

```bash
# Через Homebrew
brew install git

# Або через Xcode Command Line Tools
xcode-select --install

git --version  # Перевірка
```

### Перевірка встановлення

```bash
git --version
# Очікуваний вивід: git version 2.x.x
```

---

## 🛠️ Встановлення компілятора

### Windows - MSVC (Microsoft Visual C++)

#### Метод 1: Visual Studio Community

1. Перейдіть на https://visualstudio.microsoft.com/
2. Завантажте **Visual Studio Community**
3. Запустіть інсталер
4. При встановленні виберіть:
   - ✅ Desktop development with C++
   - ✅ Windows 10 SDK
   - ✅ CMake tools for Windows

5. Після встановлення, відкрийте **Developer Command Prompt for VS 2022**

#### Метод 2: Build Tools для Visual Studio

1. Перейдіть на https://visualstudio.microsoft.com/downloads/
2. Знайдіть **Build Tools for Visual Studio 2022**
3. Завантажте та встановіть
4. Виберіть опцію **C++ development tools**

#### Перевірка

```powershell
cl /?  # MSVC компілятор
```

---

### Windows - GCC (MinGW)

#### Метод 1: Через MSYS2

1. Перейдіть на https://www.msys2.org/
2. Завантажте **MSYS2 Installer**
3. Встановіть та запустіть **MSYS2 MinGW 64-bit**

4. Встановіть GCC:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb
```

#### Метод 2: MinGW-w64 (прямо)

1. Перейдіть на https://www.mingw-w64.org/
2. Завантажте встановлювач
3. Виберіть опції:
   - Version: latest
   - Architecture: x86_64
   - Threads: win32 або posix

#### Перевірка

```bash
gcc --version
g++ --version
```

---

### Linux - GCC

#### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install build-essential

# Перевірка
g++ --version
gcc --version
```

#### Fedora/RHEL

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install gcc-c++

# Перевірка
g++ --version
```

#### Arch Linux

```bash
sudo pacman -S base-devel

# Перевірка
g++ --version
```

---

### Linux - Clang (альтернатива GCC)

#### Ubuntu/Debian

```bash
sudo apt-get install clang

# Перевірка
clang++ --version
```

#### Fedora/RHEL

```bash
sudo dnf install clang

# Перевірка
clang++ --version
```

---

### macOS - Apple Clang

#### Через Xcode Command Line Tools

```bash
xcode-select --install

# Перевірка
clang++ --version
```

#### Через Homebrew

```bash
brew install llvm

# Перевірка
/usr/local/opt/llvm/bin/clang++ --version
```

---

## 📥 Клонування репозиторію

### Основна команда

```bash
git clone https://github.com/mrdbv/university_learning.git
cd university_learning
```

### Клонування з SSH (якщо налаштовано)

```bash
git clone git@github.com:mrdbv/university_learning.git
cd university_learning
```

### Клонування специфічної гілки

```bash
git clone --branch main https://github.com/mrdbv/university_learning.git
cd university_learning
```

### Перевірка клонування

```bash
# Повинна бути папка з файлами
ls -la

# Або на Windows PowerShell
dir

# Очікуваний вивід:
# polymorphism_logger_demo.cpp
# internet crash.cpp
# sniffer.cpp
# README.md
```

---

## 🎨 IDE налаштування

### Visual Studio Code

#### 1. Встановлення розширень

Натисніть Ctrl+Shift+X та встановіть:
- **C/C++** (Microsoft)
- **CMake Tools** (Microsoft)
- **CMake** (twxs)

#### 2. Налаштування компілятора

Натисніть Ctrl+Shift+P → "C/C++: Edit Configurations"

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": ["${workspaceFolder}/**"],
            "defines": ["_DEBUG", "_WINDOWS"],
            "windowsSdkVersion": "10.0.22621.0",
            "compilerPath": "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.38.33130/bin/Hostx64/x64/cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-msvc-x64"
        }
    ],
    "version": 4
}
```

#### 3. Запуск кода

Натисніть Ctrl+F5 для компіляції та запуску.

---

### Visual Studio

#### 1. Створення проекту

- File → New → Project
- Виберіть **Empty C++ Project**
- Name: `university_learning`
- Location: вибір папки

#### 2. Додавання файлів

1. Right-click на **Source Files** → Add → Existing Item
2. Виберіть `polymorphism_logger_demo.cpp`

#### 3. Компіляція та запуск

- Натисніть F5 для Debug
- Або Ctrl+F5 для Release

---

### Qt Creator

#### 1. Створення проекту

- File → New Project
- Виберіть **Plain C++ Application**
- Name: `university_learning`

#### 2. Додавання файлів

1. Right-click на проект
2. Add Existing Files
3. Виберіть `polymorphism_logger_demo.cpp`

#### 3. Налаштування .pro файлу

```pro
QT -= gui
CONFIG += c++17 console
TARGET = university_learning
SOURCES += polymorphism_logger_demo.cpp
```

#### 4. Запуск

- Натисніть Ctrl+R

---

### Code::Blocks

#### 1. Створення проекту

- File → New → Project
- Виберіть **Empty Project**
- Name: `university_learning`

#### 2. Додавання файлів

1. Right-click на Project
2. Add files
3. Виберіть `polymorphism_logger_demo.cpp`

#### 3. Налаштування компілятора

- Project → Build Options
- Compiler settings
- Add option: `-std=c++17`

#### 4. Запуск

- Натисніть Ctrl+F10

---

## ✅ Перевірка встановлення

### Чеклист

- [ ] Git встановлено
  ```bash
  git --version
  ```

- [ ] Компілятор встановлено
  ```bash
  # MSVC
  cl /?
  
  # GCC
  g++ --version
  
  # Clang
  clang++ --version
  ```

- [ ] Репозиторій клонований
  ```bash
  cd university_learning
  ls -la
  ```

- [ ] IDE відкрита та налаштована

### Запуск тесту

```bash
# Компіляція
g++ -std=c++17 -o test polymorphism_logger_demo.cpp

# Запуск
./test
# Або на Windows
test.exe
```

**Очікуваний вивід:**
```
Base log : Text message
File : Text message
Encrypted log :  Text message? ? ? ? ? ? ? ?
```

---

## 🆘 Вирішення проблем

### Проблема: "git: command not found"

**Рішення:**
```bash
# Windows: перезапустіть PowerShell після встановлення
# Linux/macOS: перевстановіть Git
```

### Проблема: "cl: command not found"

**Рішення:**
```powershell
# Запустіть Developer Command Prompt for VS 2022
# Замість звичайного PowerShell/CMD
```

### Проблема: "Cannot open include file: winsock2.h"

**Рішення:**
```bash
# На Linux/macOS встановіть mingw-w64
sudo apt-get install mingw-w64  # Ubuntu
brew install mingw-w64          # macOS
```

### Проблема: "undefined reference to `socket'"

**Рішення:**
```bash
# Додайте бібліотеку при компіляції
g++ -std=c++17 -o program program.cpp -lws2_32  # Windows
g++ -std=c++17 -o program program.cpp           # Linux (вже вбудовано)
```

---

## 📊 Версії компіляторів

| Компілятор | Версія | Windows | Linux | macOS |
|-----------|--------|---------|-------|-------|
| MSVC | 2019+ | ✅ | ❌ | ❌ |
| GCC | 7+ | ✅ | ✅ | ❌ |
| Clang | 5+ | ✅ | ✅ | ✅ |

---

## 📚 Подальші кроки

1. Читайте [README_UK.md](README_UK.md) для огляду проектів
2. Дивіться [BUILD_UK.md](BUILD_UK.md) для детальної компіляції
3. Вивчайте [API_UK.md](API_UK.md) для документації API

---

**Версія:** 1.0  
**Оновлено:** 2026-05-08  
**Автор:** mrdbv

*Готові почати? Запустіть ваш перший проект! 🚀*
