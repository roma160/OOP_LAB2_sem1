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

bool _test(longint& d, const longint& n, longint& x) {
    x = 2 + (7 * x + 9) % (n - 2);
    longint buff = longint::long_pow(x, d) % n;


    if (cmp(buff, 1) == 0 || cmp(buff, n - 1) == 0)
        return true;

    while (cmp(d, n - 1) != 0) {
        buff = (buff * buff) % n;
        d = d * longint(2);

        if (cmp(buff, 1) == 0) return false;
        if (cmp(buff, n - 1) == 0) return true;
    }
    return false;
}

bool primality::miller(const longint& n, size_t num)
{
    if (cmp(n, longint(2)) != 0 && n[0] % 2 == 0)
        return false;

    if (cmp(n, 1) <= 0 || cmp(n, 4) == 0)
        return false;

    if (cmp(n, 4) < 0)
        return true;

    longint d(n - 1), x(19);
    while (d[0] % 2 == 0) // d % 2 == 0
        d = d / 2;

    for (size_t i = 0; i < num; ++i) {
        if (!_test(d, n, x))
            return false;
    }

    return true;
}
