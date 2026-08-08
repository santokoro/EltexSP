# Лабораторная работа 3.2 — Имитация отправки пакетов IPv4

Программа генерирует N случайных IP-адресов назначения и определяет, принадлежат ли они подсети шлюза.

## Запуск

```bash
./network_sim <gateway_ip> <mask> <N>
```

- `gateway_ip` — IP шлюза, например `192.168.1.1`
- `mask` — маска подсети (`255.255.255.0` или `/24`)
- `N` — количество пакетов

## Пример

```bash
./network_sim 192.168.1.1 /24 10
```

## Сборка

```bash
make
```

## Тесты

```bash
make test
```

## Файлы

- `network.h` — заголовочный файл
- `network.c` — функции работы с IP
- `main.c` — главная программа
- `test.c` — unit-тесты
- `Makefile` — сборка

## Примеры

**Все local**

  <img width="544" height="384" alt="image" src="https://github.com/user-attachments/assets/cee9c61c-453b-4f2d-b4e7-27e38d703ed3" />
  
**Все remote**

  <img width="537" height="303" alt="image" src="https://github.com/user-attachments/assets/9347e2cf-57ab-49dd-b983-acfc60a3af2e" />
  
**Произвольный ввод**

  <img width="537" height="303" alt="image" src="https://github.com/user-attachments/assets/3aae0de8-1d5b-4adc-a3c2-8d664dcb06cf" />
  
**Запуск тестов**

<img width="543" height="133" alt="image" src="https://github.com/user-attachments/assets/8f953586-2ef3-4cec-8038-9926f9d81005" />


