#pragma once

struct Contact {
    char* first_name;
    char* last_name;
    char* middle_name;
    char* job_place;
    char* post;
    char* number;
    char* mail;
    char* messengers;
    struct Contact* prev;
    struct Contact* next;
};

void Init(void);
void AddContact(struct Contact new_contact);
void EditContact(int index, struct Contact update_contact);
void DeleteContact(int index);
int FindContact(const char* last_name);
void PrintContact(int index);
void PrintAll(void);
int GetCountContact(void);
