#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <gateway_ip> <mask> <N>\n", argv[0]);
        return 1;
    }

    uint32_t gateway, mask, ip;
    if (parse_ip(argv[1], &gateway) < 0) {
        printf("Invalid gateway IP\n");
        return 1;
    }
    if (parse_mask(argv[2], &mask) < 0) {
        printf("Invalid mask\n");
        return 1;
    }
    int n = atoi(argv[3]);
    if (n <= 0) {
        printf("N must be positive\n");
        return 1;
    }

    srand(time(NULL));

    int local = 0, remote = 0;
    char buf[16];

    for (int i = 0; i < n; i++) {
        ip = generate_random_ip();
        ip_to_str(ip, buf);
        if (is_same_subnet(ip, gateway, mask)) {
            printf("Packet %d: %s -> local\n", i + 1, buf);
            local++;
        } else {
            printf("Packet %d: %s -> remote\n", i + 1, buf);
            remote++;
        }
    }

    printf("\nStatistics:\n");
    printf("Local:  %d (%.2f%%)\n", local, (double)local * 100.0 / n);
    printf("Remote: %d (%.2f%%)\n", remote, (double)remote * 100.0 / n);

    return 0;
}
