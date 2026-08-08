#pragma once

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    struct Node* head;
    struct Node* tail;
} Queue;

typedef struct PriorityQueue {
    Queue queues[256];
    int max_priority;
} PriorityQueue;

void InitPriorityQueue(PriorityQueue* pq);
void AddQueue(PriorityQueue* pq, int value, int priority);
int DequeueMax(PriorityQueue* pq);
int DequeueByPriority(PriorityQueue* pq, int priority);
int DequeueWithMinPriority(PriorityQueue* pq, int min_priority);
