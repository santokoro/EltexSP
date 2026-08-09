#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Contact* head = NULL;
static int contact_count = 0;

static char* str_dup(const char* s) {
    if (!s) s = "";
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

static void free_contact(struct Contact* c) {
    if (!c) return;
    free(c->first_name);
    free(c->last_name);
    free(c->middle_name);
    free(c->job_place);
    free(c->post);
    free(c->number);
    free(c->mail);
    free(c->messengers);
    free(c);
}

static int cmp_contact(const struct Contact* a, const struct Contact* b) {
    int r = strcmp(a->last_name, b->last_name);
    if (r != 0) return r;
    return strcmp(a->first_name, b->first_name);
}

static struct Contact* get_by_index(int index) {
    if (index < 0 || index >= contact_count) return NULL;
    struct Contact* cur = head;
    for (int i = 0; i < index; i++) cur = cur->next;
    return cur;
}

static void insert_sorted(struct Contact* node) {
    node->prev = NULL;
    node->next = NULL;

    if (!head || cmp_contact(node, head) < 0) {
        node->next = head;
        if (head) head->prev = node;
        head = node;
        return;
    }

    struct Contact* cur = head;
    while (cur->next && cmp_contact(node, cur->next) >= 0) {
        cur = cur->next;
    }
    node->next = cur->next;
    if (cur->next) cur->next->prev = node;
    node->prev = cur;
    cur->next = node;
}

void Init(void) {
    struct Contact* cur = head;
    while (cur) {
        struct Contact* next = cur->next;
        free_contact(cur);
        cur = next;
    }
    head = NULL;
    contact_count = 0;
}

void AddContact(struct Contact new_contact) {
    struct Contact* node = malloc(sizeof(struct Contact));
    if (!node) return;
    node->first_name = str_dup(new_contact.first_name);
    node->last_name = str_dup(new_contact.last_name);
    node->middle_name = str_dup(new_contact.middle_name);
    node->job_place = str_dup(new_contact.job_place);
    node->post = str_dup(new_contact.post);
    node->number = str_dup(new_contact.number);
    node->mail = str_dup(new_contact.mail);
    node->messengers = str_dup(new_contact.messengers);

    insert_sorted(node);
    contact_count++;
}

void EditContact(int index, struct Contact update_contact) {
    struct Contact* target = get_by_index(index);
    if (!target) {
        printf("Ошибка: контакт с индексом %d не найден!\n", index);
        return;
    }

    if (target->prev) target->prev->next = target->next;
    else head = target->next;
    if (target->next) target->next->prev = target->prev;

    if (update_contact.first_name) {
        free(target->first_name);
        target->first_name = str_dup(update_contact.first_name);
    }
    if (update_contact.last_name) {
        free(target->last_name);
        target->last_name = str_dup(update_contact.last_name);
    }
    if (update_contact.middle_name) {
        free(target->middle_name);
        target->middle_name = str_dup(update_contact.middle_name);
    }
    if (update_contact.job_place) {
        free(target->job_place);
        target->job_place = str_dup(update_contact.job_place);
    }
    if (update_contact.post) {
        free(target->post);
        target->post = str_dup(update_contact.post);
    }
    if (update_contact.number) {
        free(target->number);
        target->number = str_dup(update_contact.number);
    }
    if (update_contact.mail) {
        free(target->mail);
        target->mail = str_dup(update_contact.mail);
    }
    if (update_contact.messengers) {
        free(target->messengers);
        target->messengers = str_dup(update_contact.messengers);
    }

    insert_sorted(target);
}

void DeleteContact(int index) {
    struct Contact* target = get_by_index(index);
    if (!target) {
        printf("Ошибка: контакт с индексом %d не найден!\n", index);
        return;
    }
    if (target->prev) target->prev->next = target->next;
    else head = target->next;
    if (target->next) target->next->prev = target->prev;
    free_contact(target);
    contact_count--;
}

int FindContact(const char* last_name) {
    struct Contact* cur = head;
    int i = 0;
    while (cur) {
        if (strcmp(cur->last_name, last_name) == 0) return i;
        cur = cur->next;
        i++;
    }
    return -1;
}

void PrintContact(int index) {
    struct Contact* c = get_by_index(index);
    if (!c) {
        printf("Ошибка: контакт с индексом %d не найден!\n", index);
        return;
    }
    printf("Имя: %s\n", c->first_name[0] ? c->first_name : "не указано");
    printf("Фамилия: %s\n", c->last_name[0] ? c->last_name : "не указано");
    printf("Отчество: %s\n", c->middle_name[0] ? c->middle_name : "не указано");
    printf("Место работы: %s\n", c->job_place[0] ? c->job_place : "не указано");
    printf("Должность: %s\n", c->post[0] ? c->post : "не указано");
    printf("Телефон: %s\n", c->number[0] ? c->number : "не указано");
    printf("Email: %s\n", c->mail[0] ? c->mail : "не указано");
    printf("Мессенджеры: %s\n", c->messengers[0] ? c->messengers : "не указано");
}

void PrintAll(void) {
    if (contact_count == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }
    printf("\n=== Телефонная книга ===\n");
    printf("Всего контактов: %d\n\n", contact_count);
    struct Contact* cur = head;
    int i = 1;
    while (cur) {
        printf("--- Контакт #%d ---\n", i++);
        PrintContact(i - 2);
        printf("\n");
        cur = cur->next;
    }
}

int GetCountContact(void) {
    return contact_count;
}