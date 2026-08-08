#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_ip(const char* s, uint32_t* ip) {
    unsigned a, b, c, d;
    if (sscanf(s, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) return -1;
    if (a > 255 || b > 255 || c > 255 || d > 255) return -1;
    *ip = (a << 24) | (b << 16) | (c << 8) | d;
    return 0;
}

void ip_to_str(uint32_t ip, char* buf) {
    sprintf(buf, "%u.%u.%u.%u",
        (ip >> 24) & 0xFF,
        (ip >> 16) & 0xFF,
        (ip >> 8) & 0xFF,
        ip & 0xFF);
}

int parse_mask(const char* s, uint32_t* mask) {
    if (s[0] == '/') {
        int bits = atoi(s + 1);
        if (bits < 0 || bits > 32) return -1;
        *mask = bits == 0 ? 0 : (~0U << (32 - bits));
        return 0;
    }
    return parse_ip(s, mask);
}

int is_same_subnet(uint32_t ip, uint32_t gateway, uint32_t mask) {
    return (ip & mask) == (gateway & mask);
}

uint32_t generate_random_ip(void) {
    return ((uint32_t)rand() << 16) ^ (uint32_t)rand();
}
