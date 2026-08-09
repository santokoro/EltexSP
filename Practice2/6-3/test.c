#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>
#include <math.h>

typedef double (*calc_func)(double, double);

int main() {
    void* h1 = dlopen("libs/add.so", RTLD_LAZY);
    assert(h1);
    calc_func f1 = dlsym(h1, "calc");
    assert(f1);
    assert(f1(2, 3) == 5);

    void* h2 = dlopen("libs/div.so", RTLD_LAZY);
    assert(h2);
    calc_func f2 = dlsym(h2, "calc");
    assert(f2);
    assert(fabs(f2(10, 2) - 5) < 1e-9);

    dlclose(h1);
    dlclose(h2);

    printf("All tests passed!\n");
    return 0;
}
