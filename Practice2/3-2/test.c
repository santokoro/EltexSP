#include "network.h"
#include <assert.h>
#include <stdio.h>

int main() {
    uint32_t ip, mask;

    assert(parse_ip("192.168.1.1", &ip) == 0);
    assert(ip == 0xC0A80101);

    assert(parse_ip("10.0.0.0", &ip) == 0);
    assert(ip == 0x0A000000);

    assert(parse_mask("255.255.255.0", &mask) == 0);
    assert(mask == 0xFFFFFF00);

    assert(parse_mask("/24", &mask) == 0);
    assert(mask == 0xFFFFFF00);

    assert(parse_mask("/16", &mask) == 0);
    assert(mask == 0xFFFF0000);

    assert(parse_mask("/0", &mask) == 0);
    assert(mask == 0);

    assert(parse_mask("/32", &mask) == 0);
    assert(mask == 0xFFFFFFFF);

    assert(is_same_subnet(0xC0A80105, 0xC0A80101, 0xFFFFFF00) == 1);
    assert(is_same_subnet(0xC0A80201, 0xC0A80101, 0xFFFFFF00) == 0);

    printf("All tests passed!\n");
    return 0;
}
