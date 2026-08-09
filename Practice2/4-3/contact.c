#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct TreeNode* root = NULL;
static int contact_count = 0;
static int ops_since_balance = 0;
#define BALANCE_EVERY 5

static char* str_dup(const char* s) {
    if (!s) s = "";
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

static void free_contact(struct Contact* c) {
    free(c->first_name);
    free(c->last_name);
    free(c->middle_name);
    free(c->job_place);
    free(c->post);
    free(c->number);
    free(c->mail);
    free(c->messengers);
}

static void free_tree(struct TreeNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free_contact(&node->data);
    free(node);
}

static int cmp_contact(struct Contact* a, struct Contact* b) {
    int r = strcmp(a->last_name, b->last_name);
    if (r != 0) return r;
    return strcmp(a->first_name, b->first_name);
}

static struct TreeNode* insert_node(struct TreeNode* node, struct TreeNode* new_node) {
    if (!node) return new_node;
    if (cmp_contact(&new_node->data, &node->data) < 0)
        node->left = insert_node(node->left, new_node);
    else
        node->right = insert_node(node->right, new_node);
    return node;
}

static void store_inorder(struct TreeNode* node, struct Contact* arr, int* i) {
    if (!node) return;
    store_inorder(node->left, arr, i);
    arr[(*i)++] = node->data;
    store_inorder(node->right, arr, i);
}

static struct TreeNode* build_balanced(struct Contact* arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->data = arr[mid];
    node->left = build_balanced(arr, start, mid - 1);
    node->right = build_balanced(arr, mid + 1, end);
    return node;
}

static void balance_tree(void) {
    if (contact_count == 0) return;
    struct Contact* arr = malloc(contact_count * sizeof(struct Contact));
    int i = 0;
    store_inorder(root, arr, &i);
    free_tree(root);
    root = build_balanced(arr, 0, contact_count - 1);
    free(arr);
}

static void check_balance(void) {
    ops_since_balance++;
    if (ops_since_balance >= BALANCE_EVERY) {
        balance_tree();
        ops_since_balance = 0;
    }
}

static struct TreeNode** find_parent_ptr(struct TreeNode** parent, struct Contact* key) {
    if (!*parent) return NULL;
    int cmp = cmp_contact(key, &(*parent)->data);
    if (cmp == 0) return parent;
    if (cmp < 0) return find_parent_ptr(&(*parent)->left, key);
    return find_parent_ptr(&(*parent)->right, key);
}

static struct TreeNode* find_min(struct TreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

static struct TreeNode* delete_node(struct TreeNode* root, struct Contact* key) {
    if (!root) return NULL;
    int cmp = cmp_contact(key, &root->data);
    if (cmp < 0) root->left = delete_node(root->left, key);
    else if (cmp > 0) root->right = delete_node(root->right, key);
    else {
        if (!root->left) {
            struct TreeNode* tmp = root->right;
            free_contact(&root->data);
            free(root);
            return tmp;
        }
        if (!root->right) {
            struct TreeNode* tmp = root->left;
            free_contact(&root->data);
            free(root);
            return tmp;
        }
        struct TreeNode* min = find_min(root->right);
        root->data = min->data;
        root->right = delete_node(root->right, &min->data);
    }
    return root;
}

static void index_inorder(struct TreeNode* node, int* idx, int target, struct TreeNode** out) {
    if (!node || *out) return;
    index_inorder(node->left, idx, target, out);
    if (*idx == target) {
        *out = node;
        (*idx)++;
        return;
    }
    (*idx)++;
    index_inorder(node->right, idx, target, out);
}

static struct TreeNode* get_by_index(int index) {
    if (index < 0 || index >= contact_count) return NULL;
    struct TreeNode* out = NULL;
    int idx = 0;
    index_inorder(root, &idx, index, &out);
    return out;
}

void Init(void) {
    free_tree(root);
    root = NULL;
    contact_count = 0;
    ops_since_balance = 0;
}

void AddContact(struct Contact new_contact) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->data.first_name = str_dup(new_contact.first_name);
    node->data.last_name = str_dup(new_contact.last_name);
    node->data.middle_name = str_dup(new_contact.middle_name);
    node->data.job_place = str_dup(new_contact.job_place);
    node->data.post = str_dup(new_contact.post);
    node->data.number = str_dup(new_contact.number);
    node->data.mail = str_dup(new_contact.mail);
    node->data.messengers = str_dup(new_contact.messengers);
    node->left = NULL;
    node->right = NULL;

    root = insert_node(root, node);
    contact_count++;
    check_balance();
}

void EditContact(int index, struct Contact update_contact) {
    struct TreeNode* target = get_by_index(index);
    if (!target) {
        printf("Ошибка: контакт с индексом %d не найден!\n", index);
        return;
    }

    struct Contact old = target->data;

    if (update_contact.first_name) {
        free(target->data.first_name);
        target->data.first_name = str_dup(update_contact.first_name);
    }
    if (update_contact.last_name) {
        free(target->data.last_name);
        target->data.last_name = str_dup(update_contact.last_name);
    }
    if (update_contact.middle_name) {
        free(target->data.middle_name);
        target->data.middle_name = str_dup(update_contact.middle_name);
    }
    if (update_contact.job_place) {
        free(target->data.job_place);
        target->data.job_place = str_dup(update_contact.job_place);
    }
    if (update_contact.post) {
        free(target->data.post);
        target->data.post = str_dup(update_contact.post);
    }
    if (update_contact.number) {
        free(target->data.number);
        target->data.number = str_dup(update_contact.number);
    }
    if (update_contact.mail) {
        free(target->data.mail);
        target->data.mail = str_dup(update_contact.mail);
    }
    if (update_contact.messengers) {
        free(target->data.messengers);
        target->data.messengers = str_dup(update_contact.messengers);
    }

    if (update_contact.last_name || update_contact.first_name) {
        if (cmp_contact(&old, &target->data) != 0) {
            struct Contact key = old;
            root = delete_node(root, &key);
            struct TreeNode* node = malloc(sizeof(struct TreeNode));
            node->data = target->data;
            node->left = NULL;
            node->right = NULL;
            root = insert_node(root, node);
            free(target);
            check_balance();
        }
    }
}

void DeleteContact(int index) {
    struct TreeNode* target = get_by_index(index);
    if (!target) {
        printf("Ошибка: контакт с индексом %d не найден!\n", index);
        return;
    }
    struct Contact key = target->data;
    root = delete_node(root, &key);
    contact_count--;
    check_balance();
}

static void find_inorder(struct TreeNode* node, const char* last_name, int* idx, int* found) {
    if (!node || *found) return;
    find_inorder(node->left, last_name, idx, found);
    if (!*found && strcmp(node->data.last_name, last_name) == 0) {
        *found = 1;
        return;
    }
    if (!*found) (*idx)++;
    find_inorder(node->right, last_name, idx, found);
}

int FindContact(const char* last_name) {
    int idx = 0;
    int found = 0;
    find_inorder(root, last_name, &idx, &found);
    return found ? idx : -1;
}

void PrintContact(int index) {
    struct TreeNode* c = get_by_index(index);
    if (!c) {
        printf("Ошибка: контакт с индексом %d не найден!\n", index);
        return;
    }
    printf("Имя: %s\n", c->data.first_name[0] ? c->data.first_name : "не указано");
    printf("Фамилия: %s\n", c->data.last_name[0] ? c->data.last_name : "не указано");
    printf("Отчество: %s\n", c->data.middle_name[0] ? c->data.middle_name : "не указано");
    printf("Место работы: %s\n", c->data.job_place[0] ? c->data.job_place : "не указано");
    printf("Должность: %s\n", c->data.post[0] ? c->data.post : "не указано");
    printf("Телефон: %s\n", c->data.number[0] ? c->data.number : "не указано");
    printf("Email: %s\n", c->data.mail[0] ? c->data.mail : "не указано");
    printf("Мессенджеры: %s\n", c->data.messengers[0] ? c->data.messengers : "не указано");
}

static void print_inorder(struct TreeNode* node, int* num) {
    if (!node) return;
    print_inorder(node->left, num);
    printf("--- Контакт #%d ---\n", (*num)++);
    printf("Имя: %s\n", node->data.first_name[0] ? node->data.first_name : "не указано");
    printf("Фамилия: %s\n", node->data.last_name[0] ? node->data.last_name : "не указано");
    printf("Отчество: %s\n", node->data.middle_name[0] ? node->data.middle_name : "не указано");
    printf("Место работы: %s\n", node->data.job_place[0] ? node->data.job_place : "не указано");
    printf("Должность: %s\n", node->data.post[0] ? node->data.post : "не указано");
    printf("Телефон: %s\n", node->data.number[0] ? node->data.number : "не указано");
    printf("Email: %s\n", node->data.mail[0] ? node->data.mail : "не указано");
    printf("Мессенджеры: %s\n", node->data.messengers[0] ? node->data.messengers : "не указано");
    printf("\n");
    print_inorder(node->right, num);
}

void PrintAll(void) {
    if (contact_count == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }
    printf("\n=== Телефонная книга ===\n");
    printf("Всего контактов: %d\n\n", contact_count);
    int num = 1;
    print_inorder(root, &num);
}

int GetCountContact(void) {
    return contact_count;
}