#pragma once
#include <sys/types.h>

void show(mode_t m);
mode_t from_sym(char* s);
mode_t from_num(char* s);
mode_t mod(mode_t cur, char* cmd);