#include <stdio.h>
#include <locale.h>
#include "priority_queue.h"

int main() {
    setlocale(LC_ALL, "Russian");

    PriorityQueue pq;
    InitPriorityQueue(&pq);

    printf("=== Тестирование очереди с приоритетами ===\n\n");

    printf("1. Добавляем элементы:\n");
    AddQueue(&pq, 100, 5);
    printf("   Добавлено: data=100, priority=5\n");
    AddQueue(&pq, 200, 3);
    printf("   Добавлено: data=200, priority=3\n");
    AddQueue(&pq, 300, 7);
    printf("   Добавлено: data=300, priority=7\n");
    AddQueue(&pq, 400, 5);
    printf("   Добавлено: data=400, priority=5\n");
    AddQueue(&pq, 500, 1);
    printf("   Добавлено: data=500, priority=1\n");
    AddQueue(&pq, 600, 7);
    printf("   Добавлено: data=600, priority=7\n");
    AddQueue(&pq, 700, 3);
    printf("   Добавлено: data=700, priority=3\n");

    printf("\n2. Извлечение с максимальным приоритетом (DequeueMax):\n");
    int val = DequeueMax(&pq);
    printf("   Извлечено: %d\n", val);
    val = DequeueMax(&pq);
    printf("   Извлечено: %d\n", val);

    printf("\n3. Извлечение по указанному приоритету (DequeueByPriority):\n");
    val = DequeueByPriority(&pq, 5);
    printf("   Извлечено с priority=5: %d\n", val);
    val = DequeueByPriority(&pq, 3);
    printf("   Извлечено с priority=3: %d\n", val);

    printf("\n4. Извлечение с приоритетом не ниже заданного (DequeueWithMinPriority):\n");
    val = DequeueWithMinPriority(&pq, 4);
    printf("   Извлечено с priority>=4: %d\n", val);
    val = DequeueWithMinPriority(&pq, 2);
    printf("   Извлечено с priority>=2: %d\n", val);

    printf("\n5. Попытка извлечения из пустой очереди:\n");
    val = DequeueMax(&pq);
    printf("   Результат: %d\n", val);

    printf("\n=== Тест завершен ===\n");

    return 0;
}