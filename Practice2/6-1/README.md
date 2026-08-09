# Лабораторная работа 6.1 — Телефонная книга (статическая библиотека)

Доработка задачи 4.1. Функции работы с двухсвязным упорядоченным списком вынесены в статическую библиотеку `libcontact.a`.

## Сборка

```
make
```
## Запуск
```
./phonebook
```
## Запуск тестов

```
make test
```

## Структура проекта

```
contact.h — заголовочный файл (API библиотеки)
contact.c — реализация функций списка
libcontact.a — статическая библиотека (собирается из contact.o)
main.c — главная программа, линкуется с -lcontact
test.c — unit-тесты, линкуются с библиотекой
Makefile — сборка библиотеки, программы и тестов
```
## Как работает библиотека

```
make компилирует contact.c в contact.o
ar rcs libcontact.a contact.o создаёт статическую библиотеку
main.c и test.c линкуются с libcontact.a через -L. -lcontact
```

## Примеры запуска программы

**Добавление контакта**

<img width="485" height="463" alt="image" src="https://github.com/user-attachments/assets/0a252906-92e6-4e9d-a9e8-ef2962902224" />

**Редактирование контакта**

<img width="521" height="665" alt="image" src="https://github.com/user-attachments/assets/bec7de8b-e6d2-425c-bb47-0e50431a7b12" />

**Просмотр контактов**

<img width="510" height="467" alt="image" src="https://github.com/user-attachments/assets/7eba0d85-fa20-4917-aaee-559e4125142c" />

**Удаление контакта**

<img width="501" height="444" alt="image" src="https://github.com/user-attachments/assets/bb37445e-adfd-46f4-bd03-28af74b9f730" />

**Запуск тестов**

<img width="451" height="60" alt="image" src="https://github.com/user-attachments/assets/e1e9c200-8823-43cb-8a8f-dddc4ce8080d" />


