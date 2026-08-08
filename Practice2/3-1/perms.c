#include "perms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show(mode_t m) {
    m &= 0777;
    printf("%c%c%c%c%c%c%c%c%c  %03o  ",
        m & 0400 ? 'r' : '-', m & 0200 ? 'w' : '-', m & 0100 ? 'x' : '-',
        m & 0040 ? 'r' : '-', m & 0020 ? 'w' : '-', m & 0010 ? 'x' : '-',
        m & 0004 ? 'r' : '-', m & 0002 ? 'w' : '-', m & 0001 ? 'x' : '-',
        m);
    for (int i = 8; i >= 0; i--) printf("%d", (m >> i) & 1);
    printf("\n");
}

mode_t from_sym(char* s) {
    mode_t m = 0;
    if (s[0] == 'r') m |= 0400;
    if (s[1] == 'w') m |= 0200;
    if (s[2] == 'x') m |= 0100;
    if (s[3] == 'r') m |= 0040;
    if (s[4] == 'w') m |= 0020;
    if (s[5] == 'x') m |= 0010;
    if (s[6] == 'r') m |= 0004;
    if (s[7] == 'w') m |= 0002;
    if (s[8] == 'x') m |= 0001;
    return m;
}

mode_t from_num(char* s) {
    int n = atoi(s);
    return ((n / 100) % 10) * 64 + ((n / 10) % 10) * 8 + (n % 10);
}

mode_t mod(mode_t cur, char* cmd) {
    int u = 0, g = 0, o = 0, a = 0;
    char* p = cmd;
    while (*p == 'u' || *p == 'g' || *p == 'o' || *p == 'a') {
        if (*p == 'u') u = 1;
        if (*p == 'g') g = 1;
        if (*p == 'o') o = 1;
        if (*p == 'a') a = 1;
        p++;
    }
    if (!u && !g && !o && !a) a = 1;
    char op = *p++;
    mode_t perm = 0;
    while (*p) {
        mode_t b = 0;
        if (*p == 'r') b = 0444;
        if (*p == 'w') b = 0222;
        if (*p == 'x') b = 0111;
        if (u || a) perm |= b & 0700;
        if (g || a) perm |= b & 0070;
        if (o || a) perm |= b & 0007;
        p++;
    }
    mode_t mask = 0;
    if (u || a) mask |= 0700;
    if (g || a) mask |= 0070;
    if (o || a) mask |= 0007;
    if (op == '=') return (cur & ~mask) | perm;
    if (op == '+') return cur | perm;
    if (op == '-') return cur & ~perm;
    return cur;
}