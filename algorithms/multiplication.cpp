#include "multiplication.h"

using dt = longint::dt;

longint r_karatsuba(const longint& a, const longint& b);
longint multiplication::karatsuba(const longint& a, const longint& b)
{
    const longint* big = &a, * small = &b;
    if (small->buffer.size() > big->buffer.size())
        swap(big, small);
    size_t l = big->buffer.size();

    if (small->buffer.size() > 1) {
        longint buff = *small;
        buff.denormalize(l);
        return r_karatsuba(*big, buff);
    }
	
	longint ret = *big;
	dmul(ret, small->buffer[0]);
	return ret;
}

longint r_karatsuba(const longint& a, const longint& b)
{
    size_t l = a.buffer.size();

	const auto begin_a = a.buffer.begin(), end_a = a.buffer.end();
	const auto begin_b = b.buffer.begin(), end_b = b.buffer.end();

	l /= 2;
	longint A(vector<dt>(begin_a + l, end_a), false),
		B(vector<dt>(begin_a, begin_a + l), false),
		C(vector<dt>(begin_b + l, end_b), false),
		D(vector<dt>(begin_b, begin_b + l), false);
	longint APB = A + B, CPD = C + D;

	longint AC = multiplication::karatsuba(A, C);
	longint BD = multiplication::karatsuba(B, D);
	longint big = multiplication::karatsuba(A + B, C + D) - AC - BD;

	AC <<= l * 2;
	big <<= l;

	longint buff = AC + big + BD;
	buff.negative = a.negative ^ b.negative;
	return buff;
}


longint r_toomcook(const longint& a, const longint& b);
longint multiplication::toomcook(const longint& a, const longint& b)
{
    const longint* big = &a, * small = &b;
    if (small->buffer.size() > big->buffer.size())
        swap(big, small);
    size_t l = big->buffer.size();

    if (small->buffer.size() > 1) {
        longint buff = *small;
        buff.denormalize(l);
        return r_toomcook(*big, buff);
    }

    longint ret = *big;
    dmul(ret, small->buffer[0]);
    return ret;
}

longint r_toomcook(const longint& a, const longint& b)
{
    size_t l = a.buffer.size();
    l += (3 - l % 3) % 3;
    size_t part_size = l / 3;

    const auto begin_a = a.buffer.begin(), end_a = a.buffer.end();
    const auto begin_b = b.buffer.begin(), end_b = b.buffer.end();

    longint a0(vector<dt>(begin_a, begin_a + part_size), a.negative);
    longint a1(vector<dt>(begin_a + part_size, begin_a + part_size * 2), a.negative);
    longint a2(vector<dt>(begin_a + part_size * 2, begin_a + part_size * 3), a.negative);

    longint b0(vector<dt>(begin_b, begin_b + part_size), b.negative);
    longint b1(vector<dt>(begin_b + part_size, begin_b + part_size * 2), b.negative);
    longint b2(vector<dt>(begin_b + part_size * 2, begin_b + part_size * 3), b.negative);
    
    a1.normalize();
    a2.normalize();
    b0.normalize();
    b1.normalize();
    b2.normalize();

    longint pp0 = a0;
    longint pp1 = a0 + a1 + a2;
    longint pn1 = a0 - a1 + a2;
    longint pn2 = a0 - 2 * a1 + 4 * a2;
    longint pinf = a2;

    longint qp0 = b0;
    longint qp1 = b0 + b1 + b2;
    longint qn1 = b0 - b1 + b2;
    longint qn2 = b0 - b1 * 2 + b2 * 4;
    longint qinf = b2;

    longint rp0 = multiplication::toomcook(pp0, qp0);
    longint rp1 = multiplication::toomcook(pp1, qp1);
    longint rn1 = multiplication::toomcook(pn1, qn1);
    longint rn2 = multiplication::toomcook(pn2, qn2);
    longint rinf = multiplication::toomcook(pinf, qinf);

    longint r0 = rp0;
    longint r4 = rinf;
    longint r3 = (rn2 - rp1) / 3;
    longint r1 = (rp1 - rn1) / 2;
    longint r2 = rn1 - rp0;
    r3 = (r2 - r3) / 2 + rinf * 2;
    r2 = r2 + r1 - r4;
    r1 = r1 - r3;

    return r0 +
        (r1 << part_size) +
        (r2 << part_size * 2) +
        (r3 << part_size * 3) +
        (r4 << part_size * 4);
}
