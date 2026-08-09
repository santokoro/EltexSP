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
<img width="529" height="100" alt="image" src="https://github.com/user-attachments/assets/f17efe2b-1322-46e1-aef4-8928c126920b" />


<img width="518" height="391" alt="image" src="https://github.com/user-attachments/assets/a41b6aba-3569-4885-9cf0-c9950dd6c3a3" />

<img width="513" height="412" alt="image" src="https://github.com/user-attachments/assets/b37c9c27-a8e9-48ac-8f78-3a3b33c8e66b" />

<img width="463" height="456" alt="image" src="https://github.com/user-attachments/assets/31391bbd-f0c0-403a-9486-075626ceb3a4" />

<img width="463" height="395" alt="image" src="https://github.com/user-attachments/assets/61c386f3-a517-4ea3-a291-74eb55991cee" />


## Особенности

- `AddContact` — вставляет контакт в список в правильном месте
- `EditContact` — после изменения фамилии переставляет контакт в нужное место
- `DeleteContact` — удаляет по индексу, пересвязывает prev/next
- `FindContact` — поиск по фамилии, возвращает индекс
