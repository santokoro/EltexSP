#include "contact.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
    Init();

    struct Contact c1 = {"Иван", "Иванов", "Иванович", "ООО Рога", "Инженер", "111", "ivan@mail.ru", "tg:ivan"};
    struct Contact c2 = {"Петр", "Петров", "Петрович", "ООО Копыта", "Менеджер", "222", "petr@mail.ru", "tg:petr"};
    struct Contact c3 = {"Сидор", "Сидоров", "Сидорович", "ООО Хвост", "Директор", "333", "sid@mail.ru", "tg:sid"};

    AddContact(c1);
    AddContact(c2);
    AddContact(c3);

    assert(GetCountContact() == 3);
    assert(FindContact("Иванов") == 0);
    assert(FindContact("Петров") == 1);
    assert(FindContact("Сидоров") == 2);

    struct Contact upd = {"Иван", "Яковлев", NULL, NULL, NULL, NULL, NULL, NULL};
    EditContact(0, upd);
    assert(FindContact("Яковлев") == 2);
    assert(FindContact("Петров") == 0);

    DeleteContact(0);
    assert(GetCountContact() == 2);
    assert(FindContact("Петров") == -1);
    assert(FindContact("Сидоров") == 0);
    assert(FindContact("Яковлев") == 1);

    printf("All tests passed!\n");
    return 0;
}