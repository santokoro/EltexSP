#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
#include <math.h>

typedef double (*calc_func)(double, double);

typedef struct {
    char name[64];
    calc_func func;
    void* handle;
} Op;

static Op ops[64];
static int op_count = 0;

static void load_libs(const char* dir) {
    DIR* d = opendir(dir);
    if (!d) return;
    struct dirent* ent;
    while ((ent = readdir(d)) != NULL) {
        int len = strlen(ent->d_name);
        if (len < 4 || strcmp(ent->d_name + len - 3, ".so") != 0) continue;

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dir, ent->d_name);

        void* h = dlopen(path, RTLD_LAZY);
        if (!h) continue;

        calc_func f = dlsym(h, "calc");
        if (!f) { dlclose(h); continue; }

        strncpy(ops[op_count].name, ent->d_name, len - 3);
        ops[op_count].name[len - 3] = '\0';
        ops[op_count].func = f;
        ops[op_count].handle = h;
        op_count++;
    }
    closedir(d);
}

static void free_libs(void) {
    for (int i = 0; i < op_count; i++) dlclose(ops[i].handle);
    op_count = 0;
}

static void print_menu(void) {
    printf("\n=== Доступные команды ===\n");
    for (int i = 0; i < op_count; i++) printf("%d. %s\n", i + 1, ops[i].name);
    printf("%d. Выход\n", op_count + 1);
    printf("Ваш выбор: ");
}

static double get_num(const char* prompt) {
    double v;
    printf("%s", prompt);
    while (scanf("%lf", &v) != 1) {
        printf("Некорректный ввод. Повторите: ");
        while (getchar() != '\n');
    }
    return v;
}

int main() {
    load_libs("libs");
    if (op_count == 0) {
        printf("Не найдено библиотек в папке libs/\n");
        return 1;
    }

    while (1) {
        print_menu();
        int c;
        if (scanf("%d", &c) != 1) {
            while (getchar() != '\n');
            continue;
        }
        if (c == op_count + 1) {
            printf("До свидания!\n");
            break;
        }
        if (c < 1 || c > op_count) {
            printf("Некорректный номер.\n");
            continue;
        }
        double a = get_num("Первое число: ");
        double b = get_num("Второе число: ");
        double r = ops[c - 1].func(a, b);
        if (isnan(r)) printf("Ошибка: недопустимая операция\n");
        else printf("Результат: %g\n", r);
    }

    free_libs();
    return 0;
}
