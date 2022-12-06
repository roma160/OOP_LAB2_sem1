#include "primality.h"

bool primality::lehmer(const longint& n)
{
    longint k = 0;
    longint S(4);
    longint M = longint::long_pow(2, n) - 1;

    while (cmp(k, n - 2) != 0) {
        S = ((S * S) - 2) % M;
        k += 1;
    }

    if (cmp(S, 0) == 0)
        return true;
    return false;
}
