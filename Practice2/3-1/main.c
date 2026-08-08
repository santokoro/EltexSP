#include "perms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    int c;
    char s[256];
    mode_t m = 0644;
    while (1) {
        printf("\n1 - ввести права\n2 - права файла\n3 - изменить права\n0 - выход\n");
        printf("Выбор: ");
        scanf("%d", &c); getchar();
        if (c == 1) {
            printf("Права (rwxr-xr-x или 755): ");
            fgets(s, sizeof(s), stdin);
            s[strcspn(s, "\n")] = 0;
            if (strlen(s) == 9) m = from_sym(s);
            else m = from_num(s);
            show(m);
        }
        else if (c == 2) {
            printf("Имя файла: ");
            fgets(s, sizeof(s), stdin);
            s[strcspn(s, "\n")] = 0;
            struct stat st;
            if (stat(s, &st) == 0) {
                m = st.st_mode & 0777;
                show(m);
                char cmd[300];
                sprintf(cmd, "ls -l %s", s);
                system(cmd);
            }
            else perror("stat");
        }
        else if (c == 3) {
            printf("Текущие: "); show(m);
            printf("Команда (например u+x, go-w): ");
            fgets(s, sizeof(s), stdin);
            s[strcspn(s, "\n")] = 0;
            m = mod(m, s);
            printf("Новые:   "); show(m);
        }
        else if (c == 0) break;
    }
    return 0;
}