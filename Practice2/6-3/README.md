# Лабораторная работа 6.3 — Калькулятор (динамические библиотеки)

Калькулятор загружает математические операции из отдельных `.so` файлов.

## Структура

- `libs/*.c` — исходники библиотек (по одной функции на файл)
- `main.c` — сканирует `libs/`, загружает `.so` через `dlopen`/`dlsym`
- `test.c` — проверяет загрузку `add.so` и `div.so`

## Сборка

```bash
make
```

## Запуск

```bash
./calc
```

## Тесты

```bash
make test
```
##

**Операция возведение в степень**

<img width="421" height="262" alt="image" src="https://github.com/user-attachments/assets/d7b0d66f-1eaf-470d-a94c-1c768ffd6d4b" />

**Операция mod**

<img width="444" height="257" alt="image" src="https://github.com/user-attachments/assets/a3ba5296-056a-43e5-99d5-dffec86d2114" />

**Операция min**

<img width="436" height="258" alt="image" src="https://github.com/user-attachments/assets/3cfb14dc-1242-4495-8921-a94dc25e9c43" />

**Операция max**

<img width="436" height="258" alt="image" src="https://github.com/user-attachments/assets/e9841733-0ebb-4b06-831e-38842c4cefbc" />

**Операция div**

<img width="436" height="258" alt="image" src="https://github.com/user-attachments/assets/88a59fbd-1f3c-4d78-a093-72fff5e29018" />

**Добавление операции**

<img width="482" height="517" alt="image" src="https://github.com/user-attachments/assets/4f3dc4aa-0d66-48fb-8b5c-d6ce9f0e500c" />

## Запуск тестов

<img width="533" height="443" alt="image" src="https://github.com/user-attachments/assets/52aebdaa-5d12-4495-978d-329f521b650b" />

