#pragma once
#include <stdint.h>

int parse_ip(const char* s, uint32_t* ip);
void ip_to_str(uint32_t ip, char* buf);
int parse_mask(const char* s, uint32_t* mask);
int is_same_subnet(uint32_t ip, uint32_t gateway, uint32_t mask);
uint32_t generate_random_ip(void);
