#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

static char* copy(const char* s) {
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

int main() {
    Init();

    int choice;
    char buffer[BUFFER_SIZE];

    do {
        printf("\n========================================\n");
        printf("           ТЕЛЕФОННАЯ КНИГА\n");
        printf("========================================\n");
        printf("1. Добавить контакт\n");
        printf("2. Редактировать контакт\n");
        printf("3. Удалить контакт\n");
        printf("4. Найти контакт по фамилии\n");
        printf("5. Показать все контакты\n");
        printf("6. Показать количество контактов\n");
        printf("0. Выход\n");
        printf("----------------------------------------\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            struct Contact new_contact = {0};

            printf("\n--- Добавление нового контакта ---\n");

            do {
                printf("Введите имя: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
            } while (strlen(buffer) == 0);
            new_contact.first_name = copy(buffer);

            do {
                printf("Введите фамилию: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
            } while (strlen(buffer) == 0);
            new_contact.last_name = copy(buffer);

            printf("Введите отчество (или Enter для пропуска): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_contact.middle_name = copy(buffer);

            printf("Введите место работы (или Enter для пропуска): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_contact.job_place = copy(buffer);

            printf("Введите должность (или Enter для пропуска): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_contact.post = copy(buffer);

            printf("Введите номер телефона (или Enter для пропуска): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_contact.number = copy(buffer);

            printf("Введите email (или Enter для пропуска): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_contact.mail = copy(buffer);

            printf("Введите мессенджеры (или Enter для пропуска): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_contact.messengers = copy(buffer);

            AddContact(new_contact);
            printf("Контакт успешно добавлен!\n");
            break;
        }

        case 2: {
            if (GetCountContact() == 0) {
                printf("Телефонная книга пуста. Нечего редактировать.\n");
                break;
            }

            char surname[BUFFER_SIZE];
            printf("\n--- Редактирование контакта ---\n");
            printf("Введите фамилию контакта для редактирования: ");
            fgets(surname, BUFFER_SIZE, stdin);
            surname[strcspn(surname, "\n")] = '\0';

            int index = FindContact(surname);
            if (index == -1) {
                printf("Контакт с фамилией '%s' не найден.\n", surname);
                break;
            }

            printf("Найден контакт:\n");
            PrintContact(index);

            struct Contact updated_contact = {0};

            printf("\nВведите новые данные (Enter для пропуска):\n");

            printf("Новое имя: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.first_name = copy(buffer);

            printf("Новая фамилия: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.last_name = copy(buffer);

            printf("Новое отчество: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.middle_name = copy(buffer);

            printf("Новое место работы: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.job_place = copy(buffer);

            printf("Новая должность: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.post = copy(buffer);

            printf("Новый телефон: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.number = copy(buffer);

            printf("Новый email: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.mail = copy(buffer);

            printf("Новые мессенджеры: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) updated_contact.messengers = copy(buffer);

            EditContact(index, updated_contact);
            printf("Контакт успешно обновлён!\n");
            break;
        }

        case 3: {
            if (GetCountContact() == 0) {
                printf("Телефонная книга пуста. Нечего удалять.\n");
                break;
            }

            char surname[BUFFER_SIZE];
            printf("\n--- Удаление контакта ---\n");
            printf("Введите фамилию контакта для удаления: ");
            fgets(surname, BUFFER_SIZE, stdin);
            surname[strcspn(surname, "\n")] = '\0';

            int index = FindContact(surname);
            if (index == -1) {
                printf("Контакт с фамилией '%s' не найден.\n", surname);
                break;
            }

            printf("Найден контакт:\n");
            PrintContact(index);

            printf("Вы уверены, что хотите удалить этот контакт? (y/n): ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            if (strcmp(buffer, "y") == 0 || strcmp(buffer, "Y") == 0) {
                DeleteContact(index);
                printf("Контакт удалён.\n");
            } else {
                printf("Удаление отменено.\n");
            }
            break;
        }

        case 4: {
            if (GetCountContact() == 0) {
                printf("Телефонная книга пуста.\n");
                break;
            }

            char surname[BUFFER_SIZE];
            printf("\n--- Поиск контакта ---\n");
            printf("Введите фамилию для поиска: ");
            fgets(surname, BUFFER_SIZE, stdin);
            surname[strcspn(surname, "\n")] = '\0';

            int index = FindContact(surname);
            if (index == -1) {
                printf("Контакт с фамилией '%s' не найден.\n", surname);
            } else {
                printf("Контакт найден:\n");
                PrintContact(index);
            }
            break;
        }

        case 5:
            PrintAll();
            break;

        case 6:
            printf("Всего контактов в книге: %d\n", GetCountContact());
            break;

        case 0:
            printf("До свидания!\n");
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}