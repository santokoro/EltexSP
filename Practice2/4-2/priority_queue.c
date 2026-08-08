#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

void InitPriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < 256; i++) {
        pq->queues[i].head = NULL;
        pq->queues[i].tail = NULL;
    }
    pq->max_priority = -1;
}

void AddQueue(PriorityQueue* pq, int value, int priority) {
    if (priority < 0 || priority > 255) {
        printf("Ошибка приоритета!\n");
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }
    new_node->data = value;
    new_node->next = NULL;

    Queue* q = &pq->queues[priority];

    if (q->head == NULL) {
        q->head = new_node;
        q->tail = new_node;
    }
    else {
        q->tail->next = new_node;
        q->tail = new_node;
    }

    if (priority > pq->max_priority) {
        pq->max_priority = priority;
    }
}

int DequeueMax(PriorityQueue* pq) {
    if (pq->max_priority == -1) {
        printf("Извлечение невозможно, очередь пуста!\n");
        return -1;
    }

    int m = pq->max_priority;
    Queue* q = &pq->queues[m];

    Node* node = q->head;
    int result = node->data;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
        while (pq->max_priority >= 0 && pq->queues[pq->max_priority].head == NULL) {
            pq->max_priority--;
        }
    }

    free(node);
    return result;
}

int DequeueByPriority(PriorityQueue* pq, int priority) {
    if (priority < 0 || priority > 255) {
        printf("Введен неверный приоритет!\n");
        return -1;
    }

    Queue* q = &pq->queues[priority];

    if (q->head == NULL) {
        printf("Нет элементов с приоритетом %d\n", priority);
        return -1;
    }

    Node* node = q->head;
    int result = node->data;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
        while (pq->max_priority >= 0 && pq->queues[pq->max_priority].head == NULL) {
            pq->max_priority--;
        }
    }
    free(node);
    return result;
}

int DequeueWithMinPriority(PriorityQueue* pq, int min_priority) {
    if (min_priority < 0 || min_priority > 255) {
        printf("Введен неверный приоритет!\n");
        return -1;
    }

    int p;
    for (p = 255; p >= min_priority; p--) {
        if (pq->queues[p].head != NULL) {
            break;
        }
    }
    if (p < min_priority) {
        printf("Нет элементов с приоритетом >= %d\n", min_priority);
        return -1;
    }

    Queue* q = &pq->queues[p];

    Node* node = q->head;
    int result = node->data;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
        while (pq->max_priority >= 0 && pq->queues[pq->max_priority].head == NULL) {
            pq->max_priority--;
        }
    }
    free(node);
    return result;
}