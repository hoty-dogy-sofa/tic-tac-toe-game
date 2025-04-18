# Лабораторная работа: Крестики-нолики 10×10

## Содержание
- [Описание](#описание)
- [Структура проекта](#структура-проекта)
- [Запуск](#запуск)
- [Управление игрой](#управление-игрой)
- [Правила игры](#правила-игры)

## Описание
Консольная реализация игры "Крестики-нолики" на поле 10×10 с поддержкой:
- Динамической загрузки различных режимов отображения
- Двух встроенных стилей интерфейса
- Механизма переключения представлений во время игры

## Структура проекта
```bash
tic-tac-toe-game/
├── include/
│ ├── game.hpp # Интерфейс игровой логики
│ └── view.hpp # Абстрактный класс представления
├── src/
│ ├── game.cpp # Реализация правил игры
│ ├── view_compact.cpp # Компактный режим
│ └── view_pretty.cpp # Графический режим
└── README.md
```

## Запуск

# Компактный режим
./tic-tac-toe view-compact

# Графический режим
./tic-tac-toe view-pretty

## 🎮 Управление игрой

### Общие команды

| Команда       | Действие                      |
|---------------|-------------------------------|
| `view-[name]` | Переключить режим отображения |
| `Ctrl+D`      | Выход из игры                 |

### Формат ходов

#### Компактный режим
```plaintext
5 5   # Строка (0-9) и столбец (0-9)
-1 -1 # Команда выхода из игры
```

#### Графический режим
```plaintext
b4    # Буква столбца (a-j) + цифра строки (0-9)
```
## Правила игры

- Игроки ходят по очереди (начинают нолики)
- Для победы нужно построить линию из 5 своих символов

- Возможны три исхода:
    - Победа крестиков
    - Победа ноликов
    - Ничья
