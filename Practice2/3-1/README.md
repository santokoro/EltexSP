# Лабораторная работа 3.1 — Маска прав доступа к файлу

Программа для расчета и отображения прав доступа к файлам в трех форматах: буквенном, цифровом и битовом.

## Что умеет

1. **Ввод прав вручную** — принимает строку вида `rwxr-xr-x` или число `755`, показывает все три представления.
2. **Чтение прав файла** — через `stat` получает права реального файла, выводит их и запускает `ls -l` для сравнения.
3. **Изменение прав (без записи в файл)** — команды в духе `chmod`: `u+x`, `go-w`, `o=r`, `a-x` и т.д. Результат отображается, файл не трогается.

## Файлы

- `perms.h` — заголовочный файл
- `perms.c` — функции для работы с правами
- `main.c` — главный файл с меню

## Сборка

```bash
gcc -o perms perms.c main.c
```



## Примеры
1. <img width="610" height="187" alt="image" src="https://github.com/user-attachments/assets/42c905b0-fb6a-41c0-b41e-f35fa0f1c9a2" />

2. <img width="589" height="150" alt="image" src="https://github.com/user-attachments/assets/225a5cdc-cc7f-455f-8542-5f8e111376b1" />

3. <img width="592" height="246" alt="image" src="https://github.com/user-attachments/assets/ac4af0ff-8408-405d-a657-ee3b53901c63" />



## Tests
<img width="511" height="106" alt="image" src="https://github.com/user-attachments/assets/58e17f4c-57bb-4037-bc41-b2d7d92e1100" />

```
