#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "priority_queue.h"

static int tests_passed = 0;
static int tests_failed = 0;

static void assert_true(int condition, const char* test_name) {
    if (condition) {
        printf("[OK] %s\n", test_name);
        tests_passed++;
    }
    else {
        printf("[ERROR] %s\n", test_name);
        tests_failed++;
    }
}

static void assert_equal_int(int expected, int actual, const char* test_name) {
    if (expected == actual) {
        printf("[OK] %s (expected: %d, got: %d)\n", test_name, expected, actual);
        tests_passed++;
    }
    else {
        printf("[ERROR] %s (expected: %d, got: %d)\n", test_name, expected, actual);
        tests_failed++;
    }
}

static void print_test_summary(void) {
    printf("\n========================================\n");
    printf("RESULTS:\n");
    printf("  Passed: %d\n", tests_passed);
    printf("  Failed: %d\n", tests_failed);
    printf("========================================\n");
}

static void test_init(void) {
    printf("\n=== Test: InitPriorityQueue ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    assert_equal_int(-1, pq.max_priority, "max_priority = -1 after init");

    int all_empty = 1;
    for (int i = 0; i < 256; i++) {
        if (pq.queues[i].head != NULL) {
            all_empty = 0;
            break;
        }
    }
    assert_true(all_empty, "All subqueues are empty");
}

static void test_add(void) {
    printf("\n=== Test: AddQueue (single priority) ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 5);

    assert_equal_int(5, pq.max_priority, "max_priority = 5");
    assert_equal_int(100, pq.queues[5].head->data, "first node data = 100");
    assert_true(pq.queues[5].head == pq.queues[5].tail, "head == tail for one element");

    AddQueue(&pq, 200, 5);
    assert_equal_int(100, pq.queues[5].head->data, "head remains 100");
    assert_equal_int(200, pq.queues[5].tail->data, "tail became 200");
    assert_true(pq.queues[5].head->next == pq.queues[5].tail, "head->next == tail");
}

static void test_add_different_priorities(void) {
    printf("\n=== Test: AddQueue (different priorities) ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 5);
    AddQueue(&pq, 200, 3);
    AddQueue(&pq, 300, 7);

    assert_equal_int(7, pq.max_priority, "max_priority = 7");
    assert_true(pq.queues[7].head->data == 300, "Priority 7: data = 300");
    assert_true(pq.queues[5].head->data == 100, "Priority 5: data = 100");
    assert_true(pq.queues[3].head->data == 200, "Priority 3: data = 200");
}

static void test_add_lower_priority_does_not_change_max(void) {
    printf("\n=== Test: AddQueue (low priority does not change max) ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 10);
    AddQueue(&pq, 200, 3);

    assert_equal_int(10, pq.max_priority, "max_priority remains 10");
    assert_equal_int(200, pq.queues[3].head->data, "Element with priority 3 added");
}

static void test_dequeue_max(void) {
    printf("\n=== Test: DequeueMax ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 5);
    AddQueue(&pq, 200, 3);
    AddQueue(&pq, 300, 7);
    AddQueue(&pq, 400, 5);
    AddQueue(&pq, 500, 7);

    int val = DequeueMax(&pq);
    assert_equal_int(300, val, "First DequeueMax: 300");
    assert_equal_int(7, pq.max_priority, "max_priority still 7");

    val = DequeueMax(&pq);
    assert_equal_int(500, val, "Second DequeueMax: 500");
    assert_equal_int(5, pq.max_priority, "max_priority became 5");

    val = DequeueMax(&pq);
    assert_equal_int(100, val, "Third DequeueMax: 100");
    assert_equal_int(5, pq.max_priority, "max_priority still 5");

    val = DequeueMax(&pq);
    assert_equal_int(400, val, "Fourth DequeueMax: 400");
    assert_equal_int(3, pq.max_priority, "max_priority became 3");

    val = DequeueMax(&pq);
    assert_equal_int(200, val, "Fifth DequeueMax: 200");
    assert_equal_int(-1, pq.max_priority, "max_priority = -1 (empty)");
}

static void test_dequeue_by_priority(void) {
    printf("\n=== Test: DequeueByPriority ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 5);
    AddQueue(&pq, 200, 3);
    AddQueue(&pq, 300, 7);
    AddQueue(&pq, 400, 5);
    AddQueue(&pq, 500, 3);

    int val = DequeueByPriority(&pq, 5);
    assert_equal_int(100, val, "DequeueByPriority(5): 100");
    assert_equal_int(7, pq.max_priority, "max_priority = 7");

    val = DequeueByPriority(&pq, 7);
    assert_equal_int(300, val, "DequeueByPriority(7): 300");
    assert_equal_int(5, pq.max_priority, "max_priority = 5");

    val = DequeueByPriority(&pq, 5);
    assert_equal_int(400, val, "DequeueByPriority(5) again: 400");
    assert_equal_int(3, pq.max_priority, "max_priority = 3");

    val = DequeueByPriority(&pq, 3);
    assert_equal_int(200, val, "DequeueByPriority(3): 200");
    assert_equal_int(3, pq.max_priority, "max_priority = 3");

    val = DequeueByPriority(&pq, 3);
    assert_equal_int(500, val, "DequeueByPriority(3) again: 500");
    assert_equal_int(-1, pq.max_priority, "max_priority = -1");
}

static void test_dequeue_by_priority_empty_subqueue(void) {
    printf("\n=== Test: DequeueByPriority (empty subqueue) ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 5);
    AddQueue(&pq, 200, 3);

    int val = DequeueByPriority(&pq, 7);
    assert_equal_int(-1, val, "DequeueByPriority(7) with no elements: -1");
    assert_equal_int(5, pq.max_priority, "max_priority unchanged");
}

static void test_dequeue_with_min_priority(void) {
    printf("\n=== Test: DequeueWithMinPriority ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 100, 5);
    AddQueue(&pq, 200, 3);
    AddQueue(&pq, 300, 7);
    AddQueue(&pq, 400, 1);
    AddQueue(&pq, 500, 5);

    int val = DequeueWithMinPriority(&pq, 6);
    assert_equal_int(300, val, "DequeueWithMinPriority(6): 300");
    assert_equal_int(5, pq.max_priority, "max_priority = 5");

    val = DequeueWithMinPriority(&pq, 4);
    assert_equal_int(100, val, "DequeueWithMinPriority(4): 100");
    assert_equal_int(5, pq.max_priority, "max_priority = 5");

    val = DequeueWithMinPriority(&pq, 4);
    assert_equal_int(500, val, "DequeueWithMinPriority(4) again: 500");
    assert_equal_int(3, pq.max_priority, "max_priority = 3");

    val = DequeueWithMinPriority(&pq, 2);
    assert_equal_int(200, val, "DequeueWithMinPriority(2): 200");
    assert_equal_int(1, pq.max_priority, "max_priority = 1");

    val = DequeueWithMinPriority(&pq, 1);
    assert_equal_int(400, val, "DequeueWithMinPriority(1): 400");
    assert_equal_int(-1, pq.max_priority, "max_priority = -1");
}

static void test_errors(void) {
    printf("\n=== Test: Error handling ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    int val = DequeueMax(&pq);
    assert_equal_int(-1, val, "DequeueMax from empty queue: -1");

    val = DequeueByPriority(&pq, 5);
    assert_equal_int(-1, val, "DequeueByPriority from empty queue: -1");

    val = DequeueWithMinPriority(&pq, 5);
    assert_equal_int(-1, val, "DequeueWithMinPriority from empty queue: -1");

    AddQueue(&pq, 100, 256);
    AddQueue(&pq, 100, -1);
    assert_equal_int(-1, pq.max_priority, "Invalid priority does not add element");

    val = DequeueByPriority(&pq, 256);
    assert_equal_int(-1, val, "DequeueByPriority with invalid priority: -1");

    val = DequeueWithMinPriority(&pq, 256);
    assert_equal_int(-1, val, "DequeueWithMinPriority with invalid priority: -1");
}

static void test_fifo(void) {
    printf("\n=== Test: FIFO within same priority ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 1, 5);
    AddQueue(&pq, 2, 5);
    AddQueue(&pq, 3, 5);
    AddQueue(&pq, 4, 5);

    assert_equal_int(1, DequeueMax(&pq), "First: 1");
    assert_equal_int(2, DequeueMax(&pq), "Second: 2");
    assert_equal_int(3, DequeueMax(&pq), "Third: 3");
    assert_equal_int(4, DequeueMax(&pq), "Fourth: 4");
}

static void test_boundary_priorities(void) {
    printf("\n=== Test: Boundary priorities 0 and 255 ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 1, 0);
    AddQueue(&pq, 2, 255);
    AddQueue(&pq, 3, 0);

    assert_equal_int(255, pq.max_priority, "max_priority = 255");

    int val = DequeueMax(&pq);
    assert_equal_int(2, val, "DequeueMax from priority 255: 2");
    assert_equal_int(0, pq.max_priority, "max_priority = 0");

    val = DequeueByPriority(&pq, 0);
    assert_equal_int(1, val, "DequeueByPriority(0) first: 1");

    val = DequeueByPriority(&pq, 0);
    assert_equal_int(3, val, "DequeueByPriority(0) second: 3");
    assert_equal_int(-1, pq.max_priority, "max_priority = -1 after empty");
}

static void test_mixed(void) {
    printf("\n=== Test: Mixed priorities ===\n");
    PriorityQueue pq;
    InitPriorityQueue(&pq);

    AddQueue(&pq, 1, 1);
    AddQueue(&pq, 10, 10);
    AddQueue(&pq, 5, 5);
    AddQueue(&pq, 2, 1);
    AddQueue(&pq, 20, 10);
    AddQueue(&pq, 7, 5);
    AddQueue(&pq, 3, 1);

    assert_equal_int(10, DequeueMax(&pq), "1st DequeueMax: 10");
    assert_equal_int(20, DequeueMax(&pq), "2nd DequeueMax: 20");
    assert_equal_int(5, DequeueMax(&pq), "3rd DequeueMax: 5");
    assert_equal_int(7, DequeueMax(&pq), "4th DequeueMax: 7");
    assert_equal_int(1, DequeueMax(&pq), "5th DequeueMax: 1");
    assert_equal_int(2, DequeueMax(&pq), "6th DequeueMax: 2");
    assert_equal_int(3, DequeueMax(&pq), "7th DequeueMax: 3");
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    setlocale(LC_ALL, "Russian");

    printf("========================================\n");
    printf("    UNIT TESTS\n");
    printf("    Priority Queue\n");
    printf("========================================\n");

    test_init();
    test_add();
    test_add_different_priorities();
    test_add_lower_priority_does_not_change_max();
    test_dequeue_max();
    test_dequeue_by_priority();
    test_dequeue_by_priority_empty_subqueue();
    test_dequeue_with_min_priority();
    test_errors();
    test_fifo();
    test_boundary_priorities();
    test_mixed();

    print_test_summary();

    return (tests_failed == 0) ? 0 : 1;
}