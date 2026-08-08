#include "perms.h"
#include <assert.h>
#include <stdio.h>

int main() {
    assert(from_sym("rwxrwxrwx") == 0777);
    assert(from_sym("---------") == 0000);
    assert(from_sym("rwxr-xr-x") == 0755);
    assert(from_sym("rw-r--r--") == 0644);

    assert(from_num("755") == 0755);
    assert(from_num("644") == 0644);
    assert(from_num("777") == 0777);
    assert(from_num("000") == 0000);

    assert(mod(0644, "u+x") == 0744);
    assert(mod(0755, "u-x") == 0655);
    assert(mod(0000, "a+rwx") == 0777);
    assert(mod(0777, "a-rwx") == 0000);
    assert(mod(0644, "o=r") == 0644);
    assert(mod(0644, "u=rwx") == 0744);
    assert(mod(0755, "g=x") == 0715);
    assert(mod(0755, "g=w") == 0725);
    assert(mod(0755, "go-w") == 0755);

    printf("All tests passed!\n");
    return 0;
}
