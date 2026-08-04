#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdint.h>
#include <errno.h>

#define BUF_SIZE 4096

/* Гарантированно записать count байт в fd */
ssize_t write_all(int fd, const void *buf, size_t count) {
    const char *p = buf;
    size_t total = 0;
    while (total < count) {
        ssize_t n = write(fd, p + total, count - total);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        total += n;
    }
    return (ssize_t)total;
}

/* Гарантированно прочитать ровно count байт из fd */
ssize_t read_exact(int fd, void *buf, size_t count) {
    char *p = buf;
    size_t total = 0;
    while (total < count) {
        ssize_t n = read(fd, p + total, count - total);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        if (n == 0)  /* EOF раньше времени */
            return (ssize_t)total;
        total += n;
    }
    return (ssize_t)total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-p fifo_name] file1 [file2 ...]\n", argv[0]);
        return 1;
    }

    int start_files = 1;
    char *fifo_name = NULL;

    if (strcmp(argv[1], "-p") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -p fifo_name file1 [file2 ...]\n", argv[0]);
            return 1;
        }
        fifo_name = argv[2];
        start_files = 3;
    }

    int pc[2] = {-1, -1};   /* parent -> child (обычный pipe) */
    int cp[2];              /* child -> parent (всегда обычный pipe) */
    int pc_read, pc_write;  /* дескрипторы, которые реально используются */

    if (pipe(cp) == -1) {
        perror("pipe cp");
        exit(1);
    }

    if (!fifo_name) {
        if (pipe(pc) == -1) {
            perror("pipe pc");
            exit(1);
        }
        pc_read  = pc[0];
        pc_write = pc[1];
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        /* ========== ДОЧЕРНИЙ ПРОЦЕСС ========== */
        close(cp[0]);   /* ребёнок пишет в cp[1], не читает из cp[0] */

        if (fifo_name) {
            /* Открываем FIFO на чтение; блокируемся, пока родитель не откроет на запись */
            pc_read = open(fifo_name, O_RDONLY);
            if (pc_read < 0) {
                perror("child open fifo");
                exit(1);
            }
        } else {
            close(pc[1]);   /* ребёнок читает из pc[0], не пишет в pc[1] */
            pc_read = pc[0];
        }

        /* Сообщаем родителю, что готовы принимать данные */
        if (write_all(cp[1], "ready", 5) != 5) {
            perror("child write ready");
            exit(1);
        }

        /* Основной цикл приёма файлов */
        while (1) {
            uint32_t name_len;
            if (read_exact(pc_read, &name_len, 4) != 4)
                break;

            if (name_len == 0)  /* сигнал завершения от родителя */
                break;

            if (name_len > 4096) {
                fprintf(stderr, "child: filename too long\n");
                exit(1);
            }

            char *name = malloc(name_len + 1);
            if (!name) {
                perror("child malloc");
                exit(1);
            }

            if (read_exact(pc_read, name, name_len) != (ssize_t)name_len) {
                free(name);
                break;
            }
            name[name_len] = '\0';

            uint64_t file_size;
            if (read_exact(pc_read, &file_size, 8) != 8) {
                free(name);
                break;
            }

            /* Формируем имя выходного файла: имя.copy */
            char *out_name = malloc(name_len + 6);
            if (!out_name) {
                perror("child malloc");
                free(name);
                exit(1);
            }
            strcpy(out_name, name);
            strcat(out_name, ".copy");

            int fd_out = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("child open output");
                free(name);
                free(out_name);
                continue;
            }

            /* Читаем ровно file_size байт из канала и пишем в файл */
            uint64_t remaining = file_size;
            char buf[BUF_SIZE];
            while (remaining > 0) {
                size_t to_read = (remaining < BUF_SIZE) ? (size_t)remaining : BUF_SIZE;
                ssize_t n = read_exact(pc_read, buf, to_read);
                if (n <= 0)
                    break;
                if (write_all(fd_out, buf, (size_t)n) != n)
                    break;
                remaining -= (size_t)n;
            }

            close(fd_out);
            free(name);
            free(out_name);
        }

        close(pc_read);
        close(cp[1]);
        exit(0);

    } else {
        /* ========== РОДИТЕЛЬСКИЙ ПРОЦЕСС ========== */
        close(cp[1]);   /* родитель читает из cp[0], не пишет в cp[1] */

        if (fifo_name) {
            /* Создаём FIFO, если ещё не существует */
            if (mkfifo(fifo_name, 0666) == -1 && errno != EEXIST) {
                perror("mkfifo");
                exit(1);
            }
            /* Открываем на запись; блокируемся, пока ребёнок не откроет на чтение */
            pc_write = open(fifo_name, O_WRONLY);
            if (pc_write < 0) {
                perror("parent open fifo");
                exit(1);
            }
        } else {
            close(pc[0]);   /* родитель пишет в pc[1], не читает из pc[0] */
            pc_write = pc[1];
        }

        /* Ждём сигнала готовности от дочернего процесса */
        char ready_buf[6] = {0};
        if (read_exact(cp[0], ready_buf, 5) == 5) {
            ready_buf[5] = '\0';
            /* Можно раскомментировать для отладки: */
            /* printf("Parent: child is %s\n", ready_buf); */
        }

        /* Цикл по всем указанным файлам */
        for (int i = start_files; i < argc; i++) {
            struct stat st;
            if (stat(argv[i], &st) < 0) {
                fprintf(stderr, "Error opening %s: ", argv[i]);
                perror("");
                continue;
            }

            uint32_t name_len = (uint32_t)strlen(argv[i]);
            uint64_t file_size = (uint64_t)st.st_size;

            /* Заголовок: длина имени → имя → размер */
            write_all(pc_write, &name_len, 4);
            write_all(pc_write, argv[i], name_len);
            write_all(pc_write, &file_size, 8);

            int fd_in = open(argv[i], O_RDONLY);
            if (fd_in < 0) {
                fprintf(stderr, "Error opening %s: ", argv[i]);
                perror("");
                continue;
            }

            /* Передаём содержимое блоками */
            char buf[BUF_SIZE];
            ssize_t n;
            while ((n = read(fd_in, buf, BUF_SIZE)) > 0) {
                if (write_all(pc_write, buf, (size_t)n) != n) {
                    perror("parent write to pipe");
                    break;
                }
            }
            close(fd_in);
        }

        /* Сигнал завершения: длина имени = 0 */
        uint32_t zero = 0;
        write_all(pc_write, &zero, 4);

        close(pc_write);
        close(cp[0]);

        if (fifo_name)
            unlink(fifo_name);

        wait(NULL);   /* ждём завершения дочернего процесса */
    }

    return 0;
}
