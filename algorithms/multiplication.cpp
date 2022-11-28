#include "multiplication.h"

using dt = longint::dt;

longint karatsuba(const longint& a, const longint& b)
{
	if (a.buffer.size() > 1 && b.buffer.size() > 1)
		return r_karatsuba(a, b);

	const longint* small = &a, * big = &b;
	if (small->buffer.size() != 1)
		swap(small, big);
	longint ret = *big;
	dmul(ret, small->buffer[0]);
	return ret;
}

longint r_karatsuba(const longint& a, const longint& b)
{
	size_t l = a.buffer.size();
	longint buff;
	const longint* buff_a = &a, * buff_b = &buff;
	if (b.buffer.size() > l)
	{
		l = b.buffer.size();
		buff = a;
		buff_a = &b;
	}
	else buff = b;
	buff.buffer.insert(buff.buffer.end(), l - buff.buffer.size(), 0);

	const auto begin_a = buff_a->buffer.begin(), end_a = buff_a->buffer.end();
	const auto begin_b = buff_b->buffer.begin(), end_b = buff_b->buffer.end();

	l /= 2;
	longint A(vector<dt>(begin_a + l, end_a), false),
		B(vector<dt>(begin_a, begin_a + l), false),
		C(vector<dt>(begin_b + l, end_b), false),
		D(vector<dt>(begin_b, begin_b + l), false);
	longint APB = A + B, CPD = C + D;

	longint AC = karatsuba(A, C);
	longint BD = karatsuba(B, D);
	longint big = karatsuba(A + B, C + D) - AC - BD;

	AC <<= l * 2;
	big <<= l;

	buff = AC + big + BD;
	buff.negative = a.negative ^ b.negative;
	return buff;
}