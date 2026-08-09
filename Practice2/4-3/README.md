# Лабораторная работа 4.1 — Телефонная книга (двухсвязный список)

Доработка задачи 2.1. Контакты хранятся в двухсвязном упорядоченном списке. Автоматическая сортировка по фамилии (при совпадении — по имени).

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

## Особенности

- `AddContact` — вставляет контакт в список в правильном месте
- `EditContact` — после изменения фамилии переставляет контакт в нужное место
- `DeleteContact` — удаляет по индексу, пересвязывает prev/next
- `FindContact` — поиск по фамилии, возвращает индекс

- ## Primer

- <img width="517" height="419" alt="image" src="https://github.com/user-attachments/assets/638360d8-1d1e-4b78-83aa-70374f1347c0" />

<img width="512" height="399" alt="image" src="https://github.com/user-attachments/assets/0470cf34-2247-48e4-bd9f-5257e076cb78" />

<img width="485" height="463" alt="image" src="https://github.com/user-attachments/assets/bc1f07f0-7766-434c-9c7d-ae18e916c7a6" />

<img width="485" height="463" alt="image" src="https://github.com/user-attachments/assets/62828387-1d26-4d05-a9ac-091bf8183a71" />

## Zapusk testov



