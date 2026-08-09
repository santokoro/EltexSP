# Лабораторная работа 4.3 — Телефонная книга (бинарное дерево + балансировка)

Контакты хранятся в бинарном дереве поиска. Автоматическая балансировка каждые 5 операций.

## Запуск

```
./phonebook
```
## Сборка

```
make

```
## Структура

```
contact.h — заголовочный файл, структура Contact и TreeNode, прототипы функций
contact.c — реализация: дерево, вставка, удаление, поиск, балансировка
main.c — консольное меню
test.c — unit-тесты
Makefile — сборка программы и тестов
```

## Балансировка

```
После каждых 5 операций (добавление/удаление/редактирование) дерево автоматически перестраивается в сбалансированное:
In-order обход → массив (отсортирован)
Построение нового дерева из середины массива (рекурсивно)
```

## Примеры работы программы
**Добавление контакта**

<img width="517" height="419" alt="image" src="https://github.com/user-attachments/assets/638360d8-1d1e-4b78-83aa-70374f1347c0" />

**Редактирование контакта**

<img width="512" height="399" alt="image" src="https://github.com/user-attachments/assets/0470cf34-2247-48e4-bd9f-5257e076cb78" />

**Просмотр контактов**

<img width="485" height="463" alt="image" src="https://github.com/user-attachments/assets/bc1f07f0-7766-434c-9c7d-ae18e916c7a6" />

**Удаление контакта**

<img width="485" height="463" alt="image" src="https://github.com/user-attachments/assets/62828387-1d26-4d05-a9ac-091bf8183a71" />

## Запуск тестов

<img width="395" height="65" alt="image" src="https://github.com/user-attachments/assets/6025d901-4550-40d1-b019-05492dab3002" />



