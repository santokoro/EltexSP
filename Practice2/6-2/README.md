# Лабораторная работа 6.2 — Телефонная книга (динамическая библиотека)

Доработка задачи 6.1. Функции работы с двухсвязным упорядоченным списком вынесены в динамическую библиотеку `libcontact.so`.

## Сборка

```bash
make
```

## Запуск

```bash
./phonebook
```

## Тесты

```bash
make test
```

## Структура

- `contact.h` — заголовочный файл (API библиотеки)
- `contact.c` — реализация функций списка
- `libcontact.so` — динамическая библиотека
- `main.c` — главная программа, линкуется с `-lcontact`
- `test.c` — unit-тесты
- `Makefile` — сборка библиотеки, программы и тестов

##

<img width="511" height="409" alt="image" src="https://github.com/user-attachments/assets/48939194-31bd-44ba-8508-1ea487cb9116" />

<img width="489" height="585" alt="image" src="https://github.com/user-attachments/assets/1ac78284-a462-4b2a-bbc3-853e68244914" />

<img width="489" height="585" alt="image" src="https://github.com/user-attachments/assets/544e9d87-b2ff-4ed2-9a16-e7dfbd696269" />

<img width="500" height="513" alt="image" src="https://github.com/user-attachments/assets/4fde2132-d2af-4463-8a27-5eb0451f5777" />


<img width="452" height="76" alt="image" src="https://github.com/user-attachments/assets/0c94eb65-89c6-429d-b543-4808fd182ad4" />
