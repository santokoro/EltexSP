#include <math.h>
double calc(double a, double b) {
    if (fabs(b) < 1e-12) return 0.0 / 0.0;
    return fmod(a, b);
}
