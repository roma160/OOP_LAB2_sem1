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

bool miller_iteration(longint& d, const longint& n, longint& x) {
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
        if (!miller_iteration(d, n, x))
            return false;
    }

    return true;
}

longint gcd(longint a, longint b) {
    if (cmp(b, 0) == 0)
        return a;
    return gcd(b, a % b);
}

longint jacobi(longint a, longint b) {
    longint g;

    if (cmp(a, b) >= 0) a = a % b;
    if (cmp(a, 0) == 0) return 0;
    if (cmp(a, 1) == 0) return 1;
    if (cmp(a, 0) < 0) {
        if (cmp(((b - 1) / 2) % 2, 0) == 0)
            return jacobi(-1 * a, b);
        else
            return -1 * jacobi(-1 * a, b);
    }

    if (cmp(a % 2, 0) == 0) {
        if (cmp(((b * b - 1) / 8) % 2, 0))
            return jacobi(a / 2, b);
        else
            return -1 * jacobi(a / 2, b);
    }

    g = gcd(a, b);

    if (cmp(g, a) == 0)
        return 0;
    else if (cmp(g, 1) != 0)
        return jacobi(g, b) * jacobi(a / g, b);
    else if (cmp(((a - 1) * (b - 1) / 4) % 2, 0) == 0)
        return jacobi(b, a);
    else
        return -1*jacobi(b, a);
}

bool primality::strassen(const longint& n, size_t num)
{
    if (cmp(n,2) != 0 && n[0] % 2 == 0)
        return false;

    if (cmp(n, 2) < 0)
        return false;

    if (cmp(n, 4) < 0)
        return true;

    longint x = 42;
    x = 2 + (7 * x + 9) % (n - 1);

    for (size_t i = 0; i < num; i++)
    {
        longint a = x;
        a = gcd(a, n);
        if (cmp(a, 1) > 0 && cmp(a, n) != 0)
            return false;

        longint jacobian = jacobi(a, n);
        longint temp = longint::long_pow(a, (n - 1) / 2);
        if (cmp(((temp - jacobian) % n), 0) != 0)
            return false;
    }
    return true;
}
