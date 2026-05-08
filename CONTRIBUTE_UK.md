# 🤝 CONTRIBUTE_UK.md - Посібник для контрибюторів

## 📋 Зміст

- [Як контрибютити](#як-контрибютити)
- [Процес Git / Pull Request](#процес-git--pull-request)
- [Стиль коду](#стиль-коду)
- [Правила комітів](#правила-комітів)
- [Чеклист перед PR](#чеклист-перед-pr)
- [FAQ](#faq)

---

## 🎯 Як контрибютити

### Варіант 1: Звіти про помилки

Якщо знайшли помилку:

1. Перейдіть на [Issues](https://github.com/mrdbv/university_learning/issues)
2. Натисніть **New issue**
3. Виберіть **Bug report**
4. Заповніть:
   - Título: Лаконічний опис помилки
   - Описание: Детальний опис
   - Кроки для відтворення
   - Очікуваний результат
   - Актуальний результат

**Приклад:**
```
Título: Segmentation fault при запуску Sniffer без admin прав

Описание:
Програма падає з помилкою сегментації при запуску без прав адміністратора.

Кроки:
1. Скомпілюй sniffer.cpp
2. Запусти без admin прав
3. Отримай segfault

Очікуване: Помилка, але не crash
Актуальне: Программа падає
```

---

### Варіант 2: Запит на нову функцію

1. Перейдіть на [Issues](https://github.com/mrdbv/university_learning/issues)
2. Натисніть **New issue**
3. Виберіть **Feature request**
4. Заповніть:
   - Вирішена проблема?
   - Запропонований розв'язок
   - Альтернативи

**Приклад:**
```
Вирішена проблема:
Важко розуміти, що робить код в Sniffer

Запропонований розв'язок:
Додати більше коментарів для кожної функції

Альтернативи:
- Відео туторіал
- Слайди з поясненням
```

---

### Варіант 3: Pull Request

Цей процес найбільш бажаний для вносу кодових змін.

---

## 🔄 Процес Git / Pull Request

### Крок 1️⃣: Fork репозиторію

1. Перейдіть на https://github.com/mrdbv/university_learning
2. Натисніть кнопку **Fork** (верхній правий кут)
3. Виберіть розташування (за замовчуванням: ваш аккаунт)

---

### Крок 2️⃣: Клонуйте ваш fork

```bash
# Клонування ВАШОГО fork (не оригіналу!)
git clone https://github.com/YOUR_USERNAME/university_learning.git
cd university_learning

# Додаємо upstream (оригінальний репо)
git remote add upstream https://github.com/mrdbv/university_learning.git

# Перевіряємо
git remote -v
# origin: ваш fork
# upstream: оригінальний
```

---

### Крок 3️⃣: Створіть гілку

```bash
# Оновлюємо main
git fetch upstream
git checkout main
git merge upstream/main

# Створюємо нову гілку для вашої зміни
git checkout -b fix/segfault-sniffer
# або
git checkout -b feature/enhanced-logging
# або
git checkout -b docs/setup-guide
```

**Конвенція назв:**
- `fix/` - Виправлення помилок
- `feature/` - Нові функції
- `docs/` - Документація
- `refactor/` - Переділення коду

---

### Крок 4️⃣: Зробіть зміни

```bash
# Редагуйте файли у вашому редакторі

# Перевіріте статус
git status

# Покажіть що змінилось
git diff

# Додайте файли
git add .
# або конкретні файли
git add sniffer.cpp API_UK.md
```

---

### Крок 5️⃣: Скоммітьте

```bash
git commit -m "fix: Додав перевірку admin прав у Sniffer"

# Або з детальним описом
git commit -m "fix: Додав перевірку admin прав у Sniffer

- Додав функцію isAdmin() для перевірки
- Тепер програма виходить з помилкою замість crash
- Додав цей обробник у main()

Fixes #42"
```

---

### Крок 6️⃣: Синхронізуйте з upstream

```bash
# Оновлюємо з оригіналу
git fetch upstream
git rebase upstream/main

# Якщо конфлікти
# Редагуйте файли
# git add .
# git rebase --continue
```

---

### Крок 7️⃣: Push до вашого fork

```bash
git push origin fix/segfault-sniffer
```

---

### Крок 8️⃣: Створіть Pull Request

1. Перейдіть на https://github.com/YOUR_USERNAME/university_learning
2. Натисніть **Pull requests**
3. Натисніть **New pull request**
4. Виберіть:
   - **Base:** mrdbv/university_learning main
   - **Compare:** your-fork fix/segfault-sniffer

5. Заповніть форму PR:

```markdown
## Описание
Коротке описание змін

## Мотивація
Чому ці зміни необхідні?

## Тип змін
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation
- [x] Code improvement

## Пов'язані Issues
Fixes #42

## Як тестувати
Кроки для перевірки роботи

## Чеклист
- [x] Мій код дотримується стилю проекту
- [x] Я додав коментарі до складних місць
- [x] Документація оновлена
- [x] Немає нових попереджень компілятора
```

---

## 📝 Стиль коду

### Google C++ Style Guide

Дотримуємось [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

### Основні правила

#### 1. Іменування

```cpp
// ✅ Правильно
class DatabaseConnection { };
void processUserInput() { }
const int MAX_BUFFER_SIZE = 1024;
std::vector<int> active_connections;

// ❌ Неправильно
class databaseConnection { };
void ProcessUserInput() { }
int max_buffer_size = 1024;
std::vector<int> activeConnections;
```

#### 2. Форматування

```cpp
// ✅ Правильно
if (condition) {
    doSomething();
} else {
    doOtherThing();
}

// ❌ Неправильно
if (condition)
    doSomething();
else
    doOtherThing();
```

#### 3. Коментарі

```cpp
// ✅ Правильно
// Це однорядковий коментар

/*
 * Це багаторядковий коментар
 * який пояснює складну логіку
 */

// ❌ Неправильно
//це коментар без пробілу
/*це багаторядковий*/
```

#### 4. Врублювання

```cpp
// ✅ Правильно - 4 пробіли
void example() {
    if (x > 0) {
        cout << "positive" << endl;
    }
}

// ❌ Неправильно - 2 пробіли
void example() {
  if (x > 0) {
    cout << "positive" << endl;
  }
}
```

#### 5. Довгі рядки

```cpp
// ✅ Правильно - розбив на кілька рядків
std::cout << "This is a very long line that should be split "
          << "into multiple lines for readability" << std::endl;

// ❌ Неправильно - один дуже довгий рядок
std::cout << "This is a very long line that should be split into multiple lines for readability" << std::endl;
```

#### 6. Константи та макроси

```cpp
// ✅ Правильно
const int MAX_RETRIES = 3;
#define BUFFER_SIZE 256

// ❌ Неправильно
const int max_retries = 3;
#define MaxRetries 3
```

---

## 📌 Правила комітів

Використовуємо **Conventional Commits**

### Формат

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Типи

| Тип | Описание | Приклад |
|-----|---------|---------|
| `feat` | Нова функція | `feat(logger): добавлена підтримка JSON` |
| `fix` | Виправлення помилки | `fix(sniffer): виправлено segfault` |
| `docs` | Документація | `docs(setup): оновлена інструкція` |
| `style` | Форматування, відсутні `;` | `style: видалені невикористані змінні` |
| `refactor` | Переділення без `feat`/`fix` | `refactor(logger): спрощена логіка` |
| `perf` | Поліпшення продуктивності | `perf(sniffer): прискорено парсинг` |
| `test` | Додавання тестів | `test(logger): додани юніт тести` |
| `ci` | Зміни в CI/CD | `ci: додан GitHub Actions` |

### Приклади

#### Простий комміт

```
git commit -m "fix(sniffer): перевірка admin прав перед запуском"
```

#### Детальний комміт

```
git commit -m "feat(logger): додано підтримка рівнів логування

- Додано enum Level { DEBUG, INFO, WARNING, ERROR }
- Оновлено всі логери для використання рівнів
- Додано фільтрування за рівнем

Closes #42"
```

#### Звіти про проблеми

```
git commit -m "fix(internet-crash): виправлено утік пам'яті

Раніше сокети не закривалися при помилці.

Fixes #15"
```

---

## ✅ Чеклист перед PR

Перед тим як подавати Pull Request, перевіріть:

### Код

- [ ] Код компілюється без помилок
- [ ] Немає нових попереджень компілятора
- [ ] Дотримується стилю Google C++ Style Guide
- [ ] Немає дублювання коду
- [ ] Видалені debug виводи

### Тестування

- [ ] Код протестований на всіх платформах (якщо можливо)
- [ ] Нові функції мають тести
- [ ] Виправлення помилок перевіряють помилку

### Документація

- [ ] README_UK.md оновлена (якщо потрібно)
- [ ] API_UK.md оновлена (для нових функцій)
- [ ] Коментарі додані до складних місць
- [ ] Docstrings написані для всіх функцій

### Git

- [ ] Гілка актуальна з upstream/main
- [ ] Комміти мають розумні повідомлення
- [ ] Немає зайвих файлів (`.o`, `.exe`, тощо)
- [ ] Немає конфліктів злиття

### PR

- [ ] Назва PR зрозуміла і повна
- [ ] Описание PR детальне
- [ ] Пов'язані Issues посилаються
- [ ] Не містить невідповідного контенту

---

## ❓ FAQ

### Як я можу почати контрибютити?

Виконайте ці кроки:
1. Fork репозиторію
2. Прочитайте [SETUP_UK.md](SETUP_UK.md)
3. Робіть зміни
4. Створіть Pull Request

---

### Що якщо мої зміни відхилені?

Це нормально! Відзначте:
- Чому вони були відхилені
- Що потрібно змінити
- Спробуйте ще раз

---

### Як оновити мій fork?

```bash
git fetch upstream
git checkout main
git merge upstream/main
git push origin main
```

---

### Як синхронізувати гілку з main?

```bash
git fetch upstream
git rebase upstream/main

# Якщо конфлікти
# Редагуйте файли
# git add .
# git rebase --continue
# git push origin your-branch -f
```

---

### Можна я користувати какою-небудь бібліотекою?

Будь ласка, ЗАПИТАЙТЕ СПОЧАТКУ через Issue!

Критерії:
- ✅ Должна бути необхідною
- ✅ Повинна мати ліцензію
- ✅ Не повинна обтяжувати проект
- ❌ Спеціальні залежності (якщо не абсолютно необхідно)

---

### Я отримав "409 Conflict"?

```bash
# Обновіть з upstream
git fetch upstream
git rebase upstream/main

# Розв'яжіть конфлікти
# Редагуйте файли

git add .
git rebase --continue
git push -f origin your-branch
```

---

### Де я можу отримати допомогу?

1. 📖 Дивіться [API_UK.md](API_UK.md)
2. 💬 Задайте питання в [Discussions](https://github.com/mrdbv/university_learning/discussions)
3. 🐛 Перевіріть [Issues](https://github.com/mrdbv/university_learning/issues)

---

## 🎓 Ресурси

- [Git Docs](https://git-scm.com/doc)
- [GitHub Guides](https://guides.github.com/)
- [Conventional Commits](https://www.conventionalcommits.org/)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

---

## 🏆 Дякуємо за контрибют!

Кожен внесок робить проект кращим. 🎉

**Версія:** 1.0  
**Оновлено:** 2026-05-08  
**Автор:** mrdbv

*Контрибютуйте з задоволенням! ❤️*
